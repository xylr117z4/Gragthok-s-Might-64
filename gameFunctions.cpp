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

void gf::initPlayer(std::vector<Entity*> entities){
	entities.emplace_back(new Player());
	(*entities[0])->sprite.setTexture(textures[0]);
	(*entities[0])->sprite.setTextureRect(sf::IntRect(0,0,9,9));
	(*entities[0])->sprite.setOrigin(9/2,9/2);
	(*entities[0])->sprite.setPosition(32, 59.5);
	(*entities[0])->size = sf::Vector2f(9, 9);
	(*entities[0])->speed = 10;
	//with raw pointers user delete !
}

void gf::update(std::vector<Entity*> entities, float elapsed){
	for(unsigned int i = 0; i < entities.size(); ++i){
		//update player
		if(entities[i].type == 0){
			(*entities[i])->update(elapsed);
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