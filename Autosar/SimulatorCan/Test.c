#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h> // Cần cho rand()
#include <time.h>   // Cần cho srand()
#include <windows.h> // Cần cho Sleep
#include <string.h>

#define E_OK 1
#define NOT_OK 0
// #define ENABLED_DEBUG

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

typedef uint16_t PduLengthType;
typedef struct {
    uint8_t *SduDataPtr;			// payload
    PduLengthType SduLength;	// length of SDU
    uint32_t id;
} PduInfoType;

typedef struct {
    uint32_t hrh;
    uint32_t hth;
} hoh;


void CanIf_RxIndication(hoh Mailbox, PduInfoType *PduInfoPtr);
void CanIf_TxTransmit(hoh Mailbox, PduInfoType *PduInfoPtr);
void CanIf_TxConfirmation(hoh Mailbox, PduInfoType *PduInfoPtr);

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
    PduInfoType PduInfor;
    static hoh pdInfor_ID_to_CanIf;

    pdInfor_ID_to_CanIf.hrh = 1;

    if (can_driver->rx_mailbox >= 16) {
        printf("Mailbox full! Message lost starting with ID=0x%X.\n", simulated_message->id);
        
        // Add a dot after "lost"
        printf("Clearing mailbox and waiting 5 seconds...\n");

        // Reset all mailboxes' status to false
        for (int i = 0; i < 16; i++) {
            can_controller->mailbox[i].status = false;
        }

        // Reset rx_mailbox index
        can_driver->rx_mailbox = 0;

        delay_ms(5000);
        return;
    }

    if (simulated_status) {
        rx_mailbox->message = *simulated_message;
        rx_mailbox->status = E_OK;

        printf("Simulated message received [%llu]: ID=0x%X, DLC=%llu, Data = ", 
               can_driver->rx_mailbox + 1, simulated_message->id, simulated_message->dlc);
        for (int j = 0; j < 8; j++) {
            printf("%02X ", simulated_message->data[j]);
        }
        printf("\n");
        
        PduInfor.SduDataPtr = simulated_message->data;
        PduInfor.SduLength = simulated_message->dlc;
        PduInfor.id = simulated_message->id;

        // pdInfor_ID_to_CanIf is different with CanId from Can 
        pdInfor_ID_to_CanIf.hrh++;

        if (pdInfor_ID_to_CanIf.hrh > 16){
            pdInfor_ID_to_CanIf.hrh = 1;
        }

        CanIf_RxIndication(pdInfor_ID_to_CanIf, &PduInfor);

        can_driver->rx_mailbox++;
    }
}


can_message_t originalMessages[16];
void can_write(can_driver_t *can_driver, can_message_t *simulated_message, bool simulated_status) {
    can_controller_t *can_controller = can_driver->can_controller;
    can_mailbox_t *tx_mailbox = &can_controller->mailbox[can_driver->tx_mailbox];
    PduInfoType PduInfor;
    static hoh pdInfor_ID_to_CanIf;
    pdInfor_ID_to_CanIf.hth = 1;

    if (can_driver->tx_mailbox >= 16) {
        printf("Mailbox full! Message lost starting with ID=0x%X.\n", simulated_message->id);
        printf("Clearing mailbox and waiting 5 seconds...\n");

        // Reset all mailboxes' status to false
        for (int i = 0; i < 16; i++) {
            can_controller->mailbox[i].status = false;
        }

        // Reset tx_mailbox index
        can_driver->tx_mailbox = 0;

        delay_ms(5000);
        return;
    }

    if (simulated_status) {
        tx_mailbox->message = *simulated_message;
        tx_mailbox->status = E_OK;

        printf("Sent messages to Bus [%llu]: ID=0x%X, DLC=%llu, Data = ", 
               can_driver->tx_mailbox + 1, simulated_message->id, simulated_message->dlc);
        for (int j = 0; j < 8; j++) {
            printf("%02X ", simulated_message->data[j]);
        }
        printf("\n");


        PduInfor.SduDataPtr = simulated_message->data;
        PduInfor.SduLength = simulated_message->dlc;
        PduInfor.id = simulated_message->id;

        // pdInfor_ID_from_CanIf is different with Can 
        pdInfor_ID_to_CanIf.hth++;

        if (pdInfor_ID_to_CanIf.hth > 16){
            pdInfor_ID_to_CanIf.hth = 1;
        }
        
        // Lưu trữ dữ liệu gốc được gửi từ CanDrv
        for (int i = 0; i < 16; i++) {
            if (originalMessages[i].id == 0) {
                originalMessages[i] = *simulated_message;
                break;
            }
        }
        CanIf_TxTransmit(pdInfor_ID_to_CanIf, &PduInfor);

        CanIf_TxConfirmation(pdInfor_ID_to_CanIf, &PduInfor);

        can_driver->tx_mailbox++;
    }
}



