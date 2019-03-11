#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
pid_t          pid;
int            restart_flag = 0;
void sig_chld(int signo)
{
    pid_t   pid;
    int     stat,i;
    while((pid = waitpid(-1, &stat, WNOHANG)) > 0)
    {
        printf("crash pid=%ld \n",pid);
        restart_flag = 1;    
    }
       
   
    return;
}
  
void child_func() 
{   while(1) {
        printf("I am child\n");
        sleep(5);
    } 
} 
int main() 
{
    restart_flag = 0; 
    if((pid = fork()) < 0)  
        return -1;
    else if(pid == 0)
    {
        child_func();
    }
    signal(SIGCHLD, sig_chld);
    while(1){
        signal(SIGCHLD, sig_chld);
        if(restart_flag == 1){
             if((pid = fork()) < 0) 
                return -1;
            else if(pid == 0)
            {
                 child_func();
            }
            restart_flag = 0; 
        }
        sleep(3); 
    } 
    return 0; 
} 
