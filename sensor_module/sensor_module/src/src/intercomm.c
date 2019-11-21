/*
 * inter_comm.c
 *
 * Created: 2019-11-21 13:37:08
 *  Author: anglo547
 */ 

#include <avr/interrupt.h>

#include "intercomm.h"
#include "spi.h"

uint8_t spi_aligned = 0;
uint8_t spi_read = 0;

// SPI Transmission/reception completed interrupt service routine
ISR(SPI_STC_vect)
{
	while (spi_aligned == 0) {
		spi_read = SPDR;
		PORTA = spi_read;
		spi_aligned = spi_read == SPI_START; // SPI is aligned if START was read
		if (spi_aligned) {
			spi_transcieve(SPI_ACK);
			
		} else {
			spi_transcieve(SPI_RESTART);
		}
	
		//PORTA = spi_read;
	}
	
	PORTA = 0xFF;
}

void enable_intercomm(void) {
	SPCR |= (1<<SPIE);
}

void disable_intercomm(void) {
	SPCR &= ~(1<<SPIE);
}