#ifndef ENTITY_H
#define ENTITY_H

#include "globalHeader.h"

class Entity{
	public:
		Entity();
		sf::Sprite sprite;
		sf::Vector2f size;
		float speed;
		float frameTime;
		int frame;
		
		virtual void update(float elapsed);
		void animate(float elapsed);
		
		~Entity();
};

#endif //ENTITY_H