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
	
	while (1)
	{
		utilities_debug_output(get_most_recent_sensor_data(RANGE_DATA_ID), 1);
	}
	
	return 0;
}
