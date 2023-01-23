#include "RotaryEncoder.h"
#include "mbed.h"

RotaryEncoder::RotaryEncoder(PinName channelA, PinName channelB, int mode, double ppr) : cA(channelA), cB(channelB), mode(mode), ppr(ppr){
    pulse = 0;
    prevT = 0;
    nowT = 0;
    dt = 0;
    increment = 0;
    encoding(mode);
    pi = 3.14159265358979323846;
    t.reset();
    t.start();
    }

void RotaryEncoder::callback1(){
    if(cB.read() != cA.read()){
        increment = 1;
        }
    else{
        increment = -1;
        }
    counter = counter + increment;
    }

void RotaryEncoder::callback2(){
    if(cB.read() != cA.read()){
        increment = -1;
        }
    else{
        increment = 1;
        }    
    counter = counter + increment;
    }

double RotaryEncoder::getPulse(){
    pulse = counter/mode;
    return pulse;
    }

double RotaryEncoder::getFreq(){
    pulse = counter/mode;
    periode = t/pulse;
    frequency = 1/periode;
    return frequency;
    }   

void RotaryEncoder::resetPulse(){
    pulse = 0; counter = 0; prevPulse = 0; prevT = 0;
    t.reset();
    t.start();
}

double RotaryEncoder::getDegree(){
    return (pulse/ppr)*360;
    }

double RotaryEncoder::getRPM(){
    nowT = t;
    pulse = counter/mode;
    dp = pulse - prevPulse;
    dt = nowT - prevT;
    prevPulse = pulse;
    prevT = nowT;
    v = dp/dt;
    return (v/ppr)*60;
    }

double RotaryEncoder::getRadian(){
    nowT = t;
    pulse = counter/mode;
    dp = pulse - prevPulse;
    dt = nowT - prevT;
    prevPulse = pulse;
    prevT = nowT;
    v = dp/dt;
    return (2*pi*v)/ppr;
    }
