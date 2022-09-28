#include "RotaryEncoder.h"
#include "mbed.h"

RotaryEncoder::RotaryEncoder(PinName channelA, PinName channelB, int mode) : cA(channelA), cB(channelB), mode(mode){
    pulse = 0;
    prevT = 0;
    nowT = 0;
    dt = 0;
    increment = 0;
    pi = 3.14159265358979323846;
    encoding(mode);
    t.reset();
    t.start();
    }

void RotaryEncoder::callback1(){
    nowT = t;
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
    nowT = t;
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

float RotaryEncoder::getPulse(){
    return pulse;
    }

float RotaryEncoder::getFreq(){
    if(pulse == 0){return 0;}
    return v;
    }   

void RotaryEncoder::resetPulse(){
    pulse = 0;
}

float RotaryEncoder::getRPM(){
    return v/(ppr*mode)*60;
    }

float RotaryEncoder::getRadian(){
    return (2*pi*v)/(ppr*dt);
    }