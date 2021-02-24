#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// a)
// int main(int argc, char *argv[]){

//     int file_to_read = open(argv[1], O_RDONLY);
//     int file_to_write = open(argv[2], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
//     char buf[1024];
//     int n;

//     if(file_to_read != -1 && file_to_write != -1){
//         while ((n = read(file_to_read, buf, 1024)) > 0) {
//             if (write(file_to_write, buf, n) != n){
//                 printf("Failure inr writing!\n"); 
//                 exit(1);
//             }
//         }

//         close(file_to_read);
//         close(file_to_write);
//     }
//     else    
//         printf("Failure to open!\n");
// }

// b)
// int main(int argc, char *argv[]){

//     FILE * file_to_read = fopen(argv[1], "r+");
//     FILE * file_to_write = fopen(argv[2], "w");
//     char c;

//     if(file_to_read != NULL && file_to_write != NULL){
//         c = fgetc(file_to_read);
//         while(c != EOF){
//             fputc(c, file_to_write);
//             c = fgetc(file_to_read);
//         }

//         fclose(file_to_read);
//         fclose(file_to_write);
//     }
//     else    
//         printf("Failure to open!\n");
// }

// // c)
int main(int argc, char *argv[]){

    FILE * file_to_read = fopen(argv[1], "r+");
    char c;

    if(file_to_read != NULL){
        c = fgetc(file_to_read);
        while(c != EOF){
            printf("%c", c);
            c = fgetc(file_to_read);
        }

        fclose(file_to_read);
    }
    else    
        printf("Failure to open!\n");
}
