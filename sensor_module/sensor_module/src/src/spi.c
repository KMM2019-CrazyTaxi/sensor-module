/*
 * spi.c
 *
 * Created: 2019-11-19 14:31:26
 *  Author: anglo547
 */ 

#include <avr/interrupt.h>

#include "spi.h"

uint8_t spi_transcieve(uint8_t trans_data) {
	SPDR = trans_data;
	/* Wait for reception complete */
	while(!(SPSR & (1<<SPIF)));
	/* Return Data Register */
	return SPDR;
}

uint8_t spi_slave_receive(void) {
	/* Wait for the reception to complete */
	while(!(SPSR & (1<<SPIF)));
	/* Return Data Register value */
	return SPDR;
}

uint8_t spi_get_data_register_value(void) {
	return SPDR;
}