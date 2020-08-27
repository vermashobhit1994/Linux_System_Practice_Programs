//program to understand SIGINT, SIGTSTP , SIGQUIT signal 

#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>
void myhandler(int signum)
{
    switch(signum)
    {
        case SIGINT:
            printf("I am in signal handler for the signal SIGINT and no %d \n",signum);
            signal(SIGINT,SIG_DFL);
            break;
        case SIGQUIT:
            printf("I am in signal handler for the signal SIGQUIT and no %d\n",signum);
            signal(SIGQUIT,SIG_DFL);
            break;
        case SIGTSTP:
            printf("I am in signal handler for the signal SIGTSTP and no %d\n",signum);
            signal(SIGTSTP,SIG_DFL);
            break;
        case SIGFPE:
            printf("I am in signal handler for the signal SIGFPE and no %d\n",signum);
            signal(SIGFPE,SIG_DFL);
            break;
        case SIGKILL:
            printf("I am in signal handler for the signal SIGKILL and no %d\n",signum);
            signal(SIGKILL,SIG_DFL);
            break;
        case SIGSTOP:
            printf("I am in signal handler for the signal SIGSTOP and no %d\n",signum);
            signal(SIGSTOP,SIG_DFL);
            break;
        
        
    }
}

int main()
{
    signal(SIGINT,myhandler);
    signal(SIGQUIT,myhandler);
    signal(SIGTSTP,myhandler);
    signal(SIGFPE,myhandler);
    signal(SIGKILL,myhandler);
    signal(SIGSTOP,myhandler);
    while(1)
    {
        printf("I am in infinite loop\n");
        sleep(1);
    }
}