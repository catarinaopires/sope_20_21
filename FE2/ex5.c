#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]){
    int id = fork();

    switch (id) {
        case -1: 
            perror ("fork"); 
            exit (1);

        case 0: 
            // CHILD
            printf("Hello "); 
            break;

        default: 
            // PARENT
            if (wait(&status))
                printf(" World!\n");
    }
}