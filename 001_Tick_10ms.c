//       10        20        30        40        50        60        70
//--*----*----*----*----*----*----*----*----*----*----*----*----*----*----*----*

//******************************************************************************
// File:   001_Tick_10ms.h
// Author: Hans Desmet
// Comments: Initial Real time 
// Revision history: Version 01.00
// Date 26/12/2018
//******************************************************************************
#include "007_Uart.h"
#include "001_Tick_10ms.h"
#include "008_RingBuffer.h"
#include "007_Uart.h"
#include "008_RingBuffer.h"

extern VAR Mobit;
extern NonVolatile NonVolatileDATA;

unsigned long MobitTimes = 0UL;// unit: ms

unsigned long Timer2Cnt = 0UL;// unit: ms

extern ringbuffer_t tmp_rbuf;
extern ringbuffer_t at_rbuf;
extern ringbuffer_t net_rbuf;

extern int IsTmpRingBufferAvailable();
extern char ReadByteFromTmpRingBuffer();

extern int IsTmpRingBufferAvailable();

extern bool WaitUartTmpRxIdle();

char tmpuse_buf[RX_RINGBUF_MAX_LEN] = {0};

extern int is_tcp_closed;

//******************************************************************************
//* Timer 1
//* Timer to make 10ms Tick
//******************************************************************************
void Configure_Tick_10ms(void)
{
    T1CONbits.TCKPS = 2;  // Select 1:64 Prescaler
    TMR1 = 0x00;          // Clear timer register
    PR1 = 2500;           // Load the period value
    IPC0bits.T1IP = T1IPL;// Set Timer 1 Interrupt Priority Level
    IFS0bits.T1IF = 0;    // Clear Timer 1 Interrupt Flag
    IEC0bits.T1IE = 1;    // Enable Timer1 interrupt
    T1CONbits.TON = 1;    // Start Timer
}

//******************************************************************************
//* Timer 2
//* Timer to make 10ms Tick
//******************************************************************************
void Configure_Tick2_10ms(void)
{
    T2CONbits.T32 = 0;
    T2CONbits.TCKPS = 2;  // Select 1:64 Prescaler
    TMR2 = 0x00;          // Clear timer register
    PR2 = 2500;           // Load the period value
    IPC1bits.T2IP = T2IPL;// Set Timer 2 Interrupt Priority Level
    IFS0bits.T2IF = 0;    // Clear Timer 2 Interrupt Flag
    IEC0bits.T2IE = 1;    // Enable Timer2 interrupt
    T2CONbits.TON = 1;    // Start Timer
}

//******************************************************************************
//* Timer 1 IRQ
//******************************************************************************
void __attribute__((__interrupt__, no_auto_psv)) _T1Interrupt(void)
{
    MobitTimes += 1;
    if(MobitTimes > 100000UL){
        MobitTimes = 0;
    }
    IFS0bits.T1IF = 0;// Clear Timer1 interrupt flag
}

