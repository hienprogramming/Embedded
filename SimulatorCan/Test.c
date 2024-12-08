#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define E_OK 1
#define E_NOT_OK 0
/*
can_driver_t:
    can_controller:
        baudrate
        base_address
    rx_mailbox
    tx_mailbox
*/

typedef struct 
{
    uint8_t can_controller_Id;
    uint32_t baudrate;
    uint64_t *base_address;
}can_controller;


typedef struct 
{
    can_controller *controller;
    uint8_t rx_mailbox;
    uint8_t tx_mailbox;
    bool status_message;
}can_driver_t;


int main()
{
    can_controller controller_variable;
    can_driver_t can_driver;
    can_driver.controller = &controller_variable;
    uint64_t base_address_data = 0x56768687;
    can_driver.controller->base_address = &base_address_data;
    can_driver.controller->baudrate = 500000;
    printf("Baudrate is: %u\n", can_driver.controller->baudrate);
    printf("Base address is: 0x%llx\n", can_driver.controller->base_address);
    printf("Hien Bach Dep Trai\n");
}


