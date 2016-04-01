#include "globalHeader.h"
#include "mainFunctions.h"
#include "Player.h"

int main(){
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
	std::vector<Entity> entities;
	
	initTextures("listOfTextures.json");
	initPlayer(entities);
    
    while (window.isOpen()){
        
		gf::update();
		
        //Render functions
        window.clear();
		gf::render();
        window.display();
    }
    return EXIT_SUCCESS;
}
