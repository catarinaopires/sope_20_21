// Turn off echoing on screen of keyboard characters: example program.

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

// int main(int argc, char *argv[]) {
// 	char c;
// 	struct termios tms, tms_ini;

//     printf("\nTo end, press [Enter]\n");

//     tcgetattr(STDIN_FILENO, &tms_ini); // read console's configuration
//     tms = tms_ini;

//     tms.c_lflag &= ~ECHO; // inhibit char echoing
//     tcsetattr(STDIN_FILENO, TCSANOW, &tms); // set new configuration

//     do {
// 	    if (read(STDIN_FILENO, &c, 1) != 1)
// 		    perror("read failed");
// 	    } while (c != '\n');	// wait for [ENTER]

//     tcsetattr(STDIN_FILENO, TCSANOW, &tms_ini);	// reset configuration
//     // experiment this program with the above line commented! ;-)
//     printf("\nInitial console configuration has been reset!\n");

//     return 0;
// } // main()

#define MAX_LENGTH 100

int main(int argc, char *argv[]) {
    char username[MAX_LENGTH];
    char pass[MAX_LENGTH];
    struct termios tms, tms_ini;


    printf("username: ");
    fflush(stdout);
    read(STDIN_FILENO, &username, MAX_LENGTH);


    printf("password: ");
    fflush(stdout);
    tcgetattr(STDIN_FILENO, &tms_ini); // read console's configuration
    tms = tms_ini;

    tms.c_lflag &= ~(ECHO | ICANON | ECHOE); // inhibit char echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &tms); // set new configuration

    int i = 0;
    char c;
    read(STDIN_FILENO, &c, 1);
    while (i < MAX_LENGTH && c != '\n') {

        pass[i++] = c;

        if (c == 127) {
            i--;
            write(STDIN_FILENO, "\b \b", 3);
        }
        else {
            write(STDIN_FILENO, "*", 1);
        }

        read(STDIN_FILENO, &c, 1);
    }


    tcsetattr(STDIN_FILENO, TCSANOW, &tms_ini);	// reset configuration
    printf("\nInitial console configuration has been reset!\n\n");

    printf("USERNAME: %s\n", username);
    printf("PASS SUPER CONFIDENTIAL: %s\n", pass);

    return 0;
}
