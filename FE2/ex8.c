#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

void printWorld() {
    printf("World: ");
}

int main(int argc, char *argv[], char *envp[]){
    int id = fork();
    signal(SIGCHLD, printWorld);

    switch (id) {
        case -1:
            perror ("fork");
            exit (1);

        case 0:
            // CHILD
            printf("Hello!\n");
            break;

        default:
            // PARENT
            raise(SIGCHLD);
            break;

    }
}

// (the parent process writes "World:" after fork() and before the child writes "Hello!").
// Output: World: Hello!