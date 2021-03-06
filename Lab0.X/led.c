/* 
 * File:   led.c
 * Author: rohan_mehta
 *
 * Created on September 13, 2015, 12:21 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "led.h"
#include <xc.h>
#include <sys/attribs.h>

#define OUTPUT 0
#define INPUT 1
/*
 * 
 */
void initLEDs(){ //Initializes the LED's as outputs
    TRISDbits.TRISD0 = OUTPUT;
    TRISDbits.TRISD1 = OUTPUT;
    TRISDbits.TRISD2 = OUTPUT;
}

void turnOnLED(int led){ //Code from class
     if(led == 1){
        LATDbits.LATD0 = 1; //LED 1
        LATDbits.LATD1 = 0;
        LATDbits.LATD2 = 0;
    }
    else if(led == 2){
        LATDbits.LATD0 = 0;
        LATDbits.LATD1 = 1; //LED 2
        LATDbits.LATD2 = 0;        
    }
    else{
        LATDbits.LATD0 = 0;
        LATDbits.LATD1 = 0;
        LATDbits.LATD2 = 1; //LED 3
    }
    
    
}