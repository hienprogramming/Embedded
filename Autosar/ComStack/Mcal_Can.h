#ifndef MCAL_CAN_H
#define MCAL_CAN_H

// Định nghĩa kiểu dữ liệu cơ bản
typedef unsigned char uint8;
typedef unsigned short uint16;

// Cấu trúc thông tin PDU (Protocol Data Unit)
// Dùng chung cho các lớp
typedef struct {
    uint8* SduDataPtr; // Con trỏ tới buffer dữ liệu
    uint8 SduLength;   // Độ dài dữ liệu (DLC)
} PduInfoType;

// Khai báo hàm
void Mcal_Can_Write(uint16 CanId, const PduInfoType* PduInfoPtr);
void Mcal_Can_SimulateRx();

#endif // MCAL_CAN_H