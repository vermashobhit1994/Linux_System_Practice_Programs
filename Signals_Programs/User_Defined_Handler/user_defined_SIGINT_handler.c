//program to understand the user defined signal handler for the SIGINT signal
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
void myhandler(int signum)
{
    printf("I am in signal handler for the signal %d\n",signum);
    exit(0);
}
int main()
{
    signal(SIGINT,myhandler);
    while(1)
    {
        printf("I am in infinite loop\n");
        sleep(1);
    }
}