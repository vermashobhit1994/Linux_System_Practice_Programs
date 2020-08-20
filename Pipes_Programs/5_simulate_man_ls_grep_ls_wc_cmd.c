//Program to simulate man ls | grep ls | wc command 
/* For verification run man ls | grep ls | wc command in terminal */
#include<stdio.h>
#include<stdlib.h>//for EXIT_FAILURE
#include<unistd.h>//for  fork(),dup2(),execlp()
#include<sys/wait.h>
int main()
{
    int fd1[2],fd2[2];
    //create the first pipe
    if(pipe(fd1) == -1)
    {
        perror("Error in creating first pipe\n");
        return EXIT_FAILURE;
    }
    //create the second pipe
    if(pipe(fd2) == -1)
    {
        perror("Error in creating second pipe\n");
        close(fd1[0]);close(fd1[1]);
        return EXIT_FAILURE;
    }
    //first child process to execute man command
    if(fork() == 0)
    {
        if(dup2(fd1[1],1) == -1)//redirect from stdout to fd1 writer end
        {
            perror("Error in duplicating in first child \n");
            close(fd1[0]);close(fd1[1]);//close remaining file descriptor before exit
            close(fd2[0]);close(fd2[1]);
            return EXIT_FAILURE;
        }
        close(fd1[0]);//close unused file descriptor
        close(fd2[0]);close(fd2[1]);
        //here the second argument can be any name
        execlp("man","shobht","ls",NULL);//to run man ls command

    }
    //Second child process to execute grep command
    else if(fork() == 0)
    {
        if(dup2(fd1[0],0) == -1)//redirect from stdin to fd1 reader end
        {
            perror("Error in duplicating in second child for reader end\n");
            close(fd1[0]);close(fd1[1]);//close remaining file descriptor before exit
            close(fd2[0]);close(fd2[1]);
            return EXIT_FAILURE;
        }
        if(dup2(fd2[1],1) == -1)//redirect from stdout to fd2 writer end
        {
            perror("Error in duplicating in second child for writer end\n");
            close(fd1[0]);close(fd1[1]);//close remaining file descriptor before exit
            close(fd2[0]);close(fd2[1]);
            return EXIT_FAILURE;
        }
        close(fd1[1]);
        close(fd2[0]);
        execlp("grep","mygrep","ls",NULL);//to run grep ls command
    }
    //Third child process to execute wc command
    else if(fork() == 0)
    {
        if(dup2(fd2[0],0) == -1)//redirect from stdout to fd2 writer end
        {
            perror("Error in duplicating in third child \n");
            close(fd1[0]);close(fd1[1]);//close remaining file descriptor before exit
            close(fd2[0]);close(fd2[1]);
            return EXIT_FAILURE;
        }
        close(fd1[0]);close(fd1[1]);//close remaining file descriptor
        close(fd2[1]);
        execlp("wc","mywc",NULL);//to run wc command

    }
    //close all file descriptor for parent process since we're not using it
    close(fd1[0]);close(fd1[1]);
    close(fd2[0]);close(fd2[1]);
    for(int i = 0;i<3;i++)
        wait(NULL);//wait until all child terminates
    printf("Program  Ends\n");
    
}