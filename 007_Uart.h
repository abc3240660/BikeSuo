//       10        20        30        40        50        60        70
//--*----*----*----*----*----*----*----*----*----*----*----*----*----*----*----*

/******************************************************************************
 * A library for PIC24F UART1(for debug) & UART2(for BG96)
 * This file is about the UART API of PIC24
 *
 * Copyright (c) 2019 Mobit technology inc.
 * @Author       : Damon
 * @Create time  : 03/11/2019
******************************************************************************/

#ifndef MUART_H
#define	MUART_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>

#define UART2_BUFFER_MAX_LEN 512

#define UART2_RX_BUFFER_MAX_LEN 1024

#define RX_RINGBUF_MAX_LEN 512

// for debug
void Uart1_Init(void);
void Uart2_Init(void);

// for BG96
int Uart2_Putc(char ch);
int Uart2_String(char *ch);
int Uart2_Printf(char *fmt,...);

// for BNO055
void Uart3_Init(void);
int Uart3_Putc(char ch);

#ifdef	__cplusplus
}
#endif

#endif	/* MUART_H */
