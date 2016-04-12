#include "Input.h"

const int TILES_ACROSS = 5;

/* Declare object pointers */
/* Intro */
orxOBJECT *currentIntro;

/* Menu */
orxOBJECT* menuBackground;
orxOBJECT* menuButtons;
orxOBJECT* menuArrow;

/* Player */
orxU64 gragthokID;
orxOBJECT *gragthokSword;
orxSPAWNER *gragthokSwordSpawner;

/* Level */
orxOBJECT *grassBackground;
orxOBJECT *dummies;

/* Baddies */
BaddyHandler BoglinHandler;

bool endState = false;

bool in::handleInput(){
	orxConfig_PushSection("GragthokVariables");
	orxFLOAT speed = orxConfig_GetFloat("GragthokSpeed");
	orxConfig_PopSection();
	
	orxVECTOR moveSpeed{0,0,0};
	
	
	/*Quit?*/
	if(orxInput_IsActive("Quit") && orxInput_HasNewStatus("Quit")){
		endState = true;
		BoglinHandler.clearBaddies();
		orxObject_SetLifeTime(grassBackground, 0);
		orxObject_SetLifeTime(dummies, 0);
		if(orxStructure_Get(gragthokID) != orxNULL){
			orxObject_SetLifeTime(orxOBJECT(orxStructure_Get(gragthokID)), 0);
			orxObject_SetLifeTime(gragthokSword, 0);
			orxObject_SetLifeTime((orxOBJECT*)gragthokSwordSpawner, 0);
		}
	}
	
	/*Movement*/
	bool moving = false;
	
	if(orxInput_IsActive("GoUp")){
		moveSpeed.fY = -speed;
		moving = true;
	}
	if(orxInput_IsActive("GoDown")){
		moveSpeed.fY = speed;
		moving = true;
	}
	if(orxInput_IsActive("GoLeft")){
		moveSpeed.fX = -speed;
		moving = true;
	}
	if(orxInput_IsActive("GoRight")){
		moveSpeed.fX = speed;
		moving = true;
	}
	if(!moving){
		moveSpeed.fX = 0;
		moveSpeed.fY = 0;
	}
	
	if(orxOBJECT(orxStructure_Get(gragthokID)) != orxNULL){
		orxObject_SetSpeed(orxOBJECT(orxStructure_Get(gragthokID)), &moveSpeed);
	
		/*Sword*/
		if(orxInput_IsActive("Shoot") && canShoot){
			orxObject_Enable(gragthokSword, orxTRUE);
			orxSpawner_Enable(gragthokSwordSpawner, orxTRUE);
		}
		if(!orxInput_IsActive("Shoot") && orxInput_HasNewStatus("Shoot")){
			orxObject_Enable(gragthokSword, orxFALSE);
			orxSpawner_Reset(gragthokSwordSpawner);
			if(canShoot){
				canShoot = false;
				orxClock_AddGlobalTimer(in::CanShoot, 0.5f, 1, orxNULL);
			}
		}
	}
	
	/*Abilities*/
	
	return false;
}

bool in::handleMenuInput(){	
	if(orxInput_IsActive("GoUp") && orxInput_HasNewStatus("GoUp")){
		//move arrow up
		orxVECTOR newArrowPos = {0,0,0};
		orxObject_SetPosition(menuArrow, &newArrowPos);
	}
	if(orxInput_IsActive("GoDown") && orxInput_HasNewStatus("GoDown")){
		//move arrow down
		orxVECTOR newArrowPos = {0,8,0};
		orxObject_SetPosition(menuArrow, &newArrowPos);
	}
	
	if(orxInput_IsActive("Shoot") && orxInput_HasNewStatus("Shoot")){
		endState = true;
		orxObject_SetLifeTime(menuBackground, 0);
		orxObject_SetLifeTime(menuArrow, 0);
		orxObject_SetLifeTime(menuButtons, 0);
	}
	return false;
}

bool in::handleIntroInput(){
	if((orxInput_IsActive("Shoot") && orxInput_HasNewStatus("Shoot")) || (orxInput_IsActive("Quit") && orxInput_HasNewStatus("Quit"))){
		endState = true;
		orxObject_SetLifeTime(currentIntro, 0);
	}
	return false;
}

void orxFASTCALL in::CanShoot(const orxCLOCK_INFO *_pstInfo, void *_pContext){
	canShoot = true;
}

