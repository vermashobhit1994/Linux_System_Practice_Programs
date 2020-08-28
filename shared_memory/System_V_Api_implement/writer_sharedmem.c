// Program to understand the Writer process in System V shared memory
#include<stdio.h>
#define SIZE_SHM 1024//shared memory size of 1KB
#include<stdlib.h>//for EXIT_FAILURE
#include<sys/ipc.h>//for ftok()
#include<unistd.h>//for unlink()
#include<sys/shm.h>//for shmget(),shmdt()
#include<string.h>//for strlen()
#include<fcntl.h>
#define __DEBUG__
int main()
{
            
    //create a file for key
    if( (creat("mykeyfile",O_CREAT | 0666)) == -1)
    {
        perror("Error in creating the key file\n");
        return EXIT_FAILURE;
    }

    //generate a unique key for shared memory
    key_t key;
    if( (key = ftok("mykeyfile",65)) == -1)
    {
        perror("Error in creating the key\n");
        return EXIT_FAILURE;
    }
    //To return an identifier to shmid i.e created
    int shmid;
    if( (shmid = shmget(key,SIZE_SHM,IPC_CREAT | 0666) ) == -1)
    {
        perror("Error in Creating the shared memory\n");
        unlink("mykeyfile");
        return EXIT_FAILURE;
    }
    #ifdef __DEBUG__
    printf("shared memory created successfully with shmid = %d\n",shmid);
    #endif
    // attach the pointer to shared memory with read and write access
    char *buffer;
    if( (buffer = shmat(shmid,NULL,0)) == (void*)-1)
    {
        perror("Error in attaching the shared memory\n");
        unlink("mykeyfile");
        return EXIT_FAILURE;
    }
    #ifdef __DEBUG__
    printf("shared memory attached successfully with shmid = %d\n",shmid);
    #endif

    printf("Enter the string to be sent\n");
    //input the string to be passed to shared memory
    if(fgets(buffer,SIZE_SHM,stdin))
    {
        
        printf("%ld byts Data written to shared memory successfully\n",strlen(buffer)-1);
        printf("Enter the string to be sent\n");
    }
        
    
    if( shmdt(buffer) == -1)
    {
        perror("Error in detaching the shared memory\n");
        unlink("mykeyfile");
        return EXIT_FAILURE;
    }
    #ifdef __DEBUG__
    printf("shared memory detached successfully with shmid = %d\n",shmid);
    #endif
    
    
    
}