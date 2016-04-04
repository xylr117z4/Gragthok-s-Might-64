#ifndef INPUT_H
#define INPUT_H

#include "orx.h"
#include <iostream>
#include <vector>
#include <sstream>

namespace in{
	static bool canShoot = true;
	void handleInput(orxSTATUS& eResult, orxOBJECT* gragthok, orxOBJECT* gragthokSword, orxSPAWNER* gragthokSwordSpawner);
	void orxFASTCALL CanShoot(const orxCLOCK_INFO *_pstInfo, void *_pContext);
	orxSTATUS orxFASTCALL PhysicsEventHandler(const orxEVENT *_pstEvent);
	void CreateDeathSplatterAtObject(orxOBJECT *object, orxSTRING exploderObjectName);
	void CheckSwordAndBaddy(orxOBJECT *pstRecipientObject, orxOBJECT *pstSenderObject, orxSTRING senderObjectName, orxSTRING recipientObjectName);
}

namespace rd{
	void loadMap(std::string mapName);
}

#endif // INPUT_H
