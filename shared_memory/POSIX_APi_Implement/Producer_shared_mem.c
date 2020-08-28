//Program to understand the POSIX shared memory concept using producer consumer problem
/* Link with -lrt flag*/
#include<stdio.h>
#include<stdlib.h>
//for shm_open()
#include <sys/stat.h>//for shm_open() 
#include <fcntl.h>//for O_CREAT
#include <sys/mman.h>//for PROT_WRITE

#include<string.h>

//for ftruncate
#include <unistd.h>
int main()
{
    const int SIZE = 1024;
    int sh_fd = shm_open("/shmfile",O_CREAT |O_RDWR ,0666);
    if(sh_fd == -1)
    {
        perror("Error in opening shared memory");
        return EXIT_FAILURE;
    }
    //configure the size of the shared memory
    int ret_ftruncate ;
    if( (ret_ftruncate= ftruncate(sh_fd,SIZE)) == -1)
    {
        perror("Error in truncating the file to required size");
        return EXIT_FAILURE;
    }

    //create a new address space in virtual memory corresponding to the 
    //shared memory file descriptor
    void *mmap_ptr = mmap(0,SIZE,PROT_WRITE,MAP_SHARED,sh_fd,0);
    if( (mmap_ptr) == (void*)-1)
    {
        perror("Error in mmap");
        return EXIT_FAILURE;
    }
    printf("Enter the first message to be written\n");
    char str [SIZE];    
    scanf(" %[^\n]s",str);//if used fgets then it would add \n also .
    sprintf(mmap_ptr,"%s",str);//put the input string to pointer to shared memory
    mmap_ptr += strlen(str);
    memset(str,0,SIZE);//clear the array
    
    printf("Enter another message\n");
    scanf(" %[^\n]s",str);
    sprintf(mmap_ptr,"%s",str);
    mmap_ptr += strlen(str);
    

}