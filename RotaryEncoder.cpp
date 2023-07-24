#include "RotaryEncoder.h"
#include "mbed.h"


RotaryEncoder::RotaryEncoder(PinName channelA, PinName channelB, int mode, float ppr) : cA(channelA), cB(channelB), _mode(mode), _ppr(ppr){
    pulse = 0;
    prevT = 0;
    nowT = 0;
    dt = 0;
    increment = 0;
    pi = 3.14159265358979323846;
    cA.mode(PullUp);
    cB.mode(PullUp);
    if(_mode == 2){
    cA.rise(callback(this, &RotaryEncoder::callback1));
    cA.fall(callback(this, &RotaryEncoder::callback1));
    }
    if(_mode == 4){
    cA.rise(callback(this, &RotaryEncoder::callback1));
    cA.fall(callback(this, &RotaryEncoder::callback1));

    cB.rise(callback(this, &RotaryEncoder::callback2));
    cB.fall(callback(this, &RotaryEncoder::callback2));
    }
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
    counter += increment;
    }

void RotaryEncoder::callback2(){
    if(cA.read() != cB.read()){
        increment = -1;
        }
    else{
        increment = 1;
        }
    counter += increment;
    }

float RotaryEncoder::getPulse(){
    pulse = counter/_mode;
    return pulse;
    }  

void RotaryEncoder::resetPulse(){
    pulse = counter/_mode;
    pulse = 0; counter = 0;
    pulse = 0; counter = 0; prevPulse = 0; prevT = 0;
    t.reset();
    t.start();
}

float RotaryEncoder::getDegree(){
    pulse = counter/_mode;
    return (pulse/_ppr)*360;
    }

float RotaryEncoder::getRPM(){
    nowT = t;
    pulse = counter;
    dp = pulse - prevPulse;
    dt = (nowT - prevT);
    prevPulse = pulse;
    prevT = nowT;
    v = dp/dt;
    return (v/_ppr)*60;
    }

float RotaryEncoder::getRadian(){
    nowT = t;
    pulse = counter;
    dp = pulse - prevPulse;
    dt = (nowT - prevT);
    prevPulse = pulse;
    prevT = nowT;
    v = dp/dt;
    return (2*pi*v)/_ppr;
    }
