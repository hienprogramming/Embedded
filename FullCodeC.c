#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
    uint32_t bit_28th: 29; // 0-28
    uint32_t bit_29th: 1;  // bit 29
    uint32_t bit_30_31th: 2; // bit 30 and 31
}PFC_Type;

typedef struct 
{
    uint32_t arr[64];  // Need to padding 256byte
    volatile PFC_Type PFC;  // 0x50000100
}PCC_TYPE;

#define PCC_REG ((volatile PCC_TYPE *)0x50000000)

/*
  EXAMPLE 2 CORRECTLY:
  Reg1: PCC: Add: 0x50000000
  Reg2: PRC: Add: 0x50000080
  Reg3: PKC: Add: 0x50000084
  Reg4: PLC: Add: 0x50000090
  Reg5: PFC: Add: 0x50000100
  1. Only Reg1 can access to Reg2, Reg3, Reg4, Reg5
  2. MicroController 32 bits
  *** In Reg5 turn on bit 29th
*/
void PFC_TurnOn_Bit29th()
{
    PCC_REG->PFC.bit_29th=0x01;
    printf("PFC Bit 29: %u\n", PCC_REG->PFC.bit_29th);
}


/*
  EXAMPLE 1. Read, write data to 0x5000
*/
void read_write_data() {
    int data = 10;
    volatile int *ptr = (volatile int *)0x5000;
    printf("Data in 0x5000: %d\n", *ptr);
    *ptr = data;
    printf("Data after writing to 0x5000: %d\n", *ptr);
}


/*
  EXAMPLE 3: Swap data with pointer
*/

void Swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
    printf("The value a after swaping: %d\n", *a);
    printf("The value b after swaping: %d\n", *b);
}

/*
Example 4: Function pointer
*/
void Sum(int a, int b)
{
    int sumof = a + b;
    printf("Sumof 2 number: %d", sumof);
    return sumof;
}

/*
  EXAMPLE 5. Enter number from screen, and find the number midle. Only using pointer.
*/
#define NUMBER 10
void find_midle_pointer()
{
    uint32_t arr[NUMBER];
    uint32_t *prt = &arr[0];
    static uint32_t index, index1, index2 = 0;
    for (int i = 0; i <= NUMBER; i++)
    {
        scanf("%d", &prt);
        *(prt+i);
    }
    if ((NUMBER % 2 == 0) & (NUMBER != 0)){
        index = NUMBER / 2;
        printf("Only one index: %d", index);
    }
    else if ((NUMBER % 2 != 0) & (NUMBER != 0)){
        index1 = (NUMBER / 2) + 1;
        printf("\nIndex1: %d", index1);
        index2 = (NUMBER / 2) - 1;
        printf("\nIndex2: %d", index1);
    }
}

/*
    EXAMPLE 6. Malloc/Calloc and Pointer like Array.
    Pointer_Like_Array_Malloc() -> Code in VS, not using in the real task. Because embedded don't use dynamic memory.
    - Enter n and then print to screen address and value of them. Only using pointer, no using arr.
*/
void find_middle_number(int n)
{
    // Khai báo mảng với kích thước tối đa
    uint32_t arr[100]; 

    printf("Enter the number of elements (<= 100): ");
    scanf("%d", &n);

    printf("Enter the numbers:\n");
    for (int i = 0; i < n; i++) {
        scanf("%u", &arr[i]);
    }

    // Xử lý tìm số ở giữa
    if (n % 2 == 1) {
        printf("Middle number: %u\n", arr[n / 2]);
    } else {
        printf("Middle numbers: %u, %u\n", arr[n / 2 - 1], arr[n / 2]);
    }
}

void Pointer_Like_Array_Malloc()
{
    int n;
    printf("Enter n: ");
    scanf("%d", &n);
    if ( n <= 0){
        printf("Invalid input!!!\n");
        exit(-1);
    }
    uint32_t *arr = (uint32_t *)malloc(n * sizeof(uint32_t));
    if (arr == NULL){
        printf("Memory allocation failed\n");
        exit(-1);
    }

    for (int i = 0; i < n; i++){
        scanf("%d", &arr);
    }
    for (int i = 0; i < n; i++){
        printf("Address of *arr[%d]: %p", (void *)&arr[i]);
        printf("Value of *arr[%d]: %d", arr[i]);
    }

    find_middle_number(n);

    free(arr);

}

