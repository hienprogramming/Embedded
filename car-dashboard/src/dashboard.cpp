#include "dashboard.h"
#include <sstream>

Dashboard::Dashboard(Vehicle& v) 
    : window(sf::VideoMode(800, 600), "Car Dashboard")
    , vehicle(v)
{
    if (!font.loadFromFile("arial.ttf")) {
        throw std::runtime_error("Could not load font");
    }

    window.setFramerateLimit(60);
    
    // Initialize text elements
    speedText.setFont(font);
    batteryText.setFont(font);
    modeText.setFont(font);
    gearText.setFont(font);
}

void Dashboard::run() {
    while (window.isOpen()) {
        handleInput();
        update();
        render();
    }
}

void Dashboard::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
            
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
                case sf::Keyboard::Space:
                    // Toggle between brake and accelerate
                    break;
                case sf::Keyboard::Up:
                    vehicle.increaseACTemp();
                    break;
                case sf::Keyboard::Down:
                    vehicle.decreaseACTemp();
                    break;
                case sf::Keyboard::M:
                    // Toggle drive mode
                    break;
                // Add other key handlers
            }
        }
    }
}

void Dashboard::update() {
    // Update vehicle state based on time and inputs
}

void Dashboard::render() {
    window.clear(sf::Color(30, 30, 40));

    // Render speed
    std::stringstream ss;
    ss << vehicle.getSpeed() << " km/h";
    speedText.setString(ss.str());
    speedText.setPosition(50, 50);
    window.draw(speedText);

    // Render battery level
    ss.str("");
    ss << "Battery: " << vehicle.getBatteryLevel() << "%";
    batteryText.setString(ss.str());
    batteryText.setPosition(50, 100);
    window.draw(batteryText);

    // Render drive mode
    modeText.setString(vehicle.getDriveMode() == Vehicle::DriveMode::ECO ? "ECO" : "SPORT");
    modeText.setPosition(50, 150);
    window.draw(modeText);

    // Render gear position
    const char* gears[] = {"P", "R", "N", "D"};
    gearText.setString(gears[static_cast<int>(vehicle.getGear())]);
    gearText.setPosition(50, 200);
    window.draw(gearText);

    window.display();
}