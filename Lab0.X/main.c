/* 
 * File:   main.c
 * Author: rohan_mehta
 * Created on September 13, 2015, 12:21 PM
 *This program uses 3 LED's. The user pushes a button for any amount of time and the green LED (3) is turned on. 
 *If the user pushes a button for less than 2 seconds then the LED moves from LED 3 to LED 1. 
 * After this button press, if the user presses the button for less than 2 seconds the LED moves
 * from LED 1 to LED 2. If, after the initial button press the user presses the button for more than 2 seconds then
 * the LED 3 moves backwards to LED 2 on the RELEASE. Likewise, if at LED 2 the button is held for longer than 2 seconds then
 * the LED moves backwards to LED 1 on the RELEASE. At any point after the initial button button press an LED will be lighted. 
 */

/*NO MAGIC NUMBERS*/

#include <xc.h>
#include <sys/attribs.h>
#include "switch.h"
#include "timer.h"
#include "led.h"
#include "interrupt.h"
#include "config.h"

#define OUTPUT 0
#define INPUT 1
#define PRESS 0
#define RELEASE 1
#define PRESSED 0
#define ON 1
#define OFF 0

//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    led3, led2, led1, waitpush, waitrelease, debouncePress, debounceRelease, waitrelease2, nextstate, prevstate
} stateType;

volatile stateType state1 = prevstate;



int main() {
    
    //This function is necessary to use interrupts. 
    enableInterrupts();
    
    //TODO: Write each initialization function
    initSwitch1();
    initLEDs();
    initTimer2();
    initTimer1();
    
//    nextstate = led2;
//    prevstate = led1;
    
    
    while(1){
        switch(state1) {
            case waitpush:
                if (PORTDbits.RD6 == PRESSED) { 
                    state1 = debouncePress;
                }
                break;   

            case debouncePress:
                delayMs(2);
                T1CONbits.TON = ON;
                state1 = waitrelease;
                break;
                
            case waitrelease:
                if(IFS0bits.T1IF = OFF) {
                    state1 = debounceRelease;
                }
                break;
                
            case waitrelease2:
                if(IFS0bits.T1IF = ON) {
                    state1 = debounceRelease;
                }
                break;  
            case debounceRelease:
                delayMs(2);
                state1 = nextstate;
                break;
            case nextstate:
                if(nextstate == led1) {
                    state1 = led2;
                }
                else if(nextstate == led2) {
                    state1 = led3;
                }
                else if(nextstate == led3) {
                    state1 = led1;
                }
                break;
            case led1:
                turnOnLED(1);
                state1 = waitpush;
                break;
            case led2:
                turnOnLED(2);
                state1 = waitpush;
                break;
            case led3:
                turnOnLED(3);
                state1 = waitpush;
                break;
        }
    }
   
        //TODO: Implement a state machine to create the desired functionality
        
    return 0;
}


void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt() {
    IFS0bits.T1IF = OFF;   
    if(state1 == led1) prevstate = led3;
    if(state1 == led2) prevstate = led1;
    if(state1 == led3) prevstate = led2;
}
