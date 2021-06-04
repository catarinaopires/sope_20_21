#include <stdio.h>
#include <string.h>

int main(void)
{
    char buff[15];
    int pass = 0;

    printf("\n Enter the password : \n");
    //gets(buff); -- error, does not stop when the size is being exceeded
    fgets(buff,15,stdin); // It stops when either (n-1) characters are read, 
                          // the newline character is read, or the end-of-file is reached, whichever comes first.
    
    if (strcmp(buff, "thegeekstuff"))
    {
        printf("\n Wrong Password. \n");
    }
    else
    {
        printf("\n Correct Password.\n");
        pass = 1;
    }

    if (pass)
    { // do somelhing priviledged stuff
        printf("\n Root privileges given to the user.\n");
    }

    return 0;
}