//Program to understand the POSIX shared memory concept using consumer problem
#include<stdio.h>
#include<stdlib.h>
//for shm_open()
#include <sys/stat.h> 
#include <fcntl.h>
#include <sys/mman.h>

//for ftruncate
#include <unistd.h>
#include <sys/types.h>


int main()
{
    int shm_fd  ;
    const int SIZE = 1024;
    const char *name="shmfile";
    if( (shm_fd = shm_open(name,O_CREAT | O_RDWR,0666))== -1)
    {
        perror("Error in opening shared memory");
        return EXIT_FAILURE;
    }
    //configure the size of the shared memory
    int ret_ftruncate  ;
    if( (ret_ftruncate = ftruncate(shm_fd,SIZE))== -1)
    {
        perror("Error in truncating the file to required size");
        return EXIT_FAILURE;
    }

    //create a new address space in virtual memory corresponding to the 
    //shared memory file descriptor with write protection.
    void *mmap_ptr ;
    if( (mmap_ptr= mmap(0,SIZE,PROT_READ,MAP_SHARED,shm_fd,0)) == (void*)-1)
    {
        perror("Error in mmap");
        return EXIT_FAILURE;
    }
    printf("Received Data : %s ",(char*)mmap_ptr);
    //close the shm file
    int ret_shm ;
    if( (ret_shm = shm_unlink(name ))== -1)
    {
        perror("Error in unlinking the shared memory");
        return EXIT_FAILURE;
    }
    

}