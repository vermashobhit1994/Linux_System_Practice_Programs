//Program to understand counting semaphore.
//Here the 5 threads waits while the 6-10th thread is blocked
#include<stdio.h>
#include<pthread.h>//for pthread_create(),pthread_join()
#include<semaphore.h>//for sem_open(),sem_close(),sem_unlink()
#include<stdlib.h>//for EXIT_FAILURE
#include<unistd.h>//for sleep()
#include<fcntl.h>//for O_CREAT

sem_t *sem;//global semaphore variable
#define __DEBUG__//activate the debug statements

void* fun(void* arg)
{
    #ifdef __DEBUG__
    printf("Inside the thread\n");
    #endif
    if( (sem_wait(sem)) != 0)
    {
        perror("Error in waiting for semaphore inside thread\n");
    }
    int val;
    if(sem_getvalue(sem,&val)  == -1)
    {
        perror("Error in getting the current value of semaphore\n");
    }
    printf("Semaphore value = %d\n",val);
    printf("\n\n");
    pthread_exit(0);//no statement after this gets executed
    printf("After pthread exit\n");//statement wouldn't execute
}
int main()
{
    const char* name = "countsem";
    //create a named semaphore of initial value = 5 .
    //O_EXCL with O_CREAT to give error if named semaphore already exists    
    if( (sem = sem_open(name,O_CREAT|O_EXCL,0666,5)) == SEM_FAILED)
    {
        perror("Error in opening semaphore\n");
        return EXIT_FAILURE;
    }
    pthread_t tid[10];
    //create the 10 threads
    for(int i = 0;i<10;i++)
    {
        //create 10 threads using same function
        if(pthread_create(&tid[i],NULL,fun,NULL) != 0)
        {
            perror("Error in creating thread\n");
            return EXIT_FAILURE;
        }
        sleep(1);//to check the value of semaphore
    }

    //wait the 10 threads
    for(int i = 0;i<10;i++)
    {
        if(pthread_join(tid[i],NULL) != 0)
        {
            perror("Error in creating thread\n");
            return EXIT_FAILURE;
        }
    }
    getchar();
    if(sem_close(sem) == -1)
    {
        perror("Error in closing the semaphore\n");
        return EXIT_FAILURE;
    }
    if(sem_unlink(name) == -1)
    {
        perror("Error in deleting the semaphore\n");
        return EXIT_FAILURE;
    }
}