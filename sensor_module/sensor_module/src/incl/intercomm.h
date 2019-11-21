/*
 * inter_comm.h
 *
 * Created: 2019-11-21 13:37:28
 *  Author: anglo547
 */ 


#ifndef INTERCOMM_H_
#define INTERCOMM_H_

#include <stdint.h>

/*
 * Enables inter modular communication by enabling SPI interrupts.
 */ 
void enable_intercomm(void);


/*
 * Disables inter modul
 */
void disable_intercomm(void);

#endif /* INTER_COMM_H_ */