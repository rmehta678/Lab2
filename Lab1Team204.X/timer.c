/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"

void delayUs(unsigned int delay2){ 
    TMR2 = 0;
    T2CONbits.TCKPS = 3;
    T2CONbits.TCS = 0;
    PR2 = delay2*9;
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 1;
    while(IFS0bits.T2IF==0);
    T2CONbits.ON = 0;
    //TODO: Create a delay using timer 2 for "delay" microseconds.
}