#ifndef MBED_ROTARYENCODER_H
#define MBED_ROTARYENCODER_H
 
#include "mbed.h"

class RotaryEncoder{
public:
    RotaryEncoder(PinName cA, PinName cB, int encoding=1);
    int getPulse();
    float getFreq();
    
    private:
    InterruptIn cA;
    InterruptIn cB;
    Timer t;
    void callback1(void);
    void callback2(void);
    volatile float v;
    volatile long nowT, dt, prevT;
    volatile int increment, pulse;
};

#endif