/*
 * range_finder_module.h
 *
 * Created: 2019-11-10 14:23:34
 *  Author: herap603
 */ 


#ifndef RANGE_FINDER_MODULE_H_
#define RANGE_FINDER_MODULE_H_

#include "vl53l0x_api.h"

#define RANGE_FINDER_TIMING_BUDGET_MS 30
#define RANGE_FINDER_BETWEEN_MEASSUREMENT_TIME_MS 3

/*
 * Initializes the range finder. Must be called before any data can be retrieved
 * from the sensor.
 */
VL53L0X_Error range_finder_init(void);

/*
 * Performs setup of range finder in continuous timed mode with interrupt when new
 * values is available. Does NOT enable global interrupt.
 */
VL53L0X_Error start_continuous_meassurement(void);

/*
 * Stops continuous timed mode on the range finder. Blocks until the next new value
 * is received.
 */
VL53L0X_Error stop_continuous_meassurement(void);

/*
 * Retrieves a single data point from the range finder.
 *
 * Assumes: The range finder is not in continuous timed mode.
 */
VL53L0X_Error range_finder_get_single_meassurement(VL53L0X_RangingMeasurementData_t* range_data);

#endif /* RANGE_FINDER_MODULE_H_ */