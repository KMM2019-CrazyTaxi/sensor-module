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
#define F_CPU 16000000UL // 16 MHz

#include "tests/basic_functionality_tests.h"
#include "utilities.h"
#include "intercomm.h"

#include "sensor_data.h"

int main (void)
{
	// Insert system clock initialization code here (sysclk_init()).

	board_init();
	range_finder_init();
	accelerator_init();
	start_continuous_meassurement();
	
	//enable_intercomm();
	sei();
	
	uint8_t range_data = 0x10;
	uint8_t* read_range_data;
		
	while (1) {
		for (uint8_t i = 0; i < 0xFF; i++) {
				write_new_sensor_data(RANGE_DATA_ID, &range_data);
				read_range_data = get_most_recent_sensor_data(RANGE_DATA_ID);
				PORTA = *read_range_data;
				utilities_busy_wait_ms(100);
				
				range_data += 0x10;
		}
	}
	
	return 0;
}
