//
//  Simulated.hpp
//  Particals
//
//  Created by James Peach on 27/10/2015.
//  Copyright © 2015 James Peach. All rights reserved.
//

#ifndef Simulated_hpp
#define Simulated_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Consts.h"
#include "Engine.hpp"
#include "EngineConfig.hpp"

class Engine;

class Simulated {
public:
  virtual void update(int64_t micros);
  virtual void draw(sf::RenderWindow *window);
  virtual bool del();
};

class SimplePoint: public Simulated {
  sf::VertexArray positions;
  float width=EngineConfig::getPointWidth();
  float height=EngineConfig::getPointHeight();
  sf::Vector2f velocity;
  sf::Vector2f acceleration;
public:
  SimplePoint(sf::Vector2f initialPosition,
           sf::Vector2f velocity, sf::Vector2f acceleration);
  void update(int64_t micros);
  void draw(sf::RenderWindow *window);
  bool del() { return positions[0].position.x > WIDTH
    || positions[0].position.y > HEIGHT || positions[0].position.x < 0 || positions[0].position.y < 0; }
};

class Particle: public SimplePoint {
  double age;
  double lifetime;
public:
  Particle(sf::Vector2f initialPosition,
                   sf::Vector2f velocity, sf::Vector2f acceleration);
  void update(int64_t micros);
  bool del();
};

class Emmitter: public Simulated {
  sf::Vertex position;
  Engine *hostEngine;
  int64_t time;
  int64_t nextSpawn;
public:
  Emmitter(sf::Vector2f initialPosition, Engine *host);
  void update(int64_t micros);
};

#endif /* Simulated_hpp */
