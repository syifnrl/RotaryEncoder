#include "RotaryEncoder.h"
#include "mbed.h"

RotaryEncoder::RotaryEncoder(PinName channelA, PinName channelB) : cA(channelA), cB(channelB){
    pulse = 0;
    prevT = 0;
    nowT = 0;
    dt = 0;
    increment = 0;
    cA.rise(this, &RotaryEncoder::callback1);
    cA.fall(this, &RotaryEncoder::callback1);
    t.start();
    }

void RotaryEncoder::callback1(){
    nowT = t.read();
    if(cB.read() != cA.read()){
        increment = 1;
        }
    else{
        increment = -1;
        }
    pulse = pulse + increment;
    dt = nowT - prevT;
    v = increment/dt;
    prevT = nowT;
    }

int RotaryEncoder::getPulse(){
    return pulse;
    }

float RotaryEncoder::getFreq(){
    return v;
    }   