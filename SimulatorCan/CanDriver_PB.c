#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h> // Cần cho rand()
#include <time.h>   // Cần cho srand()
#include <windows.h> // Cần cho Sleep

#define E_OK 1
#define NOT_OK 0

// Định nghĩa cấu trúc CAN
typedef struct {
    uint32_t id;
    uint64_t dlc;
    uint8_t data[8];
} can_message_t;

typedef struct {
    can_message_t message;
    bool status;
} can_mailbox_t;

typedef struct {
    uint8_t cantrollerID;
    uint32_t base_address;
    uint32_t baud_rate;
    uint32_t filterMask;
    can_mailbox_t mailbox[16];
} can_controller_t;

typedef struct {
    can_controller_t *can_controller;
    uint64_t tx_mailbox;
    uint64_t rx_mailbox;
} can_driver_t;

// Hàm delay
uint32_t get_current_time_ms() {
    return GetTickCount();
}

void delay_ms(int milliseconds) {
    Sleep(milliseconds);
}

// Function này để chờ cho lần tiếp theo khi phát hiện full mailbox
void runtime4full_message() {
    delay_ms(5000);
}

// Các hàm khởi tạo và nhận dữ liệu
void can_driver_init(can_driver_t *can_driver) {
    can_controller_t *can_controller = can_driver->can_controller;
    can_controller->cantrollerID = 0;
    can_controller->base_address = 0xDEADBEEF;
    can_controller->baud_rate = 500000;
    can_controller->filterMask = 0x7ff;

    for (int i = 0; i < 16; i++) {
        can_controller->mailbox[i].status = false;
    }

    can_driver->tx_mailbox = 0;
    can_driver->rx_mailbox = 0;
}

void can_read(can_driver_t *can_driver, can_message_t *simulated_message, bool simulated_status) {
    can_controller_t *can_controller = can_driver->can_controller;
    can_mailbox_t *rx_mailbox = &can_controller->mailbox[can_driver->rx_mailbox];

    if (can_driver->rx_mailbox >= 16) {
        printf("Mailbox full! Message with ID=0x%X is lost.\n", simulated_message->id);
        printf("Clearing mailbox and waiting 5 seconds...\n");

        // Reset all mailboxes' status to false
        for (int i = 0; i < 16; i++) {
            can_controller->mailbox[i].status = false;
        }

        // Reset rx_mailbox index
        can_driver->rx_mailbox = 0;

        delay_ms(5000);
        return; // Bỏ qua xử lý hiện tại để bắt đầu nhận lại từ đầu
    }

    if (simulated_status) {
        // Ghi thông điệp vào mailbox
        rx_mailbox->message = *simulated_message;
        rx_mailbox->status = E_OK;

        printf("Simulated message received [%llu]: ID=0x%X, DLC=%llu, Data = ", can_driver->rx_mailbox + 1, simulated_message->id, simulated_message->dlc);
        for (int j = 0; j < 8; j++) {
            printf("%02X ", simulated_message->data[j]);
        }
        printf("\n");

        can_driver->rx_mailbox++;
    } else {
        printf("No new message RX in mailbox %llu\n", can_driver->rx_mailbox);
    }
}

// Base on can_read to continue
void can_write(can_driver_t *can_driver, can_message_t *simulated_message, bool simulated_status){
    can_controller_t *can_controller = can_driver->can_controller;
    can_mailbox_t *tx_mailbox = &can_controller->mailbox[can_driver->tx_mailbox];
    if (tx_mailbox->status) {
            // Lấy thông điệp từ mailbox
        if (can_driver->rx_mailbox >= 16) {
            printf("Mailbox full! Message with ID=0x%X is lost.\n", simulated_message->id);
            printf("Clearing mailbox and waiting 5 seconds...\n");
            can_driver->tx_mailbox = 0;
            delay_ms(5000);
        }
        can_driver->tx_mailbox++;
        printf("Mailbox message write [%d st/nd]: ID=0x%X, DLC=%llu, Data = ", can_driver->tx_mailbox, tx_mailbox->message.id, tx_mailbox->message.dlc);
        for (int i = 0; i < 8; i++) {
            printf("%02X ", tx_mailbox->message.data[i]);
        }
        printf("\n");
    }
    else{
        printf("No new message TX in mailbox %llu\n", can_driver->tx_mailbox);
    }
}


// Hàm tạo message giả lập ngẫu nhiên
can_message_t generate_random_message() {
    can_message_t message;
    message.id = 0x600 + (rand() % 100); // Random ID từ 0x600 đến 0x6FF
    message.dlc = 8;                     // Cố định DLC là 8 byte
    for (int i = 0; i < 8; i++) {
        message.data[i] = rand() % 256;  // Random từng byte trong khoảng 0x00 - 0xFF
    }
    return message;
}

// Main
int main() {
    can_controller_t controller;
    can_driver_t driver;
    driver.can_controller = &controller;

    can_driver_init(&driver);

    printf("CanController ID: %d\n", controller.cantrollerID);
    printf("Base address: 0x%x\n", controller.base_address);
    printf("Baud rate: %u Kbps\n", controller.baud_rate);
    printf("Filter mask: 0x%x\n", controller.filterMask);

    srand(time(NULL)); // Khởi tạo seed cho rand()

    bool simulated_status = E_OK;

    while (true) {
        can_message_t random_message = generate_random_message();
        can_read(&driver, &random_message, simulated_status);
        delay_ms(500);
    }

    return 0;
}
