/* 
 * File:   interrupt.c
 * Author: rohan_mehta
 *
 * Created on September 13, 2015, 12:21 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

void enableInterrupts(){
    unsigned int val;

    // set the CP0 cause IV bit high
    asm volatile("mfc0   %0,$13" : "=r"(val));
    val |= 0x00800000;
    asm volatile("mtc0   %0,$13" : "+r"(val));

    INTCONSET = _INTCON_MVEC_MASK;

    unsigned int status = 0;
    asm volatile("ei    %0" : "=r"(status));
}
