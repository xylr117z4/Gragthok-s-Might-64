#include "Entity.h"

Entity::Entity(){
	
}

void Entity::update(float elapsed){
}

void Entity::animate(float elapsed){
	frameCounter += elapsed;
	if(frameCounter <= frameTime){
		frame = 1;
		sprite.setTextureRect(sf::IntRect(9,0,9,9));
	}
	else if(frameCounter <= frameTime*2){
		frame = 2;
		sprite.setTextureRect(sf::IntRect(18,0,9,9));
	}
	else if(frameCounter <= frameTime*3 || frameCounter > frameTime*3){
		frame = 0;
		frameCounter = 0;
		sprite.setTextureRect(sf::IntRect(0,0,9,9));
	}
}

Entity::~Entity(){
	
}