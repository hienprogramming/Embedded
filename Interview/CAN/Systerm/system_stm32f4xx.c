#include "stm32f4xx.h"

// Định nghĩa vector ngắt
__attribute__((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
    (void (*)(void))((unsigned long)&_stack_end),  // Địa chỉ đỉnh stack
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    // Các handler khác...
};

void Reset_Handler(void) {
    // Khởi tạo dữ liệu .data và .bss
    extern unsigned long _sidata, _sdata, _edata, _sbss, _ebss;
    unsigned long *src, *dst;

    // Copy dữ liệu .data từ flash vào RAM
    src = &_sidata;
    for (dst = &_sdata; dst < &_edata;) {
        *(dst++) = *(src++);
    }

    // Khởi tạo vùng .bss với 0
    for (dst = &_sbss; dst < &_ebss;) {
        *(dst++) = 0;
    }

    // Gọi hàm main
    main();
}

// Định nghĩa các handler khác
void NMI_Handler(void) { while (1); }
void HardFault_Handler(void) { while (1); }
// Các handler khác...