orxSTATUS orxFASTCALL in::PhysicsEventHandler(const orxEVENT *_pstEvent){
	if (_pstEvent->eID == orxPHYSICS_EVENT_CONTACT_ADD) {
		orxOBJECT *pstRecipientObject, *pstSenderObject;
	 
		pstSenderObject = orxOBJECT(_pstEvent->hSender);
		pstRecipientObject = orxOBJECT(_pstEvent->hRecipient);
	 
		orxSTRING senderObjectName = (orxSTRING)orxObject_GetName(pstSenderObject);
		orxSTRING recipientObjectName = (orxSTRING)orxObject_GetName(pstRecipientObject);
		
		//checks for sword hitting baddies
		CheckSwordAndBaddy(pstRecipientObject, pstSenderObject, senderObjectName, recipientObjectName);
		
		//checks for baddies hitting gragthok
		CheckBoglinAndGragthok(pstRecipientObject, pstSenderObject, senderObjectName, recipientObjectName);
		CheckSpearAndGragthok(pstRecipientObject, pstSenderObject, senderObjectName, recipientObjectName);
	}
	
	return orxSTATUS_SUCCESS;
}

orxSTATUS orxFASTCALL in::AnimEventHandler(const orxEVENT *_pstEvent){
	orxANIM_EVENT_PAYLOAD *pstPayload;
	 
	pstPayload = (orxANIM_EVENT_PAYLOAD *)_pstEvent->pstPayload;
	
	const orxSTRING animName = orxObject_GetName(orxOBJECT(_pstEvent->hRecipient));
	
	if(in::CheckIntroAnimEnd(_pstEvent->eID, animName)){
		endState = true;		
		orxOBJECT *pstSenderObject = orxOBJECT(_pstEvent->hSender);
		orxObject_SetLifeTime(pstSenderObject, 0);
	}
 
	/*switch(_pstEvent->eID){
	  case orxANIM_EVENT_START:
		orxLOG("Animation <%s>@<%s> has started!", pstPayload->zAnimName, animName);
		break;
	 
	  case orxANIM_EVENT_STOP:
		orxLOG("Animation <%s>@<%s> has stoped!", pstPayload->zAnimName, animName);
		break;
	 
	  case orxANIM_EVENT_CUT:
		orxLOG("Animation <%s>@<%s> has been cut!", pstPayload->zAnimName, animName);
		break;
	 
	  case orxANIM_EVENT_LOOP:
		orxLOG("Animation <%s>@<%s> has looped!", pstPayload->zAnimName, animName);
		break;
	  }*/
	 
	  return orxSTATUS_SUCCESS;
}

bool in::CheckIntroAnimEnd(int eID, const orxSTRING animName){
	if(eID == orxANIM_EVENT_LOOP && orxString_Compare(animName, "TeamLogoObject") == 0){
		return true;
	}
	if(eID == orxANIM_EVENT_LOOP && orxString_Compare(animName, "OrxLogoObject") == 0){
		return true;
	}
	if(eID == orxANIM_EVENT_LOOP && orxString_Compare(animName, "IntroObject") == 0){
		return true;
	}
	if(eID == orxANIM_EVENT_LOOP && orxString_Compare(animName, "GrassCardObject") == 0){
		return true;
	}
}

void in::CheckSwordAndBaddy(orxOBJECT *pstRecipientObject, orxOBJECT *pstSenderObject, orxSTRING senderObjectName, orxSTRING recipientObjectName){
	if (orxString_Compare(senderObjectName, "SwordObject") == 0){
		in::CreateDeathSplatterAtObject(pstRecipientObject, "DeathObject");
		orxObject_SetLifeTime(pstSenderObject, 0);
		orxObject_SetLifeTime(pstRecipientObject, 0);
	}
	
	if (orxString_Compare(recipientObjectName, "SwordObject") == 0){
		in::CreateDeathSplatterAtObject(pstSenderObject, "DeathObject");
		orxObject_SetLifeTime(pstSenderObject, 0);
		orxObject_SetLifeTime(pstRecipientObject, 0);
	}
}

void in::CheckSpearAndGragthok(orxOBJECT *pstRecipientObject, orxOBJECT *pstSenderObject, orxSTRING senderObjectName, orxSTRING recipientObjectName){
	if (orxString_Compare(senderObjectName, "SpearObject") == 0 && orxString_Compare(recipientObjectName, "GragthokObject") == 0){
		in::CreateDeathSplatterAtObject(pstRecipientObject, "DeathObject");
		orxObject_SetLifeTime(pstSenderObject, 0);
		orxObject_SetLifeTime(pstRecipientObject, 0);
	}
	
	if (orxString_Compare(recipientObjectName, "SpearObject") == 0 && orxString_Compare(senderObjectName, "GragthokObject") == 0){
		in::CreateDeathSplatterAtObject(pstSenderObject, "DeathObject");
		orxObject_SetLifeTime(pstSenderObject, 0);
		orxObject_SetLifeTime(pstRecipientObject, 0);
	}
}


