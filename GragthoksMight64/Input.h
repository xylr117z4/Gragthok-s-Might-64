#ifndef INPUT_H
#define INPUT_H

#include "orx.h"
#include <iostream>
#include <vector>
#include <sstream>

namespace in{
	static bool canShoot = true;
	extern orxOBJECT *gragthok;
	bool handleInput(orxSTATUS& eResult, int gragthokID, orxOBJECT* gragthokSword, orxSPAWNER* gragthokSwordSpawner);
	void orxFASTCALL CanShoot(const orxCLOCK_INFO *_pstInfo, void *_pContext);
	orxSTATUS orxFASTCALL PhysicsEventHandler(const orxEVENT *_pstEvent);
	void CreateDeathSplatterAtObject(orxOBJECT *object, orxSTRING exploderObjectName);
	void CheckSwordAndBaddy(orxOBJECT *pstRecipientObject, orxOBJECT *pstSenderObject, orxSTRING senderObjectName, orxSTRING recipientObjectName);
	void CheckSpearAndGragthok(orxOBJECT *pstRecipientObject, orxOBJECT *pstSenderObject, orxSTRING senderObjectName, orxSTRING recipientObjectName);
	void CheckBoglinAndGragthok(orxOBJECT *pstRecipientObject, orxOBJECT *pstSenderObject, orxSTRING senderObjectName, orxSTRING recipientObjectName);
}

namespace sh{
	/* Declare object pointers */
	/* Player */
	orxU64 gragthokID;
	orxOBJECT *gragthokSword;
	orxSPAWNER *gragthokSwordSpawner;
	/* Baddies */
	BaddyHandler BoglinHandler;
	
	//inits
	bool loadIntro();
	bool loadMenu();
	bool loadGame();
	//runs
	bool runIntro();
	bool runMenu();
	bool runGame();
}

namespace rd{
	void loadMap(std::string mapName);
}

#endif // INPUT_H
