// ******************************************************************************************* //
//
// File:         main.c
// Date:         
// Authors:      
//
// Description: Part 1 for lab 1
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "switch.h"
#include "timer.h"
#include "leds.h"
#include "interrupt.h"
#include "config.h"


#define OUTPUT 0
#define INPUT 1
#define ON 1
#define OFF 0

typedef enum stateTypeEnum{
   waitpush, waitrelease, debouncePress, debounceRelease
} stateType;
/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */
volatile stateType currentstate = waitpush;

int main(void) {
    SYSTEMConfigPerformance(40000000);
    enableInterrupts();
    
    //Initializes each function
    initSW2();
    initLEDs();
    
    
    
    while(1){
        switch(currentstate) {
            case waitpush:                         
                break;
            case debouncePress: 
                delayUs(5000); //delaying for 5 milliseconds            
                currentstate = waitrelease; //transition to wait release
                break;
            case waitrelease: 
                break;
            case debounceRelease:
                delayUs(5000); //delay 5ms 
                toggleLED();
                currentstate = waitpush;
                break;    
            }
        }
        //TODO: Using a finite-state machine, define the behavior of the LEDs
        //Debounce the switch
        return 0;
    }
   

void __ISR(_CHANGE_NOTICE_VECTOR, IPL7AUTO) _CNInterrupt(void){
    int temp;
    temp = PORTA;
    IFS1bits.CNAIF = OFF;
    if(currentstate == waitpush) {
        currentstate = debouncePress;
    }
    if(currentstate == waitrelease) {
        currentstate = debounceRelease;
    }
 
}

void toggleLED() {
    LATG ^= (0x1<<12);
    LATG ^= (0x1<<14);
//        LATGbits.LATG12 = !LATGbits.LATG12;
//        LATGbits.LATG14 = !LATGbits.LATG14;
}
  
    //TODO: Implement the interrupt to capture the press of the button
