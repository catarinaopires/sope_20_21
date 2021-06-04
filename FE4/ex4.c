#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int SIZE = 50000000;  // 50 MB

int main(int argc, char *argv[], char *envp[]){

    char * str = (char*) malloc(SIZE);
    while (str != NULL) {
        str = (char*) malloc(SIZE);
        sleep(1);
        printf("one more\n");
    }

    printf("Denied\n");
}