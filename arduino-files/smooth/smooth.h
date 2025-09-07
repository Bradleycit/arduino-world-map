//
//  smooth.h
//  
//
//  Created by Eric Woolsey on 2014-07-10.
//  Last Modified 2014-08-05
//

#include "arduino.h"
#ifndef _smooth_h
#define _smooth_h

class runningAverage{
private:
    byte n;
    byte index;
    bool isRepeat;
    float *array;
    runningAverage(const runningAverage &);
    runningAverage & operator = (const runningAverage &);
public:
//    runningAverage(const runningAverage &);
    runningAverage(const byte);
    ~runningAverage();
    float smooth(const float);
};

void goodDelay(unsigned long);
#endif