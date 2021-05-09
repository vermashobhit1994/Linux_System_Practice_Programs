//Program to understand thread safe vs reentrant function 


#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#define NUM_CNT            100 //5000000//5 million

#define THREAD_CNT          2


#define THREAD_LOOP         1000


__thread int t  = 0;//Making the global variable as thread safe/non-reentrant function i.e this variable now becomes per thread resource /thread local variable.



//function that can be reentrant /thread safe.
void swap(int *x, int *y) {
  t = *x;
  
  
  *x = *y;
  // `my_func()` could be called here
  sleep(2);
  *y = t;
}

//global variable for storing the sum
int sum = 0;

//function used by THREAD_CNT threads
//Here we are adding the number passed to thread upto NUM_CNT times
void* count_no(void *arg)
{
    int cnt = *( (int*)arg );
    
    for(int i = 0;i<NUM_CNT;i++)
    	/* critical section start */
    	sum += cnt;
    	/* crtical section ends*/
   
   
   int x = cnt, y = 2;
   
   printf("before swap x= %d, y = %d, t = %d for thread id = %ld\n",x,y,t,pthread_self());
   swap(&x,&y);
   
   printf("After swap x = %d, y = %d, t = %d for thread id = %ld\n",x,y,t,pthread_self());
   
   printf("\n\n\n");
   
}



int main()
{
     int n = 0;
     printf("Enter the value of n\n");
     scanf("%d",&n);

     pthread_t ThreadID[THREAD_CNT] ;
     
     
     //making the two threads runs parallel
     for(int i = 0;i < THREAD_LOOP;i++) 
     
     {
         //creating the thread
         if( pthread_create( &ThreadID[0] , NULL, count_no, &n) )
         {
             fprintf(stdout,"Error in creating %d thread\n",1);
             return EXIT_FAILURE;
         }
          
         int n1 = -n - 10;
     
         if( pthread_create( &ThreadID[1] , NULL, count_no, &n1) )
         {
             fprintf(stdout,"Error in creating %d thread\n",2);
             return EXIT_FAILURE;
         }
     
         printf("Current value of sum = %d, t = %d\n",sum,t);
         
         //waiting for all the threads by main thread
         if( pthread_join( ThreadID[0] , NULL) )
         {
             fprintf(stdout,"Error in waiting for %d thread\n",1);
             return EXIT_FAILURE;
         }
          
         if( pthread_join( ThreadID[1] , NULL) )
         {
             fprintf(stdout,"Error in waiting for %d thread\n",2);
             return EXIT_FAILURE;
         }
     
      } 
     printf("All threads execution completed\n");
     
     /* Without using the synchronization we're not getting the result = 0*/
     printf("Result = %d\n",sum);//must be 0
     
}




