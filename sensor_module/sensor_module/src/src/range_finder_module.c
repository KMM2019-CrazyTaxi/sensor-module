/*
 * range_finder_module.c
 *
 * Created: 2019-11-10 14:25:40
 *  Author: herap603
 */ 

#include "range_finder_module.h"

static VL53L0X_Dev_t dev;

VL53L0X_Error range_finder_init(void)
{
	VL53L0X_Error status;
	uint32_t refSpadCount;
	uint8_t isApertureSpads, VhvSettings, PhaseCal;
	VL53L0X_RangingMeasurementData_t ranging_data;
		
	dev.I2cDevAddr = 0x52;
	dev.comms_type = VL53L0X_COMMS_I2C;
	dev.comms_speed_khz = 250;
		
	status = VL53L0X_DataInit(&dev);
	if (status != VL53L0X_ERROR_NONE) return status;
		
	status = VL53L0X_StaticInit(&dev);
	if (status != VL53L0X_ERROR_NONE) return status;
		
	status = VL53L0X_PerformRefSpadManagement(&dev, &refSpadCount, &isApertureSpads);
	if (status != VL53L0X_ERROR_NONE) return status;
		
	status = VL53L0X_PerformRefCalibration(&dev, &VhvSettings, &PhaseCal);
	if (status != VL53L0X_ERROR_NONE) return status;
		
	status = VL53L0X_SetDeviceMode(&dev, VL53L0X_DEVICEMODE_SINGLE_RANGING);
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

VL53L0X_Error range_finder_get_single_meassurement(VL53L0X_RangingMeasurementData_t* data)
{
	return VL53L0X_PerformSingleRangingMeasurement(&dev, data);
}