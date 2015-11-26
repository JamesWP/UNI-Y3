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
      return "Move emitter";
    case GRAVITY_CHANGE:
      return "Gravity control";
    case COLOR_CHANGE:
      return "Colour control";
    default:
      return "Unknown";
  }
}
State getNextState(State s){
  switch (s){
    case MOVE_EMMITTER:
      return GRAVITY_CHANGE;
    case GRAVITY_CHANGE:
      return COLOR_CHANGE;
    case COLOR_CHANGE:
      return MOVE_EMMITTER;
    default:
      return MOVE_EMMITTER;
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
