//Program to solve the race condition using binary semaphore between the threads.
//Here we get the result as zero no matters how many times program runs
#include<stdio.h>
#include<stdlib.h>//for EXIT_FAILURE
#include<pthread.h>//for 
#include<semaphore.h>
#include<fcntl.h>
#define MAX_VAL 1000000//hundred million

//activate the debug statements
#define __DEBUG__


//global variable sharing between two threads
long long global_val = 0;

//global variable for semaphore
sem_t *sem;


void *inc_thread(void *arg)
{
    #ifdef __DEBUG__
    printf("In Increment thread\n");
    #endif
    for(int i = 0;i<MAX_VAL;i++) { 
        //decrement sem variable
        if( (sem_wait(sem)) != 0)
        {
            perror("Error in waiting for semaphore Increment thread\n");
        }
/************Critical section Starts ********************************************************/  
        global_val++;
        
/************Critical section Ends ********************************************************/  
        if( (sem_post(sem)) != 0)
        {
            perror("Error in posting for semaphore Increment thread\n");
            
        }
    }//for loop ends
    pthread_exit(0);
}
void *dec_thread(void *arg)
{
    #ifdef __DEBUG__
    printf("In Decrement thread\n");
    #endif
    for(int i = 0;i<MAX_VAL;i++){
    //decrement sem variable
        if( sem_wait(sem) != 0)
        {
            perror("Error in waiting for semaphore decrement thread\n");
        }
/************Critical section Starts ********************************************************/  
        global_val--;
    
/************Critical section Ends ********************************************************/  
        if( sem_post(sem) != 0)
        {
            perror("Error in posting for semaphore in decrement thread\n");
        }
    }//for loop ends    
    pthread_exit(0);
}

int main()
{
    //name of semaphore
    const char *name = "sem_race_solve";//Max characters for name is 251
    /*Initialize and open a named semaphore if it doesn't exists(specified by 
    O_CREAT flag) with readwrite permissions and initial value of 1*/ 
    //O_EXCL with O_CREAT to give error if named semaphore already exists    
    if( (sem = sem_open(name,O_CREAT|O_EXCL,0666,1) ) == SEM_FAILED)    {
        perror("Error in opening semaphore\n");
        return EXIT_FAILURE;
    }
/****************** CREATE THE TWO THREADS******************************************/
    //create the thread id's 
    pthread_t id1,id2;
    //create the increment thread
    if(pthread_create(&id1,NULL,inc_thread,NULL) != 0)
    {
        perror("Error in creating increment thread\n");
        return EXIT_FAILURE;
    }
    //create the decrement thread
    if(pthread_create(&id2,NULL,dec_thread,NULL) != 0)
    {
        perror("Error in creating decrement thread\n");
        return EXIT_FAILURE;
    }
    #ifdef __DEBUG__
    printf("Waiting for increment thread to finish....\n");
    #endif
/****************** CREATE THE TWO THREADS ENDS ******************************************/

/****************** WAIT FOR ALL THREADS **************************************************/
    //wait until increment thread completes
    if( pthread_join(id1,NULL) != 0)
    {
        perror("Error in waiting increment thread\n");
        return EXIT_FAILURE;
    }
    #ifdef __DEBUG__
    printf("Waiting for decrement thread to finish....\n");
    #endif
    //wait until decrement thread completes
    if( pthread_join(id2,NULL) != 0)
    {
        perror("Error in waiting decrement thread\n");
        return EXIT_FAILURE;
    }   
/****************** WAIT FOR ALL THREADS ENDS**************************************************/

    getchar();
    //close the semaphore
    if(sem_close(sem) == -1)
    {
        perror("Error in closing named semaphore\n");
        return EXIT_FAILURE;
    }
    //remove the file of semaphore
    if(sem_unlink(name) == -1)
    {
        perror("Error in deleting named semaphore\n");
        return EXIT_FAILURE;
    }
    //print the global variable
    printf("global_val = %lld\n",global_val);

}