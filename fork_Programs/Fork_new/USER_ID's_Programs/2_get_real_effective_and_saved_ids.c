//Program to print the real, effective and saved uid for user and group
// to verify use below command
//          cat /etc/passwd | grep vermas
/* If run with root i.e sudo ./a.out then the id is 0*/
/* If run with different user other than root then print the corresponding id's*/

#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h>//for getresuid() and getresgid()
int main()
{
    uid_t ruid,euid,suid;
    if(getresuid(&ruid, &euid, &suid) == -1)//to get the user real,effective and saved id's
    {
        perror("Error while getting the uid's \n");
        return 0;
    }

    //Printing the user id's
    printf("The Real user id = %d\n",ruid);
    printf("The Effective user id = %d\n",euid);
    printf("The Saved user id = %d\n",suid);
    
    gid_t rgid,egid,sgid;
    if(getresgid(&rgid, &egid, &sgid) == -1)//to get the group real,effective and saved id's
    {
        perror("Error while getting the uid's \n");
        return 0;
    }
    printf("\n\nThe Real group id = %d\n",rgid);
    printf("The Effective group id = %d\n",egid);
    printf("The Saved group id = %d\n",sgid);
    

}
