#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<assert.h>
#include<pwd.h>

int main(int argc,char *argv[])
{
    char *s = "root";
    if(argc == 2)
    {
        s = argv[1];
    }

    struct passwd *p = getpwnam(s);
    if(p == NULL)
    {
        printf("user:%s not found\n",s);
        exit(1);
    }

    pid_t pid = fork();
    assert(pid != -1);
    if(pid == 0)
    {
        setgid(p->pw_gid);
        setuid(p->pw_uid);
        execl(p->pw_shell,p->pw_shell,(char *)0);
        perror("execl error");
        exit(1);
    }
    wait(NULL);
}