//******************************************************************************
//* Timer 2 IRQ
//******************************************************************************
void __attribute__((__interrupt__, no_auto_psv)) _T2Interrupt(void)
{
    int i = 0;
    static char c = 0;
    static int tmp_len = 0;
    static int cnt_after = 0;
    static int cnt_tail = 0;

    static int cnt_tail_exp = 0;
    static int msg_done = 0;

    char *p = NULL;

    Timer2Cnt += 1;
    if(Timer2Cnt > 100000UL){
        Timer2Cnt = 0;
    }

    while (1) {
        // process till RX empty for a while
        if (0 == IsTmpRingBufferAvailable()) {
            WaitUartTmpRxIdle();
            break;
        }

        // printf("recv len = %d\n", IsTmpRingBufferAvailable());
        
        c = ReadByteFromTmpRingBuffer();

#if 0
        // when MSG1 lost tail
        // need next msg(MSG2 head) to complete MSG1
        if ('+' == c) {            
            cnt_after = 1;
        } else {
            if (cnt_after != 0) {
                cnt_after++;
            }
        }
#endif

        if (('C'==c) && (tmp_len>=4)) {
            if (('U'==tmpuse_buf[tmp_len-2]) && ('R'==tmpuse_buf[tmp_len-1]) &&
                ('Q'==tmpuse_buf[tmp_len-4]) && ('I'==tmpuse_buf[tmp_len-3]) &&
                ('+'==tmpuse_buf[tmp_len-5])) {

                if (0 == cnt_after) {
                    // process uncompleted ACKs + MSGs
                    // or skip the head "\r\n" too
                    if (tmp_len > 5) {// XXXs + "+QIUR"
                        printf("Receive ACKs: ");

                        for (i=0; i<(tmp_len-5); i++) {
                            printf("%c", tmpuse_buf[i]);
                            ringbuffer_write_byte(&at_rbuf,tmpuse_buf[i]);
                        }
                        printf("<<<\n");
                        
                        // if tail->head, printf may NG
                        // printf("Total ACKs = %s<<<\n", at_rbuf.head);
                    }
                } else {// process uncompleted MSGs + new MSGs again:
                    // just skip the previous uncompleted MSGs
                }
                
                // skip or redirection the previous head MSGs/ACKs
                tmp_len = 5;
                cnt_after = 5;

                msg_done = 0;
                cnt_tail = 0;
                cnt_tail_exp = 0;

                memset(tmpuse_buf, 0, RX_RINGBUF_MAX_LEN);
                strcpy(tmpuse_buf, "+QIUR");
            }
        } else {
            if (cnt_after != 0) {
                cnt_after++;
            }
        }
        
        tmpuse_buf[tmp_len++] = c;
        
        // "+QQQ"
        // "\r\n+QQQ"
        // "\r\n\r\n+QQQ"
        if (cnt_after >= sizeof("+QIURC: \"recv\"")) {
            if ((p=strstr(tmpuse_buf, "+QIURC: ")) != NULL) {
                if (0 == strncmp(p+sizeof("+QIURC: \"")-1, "recv", sizeof("recv")-1)) {
                    cnt_tail_exp = 2;
                } else {
                    cnt_tail_exp = 1;
                }
                
                // printf("len=%d, str = %s\n", sizeof("recv"), p+sizeof("+QIURC: \""));
            }
        }
        
        if (tmp_len >= 2) {
            if (('>'==tmpuse_buf[tmp_len-2]) && (' '==tmpuse_buf[tmp_len-1])) {
                printf("Receive XACKs: %s<<<\n", tmpuse_buf);

                for (i=0; i<tmp_len; i++) {
                    ringbuffer_write_byte(&at_rbuf,tmpuse_buf[i]);
                }
                
                msg_done = 0;
                cnt_tail = 0;
                cnt_tail_exp = 0;
                tmp_len = 0;                    
                memset(tmpuse_buf, 0, RX_RINGBUF_MAX_LEN);
            }
        }
        
        if (tmp_len > 4) {// skip "\r\n" & "\r\n\r\n"
            if (('\r'==tmpuse_buf[tmp_len-2]) && ('\n'==tmpuse_buf[tmp_len-1])) {
                if (cnt_tail_exp != 0) {
                    cnt_tail++;
                    
                    if (cnt_tail_exp == cnt_tail) {
                        cnt_after = 0;
                        msg_done = 1;
                    }
                } else {
                    msg_done = 1;
                }

                if (1 == msg_done) {
                    if ((cnt_tail_exp==cnt_tail) && (cnt_tail_exp!=0)) {
                        printf("Receive MSGs: %s<<<\n", tmpuse_buf);
                        
                        if ((p=strstr(tmpuse_buf, "+QIURC: ")) != NULL) {
                            if ((p=strstr(tmpuse_buf, "closed")) != NULL) {// TCP mode only
                                is_tcp_closed = 1;
                                printf("******* TCP Closed *******\n");
                            } else if ((p=strstr(tmpuse_buf, "recv")) != NULL) {// TCP or UDP
                                cnt_tail = 0;

                                ringbuffer_write_byte(&net_rbuf,'S');
                                ringbuffer_write_byte(&net_rbuf,'T');
                                ringbuffer_write_byte(&net_rbuf,'A');
;
                                for (i=(p-tmpuse_buf)+1; i<tmp_len; i++) {
                                    if (('\r'==tmpuse_buf[i-1]) && ('\n'==tmpuse_buf[i])) {
                                        cnt_tail++;
                                        if (cnt_tail >= 2) {
                                            break;
                                        }
                                        continue;
                                    }
                                    
                                    if (cnt_tail >= 1) {
                                        if (('\r'!=tmpuse_buf[i]) && ('\n'!=tmpuse_buf[i])) {
                                            ringbuffer_write_byte(&net_rbuf,tmpuse_buf[i]);
                                        }
                                    }
                                }

                                ringbuffer_write_byte(&net_rbuf,'E');
                                ringbuffer_write_byte(&net_rbuf,'N');
                                ringbuffer_write_byte(&net_rbuf,'D');

                                // printf("MSGs = %s\n", net_rbuf.head);
                            } else if ((p=strstr(tmpuse_buf, "incoming full")) != NULL) {// BG96 act as TCP server
                                printf("******* incoming full *******\n");
                            } else if ((p=strstr(tmpuse_buf, "incoming")) != NULL) {// BG96 act as TCP server
                                printf("******* incoming *******\n");
                            } else if ((p=strstr(tmpuse_buf, "pdpdeact")) != NULL) {
                                printf("******* pdpdeact *******\n");
                            } else {// invalid MSGs
                                printf("******* invalid MSGs *******\n");
                            }
                        } else {
                            // invalid MSGs
                        }
                    } else {
                        printf("Receive XACKs: %s<<<\n", tmpuse_buf);

                        for (i=0; i<tmp_len; i++) {
                            ringbuffer_write_byte(&at_rbuf,tmpuse_buf[i]);
                        }
                        
                        // printf("Total XACKs = %s\n", at_rbuf.head);
                    }

                    msg_done = 0;
                    cnt_tail = 0;
                    cnt_tail_exp = 0;
                    tmp_len = 0;                    
                    memset(tmpuse_buf, 0, RX_RINGBUF_MAX_LEN);
                }
            }
        }
    }
    
    if (0 == Timer2Cnt % 300) {
        // printf("timer2 trigger\r\n");
        printf("recv len = %d\n", IsTmpRingBufferAvailable());
    }

    IFS0bits.T2IF = 0;// Clear Timer2 interrupt flag
}

