/*
* File:   leds.c
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#include <stdio.h>
#include <stdlib.h>
#include "leds.h"
#include <xc.h>
#include <sys/attribs.h>

#define OUTPUT 0
#define INPUT 1
#define OFF 1
#define ON 0

/*
 * 
 */
void initLEDs(){ //Initializes the LED's as outputs
    TRISGbits.TRISG12 = OUTPUT;
    TRISGbits.TRISG14 = OUTPUT;
    LATGbits.LATG12 = ON;
    LATGbits.LATG14 = OFF;
}

//void turnOnLED(int led){ //Code from class
//     if(led == 1){
//        LATDbits.LATD1 = 1; //LED 1
//        LATDbits.LATD2 = 0;
//   
//    }
//    else if(led == 2){
//        LATDbits.LATD1 = 0;
//        LATDbits.LATD2 = 1; //LED 2
//              
//    }  
//}
    //TODO: Initialize the appropriate pins to work with the LEDs
    
