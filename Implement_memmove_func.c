//program to implement your own memmove function
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void *mymemmove(void *dest,const void *src,size_t n)
{
    char *pdest = (char*)dest,*psrc = (char*)src;

    //if src pointer is behind the dest pointer 
    if(psrc < pdest)
    {
        //check for overlapping condition
        while( n--  &&  psrc != pdest ) 
            *pdest++ = *psrc++;
        //if overlap happens start from beginning
         psrc = (char*)src;
         while(n--)
             *pdest++ = *psrc++;
    }
//if src pointer is ahead of dest pointer
    else
    {
         while(n--)
     	     *pdest++ = *psrc++;  
    }    
        
}

#include<stdio.h>
int main()
{
    char str[100] = "shobhitverma";
    char *ptr = str;
    memmove(ptr+10,ptr,strlen(str));
    char dest [100];
    memmove(dest,str,strlen(str));
    printf("Original memmove output : %s - %s \n",str,dest);

    printf("My memmove output: %s - %s \n",str,dest);
}
