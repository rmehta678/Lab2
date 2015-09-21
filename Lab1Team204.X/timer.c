/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
//uses timer1
void initTimer1(){ //code from class
    TMR1 = 0;
    T1CONbits.TCKPS = 3;
    T1CONbits.TCS = 0;
    IFS0bits.T1IF = 0;
}

void delayMs(unsigned int delay1) {
    TMR1 = 0;
    PR1 = delay1*624;
    IFS0bits.T1IF = 0;
    T1CONbits.ON = 1;
    while(IFS0bits.T2IF==0);
    T1CONbits.ON = 0;   
}


//Uses timer 2
initTimer2(){ //code from class
    //TODO: Initialize Timer 2.
    TMR2 = 0;
    T2CONbits.TCKPS = 3;
    T2CONbits.TCS = 0;
    IFS0bits.T2IF = 0;
}

void delayUs(unsigned int delay2){ 
    TMR2 = 0;
    PR2 = delay2*.624;
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 1;
    while(IFS0bits.T2IF==0);
    T2CONbits.ON = 0;
    //TODO: Create a delay using timer 2 for "delay" microseconds.
}