#pragma once

#include <SFML/Graphics.hpp>
#include "world/World.hpp" 
#include "player/Player.hpp"
#include "res/ResLoader.hpp"  


class Game {
public:
    Game(ResLoader resLoader);
    void run();

    sf::RenderWindow window;
    World world;
    Player player;

    sf::View camera;

private:

    float zoomLevel = 1.0f;
    const float ZOOM_SPEED = 0.1f;

    void processEvents(float deltaTime);
    void update(float deltaTime);
    void render();
};