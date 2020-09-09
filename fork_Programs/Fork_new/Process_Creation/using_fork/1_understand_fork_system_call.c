//Program to understand fork system call
/* Here the parent execute first then shell then the child.
Here after the parent ends first then the child process is taken care by shell*/
#include<stdio.h>
#include<stdlib.h>//for EXIT_FAILURE
#include<unistd.h>//for fork()
int main()
{
    //after the below statement the parent and child process starts executing
    pid_t cpid = fork();
    if(cpid == 0)
    {
        printf("I am child ");
        sleep(5);//done so that the child is taken by bash when parent ends.
        printf("After sleep in child ");   
    }
    else
    {
        printf("I am parent");
        exit(45);//parent exits out
    }
    return 0;
}