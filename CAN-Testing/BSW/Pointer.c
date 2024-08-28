// Truyền mảng lớn
// Thay đổi nội dung mảng   
#include<stdio.h>
#include<string.h>
typedef struct{
    int ID;
    char name[50];
}Student;

// Truyền mảng lớn
void manglon(int *arr, int size){
    for(int i = 0; i < sizeof(size); i++){
        printf("%d", arr[i]);
    }
}

// Thay đổi nội dung mảng   
void thaydoinoidungmang(Student *student, int newID){ //update student
    student->ID = newID;
    strcpy(student->name, "Bach");
}
int main()
{
    int array[] = {0,1,2,3,4,5};
    // printf("%d",sizeof(array)/sizeof(array[0]));
    manglon(array, sizeof(array)/sizeof(array[0]));
    
    Student st;
    // st.name = "Hien"; // Không thể được vì chuổi đó được hiểu là 1 con trỏ hằng, nên không thể gán trực tiếp như các kiểu khác được
    strcpy(st.name, "Hien");

    // After updated
    thaydoinoidungmang(&st, 2);
    printf("ID: %d, Name: %s\n", st.ID, st.name);
}