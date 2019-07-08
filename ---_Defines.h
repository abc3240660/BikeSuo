//       10        20        30        40        50        60        70
//--*----*----*----*----*----*----*----*----*----*----*----*----*----*----*----*

//******************************************************************************
// File:   ---_Defines.h
// Author: Hans Desmet
// Comments: Initial Define file
// Revision history: Version 01.00
// Date 26/12/2018
//******************************************************************************

#ifndef __DEFINE_H
#define __DEFINE_H

#include <p24fxxxx.h>                                                                  // include processor files - each processor file is guarded.  

#define         SW_Major_Version        1
#define         SW_Minor_Version        1
#define         SW_Release              1

#define         T1IPL                   5                                       // define Timer 1 IRQ priority levell for real tome Tick
#define         T2IPL                   1                                       // define Timer 2 IRQ priority levell for real tome Tick

#define         _XTAL_FREQ              12000000

#define false 0
#define true 1

typedef unsigned char bool;

#endif

//******************************************************************************
//* END OF FILE
//******************************************************************************
