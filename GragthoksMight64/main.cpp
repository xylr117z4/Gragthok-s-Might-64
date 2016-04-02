#include "orx.h"
#include "Input.h"

/*Declare object pointers*/
/*Player*/
orxOBJECT *gragthok;
orxOBJECT *gragthokSword;
orxSPAWNER *gragthokSwordSpawner;

orxSTATUS orxFASTCALL Init(){
	/* Displays a small hint in console */
	orxLOG("\nGragthok's Might 64!!!\n");

	/* Creates viewport */
	orxViewport_CreateFromConfig("Viewport");

	/* Creates Character */
	gragthok = orxObject_CreateFromConfig("GragthokObject");
	gragthokSword = (orxOBJECT*)orxObject_GetChild(gragthok);
	gragthokSwordSpawner = orxOBJECT_GET_STRUCTURE(gragthokSword, SPAWNER);
	orxObject_Enable(gragthokSword, orxFALSE);
	orxSpawner_Enable(gragthokSwordSpawner, orxFALSE);

	/* Create Tile Map */
	orxObject_CreateFromConfig("SandObject");
	
	/* Dummy Keep Alive Objects */
	orxObject_CreateFromConfig("SwordObjectDummy");

	/* Done! */
	return orxSTATUS_SUCCESS;
}

/** Run function
*/
orxSTATUS orxFASTCALL Run(){
	
	orxSTATUS eResult = orxSTATUS_SUCCESS;
	
	in::handleInput(eResult, gragthok, gragthokSword, gragthokSwordSpawner);

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
