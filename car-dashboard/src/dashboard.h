#pragma once
#include <SFML/Graphics.hpp>
#include "vehicle.h"

class Dashboard {
private:
    sf::RenderWindow window;
    Vehicle& vehicle;
    
    // GUI elements
    sf::Font font;
    sf::Text speedText;
    sf::Text batteryText;
    sf::Text modeText;
    sf::Text gearText;
    
public:
    Dashboard(Vehicle& v);
    void run();
    void handleInput();
    void update();
    void render();
};