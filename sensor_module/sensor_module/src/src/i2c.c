/*
 * i2c.c
 *
 * Created: 2019-11-08 18:55:27
 *  Author: herap603
 */

#include "i2c.h"

static uint8_t i2c_wait_for_ack(void)
{
	while (!(TWCR & (1 << TWINT))) { }
	return TWSR;
}

uint8_t i2c_send_start_bit(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	return i2c_wait_for_ack();
}

void i2c_send_stop_bit(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
}

uint8_t i2c_send_stop_start_bit(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWSTA) | (1 << TWEN);
	return i2c_wait_for_ack();
}

uint8_t i2c_send_data(const uint8_t data)
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	return i2c_wait_for_ack();
}

uint8_t i2c_receive_data(uint8_t* data, const uint8_t send_ack)
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (send_ack << TWEA);
	i2c_wait_for_ack();
	*data = TWDR;
	return TWSR;
}