// Hàm tạo message giả lập ngẫu nhiên Rx
can_message_t generate_random_message_Rx() {
    can_message_t message;
    message.id = 0x600 + (rand() % 49); // Random ID từ 0x600 đến 0x649
    message.dlc = 8;                     // Cố định DLC là 8 byte
    for (int i = 0; i < 8; i++) {
        message.data[i] = rand() % 256;  // Random từng byte trong khoảng 0x00 - 0xFF
    }
    return message;
}

// Hàm tạo message giả lập ngẫu nhiên TX
// Hàm tạo message giả lập ngẫu nhiên TX
can_message_t generate_random_message_TX() {
    can_message_t message;
    static uint8_t MAX1FrameTx; 
    message.id = 0x650 + (rand() % 100); // Random ID từ 0x650 đến 0x6FF
    message.dlc = 8;                     // Cố định DLC là 8 byte
    MAX1FrameTx = rand() % 10; // Random 10 để simulator for hàm CanIf_TxConfirmation
    for (int i = 0; i < MAX1FrameTx; i++) {
        message.data[i] = rand() % 256;  // Random từng byte trong khoảng 0x00 - 0xFF
    }
    return message;
}

// Rx
void can_receive_multiple_messages_from_Bus(can_driver_t *can_driver, uint32_t num_messages) {
    uint8_t num_messages_lost;

    printf("Number of messages received: %d\n", num_messages);

    if (num_messages > 16){
        num_messages_lost = num_messages - 16;
        printf("Number of messages lost: %d\n", num_messages_lost);
    } else {
        num_messages_lost = 0; // No lost messages
    }

    // Flag to track if mailbox has been cleared
    bool mailbox_cleared = false;

    // Receive multiple random messages
    for (int i = 0; i < num_messages; i++) {
        can_message_t random_message = generate_random_message_Rx();
        bool simulated_status = E_OK;

        // If mailbox has been cleared, stop processing more messages
        if (mailbox_cleared) {
            break;
        }

        // Call can_read to simulate receiving the message
        can_read(can_driver, &random_message, simulated_status);

        // Check if we've hit the mailbox limit
        if (can_driver->rx_mailbox == 0 && i >= 16) {
            mailbox_cleared = true;
        }

        // Add a short delay between receiving messages
        delay_ms(500);
    }

    // After receiving, reset the rx_mailbox index to start fresh for the next cycle
    can_driver->rx_mailbox = 0;
    printf("RX mailbox cleared for next message send cycle.\n");
}


// Tx
void can_send_multiple_messages_to_Bus(can_driver_t *can_driver, uint32_t num_messages) {
uint8_t num_messages_lost;

    printf("Number of messages sent: %d\n", num_messages);

    if (num_messages > 16){
        num_messages_lost = num_messages - 16;
        printf("Number of messages lost: %d\n", num_messages_lost);
    } else {
        num_messages_lost = 0; // No lost messages
    }

    // Flag to track if mailbox has been cleared
    bool mailbox_cleared = false;

    // Send multiple random messages
    for (int i = 0; i < num_messages; i++) {
        can_message_t random_message = generate_random_message_TX();
        bool simulated_status = E_OK;

        // If mailbox has been cleared, stop processing more messages
        if (mailbox_cleared) {
            break;
        }

        // Call can_write to simulate receiving the message
        can_write(can_driver, &random_message, simulated_status);

        // Check if we've hit the mailbox limit
        if (can_driver->rx_mailbox == 0 && i >= 16) {
            mailbox_cleared = true;
        }

        // Add a short delay between sending messages
        delay_ms(500);
    }

    // After sending, reset the tx_mailbox index to start fresh for the next cycle
    can_driver->tx_mailbox = 0;
    printf("TX mailbox cleared for next message send cycle.\n");
}


void CanIf_RxIndication(hoh Mailbox, PduInfoType *PduInfoPtr){
    uint32_t canid = Mailbox.hrh;
    uint8_t *canSduPtr = PduInfoPtr->SduDataPtr;
    uint8_t canDlc = PduInfoPtr->SduLength;

#if defined ENABLED_DEBUG
    printf("===== CanIf_RxIndication =====\n");
    printf("Received message on CAN controller ID: %d\n", canid);
    printf("DLC: %u, Data: ", canDlc);
    for (int i = 0; i < canDlc; i++){
        printf("%02X ", canSduPtr[i]);
    }
    printf("\n");
#endif
}

void CanIf_TxTransmit(hoh Mailbox, PduInfoType *PduInfoPtr){
    uint32_t canid = Mailbox.hth;
    uint8_t *canSduPtr = PduInfoPtr->SduDataPtr;
    uint8_t canDlc = PduInfoPtr->SduLength;

#if defined ENABLED_DEBUG
    printf("===== CanIf_TxTransmit =====\n");
    printf("Sent message to CAN controller: %d\n", canid);
    printf("DLC: %u, Data: ", canDlc);
    for (int i = 0; i < canDlc; i++){
        printf("%02X ", canSduPtr[i]);
    }
    printf("\n");
#endif
}

