#include "orx.h"
#include "Input.h"
#include "BaddyHandler.h"

/*Declare object pointers*/
/*Player*/
orxU64 gragthokID;
orxOBJECT *gragthokSword;
orxSPAWNER *gragthokSwordSpawner;

BaddyHandler BoglinHandler;

orxSTATUS orxFASTCALL Init(){
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
	  to spawn everything.*/
	orxVECTOR boglinSpawn = {27,-12,0};
	BoglinHandler.spawnBaddy("BoglinObject", boglinSpawn);
	
	boglinSpawn = {7,-12,0};
	BoglinHandler.spawnBaddy("BoglinObject", boglinSpawn);
	
	boglinSpawn = {45,-12,0};
	BoglinHandler.spawnBaddy("BoglinObject", boglinSpawn);
	
	/* Dummy Keep Alive Objects */
	orxObject_CreateFromConfig("Scene");

	/* Done! */
	return orxSTATUS_SUCCESS;
}

/** Run function
*/
orxSTATUS orxFASTCALL Run(){
	
	orxSTATUS eResult = orxSTATUS_SUCCESS;
	
	in::handleInput(eResult, gragthokID, gragthokSword, gragthokSwordSpawner);

	/* Done! */
	return eResult;
}

/** Exit function
*/
void orxFASTCALL Exit(){
	/* We're a bit lazy here so we let orx clean all our mess! :) */
}

/** Main function
*/
int main(int argc, char **argv){
	/* Executes a new instance of tutorial */
	orx_Execute(argc, argv, Init, Run, Exit);
	
	return EXIT_SUCCESS;
}
