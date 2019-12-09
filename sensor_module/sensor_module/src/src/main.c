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

#define SOUND_CNT_TOGGLE 5000

#include "tests/basic_functionality_tests.h"
#include "utilities.h"
#include "intercomm.h"

#include "sensor_data.h"
#include "hall_effect_sensor.h"

int main (void)
{
	

	// Insert system clock initialization code here (sysclk_init()).
	board_init();
	range_finder_init();
	accelerator_init();
	start_continuous_meassurement();
	hall_effect_init();
	
	
	enable_intercomm();
	sei();
	
	uint32_t sound_cnt = 0;
	uint8_t sound_tgl = 0;
	
	while (1) {
		++sound_cnt;
		if (sound_cnt == SOUND_CNT_TOGGLE)
		{
			sound_cnt = 0;
			if (*((uint16_t*) get_most_recent_sensor_data(RANGE_DATA_ID)) < 1000)
			{
				sound_tgl = ~sound_tgl;
			}
			PORTA = sound_tgl;
		}
	}
	
	
	return 0;
}
