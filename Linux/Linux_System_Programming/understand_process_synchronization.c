//Program to understand how synchronization is achieved in process


#include<stdio.h>

#include<unistd.h>

#define MAX 1000
int global_val = 0;

int main()
{
     
     
     pid_t id ;
     
     int i = 0;
     id = fork();
     
     
     if(id == 0)
     {
         printf("child with pid = %d and ppid = %d\n",getpid(),getppid());
         while(i < MAX)
         {
             global_val++;
             printf("Current val of global_val in child = %d\n",global_val);
             i++;
            // sleep(1);
         }
     }
     
     else
     {
         printf("Parent with pid = %d and ppid = %d\n",getpid(),getppid());
         while(i < MAX)
         {
             global_val--;
             i++;
             printf("Current val of global_val in parent = %d\n",global_val);
            // sleep(1);
         }
     }
}
