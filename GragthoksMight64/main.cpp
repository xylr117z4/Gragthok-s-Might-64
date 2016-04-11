#include "orx.h"
#include "Input.h"
#include "BaddyHandler.h"
#include <stack>
#include <functional>

/* Declare State Stack */
std::stack<std::function<bool()>> stateStack;

orxSTATUS orxFASTCALL Init(){
	stateStack.push_back(sh::runGame());
	stateStack.push_back(sh::loadGame());
	stateStack.push_back(sh::runMenu());
	stateStack.push_back(sh::loadMenu());
	stateStack.push_back(sh::runIntro());
	stateStack.push_back(sh::loadIntro());
	
	/*
		#include <iostream>
		#include <stack>
		#include <functional>
		#include <deque>
		#include <vector>
		#include <conio.h>

		void sayHello(){
			std::cout << "Hello!! \n\n";
		}

		void sayGoodbye(){
			std::cout << "Goodbye!! \n\n";
		}

		int _tmain(int argc, _TCHAR* argv[])
		{
			std::stack<std::function<void()>> stateStack;
			stateStack.push(sayGoodbye);
			stateStack.push(sayHello);
			stateStack.top()();
			stateStack.pop();
			stateStack.top()();
			_getch();
			return 0;
		}
	*/
	
	/* Done! */
	return orxSTATUS_SUCCESS;
}

/** Run function
*/
orxSTATUS orxFASTCALL Run(){
	
	orxSTATUS eResult = orxSTATUS_SUCCESS;
	
	if(stateStack.top()()){
		stateStack.pop();
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
