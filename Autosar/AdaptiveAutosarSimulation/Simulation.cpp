#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>
#include <sstream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>  // Include this header for read() and close()

// PID Controller Class
class PIDController {
private:
    double kp, ki, kd; // Proportional, Integral, Derivative coefficients
    double prev_error, integral;

public:
    PIDController(double kp, double ki, double kd) : kp(kp), ki(ki), kd(kd), prev_error(0), integral(0) {}

    double calculate(double target, double current) {
        double error = target - current;   // Error calculation
        integral += error;                // Accumulate integral
        double derivative = error - prev_error; // Calculate derivative
        prev_error = error;               // Save current error for next iteration

        // PID output
        return (kp * error) + (ki * integral) + (kd * derivative);
    }
};

// Simulated Car class
class Car {
private:
    double position;  // Current lateral position of the car (relative to lane center)
    double speed;     // Speed of the car
    double lane_width; // Width of the lane
    double desired_position; // Target position (center of the lane)

public:
    Car(double lane_width) : position(0), speed(50), lane_width(lane_width), desired_position(0) {}

    void update(double steering, double delta_time) {
        // Update the car's position based on steering input
        position += steering * delta_time;

        // Simulate speed adjustment for adaptive behavior
        if (std::fabs(position) > lane_width / 2) {
            speed -= 10; // Reduce speed if close to lane edge
        } else if (speed < 50) {
            speed += 5; // Gradually increase speed if centered
        }
    }

    double getPosition() const { return position; }
    double getSpeed() const { return speed; }
    double getLaneWidth() const { return lane_width; }
    double getDesiredPosition() const { return desired_position; }
};

// Function to receive data from Python
void receiveData(double &steering, double &position) {
    const char *host = "127.0.0.1";  // Localhost
    const int port = 65432;          // Port to connect to

    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in serv_addr{};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, host, &serv_addr.sin_addr) <= 0) {
        perror("Invalid address");
        exit(EXIT_FAILURE);
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection failed");
        exit(EXIT_FAILURE);
    }

    char buffer[1024] = {0};
    while (true) {
        int valread = read(sock, buffer, 1024);
        if (valread > 0) {
            std::stringstream ss(buffer);
            std::string steering_str, position_str;
            getline(ss, steering_str, ',');
            getline(ss, position_str, ',');

            steering = std::stod(steering_str);
            position = std::stod(position_str);

            std::cout << "Received Steering: " << steering << ", Position: " << position << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    close(sock);
}

// Simulation loop
void simulateLaneKeeping() {
    const double lane_width = 3.5; // Lane width (meters)
    const double delta_time = 0.1; // Time step (seconds)

    Car car(lane_width);
    PIDController pid(0.5, 0.1, 0.05);

    double steering = 0;
    double position = 0;

    std::thread receiver(receiveData, std::ref(steering), std::ref(position));
    receiver.detach();

    for (int step = 0; step < 200; ++step) {
        double pid_steering = pid.calculate(car.getDesiredPosition(), car.getPosition());
        car.update(steering + pid_steering, delta_time);

        std::cout << "Time: " << step * delta_time << "s"
                  << " | Position: " << car.getPosition() << "m"
                  << " | Speed: " << car.getSpeed() << "km/h"
                  << " | Steering: " << steering << "\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main() {
    std::cout << "Starting Lane-Keeping Simulation...\n";
    simulateLaneKeeping();
    std::cout << "Simulation Complete.\n";
    return 0;
}