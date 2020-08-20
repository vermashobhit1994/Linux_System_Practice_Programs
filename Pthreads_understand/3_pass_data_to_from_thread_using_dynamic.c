//Program to pass data to thread and from thread using the dynamic memory i.e malloc()
/* Here two pointers for dynamic memory allocation one in thread 
and one in main() thread.
Understand how to use pthread_exit() and pthread_join() to return a value 
by thread.
Here we're taking only single thread case.*/
#include<stdio.h>
#include<pthread.h>//for pthread_create()
#include<stdlib.h>//for atoll()

//thread function to generte sum from 0 to n
void *sum_from_zero_to_n(void *arg)
{
    /* Print statement to check when thread is executing*/
    printf("Inside the sum thread\n");
    //extract the address of the 1st argument of command line 
    long long *limit_ptr = (long long *)arg;
    //extract the data passed in the command line
    long long limit = *limit_ptr;
    
    /*free the argument to dynamic memory passed 
    i.e freeing the pointer passed by  main thread*/
    free(arg);

    long long sum = 0;//local sum variable
    //loop to find the sum
    for (long long i = 0;i<=limit;i++)
        sum += i;

    /*pointer to hold the sum calculated
    Here sizeof(*answer) is written because it would calculate the 
    no of bytes that the ptr answer holds so,if the value is NULL 
    also it always be done at compile time and so no problem arises.
    Later if answer type is changed to double then no need to change sizeof
    bytes allocated since changed automatically.*/
    long long *answer = (long long *)malloc(sizeof(*answer));
    //storing the sum in answer
    *answer = sum;
    /*to return the NULL value by pthread_join()
    Here passing a pointer to memory allocated*/
    pthread_exit(answer);
    
}
int main(int argc, char **argv)
{
    //error handling when no number is provided
    if(argc < 2)
    {
        printf("Provide the no\n");
        return -1;
    }
    /*convert the character to integer passed in command line argument
    Creating a pointer to dynamic memory for storing how many no's passed*/
    long long int *limit = malloc(sizeof(*limit));
    *limit = atoll(argv[1]);

    //creating the thread id
    pthread_t tid;
    //creating attributes
    pthread_attr_t attr;
    //intializing the attributes
    pthread_attr_init(&attr);

    //print statement to check when thread is creating
    printf("Before creating the thread\n");

    /*creating the thread. On success it return 0.
    Passing a pointer to thread as argument*/
    if(pthread_create(&tid,&attr,sum_from_zero_to_n,limit) != 0)
    {
        perror("Error while creating thread\n");
        return EXIT_FAILURE;
    }
    /* print statement to check after creating the thread*/
    printf("Waiting for thread to complete.....\n");

/*********some other work when main thread is waiting for other thread to complete***************************/
    
    /* here we're doing printing of table from 1 to 10*/
    long long num = 45;
    printf("no to print the table = %lld\n",num);
    for(int i = 0;i<10;i++)
    {
        printf("%4lld*%3d = %5lld\n",num,i+1,num * (i+1));
    }

/******************Some other work finishes*********************************************************************/
    
    /*to wait until the thread sum_from_zero_to_n done completion .
    Collecting the value returned by thread in result.*/
    long long *result;
    pthread_join(tid,(void**)&result);//typecast to void** for avoid of warning

    //printing of sum returned by sum thread
    printf("sum = %lld\n",*result);

    //free memory  allocated for storing the result
    free(result);
    
    //debug statement to check when thread completes
    printf("Out of program\n");


} 