//       10        20        30        40        50        60        70
//--*----*----*----*----*----*----*----*----*----*----*----*----*----*----*----*

//******************************************************************************
// File:   001_Tick_10ms.h
// Author: Hans Desmet
// Comments: Initial Real Time file
// Revision history: Version 01.00
// Date 26/12/2018
//******************************************************************************

#ifndef __Tick_10ms_H
#define __Tick_10ms_H

#include <p24fxxxx.h> 
#include "---_Defines.h"
#include "---_Variables.h"

void Configure_Tick_10ms(void);
void Configure_Tick2_10ms(void);
void delay_ms(unsigned long val);
void DelayMs(unsigned long val);
unsigned long GetTimeStamp();
bool isDelayTimeout(unsigned long start_time,unsigned long delayms);

#endif //__Tick_10ms_H

//******************************************************************************
//* END OF FILE
//******************************************************************************
