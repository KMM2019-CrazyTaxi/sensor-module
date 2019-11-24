/*
 * inter_comm.c
 *
 * Created: 2019-11-21 13:37:08
 *  Author: anglo547
 */ 

#include <avr/interrupt.h>

#include "intercomm.h"
#include "spi.h"

#define MAX_ALIGN_ATTEMPTS 5
#define MAX_COMM_ATTEMPTS 5

void send_status_and_data_packet(void);

static uint8_t spi_aligned = 0;
static uint8_t spi_read = 0;
static uint8_t spi_finished = 0;


/* Temporary structure of data to send, will be updated. */
static uint8_t check_byte = 0;

static uint8_t status_1 = 0x01;
static uint8_t status_2 = 0x02;

static uint8_t acc_x_1 = 0x03;
static uint8_t acc_x_2 = 0x04;
static uint8_t acc_y_1 = 0x05;
static uint8_t acc_y_2 = 0x06;
static uint8_t acc_z_1 = 0x07;
static uint8_t acc_z_2 = 0x08;

static uint8_t dist = 0x09;

static uint8_t speed = 0x0A;

// SPI Transmission/reception completed interrupt service routine
ISR(SPI_STC_vect)
{	
	uint8_t comm_attempts = 0;
	// Attempt a full communication until finished or it has been attempted over max amount
	while (spi_finished == 0 && comm_attempts < MAX_COMM_ATTEMPTS) {
		
		uint8_t align_attempts = 0;
		// Attempt to align SPI until aligned or until it has been attempted over max amount
		while (spi_aligned == 0 &&  align_attempts < MAX_ALIGN_ATTEMPTS) {
			spi_read = SPDR;
			PORTA = spi_read;
			spi_aligned = spi_read == SPI_START; // SPI is aligned if START was read
			if (spi_aligned) {
				spi_transcieve(SPI_ACK);
			
			} else {
				spi_transcieve(SPI_RESTART);
			}
			
			align_attempts++;
		}
		spi_aligned = 0;
	
		send_status_and_data_packet();
	
		spi_read = spi_transcieve(SPI_NAN);
		spi_finished = spi_read == SPI_FINISHED;
		
		comm_attempts++;
	}
	spi_finished = 0;
}


void send_status_and_data_packet(void) {
	/* Status data */	
	spi_transcieve(status_1);
	spi_transcieve(status_2);
	check_byte = status_1 ^ status_2;
	
	/* Accelerometer data */
	spi_transcieve(acc_x_1);
	check_byte ^= acc_x_1;
	
	spi_transcieve(acc_x_2);
	check_byte ^= acc_x_2;
	
	spi_transcieve(acc_y_1);
	check_byte ^= acc_y_1;
	
	spi_transcieve(acc_y_2);
	check_byte ^= acc_y_2;
	
	spi_transcieve(acc_z_1);
	check_byte ^= acc_z_1;
	
	spi_transcieve(acc_z_2);
	check_byte ^= acc_z_2;
	
	/* Distance data */
	spi_transcieve(dist);
	check_byte ^= dist;
	
	/* Speed data */
	spi_transcieve(speed);
	check_byte ^= speed;
	
	/* Check byte */
	spi_transcieve(check_byte);
	
}

void enable_intercomm(void) {
	SPCR |= (1<<SPIE);
}

void disable_intercomm(void) {
	SPCR &= ~(1<<SPIE);
}

