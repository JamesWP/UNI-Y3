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
      return "1) Move emitter";
    case GRAVITY_CHANGE:
      return "2) Gravity control";
    case COLOR_CHANGE:
      return "3) Colour control";
    case RENDER_CHANGE:
      return "4) Render control";
    case SPECIAL:
      return "5) Special control";
    default:
      return "Unknown";
  }
}
std::string getStateDescription(State s){
  switch (s){
    case MOVE_EMMITTER:
      return "Use the mouse to move the emmitter";
    case GRAVITY_CHANGE:
      return "Use the mouse to change the gravity";
    case COLOR_CHANGE:
      return "Use the mouse to affect the color of new particles\n X: freqency of change\n Y: saturation";
    case RENDER_CHANGE:
      return "Use the mouse to change the render mode\n X: change from lines, points, blocks, and points again";
    case SPECIAL:
      return "When suddenly.. the mouse became an attractor!";
    default:
      return "Unknown";
  }
}
State getNextState(State s){
  int curentState = s;
  if ((curentState+1) != (int)EngineState::LAST){
    return static_cast<State>(curentState+1);
  }else{
    return static_cast<State>(((int)EngineState::FIRST)+1);
  }
}
State getPrevState(State s){
  int curentState = s;
  if ((curentState-1) != (int)EngineState::FIRST){
    return static_cast<State>(curentState-1);
  }else{
    return static_cast<State>(((int)EngineState::LAST)-1);
  }
}

sf::Color TurnToRGB(int Hue,int Saturation,int Liminance);

sf::Color getColorFromTime(long time, int i){
  int hue = (time)&((1<<8)-1);
  return TurnToRGB(hue, i, 50);
}

double HueToRGB(double arg1, double arg2, double H)
{
  if ( H < 0 ) H += 1;
  if ( H > 1 ) H -= 1;
  if ( ( 6 * H ) < 1 ) { return (arg1 + ( arg2 - arg1 ) * 6 * H); }
  if ( ( 2 * H ) < 1 ) { return arg2; }
  if ( ( 3 * H ) < 2 ) { return ( arg1 + ( arg2 - arg1 ) * ( ( 2.0 / 3.0 ) - H ) * 6 ); }
  return arg1;
}
const double D_EPSILON = 0.00000000000001;
sf::Color TurnToRGB(int Hue,int Saturation,int Luminance)
{
  ///Reconvert to range [0,1]
  double H = Hue/360.0;
  double S = Saturation/100.0;
  double L = Luminance/100.0;

  float arg1, arg2;

  if (S <= D_EPSILON)
  {
    sf::Color C(L*255, L*255, L*255);
    return C;
  }
  else
  {
    if ( L < 0.5 ) { arg2 = L * ( 1 + S ); }
    else { arg2 = ( L + S ) - ( S * L ); }
    arg1 = 2 * L - arg2;

    sf::Uint8 r =( 255 * HueToRGB( arg1, arg2, (H + 1.0/3.0 ) ) );
    sf::Uint8 g =( 255 * HueToRGB( arg1, arg2, H ) );
    sf::Uint8 b =( 255 * HueToRGB( arg1, arg2, (H - 1.0/3.0 ) ) );
    sf::Color C(r,g,b);
    return C;
  }

}
