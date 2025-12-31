/*
MASTER:
LinSM_MainFunction
   ↓
LinIf_MainFunction
   ↓
LinIf_ScheduleRequest
   ↓
Lin_SendHeader (Lin Driver)
   ↓
[ Slave phản hồi ]

SLAVE:
Lin_MainFunction
   ↓
Nhận Header
   ↓
So ID
   ↓
Tx / Rx Response

*/
#include "stdio.h"
#include "stdint.h"

#define LIN_FRAME_CMD_ID        0x10
#define LIN_FRAME_STATUS_ID     0x11
#define LIN_FRAME_DATA_ID       0x12
#define E_OK 1
#define E_NOT_OK 0

typedef uint8_t Std_ReturnType;

typedef struct {
    uint8_t frameId;
    uint16_t delayMs;
} LinIf_ScheduleEntryType;

LinIf_ScheduleEntryType LinScheduleTable[] = {
    { LIN_FRAME_CMD_ID,    10 },
    { LIN_FRAME_STATUS_ID, 10 },
    { LIN_FRAME_DATA_ID,   10 }
};

// Master Main Function
void LinIf_MainFunction_Master(void)
{
    static uint8_t scheduleIndex = 0;

    LinIf_ScheduleEntryType *entry = &LinScheduleTable[scheduleIndex];

    /* Gửi Header */
    Lin_SendHeader(0, entry->frameId);

    scheduleIndex++;
    if (scheduleIndex >= 3)
    {
        scheduleIndex = 0;
    }
}

// Master gửi dữ liệu (Frame 0x10)
uint8_t Lin_MasterCmdData[8] = {0x01, 0x02, 0, 0, 0, 0, 0, 0};

Std_ReturnType LinIf_TriggerTransmit(uint8_t frameId, uint8_t *data)
{
    if (frameId == LIN_FRAME_CMD_ID)
    {
        memcpy(data, Lin_MasterCmdData, 8);
        return E_OK;
    }
    return E_NOT_OK;
}

// Code LIN Slave 1 (Trả Status)
// Buffer dữ liệu
uint8_t Lin_Slave1_Status[8] = {0xAA, 0x55, 0, 0, 0, 0, 0, 0};

// TriggerTransmit (Slave1 → Master)
Std_ReturnType LinIf_TriggerTransmit(uint8_t frameId, uint8_t *data)
{
    if (frameId == LIN_FRAME_STATUS_ID)
    {
        memcpy(data, Lin_Slave1_Status, 8);
        return E_OK;
    }
    return E_NOT_OK;
}


// Code LIN Slave 2 (Trả Data)
uint8_t Lin_Slave2_Data[8] = {0x10, 0x20, 0x30, 0, 0, 0, 0, 0};

Std_ReturnType LinIf_TriggerTransmit(uint8_t frameId, uint8_t *data)
{
    if (frameId == LIN_FRAME_DATA_ID)
    {
        memcpy(data, Lin_Slave2_Data, 8);
        return E_OK;
    }
    return E_NOT_OK;
}

// Nhận dữ liệu (Rx Indication – Master)
void LinIf_RxIndication(uint8_t frameId, uint8_t *data)
{
    switch (frameId)
    {
        case LIN_FRAME_STATUS_ID:
            /* xử lý status từ Slave1 */
            break;

        case LIN_FRAME_DATA_ID:
            /* xử lý data từ Slave2 */
            break;

        default:
            break;
    }
}


/* 
Master:
  Header(0x10) → Slave1 nhận RX
  Header(0x11) → Slave1 TX Status
  Header(0x12) → Slave2 TX Data

Slave:
  Nghe Header
  ID match → Tx/Rx
*/