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


// #include<stdio.h>
// #include<string.h>
// int main(){
//     int n = 4;
//     int *arr = (int *)malloc(n * sizeof(int));
//     if(arr == NULL)
//     {
//         return -1;
//     }
//     else{
//         printf("Nhap mang\n");
//         for (int i = 0; i < sizeof(n); i++){
//             scanf("%d", &arr[i]);
//         }

//         printf("In ra man hinh\n");
//         for (int i = 0; i < sizeof(n); i++){
//             printf("arr[%d] = %d\d", i, arr[i]);
//         }        
//     }
//     free(arr);
// }