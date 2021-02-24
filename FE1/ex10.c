#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[], char *envp[]){

    clock_t starting_time = clock();

    for (int i = 0; i < 100000; i++)
        printf("Hello World!");

    clock_t finishing_time = clock();

    double time_elapsed = (double) (finishing_time - starting_time) / CLOCKS_PER_SEC;
    printf("Elapsed time: %.6f\n", time_elapsed);

    return 0;
}

// Note: Try with "time ./exec"