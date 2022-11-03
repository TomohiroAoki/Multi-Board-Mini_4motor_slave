#include "mbed.h"
#include "math.h"
#include "MotorDriver.h"

#define AJT 1
Serial pc(USBTX, USBRX, 115200);

DigitalIn mc(PA_0),md(PA_1);
AnalogIn C_IN(PA_5),D_IN(PA_6);

float c_duty,d_duty;

int main(){
    while(1){

        c_duty = C_IN.read() * AJT;
        d_duty = D_IN.read() * AJT;

        if(c_duty > 0.5 || d_duty > 0.5){
            m(0,0);
        }else{
            printf("%f %f\r\n",c_duty,d_duty);
            if(mc == 1 && md == 1){
                m(c_duty,d_duty);
            }else if(mc == 1 && md == 0){
                m(c_duty,-d_duty);
            }else if(mc == 0 && md == 1){
                m(-c_duty,d_duty);
            }else{
                m(-c_duty,-d_duty);
            }
        }
    }
}
