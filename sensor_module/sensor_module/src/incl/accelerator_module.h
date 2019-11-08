/*
 * accelerator_module.h
 *
 * Created: 2019-11-08 18:57:08
 *  Author: herap603
 */ 

#ifndef ACCELERATOR_MODULE_H_
#define ACCELERATOR_MODULE_H_

#include <stdint.h>

#include "i2c.h"

#define ACCELERATOR_ADR 0x32

/*
 * Initializes the accelerator module to read linear acceleration values.
 */
void accelerator_init(void);

/*
 * Sets the value of a register in the accelerator module.
 * 
 * reg_adr: The register address.
 * val: The value to write.
 * Assumes: I2C has been initialized.
 */
void accelerator_set_register_value(const uint8_t reg_adr, const uint8_t val);

/*
 * Reads the value of a register in the accelerator module.
 * 
 * reg_adr: The register address.
 * buffer: A pointer to a 1-byte buffer to save the data to.
 * Assumes: I2C has been initialized.
 */
void accelerator_get_register_value(const uint8_t reg_adr, uint8_t* buffer);

#endif /* ACCELERATOR_MODULE_H_ */