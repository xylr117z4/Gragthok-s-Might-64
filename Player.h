#ifndef PLAYER_H
#define PLAYER_H

#include "globalHeader.h"

class Player{
	public:
		Player();
		sf::Sprite sprite;
		sf::Vector2f size;
		float speed;
		//Sword!!!
		void update();
		
		~Player();
};

#endif //PLAYER_H