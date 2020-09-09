//Program to understand process tree
/* Here both parent and child calls the fork for creating the subsequent process*/
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
        if(fork() == -1)
        {
            fprintf(stderr,"Error while creating %d child\n",i+1);
            return EXIT_FAILURE;
        }
    }
    fprintf(stderr,"pid = %d, ppid = %d\n",getpid(),getppid());

    printf("End of program\n");//to check if process creates successfully or not4
    while(1);//to prevent the creation of orphan process 
}