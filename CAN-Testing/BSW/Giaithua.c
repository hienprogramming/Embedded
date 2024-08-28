#include<stdio.h>

int giaithua(int n)
{
    if(n < 0){
        return -1;
    }
    else if(n == 0 || n == 1){
        return 1;
    }
    else{
        return giaithua(n-1)*n;
    }
}

int main(){
    int n = 10;
    int value = giaithua(10);
    printf("Value: %d", value);
    return 1;
}