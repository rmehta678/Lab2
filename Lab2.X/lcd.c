/*
 * File:   lcd.c
 * Authors:
 *
 * Created on December 31, 2014, 1:39 PM
 */

/* TODO: Make define statements for each pin used in the LCD
 */
#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"

#define LCD_RS LATCbits.LATC2 
#define LCD_E LATCbits.LATC4 

#define TRIS_D7 TRISEbits.TRISE1
#define TRIS_D6 TRISEbits.TRISE3
#define TRIS_D5 TRISEbits.TRISE5
#define TRIS_D4 TRISEbits.TRISE7 
#define TRIS_RS TRISCbits.TRISC2
#define TRIS_E TRISCbits.TRISC4 

#define D7 LATEbits.LATE1 
#define D6 LATEbits.LATE3
#define D5 LATEbits.LATE5 
#define D4 LATEbits.LATE7

#define ON 1
#define OFF 0

#define OUTPUT 0
#define INPUT 1
/* This function should take in a one-byte word and writes either the lower or upper
 * byte to the last four bits of LATB. Additionally, according to the LCD data sheet
 * It should set LCD_RS and LCD_E with the appropriate values and delays.
 * After these commands are issued, there should be a delay.
 * The command type is a simplification. From the data sheet, the RS is '1'
 * when you are simply writing a character. Otherwise, RS is '0'.
 */
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower){
    //TODO:
    if(lower == 0) {
        D7 = (word&0x80)>>7;
        D6 = (word&0x40)>>6;
        D5 = (word&0x20)>>5;
        D4 = (word&0x10)>>4;
    }
    if(lower == 1) {
        D4 = word&0x01;
        D5 = (word&0x02)>>1;
        D6 = (word&0x04)>>2;
        D7 = (word&0x08)>>3;
    }
    delayUs(1);
    LCD_RS = commandType; 
    delayUs(1);
    LCD_E = ON;
    delayUs(1);
    LCD_E = OFF;
    delayUs(delayAfter);
    
}

/* Using writeFourBits, this function should write the two bytes of a character
 * to the LCD.
 */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter){
    writeFourBits(word,commandType,delayAfter, 0);
    writeFourBits(word,commandType,delayAfter, 1);
    
    //TODO:writing 4 bits
}

/* Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
void printCharLCD(char c) {
    
    writeLCD(c, 1, 50);
    
    //TODO:
}
/*Initialize the LCD
 */
void initLCD(void) {
    int i = 0;
    // Setup D, RS, and E to be outputs (0).
    TRIS_D7 = OUTPUT;
    TRIS_D6 = OUTPUT;
    TRIS_D5 = OUTPUT;
    TRIS_D4 = OUTPUT;
    TRIS_RS = OUTPUT;
    TRIS_E  = OUTPUT;
    
    // Initilization sequence utilizes specific LCD commands before the general configuration
    // commands can be utilized. The first few initilition commands cannot be done using the
    // WriteLCD function. Additionally, the specific sequence and timing is very important.
    for (i = 0; i<=30; i++) {
        delayUs(505);
    }
   
    // Enable 4-bit interface
    writeFourBits(0x03, OFF, 4150, 1);
    writeFourBits(0x03, OFF, 101, 1);
    // Function Set (specifies data width, lines, and font.
    // 4-bit mode initialization is complete. We can now configure the various LCD
    // options to control how the LCD will function.
    writeLCD(0x32,OFF,40);
    // TODO: Display On/Off Control
        // Turn Display (D) Off
    writeLCD(0x28,OFF,40);
    // TODO: Clear Display (The delay is not specified in the data sheet at this point. You really need to have the clear display delay here.
    writeLCD(0x01,OFF,1650);
    // TODO: Entry Mode Set
        // Set Increment Display, No Shift (i.e. cursor move)
    writeLCD(0x06,OFF,40);
    // TODO: Display On/Off Control
        // Turn Display (D) On, Cursor (C) Off, and Blink(B) Off
    writeLCD(0x0F,OFF,40);
    
   // delayUs(5000);
}

/*
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void printStringLCD(const char* s) {
    //TODO:
    int i = 7;
    for (i = 0; i < strlen(s); i++) {
        printCharLCD(s[i]);
    } 
}

/*
 * Clear the display.
 */
void clearLCD(){
    writeLCD(0x01, 0, 1650); 
}

/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void moveCursorLCD(unsigned char x, unsigned char y){
    
    if(x == 0) {
        writeLCD(0x80 + y, 0, 40);
        }
    if(x == 1) {
        writeLCD(0x80 + 0x40 + y, 0, 40);
    }
}

/*
 * This function is called in lab1p2.c for testing purposes.
 * If everything is working properly, you should get this to look like the video on D2L
 * However, it is suggested that you test more than just this one function.
 */
void testLCD(){
    int i = 0;
    printCharLCD('c');
    for(i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
    for(i = 0; i < 1000; i++) delayUs(1000);
    printStringLCD("Hello!");
    moveCursorLCD(1, 2);
    for(i = 0; i < 1000; i++) delayUs(1000);
    printStringLCD("Hello!");
    for(i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
    for(i = 0; i < 1000; i++) delayUs(1000);

}