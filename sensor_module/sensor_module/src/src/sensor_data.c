/*
 * sensor_data.c
 *
 * Created: 2019-11-24 11:20:17
 *  Author: anglo547
 */ 
#include <string.h>

#include "sensor_data.h"
#include "utilities.h"

/* Constants for number of bytes in sensor data buffers */
#define ACCELEROMETER_DATA_BYTES 6
#define RANGE_DATA_BYTES 2
#define SPEED_DATA_BYTES 1


// Forward declares
static void write_new_data(circle_buffer_t *sensor_data_buffer, uint8_t* new_data);
static uint8_t* get_most_recent_data(circle_buffer_t *sensor_data_buffer);

/*
 * Global variable for storing accelerometer data. 
 * Description of indexes in the inner array:
 * 0 : acc_x_lo
 * 1 : acc_x_hi
 * 2 : acc_y_lo
 * 3 : acc_y_hi
 * 4 : acc_z_lo
 * 5 : acc_z_hi
 */
static circle_buffer_t acc_data_buffer = {
	.data = {
		(uint8_t[]) {0, 0, 0, 0, 0, 0}, // 0
		(uint8_t[]) {0, 0, 0, 0, 0, 0}, // 1
		(uint8_t[]) {0, 0, 0, 0, 0, 0}, // 2
		(uint8_t[]) {0, 0, 0, 0, 0, 0}, // 3 
		(uint8_t[]) {0, 0, 0, 0, 0, 0}, // 4
		(uint8_t[]) {0, 0, 0, 0, 0, 0}, // 5
		(uint8_t[]) {0, 0, 0, 0, 0, 0}, // 6
		(uint8_t[]) {0, 0, 0, 0, 0, 0}, // 7
		(uint8_t[]) {0, 0, 0, 0, 0, 0}, // 8
		(uint8_t[]) {0, 0, 0, 0, 0, 0}  // 9
	},			
	.data_size = ACCELEROMETER_DATA_BYTES,
	.most_recent_index = 0
};


/* 
 * Global variable for storing range data.
 */
static circle_buffer_t range_data_buffer = {
	.data = {
		(uint8_t[]) {0, 0}, // 0
		(uint8_t[]) {0, 0}, // 1
		(uint8_t[]) {0, 0}, // 2
		(uint8_t[]) {0, 0}, // 3
		(uint8_t[]) {0, 0}, // 4
		(uint8_t[]) {0, 0}, // 5
		(uint8_t[]) {0, 0}, // 6
		(uint8_t[]) {0, 0}, // 7
		(uint8_t[]) {0, 0}, // 8
		(uint8_t[]) {0, 0}  // 9
	},
	.data_size = RANGE_DATA_BYTES,
	.most_recent_index = 0
};


/*
 * Global variable for storing speed data.
 */
static circle_buffer_t speed_data_buffer = {
	.data = {
		(uint8_t[]) {0}, // 0
		(uint8_t[]) {0}, // 1
		(uint8_t[]) {0}, // 2
		(uint8_t[]) {0}, // 3
		(uint8_t[]) {0}, // 4
		(uint8_t[]) {0}, // 5
		(uint8_t[]) {0}, // 6
		(uint8_t[]) {0}, // 7
		(uint8_t[]) {0}, // 8
		(uint8_t[]) {0}  // 9
	},
	.data_size = SPEED_DATA_BYTES,
	.most_recent_index = 0
};

uint8_t get_num_bytes_in_sensor_data(uint8_t sensor_data_id) {
	switch (sensor_data_id) {
		case ACCELEROMETER_DATA_ID:
			return ACCELEROMETER_DATA_BYTES;
		case RANGE_DATA_ID:
			return RANGE_DATA_BYTES;
		case SPEED_DATA_ID:
			return SPEED_DATA_BYTES;
		default:
			// Incorrect sensor data ID
			utilities_error(UNDEFINED_SENSOR_DATA_ID_ON_READ);
	}
}

void write_new_sensor_data(uint8_t sensor_data_id, uint8_t* new_data) {
	switch (sensor_data_id) {
		case ACCELEROMETER_DATA_ID:
			write_new_data(&acc_data_buffer, new_data);
			break;
		case RANGE_DATA_ID:
			write_new_data(&range_data_buffer, new_data);
			break;
		case SPEED_DATA_ID:
			write_new_data(&speed_data_buffer, new_data);
			break;
		default:
			// Incorrect sensor ID occurred
			utilities_error(UNDEFINED_SENSOR_DATA_ID_ON_READ_NUM_BYTES);
	}
}


uint8_t* get_most_recent_sensor_data(uint8_t sensor_data_id) {
	switch (sensor_data_id) {
		case ACCELEROMETER_DATA_ID:
			return get_most_recent_data(&acc_data_buffer);
		case RANGE_DATA_ID:
			return get_most_recent_data(&range_data_buffer);
		case SPEED_DATA_ID:
			return get_most_recent_data(&speed_data_buffer);
		default:
			// Incorrect sensor ID occurred
			utilities_error(UNDEFINED_SENSOR_DATA_ID_ON_READ);
	}
	return NULL; // To avoid warning of no return at end of function
}


circle_buffer_t* get_entire_sensor_data_buffer(uint8_t sensor_data_id) {
	switch (sensor_data_id) {
		case ACCELEROMETER_DATA_ID:
			return &acc_data_buffer;
		case RANGE_DATA_ID:
			return &range_data_buffer;
		case SPEED_DATA_ID:
			return &speed_data_buffer;
		default:
			// Incorrect sensor ID occurred
			utilities_error(UNDEFINED_SENSOR_DATA_ID_ON_READ_ALL);
	}
	
	return NULL; // To avoid warning of no return at end of function
}



// Static helper functions

static void write_new_data(circle_buffer_t *sensor_data_buffer, uint8_t* new_data) {
	// Calculate new index in the circular array buffer
	uint8_t new_index = (sensor_data_buffer->most_recent_index + 1) % SENSOR_DATA_ARRAY_SIZE; 
	
	// Copy over the memory from the entered data to the array
	memcpy(sensor_data_buffer->data[new_index], new_data, sensor_data_buffer->data_size);
	
	// Update most recent index value
	sensor_data_buffer->most_recent_index = new_index;
}

static uint8_t* get_most_recent_data(circle_buffer_t *sensor_data_buffer) {
	return sensor_data_buffer->data[sensor_data_buffer->most_recent_index];
}