//       10        20        30        40        50        60        70
//--*----*----*----*----*----*----*----*----*----*----*----*----*----*----*----*

/******************************************************************************
 * A library for RingBuffer of UART2(for BG96)
 * This file is about the RingBuffer of UART2
 *
 * Copyright (c) 2019 Mobit technology inc.
 * @Author       : Damon
 * @Create time  : 03/11/2019
******************************************************************************/

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#ifdef __cplusplus
extern "C"{
#endif //__cplusplus

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <p24fxxxx.h> 

typedef struct
{
	char* head;
	unsigned int buflen;
	unsigned int readpos;
	unsigned int writepos;
	int roundsum;
} ringbuffer_t;

void ringbuffer_init(ringbuffer_t *rbuf,char * buf,unsigned int len);
int ringbuffer_write(ringbuffer_t* ringbuffer, char* buff,int len);
int ringbuffer_write_byte(ringbuffer_t* ringbuffer, char buf);
int ringbuffer_read(ringbuffer_t* ringbuffer, char* buff);
int ringbuffer_read_len(ringbuffer_t* ringbuffer, char* buff,int len);
void ringbuffer_clear(ringbuffer_t* ringbuffer);
unsigned int ringbuffer_buf_use_size(ringbuffer_t* ringbuffer);
unsigned int ringbuffer_buf_free_size(ringbuffer_t* ringbuffer);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //RINGBUFFER_H
