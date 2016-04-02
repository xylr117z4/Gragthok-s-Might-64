#include "Input.h"

void in::handleInput(orxSTATUS& eResult, orxOBJECT* gragthok, orxOBJECT* gragthokSword, orxSPAWNER* gragthokSwordSpawner){
	orxConfig_PushSection("GragthokVariables");
	orxFLOAT speed = orxConfig_GetFloat("GragthokSpeed");
	orxConfig_PopSection();
	
	orxVECTOR moveSpeed{0,0,0};
	
	
	/*Quit?*/
	if(orxInput_IsActive("Quit")){
		eResult = orxSTATUS_FAILURE;
	}
	
	/*Movement*/
	if(orxInput_IsActive("GoUp")){
		moveSpeed.fY = -speed;
	}
	if(orxInput_IsActive("GoDown")){
		moveSpeed.fY = speed;
	}
	if(orxInput_IsActive("GoLeft")){
		moveSpeed.fX = -speed;
	}
	if(orxInput_IsActive("GoRight")){
		moveSpeed.fX = speed;
	}
	orxObject_SetSpeed(gragthok, &moveSpeed);
	
	
	/*Sword*/
	if(orxInput_IsActive("Shoot")){
		orxObject_Enable(gragthokSword, orxTRUE);
		orxSpawner_Enable(gragthokSwordSpawner, orxTRUE);
	}
	else{
		orxObject_Enable(gragthokSword, orxFALSE);
		orxSpawner_Enable(gragthokSwordSpawner, orxFALSE);
		orxSpawner_Reset(gragthokSwordSpawner);
	}
	
	/*Abilities*/
}
