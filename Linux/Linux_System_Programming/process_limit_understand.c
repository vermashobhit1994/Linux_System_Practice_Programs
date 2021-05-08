	//Program to understand the maximum number of process per user


#include<stdio.h>
#include<unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

#include<signal.h>

int parent_pid = 0;


int main()
{

    pid_t id;
    
    int count = 0;
     struct rlimit rlim;
    getrlimit(RLIMIT_NPROC, &rlim);
    printf("RLIMIT_NPROC soft: %ld, hard: %ld\n", rlim.rlim_cur, rlim.rlim_max);
    
    parent_pid = getpid();
    
    
    
    int i = 0;
    
    
    while(1)
    {
        id = fork();
        if(id == -1)
        {
            printf("Total number of process = %d\n",count);
            //killing all process created
            if ( kill (0, SIGKILL) == -1)
            {
                perror ("Error in killing process\n");
                
            }
           
            return 0;
        }
        
        if (id == 0)
        {
            while(1)
            	sleep(10);
        }
        i++;
        //increment the count inside parent process
        count++;
         
       
    }
    printf("Count = %d\n",count);
     
     
     
}
