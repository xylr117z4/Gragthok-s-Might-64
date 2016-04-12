#include "BaddyHandler.h"

BaddyHandler::BaddyHandler(){
}

void BaddyHandler::spawnBaddy(std::string type, orxVECTOR location){
	baddies.push_back(orxStructure_GetGUID(orxObject_CreateFromConfig(type.c_str())));
	orxObject_SetPosition(orxOBJECT(orxStructure_Get(baddies[baddies.size()-1])), &location);
}

void BaddyHandler::clearBaddies(){
	for(unsigned int i = 0; i < baddies.size(); ++i){
		if(orxStructure_Get(baddies[i]) != orxNULL){
			orxObject_SetLifeTime(orxOBJECT(orxStructure_Get(baddies[i])), 0);
		}
	}
	baddies.empty();
}

BaddyHandler::~BaddyHandler(){
}

