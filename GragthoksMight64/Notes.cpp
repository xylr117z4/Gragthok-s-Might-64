/* example of how my state stack would work */

/* Resources.h */

class Resources{
  std::vector<orx64U> objectIDs;
  
};

/* game functions.h */

namespace gf{
  bool runGame(Resources gameResources);
  bool loadGame(Resources gameResources);
  bool runMenu(Resources menuResources);
  bool loadMenu(Resources menuResources);
  bool runIntro(Resources introResources);
  bool loadIntro(Resources introResources);
}



/* main.cpp */

static std::stack<std::tuple<std::function<bool(Resources)>, int>> stateStack;

void init(){
  stateStack.push(std::make_tuple(gf::runGame, 5));
  stateStack.push(std::make_tuple(gf::loadGame, 4));
  stateStack.push(std::make_tuple(gf::runMenu, 3));
  stateStack.push(std::make_tuple(gf::loadMenu, 2));
  stateStack.push(std::make_tuple(gf::runIntro, 1));
  stateStack.push(std::make_tuple(gf::loadIntro, 0));
}

int main(){
  sf::RenderWindow window(/* video mode stuff */);
  std::vector<Resources> resources;
  init();
  resources.reserve(stateStack.size());
  
  /* while window is open run the function on the top of the stack */
  while(window.isOpen()){
    
    /* if function returns true it's completed */
    if(std::get<0>(stateStack.top())(resrouces[std::get<1>(stateStack.top())]){
      
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
