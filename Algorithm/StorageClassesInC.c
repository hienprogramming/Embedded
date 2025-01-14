#include <stdio.h>
#include <stdint.h>
/*
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

    DisPlay_StorageClassesInC();
    return 0;
}
