#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int main(int argc, char * argv[]){
    char name[100];
    if (argc > 1) {
        strcpy(name, argv[1]);
    }else{
        fgets(name, 100, stdin);
        int i = 0;
        while (name[i] != '\n') {
            i++;
        }
        name[i] = '\0';
    }
    DIR* dir = opendir(name);
    struct dirent * cwd = readdir(dir);
    int size = 0;
    char directories[100]="Directories:";
    char files[100]="Regular Files:";
    struct stat file;
    
    if (dir != NULL){
        while (cwd != NULL){
            stat(cwd->d_name, &file);
            if((file.st_mode & S_IFMT) == S_IFDIR){
                strcat(directories,"\n\t");
                strcat(directories,cwd->d_name);
            }else{
                strcat(files,"\n\t");
                strcat(files,cwd->d_name);
            }
            size += file.st_size;            
            cwd = readdir(dir);
        }
    }

    printf("Statistics for directory: %s\nTotal Directory Size: %d Bytes\n", name, size);
    printf("%s\n\n",directories);
    printf("%s\n",files);
    return 0;
}