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

#define RUNLED 0
#define STOPLED 1

/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */
int main(void)
{

    
    while(1)
    {
        //TODO: Using a finite-state machine, define the behavior of the LEDs
        //Debounce the switch
    }
    
    return 0;
}

void __ISR(_CHANGE_NOTICE_VECTOR, IPL3SRS) _CNInterrupt(void){
    //TODO: Implement the interrupt to capture the press of the button

}