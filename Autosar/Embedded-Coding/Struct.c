#include <stdio.h>
#define True 1
#define False 0
#define numEvents 4

// Giả sử có một struct cho sự kiện
struct Event {
    const void *eventData; // Con trỏ tới dữ liệu sự kiện
    int eventId;           // ID sự kiện
    void (*eventHandler)(void); // Con trỏ tới hàm xử lý sự kiện
    int eventFlag;         // Cờ sự kiện
};

// Định nghĩa một số biến và hàm để sử dụng trong mảng sự kiện
void check(void) {
    // Hàm xử lý sự kiện
    printf("Event handled.\n");
}

// Giả lập hàm nhận tín hiệu từ Airbag
void receiveAirBagSignals(struct Event events[], int numofEvents)
{
    for(int i = 0; i <= numofEvents+1; i++)
    {
        if(events[i].eventId == 4)
        {
            events[i].eventFlag = True;
            break;
        }
        else{
            events[i].eventFlag = False;
        }
    }
}


int main() {
    // Giả sử A1 và A2 là các biến dữ liệu sự kiện
    int A1 = 10;
    int A2 = 20;

    // Khai báo mảng sự kiện tĩnh nhưng không khởi tạo ngay lập tức
    static struct Event events[numEvents];

    // Gán giá trị cho mảng sự kiện
    // events[0].eventData = &A1;
    // events[0].eventId = 15;
    // events[0].eventHandler = check;
    // events[0].eventFlag = 0;

    // events[1].eventData = &A2;
    // events[1].eventId = 16;
    // events[1].eventHandler = check;
    // events[1].eventFlag = 0;

    // Truy cập và sử dụng mảng sự kiện
    for (int i = 0; i <= 2; ++i) {
        // No send event
        events[i].eventFlag = False;
        receiveAirBagSignals(events, 4);
        if (events[i].eventFlag == True)
        {
            printf("Event ID: %d\n", events[i].eventId);
            events[i].eventHandler();
        }
        else if(events[i].eventFlag == False)
        {
            // Event send null data
            events[i].eventData = NULL;
        } 
    }
    return 0;
}
