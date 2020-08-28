//Program to understand reader in System V process
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

    
    //read the data received
    //Here the data persists until shared memory isn't removed
    printf("\n%ld bytes Data Received from Writer : %s\n",strlen(buffer)-1,buffer);

    if( shmdt(buffer) == -1)
    {
        perror("Error in detaching the shared memory\n");
        unlink("mykeyfile");
        return EXIT_FAILURE;
    }
    #ifdef __DEBUG__
    printf("shared memory detached successfully with shmid = %d\n",shmid);
    #endif
    //delete the shared memory
    if( shmctl(shmid,IPC_RMID,NULL) == -1)
    {
        perror("Error in deleting the shared memory\n");
        unlink("mykeyfile");
        return EXIT_FAILURE;
    }
    #ifdef __DEBUG__
    printf("shared memory deleted successfully with shmid = %d\n",shmid);
    #endif
    //delete the keyfile
    if(unlink("mykeyfile") == -1)
    {
        perror("Error in removing key file\n");
        return EXIT_FAILURE;
    }
    #ifdef __DEBUG__
    printf("keyfile deleted successfully\n");
    #endif
   
}