//
//  Engine.hpp
//  Particals
//
//  Created by James Peach on 19/10/2015.
//  Copyright © 2015 James Peach. All rights reserved.
//

#ifndef Engine_hpp
#define Engine_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "Consts.h"
#include "Simulated.hpp"

class Particle;
class Emmitter;

class Engine{

private:
  std::vector<Emmitter> emmitters;
  std::vector<Particle> particles;
public:
  Engine();
  void update(int64_t micros);
  void draw(sf::RenderWindow *window);
  float getFPS(const sf::Time& time);
  int objCount(){ return (int) particles.size(); }
  int emmCount(){ return (int) emmitters.size(); }
  void addNewParticle(const Emmitter&);
  void addNewParticle(const Particle&);
};

#endif /* Engine_hpp */
