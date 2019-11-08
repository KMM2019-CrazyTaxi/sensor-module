/*
 * accelerator_module.c
 *
 * Created: 2019-11-08 18:58:40
 *  Author: herap603
 */ 

#include "accelerator_module.h"

void accelerator_init(void)
{
	// Enable normal 100 Hz mode for linear XYZ acc.
	accelerator_set_register_value(0x20, 0x47);
}

void accelerator_set_register_value(const uint8_t reg_adr, const uint8_t val)
{
	i2c_send_start_bit();
	i2c_send_data(ACCELERATOR_ADR);
	i2c_send_data(reg_adr);
	i2c_send_data(val);
	i2c_send_stop_bit();
}

void accelerator_get_register_value(const uint8_t reg_adr, uint8_t* val)
{
	i2c_send_start_bit();
	i2c_send_data(ACCELERATOR_ADR);
	i2c_send_data(reg_adr);
	i2c_send_start_bit();
	i2c_send_data(ACCELERATOR_ADR | 1);
	i2c_receive_data(val, 0);
	i2c_send_stop_bit();
}
