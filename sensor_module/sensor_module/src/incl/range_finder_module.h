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

VL53L0X_Error start_continuous_meassurement(void);

VL53L0X_Error stop_continuous_meassurement(void);

#endif /* RANGE_FINDER_MODULE_H_ */