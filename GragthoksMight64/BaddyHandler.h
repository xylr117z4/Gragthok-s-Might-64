#ifndef BADDYHANDLER_H
#define BADDYHANDLER_H

#include "orx.h"
#include <iostream>

class BaddyHandler
{
public:
	BaddyHandler();
	static void spawnBaddy(std::string type, orxVECTOR location);
	~BaddyHandler();

};

#endif // BADDYHANDLER_H
