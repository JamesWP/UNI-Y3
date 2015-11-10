//
//  EngineConfig.hpp
//  Particals
//
//  Created by James Peach on 09/11/2015.
//  Copyright © 2015 James Peach. All rights reserved.
//

#ifndef EngineConfig_hpp
#define EngineConfig_hpp

#include <stdio.h>

namespace EngineConfig {
  static float width = 4.0;
  static float height = 4.0;
  static float getPointWidth(){ return width;}
  static float getPointHeight(){ return height;}

  static void setPointWidth(float newWidth){ width = newWidth;}
  static void setPointHeight(float newHeight){ height = newHeight;}
}

#endif /* EngineConfig_hp */