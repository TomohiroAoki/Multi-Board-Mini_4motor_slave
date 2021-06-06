#include "mbed.h"
#include "math.h"
#include <PS3BT.h>
#include <usbhub.h>
 
Serial pc(USBTX, USBRX, 115200);
DigitalOut LED_0(PA_0);
PwmOut LED_1(PA_1);

//MDA
DigitalOut A_IN1(PB_0),A_IN2(PB_1);
PwmOut A_PWM(PA_8);

//MDB
DigitalOut B_IN1(PB_6),B_IN2(PB_7);
PwmOut B_PWM(PA_9);
 
//Nucleo f303k8用
USB Usb(D11, D12, D13, A3, A2); // mosi, miso, sclk, ssel, intr
BTD Btd(&Usb);
PS3BT PS3(&Btd);

void motor_double_stick_mode(float max_duty){
    
    int stick_L,stick_R;
    double duty_L,duty_R;
    
    LED_1.period_us(50);
    A_PWM.period_us(50);
    B_PWM.period_us(50);
    
    stick_L = PS3.getAnalogHat(LeftHatY);
    stick_R = PS3.getAnalogHat(RightHatY);
    
    duty_L = fabsf(((double)stick_L/255-0.5)*2*max_duty);
    duty_R = fabsf(((double)stick_R/255-0.5)*2*max_duty);
    
    printf("%d %d\r\n",stick_L,stick_R);
    
    A_PWM = duty_L;
    B_PWM = duty_R;
    LED_1 = duty_R;
    
    if(stick_L >= 128){
        A_IN1 = 1;
        A_IN2 = 0;
    }else{
        A_IN1 = 0;
        A_IN2 = 1;
    }
    
    if(stick_R >= 128){
        B_IN1 = 1;
        B_IN2 = 0;
    }else{
        B_IN1 = 0;
        B_IN2 = 1;
    }
    
}
#if 1
int main(){
        
    bool printAngle = false;
 
    if (Usb.Init() == -1)
    {
        pc.printf("\r\nOSC did not start");
        while (1); // Halt
    }
    pc.printf("\r\nPS3 USB Library Started");
    
    while(1){
        Usb.Task();
        if (PS3.PS3Connected || PS3.PS3NavigationConnected) {
            motor_double_stick_mode(1);
            
        }
    }
}
#endif

#if 0
int main(){
      
    LED_1.period_us(50);
    float duty;
    
    while(1){
      for(duty = 0; duty<=1; duty+=0.01){
        LED_1 = duty;
        wait(0.01);
      }
      for(duty = 1; duty>=0; duty-=0.01){
        LED_1 = duty;
        wait(0.01);
      }     
   }   
       
}
#endif
