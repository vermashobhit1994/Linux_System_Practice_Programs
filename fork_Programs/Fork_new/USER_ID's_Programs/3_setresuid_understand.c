//Program to understand how to change the real,effective and saved user id's
/* Here if we change the owner from any user to root(owner of program) with SUID bit set and any group
then the program runs with power of root(owner of program) .*/ 


#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>//for getresuid() and setresuid()
#include<stdlib.h>//for EXIT_FAILURE
#include<stdio.h>
int main()
{
    uid_t ruid,euid,suid;
    if(getresuid(&ruid, &euid, &suid) == -1)
    {
        perror("Error while getting the real,effective and userid\n");
        return EXIT_FAILURE;
    }
    //Printing the user id's
    printf("The Real user id = %d\n",ruid);
    printf("The Effective user id = %d\n",euid);
    printf("The Saved user id = %d\n",suid);
    
    printf("\n\n");
    //set the real userid = 100,effective userid = 2000 and saved userid = 3000  
    if( setresuid(100,2000,3000) == -1)
    {
        perror("Error while setting the real,effective and userid\n");
        return EXIT_FAILURE;        
    }

    printf("\n\nsAfter changing the id's \n");
    //again getting the id's after modification
    if(getresuid(&ruid, &euid, &suid) == -1)
    {
        perror("Error while getting the real,effective and userid\n");
        return EXIT_FAILURE;
    }
    
    //Printing the user id's
    printf("The Real user id = %d\n",ruid);
    printf("The Effective user id = %d\n",euid);
    printf("The Saved user id = %d\n",suid);
    

}