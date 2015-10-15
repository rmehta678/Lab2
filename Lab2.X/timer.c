/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"

void initTimer2(){
    TMR2 = 0;
    T2CONbits.TCKPS = 0;
    T2CONbits.TCS = 0;
    IFS0bits.T2IF = 0;    
}

void delayUs(unsigned int delay){ 
    TMR2 = 0;
    if (delay == 0) return;
    PR2 = (delay*40) - 1;
    IFS0bits.T2IF = 0;
    T2CONbits.TON = 1;
    while(IFS0bits.T2IF==0);
    T2CONbits.TON = 0;
    //TODO: Create a delay using timer 2 for "delay" microseconds.
}
