#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<assert.h>
#include<pwd.h>

#define PATH "/home/zxb/mydir/gy0118/mybin/"

void myprint()
{
    int uid = getuid();
    char *ti = "$";
    if(uid == 0)
    {
        ti = "#";
    }
    struct passwd *pw = getpwuid(uid);
    if(pw == NULL)
    {
        printf("mybash>>$");
        fflush(stdout);
        return ;
    }
    char host[128] = {0};
    if(gethostname(host,127) == -1 )
    {
        printf("mybash>>$");
        fflush(stdout);
        return ;
    }

    char path[256] = {0};
    char *p = "/";
    if(getcwd(path,256) == NULL)
    {
        perror("getcwd error");
        exit(1);
    }
    char *s = strtok(path,"/");
    while(s != NULL)
    {
        p = s;
        s = strtok(NULL,"/");
    }
    printf("[%s@%s %s]%s",pw->pw_name,host,p,ti);
    fflush(stdout);
}
int main(int argc,char *argv[],char *envp[])
{
    while(1)
    {
       // printf("[zxb@localhost ~]$");
       // fflush(stdout);
       myprint();
        char buff[128] = {0};
        read(0,buff,127);
        buff[strlen(buff) - 1] = 0;
        char *myargv[10] = {0};
        char *s = strtok(buff," ");
        if(s == NULL)
        {
            continue;
        }
        else
        {
            myargv[0] = s;
        }
        int i = 1;
        while((s = strtok(NULL," ")) != NULL)
        {
           myargv[i++] = s;
        }
        if(strcmp(myargv[0],"cd") == 0)
        {
            //if(myargv[1] != NULL)
            //{
            if (chdir(myargv[1]) == -1)
            {
                perror("cd error");
            }

            continue;

        }
        if(strcmp(myargv[0],"exit") == 0)
        {
            break;
        }
        pid_t pid = fork();
        assert(pid != -1);
        if(pid == 0)
        {
            char path[256] = {0};
            if(strcpy(path,"./") == 0 || strcpy(path,"/") == 0)
            {
                strcpy(path,myargv[0]);
            }
            else
            {
                strcpy(path,PATH);
                strcat(path,myargv[0]);
            }
            execv(path,myargv);
            perror("execv error");
            exit(0);
        }
        else
        {
            wait(NULL);
        }
    }
}
