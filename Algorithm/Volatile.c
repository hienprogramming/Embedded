#include<stdio.h>
#include<stdbool.h>
volatile int systemtime;

int main()
{
    static int currenttime;
    while (true)
    {
        currenttime = systemtime;
    }
    return currenttime; // get system time and made via memory to get systemtime (volatile)
}