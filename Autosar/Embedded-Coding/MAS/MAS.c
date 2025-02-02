#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_EVENTS 100
#define EVENT_DATA_SIZE 256

typedef struct {
    int event_id;
    time_t timestamp;
    char data[EVENT_DATA_SIZE];
    unsigned short *error_code; // Con trỏ đến mã lỗi
} EventRecord;

typedef struct {
    EventRecord events[MAX_EVENTS];
    int event_count;
} BlackBox;

void initialize_black_box(BlackBox *black_box) {
    black_box->event_count = 0;
}

void record_event(BlackBox *black_box, int event_id, const char *data, int has_error) {
    if (black_box->event_count < MAX_EVENTS) {
        EventRecord *event = &black_box->events[black_box->event_count++];
        event->event_id = event_id;
        event->timestamp = time(NULL);
        strncpy(event->data, data, EVENT_DATA_SIZE - 1);
        event->data[EVENT_DATA_SIZE - 1] = '\0'; // Đảm bảo chuỗi được kết thúc đúng bằng cách thêm ký tự NULL vào

        // Cấp phát bộ nhớ cho con trỏ error_code
        event->error_code = malloc(sizeof(unsigned short));

        // Gán mã lỗi nếu có lỗi
        if (has_error) {
            *event->error_code = 0xffff;
        } else {
            *event->error_code = 0;
        }
    } else {
        printf("Black box memory full. Cannot record new events.\n");
    }
}

void display_events(const BlackBox *black_box) {
    for (int i = 0; i < black_box->event_count; i++) {
        const EventRecord *event = &black_box->events[i];
        printf("Event ID: %d\n", event->event_id);
        printf("Timestamp: %s", ctime(&event->timestamp));
        printf("Data: %s\n", event->data);
        if (*event->error_code == 0xffff) {
            printf("Error code: 0xffff\n");
        }
        printf("------------------------\n");
    }
}

int main() {
    BlackBox black_box;

    initialize_black_box(&black_box);

    record_event(&black_box, 1, "Engine start", 0);
    record_event(&black_box, 2, "Speed: 60 km/h", 0);
    record_event(&black_box, 3, "Brake applied", 0);
    record_event(&black_box, 4, "Accident detected: Front collision", 1);

    display_events(&black_box);

    // Giải phóng bộ nhớ cho các con trỏ error_code
    for (int i = 0; i < black_box.event_count; i++) {
        free(black_box.events[i].error_code);
    }

    return 0;
}