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

static void counter_init(void)
{
	// Configure counter 0 for accelerator interrupts.
	PRR0 = PRR0 & ~(1 << PRTIM0);	// Enable COUNT0 circuit.
	TCCR0A = (0 << COM0A1) | (1 << COM0A0) | (1 << WGM01) | (1 << WGM00);	// Configure output compare and ctc mode.
	TCCR0B = 0x05;	// Prescaler 1024 on system clock.
	TIMSK0 = (1 << OCIE0A);	// Enable interrupt on compare.
	OCR0A = 255;	// An interrupt is generated when counter reaches this value
}

static void external_interrupt_init(void)
{
	// Ensure global pullup isn't disabled.
	MCUCR = MCUCR & ~(1 << PUD);
	
	// Enable INT2 interrupt on high signal for range finder.
	EICRA = EICRA | (1 << ISC20) | (1 << ISC21);
	EIMSK = EIMSK | (1 << INT2);
	DDRB = DDRB & ~(1 << 2);
	PORTB = PORTB | (1 << PORTB2);
}

static void i2c_init(void)
{
	// Sätt på ström till TWI-krets.
	PRR0 = PRR0 & ~(1 << PRTWI);
	
	// Konfigurera SCL-frekvens.
	TWSR = 0x00; // Prescaler 1 ger grundfrekvens på 1 MHz, så möjliga klockfrekvenser 3.9 - 1000 KHz (400 KHz max enl. protokoll).
	TWBR = 12; // Grundfrekvensen delas med 2*TWBR.
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
}

void board_init(void)
{
	io_pin_init();
	i2c_init();
	spi_slave_init();
	counter_init();
	external_interrupt_init();
}