//******************************************************************************************
// FuncName: DelayMs
// Descriptions: delay some time(unit: millisecond)
//           (IN) val: how long to delay
// Return:   NONE
//******************************************************************************************
void delay_ms(unsigned long val)
{
    unsigned long start_time = GetTimeStamp();
    
    while (!isDelayTimeout(start_time,val));
}

//******************************************************************************************
// FuncName: DelayMs
// Descriptions: delay some time(unit: millisecond)
//           (IN) val: how long to delay
// Return:   NONE
//******************************************************************************************
void DelayMs(unsigned long val)
{
    unsigned long start_time = GetTimeStamp();
    
    while (!isDelayTimeout(start_time,val));
}

//******************************************************************************************
// FuncName: GetTimeStamp
// Descriptions: get the time stamp after program started
// Return:   number of milliseconds passed since the program started
//******************************************************************************************
unsigned long GetTimeStamp()
{
    return MobitTimes;
}
//******************************************************************************************
// FuncName: isDelayTimeout
// Descriptions: determine whether the timeout
// Return:   timeout->true,no timeout->false
//******************************************************************************************
bool isDelayTimeout(unsigned long start_time,unsigned long delayms)
{
    // delay at least 10ms
    if(delayms < 10){
        delayms = 10;
    }
    if(MobitTimes >= start_time){
        if((MobitTimes - start_time) > (delayms/10UL)){
            return 1;
        }
    }else{
        if((100000UL-start_time+MobitTimes) > (delayms/10UL)){
            return 1;
        }
    }
    return 0;
}

//******************************************************************************
//* END OF FILE
//******************************************************************************
