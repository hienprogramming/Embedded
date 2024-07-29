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
} EventRecord;

typedef struct {
    EventRecord events[MAX_EVENTS];
    int event_count;
} BlackBox;

void initialize_black_box(BlackBox *black_box) {
    black_box->event_count = 0;
}

void record_event(BlackBox *black_box, int event_id, const char *data) {
    if (black_box->event_count < MAX_EVENTS) {
        EventRecord *event = &black_box->events[black_box->event_count++];
        event->event_id = event_id;
        event->timestamp = time(NULL);
        strncpy(event->data, data, EVENT_DATA_SIZE - 1);
        event->data[EVENT_DATA_SIZE - 1] = '\0'; // Đảm bảo chuỗi được kết thúc đúng bằng cách thêm ký tự NULL vào
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
        printf("------------------------\n");
    }
}

int main() {
    BlackBox black_box;

    initialize_black_box(&black_box);

    record_event(&black_box, 1, "Engine start");
    record_event(&black_box, 2, "Speed: 60 km/h");
    record_event(&black_box, 3, "Brake applied");
    record_event(&black_box, 4, "Accident detected: Front collision");

    display_events(&black_box);

    return 0;
}

