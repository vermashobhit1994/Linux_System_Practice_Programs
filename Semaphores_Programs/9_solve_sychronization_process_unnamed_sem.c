//Program to understand synchronization among the processes using the unnamed semaphores
#include<stdio.h>
#define MAX_VAL 10000000
#include<pthread.h>
#include<stdlib.h>
#include<sys/ipc.h>//for ftok()
#include<sys/shm.h>//for shmget(),shmat(),shmctl(),shmdt()
#include<sys/wait.h>//for waitpid()
#include<unistd.h>//for fork()
#include<semaphore.h>//for sem_open(),sem_close(),sem_unlink()
#include<fcntl.h>//for O_CREAT

//to activate the debug statements
//#define __DEBUG__

//global pointer for holding address of shared memory
long long *global_ptr ;

//create a global semaphore pointer
sem_t *sem;

/* Increment function for increment value pointed by global pointer*/
void inc_func()
{
    #ifdef __DEBUG__
    printf("In Increment function\n");
    #endif
    for(int i = 0;i<MAX_VAL;i++){ 
    
    //decrement sem variable
        if( sem_wait(sem) != 0)
        {
            perror("Error in waiting for semaphore decrement thread\n");
        }
    #ifdef __DEBUG__
        printf("After the semaphore wait in increment function......\n");
    #endif    
/************Critical section Starts ********************************************************/  
        ++*global_ptr;
    
/************Critical section Ends ********************************************************/  
        if( sem_post(sem) != 0)
        {
            perror("Error in posting for semaphore in decrement thread\n");
        }
    #ifdef __DEBUG__
        printf("After the semaphore post in increment function......\n\n\n");
    #endif
    }    
}
/* Decrement function for decrement value pointed by global pointer*/
void dec_func()
{
    #ifdef __DEBUG__
    printf("In Decrement function\n");
    #endif
    for(int i = 0;i<MAX_VAL;i++){    
    //decrement sem variable
        if( sem_wait(sem) != 0)
        {
            perror("Error in waiting for semaphore decrement function\n");
        }
    #ifdef __DEBUG__
        printf("After the semaphore wait in decrement function......\n");
    #endif
/************Critical section Starts ********************************************************/  
        --*global_ptr;
    
/************Critical section Ends ********************************************************/  
        if( sem_post(sem) != 0)
        {
            perror("Error in posting for semaphore in decrement function\n");
        }
    #ifdef __DEBUG__
        printf("After the semaphore post in decrement function......\n\n\n");
    #endif
   
    }
    
}


int main()
{
    key_t key1;
    int shmid_sem,shmid_global_ptr;
/*********************** CREATE SHARED MEMORY FOR GLOBAL PTR START ********************/
    //generate a unique key
    if( ( key1 = ftok("shmfile_global_ptr",67) ) == -1)
    {
        perror("Error in creating the key\n");
        return EXIT_FAILURE;
    }
    
    /*creating shared memory of 8 bytes size with RW permissions 
    for user,group and others with shmid1*/
    if( (shmid_global_ptr = shmget(key1,8,IPC_CREAT | 0666) )  == -1)    {
        perror("Error in creating the shared memory\n");
        return EXIT_FAILURE;        
    }
    //attach the shared memory to global_ptr
    if( (global_ptr = (long long*)shmat(shmid_global_ptr,NULL,0)) == (void*)-1)
    {
        perror("Error in attaching the shared memory\n");
        return EXIT_FAILURE;               
    }
    *global_ptr = 0;//initalize global_ptr as 0 in shared memory
/************** CREATION OF SHARED MEMORY FOR GLOBAL PTR ENDS************************/    
    
/****************** CREATE SHARED MEMORY FOR SEMAPHORE PTR START*****************************/
    key_t key2;
    //generate a unique key
    if( ( key2 = ftok("shmfile_sem_ptr",67) ) == -1)
    {
        perror("Error in creating the key\n");
        return EXIT_FAILURE;
    }
    
    
    /*creating shared memory of 8 bytes size with RW permissions 
    for user,group and others with shmid1*/
    if( (shmid_sem = shmget(key2,8,IPC_CREAT | 0666) )  == -1)    {
        perror("Error in creating the shared memory\n");
        return EXIT_FAILURE;        
    }
    //attach the shared memory to semaphore ptr
    if( (sem = (sem_t*)shmat(shmid_sem,NULL,0)) == (void*)-1)
    {
        perror("Error in attaching the shared memory\n");
        return EXIT_FAILURE;               
    }
    //Initializing the semaphore with value 1
    if( (sem_init(sem,2,1) ) == -1)    {
        perror("Error in opening semaphore\n");
        return EXIT_FAILURE;
    }
/****************** CREATE SHARED MEMORY FOR SEMAPHORE PTR END*****************************/

    pid_t cpid = fork();
/******************Child Process Start*****************************************************/
    /* Child Process Increment the global pointer value*/
    if(cpid == 0)
    {
        #ifdef __DEBUG__
        printf("In child process\n");
        #endif
        inc_func();
        if(shmdt(global_ptr) == -1)
        {
            perror("Error in detaching shared memory in Child process\n");
            return EXIT_FAILURE;
        }
        #ifdef __DEBUG__
        printf("Shared Memory detached in Child Process.....\n");
        #endif
        /*
        if(sem_close(sem) == -1)
        {
            perror("Error in closing named semaphore\n");
            return EXIT_FAILURE;
        }*/
        /* Detach the sem ptr*/
        if(shmdt(sem) == -1)
        {
            perror("Error in detaching shared memory semaphore pointer in Child process\n");
            return EXIT_FAILURE;
        }
        #ifdef __DEBUG__
        printf("Semaphore detached in Child Process.....\n");
        #endif
        printf("\n\n");
    }
/******************Child Process Ends*****************************************************/


/******************Parent Process Start*****************************************************/
    else
    {
        #ifdef __DEBUG__
        printf("In Parent Process.....\n");
        #endif
        
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
        #ifdef __DEBUG__
        printf("Global Ptr Shared Memory detached in Parent Process.....\n");
        #endif
        //detach the semaphore pointer
        if(shmdt(sem) == -1)
        {
            perror("Error in detaching semaphore ptr in Parent process\n");
            return EXIT_FAILURE;
        }
        #ifdef __DEBUG__
        printf("Semaphore ptr Shared Memory detached in Parent Process.....\n");
        #endif
        //mark to delete the global Ptr shared memory
        if(shmctl(shmid_global_ptr,IPC_RMID,NULL) == -1)
        {
            perror("Error in deleting Global Ptr shared memory in Parent process\n");
            sem_destroy(sem);
            return EXIT_FAILURE;
        }
        #ifdef __DEBUG__
        printf("Global_Ptr Shared Memory deleted in Parent Process.....\n");
        #endif
        //mark to delete the global Ptr shared memory
        if(shmctl(shmid_sem,IPC_RMID,NULL) == -1)
        {
            perror("Error in deleting Semaphore Ptr shared memory in Parent process\n");
            sem_destroy(sem);
            return EXIT_FAILURE;
        }
        #ifdef __DEBUG__
        printf("Sem_Ptr Shared Memory deleted in Parent Process.....\n");
        #endif
        if(sem_destroy(sem) == -1)
        {
            perror("Error in detaching semaphore ptr in Parent process\n");
            return EXIT_FAILURE;            
        }
        #ifdef __DEBUG__
        printf("Semaphore deleted in Parent Process.....\n");
        #endif

        
    }

/******************Parent Process Ends*****************************************************/
    
}