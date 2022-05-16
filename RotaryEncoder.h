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
    
    Timer waktu;
    RotaryEncoder pA(PC_6, PC_5, 2);
    Serial pc(USBTX, USBRX);
    
    int main(){
        while(1){
         //get frequency to determine rpm, rpm formula is
         // rpm = freq/ppr*60, the encoding that is used determine the value of ppr
         float rpm = pA.getFreq() / 422 * 60;
         pc.printf("%f \t %f\n", pA.getPulse(), rpm);       
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
    
    Timer waktu;
    RotaryEncoder pA(PC_6, PC_5, 2);
    Serial pc(USBTX, USBRX);
    
    int main(){
        while(1){
         //frekuensi encoder dapat digunakan untuk mendapatkan rpm
         // rpm = freq/ppr*60, dimana ppr ditentukan oleh teknik encoding yang digunakan
         float rpm = pA.getFreq() / 422 * 60;
         pc.printf("%f \t %f\n", pA.getPulse(), rpm);       
        }
    }
    

*/

class RotaryEncoder{
public:
    //inisialisasi
    RotaryEncoder(PinName cA, PinName cB, int mode=1);
    
    //Ambil posisi encoder
    float getPulse();
    
    /*ambil kecepatan dari encoder:
        x(t) = ∆x //perpindahan posisi  ->    x = pulse(p)     p(t) = ∆p
        v(t) = ∆x/∆t //kecepatan        ->    v(t) = ∆p/∆t
             = x'(t) 
    */  
    float getFreq();
    
    //Ambil mode encoding
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
    volatile float nowT, dt, prevT;
    volatile float increment, pulse;
};

#endif