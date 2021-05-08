/*Program to understand following concept:
1. file descriptor (PPFDT - Per process file descriptor table) is inherited by child from parent.
This PPFDT is nothing but the table inside /proc/pid/fd directory.
to check the maximum number of descriptor use below command:
getconf OPEN_MAX
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
     //file created with RW Permissions for admin,R permissions for group and user 
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
    
        getchar();
    //create the child process
    pid_t id = fork();
    
    
   
    

/*************** here the fd is shared between the child and parent*************/
/*************** here the file object is also shared between the parent and child*/

    /*************** Child process start****************************************/
    if(id == 0)
    {
    
        printf("INside child process\n");
        int nbytes_write = 0;
        if(nbytes_write = write(fd,msg_child,strlen(msg_child)) == -1 )
        {
            perror("Error in writing data in child\n");
            return EXIT_FAILURE;
        }
        
        printf("child writes %d bytes successfully\n",nbytes_write);
    }
    /*************** Child process ends****************************************/
    
    /*************** Parent process start****************************************/
    
    else
    {
        printf("inside parent process\n");
        
        
    
        
        
        if(write(fd,msg_parent,strlen(msg_parent)) == -1 )
        {
            perror("Error in writing data in parent\n");
            return EXIT_FAILURE;
        }
    }
    /*************** Parent process ends****************************************/
    
    getchar();
    close(fd);
}
