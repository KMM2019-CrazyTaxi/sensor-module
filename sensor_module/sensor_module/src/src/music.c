/*
 * music.c
 *
 * Created: 2019-12-13 21:56:09
 *  Author: grave
 */ 

#include "music.h"
#include "sensor_data.h"
#include "songs.h"
#include "interrupt.h"
#include "utilities.h"

#include <asf.h>

#define BETWEEN_NOTE_PAUSE 30000
#define HORN_DISTANCE_MM 1000

static const uint16_t SOUND_CNT_VALUES[26] =
	{
		63492,
		5096,
		4810,
		4540,
		4285,
		4045,
		3818,
		3604,
		3401,
		3210,
		3030,
		2860,
		2700,
		2548,
		2405,
		2270,
		2143,
		2022,
		1909,
		1802,
		1701,
		1605,
		1515,
		1430,
		1350,
		1274
	};
	
static const uint16_t NOTE_FREQ_MULT_2[26] =
	{
		42,
		523,
		554,
		587,
		622,
		659,
		698,
		740,
		784,
		831,
		880,
		932,
		988,
		1047,
		1109,
		1175,
		1245,
		1319,
		1397,
		1480,
		1568,
		1661,
		1760,
		1865,
		1976,
		2093
	};

static song_t* current_song;
	
static uint8_t note_index = 0;
static uint16_t note_upd = 0;
static uint8_t curr_note_length = 0;

static void update_note_values(void)
{
	if (note_upd == NOTE_FREQ_MULT_2[current_song->note_pitch[note_index]]
	 / current_song->note_length_divider)
	{
		++curr_note_length;
		note_upd = 0;
	}
}

static uint16_t go_to_next_note(void)
{
	curr_note_length = 0;
	++note_index;
	return BETWEEN_NOTE_PAUSE;
}

static uint8_t note_has_ended(void)
{
	return curr_note_length >= current_song->note_length[note_index];
}

static uint8_t song_has_ended(void)
{
	return note_index >= current_song->n_notes;
}

static void music_reset(void)
{
	note_index = 0;
	note_upd = 0;
	curr_note_length = 0;
}

uint16_t update_sound(void)
{
	if (!song_has_ended())
	{
		if (current_song->note_pitch[note_index] != 0)
		{
			PORTA = ~PORTA;	
		}
		update_note_values();
		if (note_has_ended())
		{
			return go_to_next_note();
		}
		else
		{
			++note_upd;
			return SOUND_CNT_VALUES[current_song->note_pitch[note_index]];
		}
	}
	else if (*((uint16_t *) get_most_recent_sensor_data(RANGE_DATA_ID)) < HORN_DISTANCE_MM)
	{
		music_reset();
		//current_song = get_next_song();
		return 1;
	}
	else
	{
		return 1;
	}
}

void music_init(void)
{
	music_reset();
	current_song = get_next_song();
}

ISR(PCINT1_vect)
{
	if (PINB & (1 << PINB1))	// Only trigger on high, i.e. pressed button.
	{
		current_song = get_next_song();
		music_reset();
	}
}