//program to understand the SIGINT signal
//here user sends SIGINT by pressing ctrl + c 
//here the program continues to run until ctrl + c is pressed
#include<stdio.h>
#include<unistd.h>//for sleep()

int main()
{
    while(1)
    {
        printf("In infinite loop . Press ctrl + c to exit\n");
        sleep(1);
    }
}