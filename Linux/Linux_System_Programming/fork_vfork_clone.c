//Program to understand the difference between fork, vfork and clone system call

//1. fork system call

#include<stdio.h>
#include<unistd.h>//for fork()
#include<stdlib.h>


#define MAX_PROCESS_NO    4

int globalvar = 10;


 
int main()
{
    int localvar = 100;
    pid_t pid = fork();
    //pid_t pid = vfork();
    
    for(int i = 0;i< MAX_PROCESS_NO;i++)
    {
	    if(pid == -1)
	    {
		perror("Error in fork system call\n");
		exit(0);
	    }
	    
	    if(pid == 0)
	    {
		printf("Child process started \n");
		sleep(1);
		globalvar++;
		localvar++;
		printf("Child proces ended\n\n\n");
		//fflush(stdout);
	    }
	    
	    else
	    {
		printf("Parent process started\n");
		sleep(1);
		printf("Parent process ended with gloalvar = %d, localvar = %d\n\n\n",globalvar,localvar);
		//fflush(stdout);
		
		
		
	    }
    }
}
