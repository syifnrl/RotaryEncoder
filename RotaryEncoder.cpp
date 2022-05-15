#include "RotaryEncoder.h"
#include "mbed.h"

RotaryEncoder::RotaryEncoder(PinName channelA, PinName channelB, int encoding) : cA(channelA), cB(channelB), encoding(encoding){
    pulse = 0;
    prevT = 0;
    nowT = 0;
    dt = 0;
    increment = 0;
    t.start();
    if(encoding == 1){
        cA.rise(this, &RotaryEncoder::callback1);
        }
    else if(encoding == 2){
        cA.rise(this, &RotaryEncoder::callback1);
        cA.fall(this, &RotaryEncoder::callback1);
        }
    else if(encoding == 4){
        cA.rise(this, &RotaryEncoder::callback1);
        cA.fall(this, &RotaryEncoder::callback1);
        
        cB.rise(this, &RotaryEncoder::callback2);
        cB.fall(this, &RotaryEncoder::callback2);
        }
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
    
void RotaryEncoder::callback2(){
    nowT = t.read();
    if(cB.read() != cA.read()){
        increment = -1;
        }
    else{
        increment = 1;
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