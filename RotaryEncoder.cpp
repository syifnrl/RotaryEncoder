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
    nowT = t;
    if(cB.read() != cA.read()){
        increment = 1;
        }
    else{
        increment = -1;
        }
    counter = counter + increment;
    pulse = counter/mode;
    dp = pulse - prevPulse;
    dt = nowT - prevT;
    prevPulse = pulse;
    prevT = nowT;
    v = dp/dt;
    periode = t/pulse;
    sampling_periode = pulse/t;
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
    counter = counter + increment;
    pulse = counter/mode;
    dp = pulse - prevPulse;
    dt = nowT - prevT;
    prevPulse = pulse;
    prevT = nowT;
    v = dp/dt;
    periode = t/pulse;
    sampling_periode = pulse/t;
    }

double RotaryEncoder::getPulse(){
    return pulse;
    }

double RotaryEncoder::getFreq(){
    if(pulse == 0){return 0;}
    frequency = 1/periode;
    return frequency;
    }   

void RotaryEncoder::resetPulse(){
    pulse = 0; counter = 0;
}

double RotaryEncoder::getDegree(){
    return (counter/ppr)*360;
    }

double RotaryEncoder::getRPM(){
    return (v/(ppr/mode))*60;
    }

double RotaryEncoder::getRadian(){
    return (2*pi*v)/(ppr/mode);
    }
