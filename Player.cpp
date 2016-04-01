#include "Player.h"

Player::Player(){
	
}

void Player::update(){
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
}

Player::~Player(){
	
}