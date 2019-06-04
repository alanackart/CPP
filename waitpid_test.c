#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <wait.h>
#include <stdlib.h>

void signal_handler_child()
{
    pid_t pid;
    int stat;
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
        /*
        if (WIFEXITED(stat))
        {
            printf("child exited with RC=%d\n", WEXITSTATUS(stat));
        }
        if (WISIGNALED(stat))
        {
            printf("child exited via signal %d\n", WTERMSIG(stat));
        }
        */
    }
}

void signal_handler_grandchild()
{
    pid_t pid;
    int stat;
    while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
        /* can not compile due to */
        /*
        if (WIFEXITED(stat))
        {
            printf("grandchild exited with RC=%d\n", WEXITSTATUS(stat));
        }
        if (WISIGNALED(stat))
        {
            printf("grandchild exited via signal %d\n", WTERMSIG(stat));
        }
        */
    }
}

void child_func()
{

    pid_t child;
    signal(SIGCHLD, signal_handler_grandchild);
    if ((child = fork()) == 0)
    {
        printf("In Child, pid = %ld, ppid = %ld\n", getpid(), getppid());
        grandchild_func();
    }
    else if (child == (pid_t)(-1))
    {
        printf("fork grandchild fail, errno=%d, error message=%s\n", errno, strerror(errno));
        _exit(-1);
    }
    else
    {
        printf("fork grandchild %ld success\n", child);
    }

    while (1)
    {
        printf("In Child func, pid = %ld, ppid = %ld\n", getpid(), getppid());
        sleep(10);
    }
}

void grandchild_func()
{
    while (1)
    {
        printf("In grandChild func, pid = %ld, ppid = %ld\n", getpid(), getppid());
        sleep(10);
    }
}

int main()
{
    printf("In main, pid = %ld, ppid = %ld\n", getpid(), getppid());
    pid_t child;

    signal(SIGCHLD, signal_handler_child);
    if ((child = fork()) == 0)
    {
        printf("In Child, pid = %ld, ppid = %ld\n", getpid(), getppid());
        child_func();
    }
    else if (child == (pid_t)(-1))
    {
        printf("fork child fail\n");
        _exit(-1);
    }
    else
    {
        printf("fork child %ld success\n", child);
    }
    while (1)
    {
        sleep(10); /* code */
        printf("In main, pid = %ld, ppid = %ld\n", getpid(), getppid());
    }

    return 0;
}
