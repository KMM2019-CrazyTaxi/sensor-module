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

	// Configure counter 1 for hall effect right
	PRR0 = PRR0 & ~(1 << PRTIM1);	// Enable COUNT1 circuit.
	TCCR1A = 0;	// Normal mode
	TCCR1B = (0 << CS12) | (1 << CS11) | (1 << CS10);	// Prescaler 64 on system clock
	TIMSK1 = (1 << TOIE1);	// Enable overflow interrupt
	
	// Configure counter 3 for hall effect left
	PRR0 = PRR0 & ~(1 << PRTIM3);	// Enable COUNT3 circuit.
	TCCR3A = 0; // Normal mode
	TCCR3B = (0 << CS32) | (1 << CS31) | (1 << CS30);	// Prescaler 64 on system clock.
	TIMSK3 = (1 << TOIE3);	// Enable overflow interrupt
}

static void external_interrupt_init(void)
{
	// Ensure global pullup isn't disabled.
	MCUCR = MCUCR & ~(1 << PUD);
	
	// Enable INT0 interrupt on low signal for hall effect right
	EICRA = EICRA | (1 << ISC01);	// Falling edge
	EIMSK = EIMSK | (1 << INT0);	// Enable INT0
	DDRD = DDRD & ~(1 << 2);	// Enable input on appropriate pin
	PORTD = PORTD | (1 << PORTD2);	// Enable pullup
	
	// Enable INT1 interrupt on low signal for hall effect left
	EICRA = EICRA | (1 << ISC11);	// Falling edge
	EIMSK = EIMSK | (1 << INT1);	// Enable INT1
	DDRD = DDRD & ~(1 << 3);	// Enable input on appropriate pin
	PORTD = PORTD | (1 << PORTD3);	// Enable pullup
	
	// Enable INT2 interrupt on high signal for range finder.
	EICRA = EICRA | (1 << ISC20) | (1 << ISC21);	// Rising edge
	EIMSK = EIMSK | (1 << INT2);	// Enable INT2
	DDRB = DDRB & ~(1 << 2);	// Enable input on appropriate pin
	PORTB = PORTB | (1 << PORTB2);	// Enable pullup
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
