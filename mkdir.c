#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
int main(int argc,char *argv[])
{
    if(argc != 2)
    {
        printf("argc error\n");
        exit(0);
    }
    if(mkdir(argv[1],0777) == -1)
    {
        perror("mkdir error");
        exit(1);
    }
    exit(0);
}

