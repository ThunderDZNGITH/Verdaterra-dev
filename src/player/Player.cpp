#include "Player.hpp"
#include <SFML/Graphics.hpp>
#include <iostream> 

int direction = 0; // 0 -> forward  1 -> backward  2 -> left  3 -> right
float animationTimer = 0.0f;
int currentFrame = 0;

sf::Vector2f isoProject(float x, float y, float z) {
    float screenX = (x - z) * 32 / 2;
    float screenZ = (x + z) * 16 / 2 - (y * 16);
    return sf::Vector2f(screenX, screenZ);
}

Player::Player()
    : speed(5.0f), x(10), y(0), z(10), position(isoProject(x, y, z)) {
}

void Player::setResLoader(ResLoader loader){
    resLoader = loader;
    sprite.setTexture(resLoader.player);
    std::cout << "Player tex loaded" << std::endl;
    sprite.setTextureRect(sf::IntRect(5*32, 0, 32, 64));
    sprite.setOrigin(sf::Vector2f(16, 58));
} 

void Player::handleInput(float deltaTime) {
    float moveStep = speed * deltaTime;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { 
        speed = 4.0f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { 
        speed = 3.0f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { 
        speed = 3.0f;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { 
        speed = 4.0f;
    } else {
        speed = 5.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) { 
        speed = 8.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
        direction = 0;
        z -= moveStep;

        animationTimer += deltaTime;
        if (animationTimer >= 0.25f) {
            currentFrame = (currentFrame + 1) % 4;
            animationTimer = 0.0f;
        }

        sprite.setTextureRect(sf::IntRect(4*32+currentFrame*32 , 0, 32, 64));
    } 

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        direction = 1;
        z += moveStep;

        animationTimer += deltaTime;
        if (animationTimer >= 0.25f) {
            currentFrame = (currentFrame + 1) % 4;
            animationTimer = 0.0f;
        }

        sprite.setTextureRect(sf::IntRect(currentFrame*32 , 64, 32, 64));
    } 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { 
        direction = 2;
        x -= moveStep;

        animationTimer += deltaTime;
        if (animationTimer >= 0.25f) {
            currentFrame = (currentFrame + 1) % 4;
            animationTimer = 0.0f;
        }

        sprite.setTextureRect(sf::IntRect(4*32+currentFrame*32 , 64, 32, 64));
    } 
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { 
        direction = 3;
        x += moveStep;

        animationTimer += deltaTime;
        if (animationTimer >= 0.25f) {
            currentFrame = (currentFrame + 1) % 4;
            animationTimer = 0.0f;
        }

        sprite.setTextureRect(sf::IntRect(currentFrame*32 , 0, 32, 64));
    } 
 
    position = isoProject(x, y, z); 
    //std::cout << "Player pos x: "+std::to_string(x)+" y: "+std::to_string(y)+" z: "+std::to_string(z) << std::endl;
}

void Player::update() {
    sprite.setPosition(position);
}

void Player::draw(sf::RenderWindow &window) {
    sf::RectangleShape test;
    test.setFillColor(sf::Color::Red);
    test.setSize(sf::Vector2f(10, 10));
    test.setPosition(sf::Vector2f(sprite.getPosition().x, sprite.getPosition().y));

    window.draw(sprite);
    //window.draw(test);
}

sf::Vector2f Player::getPosition() {
    return position;
}
