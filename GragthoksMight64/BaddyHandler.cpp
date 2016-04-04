#include "BaddyHandler.h"

BaddyHandler::BaddyHandler(){
}

void BaddyHandler::spawnBaddy(std::string type, orxVECTOR location){
	orxOBJECT *baddy;
	baddy = orxObject_CreateFromConfig(type.c_str());
	orxObject_SetPosition(baddy, &location);
}

BaddyHandler::~BaddyHandler(){
}

