#include "RotaryEncoder.h"
#include "mbed.h"

RotaryEncoder::RotaryEncoder(PinName channelA, PinName channelB, int mode, float ppr) : cA(channelA), cB(channelB), mode(mode), ppr(ppr){
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
    prevPulse = pulse;
    nowT = t;
    if(cB.read() != cA.read()){
        increment = 1;
        }
    else{
        increment = -1;
        }
    pulse = pulse + increment;
    dt = nowT - prevT;
    prevT = nowT;
    periode = dt/(pulse - prevPulse);
    sampling_periode = (pulse - prevPulse)/dt;
    frequency = 1/periode;
    }

void RotaryEncoder::callback2(){
    prevPulse = pulse;
    nowT = t;
    if(cB.read() != cA.read()){
        increment = -1;
        }
    else{
        increment = 1;
        }
    pulse = pulse + increment;
    dt = nowT - prevT;
    prevT = nowT;
    periode = dt/(pulse - prevPulse);
    sampling_periode = (pulse - prevPulse)/dt;
    frequency = 1/periode;
    }

float RotaryEncoder::getPulse(){
    return pulse;
    }

float RotaryEncoder::getFreq(){
    if(pulse == 0){return 0;}
    return frequency/mode;
    }   

void RotaryEncoder::resetPulse(){
    pulse = 0;
}

float RotaryEncoder::getDegree(){
    return pulse/(ppr*mode)*360;
    }

float RotaryEncoder::getRPM(){
    return ((pulse/ppr)/t.read())*60;
    }

float RotaryEncoder::getRadian(){
    return (2*pi*pulse*mode)/(ppr*sampling_periode);
    }
