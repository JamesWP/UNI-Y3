//
//  Timer.hpp
//  Particals
//
//  Created by James Peach on 04/12/2015.
//  Copyright © 2015 James Peach. All rights reserved.
//

#ifndef Timer_hpp
#define Timer_hpp

#include <stdio.h>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

class Timer
{
  thread th;
  bool running = false;

public:
  typedef std::chrono::microseconds Interval;
  typedef std::function<void(void)> Timeout;

  void start(const Interval &interval,
             const Timeout &timeout);

  void stop(){running = false; th.join();}
};

#endif /* Timer_hpp */
