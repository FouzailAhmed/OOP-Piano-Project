

#include <SFML/Graphics.hpp>
#include "MultiScreens.hpp"
#include "FreePlayScreen.hpp"
#include "MainGameScreen.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(700, 600), "Piano Memory Challenge");
    window.setFramerateLimit(60);

    Scene* current = new WelcomeScene();

    while (window.isOpen()) {

        current->handleEvents(window);
        current->update();

        // Scene switching
        SceneID next = current->nextScene();
        if (next == FREEPLAY) {
            delete current;
            current = new FreePlayScreen();
        } 
        if (next == MAINGAME) {
            delete current;
            current = new MainGameScreen();
        } 
        else if (next == WELCOME) {
            delete current;
            current = new WelcomeScene();
        }
        current->resetNextScene();

        window.clear();
        current->draw(window);
        window.display();
    }

    delete current;
    return 0;
}
