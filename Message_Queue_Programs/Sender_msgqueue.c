/* Program that will send the message in message queue using the 
System V IPC */
#include<stdio.h>
#include<sys/ipc.h>//for ftok()
#include<stdlib.h>//for EXIT_FAILURE
#include<string.h>//for strcpy()
#include<sys/msg.h>//for msgget()
#define SIZE_MSG 1024//message of size 1KB
#include<unistd.h>//for unlink()
#include<fcntl.h>//for O_CREAT
#include<sys/stat.h>//for open()
#define MSG1 "Welcome to Message Queue in Linux Programming"
#define MSG2 "This is too easy to understand this program"

#define __DEBUG__
/* Structure for message queue*/
struct msgbuf
{
    long msgtype;//priority of message must be >0
    char mtext[SIZE_MSG];//actual message
};
int main()
{
        
    //create a file for key
    if( (creat("mykeyfile",O_CREAT | 0666)) == -1)
    {
        perror("Error in creating the key file\n");
        return EXIT_FAILURE;
    }
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
/****************** Place the First Message  Start *********************************************/ 
    //create a variable of msgbuf and new priority
    struct msgbuf msg1;
    msg1.msgtype = 20;//set the priority of message to be 10
    
    //copy the actual message to mtext field 
    strcpy(msg1.mtext,MSG1);
    //print the actual message copied
    #ifdef __DEBUG__
    printf("Message Copied : %s\n",msg1.mtext);
    #endif
    /*IPC_NOWAIT to return with error if insufficient space in message queue.
    If 0 then blocks.*/
    if( (msgsnd(msgid,&msg1,strlen(msg1.mtext),0)) == -1)
    {
        perror("Error in sending first message \n");
        //delete the key file
        if(unlink("mykeyfile") == -1)
        {
            perror("Error in deleting the key file\n");
            return EXIT_FAILURE;
        }
        return EXIT_FAILURE;
    }
/****************** Place the First Message Ends *********************************************/ 

/****************** Place the Second Message Start *********************************************/ 
    //create a variable of msgbuf and new priority
    struct msgbuf msg2;
    msg2.msgtype = 10;//set the priority of message to be 20
    
    //copy the actual message to mtext field 
    strcpy(msg2.mtext,MSG2);
    //print the actual message copied
    #ifdef __DEBUG__
    printf("Message Copied : %s\n",msg2.mtext);
    #endif
    /*IPC_NOWAIT to return with error if insufficient space in message queue.
    If 0 then blocks.*/
    if( (msgsnd(msgid,&msg2,sizeof(msg2.mtext),IPC_NOWAIT)) == -1)
    {
        perror("Error in sending second message \n");
        return EXIT_FAILURE;
    }
/****************** Place the Second Message Ends *********************************************/ 
    //delete the key file
    //to be done by receiver
    /*if(unlink("mykeyfile") == -1)
    {
        perror("Error in deleting the key file\n");
        return EXIT_FAILURE;
    }*/
    
        
}