//Program to solve the race condition between the processes using the named semaphores
#include<stdio.h>
#define MAX_VAL 100000000
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
    int shmid1;
    /*Create a named semaphore*/
    char *name = "sem_race_process";
    //O_EXCL with O_CREAT to give error if named semaphore already exists    
    if( (sem = sem_open(name,O_CREAT|O_EXCL,0666,1) ) == SEM_FAILED)    {
        perror("Error in opening semaphore\n");
        return EXIT_FAILURE;
    }
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

        if(sem_close(sem) == -1)
        {
            perror("Error in closing named semaphore\n");
            return EXIT_FAILURE;
        }
        #ifdef __DEBUG__
        printf("Semaphore Closed in Child Process.....\n");
        #endif

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
        printf("Shared Memory detached in Parent Process.....\n");
        #endif
        //mark to delete the shared memory
        if(shmctl(shmid1,IPC_RMID,NULL) == -1)
        {
            perror("Error in detaching shared memory in Parent process\n");
            sem_unlink(name);
            return EXIT_FAILURE;
        }
        #ifdef __DEBUG__
        printf("Shared Memory deleted in Parent Process.....\n");
        #endif
        //close the semaphore
        if(sem_close(sem) == -1)
        {
            perror("Error in closing named semaphore\n");
            return EXIT_FAILURE;
        } 
        #ifdef __DEBUG__
        printf("Semaphore closed in Parent Process.....\n");
        #endif
        //remove the file of semaphore
        if(sem_unlink(name) == -1)
        {
            perror("Error in deleting named semaphore\n");
            return EXIT_FAILURE;
        }
        #ifdef __DEBUG__
        printf("Semaphore deleted in Parent Process.....\n");
        #endif

        
    }

/******************Parent Process Ends*****************************************************/
    
}