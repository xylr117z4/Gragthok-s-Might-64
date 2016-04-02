#include "Player.h"

Player::Player(){
	
}

void Player::update(float elapsed){
	float e = 1/60;
	if(sf::Keyboard::isKeyDown(sf::Keyboard::W)){
		sprite.move(0,-speed*e);
	}
	if(sf::Keyboard::isKeyDown(sf::Keyboard::S)){
		sprite.move(0,speed*e);
	}
	if(sf::Keyboard::isKeyDown(sf::Keyboard::A)){
		sprite.move(-speed*e,0);
	}
	if(sf::Keyboard::isKeyDown(sf::Keyboard::D)){
		sprite.move(speed*e,0);
	}
	animate(elapsed);
}

void Player::animate(float elapsed){
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

Player::~Player(){
	
}