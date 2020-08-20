//Program to find sum from 0 to n using single thread
/* Here we're accessing global variable sum by thread as well as by main()*/
#include<stdio.h>
#include<pthread.h>//for pthread_create()
#include<stdlib.h>//for atoll()

long long sum=0;

//thread function to generte sum from 0 to n
void *sum_from_zero_to_n(void *arg)
{
    /* Print statement to check when thread is executing*/
    printf("Inside the sum thread\n");
    //extract the address of the 1st argument of command line 
    long long *limit_ptr = (long long *)arg;
    //extract the data passed in the command line
    long long limit = *limit_ptr;
    
    //long long sum = 0; this is moved to global one
    //loop to find the sum
    for (long long i = 0;i<=limit;i++)
        sum += i;
    //to return the NULL value by pthread_join()
    pthread_exit(0);
    
}
int main(int argc, char **argv)
{
    //error handling when no number is provided
    if(argc < 2)
    {
        printf("Provide the no\n");
        return -1;
    }
    //convert the character to integer passed in command line argument
    long long int limit = atoll(argv[1]);
    //creating the thread id
    pthread_t tid;
    //creating attributes
    pthread_attr_t attr;
    //intializing the attributes
    pthread_attr_init(&attr);

    //print statement to check when thread is creating
    printf("Before creating the thread\n");

    //creating the thread. On success it return 0
    if(pthread_create(&tid,&attr,sum_from_zero_to_n,&limit) != 0)
    {
        perror("Error while creating thread\n");
        return EXIT_FAILURE;
    }
    /* print statement to check after creating the thread*/
    printf("Waiting for thread to complete....\n");

    /* some other work when main thread is waiting for other thread to complete
    /* here we're doing printing of table from 1 to 100*/
    long long num = 4 ;
    printf("No to print the table = %lld\n",num);    
    for(int i = 0;i<10;i++)
    {
        printf("%4lld*%3d = %5lld\n",num,i+1,num * (i+1));
    }

    //to wait until the thread sum_from_zero_to_n done completion 
    if( pthread_join(tid,NULL) != 0)
    {
        perror("Error while waiting for thread\n");
        return EXIT_FAILURE;
    }

    //debug statement to check when thread completes
    printf("All Threads ended \n"); 

    //printing of sum by main() thread
    printf("sum = %lld\n",sum);
}