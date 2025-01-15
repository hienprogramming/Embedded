#include <stdio.h>
#include <stdint.h>

// Polynomial for CRC-16-CCITT
#define POLYNOMIAL 0x1021
#define INITIAL_VALUE 0xFFFF

// Function to calculate CRC-16
uint16_t calculate_crc16(uint8_t *data, size_t length) {
    uint16_t crc = INITIAL_VALUE;

    for (size_t i = 0; i < length; i++) {
        crc ^= (data[i] << 8); // XOR byte into high-order byte of CRC
        
        for (int bit = 0; bit < 8; bit++) {
            if (crc & 0x8000) {
                crc = (crc << 1) ^ POLYNOMIAL;
            } else {
                crc <<= 1;
            }
        }
    }

    return crc;
}

int main() {
    // Example data
    uint8_t data[] = {0x31, 0x32, 0x33, 0x34, 0x35}; // ASCII for "12345"
    size_t data_length = sizeof(data) / sizeof(data[0]);

    // Calculate CRC-16
    uint16_t crc_result = calculate_crc16(data, data_length);

    // Print result
    printf("CRC-16 Result: 0x%04X\n", crc_result);

    return 0;
}
