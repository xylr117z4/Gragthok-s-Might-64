#include "Input.h"

const int TILES_ACROSS = 5;

bool in::handleInput(){
	orxConfig_PushSection("GragthokVariables");
	orxFLOAT speed = orxConfig_GetFloat("GragthokSpeed");
	orxConfig_PopSection();
	
	orxVECTOR moveSpeed{0,0,0};
	
	
	/*Quit?*/
	if(orxInput_IsActive("Quit")){
		eResult = orxSTATUS_FAILURE;
		return true;
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
		return true;
	}
	bool sh::loadMenu(){
		return true;
	}
	bool sh::loadGame(){
		/* Displays a small hint in console */
		orxLOG("\nGragthok's Might 64!!!\n");

		/* Creates viewport */
		orxViewport_CreateFromConfig("Viewport");
		orxViewport_CreateFromConfig("ScreenViewport");
		
		/* Set up collision handler */
		orxEvent_AddHandler(orxEVENT_TYPE_PHYSICS, in::PhysicsEventHandler);

		/* Creates Character */
		gragthokID = orxStructure_GetGUID(orxObject_CreateFromConfig("GragthokObject"));
		std::cout << gragthokID << "\n\n-------------------------\n";
		
		gragthokSword = (orxOBJECT*)orxObject_GetChild(orxOBJECT(orxStructure_Get(gragthokID)));
		gragthokSwordSpawner = orxOBJECT_GET_STRUCTURE(gragthokSword, SPAWNER);
		orxObject_Enable(gragthokSword, orxFALSE);
		orxSpawner_Reset(gragthokSwordSpawner);

		/* Create Tile Map */
		rd::loadMap("GrassMap");
		
		/*Spawn Baddies:
		  I'll likely put this VVV function inside the BaddyHandler and have it use a for loop
		  to spawn everything.
		orxVECTOR boglinSpawn = {27,-12,0};
		BoglinHandler.spawnBaddy("BoglinObject", boglinSpawn);
		
		boglinSpawn = {7,-12,0};
		BoglinHandler.spawnBaddy("BoglinObject", boglinSpawn);
		
		boglinSpawn = {45,-12,0};
		BoglinHandler.spawnBaddy("BoglinObject", boglinSpawn);*/
		
		/* Dummy Keep Alive Objects */
		orxObject_CreateFromConfig("Scene");
		
		return true;
	}
//runs
	bool sh::runIntro(){
		bool done = false;
		
		if(done){
			return true;
		}
	}
	bool sh::runMenu(){
		bool done = false;
		
		if(done){
			return true;
		}
	}
	bool sh::runGame(){
		bool done = false;
		
		done = in::handleInput();
		
		if(done){
			return true;
		}
	}

void rd::loadMap(std::string mapName){
	orxOBJECT *map;
	map = orxObject_CreateFromConfig(mapName.c_str());
	orxVECTOR position = {0,-8336,0};
	orxObject_SetPosition(map, &position);
	
}
