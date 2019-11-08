/*
 * basic_io_test.c
 *
 * Created: 2019-11-05 10:29:16
 *  Author: herap603
 */ 

#include "basic_functionality_tests.h"

void run_regular_pulse_test(const uint8_t count_to)
{
	while (1) {
		for (uint8_t pulse = 0; pulse < count_to; ++pulse) {
			PORTA = pulse;
			for (uint8_t delay_cnt = 1; delay_cnt != 0; ++delay_cnt) { }
		}
	}
}

void i2c_transmit_test(void)
{
	accelerator_init();
	uint8_t sensor_values[6];
	while (1)
	{
		if (accelerator_new_values_available())
		{
			accelerator_get_linear_acceleration(sensor_values);
			PORTA = sensor_values[1];
		}
		else
		{
			PORTA = 0xAB;
		}
	}
}