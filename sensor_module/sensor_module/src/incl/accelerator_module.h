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
#define ACCELERATOR_CTRL_REG1_A 0x20
#define ACCELERATOR_OUT_X_L_A 0x28
#define ACCELERATOR_STATUS_REG_A 0x27

/*
 * Initializes the accelerator module to read linear acceleration values.
 */
void accelerator_init(void);

/*
 * Sets the value of a register in the accelerator module.
 * 
 * reg_adr: The register address.
 * data: The data to write.
 * Assumes: I2C has been initialized.
 */
void accelerator_set_register_value(const uint8_t reg_adr, const uint8_t data);

/*
 * Reads the value of a register in the accelerator module.
 * 
 * reg_adr: The register address.
 * buffer: A pointer to a 1-byte buffer to save the data to.
 * Assumes: I2C has been initialized.
 */
void accelerator_get_register_value(const uint8_t reg_adr, uint8_t* buffer);

/*
 * Reads the values of multiple consecutive registers in the accelerator module.
 * 
 * start_adr: The address of the first register.
 * buffer: A pointer to a buffer of size at least n_bytes to save the data to.
 * n_bytes: The number of bytes to read.
 * Assumes: I2C has been initialized.
 */
void accelerator_get_multiple_register_values(const uint8_t start_adr, uint8_t* buffer, const uint8_t n_bytes);

/*
 * Reads the values of the 3D linear acceleration.
 * 
 * buffer: A pointer to a buffer of at least 6 bytes to save the data to. The data is saved in order XYZ, little endian.
 * Assumes: I2C and the acceleration module has been initialized.
 */
void accelerator_get_linear_acceleration(uint8_t* buffer);

uint8_t accelerator_new_values_available(void);

#endif /* ACCELERATOR_MODULE_H_ */