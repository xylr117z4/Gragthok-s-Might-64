/* example of how my state stack would work */

/* game functions.h */

namespace gf{
  bool runGame();
  bool loadGame();
  bool runMenu();
  bool loadMenu();
  bool runIntro();
  bool loadIntro();
}



/* main.cpp */

static std::stack<function<bool()>> stateStack;

void init(){
  stateStack.push(runGame);
  stateStack.push(loadGame);
  stateStack.push(runMenu);
  stateStack.push(loadMenu);
  stateStack.push(runIntro);
  stateStack.push(loadIntro);
}

int main(){
  sf::RenderWindow window(/* video mode stuff */);

  init();
  
  /* while window is open run the function on the top of the stack */
  while(window.isOpen()){
    
    /* if function returns true it's completed */
    if(stateStack.top()()){
      
      /* there for pop off the function */
      stateStack.pop();
      
      /* see if there's another function on the stack */
      if(stateStack.empty()){

        /* if not close the window */
        window.close();
      }

    }
  }
  return 0;
}

/* I'll likely need to make modifications to the std::function<bool()> and make it a std::function<bool(Resources)>
so that I can store and easily reference everything in that state. then have a teardown & pause menthod... */
