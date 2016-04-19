#include "Input.h"

const int TILES_ACROSS = 5;

/* Declare object pointers */
/* Intro */
orxOBJECT *currentIntro;
orxSOUND *currentSong;
orxSOUND *currentSound;

/* Menu */
orxOBJECT* menuBackground;
orxOBJECT* menuButtons;
orxOBJECT* menuArrow;

/* Player */
orxU64 gragthokID;
orxOBJECT *gragthokSword;
orxSPAWNER *gragthokSwordSpawner;
int gragthokLives = 2;
int gragthokHealth = 2;
int bossHealth = 9;

/* Level */
orxOBJECT *grassBackground;
orxOBJECT *bossBackground;
orxOBJECT *dummies;
orxOBJECT *boundaries;

/* Baddies */
BaddyHandler BoglinHandler;
orxOBJECT *boglinSpawner;
orxSOUND *boglinSpearFire;
orxOBJECT *minotaurSpawner;
orxOBJECT *boglinArcherSpawner;
orxOBJECT *dinosaurSpawner;
orxOBJECT *boss;

bool endState = false;
bool respawned = false;
bool startGame = true; // for main menu
bool restartGame = false; // for game over
bool continueSelected = false;
bool bossBackgroundSpawned = false;
bool bossSpawned = false;
bool gameRestarted = false;
bool bossHit = false;
bool spawnBaddies = false;
bool gragthokHit = false;

bool in::handleInput(){
	orxConfig_PushSection("GragthokVariables");
	orxFLOAT speed = orxConfig_GetFloat("GragthokSpeed");
	orxConfig_PopSection();
	
	orxVECTOR moveSpeed{0,0,0};
	
	
	/*Quit?*/
	if(orxInput_IsActive("Quit") && orxInput_HasNewStatus("Quit")){
		endState = true;
		sh::tearDownGame();
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
		startGame = true;
		orxObject_SetPosition(menuArrow, &newArrowPos);
	}
	if(orxInput_IsActive("GoDown") && orxInput_HasNewStatus("GoDown")){
		//move arrow down
		orxVECTOR newArrowPos = {0,8,0};
		startGame = false;
		orxObject_SetPosition(menuArrow, &newArrowPos);
	}
	
	if(orxInput_IsActive("Shoot") && orxInput_HasNewStatus("Shoot")){
		endState = true;
		orxObject_SetLifeTime(menuBackground, 0);
		orxObject_SetLifeTime(menuArrow, 0);
		orxObject_SetLifeTime(menuButtons, 0);
		if(!startGame){
			stackOfHolding.push(sh::killGame);
		}
	}
	return false;
}

