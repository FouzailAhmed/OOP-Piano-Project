// This file is a test to see if ur SFML and Mingw setup is correct

#include <SFML/Graphics.hpp>


int main() {

    sf::VideoMode videoMode(800, 600);
    sf::RenderWindow window(videoMode, "Move Rectangle with Arrow Keys");
    window.setFramerateLimit(60);

    // rectangle shape (size 100x50)
    sf::RectangleShape rectangle(sf::Vector2f(100.f, 50.f));

    // initial position
    rectangle.setPosition(350.f, 275.f); // Center of the window

    // color
    rectangle.setFillColor(sf::Color::Green);

    // speed
    float movementSpeed = 5.0f;


    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed){
                window.close();

            }


        }

        // Real-time input for moving the rectangle
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            rectangle.move(0.f, -movementSpeed);  //up

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            rectangle.move(0.f, movementSpeed);   //down

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            rectangle.move(-movementSpeed, 0.f); //left

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            rectangle.move(movementSpeed, 0.f);  //right

        }


        //Rectangle is a class, so calling getters for info

        //current position
        sf::Vector2f pos = rectangle.getPosition();  //(350.f, 275.f)

        //size
        sf::Vector2f size = rectangle.getSize();  // (100.f, 50.f)

        //horizontally
        if (pos.x + size.x < 0) {
            rectangle.setPosition(window.getSize().x, pos.y);  //

        } else if (pos.x > window.getSize().x) {  //
            rectangle.setPosition(-size.x, pos.y);

        }

        //vertically
        if (pos.y + size.y < 0) {
            rectangle.setPosition(pos.x, window.getSize().y);  //

        } else if (pos.y > window.getSize().y) {  //
            rectangle.setPosition(pos.x, -size.y);

        }
        



        window.clear();
        window.draw(rectangle);
        window.display();

    }

    return 0;


}