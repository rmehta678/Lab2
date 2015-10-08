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
#include "config.h"
//#include "switch.h"
#include "timer.h"
//#include "leds.h"
#include "interrupt.h"
#include "lcd.h"


#define OUTPUT 0
#define INPUT 1
#define ON 1
#define OFF 0
#define minute 1
#define second 1
#define tenthssecond 1
#define hundredthssecond 1



typedef enum stateTypeEnum{
   waitpush, waitrelease, debouncePress, debounceRelease, debounceRelease2, running, stopped, reset
} stateType;
/* Please note that the configuration file has changed from lab 0.
 * the oscillator is now of a different frequency.
 */
volatile stateType currentstate = waitpush;
volatile stateType prevstate = debounceRelease;
volatile int long long count = 0;

int main(void) {
    SYSTEMConfigPerformance(80000000);
 //   enableInterrupts();
 //   int i;
    //Initializes each function
//    initSW2();
//    initLEDs();
//    initTimer1();
    initLCD();
//    TRISDbits.TRISD0 = 0;
    while(1){
        
    //    LATDbits.LATD0 ^= 1;
    //    for(i = 0; i < 1000;i++) delayUs(1000);
//        writeFourBits(0b00001010, 0, 1000, 1);
        testLCD();
    }
}
//        switch(currentstate) {
//            case waitpush:                         
//                break;
//            case debouncePress: 
//                delayUs(5000); //delaying for 5 milliseconds            
//                currentstate = waitrelease; //transition to wait release
//                break;
//            case waitrelease: 
//                break;
//            case debounceRelease:
//                delayUs(5000); //delay 5ms 
//                toggleLED();
//                currentstate = running;
//                break;
//           case debounceRelease2:
//                delayUs(5000);
//                toggleLED();
//                currentstate = stopped;
//            case running:
//                T1CONbits.TON = ON;
//                //print running to LCD
//                getTimeString(count);
//                currentstate = waitpush;
//                break;
//            case stopped:
//                T1CONbits.TON = OFF;
//                //print stopped to LCD
//                getTimeString(count);
//                currentstate = waitpush;
//                break;
//            case reset:
//                //display 00:00:00 on LCD screen
//                currentstate = waitpush;
//                break;
//        }
//        //TODO: Using a finite-state machine, define the behavior of the LEDs
//        //Debounce the switch
//        return 0;
//    }
//   
//
//void __ISR(_CHANGE_NOTICE_VECTOR, IPL7AUTO) _CNInterrupt(void){
//    int temp;
//    temp = PORTA;
//    IFS1bits.CNAIF = OFF;
//    
//    //turn reset switch down
//    if(currentstate == waitpush && CNSTATAbits.CNSTATA6==0) {
//        currentstate = debouncePress;
//    }
//    else if(currentstate == waitrelease && CNSTATAbits.CNSTATA6==0) {
//        currentstate = debounceRelease;
//    }
//    else if(currentstate == waitrelease && prevstate == debounceRelease && CNSTATAbits.CNSTATA7==1) {
//        currentstate = debounceRelease2;
//        prevstate = running;
//    }
//    else if(currentstate == waitrelease && prevstate == running && CNSTATAbits.CNSTATA7==1) { //add statement to check switch 1
//        currentstate = running;
//        prevstate = stopped;
//    }
//    else if(currentstate == waitpush && prevstate == running && CNSTATAbits.CNSTATA6==1) { //addstatement to check reset switch
//        currentstate = reset;
//        prevstate = stopped;
//    }
//}
//
//void __ISR(_TIMER_1_VECTOR, IPL7AUTO) _T1Interrupt(){
//    IFS0bits.T1IF = 0;
//    int count = 0;
//        count = count + 1;
//        prevstate = debounceRelease; 
//}
//
//void toggleLED() {
//    LATG ^= (0x1<<12);
//    LATG ^= (0x1<<14);
//}
//
//void getTimeString(count) {
//    minute = ((count*10)/360000)%10; 
//    second = (count/6000)%10;
//    
//   
//}
//    //TODO: Implement the interrupt to capture the press of the button
