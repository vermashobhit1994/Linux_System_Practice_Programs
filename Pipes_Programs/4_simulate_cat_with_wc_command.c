//Program to simulate the cat filename | wc command 
/* To cross check run cat filename | wc command on terminal.
First output is no of lines
Second output is no of words
Third output is no of characters*/

#include<stdio.h>
#include<stdlib.h>//for EXIT_FAILURE
#include<unistd.h>//for  fork(),dup2(),execlp()
int main()
{
    int fd[2];
    //create a pipe
    if(pipe(fd) == -1)
    {
        perror("Error in creating pipe\n");
        return EXIT_FAILURE;
    }
    pid_t pid = fork();//create  a child process
    if(pid == -1)
    {
        perror("Error in creating child process\n");
        close(fd[0]);close(fd[1]);/*close the read and write end if no child process created*/
        return EXIT_FAILURE;
    }
/*********************** Parent Process Start***************************************************/
    if(pid != 0)
    {
        printf("Before dup2 system call in parent\n");
        /* After below statement whatever we write to stdout using printf will go to 
        pipe writer end*/
        if(dup2(fd[1],1) == -1)//redirect stdout to writer end of pipe
        {
            perror("Error in creating pipe\n");
            return EXIT_FAILURE;
        }
        //the below statement goes to writer end of pipe
        printf("Before closing reader end in parent\n");
        
        close(fd[0]);//close the reader end of pipe

        //the below statement goes to writer end of pipe
        printf("I am Parent\n");
        
        execlp("cat","mycat","file_cat_cmd.txt",NULL);//read from file file_cat_cmd.txt
    }
/*********************** Parent Process ends***************************************************/

/*********************** Child Process Start***************************************************/
    if(pid == 0)
    {
        printf("Before dup2 system call in child\n");
        //whatever data input taken by stdin is now done by reader end of pipe
        if(dup2(fd[0],0) == -1)//redirect stdin to read end of pipe
        {
            perror("Error in creating pipe\n");
            close(fd[1]);close(fd[0]);
            return EXIT_FAILURE;
        }
        printf("Before closing writer end in child\n");
        close(fd[1]);//close the writer end of pipe
        printf("I am child\n");
        execlp("wc","mywc",NULL);
    }
/*********************** Child Process Ends***************************************************/



}