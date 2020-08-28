/* Program that will send the message in message queue using the 
POSIX IPC */
#include<stdio.h>
#include<sys/ipc.h>//for ftok()
#include<stdlib.h>//for EXIT_FAILURE
#include<string.h>//for strcpy()
#define SIZE_MSG 4096//message of size 1KB
#include<fcntl.h>//for O_CREAT

#include<mqueue.h>


#define __DEBUG__
int main()
{
    mqd_t fd_msgqueu;
    //struct mq_attr attr = {O_NONBLOCK,2,SIZE_MSG,1}; 
    char *name = "/pmsgque";//name of message queue
    /* O_NONBLOCK for prevention of blocking */
    if( (fd_msgqueu= mq_open(name,O_CREAT|O_RDONLY|O_NONBLOCK,0666,NULL)) == (mqd_t)-1)
    {
        perror("Error in creating the message queue\n");
        return EXIT_FAILURE;
    }
/****************** Place the First Message  Start *********************************************/ 
    char buff[SIZE_MSG] = {0};
    if( (mq_receive(fd_msgqueu,buff,sizeof(buff),0)) == -1)
    {
        perror("Error in receiving  message \n");
        return EXIT_FAILURE;
    }
    printf("Message Received : %s\n",buff);
/****************** Place the First Message Ends *********************************************/ 
/*
    if( mq_close(fd_msgqueu) == -1)
    {
        perror("Error in closing the message queue \n");
        return EXIT_FAILURE;
    } 
    if( mq_unlink(name) == -1)
    {
        perror("Error in deleting the message queue \n");
        return EXIT_FAILURE;
    }*/
}