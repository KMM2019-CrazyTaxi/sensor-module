/**
 * \file
 *
 * \brief User board initialization template
 *
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

static void io_pin_init(void)
{
	// Initiera io-portar.
	DDRA = 0xFF; // Alla pinnar p� A �r output.
	DDRB = 0x01; // PB0 �r output for SHTDWN p� range finder.
	__asm__ __volatile__ ("nop");
}

static void i2c_init(void)
{
	// S�tt p� str�m till TWI-krets.
	PRR0 = PRR0 & ~(1 << PRTWI);
	
	// Konfigurera SCL-frekvens.
	TWSR = 0x00; // Prescaler 1 ger grundfrekvens p� 1 MHz, s� m�jliga klockfrekvenser 3.9 - 1000 KHz (400 KHz max enl. protokoll).
	TWBR = 2; // Grundfrekvensen delas med 2*TWBR.
}

static void communication_init(void)
{
	i2c_init();
	// TODO Initialize SPI control registers.
}

void board_init(void)
{
	io_pin_init();
	communication_init();
}
