#include "Game.hpp"
#include "Utils.hpp" 

ResLoader gameResLoader;

sf::Vector2f isoUnproject(float screenX, float screenZ) {
    float x = (screenX / 16.f + (screenZ + 16.f) / 8.f) / 2.f;
    float z = ((screenZ + 16.f) / 8.f - screenX / 16.f) / 2.f;
    return sf::Vector2f(x, z);
}

Game::Game(ResLoader resLoader)
    : window(sf::VideoMode(1280, 720), "Verdaterra v"+std::to_string(Utils::GAME_VERSION_MAJOR)+
    "."+std::to_string(Utils::GAME_VERSION_MINOR)+"."+std::to_string(Utils::GAME_VERSION_PATCH)), world(100, 3, 100) {
        gameResLoader = resLoader;
        player.setResLoader(gameResLoader);
        camera.setSize(1280 * 1.0f, 720 * 1.0f);
    } 

void Game::run() {
    sf::Clock clock;
    while(window.isOpen()) {
        float delta = clock.restart().asSeconds();
        processEvents(delta);
        update(delta);
        render();
    } 
} 

void buildTile(sf::RenderWindow &window, World world){
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldCoords = window.mapPixelToCoords(mousePos);  // <-- conversion ici

    sf::Vector2f tileCoords = isoUnproject(worldCoords.x, worldCoords.y);
    
    int tileX = static_cast<int>(tileCoords.x)-1;
    int tileZ = static_cast<int>(tileCoords.y);
    
    world.map.push_back({tileX, world.heightMap[tileX][tileZ]+1, tileZ, TileType::grass});
} 

void Game::processEvents(float deltaTime) {
    sf::Event event;
    while(window.pollEvent(event)) {
        if(event.type == sf::Event::Closed) { 
            window.close();
        } 

        if(event.type == sf::Event::MouseButtonPressed) {
            if(event.mouseButton.button == sf::Mouse::Button::Left){ 
                buildTile(window, world);  
            } 
        } 
        
        /**if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta > 0) { 
                zoomLevel -= ZOOM_SPEED;
            } else { 
                zoomLevel += ZOOM_SPEED;
            } 
            camera.setSize(1280 * zoomLevel, 720 * zoomLevel);
        }
        std::cout << "Zoom level: " << zoomLevel << std::endl;*/

    } 
    player.handleInput(deltaTime, world);
} 

void drawPointer(sf::RenderWindow &window, World world) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f worldCoords = window.mapPixelToCoords(mousePos);  // <-- conversion ici

    sf::Vector2f tileCoords = isoUnproject(worldCoords.x, worldCoords.y);
    
    int tileX = static_cast<int>(tileCoords.x)-1;
    int tileZ = static_cast<int>(tileCoords.y);
    
    world.drawTile(window, gameResLoader, tileX, 1, tileZ, TileType::selector);

    std::cout << "Mouse x: " << tileX << " y: " << tileZ << std::endl;
}


void Game::update(float deltaTime) {
    player.update(); 
    camera.setCenter(player.getPosition().x, player.getPosition().y-32);
} 

void Game::render() {
    window.clear(sf::Color::Black);
    window.setView(camera);

    world.draw(window, gameResLoader);

    player.draw(window);
    drawPointer(window, world);

    window.display();
} 