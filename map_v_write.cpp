/* 文件：map_v_write.cpp
   描述:和map_v_read.cpp文件配合完成系统V共享内存编程实验
 */
//#include <sys/ipc.h>
//#include <sys/types.h>//注释掉的两个头文件是IPC最基本的，但在shm.h中include过了
#include <sys/shm.h>//系统V共享内存函数shmget shmat shmdt
 
#include <string.h>//memcpy
#include <stdio.h>//perror
#include <errno.h>//errno
 
//共享内存通信多采用结构体数据表达信息，任意定义
typedef struct{
    char name[4];
    int age;
}person;
 
main(int argc, char** argv)
{
    int shm_id,i;
    key_t key;//保存ftok函数返回值
    char temp;
    person *p_map;
 
    //创建IPC键值
    char* name = "./myshm";//务必指定存在的文件
    key = ftok(name, 1);//参数尽量别用0
/*   man ftok:
NAME
     ftok - generate an IPC key
SYNOPSIS
     #include <sys/ipc.h>
     key_t ftok(const char *path, int id);
DESCRIPTION
     The ftok() function returns a key based on path and id  that
     is  usable  in  subsequent calls to msgget(2), semget(2) and
     shmget(2). The path argument must  be  the  pathname  of  an
     existing file that the process is able to  stat(2).
     The ftok() function will return the same key value  for  all
     paths  that name the same file, when called with the same id
     value, and will return different key values when called with
     different id values.
     If the file named by path is removed while still referred to
     by a key, a call to ftok() with the same path and id returns
     an error. If the same file is  recreated,  then  a  call  to
     ftok()  with the same path and id is likely to return a dif-
     ferent key.
     Only the low  order  8-bits  of  id  are  significant.   The
     behavior of ftok() is unspecified if these bits are 0.
RETURN VALUES
     Upon successful completion, ftok() returns  a  key.   Other-
     wise,  ftok()  returns  (key_t)-1 and sets errno to indicate
     the error.
*/
    perror("ftok:");//打印errno, 参考附录errno定义
/*  man perror
NAME
     perror, errno - print system error messages
SYNOPSIS
     #include <stdio.h>
     void perror(const char *s);
     #include <errno.h>
     int errno;
DESCRIPTION
     The perror() function produces a  message  on  the  standard
     error  output  (file descriptor 2) describing the last error
     encountered during a call to a system or  library  function.
     The  argument string s is printed, followed by a colon and a
     blank, followed by the message and a NEWLINE character.   If
     s is a null pointer or points to a null string, the colon is
     not printed. The argument string should include the name  of
     the  program  that  incurred  the error. The error number is
     taken from the external variable errno, which  is  set  when
     errors  occur  but  not cleared when non-erroneous calls are
     made. See  intro(2).
*/
 
    //获取共享内存ID
    shm_id=shmget(key,4096,IPC_CREAT|00666);//give the permissions
    perror("shmget:");
/*  man shmget:
NAME
     shmget - get shared memory segment identifier
SYNOPSIS
     #include <sys/types.h>
     #include <sys/ipc.h>
     #include <sys/shm.h>
     int shmget(key_t key, size_t size, int shmflg);
DESCRIPTION
     The shmget() function returns the shared  memory  identifier
     associated with key.
     A shared memory identifier and associated data structure and
     shared  memory segment of at least size bytes (see intro(2))
     are created for key if one of the following are true:
        o  The key argument is equal to IPC_PRIVATE.
        o  The key argument does not already have a shared memory
           identifier  associated with it, and (shmflg&IPC_CREAT)
           is true.
     Upon creation, the data structure associated  with  the  new
     shared memory identifier is initialized as follows:
        o  The    values    of    shm_perm.cuid,    shm_perm.uid,
           shm_perm.cgid,  and  shm_perm.gid are set equal to the
           effective user ID  and  effective  group  ID,  respec-
           tively, of the calling process.
        o  The access permission bits of  shm_perm.mode  are  set
           equal   to  the  access  permission  bits  of  shmflg.
           shm_segsz is set equal to the value of size.
        o  The values  of  shm_lpid,  shm_nattch  shm_atime,  and
           shm_dtime are set equal to 0.
        o  The shm_ctime is set equal to the current time.
     Shared memory segments must be explicitly removed after  the
     last reference to them has been removed.
RETURN VALUES
     Upon   successful   completion,   a   non-negative   integer
     representing  a shared memory identifier is returned. Other-
     wise, -1 is returned and errno is set to indicate the error.
*/
 
    p_map=(person*)shmat(shm_id,NULL,0);
    perror("shmat:");
/*
NAME
     shmop, shmat, shmdt - shared memory operations
SYNOPSIS
     #include <sys/types.h>
     #include <sys/shm.h>
     void *shmat(int shmid, const void *shmaddr, int shmflg);
  Default
     int shmdt(char *shmaddr);
  Standard conforming
     int shmdt(const void *shmaddr);
DESCRIPTION
     The shmat() function  attaches  the  shared  memory  segment
     associated  with  the  shared memory identifier specified by
     shmid to the data segment of the calling process.    
*/    
    //往内存写入数据
    temp='a';
    for(i = 0;i<10;i++)
    {
        temp+=1;
        memcpy((*(p_map+i)).name,&temp,1);
        (*(p_map+i)).age=20+i;
    }
 
    //unlink共享内存
    shmdt((char*)p_map);//这里可以去掉char*编译试试，我这里去掉后编译不通过，待研究
    perror("shmdt:");
/*
     The shmdt() function detaches  from  the  calling  process's
     data  segment  the  shared  memory  segment  located  at the
     address  specified  by  shmaddr.  If  the   application   is
     standard-conforming (see standards(5)), the shmaddr argument
     is of type const void *. Otherwise it is of type char *.
*/
 
}
