#include <dirent.h>
#include <stdio.h>

int main()
{
    char Start[100];
    printf("Enter directory name from where to list files: ");
    scanf("%s", Start);

    struct dirent* CurrDir;
    DIR* DirStream = opendir(Start);

    if(!DirStream){
        printf("Invalid Directory");
    }
    else{
        CurrDir = readdir(DirStream);

        while(CurrDir != NULL){
            printf("%s \n", CurrDir->d_name);
            CurrDir = readdir(DirStream);
        }

        closedir(DirStream);
    }

    return 0;
}