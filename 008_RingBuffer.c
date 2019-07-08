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

#include "008_RingBuffer.h"

/****
	* @brief init ringbuffer
	* @param ringbufer
	* @param
    * @param input buf length
	* @retval void
	*/
void ringbuffer_init(ringbuffer_t *rbuf,char * buf,unsigned int len)
{
    rbuf->head = buf;
    rbuf->buflen = len;
    rbuf->readpos = 0;
    rbuf->writepos = 0;
    rbuf->roundsum = 0;
}

/****
	* @brief write ringbufer
	* @param
	* @param    
    * @param
	* @retval write length
	*/
int ringbuffer_write(ringbuffer_t* ringbuffer, char* buff, int len)
{
	int i = 0;

	for (i = 0; i < len; i++)
	{
		ringbuffer->head[ringbuffer->writepos] = buff[i];
		ringbuffer->writepos++;
		if (ringbuffer->writepos >= ringbuffer->buflen)
		{
			ringbuffer->writepos = 0;
			ringbuffer->roundsum = 1;
		}
	}
	return len;
}

/****
	* @brief write single byte to ringbufer
	* @param
	* @param    
    * @param
	* @retval write length
	*/
int ringbuffer_write_byte(ringbuffer_t* ringbuffer, char buf)
{
	ringbuffer->head[ringbuffer->writepos] = buf;
	ringbuffer->writepos++;
	if (ringbuffer->writepos >= ringbuffer->buflen)
	{
		ringbuffer->writepos = 0;
		ringbuffer->roundsum = 1;
	}
	return 0;
}

/****
	* @brief read ringbuffer
	* @param
	* @param
	* @retval read byte length
	*/
int ringbuffer_read(ringbuffer_t* ringbuffer, char* buff)
{
	int len = 0;

	while ((ringbuffer->roundsum > 0) || (ringbuffer->readpos < ringbuffer->writepos))
	{
		buff[len] = ringbuffer->head[ringbuffer->readpos];
		ringbuffer->readpos++;
		len++;
		if (ringbuffer->readpos >= ringbuffer->buflen)
		{
			ringbuffer->readpos = 0;
			ringbuffer->roundsum = 0;
		}

	}
	return len;
}

/****
	* @brief Read a certain length
	* @param    
    * @param    
	* @param    length
	* @retval read byte length
	*/
int ringbuffer_read_len(ringbuffer_t* ringbuffer, char* buff, int len)
{
	int templen = 0,i = 0;
	int useData = ringbuffer_buf_use_size(ringbuffer);
	int datalen = 0;
	datalen = useData >= len ? len : useData;
    
	while (((ringbuffer->roundsum > 0) || (ringbuffer->readpos < ringbuffer->writepos)) && datalen > 0)
	{
		buff[i] = ringbuffer->head[ringbuffer->readpos];
		ringbuffer->readpos++;
		i++;
		if (ringbuffer->readpos >= ringbuffer->buflen)
		{
			ringbuffer->readpos = 0;
			ringbuffer->roundsum = 0;
		}
		datalen--;
	}
    
	return templen;
}

/****
	* @brief clear ringbuffer
	* @param 
	*/
void ringbuffer_clear(ringbuffer_t* ringbuffer)
{
	ringbuffer->readpos = 0;
	ringbuffer->writepos = 0;
    ringbuffer->roundsum = 0;
	return;
}

/****
	* @brief bytes used
	* @param
    * @retval used length 
	*/
unsigned int ringbuffer_buf_use_size(ringbuffer_t* ringbuffer)
{
	if (ringbuffer->writepos >= ringbuffer->readpos)
	{
		if (ringbuffer->roundsum)
		{
			ringbuffer->readpos = ringbuffer->writepos;
			return ringbuffer->buflen;
		}
		else
		{
			return ringbuffer->writepos - ringbuffer->readpos;
		}
	}
	else
	{
		if (ringbuffer->roundsum)
		{
			return ringbuffer->buflen - (ringbuffer->readpos - ringbuffer->writepos);
		}
		else
		{
			ringbuffer->writepos = ringbuffer->readpos;
			return 0;
		}
	}
}

/****
	* @brief bytes unused
	* @param
    * @retval unused length 
	*/
unsigned int ringbuffer_buf_free_size(ringbuffer_t* ringbuffer)
{
	return (unsigned int)(ringbuffer->buflen - ringbuffer_buf_use_size(ringbuffer));
}
