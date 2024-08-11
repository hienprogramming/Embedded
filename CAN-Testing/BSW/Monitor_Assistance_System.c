/*
    Hệ thống cung cấp thông tin MAS - Monitor Assistance System 
    Bao gồm: 
    - Torque > MAX = 7.5 Nm -> ghi data vào MAS với 8 bit
    - Warning Light Canculation là RedOn, YellowOn (NoLight là không có đèn)
        + RedOn là lỗi nặng của hệ thống (Rotor Speed > 50 v/s (Max Rotor Speed), Airbag bi hu)
        + YellowOn lỗi nhẹ (Media bị hư)
        + Nếu hệ thống xảy ra 2 loại đèn thì Warning Light Canculation ưu tiên cái cao nhất
        + 
    Note: Sau thời gian init CAN mới ghi và sẽ ghi một lần cuối cùng khi tắt nguồn để MCU có thể giải quyết các Task khác

*/

// Union, enum, struct, pointer, static, global
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;
typedef signed char sint8;
typedef signed short sint16;
typedef signed long sint32;

#define MAX_TORQUE 7500   // 7.5 Nm 
#define MAX_AIRBAG 1000
#define MAX_ROTORSPEED 50
#define TORQUE_REDUCTION_STEP 100  // Số bước giảm torque
uint8 Limmit_Value;

#define SNA_Airbag_Sensor 65535
#define SNA_Rotor_Sensor 65535

typedef struct
{
    bool isValid;
    uint16 Torque_Sensor;
    bool BSD;
} State_Torque;

typedef struct
{
    bool isValid;
    uint16 Airbag_Sensor;
} State_Airbag;

typedef struct
{
    bool isValid;
    uint16 Rotor_Sensor;
} State_Rotor;

typedef enum{
    NO_LIGHT,
    YELLOW_ON,
    RED_ON
}WLC_State;

typedef struct{
    State_Torque torque;
    State_Airbag airbag;
    State_Rotor rotor;
    WLC_State wlc;
} EPS_Status;

float read_Torque_Sensor(uint16 *Data_Torque)
{
    return (float)(*Data_Torque * 255) / 100.0;
}

float read_Airbag_Sensor(uint16 *Data_Airbag)
{
    return (float)(*Data_Airbag * 100.0);
}


// %d: Dùng để in hoặc đọc giá trị kiểu int (số nguyên có dấu).
// %hu: Dùng để in hoặc đọc giá trị kiểu unsigned short (số nguyên không dấu).
// %hi: Dùng để in hoặc đọc giá trị kiểu signed
sint16 Vitual_Torque_Sensor()
{
    sint16 inputTorque;
    printf("Virtual Torque Sensor: ");
    if (scanf("%hi", &inputTorque) < 0 || inputTorque < 0)
    {
        printf("Invalid inputTorque, Torque is positive value");
        exit(1);
    }
    return inputTorque;
}

sint16 Vitual_Airbag_Sensor()
{
    sint16 inputAirbag;
    printf("Virtual Airbag Sensor: ");
    if (scanf("%hi", &inputAirbag) < 0 || inputAirbag < 0)
    {
        printf("Invalid inputAirbag, Airbag is positive value");
        exit(1);
    }
    return inputAirbag;
}

sint16 Vitual_Rotor_Sensor()
{
    sint16 inputRotor;
    printf("Virtual Rotor Sensor: ");
    if (scanf("%hi", &inputRotor) < 0 || inputRotor < 0)
    {
        printf("Invalid inputRotor, Rotor is positive value");
        exit(1);
    }
    return inputRotor;
}

