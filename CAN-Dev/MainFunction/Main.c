#include "Swc.h"
#include "stm32f4xx_hal.h"

// Định nghĩa chân GPIO cho đèn LED
#define LED_PIN GPIO_PIN_5
#define LED_GPIO_PORT GPIOA
#define LED_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()

void SystemClock_Config(void);
void Error_Handler(void);
void LED_Init(void);

int main(void) {
    // Khởi tạo HAL Library
    HAL_Init();

    // Cấu hình hệ thống Clock
    SystemClock_Config();

    // Khởi tạo đèn LED
    LED_Init();

    // Khởi tạo lớp ứng dụng (Application Software)
    Swc_Init();

    // Vòng lặp chính
    while (1) {
        // Thực hiện chức năng chính của ứng dụng
        Swc_MainFunction();

        // Thêm thời gian chờ để tránh vòng lặp quá nhanh
        HAL_Delay(100); // 100 ms
    }
}

// Hàm cấu hình hệ thống Clock
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    // Khởi tạo bộ dao động chính (HSE)
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        // Xử lý lỗi
        Error_Handler();
    }

    // Khởi tạo CPU, AHB và APB bus clock
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK) {
        // Xử lý lỗi
        Error_Handler();
    }
}

// Hàm khởi tạo đèn LED
void LED_Init(void) {
    // Kích hoạt clock cho GPIOA
    LED_GPIO_CLK_ENABLE();

    // Cấu hình chân GPIO cho LED
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = LED_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED_GPIO_PORT, &GPIO_InitStruct);

    // Đặt đèn LED tắt ban đầu
    HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET);
}

// Hàm xử lý lỗi
void Error_Handler(void) {
    // Vòng lặp vô hạn để đèn LED nhấp nháy chỉ báo lỗi
    while (1) {
        // Bật đèn LED
        HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_SET);
        HAL_Delay(500); // 500 ms

        // Tắt đèn LED
        HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET);
        HAL_Delay(500); // 500 ms
    }
}