//Program to understand synchronization between threads using mutex
#include<stdio.h>
#include<stdlib.h> //for EXIT_FAILURE
#include<pthread.h>//for pthread_create()
#include<unistd.h>
//#define NUM_COUNT 20000000//number count
#define NUM_COUNT 100//decremented to 100

long long sum = 0;//global variable sum

//variable for mutex
//statically intialize the mutex with no error checking
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//count the no passed upto 5 million times.
/*void count_number(int no) -> converted to thread function*/
void* count_number(void *arg)
{
    //extracting value passed
    int no = *(int*)arg;
    for(int i = 0;i<NUM_COUNT;i++){
/********************Critical section start*************************************************** 
Here since sum is accessed by both threads so it is critical section*/
    //locking by mutex
    /* Print statement for debut*/
    printf("Before the mutex locking \t");
    pthread_mutex_lock(&mutex);
    sum += no;//only one thread can access at one time
    

/********************Critical section Ends*************************************************/
    //unlock the mutex
    pthread_mutex_unlock(&mutex);
    printf("After the mutex unlocking\n");
    }//for loop ends
    printf("\nOUt of for loop\n\n");
    pthread_exit(0);//return value i.e NULL to pthread_join()
}

int main()
{
    
    int ret_pthread;
    int i = 1;
    //count_number(1);-> commented since we're using thread  so no need to function call
    
/********************** first thread creation  ********************************************/
    while(i<100)//loop to check what happens when two thread runs concurrently for 100 times
    {
    //creating the thread id
    pthread_t id1;
    
    //number which is to be count
    int num1 = 1;

    //print statement to debug
    printf("Before the first thread creation\n");

    /*creating the thread.
    Here if thread created successfully returns 0*/
    if((ret_pthread = pthread_create(&id1,NULL,count_number,&num1)) != 0)
    {
        
        perror("Error in creating thread\n");
        return EXIT_FAILURE;
    }
    printf("Waiting for first thread to complete.....\n");
/* Comment since we're first created all threads and then waits
    if(pthread_join(id1,NULL) != 0)//wait until  background thread i.e count_number completes
    {
        perror("Error in waiting thread\n");
        return EXIT_FAILURE;
    }
    printf("Out of first thread\n");//check whether thread successfully exits*/

/********************** first thread creation completed ********************************************/

/********************** Second thread creation and waiting for completion********************************************/
//creating the thread id
    pthread_t id2;
    
    //number which is to be count
    int num2 = -1;
    
    /*when using the same variable causes the race condition to arise since passed
    by address*/
    //num1 = -1;

    //print statement to debug
    printf("Before the second thread creation\n");

    /*creating the thread.
    Here if thread created successfully returns 0*/
    if((ret_pthread = pthread_create(&id2,NULL,count_number,&num2)) != 0)
    //if((ret_pthread = pthread_create(&id2,NULL,count_number,&num1)) != 0)//reusing the num1
    {
        perror("Error in creating thread\n");
        return EXIT_FAILURE;
    }
    printf("Waiting for second thread to complete.....\n");
/* Comment since we're first created all threads and then waits
    if(pthread_join(id1,NULL) != 0)//wait until  background thread i.e count_number completes
    {
        perror("Error in waiting thread\n");
        return EXIT_FAILURE;
    }
    printf("Out of Second thread\n");//check whether thread successfully exits*/

/********************** Second thread creation completed ********************************************/

/**************************Waiting for all threads to complete************************/
    if(pthread_join(id1,NULL) != 0)//wait until  background thread i.e count_number completes
    {
        perror("Error in waiting thread\n");
        return EXIT_FAILURE;
    }

    printf("\n\nOut of first thread\n\n");//check whether thread successfully exits*/
    
    if(pthread_join(id2,NULL) != 0)//wait until  background thread i.e count_number completes
    {
        perror("Error in waiting thread\n");
        return EXIT_FAILURE;
    }
    printf("Out of Second thread\n");//check whether thread successfully exits*/

/**************************Waiting for all threads to complete code finishes************************/

    /*after below statement sum = 0 since it first increment to 5 million
    then decrement to 5 million*/
    //count_number(-1); -> commented since we're using thread  so no need to function call
    
    printf("Out of All threads\n");//check whether thread successfully exits

    printf("Sum = %lld\n",sum);//printing sum after counting it
    printf("While loop ends with i = %d\n\n\n\n\n\n",i);
    i++;
    sleep(1);
    
    }
    
    
    
    
}