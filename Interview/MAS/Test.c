#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_ENVENTS 100
#define EVENT_DATA_SIZE 256

typedef struct{
    int event_id;
    time_t timestamp;
    char data[EVENT_DATA_SIZE];
}EventRecord;

typedef struct{
    EventRecord events[MAX_ENVENTS];
    int event_count;
}BlackBox;

void initialize_black_box( BlackBox *black_box)
{
    black_box->event_count = 0;
}

void Record_events(BlackBox *black_box, int event_id, const char *data)
{
    if (black_box->event_count < MAX_ENVENTS)
    {
        EventRecord *event = &black_box->events[black_box->event_count++];
        event->event_id = event_id;
        event->timestamp = time(NULL);
        strncpy(event->data, data, EVENT_DATA_SIZE - 1);
        event->data[EVENT_DATA_SIZE - 1] = '\0';
    }
    else{
        printf("Black box memory full. Can not record new events.\n");
    }
}

void display_events(const BlackBox *black_box)
{
    for(int i = 0; i < black_box->event_count; i++)
    {
        const EventRecord *event = &black_box->events[i];
        printf("Event ID: %d\n", event->event_id);
        printf("Timestamp: %s", ctime)
    }
}

int main()
{
    BlackBox black_box;
    printf("Event ID: %d\n", black_box.events[0].event_id);
    printf("Timestamp: %s", ctime(&black_box.events[0].timestamp));

    return 0;
}