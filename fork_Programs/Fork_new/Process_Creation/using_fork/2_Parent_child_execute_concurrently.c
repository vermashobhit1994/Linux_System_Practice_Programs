//Program to understand that after a fork both the parent and child process executes
//concurrently.
/* Here the statements inside both the parent and child executes simultaneoulsy*/
#include<stdio.h>
#include<unistd.h>//for fork()

int main()
{
    pid_t id = fork();

    if(id == 0)
    {
        while(1)
        {
            printf("I am in parent with value = X\n");
        }
    }
    else
    {
        while(1)
        {
            printf("I am in child with value = O\n");
        }
    }
}