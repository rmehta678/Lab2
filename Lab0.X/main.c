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
    led3, led2, led1, waitpush, waitrelease, debouncePress, debounceRelease, debounceRelease2, waitrelease2, next, prev
} stateType;

//Initializes three states to initial states
volatile stateType currentstate = waitpush;
volatile stateType nextstate = led1;
volatile stateType prevstate = led3;
volatile int count = 0;

int main() {
    
    //This function is necessary to use interrupts. 
    enableInterrupts();
    
    //TODO: Write each initialization function
    initSwitch1();
    initLEDs();
    initTimer2();
    initTimer1();
    

    
    while(1){
        switch(currentstate) {
            case waitpush:
                if (PORTDbits.RD6 == PRESSED) { 
                    currentstate = debouncePress;
                }
                break;   

            case debouncePress:
                delayMs(5);
                T1CONbits.TON = ON;
                TMR1 = OFF;
                count = 0;
                currentstate = waitrelease;
                break;
                
            case waitrelease:
                if(PORTDbits.RD6 == RELEASE && count<2) {
                    currentstate = debounceRelease;
                    T1CONbits.TON = OFF;
                }
                
                else if (PORTDbits.RD6 == RELEASE && count>=2) {
                    currentstate = debounceRelease2;
                    T1CONbits.TON = OFF;
                }
                break;
//            case waitrelease2:
//                if(PORTDbits.RD6 == RELEASE && count>=2) {
//                    currentstate = debounceRelease2;
//                }
//                break;
                
            case debounceRelease:
                delayMs(5);
                count = 0;
                currentstate = next;              
                break;
                
            case debounceRelease2:
                delayMs(5);
                currentstate = prev;
                break;
                
            case next:
                if(nextstate == led1) {
                    currentstate = nextstate;
                    prevstate = led3;
                    nextstate = led2;
                    
                }
                else if(nextstate == led2) {
                    currentstate = nextstate;
                    prevstate = led1;
                    nextstate = led3;
                }
                else if(nextstate == led3) {  
                    currentstate = nextstate;
                    prevstate = led2;
                    nextstate = led1;   
                }
                break;
            case prev: 
                if(prevstate == led1) {
                    currentstate = prevstate;
                    nextstate = led2;
                    prevstate = led3;
                    
                }
                else if(prevstate == led2) {
                    currentstate = prevstate;
                    nextstate = led3;
                    prevstate = led1;
                    
                }
                else if(prevstate == led3) {
                    currentstate = prevstate;
                    nextstate = led1;
                    prevstate = led2;     
                }
                break;
            case led1:
                turnOnLED(1);
                currentstate = waitpush;
                break;
            case led2:
                turnOnLED(2);
                currentstate = waitpush;
                break;
            case led3:
                turnOnLED(3);
                currentstate = waitpush;
                break;
        }
        
        
    }
   
        //TODO: Implement a state machine to create the desired functionality
        
    return 0;
}

/*Interrupt service routine function utilizing timer 1. This function is entered as 
 * the flag goes up for timer 1 reaching the PR value. In other words, the user has held
 * the button down for more than 2 seconds. In this function the previous state is updated 
 * to be that which is previous to currentstate */

void __ISR(_TIMER_1_VECTOR, IPL3SRS) _T1Interrupt() {
    IFS0bits.T1IF = OFF;
//    if(currentstate == waitrelease) {
//        currentstate = waitrelease2;
//    }
        count++;
    

}