void Pointer_Like_Array_Normal()
{
    int arr[5];
    int *prt = arr; 

    printf("Enter the number of arr: \n");
    for (int i = 0; i < 4 ; i++)
    {
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < 4 ; i++)
    {
        printf("Address of arr[%d]: %p\n", i, (prt + i));
        printf("Value of arr[%d]: %d\n", i, *(prt + i));
    }
}

/*
    EXAMPLE 7. The different between pointer is assigned to ARRAY and normal VARIABLE. 

        Câu hỏi 1: Tại sao uint32_t *prt = arr; không có dấu &, nhưng uint32_t *prt = &test; phải có dấu &?
            Tên mảng (arr) trong C tự động được "chuyển đổi" thành địa chỉ của phần tử đầu tiên, nên bạn không cần dùng &.
            Biến thông thường (test) không tự động chuyển đổi thành địa chỉ, nên bạn phải dùng & để lấy địa chỉ của nó khi gán vào con trỏ.

        Câu hỏi 2: %c, %d, %f, %u?
            https://www.geeksforgeeks.org/format-specifiers-in-c/

*/
void Pointer_Is_Assigned_Variable()
{
    uint8_t variable = 10;
    uint8_t *prt = &variable; // Con trỏ kiểu uint8_t để phù hợp với biến
    printf("Value of prt: %u\n", *prt); // Sử dụng %u cho kiểu uint8_t
    printf("Address of variable\n: %p", prt);
    printf("Address of pointer: %p", &prt);
}

void Pointer_Is_Assigned_Array()
{
    uint8_t arr[4]; // Max 4 data in array
    uint8_t *prt = arr; // The first index of array (arr[0])
    printf("Enter 4 numbers: \n");
    for (int i = 0; i < 4; i++){
        scanf("%d", &arr[i]);
    }
    for (int i = 0; i < 4; i++){
        printf("Address of arr[%d]: %p\n", i , (void *)&arr[i]);
        printf("Value of arr[%d]: %d\n", i , arr[i]);
    }
    printf("\nUsing pointer arithmetic:\n");
    for (int i = 0; i < 4; i++){
        printf("Address of pointer[%d]: %p", i, (prt + i));
        printf("Value of pointer[%d]: %d", i, *(prt + i));
    }
}

/*
    EXAMPLE 8. Struct normal and pointer:
                    With struct, each element is stored each different others.
                    -> We can access to other element at the same time.
                    -> Sizeof struct is size of all element in struct.
               Union:
                   Union like struct, but all members are stored in the same location
                   -> Only member in can store data at the same time.
               Ecnum:
                   
*/
typedef struct
{
    uint8_t a;
    uint8_t b;
    uint8_t c;
}Struct_Type;


void Struct_Nornal_And_Pointer()
{
    Struct_Type Normal = {1, 2, 3};
    Struct_Type instance = {7, 8, 9};
    Struct_Type *Pointer_Struct = &instance;

    printf("Size of Struct: %lu bytes\n", sizeof(Struct_Type));
    printf("Size of a: %lu bytes\n", sizeof(Normal.a));

    printf("Normal with a is: %d\n", Normal.a);
    printf("Struct with pointer a is: %d\n", Pointer_Struct->a);
}


union Union_t
{
    uint32_t a;
    uint8_t b;
    uint8_t c;
};


void Union_Nornal_And_Pointer()
{
    union Union_t Normal = {1, 2, 3};
    union Union_t instance = {7, 8, 9};
    union Union_t *Pointer_Struct = &instance;

    printf("Size of union: %lu bytes\n", sizeof(union Union_t));
    printf("Size of a: %lu bytes\n", sizeof(Normal.a));

    printf("Normal with a is: %d\n", Normal.a);
    printf("union with pointer a is: %d\n", Pointer_Struct->a);

}

typedef union 
{
    uint32_t a;
    uint16_t b;
    uint8_t c;
}Union_t;


void def_union_like_struct()
{
    Union_t union_test_normal = {1, 2};
    Union_t instance = {4, 5, 6};
    Union_t *union_test_pointer = &instance;
    
    printf("Size of union_test_normal is: %d bytes\n", sizeof(union_test_normal));
    printf("Size of union_test_pointer is: %d bytes\n", sizeof(union_test_pointer));
    printf("Address of union_test_normal is: %p\n", &union_test_normal);
    printf("Address of instance is: %p\n", &instance);
    printf("Address of instance is: %p\n", union_test_pointer);
    printf("Address of union_test_pointer is: %p\n", &union_test_pointer);
}

enum Value{
    value1, // 0
    value2, // 1
    value3 = 3, // 3
    value4, // 4
    value5, // 5 
};

