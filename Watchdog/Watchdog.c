#include "stm32f10x.h" // Thư viện HAL hoặc CMSIS cho STM32

void IWDG_Init(void) {
    // 1. Kích hoạt LSI (Low-Speed Internal Clock ~ 40kHz)
    RCC_LSICmd(ENABLE); 
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET); // Chờ LSI ổn định

    // 2. Enable IWDG (Independent Watchdog)
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); // Cho phép ghi vào các thanh ghi của IWDG
    
    IWDG_SetPrescaler(IWDG_Prescaler_64); // Chọn bộ chia tần số (Prescaler)
    IWDG_SetReload(1000);                 // Giá trị nạp lại (Reload Value): 40kHz / 64 = 625Hz -> Reset sau ~1.6s

    IWDG_ReloadCounter();                 // Nạp lại giá trị bộ đếm
    IWDG_Enable();                        // Bật Watchdog
}


int main(void) {
    SystemInit();   // Khởi tạo hệ thống
    IWDG_Init();    // Cấu hình và bật IWDG

    while (1) {
        // Các công việc chính trong hệ thống

        // Nếu hệ thống hoạt động bình thường, luôn reset Watchdog
        IWDG_ReloadCounter();

        // Giả lập thời gian xử lý (Delay)
        for (volatile int i = 0; i < 1000000; i++);
    }
}


