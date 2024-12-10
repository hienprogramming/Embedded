// CanIf_RxIndication implementation
void CanIf_RxIndication(can_controller_t *Mailbox, PduInfoType *PduInfoPtr) {
    uint32_t canId = Mailbox->cantrollerID;
    uint8_t *canSduPtr = PduInfoPtr->SduDataPtr;
    uint8_t canDlc = PduInfoPtr->SduLength;

    printf("=== CanIf_RxIndication ===\n");
    printf("Received message on CAN controller ID: %u\n", canId);
    printf("DLC: %u, Data: ", canDlc);

    for (uint8_t i = 0; i < canDlc; i++) {
        printf("%02X ", canSduPtr[i]);
    }
    printf("\n");
}

// CAN read function
void can_read(can_driver_t *can_driver, can_message_t *simulated_message, bool simulated_status) {
    can_controller_t *can_controller = can_driver->can_controller;
    can_mailbox_t *rx_mailbox = &can_controller->mailbox[can_driver->rx_mailbox];

    if (can_driver->rx_mailbox >= 16) {
        printf("Mailbox full! Message lost starting with ID=0x%X.\n", simulated_message->id);
        printf("Clearing mailbox and waiting 5 seconds...\n");

        for (int i = 0; i < 16; i++) {
            can_controller->mailbox[i].status = false;
        }

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

        PduInfoType pduInfo;
        pduInfo.SduDataPtr = simulated_message->data;
        pduInfo.SduLength = simulated_message->dlc;

        CanIf_RxIndication(can_controller, &pduInfo);

        can_driver->rx_mailbox++;
    }
}