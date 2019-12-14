/*
 * songs.c
 *
 * Created: 2019-12-13 22:51:18
 *  Author: grave
 */ 

#include "songs.h"

static uint8_t glassbilen_pitch[16] =
{
	8, 17, 20, 17, 13,
	8, 17, 20, 17, 13,
	8, 18, 18, 15, 15, 13
};

static uint8_t glassbilen_length[16] =
{
	1, 1, 1, 1, 2,
	1, 1, 1, 1, 2,
	1, 2, 1, 2, 1, 3
};

static song_t glassbilen =
{
	6,
	16,
	glassbilen_pitch,
	glassbilen_length
};

static uint8_t blinka_pitch[14] =
{
	13, 13, 20, 20, 22, 22, 20,
	18, 18, 17, 17, 15, 15, 13
};

static uint8_t blinka_length[14] =
{
	1, 1, 1, 1, 1, 1, 2,
	1, 1, 1, 1, 1, 1, 2
};

static song_t blinka =
{
	6,
	14,
	blinka_pitch,
	blinka_length
};

static uint8_t cucaracha_pitch[17] =
{
	8, 8, 8, 13, 17,
	8, 8, 8, 13, 17,
	13, 13, 12, 12, 10, 10, 8
};

static uint8_t cucaracha_length[17] =
{
	1, 1, 1, 3, 2,
	1, 1, 1, 3, 6,
	2, 1, 1, 1, 1, 1, 3
};

static song_t cucaracha = 
{
	7,
	17,
	cucaracha_pitch,
	cucaracha_length
};

static uint8_t mr_bombay_pitch[10] =
{
	8, 13, 10,
	13, 13, 13, 13, 12, 10, 8
};

static uint8_t mr_bombay_length[10] =
{
	2, 2, 4,
	1, 1, 1, 1, 1, 1, 2
};

static song_t mr_bombay = 
{
	7,
	10,
	mr_bombay_pitch,
	mr_bombay_length
};

static uint8_t barbie_pitch[12] =
{
	17, 13, 17, 22, 18,
	15, 12, 15, 20, 17, 15, 13
};

static uint8_t barbie_length[12] =
{
	1, 1, 1, 1, 4,
	1, 1, 1, 1, 2, 1, 1
};

static song_t barbie_girl =
{
	5,
	12,
	barbie_pitch,
	barbie_length
};

static uint8_t rick_roll_pitch[14] =
{
	8, 10, 11, 8, 15, 15, 13,
	6, 8, 10, 6, 13, 13, 11
};

static uint8_t rick_roll_length[14] =
{
	1, 1, 1, 1, 3, 3, 6,
	1, 1, 1, 1, 3, 3, 6
};

static song_t rick_roll =
{
	6,
	14,
	rick_roll_pitch,
	rick_roll_length
};

static uint8_t troll_pitch[16] =
{
	6, 10, 13, 18, 
	17, 17, 13, 15, 15, 11, 13,
	1, 5, 8, 11, 10
};

static uint8_t troll_length[16] =
{
	1, 1, 1, 1,
	2, 1, 1, 2, 1, 1, 4,
	1, 1, 1, 1, 4
};

static song_t troll =
{
	6,
	16,
	troll_pitch,
	troll_length
};

static uint8_t oops_pitch[16] =
{
	20, 13, 12, 13, 15, 13,
	11, 11, 15, 18, 16,
	11, 18, 20, 18, 16
};

static uint8_t oops_length[16] =
{
	2, 2, 1, 1, 1, 4,
	1, 1, 1, 1, 4,
	1, 1, 1, 1, 4
};

static song_t oops =
{
	6,
	16,
	oops_pitch,
	oops_length
};

static uint8_t cotton_eye_joe_pitch[17] =
{
	15, 18, 15, 18, 15, 18, 15, 15,
	18, 15, 11, 11, 8, 11, 11, 8, 6
};

static uint8_t cotton_eye_joe_length[17] =
{
	1, 2, 1, 2, 1, 3, 2, 4,
	2, 2, 2, 1, 1, 2, 2, 1, 3
};

static song_t cotton_eye_joe =
{
	8,
	17,
	cotton_eye_joe_pitch,
	cotton_eye_joe_length
};

static uint8_t let_it_go_pitch[14] =
{
	13, 15, 16, 11, 20, 18,
	16, 15, 13, 13, 13, 13, 15, 16
};

static uint8_t let_it_go_length[14] =
{
	1, 1, 6, 1, 1, 7,
	1, 1, 1, 1, 2, 2, 1, 3
};

static song_t let_it_go =
{
	6,
	14,
	let_it_go_pitch,
	let_it_go_length
};

static uint8_t cantina_band_pitch[18] =
{
	13, 18, 13, 18, 13, 18, 13, 12, 13,
	13, 12, 13, 11, 10, 11, 10, 9, 6
};

static uint8_t cantina_band_length[18] =
{
	2, 2, 2, 2, 1, 2, 2, 1, 2,
	1, 1, 1, 2, 1, 1, 1, 3, 5,
};

static song_t cantina_band =
{
	8,
	18,
	cantina_band_pitch,
	cantina_band_length
};

static uint8_t shut_up_pitch[1] =
{
	0
};

static uint8_t shut_up_length[1] =
{
	1
};

static song_t shut_up =
{
	1,
	1,
	shut_up_pitch,
	shut_up_length
};

#define N_SONGS 12

static song_t* songs[N_SONGS] = 
{
	&glassbilen,
	&shut_up,
	&blinka,
	&cantina_band,
	&let_it_go,
	&cotton_eye_joe,
	&oops,
	&troll,
	&cucaracha,
	&mr_bombay,
	&barbie_girl,
	&rick_roll	
};

static uint8_t current_song = 0;

song_t* get_next_song(void)
{
	++current_song;
	if (current_song >= N_SONGS)
	{
		current_song = 0;
	}
	return songs[current_song];
}