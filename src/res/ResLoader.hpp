#ifndef RES_LOADER_HPP
#define RES_LOADER_HPP

#include <SFML/Graphics.hpp> 

class ResLoader{
public:
    ResLoader();

    sf::Texture tileset;
    sf::Texture player;

    void loadRessources();
};

#endif // RES_LOADER_HPP 