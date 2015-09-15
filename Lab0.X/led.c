/* 
 * File:   led.c
 * Author: rohan_mehta
 *
 * Created on September 13, 2015, 12:21 PM
 */

#include <stdio.h>
#include <stdlib.h>

#define OUTPUT 0
#define INPUT 1
/*
 * 
 */
void initLEDs(){
    TRISDbits.TRISD0 = OUTPUT;
    TRISDbits.TRISD1 = OUTPUT;
    TRISDbits.TRISD2 = OUTPUT;
    //TODO: Initialize LEDs
}

void turnOnLED(int led){
     if(led == 1){
        LATDbits.LATD0 = 1;
        LATDbits.LATD1 = 0;
        LATDbits.LATD2 = 0;
    }
    else if(led == 2){
        LATDbits.LATD0 = 0;
        LATDbits.LATD1 = 1;
        LATDbits.LATD2 = 0;        
    }
    else{
        LATDbits.LATD0 = 0;
        LATDbits.LATD1 = 0;
        LATDbits.LATD2 = 1;
    }
    
    //TODO: You may choose to write this function
    // as a matter of convenience
    
}