//Program to understand what is thread safe and reentrant function

#include<stdio.h>

#define THREAD_NO 10000
#include<pthread.h>

#define LOOP 1000000

#include<unistd.h>

/* this variable will be updated every time swap() is called */
//int t ;//global variable


/* Here t isn't updated. 
Here the global variable is thread-safe but not reentrant.*/
__thread int t;

struct data
{
  int *x,  *y;  
};

void *swap(void *arg)
{
    //int t;
    
    //int s = t;
    
    
    struct data *d  = ( (struct data*)arg);
    t = *(d -> x);
    *(d -> x) = *(d -> y);
    *(d -> y) = t;
    
    
    
    printf("t in swap  = %d\n\n",t);
    
    for(int i = 0;i< LOOP;i++)
        t++;
     printf("After updating t = %d\n",t);
     
     //sleep(3);
    // t = s;
     
     printf("swap function ends\n");
}

/*
void *dec_global_var(void *arg)
{
    //int t = LOOP;
    printf("inside decrement global var \n");
    for(int i = 0;i<LOOP;i++)
    	t1--;
     printf("Decrement val = %d\n",t1);
     
     printf("decrement function ends\n\n");
}
*/
int main()
{
    //stack smashing detected error if put 2 insted of THREAD_NO
    pthread_t threadid[THREAD_NO];
    
    int x= 45, y = 60; 
    struct data d1 = {&x, &y};
    
    printf("Original values x = %d, y = %d\n",x,y);
    
    //creating array of threads
    for(int i= 0;i<THREAD_NO ;i++)
    {
        if ( pthread_create(&threadid[i], NULL, swap,(void*)&d1) != 0 )
        {
            fprintf( stderr,"Error while creating %ld thread\n",threadid[i] );
            
        } 
        else 
        	printf("%ld thread created success\n",threadid[i]);
        
       /* 
        pthread_t decid;
	    if ( pthread_create(&decid, NULL, dec_global_var, NULL) != 0 )
	    {
		fprintf(stderr, "Error in decrement %ld thread \n", decid);
	    }
		
            else
                printf("%ld thread created successfully\n",decid);
    */
    
       
        printf("Current values are x = %d y = %d t= %d\n",*(d1.x), *(d1.y),t);  
        //printf("t = %d\n",t);
        
    }
     
    
    /*
    for(int i = 0;i<THREAD_NO;i++)
    {
    if ( pthread_join( threadid[i], NULL) != 0)
        {
            fprintf( stderr,"Error while waiting %ld thread\n",threadid[i] );
            
        
        
        }
    }
    
    if ( pthread_join( decid, NULL) != 0)
        {
            fprintf( stderr,"Error while waiting %ld thread\n",decid );
            
        
        
        }
        */
        //while(1);
    
    
    
    
}