bool in::handleGameOverInput(){
	if(orxInput_IsActive("GoUp") && orxInput_HasNewStatus("GoUp") && !continueSelected){
		//move arrow up
		orxVECTOR newArrowPos = {-18,0,0};
		restartGame = true;
		orxObject_SetPosition(menuArrow, &newArrowPos);
	}
	if(orxInput_IsActive("GoDown") && orxInput_HasNewStatus("GoDown") && !continueSelected){
		//move arrow down
		orxVECTOR newArrowPos = {-18,8,0};
		restartGame = false;
		orxObject_SetPosition(menuArrow, &newArrowPos);
		orxObject_SetTargetAnim(menuBackground, "GameOverRun");
	}
	
	if(orxInput_IsActive("Shoot") && orxInput_HasNewStatus("Shoot")){
		if(restartGame){
			orxObject_SetTargetAnim(menuBackground, "GameOverContinue");
			gragthokLives = 2;
			restartGame = false;
			continueSelected = true;
			stackOfHolding.push(sh::loadGrassLevel);
			stackOfHolding.push(sh::runGame);
		}
		else{
			endState = true;
			continueSelected = false;
			orxObject_SetLifeTime(menuBackground, 0);
			orxObject_SetLifeTime(menuArrow, 0);
			orxObject_SetLifeTime(menuButtons, 0);
			orxSound_Delete(currentSong);
			stackOfHolding.push(sh::killGame);
		}
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

bool in::bossHandler(){
	orxVECTOR grassPosition;
	orxObject_GetPosition(grassBackground, &grassPosition);
	if(grassPosition.fY > 0 && !bossBackgroundSpawned){
		spawnBaddies = false;
		bossBackgroundSpawned = true;
		bossBackground = orxObject_CreateFromConfig("DragonBackgroundObject");
		orxVECTOR start = {0,20,0};
		orxObject_SetSpeed(bossBackground, &start);
		orxVECTOR position = {0,-64,0};
		orxObject_SetPosition(bossBackground, &position);
	}
	if(bossBackgroundSpawned && !bossSpawned){
		orxVECTOR bossBackgroundPosition;
		orxObject_GetPosition(bossBackground, &bossBackgroundPosition);	
		if(bossBackgroundPosition.fY > 0){
			bossSpawned = true;
			orxVECTOR stop = {0,0,0};
			orxObject_SetSpeed(bossBackground, &stop);
			orxObject_SetTargetAnim(bossBackground, "DragonBackgroundBrokenRun");
			boss = orxObject_CreateFromConfig("DragonObject");
			orxSound_Delete(currentSong);
			currentSong = orxSound_CreateFromConfig("BossMusic");
			orxSound_Play(currentSong);
			
		}
	}
	return false;
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
		CheckGragthok(pstRecipientObject, pstSenderObject, senderObjectName, recipientObjectName);
		
	}
	
	return orxSTATUS_SUCCESS;
}

orxSTATUS orxFASTCALL in::AnimEventHandler(const orxEVENT *_pstEvent){
	
	const orxSTRING objectName = orxObject_GetName(orxOBJECT(_pstEvent->hRecipient));
	orxANIM_EVENT_PAYLOAD *pstPayload;
	pstPayload = (orxANIM_EVENT_PAYLOAD *)_pstEvent->pstPayload;
	
	if(in::CheckIntroAnimEnd(_pstEvent->eID, objectName, pstPayload->zAnimName)){
		endState = true;
		orxOBJECT *pstSenderObject = orxOBJECT(_pstEvent->hSender);
		orxObject_SetLifeTime(pstSenderObject, 0);
	}
	 
	return orxSTATUS_SUCCESS;
}

bool in::CheckIntroAnimEnd(int eID, const orxSTRING objectName, const orxSTRING animName){
	if(eID == orxANIM_EVENT_LOOP && orxString_Compare(objectName, "TeamLogoObject") == 0){
		return true;
	}
	if(eID == orxANIM_EVENT_LOOP && orxString_Compare(objectName, "OrxLogoObject") == 0){
		return true;
	}
	if(eID == orxANIM_EVENT_LOOP && orxString_Compare(objectName, "IntroObject") == 0){
		return true;
	}
	if(eID == orxANIM_EVENT_LOOP && orxString_Compare(objectName, "GrassCardObject") == 0){
		return true;
	}
	if(eID == orxANIM_EVENT_LOOP && orxString_Compare(objectName, "LiveScreenObject") == 0){
		return true;
	}
	if(eID == orxANIM_EVENT_LOOP && orxString_Compare(animName, "Invincible") == 0){
		gragthokHit = false;
		orxLOG("done?");
		orxObject_SetTargetAnim(orxOBJECT(orxStructure_Get(gragthokID)), "GragthokRun");
		return false;
	}
	if(eID == orxANIM_EVENT_LOOP && orxString_Compare(animName, "GameOverContinue") == 0){
		orxObject_SetLifeTime(menuBackground, 0);
		orxObject_SetLifeTime(menuArrow, 0);
		orxObject_SetLifeTime(menuButtons, 0);
		orxSound_Delete(currentSong);
		continueSelected = false;
		return true;
	}
	return false;
}

bool in::BoglinNameListCheck(orxSTRING objectName){
	if(orxString_Compare(objectName, "BoglinObjectLeft") == 0){
		return true;
	}
	else if(orxString_Compare(objectName, "BoglinObjectRight") == 0){
		return true;
	}
	else if(orxString_Compare(objectName, "BoglinObjectCenter") == 0){
		return true;
	}
	if(orxString_Compare(objectName, "BoglinArcherObjectLeft") == 0){
		return true;
	}
	else if(orxString_Compare(objectName, "BoglinArcherObjectRight") == 0){
		return true;
	}
	return false;
}

bool in::BoundaryNameListCheck(orxSTRING senderObjectName, orxSTRING recipientObjectName){
	if(orxString_Compare(senderObjectName, "BoundaryObjectTop") == 0 || orxString_Compare(recipientObjectName, "BoundaryObjectTop") == 0){
		return true;
	}
	else if(orxString_Compare(senderObjectName, "BoundaryObjectLeft") == 0 || orxString_Compare(recipientObjectName, "BoundaryObjectLeft") == 0){
		return true;
	}
	else if(orxString_Compare(senderObjectName, "BoundaryObjectRight") == 0 || orxString_Compare(recipientObjectName, "BoundaryObjectRight") == 0){
		return true;
	}
	else if(orxString_Compare(senderObjectName, "BoundaryObjectBottom") == 0 || orxString_Compare(recipientObjectName, "BoundaryObjectBottom") == 0){
		return true;
	}
	return false;
}

void in::CheckSwordAndBaddy(orxOBJECT *pstRecipientObject, orxOBJECT *pstSenderObject, orxSTRING senderObjectName, orxSTRING recipientObjectName){
	bossHit = false;
	if (orxString_Compare(senderObjectName, "SwordObject") == 0){
		in::CreateDeathSplatterAtObject(pstRecipientObject, (orxCHAR*)"DeathObject");
		orxOBJECT* baddyProj = (orxOBJECT*)orxObject_GetChild(pstRecipientObject);
		orxSPAWNER* baddyProjSpawner;
		if(orxString_Compare(recipientObjectName, "DragonHeadObject") == 0){
			if(bossHealth > 0 && !bossHit){
				bossHit = true;
				--bossHealth;
			}
			else{
				baddyProjSpawner = orxOBJECT_GET_STRUCTURE(baddyProj, SPAWNER);
				orxSpawner_Enable(baddyProjSpawner, false);
				orxObject_Enable(pstRecipientObject, false);
				orxObject_SetLifeTime(boss, 0);
				stackOfHolding.push(sh::loadGameDone);
				stackOfHolding.push(sh::runIntro);
				sh::tearDownGame();
				endState = true;
			}
		}
		else{
			orxObject_Enable(pstRecipientObject, false);
		}
		if(BoglinNameListCheck(recipientObjectName)){
			baddyProjSpawner = orxOBJECT_GET_STRUCTURE(baddyProj, SPAWNER);
			orxSpawner_Enable(baddyProjSpawner, false);
		}
		orxObject_SetLifeTime(pstSenderObject, 0);
	}
	
	if (orxString_Compare(recipientObjectName, "SwordObject") == 0){
		in::CreateDeathSplatterAtObject(pstSenderObject, (orxCHAR*)"DeathObject");
		orxOBJECT* baddyProj = (orxOBJECT*)orxObject_GetChild(pstSenderObject);
		orxSPAWNER* baddyProjSpawner;
		if(orxString_Compare(senderObjectName, "DragonHeadObject") == 0){
			if(bossHealth > 0 && !bossHit){
				bossHit = true;
				--bossHealth;
			}
			else{
				baddyProjSpawner = orxOBJECT_GET_STRUCTURE(baddyProj, SPAWNER);
				orxSpawner_Enable(baddyProjSpawner, false);
				orxObject_Enable(pstSenderObject, false);
				orxObject_SetLifeTime(boss, 0);
				stackOfHolding.push(sh::loadGameDone);
				stackOfHolding.push(sh::runIntro);
				sh::tearDownGame();
				endState = true;
			}
		}
		else{
			orxObject_Enable(pstSenderObject, false);
		}
		if(BoglinNameListCheck(senderObjectName)){
			baddyProjSpawner = orxOBJECT_GET_STRUCTURE(baddyProj, SPAWNER);
			orxSpawner_Enable(baddyProjSpawner, false);
		}
		
		orxObject_SetLifeTime(pstRecipientObject, 0);
	}
}


void in::CheckGragthok(orxOBJECT *pstRecipientObject, orxOBJECT *pstSenderObject, orxSTRING senderObjectName, orxSTRING recipientObjectName){
	if(!in::BoundaryNameListCheck(senderObjectName, recipientObjectName)){
		if(orxString_Compare(recipientObjectName, "GragthokObject") == 0){
			if(!gragthokHit){
				if(gragthokHealth){
					gragthokHit = true;
					orxObject_SetTargetAnim(orxOBJECT(orxStructure_Get(gragthokID)), "Invincible");
					--gragthokHealth;
					in::CreateDeathSplatterAtObject(pstSenderObject, (orxCHAR*)"DeathObject");
				}
				else{
					in::CreateDeathSplatterAtObject(pstRecipientObject, (orxCHAR*)"DeathObject");
					orxObject_SetLifeTime(pstRecipientObject, 0);
					sh::respawn();
				}
			}
			orxObject_SetLifeTime(pstSenderObject, 0);
		}
		if(orxString_Compare(senderObjectName, "GragthokObject") == 0){
			if(!gragthokHit){
				if(gragthokHealth){
					gragthokHit = true;
					orxObject_SetTargetAnim(orxOBJECT(orxStructure_Get(gragthokID)), "Invincible");
					--gragthokHealth;
					in::CreateDeathSplatterAtObject(pstRecipientObject, (orxCHAR*)"DeathObject");
				}
				else{
					in::CreateDeathSplatterAtObject(pstSenderObject, (orxCHAR*)"DeathObject");
					orxObject_SetLifeTime(pstSenderObject, 0);
					sh::respawn();
				}
			}
			orxObject_SetLifeTime(pstRecipientObject, 0);
		}
	}
}

void in::CreateDeathSplatterAtObject(orxOBJECT *object, orxSTRING exploderObjectName){	
	orxVECTOR objectVector;
	orxObject_GetWorldPosition(object, &objectVector);
	objectVector.fX = (int)objectVector.fX;
	objectVector.fY = (int)objectVector.fY;
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
		currentSong = orxSound_CreateFromConfig("IntroMusic");
		orxSound_Play(currentSong);
		
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
		
		currentSound = orxSound_CreateFromConfig("MainMenuClip");
		orxSound_Play(currentSound);
		
		return true;
	}
	bool sh::loadGrassCard(){
		endState = false;
		
		/* Create Grass Card Anim */
		currentIntro = orxObject_CreateFromConfig("GrassCardObject");
		
		/* Stop intro song */
		orxSound_Delete(currentSong);
		orxSound_Delete(currentSound);
		currentSound = orxSound_CreateFromConfig("FeralHighlandsClip");
		orxSound_Play(currentSound);
		
		return true;
	}
	bool sh::loadGrassLevel(){
		endState = false;
		respawned = false;
		gameRestarted = true;
		spawnBaddies = true;
		bossHealth = 9;
		gragthokHealth = 2;
		
		/* Displays a small hint in console */
		orxLOG("\nGragthok's Might 64!!!\n");
		
		/* Load Song */
		currentSong = orxSound_CreateFromConfig("GrassMusic");
		orxSound_Play(currentSong);
		
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
		orxVECTOR position = {0,-4736,0};k
		orxObject_SetPosition(grassBackground, &position);
		
		/* Set up Baddy Spawners */		
		boglinSpawner = orxObject_CreateFromConfig("BoglinSpawnerObject");		
		minotaurSpawner = orxObject_CreateFromConfig("MinotaurSpawnerObject");		
		boglinArcherSpawner = orxObject_CreateFromConfig("BoglinArcherSpawnerObject");		
		dinosaurSpawner = orxObject_CreateFromConfig("DinosaurSpawnerObject");
		
		/* Dummy Keep Alive Objects */
		dummies = orxObject_CreateFromConfig("DummyScene");
		boundaries = orxObject_CreateFromConfig("BoundaryScene");
		
		return true;
	}
	bool sh::loadLiveScreen(){
		endState = false;
		
		/* Create Intro Anim */
		currentIntro = orxObject_CreateFromConfig("LiveScreenObject");
		switch(gragthokLives){
			case 3:
				orxObject_SetTargetAnim(currentIntro, "LiveScreen3Run");
				break;
			case 2:
				orxObject_SetTargetAnim(currentIntro, "LiveScreen2Run");
				break;
			case 1:
				orxObject_SetTargetAnim(currentIntro, "LiveScreen1Run");
				break;
			case 0:
				orxObject_SetTargetAnim(currentIntro, "LiveScreen0Run");
				break;
			default:
				break;
		}
		
		return true;
	}
	bool sh::loadGameOver(){
		endState = false;
		
		/* Create Intro Anim */
		menuBackground = (orxOBJECT*)orxObject_CreateFromConfig("GameOverObject");
		menuButtons = (orxOBJECT*)orxObject_CreateFromConfig("GameOverButtonsObject");
		menuArrow = (orxOBJECT*)orxObject_CreateFromConfig("MenuArrowObject");
		
		/* Load Music */
		currentSong = orxSound_CreateFromConfig("GameOverMusic");
		orxSound_Play(currentSong);
		
		orxVECTOR newArrowPos = {-18,8,0};
		orxObject_SetPosition(menuArrow, &newArrowPos);
		orxObject_SetTargetAnim(menuBackground, "GameOverRun");
		
		return true;
	}
	bool sh::loadGameDone(){
		endState = false;
		
		currentSong = orxSound_CreateFromConfig("GameDoneMusic");
		orxSound_Play(currentSong);
		
		/* Create Intro Anim */
		currentIntro = orxObject_CreateFromConfig("GameDoneObject");
		
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
	bool sh::runGameOver(){
		in::handleGameOverInput();
		return endState;
	}
	bool sh::runGame(){
		in::handleInput();
		if(gameRestarted){
			in::bossHandler();
		}
		if(!spawnBaddies){
			orxObject_Enable(boglinSpawner, false);
			orxObject_Enable(minotaurSpawner, false);
			orxObject_Enable(dinosaurSpawner, false);
			orxObject_Enable(boglinArcherSpawner, false);
		}
		return endState;
	}
	bool sh::respawn(){
		if(!respawned){
			respawned = true;
			gameRestarted = false;
			if(gragthokLives > 0){
				--gragthokLives;
				//level resets respanwed
				stackOfHolding.push(sh::loadLiveScreen);
				stackOfHolding.push(sh::runIntro);
				stackOfHolding.push(sh::loadGrassLevel);
				stackOfHolding.push(sh::runGame);
				tearDownGame();
				endState = true;
			}
			else{
				stackOfHolding.push(sh::loadGameOver);
				stackOfHolding.push(sh::runGameOver);
				tearDownGame();
				endState = true;
			}
		}
		return false;
	}
	bool sh::tearDownGame(){
		//BoglinHandler.clearBaddies();
		orxObject_SetLifeTime(grassBackground, 0);
		orxObject_SetLifeTime(dummies, 0);
		orxSound_Delete(currentSong);
		if(bossSpawned && bossHealth > 0){
			orxObject_SetLifeTime(boss, 0);
			bossSpawned = false;
		}
		if(bossBackgroundSpawned){
			orxObject_SetLifeTime(bossBackground, 0);
			bossBackgroundSpawned = false;
		}
		orxObject_SetLifeTime(boglinSpawner, 0);
		orxObject_SetLifeTime(minotaurSpawner, 0);
		orxObject_SetLifeTime(boglinArcherSpawner, 0);
		orxObject_SetLifeTime(dinosaurSpawner, 0);
		if(orxStructure_Get(gragthokID) != orxNULL){
			orxObject_SetLifeTime(orxOBJECT(orxStructure_Get(gragthokID)), 0);
			orxObject_SetLifeTime(gragthokSword, 0);
			orxObject_SetLifeTime((orxOBJECT*)gragthokSwordSpawner, 0);
		}
		return false;
	}
	bool sh::killGame(){
		clearStack = true;
		return true;
	}