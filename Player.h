#ifndef PLAYER_H
#define PLAYER_H

#include "globalHeader.h"

class Player{
	public:
		Player();
		sf::Sprite sprite;
		sf::Vector2f size;
		float speed;
		float frameTime;
		int frame;
		//Sword!!!
		void update(float elapsed);
		void animate(float elapsed);
		
		~Player();
};

#endif //PLAYER_H