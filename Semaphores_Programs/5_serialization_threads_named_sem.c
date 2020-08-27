//Program to understand serialization between the threads
/* We want output to be Shobhit Verma is very good guy*/
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
/* 3 thread functions*/
void *fun1(void *arg)
{
    printf("good guy ");
}
void *fun2(void *arg)
{
    printf("is a very ");
}
void *fun3(void *arg)
{
    printf("Shobhit verma ");
    
}

int main()
{
    //create the three thread id's
    pthread_t t1,t2,t3;

/*************** CREATE ALL THREADS START ****************************************************/
    if(pthread_create(&t1,NULL,fun1,NULL) != 0)
    {
        perror("Error in creating first thread\n");
        return EXIT_FAILURE;
    } 
    if(pthread_create(&t2,NULL,fun2,NULL) != 0)
    {
        perror("Error in creating second thread\n");
        return EXIT_FAILURE;
    }
    if(pthread_create(&t3,NULL,fun3,NULL) != 0)
    {
        perror("Error in creating third thread\n");
        return EXIT_FAILURE;
    }
/************************ CREATING ALL THREADS END**************************************/

/************************ WAITING ALL THREADS START **************************************/    
    if(pthread_join(t1,NULL) != 0)
    {
        perror("Error in waiting  first thread\n");
        return EXIT_FAILURE;
    }
    if(pthread_join(t2,NULL) != 0)
    {
        perror("Error in waiting second thread\n");
        return EXIT_FAILURE;
    }
    if(pthread_join(t3,NULL) != 0)
    {
        perror("Error in waiting third thread\n");
        return EXIT_FAILURE;
    }
/************************ WAITING ALL THREADS ENDS**************************************/

    printf("\n");
}
