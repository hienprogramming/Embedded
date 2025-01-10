/*
struct data, isvalid?
if data is invalid -> write memmory available before and notice for the system hex value


*/

#include<stdio.h>
#include<stdbool.h>
#include <stdlib.h>

#define ERROR_REGISTER_ADDR 0x54758475
#define MAX 100
typedef unsigned int       uint32_t;
typedef struct{
    int data;
    bool isvalid;
    int EventID;
}DataPacket;

DataPacket g_datapacket;
static bool isDataSent = false;
void send_data(int data)
{
    if (data < 0 || data > 100){
        // Write hex data to manage from UDS request
        // *(volatile uint32_t*)ERROR_REGISTER_ADDR = 0x0ffff; // commented to get the value because can't perform when using address
        g_datapacket.isvalid = false;
        isDataSent = false;
    }
    else {
        g_datapacket.data = data;
        g_datapacket.isvalid = true;
        isDataSent = true;
    }
}

DataPacket Receive_Data()
{
    return g_datapacket;
}

int Temporary_from_Sensor(uint32_t datasensor)
{
    return datasensor;
}

// change data before send to bus for limitation Torque
uint32_t send_data_to_bus(uint32_t addr, uint32_t data)
{
    // return *(volatile uint32_t*)addr = data;
    return data;
}

uint32_t eps_output(uint32_t addr_data, uint32_t data){
    send_data_to_bus(addr_data, data);
}

int main()
{   
    uint32_t data_send[3] = {0x02, 0x0f, 0xff};
    uint32_t torque_eps;
    printf("\n%d", (sizeof(data_send)/sizeof(data_send[0])));
    for (int i = 0; i < (sizeof(data_send)/sizeof(data_send[0])); i++)
    {
        send_data(data_send[i]);
        DataPacket Receive_Data();
        if (isDataSent){
            torque_eps = Temporary_from_Sensor(data_send[i]);
            printf("\nThe data from sensor is ok: %d", data_send[i]);
            eps_output(ERROR_REGISTER_ADDR, torque_eps);
        }
        else { 
            torque_eps = MAX/2; 
            data_send[i] = eps_output(ERROR_REGISTER_ADDR, torque_eps);
            printf("\nThe data from sensor is not ok and Torque is limited: %d", data_send[i]);
        }
    }

    return 0;
}