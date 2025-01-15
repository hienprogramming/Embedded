// C Program to illustrate the 2D array
#include <stdio.h>
#include <stdint.h>
#define rows 3
#define collums 2
#define x 2
#define y 3
#define z 2

void array_2D()
{
    uint8_t arr2D[rows][collums] = { {0, 1}, {2, 3}, {4, 5} };
    printf("Size of arr is: %d bytes\n", sizeof(arr2D)/sizeof(arr2D[0][0]));

    for (uint8_t i = 0; i < rows; i++){
        for (uint8_t j = 0; j < collums; j++){
            printf("arr2D[%d][%d]: %d    ", i, j, arr2D[i][j]);
        }
        printf("\n");
    }
}

void array_3D()
{
    uint8_t arr3D[x][y][z] = { { { 1, 1 }, { 2, 3 }, { 4, 5 } },
                               { { 6, 7 }, { 8, 9 }, { 10, 11 } } };
    printf("Sizeof array 3D: %d bytes\n", sizeof(arr3D)/sizeof(arr3D[0][0][0]));

    for (uint8_t i = 0; i < x; i++){
        for (uint8_t j = 0; j < y; j++){
            for (uint8_t k = 0; k < z; k++){
                printf("arr3D[%d][%d][%d]: %d    ", i, j, k, arr3D[i][j][k]);
            }
            printf("\n");
        }
        printf("\n");
    }
}

int main() {
    // array_2D();
    array_3D();
    return 0;
}
