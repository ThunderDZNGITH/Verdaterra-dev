#pragma once
#include <SFML/Graphics.hpp> 
#include "Tile.hpp" 
#include "../res/ResLoader.hpp"  
#include "FastNoiseLite.h"
#include <iostream> 
#include <random> 

class World {
public:
    World(int world_max_x, int world_max_y, int world_max_z);
    void update(float deltaTime);
    void draw(sf::RenderWindow &window, ResLoader resLoader);
    void drawTile(sf::RenderWindow &window, ResLoader resLoader, int x, int y, int z, TileType type);
    sf::Vector2i isoProject(int x, int y, int z);

    int heightMap[100][100] = {0};
    Tile tileMap[100][4][100] = {false};        

    ResLoader resLoader;

    std::vector<Tile> map;
private:
    int world_max_x;
    int world_max_y;
    int world_max_z;

    int tileSize = 32;
    int tileDepth = 16;
};