void Eps_Out(EPS_Status* status) {
    // Giả định rằng chúng ta có một hàm gửi dữ liệu qua CAN
    // Ví dụ: send_can_message(ID, data, length);
    
    // Gửi dữ liệu Torque
    uint8 torque_data[3] = {
        status->torque.isValid,
        (uint8)(status->torque.Torque_Sensor >> 8),
        (uint8)(status->torque.Torque_Sensor & 0xFF)
    };
    send_can_message(0x100, torque_data, 3);
    
    // Gửi dữ liệu Airbag
    uint8 airbag_data[3] = {
        status->airbag.isValid,
        (uint8)(status->airbag.Airbag_Sensor >> 8),
        (uint8)(status->airbag.Airbag_Sensor & 0xFF)
    };
    send_can_message(0x101, airbag_data, 3);
    
    // Gửi dữ liệu Rotor
    uint8 rotor_data[3] = {
        status->rotor.isValid,
        (uint8)(status->rotor.Rotor_Sensor >> 8),
        (uint8)(status->rotor.Rotor_Sensor & 0xFF)
    };
    send_can_message(0x102, rotor_data, 3);
    
    // Gửi dữ liệu WLC
    uint8 wlc_data = (uint8)status->wlc;
    send_can_message(0x103, &wlc_data, 1);
    
    printf("EPS status sent to CAN bus\n");
}
void send_can_message(uint16 id, uint8 *data, uint8 length)
{
    printf("Sending CAN message. ID:0x%X", id);
    for(int i = 0; i < length; i++){
        printf("%02X", data[i]);
    }
    printf("\n");
}

uint16 Limmit_Torque(float Decimal_Torque, State_Torque *state_torque, 
                     State_Airbag *state_Airbag,uint16 Limmit_Value)
{
    Limmit_Value = MAX_TORQUE / 2;
    state_torque->isValid = false;
    state_torque->Torque_Sensor = Limmit_Value;

    state_Airbag->isValid = false;
    state_Airbag->Airbag_Sensor = SNA_Airbag_Sensor;

    // return state_torque;  // Khong return state_torque vi co ban da su dung ptr nen data se cap nhat chinh xac
    return Limmit_Value;
}

void initialize_torque(State_Torque *state_torque)
{
    state_torque->isValid = true;
    state_torque->Torque_Sensor = 0;
}

void delay_ms(uint16 milliseconds)
{
    clock_t start = clock();
    while((clock() - start) * 1000 / CLOCKS_PER_SEC < milliseconds);
}

// Giảm Torque từ từ MAX tới MAX/10 khi hệ thống tay lái bị hư.
// Việc giảm Torque từ từ để hỗ trợ người lái chuyển qua Mode lái tay - BSD
// Việc giảm Torque trong vòng 10s
void Reduce_Torque_Support(uint16 *Torque_Support)
{
    uint16 target = MAX_TORQUE / 10;
    uint16 initial = *Torque_Support;
    uint16 range = initial - target; // 6,750
    
    printf("Starting Torque Support reduction from %d to %d\n", initial, target);
    
    for (int i = 0; i < TORQUE_REDUCTION_STEP; i++)
    {
        if (*Torque_Support > target){
            // Calculate new value based on a non-linear reduction
            *Torque_Support = initial - (range * (i + 1)) / TORQUE_REDUCTION_STEP;
            printf("Reducing Torque Support. Current value: %d\n", *Torque_Support);
            delay_ms(100); // 100 * TORQUE_REDUCTION_STEP = 10s
            
            if (*Torque_Support <= target){
                *Torque_Support = target;
                printf("Torque Support reduction completed. Final value: %d\n", *Torque_Support);
                break;
            }
        }
        else{
            break;
        }
    }
}

void Block_Steering_Detection(uint16 *Torque_Support)
{
    *Torque_Support = 0;
}


// + RedOn là lỗi nặng của hệ thống (Rotor Speed > 50 v/s (Max Rotor Speed), Airbag bi hu)
// + YellowOn lỗi nhẹ (Media bị hư)
// + Nếu hệ thống xảy ra 2 loại đèn thì Warning Light Canculation ưu tiên cái cao nhất
WLC_State WLC_System(float Torque_Value, float Airbag_Value, 
                     uint16 Rotor_Value, bool Media_System_Failure)
{
    WLC_State current_state = NO_LIGHT;

    // Check for severe errors (RED_ON)
    if (Rotor_Value > MAX_ROTORSPEED || Airbag_Value > MAX_AIRBAG)
    {
        current_state = RED_ON;
        printf("WARNING: Severe system error detected!\n");

        if (Rotor_Value > MAX_ROTORSPEED)
        {
            printf("- Rotor Speed exceeds maximum limit (Current: %d, Max: %d)\n", Rotor_Value, MAX_ROTORSPEED);
        }
        if (Airbag_Value > MAX_AIRBAG)
        {
            printf("- Airbag system failure detected (Value: %.2f, Max: %d)\n", Airbag_Value, MAX_AIRBAG);            
        }
    }

    // Check for minor errors (YELLOW_ON)
    else if (Media_System_Failure)
    {
        current_state = YELLOW_ON;
        printf("WARNING: Minor system error detected!\n");
        printf("- Media system failure\n");
    }

    // Output the current warning light state
    switch (current_state)
    {
        case RED_ON:
            printf("Warning Light: RED ON\n");
            break;
        case YELLOW_ON:
            printf("Warning Light: YELLOW ON\n");
            break;
        case NO_LIGHT:
            printf("Warning Light: OFF\n");
            break;
    }

    return current_state;
}

