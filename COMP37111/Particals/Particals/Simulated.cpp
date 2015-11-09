//
//  Simulated.cpp
//  Particals
//
//  Created by James Peach on 27/10/2015.
//  Copyright © 2015 James Peach. All rights reserved.
//

#include "Simulated.hpp"


void
Simulated::update(int64_t micros){

}

void
Simulated::draw(sf::RenderWindow *window){

}

bool
Simulated::del(){ return false; }


SimplePoint::SimplePoint(sf::Vector2f initialPosition,
                         sf::Vector2f velocity, sf::Vector2f acceleration){
  SimplePoint::position.position = initialPosition;
  SimplePoint::position.color = sf::Color::White;
  SimplePoint::velocity = velocity;
  SimplePoint::acceleration = acceleration;
}

void
SimplePoint::update(int64_t micros){
  Simulated::update(micros);

  velocity.x += acceleration.x * micros;
  velocity.y += acceleration.y * micros;

  position.position.x += velocity.x * micros;
  position.position.y += velocity.y * micros;
}

void
SimplePoint::draw(sf::RenderWindow *window){
  Simulated::draw(window);
  window->draw(&position, 1, sf::Points);
}

Particle::Particle(sf::Vector2f initialPosition,
                   sf::Vector2f velocity, sf::Vector2f acceleration)
:SimplePoint(initialPosition,velocity,acceleration){
  age = 0;
  lifetime = 3000000;
}

void
Particle::update(int64_t micros){
  SimplePoint::update(micros);
  age += micros;
}

bool
Particle::del(){
  return age > lifetime || SimplePoint::del();
}

//////////// Emmitter

float
fRand(float fMin, float fMax)
{
  float f = (float)rand() / RAND_MAX;
  return fMin + f * (fMax - fMin);
}

sf::Vector2f newPosition(const sf::Vector2f position){
  return sf::Vector2f(position.x + fRand(-5,5),position.y + fRand(-5, 5));
}

sf::Vector2f newVelocity(const sf::Vector2f direction){
  return sf::Vector2f(direction.x + fRand(-0.0002, 0.0002),
                      direction.y + fRand(-0.0002, 0.0002));
}

Particle*
newRandParticle(const sf::Vector2f position){
  return new Particle(
                      newPosition(position),
                      newVelocity(sf::Vector2f(0.0006,-0.00060)),
                      sf::Vector2f(0,0.000000002));
}

Emmitter::Emmitter(sf::Vector2f position, Engine *host){
  Emmitter::position.position = position;
  Emmitter::hostEngine = host;
  time = 0;
  nextSpawn = 1000;
}

void
Emmitter::update(int64_t micros){
  time+=micros;
  position.position.x = hostEngine->getMousePosition().x;
  position.position.y = hostEngine->getMousePosition().y;
  if(time>nextSpawn){
    nextSpawn = time + 1; //+ (rand()/10000000);
    for(int i=0;i<200;i++)
     hostEngine->addNewParticle(newRandParticle(position.position));
  }
}

