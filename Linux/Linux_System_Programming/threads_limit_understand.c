//Program to understand the max number of threads within proces limit


#include<stdio.h>
#include<pthread.h>

//left blank since no use
void *thread_func(void *arg)
{
}

int main()
{
    int retval = 0, count = 0;
    
    pthread_t id ;
    
    //keep on creating thread until return value is 0 i.e no error.
    while(retval == 0)
    {
        retval = pthread_create( &id, NULL, thread_func,NULL);
        count++;
    }
    
    printf("Count = %d\n",count);//O/P : 32752
}

