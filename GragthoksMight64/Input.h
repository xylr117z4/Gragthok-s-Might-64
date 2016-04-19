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
	bool bossHandler();
	void orxFASTCALL CanShoot(const orxCLOCK_INFO *_pstInfo, void *_pContext);
	orxSTATUS orxFASTCALL PhysicsEventHandler(const orxEVENT *_pstEvent);
	orxSTATUS orxFASTCALL AnimEventHandler(const orxEVENT *_pstEvent);
	bool CheckIntroAnimEnd(int eID, const orxSTRING objectName, const orxSTRING animName);
	void CreateDeathSplatterAtObject(orxOBJECT *object, orxSTRING exploderObjectName);
	void CheckSwordAndBaddy(orxOBJECT *pstRecipientObject, orxOBJECT *pstSenderObject, orxSTRING senderObjectName, orxSTRING recipientObjectName);
	bool BoglinNameListCheck(orxSTRING objectName);
	bool BoundaryNameListCheck(orxSTRING senderObjectName, orxSTRING recipientObjectName);
	void CheckGragthok(orxOBJECT *pstRecipientObject, orxOBJECT *pstSenderObject, orxSTRING senderObjectName, orxSTRING recipientObjectName);
	void SpawnRandomBaddies();
}

namespace sh{
	//inits
	bool loadIntro();
	bool loadTeamLogo();
	bool loadOrxLogo();
	bool loadMenu();
	bool loadGrassCard();
	bool loadGrassLevel();
	bool loadLiveScreen();
	bool loadGameOver();
	bool loadGameDone();
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
