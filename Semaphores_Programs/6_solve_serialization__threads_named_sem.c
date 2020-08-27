//Program to execute the threads in serial manner using two semaphores
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<semaphore.h>//for sem_open(),sem_close(),sem_unlink()
#include<fcntl.h>//for O_CREAT

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
    const char *nameA = "sem1_serial",*nameB = "sem2_serial";
    //O_EXCL with O_CREAT to give error if named semaphore already exists    
    if( (semA = sem_open(nameA,O_CREAT|O_EXCL,666,0) ) == SEM_FAILED)
    {
        perror("Error in creating the first semaphore\n");
        return EXIT_FAILURE;
    }
    if ( (semB = sem_open(nameB,O_CREAT|O_EXCL,666,0)) == SEM_FAILED)
    {
        perror("Error in creating the second semaphore\n");
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
    if(sem_close(semA) == -1)
    {
        perror("Error in closing the semaphoreA\n");
        return EXIT_FAILURE;
    }
    if(sem_close(semB) == -1)
    {
        perror("Error in closing the semaphoreB\n");
        return EXIT_FAILURE;
    }
    if(sem_unlink(nameA) == -1)
    {
        perror("Error in deleting the semaphoreB\n");
        return EXIT_FAILURE;
    }
    if(sem_unlink(nameB) == -1)
    {
        perror("Error in closing the semaphoreB\n");
        return EXIT_FAILURE;
    }
    printf("\n");
}
