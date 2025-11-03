#include <stdio.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

#define BLOCK_SIZE 16
#define BUFFER_SIZE 128

void add_padding(unsigned char *data, int original_len, int *padded_len) {
    int padding_len = BLOCK_SIZE - (original_len % BLOCK_SIZE);
    for (int i = 0; i < padding_len; ++i) {
        data[original_len + i] = padding_len;
    }
    *padded_len = original_len + padding_len;
}

int remove_padding(unsigned char *data, int padded_len) {
    int padding_len = data[padded_len - 1];
    return padded_len - padding_len;
}

void generate_aes_key(unsigned char *key) {
    RAND_bytes(key, BLOCK_SIZE);
}

void encrypt_aes(const unsigned char *plaintext, int plaintext_len, const unsigned char *key, unsigned char *iv, unsigned char *ciphertext, int *cipher_len) {
    AES_KEY aes_key;
    AES_set_encrypt_key(key, 128, &aes_key);

    unsigned char padded_plaintext[BUFFER_SIZE];
    memset(padded_plaintext, 0, BUFFER_SIZE);
    int actual_len;
    add_padding(padded_plaintext, plaintext_len, &actual_len);
    memcpy(padded_plaintext, plaintext, plaintext_len);

    AES_cbc_encrypt(padded_plaintext, ciphertext, actual_len, &aes_key, iv, AES_ENCRYPT);
    *cipher_len = actual_len;
}

void decrypt_aes(const unsigned char *ciphertext, int ciphertext_len, const unsigned char *key, unsigned char *iv, unsigned char *decryptedtext) {
    AES_KEY aes_key;
    AES_set_decrypt_key(key, 128, &aes_key);

    AES_cbc_encrypt(ciphertext, decryptedtext, ciphertext_len, &aes_key, iv, AES_DECRYPT);

    int unpadded_len = remove_padding(decryptedtext, ciphertext_len);
    decryptedtext[unpadded_len] = '\0';
}

void send_command(const char *command, const unsigned char *key) {
    printf("[ECU_Sender] Sending command: %s\n", command);

    unsigned char iv[BLOCK_SIZE];
    RAND_bytes(iv, BLOCK_SIZE);
    unsigned char iv_backup[BLOCK_SIZE];
    memcpy(iv_backup, iv, BLOCK_SIZE); // Lưu IV để dùng lại

    unsigned char ciphertext[BUFFER_SIZE];
    memset(ciphertext, 0, BUFFER_SIZE);
    int len = strlen(command);
    int cipher_len;

    encrypt_aes((const unsigned char *)command, len, key, iv, ciphertext, &cipher_len);

    printf("[ECU_Sender] Encrypted command: ");
    for (int i = 0; i < cipher_len; ++i) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    receive_command(ciphertext, cipher_len, key, iv_backup);
}

void receive_command(const unsigned char *ciphertext, int len, const unsigned char *key, unsigned char *iv) {
    printf("[ECU_Receiver] Received encrypted message: ");
    for (int i = 0; i < len; ++i) {
        printf("%02x", ciphertext[i]);
    }
    printf("\n");

    unsigned char decryptedtext[BUFFER_SIZE];
    memset(decryptedtext, 0, BUFFER_SIZE);

    decrypt_aes(ciphertext, len, key, iv, decryptedtext);

    printf("[ECU_Receiver] Decrypted command: %s\n", decryptedtext);
}


/////
float (int Sensor){
    return (Sensor / 76.2345);
}
uint8_t calculateChecksum(uint8_t* data, uint8_t length) {
    uint8_t checksum = 0;
    for (uint8_t i = 0; i < length; i++) {
        checksum += data[i];  // Simple addition
    }
    return ~checksum;  // Optional: Complement the result
}


int function_TestActiveReturn(){
    float Sensor_Torque; 
    float Sensor_Engine;
    float Sensor_Steering;
    int checkSum;

    if (((Sensor_Torque && Sensor_Engine) | (Sensor_Steering | Sensor_Engine)) != 0){
        Sensor_Steering = function_ReadTempSensor (Sensor_Torque);  // Sensor will return Temp
        checkSum = calculateChecksum (Sensor_Torque, sizeof(Sensor_Torque))
    }
    else if (((Sensor_Torque != Sensor_Engine) | (Sensor_Steering | Sensor_Engine)) != 0){
        Sensor_Steering = function_ReadTempSensor (Sensor_Engine);  // Sensor will return Temp
        checkSum = calculateChecksum (Sensor_Engine, sizeof(Sensor_Engine))
    }
    else if (((Sensor_Torque == Sensor_Engine) | (Sensor_Steering | Sensor_Engine)) != 0){
        Sensor_Steering = function_ReadTempSensor (Sensor_Engine);  // Sensor will return Temp
        checkSum = calculateChecksum (Sensor_Steering, sizeof(Sensor_Steering))
    }

    return checkSum;
}

int NAValue = 65535;

float ReadFromSensor (){
    return TempSensorRead = Read_SenSor / 27.5;
}

float funtion_MakeSure_Steering_Active(float Sensor_SteeringCheck)
{
    const TempConTrollSafe = 150;
    if (function_TestActiveReturn() != 0){
        Sensor_SteeringCheck = NAValue;
    }
    else if (function_TestActiveReturn() == 0){
        Sensor_SteeringCheck = ReadFromSensor ();
    }

    #if (Sensor_SteeringCheck > TempConTrollSafe) && (Sensor_SteeringCheck < 0)
    #error "Sensor temperature is error!"
    #endif

    return Sensor_SteeringCheck;
}

void sequence1(){
    funtion_MakeSure_Steering_Active ();
}

void def_function_ActiveReturn(float sensorcheckActive, float receive){
    sensorcheckActive = (receive / 255) * 10^3;
    sensorcheckActive = receive & 0x01;
}

void SteeringFunctionSequence(){
    sequence1();
    sensorActive = funtion_MakeSure_Steering_Active();
    receiveSen = sensorActive & 0x08;
    def_function_ActiveReturn(sensorActive, receiveSen);
}



/////

int main() {
    unsigned char shared_key[BLOCK_SIZE];
    generate_aes_key(shared_key);

    const char *control_command = "Activate_Headlights";

    send_command(control_command, shared_key);

    return 0;
}



