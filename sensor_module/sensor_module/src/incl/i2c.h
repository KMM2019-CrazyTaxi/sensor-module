/*
 * i2c.h
 *
 * Created: 2019-11-08 18:53:29
 *  Author: herap603
 */ 


#ifndef I2C_H_
#define I2C_H_

#include <asf.h>
#include <stdint.h>

/*
 * Sends a start bit on the I2C bus.
 *
 * Returns: The I2C status code (TWDR).
 * Assumes: All I2C registers except TWCR has been configured.
 */
uint8_t i2c_send_start_bit(void);

/*
 * Sends a stop bit on the I2C bus.
 *
 * Assumes: All I2C registers except TWCR has been configured.
 */
void i2c_send_stop_bit(void);

/*
 * Sends a data byte on the I2C bus.
 *
 * data: The data to transmit.
 * Returns: The I2C status code (TWDR).
 * Assumes: All I2C registers except TWCR has been configured.
 */
uint8_t i2c_send_data(const uint8_t data);

/*
 * Receives a data byte on the I2C bus.
 *
 * data: A pointer to a 1-byte buffer to save the data to.
 * send_ack: 1 if the I2C circuit should send an ACK after receiving
 * the data, else 0. An ACK should be sent to receive multiple bytes.
 * Returns: The I2C status code (TWDR).
 * Assumes: All I2C registers except TWCR has been configured.
 */
uint8_t i2c_receive_data(uint8_t* buffer, const uint8_t send_ack);

#endif /* I2C_H_ */