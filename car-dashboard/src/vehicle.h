#pragma once
#include <string>

class Vehicle {
public:
    enum class DriveMode {
        ECO,
        SPORT
    };

    enum class GearPosition {
        P, R, N, D
    };

private:
    int speed;
    float battery_level;
    float temperature;
    float ac_temperature;
    DriveMode drive_mode;
    GearPosition gear;
    float total_distance;
    float remaining_range;

public:
    Vehicle();
    
    void setSpeed(int speed);
    void setBatteryLevel(float level);
    void setTemperature(float temp);
    void setACTemperature(float temp);
    void setDriveMode(DriveMode mode);
    void setGear(GearPosition gear);
    
    int getSpeed() const;
    float getBatteryLevel() const;
    float getTemperature() const;
    float getACTemperature() const;
    DriveMode getDriveMode() const;
    GearPosition getGear() const;
    float getTotalDistance() const;
    float getRemainingRange() const;
    
    void increaseACTemp();
    void decreaseACTemp();
    void increaseFanSpeed();
    void brake();
    void accelerate();
};