#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

int main(void) {
    printf("********* Alínea a: ********** \n");
    printf ("_SC_CLK_TCK = %ld\n\n", sysconf (_SC_CLK_TCK)); // nr de ticks per second


    printf("********* Alínea b: ********** \n");
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    printf("seconds : %ld\nmicro seconds : %ld\n\n", current_time.tv_sec, current_time.tv_usec);


    printf("********* Alínea c: ********** \n");
    printf("%ld Bytes\n", sizeof(time_t));

    return 0;
}