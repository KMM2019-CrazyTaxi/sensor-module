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
 */
void i2c_transmit_test(void);

#endif /* BASIC_IO_TEST_H_ */