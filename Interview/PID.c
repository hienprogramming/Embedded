// Theory about PID: https://www.iostream.co/article/thuat-toan-pid-trong-dieu-khien-tu-dong-3Iu1u
/*
P: độ lỗi ở thời điểm hiện tại, để có độ lỗi này cần một giá trị tên pivot là giá trị lý tưởng mong muốn động cơ đạt được, có thể suy ra độ lỗi từ pivot.
I: độ lỗi của toàn bộ quá trình, với giá trị này, giá trị điều chỉnh sẽ phụ thuộc vào toàn bộ quá trình hoạt động của động cơ, giá trị này sẽ lấy dựa vào trung bình độ lỗi ở mỗi thời điểm trước đó.
D: đạo hàm độ lỗi trong một khoảng thời gian trước đó, giá trị này có nghĩa giá trị điều chỉnh sẽ phần nào đó đoán được xu hướng của động cơ mà điều chỉnh cho hợp lý.
*/
#include <stdio.h>

typedef struct{
    float Kp;    // Proportional gain: tăng tỷ lệ thuận    
    float Ki;    // Integral gain: tích phân đạt được
    float Kd;    // Lợi nhuận phát sinh
    float pre_error;  // Previous error
    float integral;   // Integral
}PID;


void PID_init(PID *pid, float Kp, float Ki, float Kd)
{
    
}