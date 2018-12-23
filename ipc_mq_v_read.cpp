
#include <sys/shm.h>
#include <unistd.h>
 
#include <string.h>
#include <stdio.h>
 
//读端程序要和写端程序保持一致，这样才能互相通信
//定义数据结构
typedef struct{
    char name[4];
    int age;
} person;
 
int main(int argc, char** argv)
{
    int shm_id,i;
    key_t key;
    person *p_map;
    
    //create shm file and get key
    char* name = "./myshm";
    key = ftok(name,1);
    perror("ftok:");
    
    //get shm
    shm_id = shmget(key,4096,IPC_CREAT);
    perror("shmget:");
    
    //link the shm
    p_map = (person*)shmat(shm_id,NULL,0);
    perror("shmat:");
    for(i = 0;i<10;i++)
    {
        printf( "name:%s\n",(*(p_map+i)).name );
        printf( "age %d\n",(*(p_map+i)).age );
    }
    
    //unlink
    shmdt((char*)p_map);
    perror("shmdt:");
    return 0;
}
