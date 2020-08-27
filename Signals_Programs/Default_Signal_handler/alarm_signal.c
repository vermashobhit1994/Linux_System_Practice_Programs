//Program to understand alarm signal
//understand what happens when two alarms set for different time
#include<stdio.h>
#include<unistd.h>

int main()
{
    int first_alarm = alarm(200);
    printf("first_alarm value is %d\n",first_alarm);
    sleep(5);
    int second_alarm = alarm(10);
    //print the remaining value of the first alarm by second alarm
    printf("After 10 s alarm return value is %d\n",second_alarm);
    sleep(100);
}