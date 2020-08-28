/* Program that will receive the message in message queue using the 
System V IPC */
#include<stdio.h>
#include<sys/ipc.h>//for ftok()
#include<stdlib.h>//for EXIT_FAILURE
#include<string.h>//for strcpy()
#include<sys/msg.h>//for msgget()
#define SIZE_MSG 4096//message of size 1KB
#include<unistd.h>//for unlink()
#include<fcntl.h>//for O_CREAT
#include<sys/stat.h>//for open()
#define MSG_HIGH_PRIO "Welcome to Message Queue in Linux Programming"
#define MSG_LOW_PRIO "This is too easy to understand this program"

#define __DEBUG__
/* Structure for message queue*/
struct msgbuf
{
    long msgtype;//priority of message must be >0
    char mtext[SIZE_MSG];//actual message
};
int main()
{
        
    
    //create a unique key
    key_t key;
    
    if( (key = ftok("mykeyfile",65)) == -1)
    {
        perror("Error in creating the key\n");
        //delete the key file
        if(unlink("mykeyfile") == -1)
        {
            perror("Error in deleting the key file\n");
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }
    /*create an entry in msgqueue.
    Here the IPC_EXCL Flag specify that if msgqueue already exists with key 
    then msgid fails */
    int msgid;
    
    if( (msgid = msgget(key,IPC_CREAT  |0666)) == -1)
    {
        perror("Error in creating the entry in message queue\n");
        //delete the key file
        if(unlink("mykeyfile") == -1)
        {
            perror("Error in deleting the key file\n");
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }
/****************** Receving Message  Start *********************************************/ 
    //create a variable of msgbuf and new priority
    struct msgbuf msg1;
    
    /*IPC_NOWAIT to return with error if insufficient space in message queue.
    If 0 then blocks.
    here the message are received in sequential order.*/
    ssize_t ret_msgreceive;
   /**************** RECEIVE MESSAGE ONE By ONE START ************************************/ 
    /*
    // comment the keyfile and msgqueue file
    if((ret_msgreceive = msgrcv(msgid,&msg1,sizeof(msg1.mtext),0,IPC_NOWAIT)) == -1)
    {
        perror("Error in receiving message\n");
        //delete the key file
        if(unlink("mykeyfile") == -1)
        {
            perror("Error in deleting the key file\n");
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;

    }
    printf("Received message : %s\n",msg1.mtext);
    */
    /**************** RECEIVE MESSAGE ONE By ONE ENDS************************************/
    
    //continuously receive message
    while((ret_msgreceive = msgrcv(msgid,&msg1,sizeof(msg1.mtext),0,IPC_NOWAIT)) != -1)
    {
        if(ret_msgreceive == -1)
        {
            perror("Error in receiving message\n");
            //delete the key file
            if(unlink("mykeyfile") == -1)
            {
                perror("Error in deleting the key file\n");
                return EXIT_FAILURE;
            }
            return EXIT_FAILURE;
        }
        printf("Message Received : %s\n",msg1.mtext);

    }
    
/****************** Receving Message Ends *********************************************/ 


    //delete the key file
    if(unlink("mykeyfile") == -1)
    {
        perror("Error in deleting the key file\n");
        return EXIT_FAILURE;
    }
    
    //delete the message queue
    if( (msgctl(msgid,IPC_RMID,NULL)) == -1 )
    {
        perror("Error in deleting the message queue id \n");
        return EXIT_FAILURE;        
    }
}