int main()
{
    State_Torque *state_torque = (State_Torque *)malloc(sizeof(State_Torque));
    State_Airbag *state_Airbag = (State_Airbag *)malloc(sizeof(State_Airbag));
    State_Rotor *rotor_torque = (State_Rotor *)malloc(sizeof(State_Rotor));

    // initialize_torque(&state_torque); // Prt to Prt
    initialize_torque(state_torque);     // Prt to Struct don't use "&""

    printf("Max_torque_value = 7500 --- (Data_Torque * 255) / 100.0\n");
    sint16 torque_value = Vitual_Torque_Sensor();
    float Decimal_Torque_Value = read_Torque_Sensor(&torque_value);
    printf("Value decimal of Torque is: %.2f\n", Decimal_Torque_Value);

    printf("Max_airbag_value = 1000 --- (Data_Airbag * 100.0)\n");
    sint16 airbag_value = Vitual_Airbag_Sensor();
    float Decimal_Airbag_Value = read_Airbag_Sensor(&airbag_value);
    printf("Value decimal of Airbag is: %.2f\n", Decimal_Airbag_Value);

    printf("Max_rotor_value = 50 --- inputAirbag * 1\n");
    sint16 rotor_value = Vitual_Airbag_Sensor();
    float Decimal_Rotor_Value = rotor_value;
    printf("Value decimal of Rotor Speed is: %.2f\n", Decimal_Rotor_Value);

    static uint16 Torque_Support;
    if (Decimal_Torque_Value > MAX_TORQUE || Decimal_Airbag_Value > MAX_AIRBAG)
    {
        // Limmit_Torque(Decimal_Torque_Value, &state_torque, Limmit_Value);
        Torque_Support = Limmit_Torque(Decimal_Torque_Value, state_torque, state_Airbag ,Limmit_Value);
        printf("Torque will be limited like: %.2f", (float)Torque_Support);
    }
    else{
        state_torque->isValid = true;
        state_Airbag->isValid = true;
    }
    
    if (Decimal_Rotor_Value > MAX_ROTORSPEED)
    {
        printf("Rotor Speed exceeded maximum limit (%d). Current value: %d\n", MAX_ROTORSPEED, Decimal_Rotor_Value);
        printf("Starting Torque Support reduction process...\n");
        Torque_Support = MAX_TORQUE;
        state_torque->isValid = false; // not valid
        rotor_torque->isValid = false; // not valid
        rotor_torque->Rotor_Sensor = SNA_Rotor_Sensor;
        state_torque->BSD = true; // true is active

        // BSD active
        if (state_torque->BSD == true){
            Reduce_Torque_Support(&Torque_Support);
            delay_ms(100);
            printf("BSD active and Deative Torque!\n");  
            Block_Steering_Detection(&Torque_Support);
            printf("Torque_Support hiện tại là: %d\n", Torque_Support);
        }
    }
    else
    {
        rotor_torque->isValid = true;
        rotor_torque->Rotor_Sensor = Decimal_Rotor_Value;
        printf("Rotor Speed is within normal range. No reduction needed.\n");
    }

    // Simulating media system failure (you can replace this with an actual check)
    bool Media_System_Failure = false;
    printf("Is there a media system failure? (1 for Yes, 0 for No): ");
    scanf("%d", &Media_System_Failure);

    // Call WLC_System to determine warning light state
    WLC_State warning_state = WLC_System(Decimal_Torque_Value, Decimal_Airbag_Value, Decimal_Rotor_Value, Media_System_Failure);

    // Cập nhật EPS_Status
    EPS_Status eps_status;
    eps_status.torque = *state_torque;
    eps_status.airbag = *state_Airbag;
    eps_status.rotor = *rotor_torque;
    eps_status.wlc = warning_state;

    // Gọi Eps_Out để gửi dữ liệu
    Eps_Out(&eps_status);

    free(state_torque);
    free(state_Airbag);
    free(rotor_torque);
}



