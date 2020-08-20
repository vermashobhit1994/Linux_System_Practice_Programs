/* Program to understand how to run the same function multiple times using the thread
This is done by doing sum from 0 to n of numbers passed in command line arguments
and then find sum of each number passed from 0 to n.

For multiple threads for collecting the numbers and returning sum we're
using  structure since we've only single pointer i.e void*
*/
#include<stdio.h>
#include<pthread.h>//for pthread_create()
#include<stdlib.h>//for atoll()
/* structure for holding the value returned by thread and limit upto which sum is 
to be done.
It is used since we're only using a single pointer
This structure is different for each thread.*/
struct sum_arg_struct
{
    long long limit;
    long long answer;
};

//thread function to generte sum from 0 to n
void *sum_from_zero_to_n(void *arg)
{
    /* Print statement to check when thread is executing*/
    printf("Inside the sum thread\n");
    
    //extract the address of the structure passed for each number.
    /* pointer to structure. Here pointer store the address of argument passed*/ 
    struct sum_arg_struct *arg_struct = (struct sum_arg_struct *)arg;
    
    /*extract the data passed in the command line.
    The below limit value is taken as member to structure*/
    //long long limit = *limit_ptr;
    
    /*Here we've taken it locally because we're actually
    returning this value back to main thread by putting the sum into answer field.*/  
    long long sum = 0;    //loop to find the sum
    for (long long i = 0;i <= arg_struct -> limit;i++)
        sum += i;

    //putting the sum into structure
    arg_struct -> answer = sum;
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

    /*variable to store the number of arguments passed in command line arguments
    -1 is done due to first argument is file name itself*/
    int num_args = argc -1;

    /*convert the character to integer passed in command line argument
    Move to thread creation loop so as to have the all the numbers added from 1 to n
    instead of just one*/
    //long long int limit = atoll(argv[1]);

    /*creating the thread id for multiple threads
    Here the no of threads equal to num_args or number passed in command line arguments*/
    pthread_t tids[num_args];
    //creating attributes
    pthread_attr_t attr;
    //intializing the attributes
    pthread_attr_init(&attr);

    //print statement to check when thread is creating
    printf("Before creating the thread\n");

    /* Creating the array of structures. 
    Putting the number passed in command line argument in structure limit field.
    Here we've array of num_args for numbers passed.*/
    struct sum_arg_struct args[num_args];    

    /*creating the multiple threads concurrently i.e parallely one by one.
    Here the same one thread is running 3 times*/
    int i;
    for(i = 0;i<num_args;i++)
    {
        //+1 is due to exclude first argument which is name of file itself
        /*struct arg_struct args ; moved outside of loop so that at end
        of loop sum can be accessed .
        Access numbers passed in command line arguments one by one.*/
        args[i].limit = atoll(argv[i+1]);

        //here args is passed which is variable to structure
        /*Passed args[i] to take all numbers passed in command line arguments*/
        if(pthread_create(&tids[i],&attr,sum_from_zero_to_n,&args[i]) != 0)
        {
            perror("Error while creating thread\n");
            return EXIT_FAILURE;
        }
    }
    /* print statement to check after creating the thread*/
    printf("After creation the %d thread \n",i);

/*********some other work when main thread is waiting for other thread to complete********************************/
   
    /* here we're doing printing of table from 1 to 100*/
    long long num = 78;
    printf("no of to print the table = %lld\n",num);
    //scanf("%lld",&num);
    for(int i = 0;i<10;i++)
    {
        printf("%4lld*%3d = %5lld\n",num,i+1,num * (i+1));
    }

/********************Other work completes********************************************************/
    
    //to wait multiple threads sum_from_zero_to_n done completion
    for(int i = 0;i<num_args;i++)
    {
        //waiting the thread to complete.
        pthread_join(tids[i],NULL);

        //printing of sum by return value in structure by thread
        printf("sum for thread id [%ld] = %lld\n",tids[i],args[i].answer);
    } 

    //debug statement to check when thread completes
    printf("Out of program\n");


}