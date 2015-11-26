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
#include <SFML/Graphics.hpp>
#include "Consts.h"

typedef enum State{
  MOVE_EMMITTER, GRAVITY_CHANGE
} EngineState;

std::string getStateString(EngineState s);
EngineState getNextState(EngineState s);

class EngineConfig {
private:
  float width = 4.0;
  float height = 4.0;
  sf::Vector2i mPos = sf::Vector2i(0,HEIGHT/2 + 100);
  EngineState engineState = MOVE_EMMITTER;
public:
  float getPointWidth(){ return width;}
  float getPointHeight(){ return height;}
  sf::Vector2i getMousePosition(){return mPos;}

  void setPointWidth(float newWidth){ width = newWidth;}
  void setPointHeight(float newHeight){ height = newHeight;}
  void setMousePosition(const sf::Vector2i newMPos){ mPos = newMPos;}

  EngineState getCurentState(){return engineState;}
  bool inState(EngineState s){return s==engineState;}
  void nextState(){engineState = getNextState(engineState);}
  std::string getStateMsg(){return getStateString(engineState);}
};

#endif /* EngineConfig_hp */