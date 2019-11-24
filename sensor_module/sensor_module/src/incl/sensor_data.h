/*
 * sensor_data.h
 *
 * Created: 2019-11-24 11:20:00
 *  Author: anglo547
 */ 

#include <stdint.h>

#ifndef SENSOR_DATA_H_
#define SENSOR_DATA_H_

/* Sensor data IDs */
#define ACCELEROMETER_DATA_ID 0
#define RANGE_DATA_ID 1
#define SPEED_DATA_ID 2

/* Sensor data constants */
#define SENSOR_DATA_ARRAY_SIZE 10

#define ACCELEROMETER_DATA_BYTES 6
#define RANGE_DATA_BYTES 1
#define SPEED_DATA_BYTES 1


/* 
 * Sensor data struct that can save data of various sizes.
 * Saves the ten most recent sensor measurements in a circular array buffer and has an index for the most recent data that was saved.
 * The data_size member indicates how many bytes each individual sensor data consists of.
 */
typedef struct {
	uint8_t* data [SENSOR_DATA_ARRAY_SIZE]; // Array of pointers to uint8_t, makes it possible to save data of different sizes
	uint8_t data_size; // Data size in amount of bytes
	uint8_t most_recent_index;
} circle_buffer_t;


/*
 * Writes the new_data buffer to the circular buffer of the entered sensor data id.
 * The new data overwrites the oldest data in the buffer.
 */
void write_new_sensor_data(uint8_t sensor_data_id, uint8_t* new_data);


/*
 * Returns a buffer with the most recent data of the sensor with the entered sensor data id.
 */
uint8_t* get_most_recent_sensor_data(uint8_t sensor_data_id);


/* 
 * Returns the entire circular buffer of the sensor with the entered sensor data id.
 */
circle_buffer_t* get_entire_sensor_data_buffer(uint8_t sensor_data_id);


#endif /* SENSOR_DATA_H_ */