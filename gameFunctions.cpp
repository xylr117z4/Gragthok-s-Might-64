#include "gameFunctions.h"

void gf::initTextures(std::string textureFileLocation){
	
	json listOfTextures;
	ifstream listOfTexturesSource(textureFileLocation);
	listOfTexturesSource >> listOfTextures;
	
	for(unsigned int i = 0; i < listOfTextures.size(); ++i){
		std::stringstream ss;
		sf::Texture temp;
		ss << i;
		temp.loadFromFile(listOfTextures[ss.str()]);
		textures.push_back(temp);
	}
}

void gf::initPlayer(std::vector<Entity>& entities){
	Player temp;
	temp.setTexture(textures[0]);
	temp.size = sf::Vector2f(9, 9);
	temp.speed = 10;
	entities.emplace_back();
	entities[entities.back()].unit = temp;
}

void gf::update(std::vector<Entity>& entities){
	for(unsigned int i = 0; i < entities.size(); ++i){
		//update player
		if(entities[i].type == 0){
			entities[i].unit.player.update();
		}
		
		/*//update boglin
		else if(entities[i].type == 1){
			entities[i].unit.boglin.update();
		}
		
		//update boglin
		else if(entities[i].type == 2){
			entities[i].unit.octoeye.update();
		}*/
	}
}

void gf::render(){
	
}