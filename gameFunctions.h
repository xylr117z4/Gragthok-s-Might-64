#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include "globalHeader.h"
#include "Player.h"

using json = nlohmann::json;

namespace gf{
	static std::vector<sf::Texture> textures;
	void initTextures(std::string textureFileLocation); //load textures
	void initPlayer(std::vector<Entity*> entities);
	void update(std::vector<Entity*> entities);
	void render();
}

#endif //GAMEFUNCTIONS_H