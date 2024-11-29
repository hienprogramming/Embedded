#include "stm32f10x.h"

// Khởi tạo IWDG (Independent Watchdog Timer)
void IWDG_Init(void) {
    // Kích hoạt LSI (Low-Speed Internal Clock ~ 40kHz)
    RCC_LSICmd(ENABLE); 
    while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET); // Chờ LSI ổn định

    // Cấu hình IWDG
    IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable); // Cho phép ghi vào thanh ghi IWDG
    IWDG_SetPrescaler(IWDG_Prescaler_64);        // Prescaler = 64
    IWDG_SetReload(2000);                        // Reload Value: Timeout khoảng 2 giây
    IWDG_ReloadCounter();                        // Nạp giá trị bộ đếm ban đầu
    IWDG_Enable();                               // Kích hoạt IWDG
}

int main(void) {
    SystemInit();   // Khởi tạo hệ thống
    IWDG_Init();    // Khởi tạo và bật Watchdog

    static int error_simulation = 0; // Biến để giả lập lỗi

    while (1) {
        // Kiểm tra trạng thái lỗi
        if (error_simulation == 0) {
            // Hệ thống hoạt động bình thường
            IWDG_ReloadCounter(); // Reset Watchdog để tránh reset hệ thống
        } else {
            // Giả lập lỗi: không reset Watchdog
            // Sau khoảng 2 giây, hệ thống sẽ tự reset do timeout của Watchdog
        }

        // Giả lập chuyển sang trạng thái lỗi sau một thời gian
        for (volatile int i = 0; i < 1000000; i++); // Delay giả lập
        error_simulation = 1; // Kích hoạt lỗi sau vòng lặp đầu tiên
    }
}
