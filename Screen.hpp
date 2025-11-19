// #ifndef SCENE_HPP
// #define SCENE_HPP

// #include <SFML/Graphics.hpp>

// class Scene {
// public:
//     virtual ~Scene() {}
//     virtual void handleEvents(sf::RenderWindow& window) = 0;
//     virtual void update() = 0;
//     virtual void draw(sf::RenderWindow& window) = 0;
// };

// #endif

#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SFML/Graphics.hpp>

enum SceneID {
    NONE,
    WELCOME,
    FREEPLAY,
    MAINGAME
};

class Scene {
public:
    virtual ~Scene() {}
    virtual void handleEvents(sf::RenderWindow& window) = 0;
    virtual void update() = 0;
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual SceneID nextScene() { return NONE; }  
    virtual void resetNextScene() {}              
};

#endif


