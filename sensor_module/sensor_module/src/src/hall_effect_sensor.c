/*
 * hall_effect_sensor.c
 *
 * Created: 2019-11-25 13:05:48
 *  Author: herap603
 */

#include "interrupt.h"

#include "hall_effect_sensor.h"
#include "sensor_data.h"

// Indicates if an overflow has occured since last hall effect interrupt.
static uint8_t cnt_1_overflow = 1;
static uint8_t cnt_3_overflow = 1;

// The speed for both wheels in dm / s.
static uint8_t speed_right = 0;
static uint8_t speed_left = 0;

// Utility function for updating the current speed.
static void update_speed(void)
{
	uint16_t speed = speed_right;
	speed += speed_left;
	speed >>= 1;
	write_new_sensor_data(SPEED_DATA_ID, (uint8_t*) &speed);
}

void hall_effect_init(void)
{
	TCNT1 = 0;
	TCNT3 = 0;
}

// Right wheel interrupt routine
ISR(INT0_vect)
{
	if (!cnt_1_overflow)
	{
		const uint16_t counter_value = TCNT1;
		const uint16_t counter_to_speed_constant = 62500;
		speed_right = counter_to_speed_constant / counter_value;
	}
	update_speed();
	cnt_1_overflow = 0;
	TCNT1 = 0;
}

// Right wheel interrupt routine. If this routine is triggered, no hall effect
// interrupt has occured during the last .25 seconds, which means our speed is
// less than 1 dm/s.
ISR(TIMER1_OVF_vect)
{
	speed_right = 0;
	update_speed();
	cnt_1_overflow = 1;
	TCNT1 = 0;
}

// Left wheel interrupt routine
ISR(INT1_vect)
{
	if (!cnt_3_overflow)
	{
		const uint16_t counter_value = TCNT3;
		const uint16_t counter_to_speed_constant = 62500;
		speed_left = counter_to_speed_constant / counter_value;
	}
	update_speed();
	cnt_3_overflow = 0;
	TCNT3 = 0;
}

// Left wheel interrupt routine. If this routine is triggered, no hall effect
// interrupt has occured during the last .25 seconds, which means our speed is
// less than 1 dm/s.
ISR(TIMER3_OVF_vect)
{
	speed_left = 0;
	update_speed();
	cnt_3_overflow = 1;
	TCNT3 = 0;	
}