//program to understand what happens when fork is called repeatedly
#include<stdio.h>
#include<unistd.h>//for getpid() and fork()
#include<sys/types.h>//for pid_t
#include<stdlib.h>
int main()
{
    for(int i = 1;i<=4;i++)
    {
        fork();
        printf("Program pid = %d\n",(int)getpid());
    }
    sleep(1);
    printf("Out of loop program pid = %d\n",(int)getpid());
}