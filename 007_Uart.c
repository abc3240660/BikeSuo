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

#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#include <p24fxxxx.h>

#include "003_BG96.h"
#include "007_Uart.h"
#include "008_RingBuffer.h"

char Uart2_Send_Buf[UART2_BUFFER_MAX_LEN] = {0};

extern ringbuffer_t tmp_rbuf;
extern ringbuffer_t at_rbuf;
extern ringbuffer_t net_rbuf;

uint8_t Uart3_Buffer[64] = {0};
int Uart3_Use_Len = 0;

extern int rx_debug_flag;

extern int IsTmpRingBufferAvailable();

// 115200
void Uart1_Init(void)
{
    _RP22R = 3;// RD3
    _U1RXR = 23;// RD2
    
    _LATD3 = 1;             
    _TRISD2 = 1;            
    _TRISD3 = 0;            
    
    _LATD6 = 0;             
    _TRISD6 = 0;            
    
    U1MODE = 0X8808;        
    U1STA = 0X2400;         
    // 4M/(34+1) = 114285
    U1BRG = 34;            
    
    _U1TXIP = 3;            
    _U1RXIP = 7;            
    _U1TXIF = 0;
	_U1RXIF = 0;
	_U1TXIE = 0;           
	_U1RXIE = 1;            
}

// 115200
void Uart2_Init(void)
{
    _RP17R = 5;// RF5
    _U2RXR = 10;// RF4      
	
    _LATF5 = 1;            
    _TRISF4 = 1;            
    _TRISF5 = 0;            
    U2MODE = 0X8808;       
    U2STA = 0X2400;         
    U2BRG = 34;            
    
    _U2TXIP = 1;            
    _U2RXIP = 2;            
    _U2TXIF = 0;
	_U2RXIF = 0;
	_U2TXIE = 0;            
	_U2RXIE = 1; 
}

// 115200
void Uart3_Init(void)
{
	// PIC24FJ256 is 28
	// PIC24FJ1024 is 19
    _RP3R = 19;     //RP3(RD10) = U3TX         
    _U3RXR = 4;     //U3RXR     = RP4(RD9)      
	
    _LATD10 = 1;            
    _TRISD9 = 1;            
    _TRISD10 = 0;            
    U3MODE = 0X8808;       
    U3STA = 0X2400;         
    U3BRG = 34;            
    
    _U3TXIP = 1;            
    _U3RXIP = 2;            
    _U3TXIF = 0;
	_U3RXIF = 0;
	_U3TXIE = 0;   
    _U3RXIE = 1;
}

int fputc(int ch,FILE * f)
{
    U1TXREG = ch;
    while(_U1TXIF == 0);
    _U1TXIF = 0;
    return ch;
}

int Uart1_Putc(char ch)
{
    U1TXREG = ch;
    while(_U1TXIF == 0);
    _U1TXIF = 0;
    return ch;
}

int Uart2_Putc(char ch)
{
    U2TXREG = ch;
    while(_U2TXIF == 0);
    _U2TXIF = 0;
    return ch;
}

int Uart3_Putc(char ch)
{
    U3TXREG = ch;
    while(_U3TXIF == 0);
    _U3TXIF = 0;
    
//    printf("%.2X\r\n", (uint8_t)ch);
    
    return ch;
}

int uart3_write_bytes(char * buf,int len)
{
    int i = 0;
    for(i=0;i<len;i++){
        Uart3_Putc(buf[i]);
    }
    return len;
}

int Uart2_String(char *ch)
{
    int i=0;
    
    int len = strlen(ch);
    for(i=0;i<len;i++){
        Uart2_Putc(ch[i]);
    }
    return len;
}
int Uart2_Printf(char *fmt,...)
{
    short i,len;
    va_list ap;
    va_start(ap,fmt);
    len = vsprintf((char*)Uart2_Send_Buf,fmt,ap);
    va_end(ap);
    for(i=0;i<len;i++)
    {
        U2TXREG = Uart2_Send_Buf[i];
        while(_U2TXIF == 0);
        _U2TXIF = 0;
    }
    return len;
}

void __attribute__((__interrupt__,no_auto_psv)) _U2RXInterrupt(void)
{
    char temp = 0;

    do {
        temp = U2RXREG;
        //if (rx_debug_flag) {
        //    printf("%.2X-%c\n", temp, temp);
        //}
        _U2RXIF = 0;
        if (U2STAbits.OERR) {
            U2STAbits.OERR = 0;
        } else {
            ringbuffer_write_byte(&tmp_rbuf,temp);
        }            
    } while (U2STAbits.URXDA);
}

void __attribute__((__interrupt__,no_auto_psv)) _U1RXInterrupt(void)
{
    char temp = 0;
    
    do {
        temp = U1RXREG;
        // Uart1_Putc(temp);
        _U1RXIF = 0;
        if (U1STAbits.OERR) {
            U1STAbits.OERR = 0;
        } else {
            // printf("%.2X\n", temp);
            // ringbuffer_write_byte(&tmp_rbuf,temp);
            // printf("recv len = %d\n", IsTmpRingBufferAvailable());
        }
    } while (U1STAbits.URXDA);
}

void __attribute__((__interrupt__,no_auto_psv)) _U3RXInterrupt(void)
{
    char temp = 0;
    
    do {
        temp = U3RXREG;
        // printf("%.2X\r\n", (uint8_t)temp);
        _U3RXIF = 0;
        if (U3STAbits.OERR) {
            U3STAbits.OERR = 0;
        } else {
            Uart3_Buffer[Uart3_Use_Len++] = temp;
        }
    } while (U3STAbits.URXDA);
}
