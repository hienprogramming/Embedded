#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


#define MAX_ERRORS        10
#define MAX_SUBSCRIBERS   10
#define MAX_ERROR_MESSAGE 10

typedef void (*DiagNotifyFunc)(const char *msg);

/* Danh sách lỗi định nghĩa trước */
typedef enum {
    ERR_ENGINE = 0,
    ERR_OVERHEAT,
    ERR_SENSOR,
    ERR_MAX
} DiagErrorId_t;

/* Cấu trúc chứa subscriber cho mỗi lỗi */
typedef struct {
    const char *name;
    DiagNotifyFunc  callback;
} DiagSubscriber_t;

/* Database cho từng lỗi */
typedef struct {
    DiagErrorId_t errorId;
    const char *errorName;
    uint8_t  subscriberCount;
    DiagSubscriber_t  subscribers[MAX_SUBSCRIBERS];
} DiagEventDB_t;

/*-------------------------------------------
 * Static database
 *-------------------------------------------*/
static DiagEventDB_t diagDB[MAX_ERRORS];
static uint8_t diagErrorCount = 0;


/*-------------------------------------------
 * Tạo database cho từng loại lỗi
 *-------------------------------------------*/
bool Diag_RegisterError(DiagErrorId_t id, const char *name)
{
    if (diagErrorCount >= MAX_ERRORS) return false;
    diagDB[diagErrorCount].errorId = id;
    diagDB[diagErrorCount].errorName = name;
    diagDB[diagErrorCount].subscriberCount = 0;
    diagErrorCount++;
    return true;
}


/*-------------------------------------------
 * Đăng ký component muốn nhận thông báo lỗi
 *-------------------------------------------*/

 bool Diag_RegisterSubscriber(DiagErrorId_t id, const char *compName, DiagNotifyFunc cb)
{
    for (uint8_t i = 0; i < diagErrorCount; i++) {
        if (diagDB[i].errorId == id) {
            uint8_t n = diagDB[i].subscriberCount;
            if (n >= MAX_SUBSCRIBERS) return false;
            diagDB[i].subscribers[n].name = compName;
            diagDB[i].subscribers[n].callback = cb;
            diagDB[i].subscriberCount++;
            return true;
        }
    }
    return false;
}

/*-------------------------------------------
 * Khi có lỗi xảy ra -> chỉ trigger đúng subscriber
 *-------------------------------------------*/
void Diag_HandleError(DiagErrorId_t id)
{
    for (uint8_t i = 0; i < diagErrorCount; i++) {
        if (diagDB[i].errorId == id) {
            printf("\n[Diag] Error detected: %s\n", diagDB[i].errorName);

            for (uint8_t j = 0; j < diagDB[i].subscriberCount; j++) {
                if (diagDB[i].subscribers[j].callback != NULL) {
                    diagDB[i].subscribers[j].callback(diagDB[i].errorName);
                }
            }
            return;
        }
    }
}
