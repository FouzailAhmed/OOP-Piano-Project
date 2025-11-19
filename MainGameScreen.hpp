#ifndef MAINGAMESCREEN_HPP
#define MAINGAMESCREEN_HPP

#include "Screen.hpp"
#include "Button.hpp"
#include <vector>


class MainGameScreen : public Scene {

private:

    sf::Font font;
    sf::Text title;

    struct PianoKey {

        sf::RectangleShape rect;
        bool black;                  //is the key black or white
        bool hovered = false;
        bool pressed = false;

    };

    std::vector<PianoKey> whiteKeys;                // 7
    std::vector<PianoKey> blackKeys;                // 5

    Button backBtn;

    sf::RectangleShape gradient;
    std::vector<sf::CircleShape> particles;         

    SceneID goTo = NONE;

public:

    MainGameScreen() {

        // FONT + TITLE
        font.loadFromFile("arial.ttf");
        title.setFont(font);
        title.setString("Main Game Mode");
        title.setCharacterSize(42);
        title.setFillColor(sf::Color::White);

        sf::FloatRect tb = title.getLocalBounds();
        title.setOrigin(tb.width / 2, tb.height / 2);
        title.setPosition(350, 60);

        // BACK BUTTON (top-left)
        backBtn = Button({100, 50}, {20, 20}, font, "Quit");

        // BACKGROUND
        gradient.setSize({700, 600});
        gradient.setFillColor(sf::Color(40, 20, 90));

        // Particles
        for (int i = 0; i < 10; i++) {

            sf::CircleShape c(5 + rand() % 4);
            c.setFillColor(sf::Color(255, 255, 255, 40));
            c.setPosition(rand() % 700, rand() % 600);
            particles.push_back(c);

        }


        float wWidth = 700;
        float whiteH = 240;
        float y = 330;

        float whiteW = wWidth / 7.0f;    // Perfect fit
        float blackW = whiteW * 0.6f;
        float blackH = whiteH * 0.6f;

        // WHITE KEYS (C, D, E, F, G, A, B)
        for (int i = 0; i < 7; i++) {

            PianoKey k;
            k.black = false;

            k.rect.setSize({whiteW, whiteH});
            k.rect.setPosition(i * whiteW, y);
            k.rect.setFillColor(sf::Color(250, 250, 255));

            k.rect.setOutlineThickness(2);
            k.rect.setOutlineColor(sf::Color::Black);                         //Black outline for white keys

            whiteKeys.push_back(k);

        }

        // BLACK KEYS (C#, D#, F#, G#, A#)
        int blackIndexMap[5] = {0, 1, 3, 4, 5};  

        for (int i : blackIndexMap) {

            PianoKey k;
            k.black = true;

            float center = i * whiteW + whiteW;                     // Center between two white keys

            k.rect.setSize({blackW, blackH});
            k.rect.setPosition(center - blackW / 2, y);
            k.rect.setFillColor(sf::Color(30, 30, 30));

            k.rect.setOutlineThickness(2);
            k.rect.setOutlineColor(sf::Color::Black);                       //Black outline for black keys   

            blackKeys.push_back(k);

        }


    }

    // EVENT HANDLING
    void handleEvents(sf::RenderWindow& window) {

        sf::Event event;

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed){
                window.close();
            }

            if (backBtn.isClicked(window, event)) {
                goTo = WELCOME;
                
            }
            

            // Click detection
            if (event.type == sf::Event::MouseButtonPressed) {

                sf::Vector2i m = sf::Mouse::getPosition(window);

                for (auto& k : blackKeys){

                    if (k.rect.getGlobalBounds().contains(m.x, m.y)){
                        k.pressed = true;

                    }

                }

                        
                for (auto& k : whiteKeys){

                    if (k.rect.getGlobalBounds().contains(m.x, m.y)){
                        k.pressed = true;

                    }

                }


            }

        }

        // Hover detection
        sf::Vector2i m = sf::Mouse::getPosition(window);

        // Blacks first (they overlap)
        for (auto& k : blackKeys){
            k.hovered = k.rect.getGlobalBounds().contains(m.x, m.y);
        }
            

        for (auto& k : whiteKeys){
            k.hovered = k.rect.getGlobalBounds().contains(m.x, m.y);
        }

        backBtn.setHoverColor(backBtn.isHovered(window));


    }

    // UPDATE COLORS
    void update() {

        // White keys
        for (auto& k : whiteKeys) {

            if (k.pressed){
                k.rect.setFillColor(sf::Color(190, 190, 240));       //Darker Blue            

            }else if (k.hovered){
                k.rect.setFillColor(sf::Color(220, 220, 255));       //Lighter Blue


            }else{

                k.rect.setFillColor(sf::Color(250, 250, 255));       //White Default

            } // Closing the else block for whiteKeys
        } // Closing the for loop for whiteKeys

        // Black keys
        for (auto& k : blackKeys) {

            if (k.pressed){
                k.rect.setFillColor(sf::Color(90, 90, 110));     //Lighter Charcoal

            }else if (k.hovered){
                k.rect.setFillColor(sf::Color(50, 50, 60));      //Grayish Charcoal
            
            
            }else{

                k.rect.setFillColor(sf::Color(30, 30, 30));      //Default Charcoal
            }

            k.pressed = false;

        }

        // Move particles slowly
        for (auto& p : particles) {

            sf::Vector2f pos = p.getPosition();
            pos.y -= 0.18f;
            if (pos.y < -10) pos.y = 620;
            p.setPosition(pos);

        }
    }

    // DRAW Order:

    // Background, Particles, Glow bars, Title + Back Button, White Keys, Black Keys

    void draw(sf::RenderWindow& window) {
        
        window.draw(gradient);

        for (const auto& particle : particles) {
            window.draw(particle);
        }

        for (const auto& key : whiteKeys) {
            window.draw(key.rect);
        }

        for (const auto& key : blackKeys) {
            window.draw(key.rect);
        }

        window.draw(title);
        backBtn.draw(window);
        
    } 

}; 

#endif
