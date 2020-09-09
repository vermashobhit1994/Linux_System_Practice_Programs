//Program to understand the getpid and getppid functions use
#include<stdio.h>
#include<unistd.h>//for getpid and getppid and fork
int main()
{
    printf("Program pid = %d\n",getpid());
    printf("Program parent pid = %d\n",getppid());

}