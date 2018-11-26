#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<assert.h>
#include<sys/stat.h>
#include<dirent.h>

int main()
{

    DIR *dir = opendir(".");
    if(NULL == dir)
    {
        printf("no file\n");
        exit(1);
    }
    struct dirent *entry = NULL;
    while((entry = readdir(dir)) != NULL)
    {
        if(strcmp(entry->d_name,".") == 0 || strcmp(entry->d_name,"..") == 0)
        {
            continue;
        }
        else
        {
            struct stat st;
            lstat(entry->d_name,&st);
            if(S_ISDIR(st.st_mode))
            {
                printf("\033[1m\033[34m%s\033[0m  ",entry->d_name);
            }
            else if(S_ISREG(st.st_mode))
            {
                if(st.st_mode & (S_IXUSR | S_IXGRP | S_IXOTH))
                {
                    printf("\033[1m\033[32m%s\033[0m ",entry->d_name);
                }
                else
                {
                    printf("%s ",entry->d_name);
                }

            }
        }
    }
    printf("\n");
    closedir(dir);
    exit(0);
}
