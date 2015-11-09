//
//  Engine.cpp
//  Particals
//
//  Created by James Peach on 19/10/2015.
//  Copyright © 2015 James Peach. All rights reserved.
//

#include "Engine.hpp"


// Initialise
Engine::Engine(){
  // create single emmittor
  objects.push_back(new Emmitter(sf::Vector2f(0,HEIGHT),this));
}

bool
isDeleted(Simulated* s){ return s->del(); }

float
Engine::getFPS(const sf::Time& time) {
  return (1000000.0f / time.asMicroseconds());
}


// millis Milliseconds have passed, update state
void
Engine::update(int64_t micros){
  for(auto s : objects){
    s->update(micros);
  }
  objects.erase(
               std::remove_if(objects.begin(), objects.end(), isDeleted),
               objects.end());
}


// draw current state of the engine
void
Engine::draw(sf::RenderWindow *window){
  for(auto s: objects){
    s->draw(window);
  }
}