/* Testing access issues to shared variables
 * - Race conditions!
 * JMMC - Out.2001
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUF_SIZE 20
#define MAX_ITER 100000
long count;
long iter;
void *consumer_thr(void *);
void *producer_thr(void *);

pthread_mutex_t mutex;
pthread_cond_t emptyCond;
pthread_cond_t fullCond;


int main(int argc, char *argv[]) {
	pthread_t *pconsumer_id, *pproducer_id;
	int nthreads;
	int i;

	setbuf(stdout,NULL);
	if (argc < 2) {
		printf("\nUsage: %s #threads\n", argv[0]);
		exit(1);
	}
	nthreads = atoi(argv[1]);
	pconsumer_id = (pthread_t *) malloc(nthreads * sizeof(pthread_t));
	if (pconsumer_id == NULL) {
		perror("malloc");
		exit(2);
	}

    pproducer_id = (pthread_t *) malloc(nthreads * sizeof(pthread_t));
	if (pproducer_id == NULL) {
		perror("malloc");
		exit(2);
	}


    /* Initialize primitives */
	pthread_cond_init(&emptyCond, NULL);
	pthread_cond_init(&fullCond, NULL);
    pthread_mutex_init(&mutex, NULL);

    /* Create equal number of producer and consumer threads */
	for (i = 0; i< nthreads; i++) {
		if(pthread_create(&pconsumer_id[i],NULL,consumer_thr,NULL) != 0 ||
           pthread_create(&pproducer_id[i],NULL,producer_thr,NULL) != 0) {
			perror("pthread_create");
			exit(3);
		}
	}

    /* Wait for everyone to be finished */
	for (i = 0; i< nthreads; i++){
		pthread_join(pconsumer_id[i],NULL);
		pthread_join(pproducer_id[i],NULL);

    }

    /* Destroy primitives */
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&emptyCond);
    pthread_cond_destroy(&fullCond);

	printf("\nEND!\n");
	return 0;
}


void *consumer_thr(void * arg) {

   while (1) { 
	   pthread_mutex_lock(&mutex);
		while (iter < MAX_ITER && count <= 0) {
        	pthread_cond_wait(&fullCond, &mutex); 
		}

		if (iter < MAX_ITER){

			printf("\niter: %ld", iter);
			count--;
        	iter++;
		}
	
		pthread_cond_broadcast(&emptyCond);
		pthread_mutex_unlock(&mutex);

		if (iter >= MAX_ITER)
			break;
		
	}
    
	return (NULL);  
}

void *producer_thr(void * arg) {
	while (1) { 
	   	pthread_mutex_lock(&mutex);
		while (iter < MAX_ITER && count >= BUF_SIZE) {
        	pthread_cond_wait(&emptyCond, &mutex); 
		}

		if (iter < MAX_ITER){

			printf("\niter: %ld", iter);
			count++;
        	iter++;
		}
	
		pthread_cond_broadcast(&fullCond);
		pthread_mutex_unlock(&mutex);

		if (iter >= MAX_ITER)
			break;
		
	}

	return (NULL);
}
