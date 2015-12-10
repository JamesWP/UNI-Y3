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

const sf::Vector2f
Simulated::acceleration(const sf::Vector2f pos){
  if(!conf.inState(EngineState::SPECIAL)){
    const sf::Vector2f unit = sf::Vector2f(0.00000000001,0.00000000001);
    sf::Vector2i mPos;
    if(conf.inState(EngineState::GRAVITY_CHANGE)){
        mPos = conf.getMousePosition();
    }else{
      mPos = sf::Vector2i(WIDTH/2,HEIGHT/2 + 20);
    }

    return sf::Vector2f(unit.x*(mPos.x - (WIDTH/2)),unit.y*(mPos.y-(HEIGHT/2)));
  }else{
    // construct a vector to point towards the mouse
    sf::Vector2f mPos = (sf::Vector2f) conf.getMousePosition();
    sf::Vector2f toM = mPos - pos;
    //float mag = sqrt(toM.x * toM.x + toM.y * toM.y)/100000000000000.0;
    float mag = sqrt(toM.x * toM.x + toM.y * toM.y)/1000000000000.0;
    toM.x *= mag;
    toM.y *= mag;
    return toM;
  }
}


SimplePoint::SimplePoint(sf::Vector2f initialPosition,
                         sf::Vector2f velocity,
                         const sf::Color col){
  positions = sf::VertexArray(sf::Quads, 4);
  SimplePoint::positions[0].position = initialPosition;
  SimplePoint::positions[1].position = sf::Vector2f(initialPosition.x + width,initialPosition.y);
  SimplePoint::positions[2].position = sf::Vector2f(initialPosition.x + width,initialPosition.y + height);
  SimplePoint::positions[3].position = sf::Vector2f(initialPosition.x,
                                                    initialPosition.y + height);
  SimplePoint::positions[0].color = col;
  SimplePoint::positions[1].color = col;
  SimplePoint::positions[2].color = col;
  SimplePoint::positions[3].color = col;

  lastPositions = sf::VertexArray(sf::Lines,2);
  lastPositions[0] = initialPosition;
  lastPositions[1] = initialPosition;

  lastPositions[0].color = col;
  lastPositions[1].color = col;

  SimplePoint::velocity = velocity;
}

void
SimplePoint::update(int64_t micros){
  Simulated::update(micros);

  const sf::Vector2f acceleration = SimplePoint::acceleration(positions[0].position);
  velocity.x += acceleration.x * micros;
  velocity.y += acceleration.y * micros;

  positions[0].position.x += velocity.x * micros;
  positions[0].position.y += velocity.y * micros;

  SimplePoint::positions[1].position = sf::Vector2f(positions[0].position.x + width,positions[0].position.y);
  SimplePoint::positions[2].position = sf::Vector2f(positions[0].position.x + width,positions[0].position.y + height);
  SimplePoint::positions[3].position = sf::Vector2f(positions[0].position.x,
                                                    positions[0].position.y + height);

  lastPositions[0] = lastPositions[1];
  lastPositions[1] = positions[0];
}

void
SimplePoint::draw(sf::RenderWindow *window){
  if(conf.inState(EngineState::RENDER_CHANGE)){
    int render = conf.getMousePosition().x/(HEIGHT/3);
    switch(render){
      case 0:
        window->draw(&lastPositions[0], 2, sf::Lines);
        break;
      case 2:
        window->draw(&positions[0], 4, sf::Quads);
        break;
      case 1:
      case 3:
        window->draw(&positions[0], 1, sf::Points);
        break;
    }
  }else{
    window->draw(&positions[0], 1, sf::Points);
  }
}

Particle::Particle(sf::Vector2f initialPosition,
                   sf::Vector2f velocity,
                   const sf::Color col)
:SimplePoint(initialPosition,velocity,col){
  age = 0;
  lifetime = 300000000;
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
sf::Vector2f randVec(const float maxMag){
  const float mag = fRand(maxMag*0.6f, maxMag);
  auto v = MathUtil::GetVectorFromAngle(fRand(0.0,360.0));
  v.x*=mag;
  v.y*=mag;
  return v;
}

sf::Vector2f newPosition(const sf::Vector2f position){
  return sf::Vector2f(position.x + fRand(-5,5),position.y + fRand(-5, 5));
}

sf::Vector2f newVelocity(const sf::Vector2f direction){
  return direction + randVec(0.0001);
}

const sf::Color newColor(){
  if(conf.inState(EngineState::COLOR_CHANGE)){
    return conf.getColor();
  }else if (conf.inState(EngineState::SPECIAL)){
    return conf.getColor();
  }else return sf::Color::White;
}

Particle
newRandParticle(const sf::Vector2f position){
    return Particle(
                        newPosition(position),
                        newVelocity(sf::Vector2f(0,0)),
                        newColor());
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
  if(conf.inState(EngineState::MOVE_EMMITTER)){
    position.position.x = conf.getMousePosition().x;
    position.position.y = conf.getMousePosition().y;
  }
  if(time>nextSpawn){
    nextSpawn = time + 1; //+ (rand()/10000000);
    int ps = 1000;
    switch (conf.getCurentState()){
      case EngineState::RENDER_CHANGE:
        ps = conf.getMousePosition().y*4;
        break;
      case EngineState::SPECIAL:
        ps = 50;
        break;
      default:;
    }
    for(int i=0;i<ps;i++)
     hostEngine->addNewParticle(newRandParticle(position.position));
  }
}

