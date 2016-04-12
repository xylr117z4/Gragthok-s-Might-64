#ifndef BADDYHANDLER_H
#define BADDYHANDLER_H

#include "orx.h"
#include <iostream>
#include <vector>

class BaddyHandler
{
public:
	BaddyHandler();
	std::vector<orxU64> baddies;
	void spawnBaddy(std::string type, orxVECTOR location);
	void clearBaddies();
	~BaddyHandler();

};

#endif // BADDYHANDLER_H
