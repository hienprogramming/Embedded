#include <stdint.h>
#include <stdbool.h>

#define STACK_SIZE 10  // Kích thước stack

typedef struct {
    uint8_t buffer[STACK_SIZE];
    uint16_t top;      // Vị trí đỉnh stack
} LIFO_TypeDef;

LIFO_TypeDef lifo;

void LIFO_Init(LIFO_TypeDef *s) {
    s->top = 0;
}

bool LIFO_IsEmpty(LIFO_TypeDef *s) {
    return (s->top == 0);
}


bool LIFO_IsFull(LIFO_TypeDef *s) {
    return (s->top == STACK_SIZE);
}

bool LIFO_Push(LIFO_TypeDef *s, uint8_t data) {
    if (LIFO_IsFull(s)) {
        return false; // Stack đầy, không thể thêm
    }

    s->buffer[s->top] = data;
    s->top++;
    return true;
}

bool LIFO_Pop(LIFO_TypeDef *s, uint8_t *data) {
    if (LIFO_IsEmpty(s)) {
        return false; // Stack rỗng, không thể lấy
    }

    s->top--;
    *data = s->buffer[s->top];
    return true;
}

int main() {
    LIFO_Init(&lifo); // Khởi tạo stack

    // Thêm phần tử vào stack
    for (uint8_t i = 0; i < STACK_SIZE; i++) {
        LIFO_Push(&lifo, i);
    }

    // Lấy phần tử từ stack
    uint8_t data;
    while (!LIFO_IsEmpty(&lifo)) {
        LIFO_Pop(&lifo, &data);
        // Xử lý data...
    }

    return 0;
}