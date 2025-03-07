// File: acc_server_windows.cpp
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <cstring>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsaData;
    int iResult;

    // Khởi tạo Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        cerr << "WSAStartup failed: " << iResult << endl;
        return 1;
    }

    // Tạo socket
    SOCKET ListenSocket = INVALID_SOCKET, ClientSocket = INVALID_SOCKET;
    int port = 12345;

    ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ListenSocket == INVALID_SOCKET) {
        cerr << "socket() failed: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }

    // Cài đặt địa chỉ và cổng
    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = INADDR_ANY;
    service.sin_port = htons(port);

    if (bind(ListenSocket, (SOCKADDR *)&service, sizeof(service)) == SOCKET_ERROR) {
        cerr << "bind() failed: " << WSAGetLastError() << endl;
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    if (listen(ListenSocket, 3) == SOCKET_ERROR) {
        cerr << "listen() failed: " << WSAGetLastError() << endl;
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    cout << "Server listening on port " << port << endl;
    
    // Chấp nhận kết nối từ client
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        cerr << "accept() failed: " << WSAGetLastError() << endl;
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    
    // Các biến mô phỏng
    double front_speed = 25.0;
    double our_speed = 30.0;
    double gap = 25.0;
    double dt = 1.0;
    
    char buffer[128];
    int time_count = 0; // Biến đếm thời gian

    while (true) {
        // Cập nhật tốc độ và khoảng cách
        front_speed = 30.0 + ((rand() % 100) / 100.0 * 10.0 - 5.0);
        gap = gap + (front_speed - our_speed) * dt;
        if (gap < 0) gap = 0;

        // Luôn in khoảng cách thực tế
        cout << "[Sensor] Current gap: " << gap << " m" << endl;

        // Gửi/nhận dữ liệu sau 5 giây
        if (time_count >= 5) {
            sprintf(buffer, "%.2f,%.2f,%.2f", front_speed, our_speed, gap);
            int sendResult = send(ClientSocket, buffer, (int)strlen(buffer), 0);
            if (sendResult == SOCKET_ERROR) {
                cerr << "send() failed: " << WSAGetLastError() << endl;
                break;
            }
            cout << "Sent to client: " << buffer << endl;

            // Nhận lệnh tốc độ mới
            char recv_buffer[128] = {0};
            int recvResult = recv(ClientSocket, recv_buffer, 128, 0);
            if (recvResult > 0) {
                double new_speed = atof(recv_buffer);
                cout << "Received new speed: " << new_speed << " m/s" << endl;
                our_speed = new_speed;
            }
        } else {
            time_count++; // Tăng biến đếm thời gian
            cout << "Initializing... (" << time_count << "/5 seconds)" << endl;
        }

        Sleep(1000); // Chờ 1 giây
    }
    
    // Đóng socket và dọn dẹp
    closesocket(ClientSocket);
    closesocket(ListenSocket);
    WSACleanup();
    return 0;
}