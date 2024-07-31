#include<stdio.h>
#include<stdlib.h>

int main()
{
    int n;
    printf("Nhap n phan tu: ", n);
    scanf("%d", &n);
    int *arr = (int *) malloc(n * sizeof(int));
    if (arr == NULL){
        printf("Cap phat error\n");
        return -1;
    }
    // Nhap data
    printf("Nhap data phan tu:\n");
    for (int i=0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    // In data
    printf("In data phan tu:\n");
    for (int i=0; i < n; i++){
        printf("Data[%i]: %d\n", i, arr[i]);
    }
    free(arr);
}