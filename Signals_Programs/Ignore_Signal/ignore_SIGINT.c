//program to understand how to ignore the SIGINT
#include<stdio.h>
#include<unistd.h>//for sleep()
#include<signal.h>//for signal()
int main()
{
    signal(SIGINT, SIG_IGN);
    while(1)
    {
        printf("I am in infinite loop\n");
        printf("You can't kill me by pressing ctrl + c\n");
        sleep(1);
    }
}