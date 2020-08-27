//program to understand SIGFPE signal
//generated when the floating point exception occurs
//here kernel sends a SIGFPE signal to process
#include<stdio.h>
#include<unistd.h>//for sleep()
int main()
{
    printf(" I am in main\n");
    sleep(1);
    printf("process which divide the no by zero started\n");
    sleep(1);
    //here (a-b) written instead of 0 since to remove warning
    int a = 3,b =3;
    float ans = 3/(a-b);
    return 0;
}