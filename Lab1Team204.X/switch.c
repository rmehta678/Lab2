/*
 * File:   switch.c
 * Author: Garrett
 *
 * Created on September 19, 2015, 10:46 AM
 */
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

#define INPUT 1
#define OUTPUT 0

void initRSW() {
    TRISAbits.TRISA6 = INPUT;   // Enable input for switch (TEMP)
    CNCONAbits.ON = 1;          // Turn on CN device (TEMP)
    CNENAbits.CNIEA6 = 1;       // Enable CN interrupt for pin (TEMP)
    CNPUAbits.CNPUA6 = 1;       // Enable Internal Pull-up resistor (TEMP)
    IPC8bits.CNIP = 7;          // Configure the Interrupt Priority
    IEC1bits.CNAIE = 1;         // Enable overall CN Interrupt (TEMP)
    IFS1bits.CNAIF = 0;         // Put Interrupt flag down (TEMP)
}
void initSW2(){
    TRISAbits.TRISA7 = INPUT;   // Enable input for switch (TEMP)
    CNCONAbits.ON = 1;          // Turn on CN device (TEMP)
    CNENAbits.CNIEA7 = 1;       // Enable CN interrupt for pin (TEMP)
    CNPUAbits.CNPUA7 = 1;       // Enable Internal Pull-up resistor (TEMP)
    IPC8bits.CNIP = 7;          // Configure the Interrupt Priority
    IEC1bits.CNAIE = 1;         // Enable overall CN Interrupt (TEMP)
    IFS1bits.CNAIF = 0;         // Put Interrupt flag down (TEMP)
    //TODO: Initialize the appropriate pins to work with the external switch using a
    //change notification interrupt.
}
