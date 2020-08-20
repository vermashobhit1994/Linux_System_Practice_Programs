/* Program to understand pipe in related process i.e between the child and parent process*/
#include<stdio.h>
#include<string.h>//for strlen()
#include<stdlib.h>//for exit()
#include<unistd.h>//for write() and read()
#include<sys/wait.h>
#define SIZE 4096


int main()
{
    int fd[2];
    int ret_pipe,nbytes_write; 
    if( (ret_pipe = pipe(fd) ) == -1)//create a single pipe in parent process
    {
        perror("Error in creating pipe in parent process\n");
        return EXIT_FAILURE;
    }
    pid_t pid = fork();//create  a child process
    if(pid == -1)
    {
        perror("Error in creating child process\n");
        close(fd[0]);/*close the read and write end if no child process created*/
        close(fd[1]);
        return EXIT_FAILURE;
    }
    if(pid != 0)//parent process
    {
        close(fd[0]);//close the read end of pipe
        const char *msg = "Welcome to pipes understand program\n";
        
        if( (nbytes_write = write(fd[1],msg,strlen(msg)) ) == -1)
        {
            perror("Error while writing by parent process\n");
            return EXIT_FAILURE;
        }
        if(waitpid(pid,NULL,0) == -1)//done so as to wait for child to finish if parent process start first
        {
            perror("Error in waiting for child\n");
            return EXIT_FAILURE;
        }
    }
    else//child process
    {
        close(fd[1]);//close the writer end of pipe
        char buff[SIZE] ;//create a buffer
        //memset(buff,0,sizeof(buff));//clear the buffer
        fprintf(stdout,"Message sent from parent is :");
        int nbytes_read ;
        //here taken SIZE instead of nbytes_write because nbytes_write variable is in separate process
        if( (nbytes_read = read(fd[0],buff,SIZE ) )== -1)
        {
            perror("Error while reading\n");
            return EXIT_FAILURE;
        }
        write(1,buff,nbytes_read);//write to stdout
    }

}