//       10        20        30        40        50        60        70
//--*----*----*----*----*----*----*----*----*----*----*----*----*----*----*----*

/******************************************************************************
 * Entrance of Application
 * This file is entrance of APP
 *
 * Copyright (c) 2019 Mobit technology inc.
 * @Author       : Damon
 * @Create time  : 03/11/2019
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <p24fxxxx.h>

#include "---_Variables.h"

#include "001_Tick_10ms.h"
#include "002_CLRC663.h"
#include "003_BG96.h"
#include "004_LB1938.h"
#include "005_BNO055.h"
#include "006_Gpio.h"
#include "007_Uart.h"
#include "009_System.h"
#include "011_Spi.h"
#include "012_CLRC663_NFC.h"
#include "013_Protocol.h"

extern int temp;

VAR Mobit __attribute__((section("MobitVAR")));
NonVolatile NonVolatileDATA;

char one_svr_cmds[RX_RINGBUF_MAX_LEN] = {0};

int is_mode_nb = 0;
int is_tcp_closed = 0;

u8 g_bg96_imei[LEN_COMMON_USE] = "1234567890";
u8 g_bg96_iccid[LEN_COMMON_USE] = "ABCDEFGHIJK";

u8 g_first_md5[LEN_COMMON_USE] = "";

void process_bg96(void)
{
    int i = 0;
    int skip_flag = 0;

    if (0 == IsNetRingBufferAvailable()) {
        return;
    }

    while(1) {
        if (0 == IsNetRingBufferAvailable()) {
            WaitUartNetRxIdle();
            
            // buffer is empty for 50MS
            if (0 == IsNetRingBufferAvailable()) {
                break;
            }
        }
        one_svr_cmds[i++] = ReadByteFromNetRingBuffer();
        
        if (3 == i) {
            if ((one_svr_cmds[0]=='S')&&(one_svr_cmds[1]=='T')&&(one_svr_cmds[2]=='A')) {
                skip_flag = 0;
            } else {
                // invalid MSGs or overwritten: "XTA" -> just skip till net "STA"
                skip_flag = 1;
            }
        }
        
        if (i > 3) {
            if ((one_svr_cmds[i-3]=='S')&&(one_svr_cmds[i-2]=='T')&&(one_svr_cmds[i-3]=='A')) {
                if (i != 3) {
                    i = 3;
                    one_svr_cmds[0] = 'S';
                    one_svr_cmds[1] = 'T';
                    one_svr_cmds[2] = 'A';
                }

                skip_flag = 0;
            }
            
            if ((one_svr_cmds[i-3]=='E')&&(one_svr_cmds[i-2]=='N')&&(one_svr_cmds[i-1]=='D')) {
                if ((one_svr_cmds[0]=='S')&&(one_svr_cmds[1]=='T')&&(one_svr_cmds[2]=='A')) {
                    // process the valid MSGs
                    printf("process MSGs: %s\n", one_svr_cmds);
                    one_svr_cmds[i-3] = '\0';// D
                    one_svr_cmds[i-2] = '\0';// N
                    one_svr_cmds[i-1] = '\0';// E
                    if (('#'==one_svr_cmds[3]) && ('$'==one_svr_cmds[i-4])) {
                        one_svr_cmds[i-4] = '\0';// $
                        parse_mobit_msg(one_svr_cmds+3);
                    } else {
                        printf("Error MSGs %c:%c\n", one_svr_cmds[3], one_svr_cmds[i-4]);
                    }
                } else {
                    // skip the invalid MSGs
                    i = 0;
                }
                
                skip_flag = 0;
                memset(one_svr_cmds, 0, RX_RINGBUF_MAX_LEN);

                continue;
            }
        }
        
        if (1 == skip_flag) {
            i = 0;
        }
    }
}

int main(void)
{
    // unsigned long xxx = 0x1345678;
    unsigned long task_cnt = 0;

    System_Config();
    Configure_Tick_10ms();
    Configure_Tick2_10ms();
    GPIOB_Init();    
    Uart1_Init();
    Uart2_Init();
    Uart3_Init();  
    // clrc663_SPI_init();
    
	// Configure_CLRC663();
	// Configure_LB1938();
	// Configure_BNO055();

    // bno055_calibrate_demo();

    // printf("Hello PIC24F Uart1... 0x%.8lX\r\n", xxx);
    printf("Hello PIC24F Uart1...\r\n");
    
    // calc_first_md5();

    Configure_BG96();

    while(1)
    {
        // TcpClientDemo10s();
        // read_iso14443B_nfc_card();
        // bno055_demo();
        
        task_cnt++;
        
        if (is_tcp_closed) {
            TcpClose();
            ConnectTcp();
        }

        if (10 == task_cnt) {// 500MS -> process task1
            process_bg96();
        } else if (20 == task_cnt) {// 1000MS -> process task2
        } else if (30 == task_cnt) {// 1500MS -> process task3
        } else if (40 == task_cnt) {// 2000MS -> process task4
        } else if (50 == task_cnt) {// 2500MS -> process task4
            // ProcessEvent();
            HeartBeat();
            task_cnt = 0;
        }
        
        if ((task_cnt%16) < 8) {
            GPIOB_SetPin(task_cnt%8, 1);
        } else {
            GPIOB_SetPin(task_cnt%8, 0);
        }
        delay_ms(50);
    }
}

