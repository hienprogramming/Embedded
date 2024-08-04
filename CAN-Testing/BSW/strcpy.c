// strncpy copy string - chuỗi
#include<stdio.h>
#include<string.h>
int main()
{
    char str[] = "Hello world";
    char destination[10];
    strncpy(destination, str, 5); //copy 5 words in this string
    printf("Destination: %s", destination);
}