/*
 * accelerator_module.c
 *
 * Created: 2019-11-08 18:58:40
 *  Author: herap603
 */ 

#include "accelerator_module.h"
#include "utilities.h"
#include "interrupt.h"

void accelerator_init(void)
{
	// Enable normal 50 Hz mode for linear XYZ acceleration.
	accelerator_set_register_value(0x20, 0x47);
}

void accelerator_set_register_value(const uint8_t reg_adr, const uint8_t data)
{
	i2c_send_start_bit();
	i2c_send_data(ACCELERATOR_ADR);
	i2c_send_data(reg_adr);
	i2c_send_data(data);
	i2c_send_stop_bit();
}

void accelerator_get_register_value(const uint8_t reg_adr, uint8_t* buffer)
{
	i2c_send_start_bit();
	i2c_send_data(ACCELERATOR_ADR);
	i2c_send_data(reg_adr);
	i2c_send_start_bit();
	i2c_send_data(ACCELERATOR_ADR | 1);
	i2c_receive_data(buffer, 0);
	i2c_send_stop_bit();
}

void accelerator_get_multiple_register_values(const uint8_t start_adr, uint8_t* buffer, const uint8_t n_bytes)
{
	i2c_send_start_bit();
	i2c_send_data(ACCELERATOR_ADR);
	i2c_send_data(start_adr | 0x80);
	i2c_send_start_bit();
	i2c_send_data(ACCELERATOR_ADR | 1);
	for (uint8_t i = 0; i < n_bytes; ++i)
	{
		i2c_receive_data(buffer + i, i < n_bytes - 1);
	}
	i2c_send_stop_bit();
}

void accelerator_get_linear_acceleration(uint8_t* buffer)
{
	accelerator_get_multiple_register_values(ACCELERATOR_OUT_X_L_A, buffer, 6);
}

uint8_t accelerator_new_values_available(void)
{
	uint8_t status = 0;
	accelerator_get_register_value(ACCELERATOR_STATUS_REG_A, &status);
	return (status & 7) == 7;
}

ISR(TIMER0_COMPA_vect)
{
	uint8_t data[6];
	accelerator_get_linear_acceleration(data);
	utilities_debug_output(data, 2);
	
	// TODO Put data in correct place.
}