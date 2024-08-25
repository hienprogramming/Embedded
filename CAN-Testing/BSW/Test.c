#include <stdio.h>

int main() {
    int arr[] = {9, 38, 88, 77, 3, 38};
    int n = sizeof(arr) / sizeof(arr[0]);
    int target = 38;
    int found = 0;

    // Duyệt qua mảng để tìm số 38
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            printf("Số %d xuất hiện ở vị trí %d trong mảng.\n", target, i);
            found = 1;
        }
    }

    if (!found) {
        printf("Số %d không xuất hiện trong mảng.\n", target);
    }

    return 0;
}