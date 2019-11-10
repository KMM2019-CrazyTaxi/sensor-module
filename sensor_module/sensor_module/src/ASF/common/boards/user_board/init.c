/**
 * \file
 *
 * \brief User board initialization template
 *
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

static void debug_io_init(void)
{
	// Initiera io-portar.
	DDRA = 0x00; // Alla pinnar på A är output.
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

static void communication_init(void)
{
	i2c_init();
	// TODO Initialize SPI control registers.
}

void board_init(void)
{
	debug_io_init();
	communication_init();
}
