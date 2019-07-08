/* 
 * File:   011_CLRC663_SPI.h
 * Author: Micheal
 *
 * Created on 2019?3?28?, ??10:33
 */

#ifndef CLRC663_SPI_H
#define	CLRC663_SPI_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


    
void clrc663_SPI_init(void);
    /*!
  @brief Transmit and receive bytes via SPI.
  
    This function should provide the main SPI transfer functionality. SPI always reads a byte at the same time as it
    transmits a byte, the function should read from the `tx` array to transmit this data over MOSI and it should write
    the data received via MISO to the `rx` array.


  \param [in] len This is the number of bytes to be transfered.
  \param [in] tx The bytes from this array are transmitted, `len` bytes are always read from this argument. (MOSI)
  \param [out] rx The bytes received during transmission are written into this array, `len` bytes are always written.
               (MISO)
 */
uint16_t clrc663_SPI_transfer(const unsigned char * tx, unsigned char* rx, uint16_t len);

/*!
  @brief Selects the CLRC630 to accept data from the SPI bus.
  
    This function should set the Chip Select (NSS) line to the appropriate level such that the chip acceps the data
    on the SPI bus. For the CLRC630 this means setting the Chip Select line to a LOW logic level.

 */
void clrc663_SPI_select();

/*!
  @brief Deselects the CLRC630 to stop accepting data from the SPI bus.
  
    This function should set the Chip Select (NSS) line to the appropriate level such that the chip does not accept the
    data on the SPI bus. For the CLRC630 this means setting the Chip Select line to a HIGH logic level.

 */
void clrc663_SPI_unselect();
void test_spi(void);
#ifdef	__cplusplus
}
#endif

#endif	/* CLRC663_SPI_H */

