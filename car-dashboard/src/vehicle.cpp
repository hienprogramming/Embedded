#include "vehicle.h"

Vehicle::Vehicle() 
    : speed(0)
    , battery_level(100.0f)
    , temperature(25.0f)
    , ac_temperature(19.0f)
    , drive_mode(DriveMode::ECO)
    , gear(GearPosition::P)
    , total_distance(1000.0f)
    , remaining_range(198.0f)
{}

void Vehicle::setSpeed(int s) {
    speed = (s < 0) ? 0 : (s > 200) ? 200 : s;
}

void Vehicle::setBatteryLevel(float level) {
    battery_level = (level < 0) ? 0 : (level > 100) ? 100 : level;
}

void Vehicle::setTemperature(float temp) {
    temperature = temp;
}

void Vehicle::setACTemperature(float temp) {
    ac_temperature = (temp < 16) ? 16 : (temp > 28) ? 28 : temp;
}

void Vehicle::setDriveMode(DriveMode mode) {
    drive_mode = mode;
}

void Vehicle::setGear(GearPosition g) {
    gear = g;
}

int Vehicle::getSpeed() const { return speed; }
float Vehicle::getBatteryLevel() const { return battery_level; }
float Vehicle::getTemperature() const { return temperature; }
float Vehicle::getACTemperature() const { return ac_temperature; }
Vehicle::DriveMode Vehicle::getDriveMode() const { return drive_mode; }
Vehicle::GearPosition Vehicle::getGear() const { return gear; }
float Vehicle::getTotalDistance() const { return total_distance; }
float Vehicle::getRemainingRange() const { return remaining_range; }

void Vehicle::increaseACTemp() {
    if (ac_temperature < 28) ac_temperature += 1.0f;
}

void Vehicle::decreaseACTemp() {
    if (ac_temperature > 16) ac_temperature -= 1.0f;
}

void Vehicle::increaseFanSpeed() {
    // Implementation for fan speed control
}

void Vehicle::brake() {
    if (speed > 0) speed -= 5;
}

void Vehicle::accelerate() {
    if (gear == GearPosition::D && speed < 200) speed += 5;
}