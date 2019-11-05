/**
 * \file
 *
 * \brief User board initialization template
 *
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

static void basic_io_test_init(void)
{
	// Initiera io-portar.
	DDRA = 0x00; // Alla pinnar på A är input.
	__asm__ __volatile__ ("nop");
}

static void i2c_init(void)
{
	// Sätt på ström till TWI-krets.
	PRR0 = PRR0 & ~(1 << PRTWI);
	
	// Konfigurera SCL-frekvens.
	TWSR = 0x00; // Prescaler 1 ger grund på 1 MHz, så möjliga klockfrekvenser 3.9 - 1000 KHz (400 KHz max enl. protokoll).
	TWBR = 50; // Ger SCL-frekvens 10 KHz.
	
	// Övrig konfigurering.
	unsigned char twcr_value = 0;
	twcr_value |= (0 << TWINT); // Clear interrupt bit.
	twcr_value |= (0 << TWIE); // Don't use interrupt for I2C transmissions.
	twcr_value |= (1 << TWEA); // Enable ACK when data received.
	twcr_value |= (1 << TWEN); // Enable I2C circuit.
	TWCR = twcr_value;	
}

static void communication_init(void)
{
	i2c_init();
	// TODO Initialize SPI control registers.
}

void board_init(void)
{
	communication_init();
}
