/* 
 * File:   switch.c
 * Author: rohan_mehta
 *
 * Created on September 13, 2015, 12:21 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#define INPUT 1
#define OUTPUT 0

void initSwitch1(){
    TRISDbits.TRISD6 = INPUT;   // Enable input for switch
    CNCONDbits.ON = 1;          // Turn on CN device
//    CNENDbits.CNIED6 = 1;       // Enable CN interrupt for pin
//    IEC1bits.CNDIE = 1;         // Enable overall CN Interrupt
//    IFS1bits.CNDIF = 0;         // Put Interrupt flag down
    CNPUDbits.CNPUD6 = 1;       // Enable Internal Pull-up resistor
}