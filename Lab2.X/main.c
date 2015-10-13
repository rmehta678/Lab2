// ******************************************************************************************* //
// File:         main.c
// Date:         
// Authors:      
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "keypad.h"
#include "config.h"
#include "interrupt.h"
typedef enum stateTypeEnum{
    waitpush, debouncePress, scanKeyPad, waitrelease, debounceRelease
} stateType;

volatile stateType currentstate = waitpush;
volatile int dummyVariable = 0;
volatile char c;
int main(void)
{
    SYSTEMConfigPerformance(80000000);
    enableInterrupts();
    initKeypad();
    initLCD();
    while (1) {
        switch(currentstate) {
        case waitpush:
           break; 
        case debouncePress:
            delayUs(50);
            c = scanKeypad();
            if(c==-1) {
                currentstate = waitpush;
            }
            else {
                currentstate = waitrelease;
            }        
            break;
        case waitrelease:
            break;
        case debounceRelease:
            delayUs(50);
            printCharLCD(c);
            break;           
        }
    }
    
    /* TESTING LCD*/
//    initLCD(); 
//    while(1)
//    {
//       testLCD();
//    }
   /*TESTING KEYPAD*/
 
 
// while(1)
//    {
//       ODCBbits.ODCB11 = 0;
//       LATBbits.LATB11 = 0; 
//       
//    }
}
    
 void __ISR(_CHANGE_NOTICE_VECTOR, IPL7SRS) _CNInterrupt( void ){
    dummyVariable = PORTB;
    IFS1bits.CNBIF = 0;
    if(currentstate==waitpush) {
        currentstate = debouncePress;
    }
    if(currentstate==waitrelease) {
        currentstate = debounceRelease;
    }  
 }
