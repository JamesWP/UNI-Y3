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
  emmitters.push_back(Emmitter(sf::Vector2f(WIDTH/2,HEIGHT/2),this));
}

bool
isDeleted(Particle &s){ return s.del(); }

float
Engine::getFPS(const sf::Time& time) {
  return (1000000.0f / time.asMicroseconds());
}

int irand(int max){ return rand()%max;}


// millis Milliseconds have passed, update state
void
Engine::update(int64_t micros){

  if(conf.readEnter()){
    emmitters.push_back(Emmitter(sf::Vector2f(conf.getMousePosition().x,conf.getMousePosition().y),this));
  }
  if(conf.readBackspace()){
    emmitters.erase(emmitters.begin(), emmitters.end());
    particles.erase(particles.begin()++, particles.end());
  }
  
  for(auto &s : particles){
    s.update(micros);
  }
  for(auto &s : emmitters){
    s.update(micros);
  }
    particles.erase(
               std::remove_if(particles.begin()++, particles.end(), isDeleted),
               particles.end());
}


// draw current state of the engine
void
Engine::draw(sf::RenderWindow *window){
  for(auto &s: particles){
    s.draw(window);
  }
}

void
Engine::addNewParticle(const Emmitter &s){
  emmitters.push_back(s);
}

void
Engine::addNewParticle(const Particle &s){
  particles.push_back(s);
}