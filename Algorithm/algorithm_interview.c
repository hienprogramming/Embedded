// Cho 1 mang n pham tu. Sap xep theo thu tu giam dan va nguoc lai
#include<stdio.h>

void swap(int *a, int *b){
    int tem = *a;
    *a = *b;
    *b = tem;
}

void giandan(int array[], int size)
{
    for(int i=0; i<size; i++){
        for(int j=i+1; j<size; j++){
            if(array[i]<array[j]){
                swap(&array[i], &array[j]);
            }
        }
    }
}

void tangdan(int array[], int size){
    for(int i=0; i<size; i++){
        for(int j=i+1; j<size; j++){
            if(array[i]>array[j]){
                swap(&array[i], &array[j]);
            }
        }
    }
}

int max_number(int array[], int size){


  int max = array[0]; // Giả sử phần tử đầu tiên là lớn nhất
  int max_index = 0; // Vị trí của phần tử lớn nhất

  // Duyệt qua mảng để tìm giá trị lớn nhất
  for (int i = 1; i < size; i++) {
    if (array[i] > max) {
      max = array[i];
      max_index = i;
    }
  }

  printf("Giá trị lớn nhất: %d\n", max);
  printf("Vị trí của giá trị lớn nhất: %d\n", max_index);
  return max_index;
}
int main(){
    int arr[] = {9, 38, 88, 77, 3};
    printf("Giam dan:\n");
    giandan(arr, sizeof(arr)/sizeof(arr[0]));
    for(int i=0; i<sizeof(arr)/sizeof(arr[0]); i++){
        printf("Arr[%d] = %d\n", i, arr[i]);
    }

    printf("Tang dan:\n");
    tangdan(arr, sizeof(arr)/sizeof(arr[0]));
    for(int i=0; i<sizeof(arr)/sizeof(arr[0]); i++){
        printf("Arr[%d] = %d\n", i, arr[i]);
    }

    printf("Max value:\n");
    max_number(arr, sizeof(arr)/sizeof(arr[0]));
}