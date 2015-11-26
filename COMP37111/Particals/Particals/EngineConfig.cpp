//
//  EngineConfig.cpp
//  Particals
//
//  Created by James Peach on 09/11/2015.
//  Copyright © 2015 James Peach. All rights reserved.
//

#include "EngineConfig.hpp"



std::string getStateString(State s){
  switch (s){
    case MOVE_EMMITTER:
      return "Move emitter";
    case GRAVITY_CHANGE:
      return "Gravity control";
    default:
      return "Unknown";
  }
}
State getNextState(State s){
  switch (s){
    case MOVE_EMMITTER:
      return GRAVITY_CHANGE;
    case GRAVITY_CHANGE:
      return MOVE_EMMITTER;
    default:
      return MOVE_EMMITTER;
  }
}