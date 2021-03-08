/*
*	Example of threads in action
*/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NTHREADS 3

void *rot(void *a) {
    printf("\n\t In thread PID: %d ; TID: %lu.", getpid(), (unsigned long) pthread_self());
    int i = *((int *) a);
    int *ret = malloc(sizeof (int));
    *ret = i*i;
    pthread_exit(ret);    
}

int main() {
    int i;    // thread counter
    pthread_t ids[NTHREADS];    // storage of (system) Thread Identifiers
    int thread_args[NTHREADS];
    // new threads creation
    for (i = 0; i < NTHREADS; i++) {
        thread_args[i] = i;
        if (pthread_create(&ids[i], NULL, rot, &thread_args[i]) != 0)
            exit(-1);    // here, we decided to end process
        else
            printf("\nNew thread %d ; TID: %lu.", i, (unsigned long) ids[i]);

    }

    sleep(5);
    
    // wait for finishing of created threads
    for (i = 0; i < NTHREADS; i++) {
        int *result;
        pthread_join(ids[i], &result);    // Note: threads give no termination code
        printf("\nTermination of thread %d: %lu. -> result: %d\n\n", i, (unsigned long) ids[i], (int) *result);
    }

    printf("\n");
    pthread_exit(NULL);    // here, not really necessary...
    return 0;    // will not run this!
}
