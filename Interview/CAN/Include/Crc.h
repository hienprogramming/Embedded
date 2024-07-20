#ifndef CRC_H
#define CRC_H

#include <stdint.h>
#include <stddef.h>

uint32_t calculate_crc(const uint8_t *data, size_t length);

#endif // CRC_H