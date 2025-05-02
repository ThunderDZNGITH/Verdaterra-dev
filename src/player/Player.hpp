#pragma once
#include <SFML/Graphics.hpp>
#include "../world/World.hpp" 
#include "../res/ResLoader.hpp"  

class Player {
public:

    void setResLoader(ResLoader loader);

    Player();
    void handleInput(float deltaTime, World world);
    void update();
    void draw(sf::RenderWindow &window);
    sf::Vector2f getPosition();

    ResLoader resLoader;

private:
    float speed;

    sf::Sprite sprite;
    sf::Texture texture;
    float x, y, z;
    sf::Vector2f position;
};
