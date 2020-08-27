/* Program to understand writer process*/
#include<stdio.h>
#define SIZE 1024//buffer size 1 MB
#include<unistd.h>//for read(),write()
#include<sys/stat.h>//for open()
#include<fcntl.h>//for S_IFIFO
#include<stdlib.h>//for EXIT_FAILURE
#include<string.h>//for strlen()

#define __DEBUG__//activate the debug statements
int main()
{
    /* delete the fifo files if already created*/
    if( (unlink("fifo1") && unlink("fifo2")) == -1)
    {
        perror("Error in removing fifo1 and fifo2\n");
        return EXIT_FAILURE;
    }
    
    #ifdef __DEBUG__
    printf("All pre fifo files deleted\n");
    #endif
    #ifdef __DEBUG__
    printf("Press any key to continue....\n");
    #endif
    
    getchar();//wait until press any key

    //create the first fifo using mknod command
   if(mknod("fifo1",S_IFIFO | 0666,0) == -1)
    {
        perror("Error in creating the fifo using mknod\n");
        return EXIT_FAILURE;
    }  
    if(mkfifo("fifo2",0666) == -1)
    {
        perror("Error in creating the fifo using mkfifo\n");
        unlink("fifo1");//delete the fifo1 
        return EXIT_FAILURE;
    }
    #ifdef __DEBUG__
    printf("Waiting for student to connect\n");
    #endif
    int fd_read,fd_write;
    //open the fifo1 in readonly mode
    if( (fd_read = open("fifo1",O_RDONLY)) == -1)
    {
        perror("Error in opening fifo1\n");
        unlink("fifo1");//delete the fifo1 file
        unlink("fifo2");//delete the fifo2 file 
        return EXIT_FAILURE;
    }
    //open the fifo2 in writeonly mode
    if((fd_write = open("fifo2",O_WRONLY)) == -1)
    {
        perror("Error in opening fifo2 \n");
        close(fd_read);
        unlink("fifo1");//delete the fifo1 file
        unlink("fifo2");//delete the fifo2 file 
        return EXIT_FAILURE;
    }
    
    #ifdef __DEBUG__
    printf("Student connected\n");;
    #endif

    //read from the student
    char tbuff[SIZE] = {0};int nbytes_read,nbytes_write;
    if( (nbytes_read = read(fd_read,tbuff,sizeof(tbuff))) == -1)
    {
        perror("Error in reading via fifo1 \n");
        close(fd_read);//close the read file descriptor for fifo1
        close(fd_write);//close the write file descriptor for fifo2
        unlink("fifo1");//delete the fifo1 file
        unlink("fifo2");//delete the fifo2 file 
        return EXIT_FAILURE;        
    }
    //write to stdout whatever read from student 
    if( (nbytes_write = write(1,tbuff,strlen(tbuff))) == -1)
    {
        perror("Error in reading via fifo1 \n");
        close(fd_read);//close the read file descriptor for fifo1
        close(fd_write);//close the write file descriptor for fifo2
        unlink("fifo1");//delete the fifo1 file
        unlink("fifo2");//delete the fifo2 file 
        return EXIT_FAILURE;        
    }
    //sleep for some time
    sleep(5);
    const char *tmsg = "Teacher Reply: Work Smarter with Hard Work to Gain Success";
    //write the message to be sent to student
    if( (nbytes_write = write(fd_write,tmsg,strlen(tmsg))) == -1)
    {
        perror("Error in reading via fifo1 \n");
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
    
}