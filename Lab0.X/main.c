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
    led3, led2, led1, waitpush, waitrelease, debouncePress, debounceRelease, waitrelease2, next
} stateType;

volatile stateType currentstate = waitpush;
volatile stateType nextstate = led2;
volatile stateType prevstate = led3;


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
                delayMs(200);
                T1CONbits.TON = ON;
                currentstate = waitrelease;
                break;
                
            case waitrelease:
                if(IFS0bits.T1IF = OFF) {
                    currentstate = debounceRelease;
                }
                break;
                
            case waitrelease2:
                if(IFS0bits.T1IF = ON) {
                    nextstate = prevstate;
                }
                break;  
            case debounceRelease:
                delayMs(200);
                currentstate = nextstate;
                break;
            case next:
                if(currentstate == led1) {
                    nextstate = led2;
                }
                else if(currentstate == led2) {
                    nextstate = led3;
                }
                else if(currentstate == led3) {
                    nextstate = led1;
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


void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt() {
    IFS0bits.T1IF = OFF;   
    if(currentstate == led1) prevstate = led3;
    if(currentstate == led2) prevstate = led1;
    if(currentstate == led3) prevstate = led2;
}
