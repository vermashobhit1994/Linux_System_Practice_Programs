/* Program to understand how to read and write from a single pipe in single process*/
#include<stdio.h>
#include<string.h>//for strlen()
#include<stdlib.h>//for exit()
#include<unistd.h>//for write() and read()
#define SIZE 4096
int main()
{
    int fd[2],nbytes_read = 0,nbytes_write = 0;//file descriptors where fd[0] -> read and fd[1] -> write
    const char *msg = "Welcome to pipes introduction\n";//constant string to be transferred via pipe
    char buff[SIZE] = {0};
    memset(buff,0,sizeof(buff));//Initialize to 0 by default

    /* create a pipe*/
    if(pipe(fd) == -1)
    {
        perror("Error in creating pipe\n");
        exit(1);
    }    
    /*Writing by using fd[1]*/
    if( (nbytes_write = write(fd[1],msg,strlen(msg)) ) == -1)
    {
        perror("Error in writing the data\n");
        exit(1);
    }
    if( (nbytes_read = read(fd[0], buff,nbytes_write) ) == -1)
    {
        perror("Error in reading the data\n");
        exit(1);
    }
    /* write data to stdout*/
    write(1,buff,nbytes_read);//display message on stdout
    while(1);//done to see extra file descriptor in /proc/pid/fd directory

}