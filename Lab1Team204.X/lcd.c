/*
 * File:   lcd.c
 * Authors:
 *
 * Created on December 31, 2014, 1:39 PM
 */

/* TODO: Make define statements for each pin used in the LCD
 */
#include <xc.h>
#include<sys/attribs.h>
#include "lcd.h"
#include "timer.h"

#define LCD_DATA  
#define LCD_RS  
#define LCD_E   

#define TRIS_D7 
#define TRIS_D6 
#define TRIS_D5 
#define TRIS_D4 
#define TRIS_RS 
#define TRIS_E  

#define D7  
#define D6
#define D5
#define D4

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
        D7 = (word&(0b10000000)>>7);
        D6 = (word&(0b01000000)>>6);
        D5 = (word&(0b00100000)>>5);
        D4 = (word&(0b00010000)>>4);
    }
    if(lower == 1) {
        D7 = (word&(0b00000001));
        D6 = (word&(0b00000010)>>1);
        D5 = (word&(0b00000100)>>2);
        D4 = (word&(0b00001000)>>3);
    }
    
    LCD_RS = commandType;    
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
    
    writeLCD(c, 1, 48);
    
    //TODO:
}
/*Initialize the LCD
 */
void initLCD(void) {
    
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
    delayUs(16000);
    // Enable 4-bit interface
    writeFourBits(0x30, OFF, 4100, 0);
    writeFourBits(0x30, OFF, 101, 0);
    // Function Set (specifies data width, lines, and font.
  

    // 4-bit mode initialization is complete. We can now configure the various LCD
    // options to control how the LCD will function.
    writeLCD(0x32,OFF,0);
    
    
   
  

    // TODO: Display On/Off Control
        // Turn Display (D) Off
    writeLCD(0x28,OFF,0);
    // TODO: Clear Display (The delay is not specified in the data sheet at this point. You really need to have the clear display delay here.
    writeLCD(0x08,OFF,0);
    // TODO: Entry Mode Set
        // Set Increment Display, No Shift (i.e. cursor move)
    writeLCD(0x01,OFF,0);
    // TODO: Display On/Off Control
        // Turn Display (D) On, Cursor (C) Off, and Blink(B) Off
    writeLCD(0x07,OFF,0);
}

/*
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void printStringLCD(const char* s) {
    //TODO:
    int i = 7;
    for (i = 7; i--; i=0) {
        printCharLCD(s[i]);
    } 
}

/*
 * Clear the display.
 */
void clearLCD(){
    writeLCD(0x01,1,1600); 
}

/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void moveCursorLCD(unsigned char x, unsigned char y){
    
    if(y == 1) {
        writeLCD(0x80 + (x-1), 0, 40);
        }
    if(y == 2) {
        writeLCD(0x80 + 0x40 + (x-1), 0, 40);
    }
}

/*
 * This function is called in lab1p2.c for testing purposes.
 * If everything is working properly, you should get this to look like the video on D2L
 * However, it is suggested that you test more than just this one function.
 */
void testLCD(){
    initLCD();
    int i = 0;
    printCharLCD('c');
    for(i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
    printStringLCD("Hello!");
    moveCursorLCD(1, 2);
    for(i = 0; i < 1000; i++) delayUs(1000);
    printStringLCD("Hello!");
    for(i = 0; i < 1000; i++) delayUs(1000);
}