// Hàm này trả về dữ liệu gốc được gửi từ CanDrv
can_message_t getOriginalMessage(uint32_t canid) {
    // Giả sử bạn có một mảng lưu trữ dữ liệu gốc được gửi từ CanDrv
    can_message_t originalMessages[16];
    // ...

    // Tìm kiếm dữ liệu gốc dựa trên canid
    for (int i = 0; i < 16; i++) {
        if (originalMessages[i].id == canid) {
            return originalMessages[i];
        }
    }

    // Nếu không tìm thấy dữ liệu gốc, trả về một giá trị mặc định
    can_message_t defaultMessage;
    defaultMessage.id = 0;
    defaultMessage.dlc = 0;
    memset(defaultMessage.data, 0, 8);
    return defaultMessage;
}

// Hàm này tính toán checksum của dữ liệu
uint8_t calculateChecksum(uint8_t *data, uint8_t length) {
    uint8_t checksum = 0;
    for (int i = 0; i < length; i++) {
        checksum += data[i];
    }
    return checksum;
}

// Hàm này trả về checksum của dữ liệu gốc
uint8_t getOriginalChecksum(uint32_t canid) {
    can_message_t originalMessage = getOriginalMessage(canid);
    return calculateChecksum(originalMessage.data, originalMessage.dlc);
}

// CanIf->Can to confirm transmission
void CanIf_TxConfirmation(hoh Mailbox, PduInfoType *PduInfoPtr) {
    uint32_t canid = Mailbox.hth;
    uint8_t *canSduPtr = PduInfoPtr->SduDataPtr;
    uint8_t canDlc = PduInfoPtr->SduLength;

    // So sánh dữ liệu nhận được với dữ liệu gốc
    can_message_t originalMessage = getOriginalMessage(canid); // Hàm này trả về dữ liệu gốc được gửi từ CanDrv
    if (memcmp(originalMessage.data, canSduPtr, canDlc) != 0) {
        printf("Dữ liệu nhận được không khớp với dữ liệu gốc\n");
        return;
    }

    // Kiểm tra độ dài của dữ liệu
    if (canDlc > 8 || canDlc < 0) {
        printf("Độ dài dữ liệu không hợp lệ\n");
        return;
    }

    // Kiểm tra checksum của dữ liệu
    uint8_t checksum = calculateChecksum(canSduPtr, canDlc); // Hàm này tính toán checksum của dữ liệu
    if (checksum != getOriginalChecksum(canid)) { // Hàm này trả về checksum của dữ liệu gốc
        printf("Checksum của dữ liệu nhận được không khớp với checksum của dữ liệu gốc\n");
        return;
    }

    #if defined ENABLED_DEBUG
        printf("===== CanIf_TxConfirmation =====\n");
        printf("Transmission confirmed for CAN controller: %d\n", canid);
        printf("DLC: %u, Data: ", canDlc);
        for (int i = 0; i < canDlc; i++){
            printf("%02X ", canSduPtr[i]);
        }
        printf("\n");
    #endif
}

// Main
int main() {
    // Sở dĩ không bị confict là bởi vì trước đó đã cấp 1 vùng nhớ tỉnh cho controller
    can_controller_t controller;
    can_driver_t driver;
    driver.can_controller = &controller;
    uint8_t num_messages_Tx, num_messages_Rx;

    can_driver_init(&driver);

    printf("CanController ID: %d\n", controller.cantrollerID);
    printf("Base address: 0x%x\n", controller.base_address);
    printf("Baud rate: %u Kbps\n", controller.baud_rate);
    printf("Filter mask: 0x%x\n", controller.filterMask);

    srand(time(NULL)); // Khởi tạo seed cho rand()

    bool simulated_status = E_OK;

    while (true) {

        printf("===================================\n");
        printf("                 RX                \n");
        printf("===================================\n");
        num_messages_Rx = rand() % 30; // Random từ 0 đến 29 Tx
        can_receive_multiple_messages_from_Bus(&driver, num_messages_Rx);
        delay_ms(5000); // 5s để xem được Rx. Trong thực tế thời gian này là rất nhanh


        printf("===================================\n");
        printf("                 TX                \n");
        printf("===================================\n");
        num_messages_Tx = rand() % 25; // Random từ 0 đến 24 Tx
        can_send_multiple_messages_to_Bus(&driver, num_messages_Tx);
        delay_ms(5000); // 5s để xem được Rx. Trong thực tế thời gian này là rất nhanh
    }

    return 0;
}


