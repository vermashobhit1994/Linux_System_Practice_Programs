/*Program to understand following concept:
1. file descriptor is inherited by child from parent.
2. Current file object is shared between the child and parent. 
*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>//for exit()
#include<fcntl.h>
#include<string.h>
int main()
{
    char *msg1 = "Welcome to linux programming\n";
    char *msg_child = "Hey this is child\n";
    char *msg_parent = "Hey this is parent\n";

    int fd;
    if( (fd = open("f1.txt",O_CREAT|O_WRONLY,0644) ) == -1)
    {
        perror("Error in creating file with required permissions\n");
        return EXIT_FAILURE;
    }
    if(write(fd,msg1,strlen(msg1)) == -1 )
    {
        perror("Error in writing data\n");
        return EXIT_FAILURE;
    }
    //create the child process
    pid_t id = fork();

/*************** here the fd is shared between the child and parent*************/

    /*************** Child process start****************************************/
    if(id == 0)
    {
        if(write(fd,msg_child,strlen(msg_child)) == -1 )
        {
            perror("Error in writing data in child\n");
            return EXIT_FAILURE;
        }
    }
    /*************** Child process ends****************************************/
    
    /*************** Parent process start****************************************/
    
    else
    {
        if(write(fd,msg_parent,strlen(msg_parent)) == -1 )
        {
            perror("Error in writing data in parent\n");
            return EXIT_FAILURE;
        }
    }
    /*************** Parent process ends****************************************/
    
    close(fd);
}