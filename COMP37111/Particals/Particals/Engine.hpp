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

class Simulated;

class Engine{

private:
  std::vector<Simulated*> objects;
public:
  Engine();
  void update(int64_t micros);
  void draw(sf::RenderWindow *window);
  float getFPS(const sf::Time& time);
  int objCount(){ return (int) objects.size(); }
  void addNewParticle(Simulated *s){ objects.push_back(s); }
};

#endif /* Engine_hpp */
