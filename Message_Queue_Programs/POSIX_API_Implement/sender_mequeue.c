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
    struct mq_attr attr = {0,0,SIZE_MSG,1}; 
    
    char *name = "/pmsgque";//name of message queue
    if( (fd_msgqueu= mq_open(name,O_CREAT|O_WRONLY|O_NONBLOCK,0666,&attr)) == (mqd_t)-1)
    {
        perror("Error in creating the message queue\n");
        return EXIT_FAILURE;
    }
/****************** Place the First Message  Start *********************************************/ 
    const char *msg1 = "Welcome to Message Queue in Linux Programming";
    if( (mq_send(fd_msgqueu,msg1,strlen(msg1),0)) == -1)
    {
        perror("Error in sending first message \n");
        return EXIT_FAILURE;
    }
    printf("First Message sent successfully \n");
/****************** Place the First Message Ends *********************************************/ 

/****************** Place the Second Message Start *********************************************/ 
    const char *msg2 = "This is too easy to understand this program";
    if( (mq_send(fd_msgqueu,msg2,strlen(msg2),0)) == -1)
    {
        perror("Error in sending second message \n");
        return EXIT_FAILURE;
    }
    printf("Second Message sent Successfully \n");
/****************** Place the Second Message Ends *********************************************/ 
        
}