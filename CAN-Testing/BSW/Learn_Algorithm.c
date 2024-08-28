// #include<stdio.h>
// #include<stdbool.h>

// void swap(int *a, int *b){
//     int tem = *a;
//     *a = *b;
//     *b = tem;
// }

// void giandan(int array[], int size)
// {
//     for(int i=0; i<size; i++){
//         for(int j=i+1; j<size; j++){
//             if(array[i]<array[j]){
//                 swap(&array[i], &array[j]);
//             }
//         }
//     }
// }

// void tangdan(int array[], int size){
//     for(int i=0; i<size; i++){
//         for(int j=i+1; j<size; j++){
//             if(array[i]>array[j]){
//                 swap(&array[i], &array[j]);
//             }
//         }
//     }
// }

// // 2. Thuật toán tìm kiếm (Binary Search):

// void Search(int arr[], int size, int target) {
//     int found = 0;

//     // Duyệt qua mảng để tìm số 38
//     for (int i = 0; i < size; i++) {
//         if (arr[i] == target) {
//             printf("Số %d xuất hiện ở vị trí %d trong mảng.\n", target, i);
//             found = 1;
//         }
//     }

//     if (!found) {
//         printf("Số %d không xuất hiện trong mảng.\n", target);
//     }
// }

// int main()
// {

//     // 1. Thuật toán sắp xếp (Bubble Sort):
//     int arr[] = {9, 38, 88, 77, 3, 38};

//     printf("Giam dan:\n");
//     giandan(arr, sizeof(arr)/sizeof(arr[0]));
//     for(int i=0; i<sizeof(arr)/sizeof(arr[0]); i++){
//         printf("Arr[%d] = %d\n", i, arr[i]);
//     }

//     printf("Tang dan:\n");
//     tangdan(arr, sizeof(arr)/sizeof(arr[0]));
//     for(int i=0; i<sizeof(arr)/sizeof(arr[0]); i++){
//         printf("Arr[%d] = %d\n", i, arr[i]);
//     }

//     // 2. Thuật toán tìm kiếm (Binary Search):

//     Search(arr, sizeof(arr) / sizeof(arr[0]), 38);

//     return 1;
// }

#include <stdio.h>

// Hàm hoán đổi hai số
void swap(int *a, int *b) {
    int tem = *a;
    *a = *b;
    *b = tem;
}

// Hàm sắp xếp giảm dần
void giandan(int array[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (array[i] < array[j]) {
                swap(&array[i], &array[j]);
            }
        }
    }
}

// Hàm sắp xếp tăng dần
void tangdan(int array[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (array[i] > array[j]) {
                swap(&array[i], &array[j]);
            }
        }
    }
}
// int arr[] = {9, 38, 88, 77, 3, 38};
// Hàm tìm kiếm số trong mảng
void Search(int arr[], int size, int target) {
    int found = 0;

    // Duyệt qua mảng để tìm số target
    for (int i = 0; i < size; i++) {
        if (arr[i] == target) {
            printf("Số %d xuất hiện ở vị trí %d trong mảng.\n", target, i);
            found = 1;
        }
    }

    if (!found) {
        printf("Số %d không xuất hiện trong mảng.\n", target);
    }
}

int main() {
    int arr[] = {9, 38, 88, 77, 3, 38};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Giảm dần:\n");
    giandan(arr, size);
    for (int i = 0; i < size; i++) {
        printf("Arr[%d] = %d\n", i, arr[i]);
    }

    printf("Tăng dần:\n");
    tangdan(arr, size);
    for (int i = 0; i < size; i++) {
        printf("Arr[%d] = %d\n", i, arr[i]);
    }

    // Tìm kiếm số 38 trong mảng
    Search(arr, size, 38);

    return 0;
}