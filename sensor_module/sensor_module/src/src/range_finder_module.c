/*
 * range_finder_module.c
 *
 * Created: 2019-11-10 14:25:40
 *  Author: herap603
 */ 

#include "interrupt.h"
#include "range_finder_module.h"

#define RANGE_FINDER_BOOT_TIME_MS 2

static VL53L0X_Dev_t dev;

VL53L0X_Error range_finder_init(void)
{
	VL53L0X_Error status;
	uint32_t refSpadCount;
	uint8_t isApertureSpads, VhvSettings, PhaseCal;
		
	dev.I2cDevAddr = 0x52;
	dev.comms_type = VL53L0X_COMMS_I2C;
	dev.comms_speed_khz = 250;
	
	// Restart range finder.
	PORTB &= 0xFE;
	utilities_busy_wait_ms(RANGE_FINDER_BOOT_TIME_MS);
	PORTB |= 0x01;
	utilities_busy_wait_ms(RANGE_FINDER_BOOT_TIME_MS);
		
	status = VL53L0X_DataInit(&dev);
	if (status != VL53L0X_ERROR_NONE) return status;
		
	status = VL53L0X_StaticInit(&dev);
	if (status != VL53L0X_ERROR_NONE) return status;
		
	status = VL53L0X_PerformRefSpadManagement(&dev, &refSpadCount, &isApertureSpads);
	if (status != VL53L0X_ERROR_NONE) return status;
		
	status = VL53L0X_PerformRefCalibration(&dev, &VhvSettings, &PhaseCal);
	if (status != VL53L0X_ERROR_NONE) return status;
	
	status = VL53L0X_SetMeasurementTimingBudgetMicroSeconds(&dev, RANGE_FINDER_TIMING_BUDGET_MS * 1000);
	if (status != VL53L0X_ERROR_NONE) return status;
	
	status = VL53L0X_SetInterMeasurementPeriodMilliSeconds(&dev, RANGE_FINDER_BETWEEN_MEASSUREMENT_TIME_MS);
	if (status != VL53L0X_ERROR_NONE) return status;	
			
	status = VL53L0X_SetLimitCheckEnable(&dev, VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1);
	if (status != VL53L0X_ERROR_NONE) return status;
		
	status = VL53L0X_SetLimitCheckEnable(&dev, VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1);
	if (status != VL53L0X_ERROR_NONE) return status;
		
	status = VL53L0X_SetLimitCheckEnable(&dev, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, 1);
	if (status != VL53L0X_ERROR_NONE) return status;
		
	FixPoint1616_t f = 1.5;
	f *= 0.023;
	uint32_t i = 65536;
	f *= i;
	status = VL53L0X_SetLimitCheckValue(&dev, VL53L0X_CHECKENABLE_RANGE_IGNORE_THRESHOLD, f);
	
	return status;
}

VL53L0X_Error range_finder_get_single_meassurement(VL53L0X_RangingMeasurementData_t* range_data)
{
	return VL53L0X_PerformSingleRangingMeasurement(&dev, range_data);
}

VL53L0X_Error start_continuous_meassurement(void)
{
	VL53L0X_Error status;
	
	status = VL53L0X_SetDeviceMode(&dev, VL53L0X_DEVICEMODE_CONTINUOUS_TIMED_RANGING);
	if (status != VL53L0X_ERROR_NONE) return status;
	
	status = VL53L0X_SetGpioConfig(&dev, 0, VL53L0X_DEVICEMODE_CONTINUOUS_TIMED_RANGING, 
								   VL53L0X_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY, 
								   VL53L0X_INTERRUPTPOLARITY_HIGH);
	if (status != VL53L0X_ERROR_NONE) return status;
	
	status = VL53L0X_StartMeasurement(&dev);
	if (status != VL53L0X_ERROR_NONE) return status;
	
	return status;
}

VL53L0X_Error stop_continuous_meassurement(void)
{
	VL53L0X_Error status;
	uint32_t has_stopped = 0;
	VL53L0X_RangingMeasurementData_t data;
	
	status = VL53L0X_StopMeasurement(&dev);
	if (status != VL53L0X_ERROR_NONE) return status;
	
	while (!has_stopped) 
	{
		status = VL53L0X_GetStopCompletedStatus(&dev, &has_stopped);
		if (status != VL53L0X_ERROR_NONE) return status;	
	}
	
	status = VL53L0X_GetRangingMeasurementData(&dev, &data);
	if (status != VL53L0X_ERROR_NONE) return status;
	
	status = VL53L0X_ClearInterruptMask(&dev, 0);
	if (status != VL53L0X_ERROR_NONE) return status;
	
	return status;
}

ISR(INT2_vect)
{
	// TODO Error handling.
	
	VL53L0X_Error status;
	VL53L0X_RangingMeasurementData_t data;
	
	status = VL53L0X_GetRangingMeasurementData(&dev, &data);
	
	// TODO Write data to appropriate place.
	utilities_debug_output((uint8_t*) &data.RangeMilliMeter, 2);
	
	status = VL53L0X_ClearInterruptMask(&dev, VL53L0X_REG_SYSTEM_INTERRUPT_GPIO_NEW_SAMPLE_READY);
}