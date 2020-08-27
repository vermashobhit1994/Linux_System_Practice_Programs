//Program to generate race condition between processes*/
#include<stdio.h>
#define MAX_VAL 100000000
#include<pthread.h>
#include<stdlib.h>
#include<sys/ipc.h>//for ftok()
#include<sys/shm.h>//for shmget(),shmat(),shmctl(),shmdt()
#include<sys/wait.h>//for waitpid()
#include<unistd.h>//for fork()

//global pointer for holding address of shared memory
long long *global_ptr ;

/* Increment function for increment value pointed by global pointer*/
void inc_func()
{
    #ifdef __DEBUG__
    printf("In Increment function\n");
    #endif
    for(int i = 0;i<MAX_VAL;i++)    
        ++*global_ptr;
    
}
/* Decrement function for decrement value pointed by global pointer*/
void dec_func()
{
    #ifdef __DEBUG__
    printf("In Decrement function\n");
    #endif
    for(int i = 0;i<MAX_VAL;i++)    
        --*global_ptr;
    
}


int main()
{
    key_t key1;
    int shmid1;
    //generate a unique key
    if( ( key1 = ftok("shmfile",67) ) == -1)
    {
        perror("Error in creating the key\n");
        return EXIT_FAILURE;
    }
    /*creating shared memory of 8 bytes size with RW permissions 
    for user,group and others with shmid1*/
    if( (shmid1 = shmget(key1,8,IPC_CREAT | 0666) )  == -1)    {
        perror("Error in creating the shared memory\n");
        return EXIT_FAILURE;        
    }
    //attach the shared memory to global_ptr
    if( (global_ptr = (long long*)shmat(shmid1,NULL,0)) == (void*)-1)
    {
        perror("Error in attaching the shared memory\n");
        return EXIT_FAILURE;               
    }
    *global_ptr = 0;//initalize global_ptr as 0 in shared memory
    pid_t cpid = fork();
/******************Child Process Start*****************************************************/
    /* Child Process Increment the global pointer value*/
    if(cpid == 0)
    {
        inc_func();
        if(shmdt(global_ptr) == -1)
        {
            perror("Error in detaching shared memory in Child process\n");
            return EXIT_FAILURE;
        }

    }
/******************Child Process Ends*****************************************************/


/******************Parent Process Start*****************************************************/
    else
    {
        dec_func();
        #ifdef __DEBUG__
        printf("Waiting for child to finish......\n");
        #endif
        
        if(waitpid(cpid,NULL,0) == -1)//waiting for child to complete
        {
            perror("Error in waiting for the child\n");
            return EXIT_FAILURE;
        }
        //print the global_ptr value
        printf("In Parent global_val = %lld\n",*global_ptr);
        if(shmdt(global_ptr) == -1)
        {
            perror("Error in detaching shared memory in Parent process\n");
            return EXIT_FAILURE;
        }
        //mark to delete the shared memory
        if(shmctl(shmid1,IPC_RMID,NULL) == -1)
        {
            perror("Error in detaching shared memory in Parent process\n");
            return EXIT_FAILURE;
        } 

        
    }

/******************Parent Process Ends*****************************************************/
    
}