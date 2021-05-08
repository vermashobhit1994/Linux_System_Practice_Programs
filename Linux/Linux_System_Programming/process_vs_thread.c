//Program to understand the difference between thread and process


#include<stdio.h>

#include<unistd.h>
#include<pthread.h>

#include<sys/types.h>//for gettid()

#include<sys/wait.h>

#include<stdlib.h>

int dec_thread_id = 0;

void *decrement_thread(void *arg)
{
    sleep(3);
    printf("Inside the decrement thread with pid = %ld  and arg = %d\n",pthread_self(), *((int*)arg) );
    
/*************** Link1 : Return the status from thread to calling thread ********/
    //creating a pointer to store the value return by thread
    int *pVal = (int*)malloc(sizeof(int) * 10);
    
    dec_thread_id = pthread_self();
   
    *pVal = 104;
    
    
    while(1)//block the thread 
    {
        printf("Decrement thread is looping\n");
        pthread_testcancel();
        sleep(1);
    }
    
    printf("After the infinite loop\n");
    
    //returning the value 
    pthread_exit((void*)pVal);
    
    
    
    
/********************************************************************************/

}


void *increment_thread(void* arg)
{
    
    printf("inside the increment thread function with pid = %ld\n",pthread_self());
    
    pid_t tid ;
    printf(" in increment thread with id = %d\n",tid);
    
    int dec_thread_arg = 5;
    
    pthread_t threadid2;
    if (pthread_create (&threadid2, NULL, decrement_thread, &dec_thread_arg) != 0)
        
    {
            perror("Error in dec pthread creation\n");
            return 0;
    }
     
     printf("After 2nd thread creation\n");
     //while(1);//stop the thread   

/******************* Link1 : Return the status from thread to calling thread ********/     
     
     sleep(5);//waiting so that decrement thread can be executed for some time
     
     
      //if(kill(dec_thread_id, SIGKILL ) == -1) //-> can't be killed by kill()
    if (pthread_cancel(threadid2) != 0)
     {
         perror("Error in deleting decrement thread\n");
         
     }
     else
     	printf("Decrement thread killed success\n");
     
     int *pRetVal = malloc(sizeof(int) );
     
     
     if(pRetVal == NULL)
     {
         perror("Error while allocating memory in increment thread \n");
     }
     
     //parent proces wait until the thread ends
        if (pthread_join( threadid2, (void**)&pRetVal) != 0)
        //if(pthread_join(threadid2, NULL) != 0)
        {
            perror("Error while waiting for the dec thread\n");
        }
     //printf("Decrement thread ends with return value = %d\n",*((int*) pRetVal));
	printf("Decrement thread ends\n ");

	//free(pRetVal);
/********************************************************************************/

}

/*
void kill_child(int signum)
{
    printf("in signal handler with signal number = %d\n",signum);
    if(signum == SIGINT)
    {
        if (kill (0, SIGKILL) == -1)
        {
            perror("Error in killing the child \n");
        
        }
        else
            printf("second child deleting success\n");
    } 
}
*/

int main()
{
    pid_t id;
    
    if(id == -1)
    {
        perror("Error while creating child process\n");
        return 0;
    }
    
    //create the child process
    id = fork();
    
    printf("Fork return value = %d\n",id);
    
    if( id == 0)
    {
        
        printf("in child process with pid = %d and parent = %d\n",getpid(), getppid());
        sleep(1);
       // while(1);
       printf("child finished\n");
       _exit(10);
        
    }
    
    else
    {
        sleep(1);
        printf("IN parent process with pid = %d  and parent = %d\n",getpid(), getppid());
        
        pthread_t threadid1;
    
        int retval_thread_1 = pthread_create (&threadid1, NULL, increment_thread, NULL) ;
        if(retval_thread_1 != 0)
        {
            perror("Error in inc pthread creation\n");
            return 0;
        }
        
        
        printf("Thread1 is created sucess\n");
        
        printf("Parent is waiting for child to finish\n");
        
        int child_status;
        
        
/************************ Link1 return the status from child *******************/
        //wait() return -1 on error
        //pid_t childid = wait(&child_status);
        
        //waitpid return -1 on error
        pid_t childid = waitpid(0,&child_status, WUNTRACED); 
        
        
        if( child_status != 0 && childid != -1) 
        	printf("Return value from Child with pid = %d and status = %d and return value by child = %d\n",childid, child_status, WEXITSTATUS(child_status) );
        
        else
            printf("child status  = %d\n",child_status);
/*****************************************************************************/
         
           
        //parent proces wait until the thread ends
        if (pthread_join( threadid1, NULL) != 0)
        {
            fprintf(stderr,"Error while waiting for thread with %ld \n",pthread_self());
        }
        
        
        int second_child_pid = 0;
        
        //creating one more child process
        id = fork();
        
        if(id != 0)
            second_child_pid = id;
            
        printf("second_child_pid = %d\n",second_child_pid);
        
           
        if(id == 0)
        {
             printf("inside child proces with pid = %d with parent = %d\n",getpid(), getppid());
             
             second_child_pid = getpid();
             
             while(1)
             {
                 printf("child process is looping with id %d\n",second_child_pid);
                 sleep(2);
             }
             exit(523);//return value by child process
        }
        
        else
        {
            printf("inside parent process with pid = %d, ppid = %d with child pid = %d\n",getpid(),getppid(),second_child_pid);
            
            sleep(5);
            
            //kill on child on press of ctrl+c
           // signal(SIGINT,kill_child);
            
             if (kill (second_child_pid, SIGKILL) == -1)
             {
                fprintf(stderr,"Error in killing the child with pid = %d\n",second_child_pid);
        
             }
            else
                printf("second child deleting success with pid = %d\n",second_child_pid);
            
            
            
              
        }
        
        
        
        
        
       
        
    }
    printf("all process ended\n");
    
    
   
}



