#include<stdio.h>
#include<unistd.h>//for getpid() and fork()
#include<sys/types.h>//for pid_t
#include<stdlib.h>//for exit(0)
#include<sys/wait.h>//for wait()
int i = 0;
void doSomeWork(char *name)
{
    const int NUM_TIMES = 5;
    //const int NUM_TIMES = 2;//change from 5 to 2 for zombie process
    //loop for both child and parent process
    for(;i<NUM_TIMES;i++)
    {
        int val = rand();
        printf("rand() value = %d\n",val);
        sleep(val % 4);//sleep between 0 to 3 sec
        printf("Done Pass = %d of loop \n\n",i);
    }

    /************** for loop for specific to process with print of process name************/
    /*
    for(int i = 0;i<NUM_TIMES;i++)
    {
        printf("rand() value = %d for %s\n",rand(),name);
        sleep(rand() % 4);//sleep randomly between 0 to 3 sec 
        printf("Done Pass = %d of loop for %s process\n",i,name);
        printf("\n\n");
    }*/

}
int main()
{
    printf("The current program pid = %d\n\n",getpid());
    pid_t pid = fork();
    srand((int)pid);//to make the child and parent process randomly execute the doSomeWork()
    
    printf("Fork returned value  = %d\n",(int)pid);

    /**************** Error checking in fork Start *******************************************/
    if(pid < 0)
    {
        perror("Fork failed\n");
        return 0;
    }
    /**************** Error checking in fork Ends ********************************************/
    
/******************* Child Process Start*****************************************************/    

    if(pid == 0)
    {
        printf("\n\n");//separate the parent and child print statements
        printf("I am in child process with pid = %d\n",(int)getpid());//use of getpid()
        //sleep(5);//child wait for the five sec.
        doSomeWork("child");
        printf("child exiting\n\n");
        exit(42);//done so as no use of else in parent process
    }
/******************* Child Process Ends*****************************************************/    

/******************* Parent Process Start*****************************************************/    
    printf("I am in parent process with pid = %d and waiting for child to finish\n",getpid());
    //sleep(30);//done to start the zombie process
    doSomeWork("Parent");
    wait(NULL);//parent waits until child finishes
    
    /******************** Collect the return status of child by parent start*******************/
    printf("\n\n");
    int status;
    pid_t childpid = wait(&status);
    printf("Parent knows child with pid = %d finishes with status = %d\n",(int)childpid,status);
    int child_ret_val = WEXITSTATUS(status);
    printf("Return value by child = %d\n",child_ret_val);
    
    /******************** Collect the return status of child by parent ends********************/
    
    printf("Parent ends\n");
/******************* Parent Process Ends*****************************************************/    

    //getchar();
    
}