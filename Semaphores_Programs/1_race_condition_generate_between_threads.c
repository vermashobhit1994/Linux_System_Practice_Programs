/*Program that will generate the race condition between threads.
Here we're generating a different value when printing the 
global variable in main() thread due to race condition.*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define MAX_VAL 100000000//hundred million

#define __DEBUG__//for using the debug statements

//global variable for two threads
long long global_val = 0;

/*Increment the global variable */
void *inc_thread(void *arg)
{
    #ifdef __DEBUG__
    printf("In Increment thread\n");
    #endif
    for(int i = 0;i<MAX_VAL;i++)    
        global_val++;
    pthread_exit(0);
}

/*Decrement the global variable */
void *dec_thread(void *arg)
{
    #ifdef __DEBUG__
    printf("In Decrement thread\n");
    #endif
    for(int i = 0;i<MAX_VAL;i++)    
        global_val--;
    pthread_exit(0);
}

int main()
{
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
    //wait until increment thread completes
    if( pthread_join(id1,NULL) != 0)
    {
        perror("Error in waiting increment thread\n");
        return EXIT_FAILURE;
    }
    #ifdef __DEBUG__
    printf("Waiting for decrement thread to finish....\n");
    #endif
    //wait until increment thread completes
    if( pthread_join(id2,NULL) != 0)
    {
        perror("Error in waiting decrement thread\n");
        return EXIT_FAILURE;
    }   

    //print the global variable
    printf("global_val = %lld\n",global_val);

}
