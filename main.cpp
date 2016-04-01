#include "globalHeader.h"
#include "mainFunctions.h"
#include "Player.h"

int main(){
    // Create the main window & set up view to upscale the 64x64 game by a factor of 10.
    sf::RenderWindow window(sf::VideoMode(640, 640), "SFML window");
    sf::View mainView(sf::FloatRect(0, 0, 64, 64));
    window.setView(mainView);
    std::vector<Entity> entities;
    initTextures("listOfTextures.json");
    initPlayer(entities);
    
    while (window.isOpen()){
        
		//update units, projectiles and background
		gf::update(elapsed);
		
        //Render functions
        window.clear();
		gf::render();
        window.display();
    }
    return EXIT_SUCCESS;
}
