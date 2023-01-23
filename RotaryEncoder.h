#ifndef MBED_ROTARYENCODER_H
#define MBED_ROTARYENCODER_H
 
#include "mbed.h"
/*
    A library for quadrate incremental encoder. There are three encoding
    that can be used to determine posistion in quadrate incremental encoder; X1, X2, X4. For more information,
    you can see in: https://www.motioncontroltips.com/faq-what-do-x1-x2-and-x4-position-encoding-mean-for-incremental-encoders/
    
    Example on using X4 encoding: 
    #include "mbed.h"
    #include "RotaryEncoder.h"
    
    RotaryEncoder pA(PC_6, PC_5, 4, 200);// PC_6 and PC_5 are the pin used for hall sensor, 4 represent the encoding, and 200 is the ppr of the rotor
    Serial pc(USBTX, USBRX);
    
    int main(){
        while(1){
         pc.printf("%d\n", pA.getPulse());       
        }
    }
    
    ------------------------------------------------------------------------------------------------------------------------------
    
    Library untuk quadrate incremental encoder. Terdapat tiga jenis encoding
    yang dapat dipakai dalam menentukan posisi pada quadrate incremental encoder.
    Untuk informasi lebih lanjut, dapat dilihat pada: 
    https://www.motioncontroltips.com/faq-what-do-x1-x2-and-x4-position-encoding-mean-for-incremental-encoders/
    
    Contoh code untuk penggunaan encoding X4:
    #include "mbed.h"
    #include "RotaryEncoder.h"
    
    RotaryEncoder pA(PC_6, PC_5, 4, 200);// PC_6 dan PC_5 adalah pin untuk input hall sensor, 4 adalah jenis encoding yang dipakai, dan 200 adalah ppr dari rotor
    Serial pc(USBTX, USBRX);
    
    int main(){
        while(1){
         pc.printf("%d\n", pA.getPulse());       
        }
    }
    

*/

class RotaryEncoder{
public:
    //inisialisasi
    RotaryEncoder(PinName cA, PinName cB, int mode=1, double ppr=200);
    
    //Ambil posisi encoder
    double getPulse();
    
    /*ambil kecepatan dari encoder*/  
    double getFreq();
    
    //Ambil mode encoding
    int getEncoding(){return mode;}
    
    //reset pulse
    void resetPulse();
    
    //get degree
    double getDegree();
    
    //get speed of motor
    double getRPM();
    double getRadian();
    
    private:
    InterruptIn cA;
    InterruptIn cB;
    Timer t;
    protected:
    double pi;
    const int mode;
    const double ppr;
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
    volatile double periode, frequency;
    volatile double nowT, dt, prevT;
    volatile double increment, counter, pulse, prevPulse, dp, v;
};

#endif
