#include "Game.hpp"
#include "res/ResLoader.hpp" 
int main(){

    ResLoader resLoader;
    resLoader.loadRessources();

    Game game(resLoader);
    game.run();
    return 0;
} 