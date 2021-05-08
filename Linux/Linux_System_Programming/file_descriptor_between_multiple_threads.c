//Program to understand what happened when file descriptor is opened in one thread


#include<stdio.h>

#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#include<pthread.h>

#include<unistd.h>

#include<string.h>


    int fd = 0;
    char *inc_thread_msg = "Hello from increment thread";
    char *dec_thread_msg = "Hello from decrement thread";
void *inc_thread(void *arg)
{
     //int fd = *( (int*)arg );
     write(fd , inc_thread_msg, strlen(inc_thread_msg) );   
}


void *dec_thread(void *arg)
{
     //int fd = *( (int*)arg );
    write(fd , dec_thread_msg, strlen(dec_thread_msg) );  
}

int main()
{
    //int fd = 0;//gives error
    
    if ( (fd  = open("f2.txt", O_CREAT | O_RDWR,0644)) == -1)
    {
        perror("Error in opening the file \n");
        return -1;
    }
    
    printf("fd =  %d\n",fd);
    
    if(write(fd,"Hello World",strlen("Hello World")) == -1 )
        {
            perror("Error in writing data\n");
            return -1;
        } 
    //creating the increment thread
    pthread_t inc_id;
    if (pthread_create(&inc_id, NULL, inc_thread,&fd ) != 0)
    {
        perror("Error in creating inc thread\n");
        return -1;
        
        
    }
    

    //creating the increment thread
    pthread_t dec_id;
    if (pthread_create(&dec_id, NULL, dec_thread,&fd ) != 0)
    {
        perror("Error in creating dec thread\n");
        return -1;
        
        
    }
    
    
    if ( pthread_join(inc_id, NULL) != 0)
    {
        perror("Error in waiting for inc thread\n");
    }
    
    if ( pthread_join(dec_id, NULL) != 0)
    {
        perror("Error in waiting for dec thread\n");
    }
    
    
   
    
     
    
    

    
}

