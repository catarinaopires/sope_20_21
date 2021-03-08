#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// a.
int alinea_a() {
    int proc;
    int pp[2];
    if (pipe(pp) == -1) {
        perror("pipe()");
        exit(1);
    }
    if ((proc = fork()) == -1) {
        perror("fork()");
        exit(2);
    }
    // CHILD
    if (proc == 0) {
        char msg[1024];
        close(pp[1]);

        read(pp[0], msg, 1024); // waits...
        strcat(msg, "Systems");

        printf("Result: «%s»\n", msg);
        close(pp[0]);
    }
    // PARENT
    else {
        close(pp[0]);
        write(pp[1], "Operating ", 1 + strlen("Operating "));
        close(pp[1]);
    }
}

// b.
int alinea_b() {

    int proc;
    int pp[2];

    // READER:
    int np;
    char msg[1024];

    if ((proc = fork()) == -1) {
        perror("fork()");
        exit(2);
    }
    // CHILD
    if (proc == 0) {
        if (mkfifo("np", 0666) < 0)
            perror("mkfifo");

        while ((np = open("/tmp/np", O_RDONLY)) < 0)
            ;                // synchronization...
            
        read(np, msg, 1024); // waits...
        strcat(msg, "Systems");
        printf("Result: «%s»\n", msg);
        close(np);
    }
    // PARENT
    else {
        // WRITER:
        if (mkfifo("np", 0666) < 0)
            perror("mkfifo");

        while ((np = open("/tmp/np", O_WRONLY)) < 0)
            ; // synchronization...

        write(np, "Operating ", 1 + strlen("Operating "));
        close(np);
    }
}

// c.
int alinea_c() {
    int proc;
    int pp[2];

    if (pipe(pp) == -1) {
        perror("pipe()");
        exit(1);
    }
    if ((proc = fork()) == -1) {
        perror("fork()");
        exit(2);
    }
    // CHILD
    if (proc == 0) {
        char msg[1024];
        close(pp[1]);

        read(pp[0], msg, 1024); // waits...

        printf("Result: «%s %s» \n", "Operating", msg);
        close(pp[0]);
        
    }
    // PARENT
    else {
        close(pp[0]);
        write(pp[1], "Systems", 1 + strlen("Systems"));
        close(pp[1]);
    }
}

// d.
int alinea_d() {

    int proc;
    int pp[2];

    // READER:
    int np;
    char msg[1024];

    if ((proc = fork()) == -1) {
        perror("fork()");
        exit(2);
    }
    // CHILD
    if (proc == 0) {
        if (mkfifo("np", 0666) < 0)
            perror("mkfifo");

        while ((np = open("/tmp/np", O_RDONLY)) < 0)
            ;                // synchronization...
            
        read(np, msg, 1024); // waits...

        printf("Result: «%s %s» \n", "Operating", msg);
        close(np);
    }
    // PARENT
    else {
        // WRITER:
        if (mkfifo("np", 0666) < 0)
            perror("mkfifo");

        while ((np = open("/tmp/np", O_WRONLY)) < 0)
            ; // synchronization...

        write(np, "Systems", 1 + strlen("Systems"));
        close(np);
    }
}


int main(int argc, char *argv[], char *envp[]) {
    alinea_a();
    //alinea_b();
    //alinea_c();
    //alinea_d();
}