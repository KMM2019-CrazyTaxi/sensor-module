/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
#include <asf.h>
#include <stdint.h>

#include "tests/basic_functionality_tests.h"
#include "utilities.h"
#include "spi.h"

int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).

	board_init();

	uint8_t spi_ready = 0;
	uint8_t spi_read;
	
	while (1) {
		spi_ready = 0;
		while (spi_ready == 0) {
			spi_read = spi_transcieve(SPI_ACK);
			spi_ready = spi_read == SPI_START;
			
			//PORTA = spi_read;
		}
	}
}
