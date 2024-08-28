#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
    char *ten;
    int maso;
    float diemso;
}sinhvien;
int main()
{
    sinhvien sv;
    sv.ten = (char*)malloc(sizeof(char) * 50);
    strcpy(sv.ten, "Bach Dinh Hien");
    printf("size: %zu", strlen(sv.ten));

    sv.maso = 2000;
    sv.diemso = 8.9;
    printf("\nmaso sv: %d\n", sv.maso);
    printf("Ten sv: %s\n", sv.ten);
    printf("Diemso sv: %.2f", sv.diemso);

    free(sv.ten);
    return 1;
}
