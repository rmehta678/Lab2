#include <xc.h>
#include "keypad.h"
#include "timer.h"

 #define col1 PORTBbits.RA2
 #define col2 PORTBbits.RA3
 #define col3 PORTBbits.RA4

 #define row1 ODCBbits.B11
 #define row2 ODCBbits.B12
 #define row3 ODCBbits.B13
 #define row4 ODCBbits.B14

#define INPUT 1
#define OUTPUT 0
  
/* Initialize the rows as ODC outputs and the columns as inputs with pull-up
 * resistors. Don't forget about other considerations...
 */
void initKeypad(void){
    
}

/* This function will be called AFTER you have determined that someone pressed
 * SOME key. This function is to figure out WHICH key has been pressed.
 * This function should return -1 if more than one key is pressed or if
 * no key is pressed at all. Otherwise, it should return the ASCII character of
 * the key that is pressed.
 */
char scanKeypad(void){
    char key = -1;
    
    return key;
}
