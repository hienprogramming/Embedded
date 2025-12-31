def ble_crc24(data: bytes, length: int) -> int:
    crc = 0x555555

    for i in range(length):
        d = data[i]

        for _ in range(8):
            data_bit = d & 0x01
            crc_bit  = crc & 0x01

            crc >>= 1

            if data_bit ^ crc_bit:
                crc ^= 0x00065B

            d >>= 1

    return crc & 0xFFFFFF


def main():
    pdu = bytes([0x02, 0x01, 0x06])
    length = len(pdu)

    crc = ble_crc24(pdu, length)

    print(f"BLE CRC24 result: 0x{crc:06X}")
    print(f"CRC bytes (TX order): "
          f"{crc & 0xFF:02X} "
          f"{(crc >> 8) & 0xFF:02X} "
          f"{(crc >> 16) & 0xFF:02X}")


if __name__ == "__main__":
    main()
