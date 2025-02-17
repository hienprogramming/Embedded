#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define FIFO_SIZE 10  // Kích thước buffer

typedef struct {
    uint8_t buffer[FIFO_SIZE];
    uint16_t head;    // Vị trí đọc
    uint16_t tail;    // Vị trí ghi
    uint16_t count;   // Số phần tử hiện có trong buffer (optional)
} FIFO_TypeDef;

FIFO_TypeDef fifo;

void FIFO_Init(FIFO_TypeDef *f) {
    f->head = 0;
    f->tail = 0;
    f->count = 0;
}

bool FIFO_IsEmpty(FIFO_TypeDef *f) {
    return (f->head == f->tail && f->count == 0); // Hoặc return (f->count == 0);
}

bool FIFO_IsFull(FIFO_TypeDef *f) {
    return (f->head == f->tail && f->count == FIFO_SIZE); // Hoặc return (f->count == FIFO_SIZE);
}

// Hàm thêm phần tử vào FIFO (Enqueue)
bool FIFO_Enqueue(FIFO_TypeDef *f, uint8_t data) {
    if (FIFO_IsFull(f)) {
        return false; // FIFO đầy, không thể thêm
    }

    f->buffer[f->tail] = data;
    f->tail = (f->tail + 1) % FIFO_SIZE; // Di chuyển tail theo vòng tròn
    f->count++;
    return true;
}

// Hàm lấy phần tử khỏi FIFO (Dequeue)
bool FIFO_Dequeue(FIFO_TypeDef *f, uint8_t *data) {
    if (FIFO_IsEmpty(f)) {
        return false; // FIFO rỗng, không thể lấy
    }

    *data = f->buffer[f->head];
    f->head = (f->head + 1) % FIFO_SIZE; // Di chuyển head theo vòng tròn
    f->count--;
    return true;
}

/*Code trên triển khai FIFO dạng circular buffer, phù hợp cho các ứng dụng embedded 
như truyền thông UART, SPI, quản lý task, hoặc xử lý dữ liệu cảm biến. Tùy vào yêu 
cầu cụ thể, bạn có thể điều chỉnh kích thước buffer, kiểu dữ liệu, hoặc thêm các 
tính năng như timeout, xử lý lỗi.*/

int main() {
    FIFO_Init(&fifo); // Khởi tạo FIFO

    // Thêm phần tử vào FIFO
    for (uint8_t i = 0; i < FIFO_SIZE; i++) {
        if (FIFO_Enqueue(&fifo, i)) {
            printf("Da them %d vao FIFO\n", i);
        } else {
            printf("FIFO da day, khong the them %d\n", i);
        }
    }

    if (FIFO_Enqueue(&fifo, 20)) {
        printf("Da them thanh cong so 20 vao FIFO\n");
    } else {
        printf("FIFO da day, khong the them so 20\n");
    }
    
    if (FIFO_Enqueue(&fifo, 21)) {
        printf("Da them thanh cong so 21 vao FIFO\n"); 
    } else {
        printf("FIFO da day, khong the them so 21\n");
    }
    
    // Lấy phần tử từ FIFO
    uint8_t data;
    uint8_t tempArray[FIFO_SIZE];
    int tempCount = 0;

    // Lấy và lưu tất cả phần tử vào mảng tạm
    while (!FIFO_IsEmpty(&fifo)) {
        // if (FIFO_Dequeue(&fifo, &data)) {
        //     printf("Da lay %d ra khoi FIFO\n", data);
        FIFO_Dequeue(&fifo, &data);
        if (data != 3) { // Bỏ qua phần tử số 3
            tempArray[tempCount++] = data;
        }
    }

    // Thêm lại các phần tử (trừ số 3) vào FIFO
    for (int i = 0; i < tempCount; i++) {
        FIFO_Enqueue(&fifo, tempArray[i]);
    }

    // In ra các phần tử sau khi xóa số 3
    printf("\nCac phan tu sau khi xoa so 3:\n");
    while (!FIFO_IsEmpty(&fifo)) {
        if (FIFO_Dequeue(&fifo, &data)) {
            printf("Phan tu: %d\n", data);
        }
    }

    return 0;
}