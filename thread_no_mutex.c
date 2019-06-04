#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>

int sharedi = 0;
/* a question for programmmer with no thread programming 
experience would be what's the range of shardi 
*/
void increse_num(void *message);
pid_t gettid();

int main()
{
    int ret;
    pthread_t thrd1, thrd2, thrd3;
    char *message1 = "thread1";
    char *message2 = "thread2";
    char *message3 = "thread3";
    printf("#### In %s: threadid = %ld, pid = %ld ######\n", "Main", gettid(), getpid());

    ret = pthread_create(&thrd1, NULL, (void *)increse_num, (void *)message1);
    ret = pthread_create(&thrd2, NULL, (void *)increse_num, (void *)message2);
    ret = pthread_create(&thrd3, NULL, (void *)increse_num, (void *)message3);

    pthread_join(thrd1, NULL);
    pthread_join(thrd2, NULL);
    pthread_join(thrd3, NULL);

    printf("sharedi = %d\n", sharedi);

    return 0;
}

void increse_num(void *message)
{
    long i, tmp;
    for (i = 0; i <= 100000; i++)
    {
        tmp = sharedi;
        tmp = tmp + 1;
        sharedi = tmp;
        printf("#### In %s: threadid = %ld, pid = %ld, sharedi = %d, i = %ld ######\n", (char *)message, gettid(), getpid(), sharedi, i);
    }
}

pid_t gettid()
{
    return syscall(__NR_gettid);
}