#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    DIR *dir="/home/nisarg/Desktop/OS/Linux_Programing/Assignment-1/";
    struct dirent *entry;
    int dot_found = 0;
    int dotdot_found = 0;
    struct stat statbuf_dot, statbuf_dotdot;
    
    if (argc != 2){
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    if ((dir = opendir(argv[1])) == NULL){
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    
    while ((entry = readdir(dir)) != NULL) {   
        if (strcmp(entry->d_name, ".") == 0) {
            dot_found = 1;
            stat(argv[1], &statbuf_dot); 
        }
        
        else if (strcmp(entry->d_name, "..") == 0) {
            dotdot_found = 1;
            stat(argv[1], &statbuf_dotdot); 
        }
    }
    closedir(dir);

    if (dot_found && dotdot_found) {
        printf("The entries . and .. in directory '%s' are different.\n", argv[1]);
        printf("Inode number of . : %lu\n", statbuf_dot.st_ino);
        printf("Inode number of .. : %lu\n", statbuf_dotdot.st_ino);
    } 
     
    else if (!dot_found && !dotdot_found) {   
        printf("The entries . and .. in directory '%s' are the same.\n", argv[1]);   
        printf("Inode number of . : %lu\n", statbuf_dot.st_ino);   
        printf("Inode number of .. : %lu\n", statbuf_dotdot.st_ino);
    } 
    
    
    
    else {
        printf("Inconsistent directory structure for '%s'.\n", argv[1]);
    }

    return EXIT_SUCCESS;
}