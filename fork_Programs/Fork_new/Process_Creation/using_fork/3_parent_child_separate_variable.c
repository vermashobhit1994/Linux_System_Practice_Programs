//Program to understand that after a fork the parent and child have separate copy of variable
/* here the count variable is initialized to default value in both the parent and child*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>//for exit()
int main()
{
    int count = 0;//variable to be checked between the child and parent
    pid_t id = fork();
    if(id == -1)
    {
        perror("Error in creating the child process\n");
        return 0;
    }
    if(id == 0)
    {
        count = 100;//child initialize this variable again
        sleep(5);//sleep in child so that taken by bash program after parent exits out
        //loop to increment count three times
        for(int  i = 0;i<3;i++)
            printf("IN child count = %d\n",count++);
    }
    else
    {
        //loop to increment count three times
        for(int  i = 0;i<3;i++)
            printf("IN parent count = %d\n",count++);
        printf("\n\n");
        exit(2);//exit the parent
    }
}