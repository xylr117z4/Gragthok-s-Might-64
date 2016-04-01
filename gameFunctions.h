#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include "globalHeader.h"
#include "Player.h"

using json = nlohmann::json;

struct Entity{
	union unit{
		Player player;
		//Boglin boglin;
		//Octoeye octoeye;
	}
	int type;
	//0 = Player, 1 = Boglin, 2 = Octoeye...
};

namespace gf{
	static std::vector<sf::Texture> textures;
	void initTextures(std::string textureFileLocation); //load textures
	void initPlayer(std::vector<Entity>& entities);
	void update(std::vector<Entity>& entities);
	void render();
}

#endif //GAMEFUNCTIONS_H