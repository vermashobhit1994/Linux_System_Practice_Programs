//program to understand SIGHUP signal using kill system call
#include<stdio.h>
#include<unistd.h>//for sleep()
#include<signal.h>//for kill()
int main()
{
    printf("After 5 seconds I would receive a SIGHUP signal\n");
    sleep(5);
    kill(getpid(),SIGHUP);
    printf("After the kill \n");
}