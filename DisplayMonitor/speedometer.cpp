#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>

const float PI = 3.14159265359;

class Speedometer {
public:
    sf::RenderWindow& window;
    sf::Font font;
    float radius;
    sf::Vector2f center;
    float minSpeed;
    float maxSpeed;
    float currentSpeed;
    bool manualMode;

    struct Button {
        sf::RectangleShape shape;
        sf::Text label;
    };

    Button minusButton, plusButton, manualButton;

    struct WarningLight {
        sf::CircleShape shape;
        sf::Text label;
        bool isOn;
    };
    std::vector<WarningLight> warningLights;

public:
    Speedometer(sf::RenderWindow& win) :
        window(win),
        radius(200),
        minSpeed(0),
        maxSpeed(240),
        currentSpeed(0),
        manualMode(false)
    {
        center = sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f);

        if (!font.loadFromFile("/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf")) {
            std::cerr << "Error loading font" << std::endl;
            throw std::runtime_error("Cannot load font");
        }

        setupWarningLights();
        setupButtons();
    }

    void setupWarningLights() {
        std::vector<std::string> symbols = { "ABS", "FUEL", "OIL", "CHECK", "TEMP" };
        float startX = center.x - 150;
        float y = center.y + 50;

        for (int i = 0; i < symbols.size(); i++) {
            WarningLight light;
            light.shape.setRadius(20);
            light.shape.setPosition(startX + i * 60, y);
            light.shape.setFillColor(sf::Color(50, 50, 50));

            light.label.setFont(font);
            light.label.setString(symbols[i]);
            light.label.setCharacterSize(16);
            light.label.setPosition(startX + i * 60 + 5, y + 5);
            light.label.setFillColor(sf::Color::White);

            light.isOn = false;
            warningLights.push_back(light);
        }
    }

    void setupButtons() {
        float buttonWidth = 100;
        float buttonHeight = 50;
        float buttonY = center.y + 150;

        minusButton.shape.setSize(sf::Vector2f(buttonWidth, buttonHeight));
        minusButton.shape.setPosition(center.x - 180, buttonY);
        minusButton.shape.setFillColor(sf::Color::Blue);
        minusButton.label.setFont(font);
        minusButton.label.setString("-");
        minusButton.label.setCharacterSize(30);
        minusButton.label.setFillColor(sf::Color::White);
        minusButton.label.setPosition(center.x - 150, buttonY + 5);

        plusButton.shape.setSize(sf::Vector2f(buttonWidth, buttonHeight));
        plusButton.shape.setPosition(center.x + 80, buttonY);
        plusButton.shape.setFillColor(sf::Color::Blue);
        plusButton.label.setFont(font);
        plusButton.label.setString("+");
        plusButton.label.setCharacterSize(30);
        plusButton.label.setFillColor(sf::Color::White);
        plusButton.label.setPosition(center.x + 110, buttonY + 5);

        manualButton.shape.setSize(sf::Vector2f(buttonWidth, buttonHeight));
        manualButton.shape.setPosition(center.x - 50, buttonY);
        manualButton.shape.setFillColor(sf::Color::Blue);
        manualButton.label.setFont(font);
        manualButton.label.setString("Manual");
        manualButton.label.setCharacterSize(20);
        manualButton.label.setFillColor(sf::Color::White);
        manualButton.label.setPosition(center.x - 30, buttonY + 15);
    }

    void setSpeed(float speed) {
        currentSpeed = std::min(std::max(speed, minSpeed), maxSpeed);
        std::cout << "Speed set to: " << currentSpeed << std::endl;
    }

    void toggleWarningLight(int index) {
        if (index >= 0 && index < warningLights.size()) {
            warningLights[index].isOn = !warningLights[index].isOn;
            warningLights[index].shape.setFillColor(warningLights[index].isOn ? sf::Color::Red : sf::Color(50, 50, 50));
        }
    }

    void toggleManualMode() {
        manualMode = !manualMode;
        std::cout << "Manual mode: " << (manualMode ? "ON" : "OFF") << std::endl;
    }

    bool isManualMode() const {
        return manualMode;
    }

    bool isButtonClicked(sf::Vector2f mousePos, Button& button) {
        return button.shape.getGlobalBounds().contains(mousePos);
    }

    void draw() {
        sf::CircleShape outline(radius);
        outline.setPosition(center.x - radius, center.y - radius);
        outline.setFillColor(sf::Color(30, 30, 30));
        outline.setOutlineThickness(2);
        outline.setOutlineColor(sf::Color::White);
        window.draw(outline);

        for (int i = 0; i <= 12; i++) {
            float angle = (i * 20 - 120) * PI / 180;
            sf::Text speedText;
            speedText.setFont(font);
            speedText.setString(std::to_string(i * 20));
            speedText.setCharacterSize(20);
            speedText.setFillColor(sf::Color::White);

            float x = center.x + (radius - 30) * std::sin(angle) - 10;
            float y = center.y - (radius - 30) * std::cos(angle) - 10;
            speedText.setPosition(x, y);
            window.draw(speedText);
        }

        float angle = (currentSpeed / maxSpeed) * 240 - 120;
        angle = angle * PI / 180;

        sf::RectangleShape needle(sf::Vector2f(4, radius - 40));
        needle.setOrigin(2, radius - 40);
        needle.setPosition(center);
        needle.setRotation(angle * 180 / PI);
        needle.setFillColor(sf::Color::Red);
        window.draw(needle);

        sf::Text speedDisplay;
        speedDisplay.setFont(font);
        speedDisplay.setString(std::to_string((int)currentSpeed));
        speedDisplay.setCharacterSize(50);
        speedDisplay.setFillColor(sf::Color::White);
        speedDisplay.setPosition(center.x - 30, center.y + 80);
        window.draw(speedDisplay);

        for (auto& light : warningLights) {
            window.draw(light.shape);
            window.draw(light.label);
        }

        window.draw(minusButton.shape);
        window.draw(minusButton.label);
        window.draw(plusButton.shape);
        window.draw(plusButton.label);
        window.draw(manualButton.shape);
        window.draw(manualButton.label);
    }
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Digital Speedometer");
    window.setFramerateLimit(60);

    Speedometer speedometer(window);
    float speed = 0.0f;
    bool increasing = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

                if (speedometer.isButtonClicked(mousePos, speedometer.manualButton)) {
                    speedometer.toggleManualMode();
                }
                if (speedometer.isManualMode()) {
                    if (speedometer.isButtonClicked(mousePos, speedometer.plusButton)) {
                        speedometer.setSpeed(speedometer.currentSpeed + 10);
                    }
                    if (speedometer.isButtonClicked(mousePos, speedometer.minusButton)) {
                        speedometer.setSpeed(speedometer.currentSpeed - 10);
                    }
                }
            }
        }

        if (!speedometer.isManualMode()) {
            speed += (increasing ? 0.5f : -0.5f);
            increasing = (speed >= 240) ? false : (speed <= 0) ? true : increasing;
        }

        speedometer.setSpeed(speed);
        window.clear(sf::Color::Black);
        speedometer.draw();
        window.display();
    }

    return 0;
}
