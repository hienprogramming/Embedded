//stm32f4xx.h (Giả định đây là tệp tiêu đề chứa các định nghĩa cơ bản cho STM32F4)

#ifndef STM32F4XX_H
#define STM32F4XX_H

#include <stdint.h>

// Khai báo các hàm xử lý ngắt
void Reset_Handler(void);
void NMI_Handler(void);
void HardFault_Handler(void);

#endif // STM32F4XX_H