/* 
 * File:   timer.c
 * Author: rohan_mehta
 *
 * Created on September 13, 2015, 12:20 PM
 */
#include <proc/p32mx470f512l.h>
#include <xc.h>

void initTimer1(){
 
    TMR1 = 0;// clear TMR1
    PR1 = 1221*2;// Initialize PR1
    T1CONbits.TCKPS = 3; // Initialize pre-scalar
    T1CONbits.TCS = 0; // Setting the oscillator
    IEC0bits.T1IE = 1;// Enable the interrupt
    IFS0bits.T1IF = 0;// Put the flag down
    IPC1bits.T1IP = 3;// Configure the Interrupt Priority
    T1CONbits.TON = 1;// Turn the timer on
}

initTimer2(){
    //TODO: Initialize Timer 2.
    TMR2 = 0;
    T2CONbits.TCKPS = 3;
    T2CONbits.TCS = 0;
    IFS0bits.T2IF = 0;
}

delayMs(int delay){
    TMR2 = 0;
    PR2 = delay*624;
    IFS0bits.T2IF = 0;
    T2CONbits.ON = 1;
    while(IFS0bits.T2IF==0);
    T2CONbits.ON = 0;
    //TODO: Using timer 2, create a delay
    // that is delay amount of ms.
}