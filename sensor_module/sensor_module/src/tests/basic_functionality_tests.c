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

void accelerator_communication_test(void)
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
	}
}

/*
void range_finder_communication_test(void)
{
	VL53L0X_Error status;
	VL53L0X_RangingMeasurementData_t ranging_data;

	status = range_finder_init();
	if (status != VL53L0X_ERROR_NONE) utilities_error(0xF1);
	
	while (1)
	{
		range_finder_get_single_meassurement(&ranging_data);
		if (status != VL53L0X_ERROR_NONE) utilities_error(0xF2);
		PORTA = ranging_data.RangeMilliMeter >> 3;
	}
}

void combined_range_accelerator_test(void)
{
	VL53L0X_Error range_status;
	VL53L0X_RangingMeasurementData_t range_data;
	uint8_t accelerator_data[6];
	uint8_t range_data_byte;
	
	accelerator_init();
	range_status = range_finder_init();
	if (range_status != VL53L0X_ERROR_NONE) utilities_error(0xF1);
	
	while (1)
	{
		range_status = range_finder_get_single_meassurement(&range_data);
		if (range_status != VL53L0X_ERROR_NONE) utilities_error(0xF2);
		range_data_byte = range_data.RangeMilliMeter >> 3;
		
		accelerator_get_linear_acceleration(accelerator_data);
		
		utilities_debug_output(&range_data_byte, 1);
		utilities_debug_output(accelerator_data + 1, 1);
	}
}
*/

void debug_output_test(void)
{
	uint32_t data = 0xABCDEF12;
	utilities_debug_output((uint8_t*) &data, 4);
}