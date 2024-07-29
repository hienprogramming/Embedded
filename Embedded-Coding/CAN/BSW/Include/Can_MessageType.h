// Can_MessageType.h
#ifndef CAN_MESSAGETYPE_H
#define CAN_MESSAGETYPE_H

typedef struct {
    uint32_t id;
    uint8_t data[8];
} Can_MessageType;

#endif // CAN_MESSAGETYPE_H