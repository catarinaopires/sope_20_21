#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 2

void *perform_work(void *arguments) {
    char *str = *((char **)arguments);

    char **ret = malloc(sizeof(char *));
    *ret = str;
    pthread_exit(ret);
}

int main(void) {
    pthread_t threads[NUM_THREADS];
    char *thread_args[NUM_THREADS];
    int i;
    int result_code;

    //create all threads one by one
    for (i = 0; i < NUM_THREADS; i++) {
        if (i == 0) {
            thread_args[i] = "Operating ";
        }
        else {
            thread_args[i] = "Systems\n";
        }
        result_code = pthread_create(&threads[i], NULL, perform_work, &thread_args[i]);
        assert(!result_code);
    }

    //wait for each thread to complete
    for (i = 0; i < NUM_THREADS; i++) {
        char **res;
        result_code = pthread_join(threads[i], &res);
        assert(!result_code);
        printf("%s", *res);
    }

    return 0;
}