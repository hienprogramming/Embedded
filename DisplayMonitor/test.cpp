#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(400, 400), "Circle Drawing");

    sf::CircleShape circle(100);
    circle.setFillColor(sf::Color::White);
    circle.setOutlineThickness(1);
    circle.setOutlineColor(sf::Color::Blue);
    circle.setPosition(100, 100);  // Vị trí vòng tròn

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);
        window.draw(circle);
        window.display();
    }

    return 0;
}