void Enum_Test()
{
    enum Value value_test;
    value_test = value4;
    printf("Value of 1 is: %d\n", value_test);
}

/*
    EXAMPLE 9. Double pointer
    Find solution about address and value of double pointer.
*/
void def_double_pointer()
{
    uint8_t a = 10;
    uint8_t *prt = &a;
    uint8_t **pprt = &prt;

    printf("Value of a is: %d\n", a);
    printf("Value of *prt is: %d\n", *prt);
    printf("Value of **pprt is: %d\n", **pprt);

    printf("Address of a: %p\n", &a);
    printf("Address of prt to a: %p\n", prt);
    printf("Address of prt: %p\n", &prt);
    printf("Address of pprt to prt: %p\n", pprt);
    printf("Address of pprt: %p\n", &pprt);
}

/*
    EXAMPLE 10. Copy data 
        With strcpy
        Assign data by array
        Sử dụng hàm memcpy từ thư viện <string.h> để sao chép vùng nhớ động (Not emplement):
            strcpy(Dest, Source): string data
            memcpy(Dest, Source): number data
        Copy data by pointer
        Copy data by Argument


*/
typedef struct 
{
    char name[20];
    char ID[20];
    uint8_t point;
}Student_t;

void def_strcpy_source_to_Dest()
{
    char src[] = "def_strcpy_source_to_Dest";
    char Dest[50];

    strcpy(Dest, src); // Copy data from src to Dest

    printf("src: %s\n", Dest);
    printf("Dest: %s\n", Dest);
}

void def_strcpy()
{
    Student_t Student;
    strcpy(Student.name, "HienBach");
    strcpy(Student.ID, "01234");
    Student.point = 9;

    printf("Name of student is: %s\n", Student.name);
    printf("ID of student is: %s\n", Student.ID);
    printf("Point of student is: %c\n", Student.point);

    def_strcpy_source_to_Dest();
}


void Read_Toorque_Sensor_memcpy(uint8_t *TorqueSensor, uint8_t numSenSor)
{
    for (uint8_t i = 0; i < numSenSor; i++){
        TorqueSensor[i] = rand() % 256;
        printf("TorqueSensor[%d]: %d\n", i, TorqueSensor[i]);
    }
}

void assign_data_by_array()
{
    int src[] = {1, 2, 3, 4, 5};
    int dest[5];
    int n = 5;

    for (int i = 0; i < n; i++) {
        dest[i] = src[i]; // Sao chép từng phần tử
    }

    // In kết quả
    for (int i = 0; i < n; i++) {
        printf("%d ", dest[i]);
    }
}


void copy_data_by_pointer()
{
    int a = 10;
    int *p1= &a;
    int *p2;
    p2 = p1;
    printf("Value via p1: %d\n", *p1);
    printf("Value via p2: %d\n", *p2);
}


typedef struct{
    uint8_t a;
    uint8_t b;
}DataType;

void copy_data_by_pointer_struct()
{
    DataType instance = {1, 2};
    DataType *Data = &instance;
    DataType *CopyData;
    CopyData = Data;

    printf("Value a via CopyData: %d\n", CopyData->a);
    printf("Value b via CopyData: %d", CopyData->b);

}

void Copy_Data_By_Argument(int *src, int *dest, int size)
{
    for (int i = 0; i < size; i++){
        dest[i] = src[i]; // Copy address from src to dest
    }
}

void Perform_Copy_Data_By_Argument()
{
    int source[] = {0, 1, 2, 3};
    int size = 4;
    int dest[size];

#define ENABLE 1

#if ENABLE
    Copy_Data_By_Argument(source, dest, size);
    for (int i = 0; i < size; i++){
        printf("%d", dest[i]);
    }
#elif NOT_ENABLE
    // Do nothing in here
#else
    // Do nothing in here
#endif
}


/*
    EXAMPLE 12. Recursive 
*/
int Fibonacci(int n)
{
    if (n < 0){
        exit(-1);
    }
    else if (n == 1 || n == 0){
        return 1;
    }
    else {
        return Fibonacci(n - 1) * n;
    }
}

void recursive_function(int depth) {
  int local_array[1024]; // Khai báo mảng lớn trong hàm đệ quy

  printf("Depth: %d\n", depth);

  if (depth < 10) {
    recursive_function(depth + 1);
  }
}

/*
    EXAMPLE 13. Array 
*/

// Must to pointer for *a and *b. If not, we can not swap correctly.
void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void arrage_ascending(int array[], int size)
{
    for (int i = 0; i < size; i++){
        for (int j = i+1; j < size; j++){
            if (array[i] > array[j]){
                swap(&array[i], &array[j]);

            }
        }
    }
}

