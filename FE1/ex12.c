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

    printf("\n%s", file_path);

    struct stat sb;
    // Check if 'base_path' is a directory. If not, nothing to do, return 0.
    if (stat(file_path, &sb) == 0 && S_ISDIR(sb.st_mode))
    {

        char new_path[100];
        struct dirent *dp;
        DIR *dir = opendir(file_path);

        if (dir == NULL)
        {
            printf("xmod: cannot read directory '%s': Permission denied\n", file_path);
            exit(1);
        }

        // Iterate through the directory
        while ((dp = readdir(dir)) != NULL)
        {
            if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
            {

                strcpy(new_path, file_path);
                strcat(new_path, "/");
                strcat(new_path, dp->d_name);
                printf("\n%s", new_path);

                printDir(new_path);
            }
        }
        closedir(dir);
    }
}

int main(int argc, char *argv[])
{
    printDir(argv[1]);
    return 1;
}