//
//  Timer.cpp
//  Particals
//
//  Created by James Peach on 04/12/2015.
//  Copyright © 2015 James Peach. All rights reserved.
//

#include "Timer.hpp"

void
Timer::start(const Interval &interval,
             const Timeout &timeout)
{
  running = true;

  th = thread([=]()
              {
                while (running == true) {
                  this_thread::sleep_for(interval);
                  timeout();
                }
              });
}