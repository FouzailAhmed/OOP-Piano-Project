\


#ifndef MULTISCENES_HPP
#define MULTISCENES_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include <SFML/Audio.hpp>
#include <vector>
#include <cmath>

class WelcomeScene : public Scene {
private:
    sf::Font font;
    sf::Text title;

    Button startBtn;
    Button freeBtn;
    Button exitBtn;

    sf::RectangleShape gradient;

    std::vector<sf::CircleShape> particles;
    float glowTimer = 0;

    sf::Music bgMusic;

    SceneID next = NONE;   

public:
    WelcomeScene() {

        // Load font
        font.loadFromFile("arial.ttf");

        // Title styling
        title.setFont(font);
        title.setString("PIANO MEMORY");
        title.setCharacterSize(52);
        title.setFillColor(sf::Color::White);
        sf::FloatRect t = title.getLocalBounds();
        title.setOrigin(t.width / 2, t.height / 2);
        title.setPosition(350, 80);

        // Background gradient
        gradient.setSize({700, 600});
        gradient.setFillColor(sf::Color(40, 20, 90));

        // Particles
        for (int i = 0; i < 12; i++) {
            sf::CircleShape c(5 + rand() % 5);
            c.setFillColor(sf::Color(255, 255, 255, 40));
            c.setPosition(rand() % 700, rand() % 600);
            particles.push_back(c);
        }

        // Buttons
        startBtn = Button({300, 70}, {200, 200}, font, "Start Game");
        freeBtn  = Button({300, 70}, {200, 300}, font, "Free Play");
        exitBtn  = Button({300, 70}, {200, 400}, font, "Exit");

        // Background Music
        if (bgMusic.openFromFile("soft-piano.wav")) {
            bgMusic.setLoop(true);
            bgMusic.setVolume(30);
            bgMusic.play();
        }
    }

    void handleEvents(sf::RenderWindow& window) {
        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();


            if (freeBtn.isClicked(window, event)) {
                next = FREEPLAY;                                 // triggers scene switch
            }
            if (startBtn.isClicked(window, event)) {
                next = MAINGAME;                                 // triggers scene switch
            }

            if (exitBtn.isClicked(window, event)) {
                window.close();
            }
        }

        // Hover effects
        startBtn.setHoverColor(startBtn.isHovered(window));
        freeBtn.setHoverColor(freeBtn.isHovered(window));
        exitBtn.setHoverColor(exitBtn.isHovered(window));
    }

    void update() {
        glowTimer += 0.03f;
        float glow = 180 + std::sin(glowTimer) * 75;
        title.setFillColor(sf::Color(glow, glow, 255));

        for (auto& p : particles) {
            sf::Vector2f pos = p.getPosition();
            pos.y -= 0.2f;
            if (pos.y < -10) pos.y = 620;
            p.setPosition(pos);
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(gradient);

        for (auto& p : particles)
            window.draw(p);

        window.draw(title);
        startBtn.draw(window);
        freeBtn.draw(window);
        exitBtn.draw(window);
    }

    SceneID nextScene() override { return next; }
    void resetNextScene() override { next = NONE; }
};

#endif
