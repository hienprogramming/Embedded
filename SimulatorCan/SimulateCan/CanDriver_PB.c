


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <windows.h> // Cần cho Sleep

#define E_OK 0
#define NOT_OK 1

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

void can_receive(can_driver_t *can_driver, can_message_t *simulated_message, bool simulated_status) {
    can_controller_t *can_controller = can_driver->can_controller;
    can_mailbox_t *rx_mailbox = &can_controller->mailbox[can_driver->rx_mailbox];

    if (simulated_status) {
        // Ghi thông điệp vào mailbox
        rx_mailbox->message = *simulated_message;
        rx_mailbox->status = true;
        printf("Simulated message received: ID=0x%X, DLC=%llu, Data=", simulated_message->id, simulated_message->dlc);
        // In từng byte của mảng data
        for (int i = 0; i < 8; i++) {
            printf("%02X ", simulated_message->data[i]);
        }
        printf("\n");
    } else if (rx_mailbox->status) {
        // Lấy thông điệp từ mailbox
        printf("Mailbox message read: ID=0x%X, DLC=%llu, Data=", rx_mailbox->message.id, rx_mailbox->message.dlc);
        for (int i = 0; i < 8; i++) {
            printf("%02X ", rx_mailbox->message.data[i]);
        }
        printf("\n");
        rx_mailbox->status = false; // Đánh dấu là đọc xong
    } else {
        printf("No new message in mailbox %llu\n", can_driver->rx_mailbox);
    }
}

// Nhiệm vụ
void task_10_ms() {
    for (int i = 0; i < 10000; i++){

    }
}
void task_20_ms() {
    for (int i = 0; i < 20000; i++){
        
    }
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

    while (true) {
        
        // Chờ cho CAN init xong từ Bus
        task_10_ms();

        // Tạo thông điệp giả lập
        can_message_t simulated_message_mailbox = {
            .id = 0x650,
            .dlc = 8,
            .data = {0xff, 0xfe, 0x03, 0x45, 0x05, 0x06, 0x07, 0x08}
        };
        bool simulated_status = true;

        // for (int i = 0; i < 10; i++) {
            task_10_ms();
            can_receive(&driver, &simulated_message_mailbox, simulated_status);
            printf("Message are received\n");  
            exit(0);
        //     if (i == 9){
        //         exit(0);
        //     }         
        // }        
    }

    return 0;
}


