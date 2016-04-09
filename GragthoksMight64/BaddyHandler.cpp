#include "BaddyHandler.h"

BaddyHandler::BaddyHandler(){
}

void BaddyHandler::spawnBaddy(std::string type, orxVECTOR location){
	baddies.push_back(orxStructure_GetGUID(orxObject_CreateFromConfig(type.c_str())));
	orxObject_SetPosition(orxOBJECT(orxStructure_Get(baddies[baddies.size()-1])), &location);
}

BaddyHandler::~BaddyHandler(){
}