void in::CheckBoglinAndGragthok(orxOBJECT *pstRecipientObject, orxOBJECT *pstSenderObject, orxSTRING senderObjectName, orxSTRING recipientObjectName){
	if (orxString_Compare(senderObjectName, "BoglinObject") == 0 && orxString_Compare(recipientObjectName, "GragthokObject") == 0){
		in::CreateDeathSplatterAtObject(pstRecipientObject, "DeathObject");
		orxObject_SetLifeTime(pstRecipientObject, 0);
	}
	
	if (orxString_Compare(recipientObjectName, "BoglinObject") == 0 && orxString_Compare(senderObjectName, "GragthokObject") == 0){
		in::CreateDeathSplatterAtObject(pstSenderObject, "DeathObject");
		orxObject_SetLifeTime(pstSenderObject, 0);
	}
}

void in::CreateDeathSplatterAtObject(orxOBJECT *object, orxSTRING exploderObjectName){	
	orxVECTOR objectVector;
	orxObject_GetWorldPosition(object, &objectVector);
	objectVector.fX = (int)objectVector.fX;
	objectVector.fY = (int)objectVector.fY;
	std::cout << objectVector.fX << ", " << objectVector.fY << "\n\n";
	objectVector.fZ = 0.0;
	
	orxOBJECT *deathSplatter = orxObject_CreateFromConfig("DeathObject");
	orxObject_SetPosition(deathSplatter, &objectVector);
}

//inits
	bool sh::loadIntro(){
		endState = false;
		
		/* Create Intro Anim */
		currentIntro = orxObject_CreateFromConfig("IntroObject");
		
		return true;
	}
	bool sh::loadTeamLogo(){
		endState = false;
		
		/* Create Intro Anim */
		currentIntro = orxObject_CreateFromConfig("TeamLogoObject");
		
		return true;
	}
	bool sh::loadOrxLogo(){
		endState = false;
		
		/* Create Intro Anim */
		currentIntro = orxObject_CreateFromConfig("OrxLogoObject");
		
		return true;
	}
	bool sh::loadMenu(){
		endState = false;
		
		menuBackground = (orxOBJECT*)orxObject_CreateFromConfig("MenuObject");
		menuButtons = (orxOBJECT*)orxObject_CreateFromConfig("MenuButtonsObject");
		menuArrow = (orxOBJECT*)orxObject_CreateFromConfig("MenuArrowObject");
		
		return true;
	}
	bool sh::loadGrassCard(){
		endState = false;
		
		/* Create Grass Card Anim */
		currentIntro = orxObject_CreateFromConfig("GrassCardObject");
	}
	bool sh::loadGrassLevel(){
		endState = false;
		
		/* Displays a small hint in console */
		orxLOG("\nGragthok's Might 64!!!\n");
		
		/* Set up collision handler */
		orxEvent_AddHandler(orxEVENT_TYPE_PHYSICS, in::PhysicsEventHandler);

		/* Creates Character */
		gragthokID = orxStructure_GetGUID(orxObject_CreateFromConfig("GragthokObject"));
		
		gragthokSword = (orxOBJECT*)orxObject_GetChild(orxOBJECT(orxStructure_Get(gragthokID)));
		gragthokSwordSpawner = orxOBJECT_GET_STRUCTURE(gragthokSword, SPAWNER);
		orxObject_Enable(gragthokSword, orxFALSE);
		orxSpawner_Reset(gragthokSwordSpawner);

		/* Create Tile Map */
		grassBackground = orxObject_CreateFromConfig("GrassMap");
		orxVECTOR position = {0,-8336,0};
		orxObject_SetPosition(grassBackground, &position);
		
		/*Spawn Baddies:
		  I'll likely put this VVV function inside the BaddyHandler and have it use a for loop
		  to spawn everything. */
		orxVECTOR boglinSpawn = {27,-12,0};
		BoglinHandler.spawnBaddy("BoglinObject", boglinSpawn);
		
		boglinSpawn = {7,-12,0};
		BoglinHandler.spawnBaddy("BoglinObject", boglinSpawn);
		
		boglinSpawn = {45,-12,0};
		BoglinHandler.spawnBaddy("BoglinObject", boglinSpawn);
		
		/* Dummy Keep Alive Objects */
		dummies = orxObject_CreateFromConfig("Scene");
		
		return true;
	}
//runs
	bool sh::runIntro(){
		in::handleIntroInput();
		return endState;
	}
	bool sh::runMenu(){
		in::handleMenuInput();
		return endState;
	}
	bool sh::runGame(){
		in::handleInput();
		return endState;
	}
