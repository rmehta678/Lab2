#include <xc.h>
#include "keypad.h"
#include "timer.h"

 #define col1 TRISBbits.TRISB4
 #define col2 TRISBbits.TRISB2
 #define col3 TRISBbits.TRISB0

 #define odcrow1 ODCBbits.ODCB5
 #define odcrow2 ODCBbits.ODCB11
 #define odcrow3 ODCGbits.ODCG6
 #define odcrow4 ODCGbits.ODCG8
 
#define row1 TRISBbits.TRISB5
#define row2 TRISBbits.TRISB11
#define row3 TRISGbits.TRISG6
#define row4 TRISGbits.TRISG8

#define overallinterrupt CNCONBbits.ON
#define registerinterrupt CNENB
#define flag IFS1bits.CNBIF
#define interruptpriority IPC8bits.CNIP 
#define interruptsubpriority IPC8bits.CNIS
#define interruptB IEC1bits.CNBIE

#define writerow1 LATBbits.LATB5
#define writerow2 LATBbits.LATB11
#define writerow3 LATGbits.LATG6
#define writerow4 LATGbits.LATG8

#define readcol1 PORTBbits.RB4
#define readcol2 PORTBbits.RB2
#define readcol3 PORTBbits.RB0

#define INPUT 1
#define OUTPUT 0

#define ENABLED 1
#define DISABLED 0

#define DIGITAL 0

#define PRESSED 0
#define RELEASED 1

#define HIGH 0
#define LOW 1
  
/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */
void initKeypad(void){
    
    ANSELBbits.ANSB4 = DIGITAL;
    ANSELBbits.ANSB2 = DIGITAL;
    ANSELBbits.ANSB0 = DIGITAL;
    
    
    odcrow1 = OUTPUT;
    odcrow2 = OUTPUT;
    odcrow3 = OUTPUT;
    odcrow4 = OUTPUT;
    
    row1 = OUTPUT;
    row2 = OUTPUT;
    row3 = OUTPUT;
    row4 = OUTPUT;
    
    col1 = INPUT;
    col2 = INPUT;
    col3 = INPUT; 
    
    overallinterrupt = 1;                  // Enable overall interrupt
    registerinterrupt =  ENABLED;          // Enable pin C
    flag = 0;                              // Put down the flag
    interruptpriority = 7;                 // Configure interrupt priority
    interruptsubpriority = 7;              // Configure the interrupt sub-priority
    interruptB = ENABLED;                  // Enable interrupt for B pins
}

/* This function will be called AFTER you have determined that someone pressed
 * SOME key. This function is to figure out WHICH key has been pressed.
 * This function should return -1 if more than one key is pressed or if
 * no key is pressed at all. Otherwise, it should return the ASCII character of
 * the key that is pressed.
 */
char scanKeypad(void){
    //if row ODC is enabled
    char key = -1;
    interruptB = DISABLED;
    writerow1 = HIGH;
    writerow2 = LOW;
    writerow3 = LOW;
    writerow4 = LOW;
    if(readcol1==PRESSED&&readcol2==RELEASED&&readcol3==RELEASED) {
        return '1';
    }
    else if(readcol1==RELEASED&&readcol2==PRESSED&&readcol3==RELEASED) {
        return '2';
    } 
    else if(readcol1==RELEASED&&readcol2==RELEASED&&readcol3==PRESSED){
        return '3';
    }
    writerow1 = LOW;
    writerow2 = HIGH;
    writerow3 = LOW;
    writerow4 = LOW;
    if(readcol1&&readcol2==RELEASED&&readcol3==RELEASED) {
        return '4';
    }
    else if(readcol1==RELEASED&&readcol2==PRESSED&&readcol3==RELEASED) {
        return '5';
    }
    else if(readcol1==RELEASED&&readcol2==RELEASED&&readcol3==PRESSED){
        return '6';
    }
    writerow1 = LOW;
    writerow2 = LOW;
    writerow3 = HIGH;
    writerow4 = LOW;
    if(readcol1==PRESSED&&readcol2==RELEASED&&readcol3==RELEASED) {
        return '7';
    }
    else if(readcol1==RELEASED&&readcol2==PRESSED&&readcol3==RELEASED) {
        return '8';
    }
    else if(readcol1==RELEASED&&readcol2==RELEASED&&readcol3==PRESSED){
        return '9';
    }
    writerow1 = LOW;
    writerow2 = LOW;
    writerow3 = LOW;
    writerow4 = HIGH;
    if(readcol1==PRESSED&&readcol2==RELEASED&&readcol3==RELEASED) {
        return '*';
    }
    else if(readcol1==RELEASED&&readcol2==PRESSED&&readcol3==RELEASED) {
        return '0';
    }
    else if(readcol1==RELEASED&&readcol2==RELEASED&&readcol3==PRESSED){
        return '#';
    }
    else {
    return key;
    }
    interruptB = ENABLED;
}
