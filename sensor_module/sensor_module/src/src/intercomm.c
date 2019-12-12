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
#include "utilities.h"

// Forward declares
static void send_status_and_data_packet(void);
static void send_sensor_data_and_update_check_byte(uint8_t sensor_data_id, uint8_t* check_byte);
static void send_and_update_check_byte(uint8_t data, uint8_t* check_byte);


static uint8_t spi_aligned = 0;
static uint8_t spi_read = 0;
static uint8_t spi_confirmed = 0;


// Temporary static variables
static uint8_t status_1 = 0x01;
static uint8_t status_2 = 0x02;

// SPI Transmission/reception completed interrupt service routine
ISR(SPI_STC_vect)
{	
	spi_read = spi_get_data_register_value();

	spi_aligned = (spi_read == SPI_START); // SPI is aligned if START was read
	if (spi_aligned) {
		// Send SPI acknowledge byte
		spi_transcieve(SPI_ACK);
		
		if (SPSR & (1 << WCOL))
		{
			return;
		}
		// Read SPI confirm byte
		spi_read = spi_transcieve(SPI_NAN);
		spi_confirmed = spi_read == SPI_CONFIRM;
		
		if (spi_confirmed) {
			send_status_and_data_packet();
			spi_transcieve(SPI_NAN);
		}
	}
}


/*
 *  Sends status and data packets and a checkbyte of all the data transmitted via SPI.
 */
void send_status_and_data_packet(void) {
	uint8_t check_byte = 0x00;

	/* Status data */		
	send_and_update_check_byte(status_1, &check_byte);
	send_and_update_check_byte(status_2, &check_byte);
	
	
	/* Accelerometer data */
	send_sensor_data_and_update_check_byte(ACCELEROMETER_DATA_ID, &check_byte);


	/* Range data */
	send_sensor_data_and_update_check_byte(RANGE_DATA_ID, &check_byte);
	
	
	/* Speed data */
	send_sensor_data_and_update_check_byte(SPEED_DATA_ID, &check_byte);
	
	
	/* Check byte */
	spi_transcieve(check_byte);
}


void send_sensor_data_and_update_check_byte(uint8_t sensor_data_id, uint8_t* check_byte) {
	uint8_t* sensor_data_buffer = get_most_recent_sensor_data(sensor_data_id);
		
	// Sends in little endian order
	for (uint8_t i = 0; i < get_num_bytes_in_sensor_data(sensor_data_id); i++) {
		send_and_update_check_byte(sensor_data_buffer[i], check_byte);
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

