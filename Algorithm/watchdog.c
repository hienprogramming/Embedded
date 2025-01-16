#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

// Mô phỏng watchdog timer
#define WATCHDOG_TIMEOUT 5 // Thời gian timeout (giây)

// Biến toàn cục để mô phỏng hệ thống
time_t watchdog_last_reset; // Thời gian watchdog được reset
bool system_running = true; // Trạng thái hệ thống
bool task_running = true;   // Trạng thái task

// Hàm khởi tạo watchdog
void Watchdog_Init(void) {
    watchdog_last_reset = time(NULL); // Ghi lại thời gian hiện tại
    printf("Watchdog initialized (timeout: %d seconds)\n", WATCHDOG_TIMEOUT);
}

// Hàm feed (reset) watchdog
void Watchdog_Feed(void) {
    watchdog_last_reset = time(NULL); // Ghi lại thời gian hiện tại
    printf("Watchdog fed\n");
}

// Hàm kiểm tra watchdog
void Watchdog_Check(void) {
    // Lấy thời gian hiện tại
    time_t current_time = time(NULL);

    // Kiểm tra nếu vượt quá timeout
    if (difftime(current_time, watchdog_last_reset) > WATCHDOG_TIMEOUT) {
        printf("Watchdog timeout! System reset...\n");
        system_running = false; // Mô phỏng reset hệ thống
    }
}

// Hàm mô phỏng task
void Task_Run(void) {
    printf("Task running...\n");
    if (task_running) {
        // Mô phỏng task bị trễ
        int delay = rand() % 8; // Random delay từ 0-6 giây
        printf("Task delay: %d seconds\n", delay);

        if (delay > WATCHDOG_TIMEOUT) {
            printf("Task failed! Not feeding watchdog.\n");
            task_running = false; // Task không hoạt động bình thường
        } else {
            sleep(delay); // Mô phỏng công việc của task
            Watchdog_Feed(); // Feed watchdog nếu task hoàn thành
        }
    } else {
        printf("Task not running. Watchdog will timeout.\n");
    }
}

int main(void) {
    // Khởi tạo watchdog
    Watchdog_Init();

    // Vòng lặp chính
    while (system_running) {
        printf("System running...\n");

        // Chạy task
        Task_Run();

        // Kiểm tra watchdog
        Watchdog_Check();

        // Thêm delay nhỏ để mô phỏng vòng lặp hệ thống
        sleep(1);
    }

    // Khi hệ thống bị reset
    printf("System restarted\n");
    return 0;
}
