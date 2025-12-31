#include <iostream>
#include <cstdint>

uint32_t ble_crc24(const uint8_t* data, uint16_t len)
{
    uint32_t crc = 0x555555;   // BLE init value

    for (uint16_t i = 0; i < len; i++)
    {
        uint8_t d = data[i];

        for (uint8_t bit = 0; bit < 8; bit++)
        {
            uint8_t data_bit = d & 0x01;
            uint8_t crc_bit  = crc & 0x01;

            crc >>= 1;

            if (data_bit ^ crc_bit)
            {
                crc ^= 0x00065B;
            }

            d >>= 1;
        }
    }

    return crc & 0xFFFFFF;   // 24-bit
}


int main()
{
    uint8_t pdu[]= {
        0x02,   // Header
        0x01, 0x06   // Payload
    };

    uint16_t len = sizeof(pdu) / sizeof(pdu[0]);

    uint32_t crc = ble_crc24(pdu, len);

    printf("BLE CRC24 result: 0x%06X\n", crc);

    // CRC bytes as sent on air (LSB first)
    uint8_t crc0 = (uint8_t)(crc ^ 0xFF);
    uint8_t crc1 = (uint8_t)((crc >> 8) ^ 0xFF);
    uint8_t crc2 = (uint8_t)((crc >> 16) ^ 0xFF);

    printf("CRC bytes (TX order): %02X %02X %02X\n",
           crc0, crc1, crc2);

    return 0;
}