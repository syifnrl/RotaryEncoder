#ifndef MBED_ROTARYENCODER_H
#define MBED_ROTARYENCODER_H
 
#include "mbed.h"

class RotaryEncoder{
public:
    RotaryEncoder(PinName cA, PinName cB, int mode=1);
    int getPulse();
    float getFreq();
    int getEncoding(){return mode;}
    private:
    InterruptIn cA;
    InterruptIn cB;
    Timer t;
    protected:
    const int mode;
    void encoding(int val){
        if(val == 1){
            cA.rise(this, &RotaryEncoder::callback1);
            }
        else if(val == 2){
            cA.rise(this, &RotaryEncoder::callback1);
            cA.fall(this, &RotaryEncoder::callback1);
            }
        else if(val == 4){
            cA.rise(this, &RotaryEncoder::callback1);
            cA.fall(this, &RotaryEncoder::callback1);
    
            cB.rise(this, &RotaryEncoder::callback2);
            cB.fall(this, &RotaryEncoder::callback2);
            }
        }
    void callback1(void);
    void callback2(void);
    volatile float v;
    volatile long nowT, dt, prevT;
    volatile int increment, pulse;
};

#endif