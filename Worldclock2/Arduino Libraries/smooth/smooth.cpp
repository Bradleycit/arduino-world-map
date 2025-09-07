//
//  smooth.cpp
//  
//
//  Created by Eric Woolsey on 2014-07-10.
//  Last Modified 2014-08-05
//

#include "smooth.h"

runningAverage::runningAverage(const byte a){
    n = a;
    array = new float[n]();
    index = 0;
    isRepeat = 0;
}

//runningAverage::runningAverage(const runningAverage & other){
//    n = other.n;
//    array = new float[n]();
//    *array = *(other.array);
//    index = other.index;
//    isRepeat = other.isRepeat;
//}

runningAverage::~runningAverage(){
    delete[] array;
}

float runningAverage::smooth(const float a){
    float output;
    array[index] = a;
    if(index == n-1) {
        index = 0;
        isRepeat = 1;
    }
    else index++;
    if (isRepeat){
        for (byte i = output = 0; i < n; i++) {
            output += array[i];
        }
        return (output/(float)n);
    }
    else {
        for (byte i = output = 0; i < index; i++) {
              output += array[i];
        }
        return (output/(float)index);
    }
}

void goodDelay(const unsigned long time){
    unsigned long tStart = millis();
    while((millis()-tStart) < time){
        if (millis() - tStart < 0) break;
    };
}