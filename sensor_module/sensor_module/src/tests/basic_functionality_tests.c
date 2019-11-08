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
	uint8_t sensor_value = 0;
	while (1)
	{
		accelerator_get_register_value(0x27, &sensor_value);
		if (sensor_value & 1)
		{
			accelerator_get_register_value(0x28, &sensor_value);
			accelerator_get_register_value(0x29, &sensor_value);
			PORTA = sensor_value;
		}
	}
}