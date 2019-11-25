/*
 * hall_effect_sensor.c
 *
 * Created: 2019-11-25 13:05:48
 *  Author: herap603
 */

#include "interrupt.h"
#include "hall_effect_sensor.h"

void hall_effect_init(void)
{
	TCNT1 = 0;
	TCNT3 = 0;
}

// Right wheel interrupt routine
ISR(INT0_vect)
{
	const uint16_t counter_value = TCNT1;
	const uint16_t counter_to_speed_constant = 62500;
	uint8_t dm_per_s = counter_to_speed_constant / counter_value;
	TCNT1 = 0;
}

// Left wheel interrupt routine
ISR(INT1_vect)
{
	const uint16_t counter_value = TCNT3;
	const uint16_t counter_to_speed_constant = 62500;
	uint8_t dm_per_s = counter_to_speed_constant / counter_value;
	TCNT3 = 0;
}

