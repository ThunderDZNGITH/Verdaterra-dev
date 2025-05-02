#include "World.hpp"

sf::Vector2i World::isoProject(int x, int y, int z) {
    int screenX = (x - z) * tileSize / 2;
    int screenZ = (x + z) * tileDepth / 2 - (y * tileDepth);
    return sf::Vector2i(screenX, screenZ);
}

World::World(int world_max_x, int world_max_y, int world_max_z)
    : world_max_x(world_max_x), world_max_y(world_max_y), world_max_z(world_max_z) {
    
        std::random_device rd;
        std::mt19937 gen(rd()); // Générateur Mersenne Twister
    
        // Distribution uniforme entre 1 et 100
        std::uniform_int_distribution<> distrib(1, 100);
    
        // Générer un nombre
        int random_number = distrib(gen);
    
        FastNoiseLite noise;
        noise.SetNoiseType(FastNoiseLite::NoiseType_ValueCubic);
        noise.SetSeed(random_number);
        noise.SetFrequency(0.08f);

    for (int x = 0; x < world_max_x; ++x) {
        for (int z = 0; z < world_max_z; ++z) {
            float noiseValue = noise.GetNoise((float)x, (float)z);
            int height = static_cast<int>((noiseValue + 1.0f) * 10);
            World::map.push_back({x, height, z, TileType::grass});
            heightMap[x][z] = height;   
        }
    }
    World::map.push_back({1, 2, 1, TileType::grass});
} 

void World::draw(sf::RenderWindow &window, ResLoader resLoader){
    for (auto& tile : map) {
        sf::Vector2f pos = static_cast<sf::Vector2f>(isoProject(tile.x, tile.y, tile.z));

        sf::Sprite sprite(resLoader.tileset);
        switch(tile.type) {
            case TileType::grass:
                sprite.setTextureRect(sf::IntRect(0 * tileSize, 0 * tileSize, tileSize, tileSize));
                break;
            default:
                break;
        } 
        sprite.setPosition(pos); // centrage

        window.draw(sprite);
    }
} 

void World::drawTile(sf::RenderWindow &window, ResLoader resLoader, int x, int y, int z, TileType type){
    sf::Vector2f pos = static_cast<sf::Vector2f>(isoProject(x, y, z));

    heightMap[x][z] = heightMap[x][z]+1;   

    sf::Sprite sprite(resLoader.tileset);
    switch(type) {
        case TileType::selector:
            sprite.setTextureRect(sf::IntRect(5 * tileSize, 0 * tileSize, tileSize, tileSize));
            break;
        default:
            break;
    }

    sprite.setPosition(pos); // centrage

    window.draw(sprite);
} 