#ifndef INPUT_H
#define INPUT_H

#include "orx.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <stack>
#include <functional>
#include "BaddyHandler.h"

extern std::stack<std::function<bool()>> stateStack;
extern std::stack<std::function<bool()>> stackOfHolding;
extern bool clearStack;

namespace in{
	static bool canShoot = true;
	bool handleInput();
	bool handleMenuInput();
	bool handleGameOverInput();
	bool handleIntroInput();
	void orxFASTCALL CanShoot(const orxCLOCK_INFO *_pstInfo, void *_pContext);
	orxSTATUS orxFASTCALL PhysicsEventHandler(const orxEVENT *_pstEvent);
	orxSTATUS orxFASTCALL AnimEventHandler(const orxEVENT *_pstEvent);
	bool CheckIntroAnimEnd(int eID, const orxSTRING animName);
	void CreateDeathSplatterAtObject(orxOBJECT *object, orxSTRING exploderObjectName);
	void CheckSwordAndBaddy(orxOBJECT *pstRecipientObject, orxOBJECT *pstSenderObject, orxSTRING senderObjectName, orxSTRING recipientObjectName);
	void CheckSpearAndGragthok(orxOBJECT *pstRecipientObject, orxOBJECT *pstSenderObject, orxSTRING senderObjectName, orxSTRING recipientObjectName);
	void CheckBoglinAndGragthok(orxOBJECT *pstRecipientObject, orxOBJECT *pstSenderObject, orxSTRING senderObjectName, orxSTRING recipientObjectName);
}

namespace sh{
	//inits
	bool loadIntro();
	bool loadTeamLogo();
	bool loadOrxLogo();
	bool loadMenu();
	bool loadGrassCard();
	bool loadGrassLevel();
	bool loadGameOver();
	//runs
	bool runIntro();
	bool runMenu();
	bool runGame();
	bool runGameOver();
	bool respawn();
	bool tearDownGame();
	//kill
	bool killGame();
}

#endif // INPUT_H
