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

static sem_t s;
static pthread_mutex_t mutex; // make buffer addition/removal atomic

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

    /* Initialize semaphores */
	sem_init(&s, 0, BUF_SIZE);
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

    /* Destroy semaphores */
	sem_destroy(&s);
    pthread_mutex_destroy(&mutex);

	printf("\nEND!\n");
	return 0;
}


void *consumer_thr(void * arg) {
	sem_wait(&s);			// To lock a semaphore or wait we can use the sem_wait function

    pthread_mutex_lock(&mutex);
	while (iter < MAX_ITER) {
		printf("\n%ld",count);
		count--;
        iter++;
	}
	printf("\nEND thread %lu!\n", (unsigned long) pthread_self());
	pthread_mutex_unlock(&mutex);
	sem_post(&s);			// To release or signal a semaphore, we use the sem_post function

	return (NULL);
    
}
void *producer_thr(void * arg) {
    sem_wait(&s);			// To lock a semaphore or wait we can use the sem_wait function

    pthread_mutex_lock(&mutex);
	while (iter < MAX_ITER) {
		printf("\n%ld",count);
		count++;
        iter++;
	}
	printf("\nEND thread %lu!\n", (unsigned long) pthread_self());
	pthread_mutex_unlock(&mutex);
	sem_post(&s);			// To release or signal a semaphore, we use the sem_post function

	return (NULL);
}
