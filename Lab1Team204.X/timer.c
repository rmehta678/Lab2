/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"

void delayUs(unsigned int delay){ 
    TMR2 = 0;
    T2CONbits.TCKPS = 3;
    T2CONbits.TCS = 0;
    PR2 = (delay*10) - 1;
    IFS0bits.T2IF = 0;
    T2CONbits.TON = 1;
    while(IFS0bits.T2IF==0);
    T2CONbits.TON = 0;
    //TODO: Create a delay using timer 2 for "delay" microseconds.
}

void initTimer1() {
    TMR1 = 0;// clear TMR1
    PR1 = 3124;// Initialize PR1
    T1CONbits.TCKPS = 3; // Initialize pre-scalar
    T1CONbits.TCS = 0; // Setting the oscillator
    IEC0bits.T1IE = 1;// Enable the interrupt
    IFS0bits.T1IF = 0;// Put the flag down
    IPC1bits.T1IP = 3;// Configure the Interrupt Priority
    T1CONbits.TON = 1;// Turn the timer on
}