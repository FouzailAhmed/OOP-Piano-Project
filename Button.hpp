

#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>

class Button {
private:
    sf::RectangleShape shape;
    sf::Text text;

public:
    Button() {}

    Button(sf::Vector2f size, sf::Vector2f position, const sf::Font& font, const std::string& label) {
        shape.setSize(size);
        shape.setPosition(position);
        shape.setFillColor(sf::Color(70, 70, 70));

        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);

        // Center text
        sf::FloatRect bounds = text.getLocalBounds();
        text.setOrigin(bounds.width / 2, bounds.height / 2);
        text.setPosition(position.x + size.x / 2, position.y + size.y / 2 - 5);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
        window.draw(text);
    }

    bool isHovered(sf::RenderWindow& window) {
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        return shape.getGlobalBounds().contains(mouse.x, mouse.y);
    }

    bool isClicked(sf::RenderWindow& window, sf::Event event) {
        if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left) 
        {
            return isHovered(window);
        }
        return false;
    }

    void setHoverColor(bool hover) {
        if (hover)
            shape.setFillColor(sf::Color(90, 90, 90));
        else
            shape.setFillColor(sf::Color(70, 70, 70));
    }
};

#endif

