#include <stdio.h>

// Exercise 5a
// int main(int argc, char *argv[], char *envp[]){
//     printf("Displaying args: \n");
//     for(int i = 0; i < argc; i++){
//         printf("%s\n", argv[i]);
//     }

//     printf("\nEnvironment variables:\n");
//     for(int i = 0; i < argc; i++){
//         printf("%s\n", envp[i]);
//     }
// }

// Exercise 5b
int main(int argc, char *argv[], char *envp[]){

    printf("\nEnvironment variables:\n");
    for(int i = 0; i < argc; i++){
        const char* s = getenv(argv[i]);

        printf("%s : ",argv[i]);
        if(s != NULL)
            printf("%s\n", getenv(argv[i]));
        else
            printf("NULL\n");
        
    }
}

// Confirmed in terminal with:
// echo "$HOME"
//  OR
// printenv #name of variable#(displays all environment variables and its values)
// printenv HOME
