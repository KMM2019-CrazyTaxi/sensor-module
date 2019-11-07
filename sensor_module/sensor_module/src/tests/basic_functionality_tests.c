/*
 * basic_io_test.c
 *
 * Created: 2019-11-05 10:29:16
 *  Author: herap603
 */ 

#include "basic_functionality_tests.h"

void run_regular_pulse_test(const uint8_t count_to)
{
	while (1) {
		for (uint8_t pulse = 0; pulse < count_to; ++pulse) {
			PORTA = pulse;
			for (uint8_t delay_cnt = 1; delay_cnt != 0; ++delay_cnt) { }
		}
	}
}

static void i2c_wait_for_ack(void)
{
	PORTA = 3;
	while (!(TWCR & (1 << TWINT))) { }
	PORTA = 4;
}

static void i2c_send_start_bit(void)
{
	PORTA = 1;
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	PORTA = 2;
	i2c_wait_for_ack();
}

static void i2c_send_stop_bit(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	i2c_wait_for_ack();
}

static void i2c_send_data(const uint8_t data)
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	i2c_wait_for_ack();
}

void i2c_transmit_test(const uint8_t data)
{
	while (1)
	{
		i2c_send_start_bit();
		i2c_send_data(data);
		i2c_send_stop_bit();
	}
}