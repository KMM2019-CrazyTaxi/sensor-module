/*
 * songs.h
 *
 * Created: 2019-12-13 22:48:01
 *  Author: grave
 */ 


#ifndef SONGS_H_
#define SONGS_H_

#include <stdint.h>

typedef struct {
	uint8_t note_length_divider;
	uint8_t n_notes;
	uint8_t* note_pitch;
	uint8_t* note_length;
} song_t;

song_t* get_next_song(void);

#endif /* SONGS_H_ */