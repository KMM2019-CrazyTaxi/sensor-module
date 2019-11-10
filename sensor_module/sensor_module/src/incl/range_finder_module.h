/*
 * range_finder_module.h
 *
 * Created: 2019-11-10 14:23:34
 *  Author: herap603
 */ 


#ifndef RANGE_FINDER_MODULE_H_
#define RANGE_FINDER_MODULE_H_

#include "vl53l0x_api.h"

VL53L0X_Error range_finder_init(void);
VL53L0X_Error range_finder_get_single_meassurement(VL53L0X_RangingMeasurementData_t* data);

#endif /* RANGE_FINDER_MODULE_H_ */