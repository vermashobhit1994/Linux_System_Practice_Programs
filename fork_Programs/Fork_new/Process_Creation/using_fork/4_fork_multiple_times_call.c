//Program to understand what happens when fork is called multiple times
/* here the process creates = 2^n where n is no of times the fork is called*/
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
        if(fork() == -1)
        {
            fprintf(stderr,"Error while creating %d child\n",i+1);
            return EXIT_FAILURE;
        }
    printf("End of program\n");//to check if process creates successfully or not4
    exit(0);
}