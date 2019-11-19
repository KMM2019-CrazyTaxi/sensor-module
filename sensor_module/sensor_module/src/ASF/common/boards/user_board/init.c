/**
 * \file
 *
 * \brief User board initialization template
 *
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

#include "spi.h"

static void io_pin_init(void)
{
	// Initiera io-portar.
	DDRA = 0xFF; // Alla pinnar på A är output.
	DDRB = 0x01; // PB0 är output for SHTDWN på range finder.
	__asm__ __volatile__ ("nop");
}

static void i2c_init(void)
{
	// Sätt på ström till TWI-krets.
	PRR0 = PRR0 & ~(1 << PRTWI);
	
	// Konfigurera SCL-frekvens.
	TWSR = 0x00; // Prescaler 1 ger grundfrekvens på 1 MHz, så möjliga klockfrekvenser 3.9 - 1000 KHz (400 KHz max enl. protokoll).
	TWBR = 2; // Grundfrekvensen delas med 2*TWBR.
}

/*
 * Initiates the ATmega as a slave for SPI communication.
 */
static void spi_slave_init(void) 
{
	/* Set MISO output, all others input */
	DDR_SPI |= (1<<DD_MISO);
	//DDR_SPI &= ~((1<<DD_MOSI) | (1<<DD_SS) | (1<<DD_SCK));
	
	/* Enable SPI */
	SPCR = (1<<SPE);
	PORTA = 0xFF;
}

void board_init(void)
{
	io_pin_init();
	i2c_init();
	spi_slave_init();
}
