#include <stdio.h>
#include <unistd.h>
void log_fun(pid_t p){
        printf("in %s, pid=%d, ppid=%d\n",((int)p == 0)? "child": "parent", (int)getpid(), (int)getppid() );
}
int main(){
        pid_t p;
        int i = 2;
        while(i-- > 0){
                p = fork();
                log_fun(p);
        }
        printf("bye!\n" );
        sleep(40); /* so we can check the process */
        return 0;
}
