#include "stdint.h"

#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H

// Cấu trúc của một CAN message
typedef struct {
    uint32_t id;        // CAN ID
    uint8_t  dlc;       // Data Length Code
    uint8_t  data[8];   // Dữ liệu
} can_message_t;

// Cấu trúc của một CAN mailbox
typedef struct {
    can_message_t message;  // CAN message
    uint8_t       status;   // Trạng thái của mailbox (e.g. empty, full, ...)
} can_mailbox_t;

// Cấu trúc của một CAN controller
typedef struct {
    uint32_t base_address;  // Địa chỉ cơ sở của CAN controller
    uint32_t baud_rate;     // Tốc độ baud của CAN controller
    uint32_t filter_mask;   // Bộ lọc của CAN controller
    can_mailbox_t mailboxes[16];  // Mảng mailbox
} can_controller_t;

// Cấu trúc của một CAN driver
typedef struct {
    can_controller_t *can_controller;  // Con trỏ đến CAN controller
    uint8_t          tx_mailbox;       // Số hiệu của mailbox truyền đi
    uint8_t          rx_mailbox;       // Số hiệu của mailbox nhận
} can_driver_t;

// Hàm khởi tạo CAN driver
void can_driver_init(can_driver_t *can_driver);

// Hàm truyền đi một CAN message
void can_driver_transmit(can_driver_t *can_driver, can_message_t *message);

// Hàm nhận một CAN message
void can_driver_receive(can_driver_t *can_driver, can_message_t *message);

// Hàm đọc trạng thái của một mailbox
uint8_t can_driver_get_mailbox_status(can_driver_t *can_driver, uint8_t mailbox);

// Hàm truyền message lên CANIF
void can_driver_send_to_canif(can_driver_t *can_driver, can_message_t *message);

#endif  // CAN_DRIVER_H