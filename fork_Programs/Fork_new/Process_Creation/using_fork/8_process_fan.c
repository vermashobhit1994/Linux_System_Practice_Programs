//Program to understand the process fan concept.
//here only parent creates all child process and child exits out . 
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>//for exit()
int main(int argc,char **argv)
{
    pid_t id ;
    if(argc != 2)
    {
        printf("please enter any argument\n");
        return EXIT_FAILURE;
    }
    int n  = atoi(argv[1]);//convert the argument to int
    //for loop to execute the fork() n times 
    for(int i = 0;i<n;i++)
    {
        if(fork() == 0)//to exit the child process 
        {
            printf("%d child exited\n",i+1);
            break;
        }
    }
    fprintf(stderr,"pid = %d, ppid = %d\n",getpid(),getppid());

    printf("End of program\n");//to check if process creates successfully or not4
    while(1);//to prevent the creation of orphan process 
}