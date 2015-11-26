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

typedef enum State{
  MOVE_EMMITTER, GRAVITY_CHANGE, COLOR_CHANGE
} EngineState;

std::string getStateString(EngineState s);
EngineState getNextState(EngineState s);
sf::Color getColorFromTime(long time, int intensity);

class EngineConfig {
private:
  float width = 4.0;
  float height = 4.0;
  sf::Clock *clock;
  sf::Vector2i mPos = sf::Vector2i(0,0);
  EngineState engineState = MOVE_EMMITTER;
public:
  float getPointWidth(){ return width;}
  float getPointHeight(){ return height;}
  sf::Vector2i getMousePosition(){return mPos;}

  void setPointWidth(float newWidth){ width = newWidth;}
  void setPointHeight(float newHeight){ height = newHeight;}
  void setMousePosition(const sf::Vector2i newMPos){ mPos = newMPos;}
  void setClock(sf::Clock *newClock){clock = newClock;}

  EngineState getCurentState(){return engineState;}
  bool inState(EngineState s){return s==engineState;}
  void nextState(){engineState = getNextState(engineState);}
  std::string getStateMsg(){return getStateString(engineState);}

  const sf::Color getColor(){
    int shift = mPos.x/30;
    int intensity = mPos.y/3;
    return getColorFromTime(clock->getElapsedTime().asMicroseconds()>>shift,intensity);
  }
};

#endif /* EngineConfig_hp */