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
	VL53L0X_Error status;
	uint32_t refSpadCount;
	uint8_t isApertureSpads, VhvSettings, PhaseCal;
	VL53L0X_RangingMeasurementData_t ranging_data;
	VL53L0X_Dev_t dev;
	
	dev.I2cDevAddr = 0x52;
	dev.comms_type = VL53L0X_COMMS_I2C;
	dev.comms_speed_khz = 10;
	VL53L0X_ResetDevice(&dev);
	
	PORTA = 0x01;
	status = VL53L0X_DataInit(&dev);
	if (status != VL53L0X_ERROR_NONE)
	{
		PORTA = 0xF1;
		while (1);
	}
	
	PORTA = 2;
	VL53L0X_StaticInit(&dev);
	if (status != VL53L0X_ERROR_NONE)
	{
		PORTA = 0xF2;
		while (1);
	}
	
	PORTA = 3;
	VL53L0X_PerformRefSpadManagement(&dev, &refSpadCount, &isApertureSpads);
	if (status != VL53L0X_ERROR_NONE)
	{
		PORTA = 0xF3;
		while (1);
	}
	
	PORTA = 4;
	VL53L0X_PerformRefCalibration(&dev, &VhvSettings, &PhaseCal);
	if (status != VL53L0X_ERROR_NONE)
	{
		PORTA = 0xF4;
		while (1);
	}
	
	PORTA = 5;
	VL53L0X_SetDeviceMode(&dev, VL53L0X_DEVICEMODE_SINGLE_RANGING);
	if (status != VL53L0X_ERROR_NONE)
	{
		PORTA = 0xF5;
		while (1);
	}
	
	PORTA = 6;
	VL53L0X_SetLimitCheckEnable(&dev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1);
	if (status != VL53L0X_ERROR_NONE)
	{
		PORTA = 0xF6;
		while (1);
	}
	
	PORTA = 7;
	VL53L0X_SetLimitCheckEnable(&dev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1);
	if (status != VL53L0X_ERROR_NONE)
	{
		PORTA = 0xF7;
		while (1);
	}
	
	PORTA = 8;
	VL53L0X_SetLimitCheckEnable(&dev, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, 1);
	if (status != VL53L0X_ERROR_NONE)
	{
		PORTA = 0xF8;
		while (1);
	}
	
	PORTA = 9;
	FixPoint1616_t f = 1.5;
	f *= 0.023;
	uint32_t i = 65536;
	f *= i;
	VL53L0X_SetLimitCheckValue(&dev, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, f);
	if (status != VL53L0X_ERROR_NONE)
	{
		PORTA = 0xF9;
		while (1);
	}
	
	PORTA = 10;	
	while (1)
	{
		VL53L0X_PerformSingleRangingMeasurement(&dev, &ranging_data);
		if (status != VL53L0X_ERROR_NONE)
		{
			PORTA = 0xFA;
			while (1);
		}
		PORTA = ranging_data.RangeMilliMeter >> 3;
	}
}

void debug_output_test(void)
{
	uint32_t data = 0xABCDEF12;
	utilities_debug_output((uint8_t*) &data, 4);
}