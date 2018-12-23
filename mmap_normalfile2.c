/*-------------mmap_normalfile2.c-----------*/
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
 
main(int argc, char** argv)  // map a normal file as shared mem:
{
    int fd,i;
    person *p_map;
    
    //open file
    fd=open( argv[1],O_CREAT|O_RDWR,00777 );
    
    //create mmap and read
    p_map = (person*)mmap(NULL,sizeof(person)*100, PROT_READ|PROT_WRITE, MAP_SHARED,fd,0);
    for(i = 0;i<25;i++)
    {
        printf( "name: %s age %d;\n",(*(p_map+i)).name, (*(p_map+i)).age );
    }
    
    //unmap
    munmap((char*)p_map,sizeof(person)*100);
}
