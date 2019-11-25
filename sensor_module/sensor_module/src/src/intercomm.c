/*
 * inter_comm.c
 *
 * Created: 2019-11-21 13:37:08
 *  Author: anglo547
 */ 

#include <avr/interrupt.h>

#include "intercomm.h"
#include "spi.h"
#include "sensor_data.h"

#define MAX_ALIGN_ATTEMPTS 5
#define MAX_COMM_ATTEMPTS 5

void send_status_and_data_packet(void);
void send_and_update_check_byte(uint8_t data, uint8_t* check_byte);


static uint8_t spi_aligned = 0;
static uint8_t spi_read = 0;
static uint8_t spi_finished = 0;

static uint8_t status_1 = 0x01;
static uint8_t status_2 = 0x02;

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

/*
 *  Sends status and data packets and a checkbyte of all the data transmitted via SPI.
 */
void send_status_and_data_packet(void) {
	uint8_t check_byte = 0x00;

	/* Status data */		
	send_and_update_check_byte(status_1, check_byte);
	send_and_update_check_byte(status_2, check_byte);
	


	/* Range data */
	uint8_t range_data_buffer = get_most_recent_sensor_data(RANGE_DATA_ID);
	
	// Sends in the following order RANGE_LO, RANGE_HI
	for (uint8_t = 0; i < RANGE_DATA_BYTES; i++) {
		send_and_update_check_byte(acc_data_buffer[i], check_byte);
	}
	
	/* Speed data */
	// Sends in the 
	
	/* Check byte */
	spi_transcieve(check_byte);
}

void send_sensor_data_and_update_check_byte(uint8_t data_id) {
	uint8_t* sensor_data_buffer = get_most_recent_sensor_data(data_id);
		
	// Sends in little endian order
	for (uint8_t i = 0; i < data_id; i++) {
		send_and_update_check_byte(acc_data_buffer[i], check_byte);
	}	
}

void send_and_update_check_byte(uint8_t data, uint8_t* check_byte) {
	spi_transcieve(data);
	(*check_byte) ^= data;
}

void enable_intercomm(void) {
	SPCR |= (1<<SPIE);
}

void disable_intercomm(void) {
	SPCR &= ~(1<<SPIE);
}

