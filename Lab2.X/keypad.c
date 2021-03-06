#include <xc.h>
#include "keypad.h"
#include "timer.h"

 #define COL1 TRISBbits.TRISB4 //Pin3-RB4-J11 (30)
 #define COL2 TRISBbits.TRISB2 //Pin1-RB2-J11 (32)
 #define COL3 TRISBbits.TRISB0 //Pin5-RB0-J11 (34)

 #define ODCROW1 ODCBbits.ODCB10 //Pin2-RB10-J10 (47)
 #define ODCROW2 ODCBbits.ODCB14 //Pin7-RB14-J10 (59)
 #define ODCROW3 ODCGbits.ODCG6 //Pin6-RA9-J10 (55)
 #define ODCROW4 ODCGbits.ODCG8 //Pin4-RG8-J10 (57)

#define ROW1 TRISBbits.TRISB10
#define ROW2 TRISBbits.TRISB14
#define ROW3 TRISGbits.TRISG6
#define ROW4 TRISGbits.TRISG8

#define OVERALLINTERRUPT CNCONBbits.ON

#define REGISTERINTERRUPTB4 CNENBbits.CNIEB4
#define REGISTERINTERRUPTB2 CNENBbits.CNIEB2
#define REGISTERINTERRUPTB0 CNENBbits.CNIEB0

#define FLAG IFS1bits.CNBIF
#define INTERRUPTPRIORITY IPC8bits.CNIP 
#define INTERRUPTSUBPRIORITY IPC8bits.CNIS
#define INTERRUPTB IEC1bits.CNBIE

#define WRITEROW1 LATBbits.LATB10
#define WRITEROW2 LATBbits.LATB14
#define WRITEROW3 LATGbits.LATG6
#define WRITEROW4 LATGbits.LATG8

#define READCOL1 PORTBbits.RB4
#define READCOL2 PORTBbits.RB2
#define READCOL3 PORTBbits.RB0

#define INPUT 1
#define OUTPUT 0

#define ENABLED 1
#define DISABLED 0

#define DIGITAL 0

#define PRESSED 0
#define RELEASED 1

#define HIGH 0
#define LOW 1

volatile int counter = 0;
  
/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */
void initKeypad(void){
    
    ANSELBbits.ANSB4 = DIGITAL;
    ANSELBbits.ANSB2 = DIGITAL;
    ANSELBbits.ANSB0 = DIGITAL;
//    ANSELBbits.ANSB5 = DIGITAL;
//    ANSELBbits.ANSB11 = DIGITAL;
//    ANSELGbits.ANSG6 = DIGITAL;
//    ANSELGbits.ANSG8 = DIGITAL;
    
    COL1 = INPUT;
    COL2 = INPUT;
    COL3 = INPUT; 
    
    ROW1 = OUTPUT;
    ROW2 = OUTPUT;
    ROW3 = OUTPUT;
    ROW4 = OUTPUT;
    
    ODCROW1 = ENABLED;
    ODCROW2 = ENABLED;
    ODCROW3 = ENABLED;
    ODCROW4 = ENABLED;
    
    WRITEROW1 = HIGH;
    WRITEROW2 = HIGH;
    WRITEROW3 = HIGH;
    WRITEROW4 = HIGH;
    
    OVERALLINTERRUPT = ENABLED;                  // Enable overall interrupt
    REGISTERINTERRUPTB4 = ENABLED;         // Enable pin CN
    REGISTERINTERRUPTB2 = ENABLED;
    REGISTERINTERRUPTB0 = ENABLED;
    INTERRUPTPRIORITY = 7;                  // Configure interrupt priority
    INTERRUPTSUBPRIORITY = 7;                  // Configure the interrupt sub-priority
    INTERRUPTB = ENABLED;           // Enable interrupt for B pins
    FLAG = DISABLED;                 // Put down the flag
    

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
    counter = 0;
    //consider a different interrupt bit because how is the keypad supposed to recognize presses if the CN is disabled
    INTERRUPTB = DISABLED;
    
    WRITEROW1 = HIGH;
    WRITEROW2 = LOW;
    WRITEROW3 = LOW;
    WRITEROW4 = LOW;
    delayUs(10);
    if((READCOL1==PRESSED)&&(READCOL2==RELEASED)&&(READCOL3==RELEASED)) {
        key= '1';
        counter = counter+1;
    }
    else if((READCOL1==RELEASED)&&(READCOL2==PRESSED)&&(READCOL3==RELEASED)) {
        key= '2';
        counter = counter+1;
    } 
    else if((READCOL1==RELEASED)&&(READCOL2==RELEASED)&&(READCOL3==PRESSED)){
        key= '3';
        counter = counter+1;
    }
    WRITEROW1 = LOW;
    WRITEROW2 = HIGH;
    WRITEROW3 = LOW;
    WRITEROW4 = LOW;
    delayUs(10);
    if((READCOL1==PRESSED)&&(READCOL2==RELEASED)&&(READCOL3==RELEASED)) {    
        key= '4'; 
        counter = counter+1;
    }
    else if((READCOL1==RELEASED)&&(READCOL2==PRESSED)&&(READCOL3==RELEASED)) {
        key= '5';
        counter = counter+1;
    }
    else if((READCOL1==RELEASED)&&(READCOL2==RELEASED)&&(READCOL3==PRESSED)){
        key= '6';
        counter = counter+1;
    }
    WRITEROW1 = LOW;
    WRITEROW2 = LOW;
    WRITEROW3 = HIGH;
    WRITEROW4 = LOW;
    delayUs(10);
    if((READCOL1==PRESSED)&&(READCOL2==RELEASED)&&(READCOL3==RELEASED)) {
        key= '7'; 
        counter = counter+1;
    }
    else if((READCOL1==RELEASED)&&(READCOL2==PRESSED)&&(READCOL3==RELEASED)) {
        key= '8';
        counter = counter+1;
    }
    else if((READCOL1==RELEASED)&&(READCOL2==RELEASED)&&(READCOL3==PRESSED)){
        key= '9';
        counter = counter+1;
    }
    WRITEROW1 = LOW;
    WRITEROW2 = LOW;
    WRITEROW3 = LOW;
    WRITEROW4 = HIGH;
    delayUs(10);
    if((READCOL1==PRESSED)&&(READCOL2==RELEASED)&&(READCOL3==RELEASED)) {
        key = '*';
        counter = counter+1;
    }
    else if((READCOL1==RELEASED)&&(READCOL2==PRESSED)&&(READCOL3==RELEASED)) {
        key ='0';
        counter = counter+1;
    }
    else if((READCOL1==RELEASED)&&(READCOL2==RELEASED)&&(READCOL3==PRESSED)){
        key ='#';
        counter = counter+1;
    }
    delayUs(5);
    if(counter>1) {
        key = -1;
    }
    delayUs(1);
    WRITEROW1 = HIGH;
    WRITEROW2 = HIGH;
    WRITEROW3 = HIGH;
    WRITEROW4 = HIGH;
    delayUs(1);
    INTERRUPTB = ENABLED;
    return key;
}
