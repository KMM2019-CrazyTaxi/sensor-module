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

void range_finder_communication_test(void)
{
	uint32_t refSpadCount;
	uint8_t isApertureSpads, VhvSettings, PhaseCal;
	VL53L0X_RangingMeasurementData_t ranging_data;
	VL53L0X_Dev_t dev;
	
	PORTA = 1;
	VL53L0X_DataInit(&dev);
	PORTA = 2;
	VL53L0X_StaticInit(&dev);
	PORTA = 3;
	VL53L0X_PerformRefSpadManagement(&dev, &refSpadCount, &isApertureSpads);
	PORTA = 4;
	VL53L0X_PerformRefCalibration(&dev, &VhvSettings, &PhaseCal);
	PORTA = 5;
	VL53L0X_SetDeviceMode(&dev, VL53L0X_DEVICEMODE_SINGLE_RANGING);
	PORTA = 6;
	VL53L0X_SetLimitCheckEnable(&dev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1);
	PORTA = 7;
	VL53L0X_SetLimitCheckEnable(&dev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1);
	PORTA = 8;
	VL53L0X_SetLimitCheckEnable(&dev, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, 1);
	PORTA = 9;
	VL53L0X_SetLimitCheckValue(&dev, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, (FixPoint1616_t)(1.5 * 0.023 * 65536));
	PORTA = 10;
	
	while (1)
	{
		VL53L0X_PerformSingleRangingMeasurement(&dev, &ranging_data);
		PORTA = ranging_data.RangeMilliMeter;
	}
}