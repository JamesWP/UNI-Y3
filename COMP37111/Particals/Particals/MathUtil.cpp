//
//  MathUtil.cpp
//  Particals
//
//  Created by James Peach on 04/12/2015.
//  Copyright © 2015 James Peach. All rights reserved.
//

#include "MathUtil.hpp"
extern sf::Vector2f MathUtil::GetVectorFromAngle(float angle)
{
  if(angle < 0) angle += 360; //make sure angle is always positive value
  switch((int)angle)
  {
    case 0:
    case 360:
      return sf::Vector2f(1.f, 0.f);
    case 90:
      //case -270:
      return sf::Vector2f(0.f, 1.f);
    case 180:
      //case -180:
      return sf::Vector2f(-1.f, 0.f);
    case 270:
      //case -90:
      return sf::Vector2f(0.f, -1.f);
      break;
    default:
      angle = (float)(angle * (3.14159265 / 180));
      return sf::Vector2f(cos(angle), sin(angle));
  }
}