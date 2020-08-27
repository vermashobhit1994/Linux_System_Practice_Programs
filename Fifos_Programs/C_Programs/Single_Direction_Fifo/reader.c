//Program that will read from fifo
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
    char dbuff[SIZE] = {0};
    //create a fifo name myfifo with RW permission for user,other and group
    /*if(mknod("myfifo",S_IFIFO | 0666,0) == -1)
    {
        perror("Error in creating the fifo\n");
        return EXIT_FAILURE;
    }*/
    #ifdef __DEBUG__
    printf("Waiting for the writers\n");
    #endif
    int fd_read;
    if( (fd_read = open("myfifo",O_RDONLY) ) == -1)
    {
        perror("Error in opening the fifo\n");
        return EXIT_FAILURE;
    } 
    #ifdef __DEBUG__
    printf("Writer Connected .\n");
    #endif
    int nbytes_read;
    //read from stdin and write to myfifo
    
    while((nbytes_read = read(fd_read,dbuff,sizeof(dbuff)) ) > 0)
    {
        
        printf("Reader read %d bytes with data : %s ",nbytes_read-1,dbuff);
        //clear the buffer
        memset(dbuff,0,sizeof(dbuff));
      
    }
    /*
    do
    {
        (nbytes_read = read(fd_read,dbuff,sizeof(dbuff)));
        printf("Reader read %d bytes with data : %s ",nbytes_read,dbuff);
        //clear the buffer
        memset(dbuff,0,sizeof(dbuff));

    }while(nbytes_read  > 0);*/

}