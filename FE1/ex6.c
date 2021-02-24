#include <stdio.h>

// Exercise 6a
// int main(){
//     char *filename;
//     printf("Enter filename: ");
//     scanf("%s", filename);

//     FILE * file = fopen(filename, "r+");

//     if(file != NULL)
//         fclose(file);
//     else    
//         printf("Failure to open!\n");
// }

// Exercise 6b
// int main(){
//     char *filename;
//     printf("Enter filename: ");
//     scanf("%s", filename);

//     FILE * file = fopen(filename, "r+");

//     if(file != NULL)
//         fclose(file);
//     else{

//         fprintf( stdout, "ERROR TO STDOUT: Failure to open!\n");
//         fprintf( stderr, "ERROR TO STDERR: Failure to open!\n");
//     }    
// }


// Exercise 6c
int main(){
    char *filename;
    printf("Enter filename: ");
    scanf("%s", filename);

    FILE * file = fopen(filename, "r+");

    if(file != NULL)
        fclose(file);
    else{
        perror("Error: ");
    }    
}


// NOTES:
// printf("%s", "Hello world\n");              // "Hello world" on stdout (using printf)
// fprintf(stdout, "%s", "Hello world\n");     // "Hello world" on stdout (using fprintf)
// fprintf(stderr, "%s", "Stack overflow!\n"); // Error message on stderr (using fprintf)