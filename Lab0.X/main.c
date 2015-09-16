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
#define SYS_FREQ (8000000000L)
#define TOGGLES_PER_SEC 2
#define CORE_TICK_RATE (SYS_FREQ/2/TOGGLES_PER_SEC)
//TODO: Define states of the state machine
typedef enum stateTypeEnum{
    led3on, led2on, led1on, waitpush, waitrelease, debouncePress, debounceRelease, debounceRelease2
} stateType;

volatile stateType state1 = led3on;

int main() {
    
    //This function is necessary to use interrupts. 
    enableInterrupts();
    
    //TODO: Write each initialization function
    initSwitch1();
    initLEDs();
    initTimer2();
    initTimer1();
    
    while(1){
        switch(state1) {
            
            case led3on:
                if(IFS1bits.CNDIF==1) turnOnLED(3);
                    break;  
            case waitrelease: 
                if(IFS0bits.T1IF==1);
                    break;
            case led2on: 
                if(IFS1bits.CNDIF==1) turnOnLED(2);
                    break;     
            case led1on:
                if(IFS1bits.CNDIF==1) turnOnLED(1);
                    break;
                
        }
            
        }
        //TODO: Implement a state machine to create the desired functionality
        
    return 0;
}

//void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt() {
//    IFS1bits.CNDIF = 0;
//}
void __ISR(_TIMER_1_VECTOR, IPL7SRS) _T1Interrupt() {
    IFS0bits.T1IF = 0; 
    if(state1 == led3on) state1 = led2on; 
    else if (state1 == led2on) state1 = led1on;
    else if (state1 == led1on) state1 = led3on; 
}

void __ISR(_TIMER_2_VECTOR, IPL7SRS) _T2Interrupt() {
    IFS0bits.T2IF = 0; 
    if(state1 == led3on) state1 = led2on; 
    else if (state1 == led2on) state1 = led1on;
    else if (state1 == led1on) state1 = led3on; 
}