void arrage_descending(int array[], int size)
{
    for (int i = 0; i < size; i++){
        for (int j = i+1; j < size; j++){
            if (array[i] < array[j]){
                swap(&array[i], &array[j]);
            }
        }
    }
}

void Display_Array()
{
    int array[] = {0, 3, 2, 5, 4};
    int sizeofarray = sizeof(array) / sizeof(array[0]);

    printf("arrage_ascending:\n");
    arrage_ascending(array, sizeofarray);
    for (int i = 0; i < sizeofarray; i++) {
        printf("Arr[%d] = %d\n", i, array[i]);
    }

    printf("arrage_descending:\n");
    arrage_descending(array, sizeofarray);
    for (int i = 0; i < sizeofarray; i++) {
        printf("Arr[%d] = %d\n", i, array[i]);
    }    
}

/*
    EXAMPLE 14. Len Of string 
*/
void len_string()
{
    char name[] = "Bach Dinh Hien";
    printf("Lengh of string: %d", strlen(name));
}

/*
    EXAMPLE 15. C embedded, turin on, clear specific bit
*/
void Clear_SpecificBit_Special(uint32_t num, uint8_t pos)
{
    num = 15;
    uint32_t mask = ~(1 << pos);
    printf("Value num before clear bit %dth: %d\n", pos, num);
    num &= mask;
    printf("Value num after clear bit %dth: %d", pos, num);
}

void TurnOn_SpecificBit_Special(uint32_t num, uint8_t pos)
{
    uint32_t mask = (1 << pos);
    printf("Value num before clear bit %dth: %d\n", pos, num);
    num |= mask;
    printf("Value num after clear bit %dth: %d", pos, num);
}


void turnon_4bits()
{
    uint32_t register1;
    // Turn on the first of 4 bit
    register1 |= 0x0f;
}

void clear_4bits()
{
    uint32_t register1;
    // Turn on the first of 3 bit
    // Example register1 is: 0x00FA0
    register1 &= 0x000A;
}


// clear bit 3th
void clear_3thbit()
{
    uint32_t register1;
    // Turn on the first of 3 bit
    // Example register1 is: 0x00FA0
    register1 &= 0x00f2;
}

void Access_Bit()
{
    turnon_4bits();
    clear_4bits();
    clear_3thbit();

}

/*
    EXAMPLE 16. Write value directly to specific address. (see more example 1 and example 2)
    And simulate process to access register in Window (Vscode)
*/
void Accsess_Register_method1(int value)
{
    // Wrire value to 0x2000, chip 32bits
    *(volatile uint32_t *)0x2000 = value;
}


void Accsess_Register_method2(uint32_t value)
{
    // Write value to 0x2000
    // Create one pointer have value 0x2000 with volatile
    uint32_t *prt = (volatile uint32_t *)0x2000;
    *prt = value;
}

void Accsess_Register_Vitualization()
{
    uint32_t temp;
    uint32_t *prt = &temp;
    printf("Address prt via temp: %p\n", prt);

    *(volatile uint32_t *)prt = 10; 

    printf("Value of temp is: %d\n", temp);
    printf("Value of prt via temp is: %d\n", *prt);
}

#define I2C3_MSA_R  (*(volatile uint32_t *)0x00003)


void Show_Result_Accsess_Register()
{
    I2C3_MSA_R = 100;
    Accsess_Register_method1(5);
    Accsess_Register_method2(100);
    Accsess_Register_Vitualization();
}

/*
    EXAMPLE 17. Static and global VARIABLE
*/
int global_var = 10;
static int static_var = 10;

void function1()
{
    int local_var = 10;
    static int local_var_static = 10;
    printf("global_var co gia tri: %d\n", global_var);
    printf("static_var co gia tri: %d\n", static_var);
    printf("local_var co gia tri: %d\n", local_var);
    printf("local_var_static co gia tri: %d\n", local_var_static);

    global_var++;
    static_var++;
    local_var++;
    local_var_static++;
}

void function2()
{
    int local_var = 10;
    static int local_var_static = 10;
    printf("global_var co gia tri: %d\n", global_var);
    printf("static_var co gia tri: %d\n", static_var);
    printf("local_var co gia tri: %d\n", local_var);
    printf("local_var_static co gia tri: %d\n", local_var_static);

    global_var++;
    static_var++;
    local_var++;
    local_var_static++;
}

/*
    EXAMPLE 18. Ternary operator
    |--------------------------------------|
    |condition ? expression1 : expression2 |
    |--------------------------------------|
    return (*a > *b) ? (*a + *b) : (*b - *a);
*/

