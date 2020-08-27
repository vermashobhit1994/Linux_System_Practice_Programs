//Program to solve the serialization between threads using unnamed semaphores
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<semaphore.h>

sem_t *semA,*semB;

void *fun1(void *arg)
{
    if( (sem_wait(semB)) != 0)
    {
        perror("Error in waiting for semaphore in Function1\n");
    }
    printf("good guy ");
    
}
void *fun2(void *arg)
{

    if( (sem_wait(semA)) != 0)
    {
        perror("Error in waiting for semaphore in function2\n");
    }
    printf("is a very ");
    if( (sem_post(semB)) != 0)
    {
        perror("Error in posting for semaphore in function2\n");
    }
}
void *fun3(void *arg)
{

    printf("Shobhit verma ");
    if( (sem_post(semA)) != 0)
    {
        perror("Error in posting for semaphore in Function3\n");
    }
}

int main()
{
    /* Creating a heap memory for storing the semaphore variables*/
    semA = (sem_t*)malloc(sizeof(semA));
    semB = (sem_t*)malloc(sizeof(semB));
    //Initializing the first semaphore
    if( sem_init(semA,0,0) == -1)
    {
        perror("Error in initializing the first semaphore\n");
        return EXIT_FAILURE;
    }
    //Initializing the second semaphore
    if ( sem_init(semB,0,0) == -1)
    {
        perror("Error in initializing the second semaphore\n");
        sem_destroy(semA);
        sem_destroy(semB);
        return EXIT_FAILURE;
    }
    //create the three thread id's
    pthread_t t1,t2,t3;

/*************** CREATE ALL THREADS****************************************************/
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
    //delete the first semaphore
    if ( sem_destroy(semA) == -1)
    {
        perror("Error in destroy the first semaphore\n");
        return EXIT_FAILURE;
    }
    //delete the second semaphore
    if ( sem_destroy(semB) == -1)
    {
        perror("Error in destroy the second semaphore\n");
        return EXIT_FAILURE;
    }

    printf("\n");
}
