// Program that write to fifo i.e string entered by user
#include<stdio.h>
#define SIZE 1024
#include<fcntl.h>//for S_FIFO
#include<unistd.h>//for read()
#include<stdlib.h>//for EXIT_FAILURE
#include<string.h>//for strlen()
#include<sys/stat.h>//for mknod()
#define __DEBUG__
int main()
{
    //user buffer for writing the data
    char ubuff[SIZE] = {0};
    unlink("myfifo");
    if(mknod("myfifo",S_IFIFO | 0666,0) == -1)
    {
        perror("Error in creating the fifo\n");
        return EXIT_FAILURE;
    }
    #ifdef __DEBUG__
    printf("Waiting for the readers\n");
    #endif
    int fd_write;
    if( (fd_write = open("myfifo",O_WRONLY) ) == -1)
    {
        perror("Error in opening the fifo\n");
        return EXIT_FAILURE;
    } 
    #ifdef __DEBUG__
    printf("Readers Connected .\n");
    #endif
    #ifdef __DEBUG__
    printf("Type Some text to be sent: ");
    #endif
    int nbytes_write;
    //read from stdin and write to myfifo
    while(fgets(ubuff,SIZE,stdin))
    {
        
        if( (nbytes_write = write(fd_write,ubuff,strlen(ubuff))) == -1)
        {
            perror("Error in writing data ");
            return EXIT_FAILURE;
        }
        printf("\n%d bytes written successfully\n",nbytes_write);
        //clear the buffer
        //memset(ubuff,0,sizeof(ubuff));
      
        #ifdef __DEBUG__
        printf("\nType Some text to be sent: ");
        #endif
        
    };
}