uint8_t Ternary_Operator(uint8_t *a, uint8_t *b)
{
    return (*a > *b) ? (*a + *b) : (*b - *a);
}


/*
    EXAMPLE 19. StorageClassesInC
    Storage Classes In C
    1. auto
    2. extern
    3. static
    4. register
*/

// Biến toàn cục (global variable) - thuộc data segment
uint8_t global_variable = 100;

// Hàm minh họa auto (mặc định là auto)
void auto_test() {
    uint8_t auto_var = 10; // Biến auto nằm trên stack
    auto_var += 10;
    printf("Auto_Var: %d\n", auto_var);
}

// Hàm minh họa extern
void extern_test() {
    extern uint8_t global_variable; // Tham chiếu đến biến toàn cục
    global_variable += 10;
    printf("Global_Variable (Extern): %d\n", global_variable);
}

// Hàm minh họa static
void static_test() {
    static uint8_t static_variable = 0; // Biến static giữ giá trị qua các lần gọi
    static_variable += 10;
    printf("Static_Variable: %d\n", static_variable);
}

// Hàm minh họa register
void register_test() {
    register uint8_t register_variable = 0; // Khuyến nghị lưu trong thanh ghi
    register_variable += 10;
    printf("Register_Variable: %d\n", register_variable);
}

void DisPlay_StorageClassesInC()
{
    printf("Testing auto:\n");
    auto_test();
    auto_test();

    printf("\nTesting extern:\n");
    extern_test();
    extern_test();

    printf("\nTesting static:\n");
    static_test();
    static_test();

    printf("\nTesting register:\n");
    register_test();
    register_test();

}

int main() {
    /*Example 1*/
    read_write_data();

    /*Example 2*/
    PFC_TurnOn_Bit29th();

    /*Example 3*/
    int a = 1, b = 10;
    int *num1 = &a;  // If not initialize for poiter -> compiler will notice error
    int *num2 = &b;
    printf("The value a before swaping: %d\n", *num1);
    printf("The value b before swaping: %d\n", *num2);
    Swap(num1, num2);

    /*Example 4*/
    // Initialize for function pointer
    int (*function_pointer)(int, int) = &Sum;  // It should be to show kind of pointer.
    // int (*function_pointer)(int, int) = Sum; // It's ok also.
    function_pointer(a, b);

    /*Example 6*/
    Pointer_Like_Array_Malloc();
    Pointer_Like_Array_Normal(); // Need to see

    /*Example 7*/
    Pointer_Is_Assigned_Variable();
    Pointer_Is_Assigned_Array();

    /*Example 8*/
    Struct_Nornal_And_Pointer();
    Union_Nornal_And_Pointer();
    def_union_like_struct();
    Enum_Test();

    /*Example 9*/
    def_double_pointer();

    /*Example 10*/
    def_strcpy();
    copy_data_by_pointer();
    copy_data_by_pointer_struct();
    Perform_Copy_Data_By_Argument();

    uint8_t numSenSorEps = 8;
    uint8_t SenSor_Eps[numSenSorEps]; 
    uint8_t copydataSenSor[numSenSorEps];
    Read_Toorque_Sensor_memcpy(SenSor_Eps, numSenSorEps);  // don't have &SenSor_Eps, because we are pointing to SenSor_Eps[0]
    memcpy(copydataSenSor, SenSor_Eps, numSenSorEps);
    for (uint8_t i = 0; i < numSenSorEps; i++){
        printf("copydataSenSor[%d]: %d\n", i, copydataSenSor[i]);
    }

    /*Example 11*/
    Fibonacci(10);
    int Recursive = Fibonacci(10);
    printf("Recursive is: %d", Recursive);
    recursive_function(0);

    /*Example 13*/
    Display_Array();

    /*Example 14*/
    len_string();

    /*Example 15*/
    Access_Bit();
    Clear_SpecificBit_Special(15, 2);
    TurnOn_SpecificBit_Special(8, 2);

    /*Example 16*/
    Show_Result_Accsess_Register();

    /*Example 17*/
    printf("Function1\n");
    function1();
    printf("Function1+1\n");
    function1();
    printf("Function2\n");
    function2();
    printf("Function2+2\n");
    function2();


    /*Example 18*/
    uint8_t a = 5, b = 4;
    uint8_t value = Ternary_Operator(&a, &b);
    printf("value is: %d", value);

    /*Example 19*/
    DisPlay_StorageClassesInC();

    return 0;
}

