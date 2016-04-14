#include "orx.h"
#include "Input.h"
#include "BaddyHandler.h"
#include <stack>
#include <functional>

/* Please read the included dbad-license.txt file in full before altering any code. */
std::stack<std::function<bool()>> stateStack;
std::stack<std::function<bool()>> stackOfHolding;
bool clearStack = false;

orxSTATUS orxFASTCALL Init(){
	/* Creates viewport */
	orxViewport_CreateFromConfig("Viewport");
	orxViewport_CreateFromConfig("ScreenViewport");
	
	/* Watch for ending animations */
	orxEvent_AddHandler(orxEVENT_TYPE_ANIM, in::AnimEventHandler);
	
	stateStack.push(sh::runGame);
	stateStack.push(sh::loadGrassLevel);
	stateStack.push(sh::runIntro);
	stateStack.push(sh::loadGrassCard);
	stateStack.push(sh::runMenu);
	stateStack.push(sh::loadMenu);
	stateStack.push(sh::runIntro);
	stateStack.push(sh::loadIntro);
	stateStack.push(sh::runIntro);
	stateStack.push(sh::loadOrxLogo);
	stateStack.push(sh::runIntro);
	stateStack.push(sh::loadTeamLogo);
	
	/* Done! */
	return orxSTATUS_SUCCESS;
}

/** Run function
*/
orxSTATUS orxFASTCALL Run(){
	
	orxSTATUS eResult = orxSTATUS_SUCCESS;
	
	if(stateStack.top()()){
		stateStack.pop();
		
		while(!stackOfHolding.empty()){
			stateStack.push(stackOfHolding.top());
			stackOfHolding.pop();
		}
		
		if(clearStack){
			while(!stateStack.empty()){
				stateStack.pop();
			}
		}
		
		if(stateStack.empty()){
			return orxSTATUS_FAILURE;
		}
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
