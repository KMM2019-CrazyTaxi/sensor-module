/*
 * spi.h
 *
 * Created: 2019-11-19 14:31:16
 *  Author: anglo547
 */ 

#ifndef SPI_H_
#define SPI_H_


#include <stdint.h>


/* SPI port constants */
#define DD_SS PORTB4
#define DDR_SPI DDRB
#define DD_MOSI PORTB5
#define DD_MISO PORTB6
#define DD_SCK PORTB7

/* SPI value constants */
#define SPI_START 0xAA
#define SPI_NAN 0x00
#define SPI_FINISHED 0x66
#define SPI_RESTART 0x99
#define SPI_ERROR 0x55
#define SPI_ACK 0xEE


/*
 * Transmits and receives one byte simultanosly  on the SPI bus. 
 * Transmits the byte entered and returns the byte received.
 */
uint8_t spi_transcieve(uint8_t trans_data); 


/* 
 * Receives one byte on the SPI bus and returns it.
 */
uint8_t spi_slave_receive(void);




#endif /* SPI_H_ */