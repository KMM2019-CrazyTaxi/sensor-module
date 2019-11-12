/*
 * range_finder_module.h
 *
 * Created: 2019-11-10 14:23:34
 *  Author: herap603
 */ 


#ifndef RANGE_FINDER_MODULE_H_
#define RANGE_FINDER_MODULE_H_

#include "vl53l0x_api.h"

/*
 * Initializes the range finder. Must be called before any data can be retrieved
 * from the sensor.
 */
VL53L0X_Error range_finder_init(void);

/*
 * Instructs the range finder to retrieve a single range meassurement. This function
 * blocks while the range finder performs the meassurement.
 *
 * data: A pointer to the struct where the data should be saved. See range finder API docs.
 */
VL53L0X_Error range_finder_get_single_meassurement(VL53L0X_RangingMeasurementData_t* data);

#endif /* RANGE_FINDER_MODULE_H_ */