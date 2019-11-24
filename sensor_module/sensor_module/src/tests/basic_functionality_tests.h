/*
 * basic_io_test.h
 *
 * Created: 2019-11-05 10:15:19
 *  Author: herap603
 */ 


#ifndef BASIC_IO_TEST_H_
#define BASIC_IO_TEST_H_

#include <asf.h>
#include <stdint.h>

#include "accelerator_module.h"
#include "range_finder_module.h"
#include "vl53l0x_api.h"
#include "i2c.h"
#include "utilities.h"

/*
 * Counts from 0 (inclusive) to count_to (non-inclusive) repeatedly on port A.
 *
 * Assumes: Port A has been configured as output port.
 */
void run_regular_pulse_test(const uint8_t count_to);

/*
 * Configures the accelerator, continuously reads linear X acceleration and puts
 * the 8 MSB (including 2-complement bit) on PORTA.
 *
 * Assumes: Port A has been configure as output port.
 *          I2C has been configured.
 */
void accelerator_communication_test(void);

/*
 * Configures the range finder, continuously reads range and outputs the detected
 * in ~cm in PORTA.
 *
 * Assumes: Port A has been configured as output port.
 *          I2C has been configured.
 */
//void range_finder_communication_test(void);

/*
 * Combined test of range finder and accelerator. This test configures both sensors
 * and alternates between polling them. Sensor data it outputted to port a.
 *
 * Assumes: Porta A has been configured as output port.
 *          I2C has been configured.
 */
void combined_range_accelerator_test(void);

/*
 * Tests the debug output function by outputting 0xABCDEF12 to port a. Note that
 * the output is little endian.
 *
 * Assumes: Porta A has been configured as output port.
 */
void debug_output_test(void);

#endif /* BASIC_IO_TEST_H_ */