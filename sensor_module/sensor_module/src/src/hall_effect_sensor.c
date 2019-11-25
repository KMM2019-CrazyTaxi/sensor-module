/*
 * hall_effect_sensor.c
 *
 * Created: 2019-11-25 13:05:48
 *  Author: herap603
 */

#include "interrupt.h" 

static uint8_t signals_left;
static uint8_t signals_right;

void hall_effect_init(void)
{
	signals_left = 0;
	signals_right = 0;
}

// Right wheel interrupt routine
ISR(INT0_vect)
{
	++signals_right;
}

// Left wheel interrupt routine
ISR(INT1_vect)
{
	++signals_left;
}