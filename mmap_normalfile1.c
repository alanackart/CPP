/*-------------map_normalfile1.c-----------*/
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
 
#include <stdio.h>
#include <string.h>
 
typedef struct{
    char name[4];
    int  age;
}person;
 
main(int argc, char** argv) // map a normal file as shared mem:
{
    int fd,i;
    person *p_map;
    char temp[4];
    
    //open file
    fd=open(argv[1],O_CREAT|O_RDWR|O_TRUNC,00777);
    printf("file opened\n");
/*  man open
NAME
     open, openat - open a file
SYNOPSIS
     #include <sys/types.h>
     #include <sys/stat.h>
     #include <fcntl.h>
     int open(const char *path, int oflag,  mode_t mode ...);
DESCRIPTION
     The open() function establishes  the  connection  between  a
     file and a file descriptor. It creates an open file descrip-
     tion that refers to a file and a file descriptor that refers
     to  that  open file description. The file descriptor is used
     by other I/O functions to refer  to  that  file.   The  path
     argument points to a pathname naming the file.
     The file offset used to mark the current position within the
     file is set to the beginning of the file.
     The file status flags and file access modes of the open file
     description  are  set  according  to the value of oflag. The
     mode argument is used only when O_CREAT  is  specified  (see
     below.)
     Values for oflag are constructed by  a  bitwise-inclusive-OR
     of  flags  from  the  following  list, defined in <fcntl.h>.
     Applications must specify exactly one  of  the  first  three
     values (file access modes) below in the value of oflag:
     O_RDONLY
           Open for reading only.
     O_WRONLY
           Open for writing only.
     O_RDWR
           Open for reading and writing. The result is  undefined
           if this flag is applied to a FIFO.
     Any combination of the following may be used:
     O_APPEND
           If set, the file offset is set to the end of the  file
           prior to each write.
     O_CREAT
           Create the file  if  it  does  not  exist.  This  flag
           requires that the mode argument be specified.
     .....
*/    
    lseek(fd,sizeof(person)*5-1,SEEK_SET);
    write(fd,"",1);
/*
NAME
     lseek - move read/write file pointer
SYNOPSIS
     #include <sys/types.h>
     #include <unistd.h>
     off_t lseek(int fildes, off_t offset, int whence);
DESCRIPTION
     The lseek() function sets the file pointer  associated  with
     the open file descriptor specified by fildes as follows:
        o  If whence is SEEK_SET, the pointer is  set  to  offset
           bytes.
        o  If whence is SEEK_CUR,  the  pointer  is  set  to  its
           current location plus offset.
        o  If whence is SEEK_END, the pointer is set to the  size
           of the file plus offset.
     The symbolic constants SEEK_SET, SEEK_CUR, and SEEK_END  are
     defined in the header <unistd.h>.
*/    
    //create mmap
    p_map = (person*) mmap(NULL, sizeof(person)*100, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    close( fd );
/*
NAME
     mmap - map pages of memory
SYNOPSIS
     #include <sys/mman.h>
     void *mmap(void *addr, size_t len, int prot, int flags,  int
     fildes, off_t off);
DESCRIPTION
     The  mmap()  function  establishes  a  mapping   between   a
     process's  address space and a file or shared memory object.
     The format of the call is as follows:
          pa = mmap(addr, len, prot, flags, fildes, off);
     The  mmap()  function  establishes  a  mapping  between  the
     address  space of the process at an address pa for len bytes
     to the memory object  represented  by  the  file  descriptor
     fildes  at  offset  off  for len bytes. The value of pa is a
     function of the  addr argument and values of flags,  further
     described  below. A successful mmap() call returns pa as its
     result. The address range starting at pa and continuing  for
     len  bytes  will  be legitimate for the possible (not neces-
     sarily current) address space of the process. The  range  of
     bytes  starting  at off and continuing for len bytes will be
     legitimate  for  the  possible  (not  necessarily   current)
     offsets  in  the file or shared memory object represented by
     fildes.
*/    
    //write mmap
    temp[0] = 'a';
    for(i=0; i<25; i++)
    {
        temp[0] += 1;
		temp[1] = '\0';
        memcpy(( *(p_map+i)).name, &temp, 2);
        (*(p_map+i)).age = 20+i;
    }
    printf("initialize over\n");
    
    //unmap the mmap
    sleep(10);
    munmap((char*)p_map, sizeof(person)*100);
    printf("umap ok\n");
    
/*
NAME
     munmap - unmap pages of memory
SYNOPSIS
     #include <sys/mman.h>
     int munmap(void *addr, size_t len);
DESCRIPTION
     The munmap() function removes the mappings for pages in  the
     range  [addr,  addr  + len), rounding the len argument up to
     the  next  multiple  of  the  page  size  as   returned   by
     sysconf(3C).  If  addr is not the address of a mapping esta-
     blished by a prior call to mmap(2), the  behavior  is  unde-
     fined.  After  a  successful call to munmap() and before any
     subsequent mapping of the unmapped pages, further references
     to  these  pages  will result in the delivery of a SIGBUS or
     SIGSEGV signal to the process.
*/
}
