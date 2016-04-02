#include "orx.h"

orxSTATUS orxFASTCALL Init(){
	  /* Displays a small hint in console */
	  orxLOG("\nGragthok's Might 64!!!\n");

	  /* Creates viewport */
	  orxViewport_CreateFromConfig("Viewport");

	  /* Creates object */
	  orxObject_CreateFromConfig("Object");

	  /* Done! */
	  return orxSTATUS_SUCCESS;
}

/** Run function
 */
orxSTATUS orxFASTCALL Run(){
	  orxSTATUS eResult = orxSTATUS_SUCCESS;

	  /* Should quit? */
	  if(orxInput_IsActive("Quit"))
	  {
		/* Updates result */
		eResult = orxSTATUS_FAILURE;
	  }

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
