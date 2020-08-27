/* Program to understand reader process*/
#include<stdio.h>
#define SIZE 1024//buffer size 1 MB
#include<unistd.h>//for read(),write()
#include<sys/stat.h>//for open()#include<fcntl.h>//for S_IFIFO
#include<stdlib.h>//for EXIT_FAILURE
#include<string.h>//for strlen()
#include<fcntl.h>//for S_IFIFO

#define __DEBUG__//activate the debug statements
int main()
{
    //create the first fifo using mknod command
    //This fifo file is created by teacher
    /*if(mknod("fifo1",S_IFIFO | 0666,0) == -1)
    {
        perror("Error in creating the fifo using mknod\n");
        return EXIT_FAILURE;
    }  
    if(mkfifo("fifo2",0666) == -1)
    {
        perror("Error in creating the fifo using mkfifo\n");
        unlink("fifo1");//delete the fifo1 
        return EXIT_FAILURE;
    }*/
    #ifdef __DEBUG__
    printf("Waiting for teacher to connect\n");
    #endif
    int fd_read,fd_write;
    //open the fifo1 in readonly mode
    if( (fd_write = open("fifo1",O_WRONLY)) == -1)
    {
        perror("Error in opening fifo1\n");
        unlink("fifo1");//delete the fifo1 file
        unlink("fifo2");//delete the fifo2 file 
        return EXIT_FAILURE;
    }
    //open the fifo2 in writeonly mode
    if((fd_read = open("fifo2",O_RDONLY)) == -1)
    {
        perror("Error in opening fifo2 \n");
        close(fd_write);
        unlink("fifo1");//delete the fifo1 file
        unlink("fifo2");//delete the fifo2 file 
        return EXIT_FAILURE;
    }
    
    #ifdef __DEBUG__
    printf("Teacher connected\n");;
    #endif

    //write the message to teacher
    const char *smsg = "Student Asked : This Program is little bit messy to understand?";
    int nbytes_read,nbytes_write;
    if( (nbytes_write = write(fd_write,smsg,strlen(smsg))) == -1)
    {
        perror("Error in writing via fifo1 \n");
        close(fd_read);//close the read file descriptor for fifo1
        close(fd_write);//close the write file descriptor for fifo2
        unlink("fifo1");//delete the fifo1 file
        unlink("fifo2");//delete the fifo2 file 
        return EXIT_FAILURE;        
    }
    
    char sbuff[SIZE] = {0};
    //write the message to be sent to student
    if( (nbytes_read = read(fd_read,sbuff,sizeof(sbuff))) == -1)
    {
        perror("Error in writing via fifo2 \n");
        close(fd_read);//close the read file descriptor for fifo1
        close(fd_write);//close the write file descriptor for fifo2
        unlink("fifo1");//delete the fifo1 file
        unlink("fifo2");//delete the fifo2 file 
        return EXIT_FAILURE;        
    }
    //write to stdout whatever read from teacher 
    if( (nbytes_read= write(1,sbuff,strlen(sbuff))) == -1)
    {
        perror("Error in writing to stdout via fifo2 \n");
        close(fd_read);//close the read file descriptor for fifo1
        close(fd_write);//close the write file descriptor for fifo2
        unlink("fifo1");//delete the fifo1 file
        unlink("fifo2");//delete the fifo2 file 
        return EXIT_FAILURE;        
    }
    /* close all file descriptors*/
    close(fd_read);
    close(fd_write);
    printf("\n");
    /* delete the fifo files created*/
    unlink("fifo1");
    unlink("fifo2");

}