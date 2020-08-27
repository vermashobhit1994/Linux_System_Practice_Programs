//Program to understand SIGSEGV signal using kill system call
#include<stdio.h>
#include<unistd.h>
#include <signal.h>//for kill()
#include<stdlib.h>
int main()
{
    pid_t cpid = fork();
    if (cpid == 0)//child process
    {
        while(1)
        {
            printf("I am in infinite loop child process\n");
            sleep(1);
        }
        
    }
    else//for parent
    {
        printf("I am in parent\n");
        sleep(5);
        kill(cpid,SIGSEGV);
        printf("I killed the child\n");
        exit(0);
    }
}