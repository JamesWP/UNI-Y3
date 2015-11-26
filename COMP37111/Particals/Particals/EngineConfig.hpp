//
//  EngineConfig.hpp
//  Particals
//
//  Created by James Peach on 09/11/2015.
//  Copyright © 2015 James Peach. All rights reserved.
//

#ifndef EngineConfig_hpp
#define EngineConfig_hpp

#include <stdio.h>
#include <string>

typedef enum State{
  MOVE_EMMITTER, GRAVITY_CHANGE
} EngineState;

std::string getStateString(EngineState s);
EngineState getNextState(EngineState s);

class EngineConfig {
private:
  float width = 4.0;
  float height = 4.0;
  EngineState engineState = MOVE_EMMITTER;
public:
  float getPointWidth(){ return width;}
  float getPointHeight(){ return height;}

  void setPointWidth(float newWidth){ width = newWidth;}
  void setPointHeight(float newHeight){ height = newHeight;}

  EngineState getCurentState(){return engineState;}
  bool inState(EngineState s){return s==engineState;}
  void nextState(){engineState = getNextState(engineState);}
  std::string getStateMsg(){return getStateString(engineState);}
};

#endif /* EngineConfig_hp */