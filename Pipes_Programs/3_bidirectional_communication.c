/* Program to understand bidirectional communication using pipes*/
/* Program to understand pipe in related process i.e between the child and parent process*/
/* Here pipe gets blocked when no data at read end and full in writer end*/ 
#include<stdio.h>
#include<string.h>//for strlen()
#include<stdlib.h>//for exit()
#include<unistd.h>//for write() and read()
#include<sys/wait.h>
#define SIZE 4096


int main()
{
    int fd1[2],fd2[2];
    int ret_pipe,nbytes_write,nbytes_read; 
    if( (ret_pipe = pipe(fd1) ) == -1)//create a first pipe in parent process
    {
        perror("Error in creating first pipe in parent process\n");
        return EXIT_FAILURE;
    }
    if( (ret_pipe = pipe(fd2) ) == -1)//create a first pipe in parent process
    {
        perror("Error in creating second pipe in parent process\n");
        return EXIT_FAILURE;
    }
    pid_t pid = fork();//create  a child process
    if(pid == -1)
    {
        perror("Error in creating child process\n");
        close(fd1[0]);close(fd1[1]);/*close the read and write end if no child process created*/
        close(fd2[0]);close(fd2[1]);
        return EXIT_FAILURE;
    }


/***************************Parent Process Start*************************************************************/
    if(pid != 0)//parent process
    {
        close(fd1[1]);//close the writer end of pipe1
        close(fd2[0]);//close the reader end of pipe2
        char parent_buff[SIZE];
        memset(parent_buff,0,sizeof(parent_buff));//clear the parent buffer
        const char *msgfromparent = "What is your name child ?";
/*********************Here first write then read**************************************************************/
        printf("before write in parent process\n");
        if( (nbytes_write = write(fd2[1],msgfromparent,strlen(msgfromparent)) ) == -1)
        {
            perror("\nError while writing by parent \n");
            close(fd1[0]);close(fd2[1]);//close the remaining file descriptor
            return EXIT_FAILURE;
        }
        printf("before read in parent process\n");
        if( (nbytes_read = read(fd1[0],parent_buff,SIZE ) )== -1)
        {
            perror("\nError while reading in parent \n");
            close(fd1[0]);close(fd2[1]);//close the remaining file descriptor
            return EXIT_FAILURE;
        }
        printf("\n\nI am Parent \n ");
        printf("Parent has received data from child : ");
        fflush(stdout);//clear the stdout so that data received not mix with above printf statement
        write(1,parent_buff,nbytes_read);//write to stdout
        
    }
/***************************Parent Process Ends*************************************************************/

/***************************Child Process Start*************************************************************/
    if(pid == 0)//child process
    {
        close(fd1[0]);//close the reader end of pipe1
        close(fd2[1]);//close the writer end of pipe2
        char child_buff[SIZE] ;//create a buffer
        memset(child_buff,0,sizeof(child_buff));//clear the child buffer
        const char *msgfromchild = "Helloo from child\n";
        
        
/***************************Here first read then write in child process********************************/

        //child reads data from parent
        //here taken SIZE instead of nbytes_write because nbytes_write variable is in separate process
        printf("before read in child process\n");
        if( (nbytes_read = read(fd2[0],child_buff,SIZE ) )== -1)
        {
            perror("\nError while reading in child \n");
            close(fd1[1]);close(fd2[0]);
            return EXIT_FAILURE;
        }
        
        printf("I am child process\n");
        fprintf(stdout,"Parent asked :");
        fflush(stdout);//done so as to avoid the mixing of above printf and data received by child
        write(1,child_buff,nbytes_read);//write to stdout
        
        //child sends data to parent
        if( (nbytes_write = write(fd1[1],msgfromchild,strlen(msgfromchild) ) )== -1)
        {
            perror("\nError while writing in child \n");
            close(fd1[1]);close(fd2[0]);
            return EXIT_FAILURE;
        }
    }
/***************************Child Process Ends*************************************************************/


}