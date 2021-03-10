#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>
#include <dirent.h>

void printDir(char *file_path)
{

    struct stat sb;
    // Check if 'base_path' is a directory. If not, nothing to do, return 0.
    if (stat(file_path, &sb) == 0 && S_ISDIR(sb.st_mode))
    {

        char new_path[100];
        struct dirent *dp;
        DIR *dir = opendir(file_path);

        if (dir == NULL)
        {
            printf("cannot read directory '%s': Permission denied\n", file_path);
            exit(1);
        }

        // Iterate through the directory
        while ((dp = readdir(dir)) != NULL)
        {
            if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
            {

                int pid = fork();
                int status;
                switch (pid)
                {
                case -1:
                    perror("Error in fork()\n");
                    break;

                case 0:
                    strcpy(new_path, file_path);
                    strcat(new_path, "/");
                    strcat(new_path, dp->d_name);

                    //printf("\n%s", new_path);
                    printDir(new_path);
                    exit(0);

                default:
                    break;
                }
            }
        }
        closedir(dir);
    }
    else {
        printf("\n%s", file_path);
    }

}

int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);
    char *file_path = argv[1];
    printDir(file_path);

    printf("\n\nterminated main\n");
    
}