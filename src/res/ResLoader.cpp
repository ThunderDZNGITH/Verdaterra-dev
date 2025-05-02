#include "ResLoader.hpp"
#include <iostream> 

ResLoader::ResLoader(){

} 

void ResLoader::loadRessources(){
    if (!tileset.loadFromFile("assets/IsoTiles.png")) {
        std::cout << "Can't load texture : assets/IsoTiles.png" << std::endl;
        return;
    }
    if (!player.loadFromFile("assets/player.png")) {
        std::cout << "Can't load texture : assets/player.png" << std::endl;
        return;
    }

    std::cout << "All ressources loaded without error." << std::endl;
} 