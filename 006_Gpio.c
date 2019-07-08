//       10        20        30        40        50        60        70
//--*----*----*----*----*----*----*----*----*----*----*----*----*----*----*----*

/******************************************************************************
 * A library for PIC24F GPIO Configuration
 * This file is about the GPIO API of PIC24
 *
 * Copyright (c) 2019 Mobit technology inc.
 * @Author       : Damon
 * @Create time  : 03/11/2019
******************************************************************************/

#include <stdio.h>

#include <p24fxxxx.h>

#include "006_Gpio.h"

void GPIOB_Init(void)
{
    CM2CON = 0;
    ODCB &= 0xFFF0;// Open-Drain Control
    // AD1PCFGL |= 0x000F;
    LATB |= 0X0000;// Output Value:0-OFF 1-ON
    TRISB &= 0XFF00;// Direction:0-OUT 1-IN
}

void GPIOB_SetPin(short pin,char value)
{
    // PORTB: for read
    // LATB: for read -> modify -> write
    if(value){
        LATB |= (0x0001<<pin);
    }else{
        LATB &= (~0x0001<<pin);
    }
}
