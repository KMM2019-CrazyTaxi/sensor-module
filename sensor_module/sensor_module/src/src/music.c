/*
 * music.c
 *
 * Created: 2019-12-13 21:56:09
 *  Author: grave
 */ 

#include "music.h"
#include "sensor_data.h"

#include <asf.h>

#define BETWEEN_NOTE_PAUSE 20000
#define HORN_DISTANCE_MM 1000

static const uint16_t SOUND_CNT_VALUES[25] =
	{
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
	
static const uint16_t NOTE_FREQ_MULT_2[25] =
	{
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
	
#define NOTE_LENGTH_DIVIDER 6

/*
// Blinka lilla stjärna.
#define N_NOTES 42

static uint8_t notes[N_NOTES] =
	{
		13, 13, 20, 20, 22, 22, 20,
		18, 18, 17, 17, 15, 15, 13,
		20, 20, 18, 18, 17, 17, 15,
		20, 20, 18, 18, 17, 17, 15,
		13, 13, 20, 20, 22, 22, 20,
		18, 18, 17, 17, 15, 15, 13
	};
	
static uint8_t note_length[N_NOTES] =
	{
		1, 1, 1, 1, 1, 1, 2,
		1, 1, 1, 1, 1, 1, 2,
		1, 1, 1, 1, 1, 1, 2,
		1, 1, 1, 1, 1, 1, 2,
		1, 1, 1, 1, 1, 1, 2,
		1, 1, 1, 1, 1, 1, 2
	};
*/

// Glassbilen
#define N_NOTES 16
static uint8_t notes[N_NOTES] =
	{
		8, 17, 20, 17, 13,
		8, 17, 20, 17, 13,
		8, 18, 18, 15, 15, 13
	};
	
static uint8_t note_length[N_NOTES] =
	{
		1, 1, 1, 1, 2,
		1, 1, 1, 1, 2,
		1, 2, 1, 2, 1, 5
	};
	
static uint8_t note_index = 0;
static uint16_t note_upd = 0;
static uint8_t curr_note_length = 0;

static void update_note_values(void)
{
	if (note_upd == NOTE_FREQ_MULT_2[notes[note_index]] / NOTE_LENGTH_DIVIDER)
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
	return curr_note_length >= note_length[note_index];
}

static uint8_t song_has_ended(void)
{
	return note_index >= N_NOTES;
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
		PORTA = ~PORTA;
		update_note_values();
		if (note_has_ended())
		{
			return go_to_next_note();
		}
		else
		{
			++note_upd;
			return SOUND_CNT_VALUES[notes[note_index]];
		}
	}
	else if (*((uint16_t *) get_most_recent_sensor_data(RANGE_DATA_ID)) < HORN_DISTANCE_MM)
	{
		music_reset();
		return 1;
	}
	else
	{
		return 1;
	}
}