/*******************************************************************************
Copyright � 2015, STMicroelectronics International N.V.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of STMicroelectronics nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND
NON-INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS ARE DISCLAIMED.
IN NO EVENT SHALL STMICROELECTRONICS INTERNATIONAL N.V. BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
********************************************************************************/

/**
 * @file VL53L0X_i2c.c
 *
 * Copyright (C) 2014 ST MicroElectronics
 *
 * provide variable word size byte/Word/dword VL6180x register access via i2c
 *
 */
#include "vl53l0x_platform.h"
#include "vl53l0x_i2c_platform.h"
#include "vl53l0x_api.h"

#define LOG_FUNCTION_START(fmt, ... )           _LOG_FUNCTION_START(TRACE_MODULE_PLATFORM, fmt, ##__VA_ARGS__)
#define LOG_FUNCTION_END(status, ... )          _LOG_FUNCTION_END(TRACE_MODULE_PLATFORM, status, ##__VA_ARGS__)
#define LOG_FUNCTION_END_FMT(status, fmt, ... ) _LOG_FUNCTION_END_FMT(TRACE_MODULE_PLATFORM, status, fmt, ##__VA_ARGS__)

/**
 * @def I2C_BUFFER_CONFIG
 *
 * @brief Configure Device register I2C access
 *
 * @li 0 : one GLOBAL buffer \n
 *   Use one global buffer of MAX_I2C_XFER_SIZE byte in data space \n
 *   This solution is not multi-Device compliant nor multi-thread cpu safe \n
 *   It can be the best option for small 8/16 bit MCU without stack and limited ram  (STM8s, 80C51 ...)
 *
 * @li 1 : ON_STACK/local \n
 *   Use local variable (on stack) buffer \n
 *   This solution is multi-thread with use of i2c resource lock or mutex see VL6180x_GetI2CAccess() \n
 *
 * @li 2 : User defined \n
 *    Per Device potentially dynamic allocated. Requires VL6180x_GetI2cBuffer() to be implemented.
 * @ingroup Configuration
 */
#define I2C_BUFFER_CONFIG 0
/** Maximum buffer size to be used in i2c */
#define VL53L0X_MAX_I2C_XFER_SIZE   64 /* Maximum buffer size to be used in i2c */

#if I2C_BUFFER_CONFIG == 0
    /* GLOBAL config buffer */
    uint8_t i2c_global_buffer[VL53L0X_MAX_I2C_XFER_SIZE];

    #define DECL_I2C_BUFFER
    #define VL53L0X_GetLocalBuffer(Dev, n_byte)  i2c_global_buffer

#elif I2C_BUFFER_CONFIG == 1
    /* ON STACK */
    #define DECL_I2C_BUFFER  uint8_t LocBuffer[VL53L0X_MAX_I2C_XFER_SIZE];
    #define VL53L0X_GetLocalBuffer(Dev, n_byte)  LocBuffer
#elif I2C_BUFFER_CONFIG == 2
    /* user define buffer type declare DECL_I2C_BUFFER  as access  via VL53L0X_GetLocalBuffer */
    #define DECL_I2C_BUFFER
#else
#error "invalid I2C_BUFFER_CONFIG "
#endif


#define VL53L0X_I2C_USER_VAR         /* none but could be for a flag var to get/pass to mutex interruptible  return flags and try again */
#define VL53L0X_GetI2CAccess(Dev)    /* todo mutex acquire */
#define VL53L0X_DoneI2CAcces(Dev)    /* todo mutex release */


VL53L0X_Error VL53L0X_LockSequenceAccess(VL53L0X_DEV Dev){
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;

    return Status;
}

VL53L0X_Error VL53L0X_UnlockSequenceAccess(VL53L0X_DEV Dev){
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;

    return Status;
}

// the ranging_sensor_comms.dll will take care of the page selection
VL53L0X_Error VL53L0X_WriteMulti(VL53L0X_DEV Dev, uint8_t index, uint8_t *pdata, uint32_t count){

	VL53L0X_Error error = VL53L0X_ERROR_NONE;
    uint8_t status_int = 0;
	uint8_t deviceAddress;

    if (count>=VL53L0X_MAX_I2C_XFER_SIZE){
        return VL53L0X_ERROR_INVALID_PARAMS;
    }

	deviceAddress = Dev->I2cDevAddr;
	
	status_int = i2c_send_start_bit();
	error = (status_int == I2C_STATUS_START ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE);
	
	if (error == VL53L0X_ERROR_NONE)
	{
		status_int = i2c_send_data(deviceAddress);
		error = (status_int == I2C_STATUS_SLA_W_ACK ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE);
	}

	if (error == VL53L0X_ERROR_NONE)
	{
		status_int = i2c_send_data(index);
		error = (status_int == I2C_STATUS_DATA_TRANS_ACK ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE);
	}
	
	for (uint32_t i = 0; i < count; ++i)
	{
		if (error == VL53L0X_ERROR_NONE)
		{
			status_int = i2c_send_data(pdata[i]);
			error = (status_int == I2C_STATUS_DATA_TRANS_ACK ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE);
		}
	}
	
	i2c_send_stop_bit();
	//utilities_busy_wait_ms(1);
	return error;
}

// the ranging_sensor_comms.dll will take care of the page selection
VL53L0X_Error VL53L0X_ReadMulti(VL53L0X_DEV Dev, uint8_t index, uint8_t *pdata, uint32_t count){
	
	VL53L0X_Error error;
	uint8_t deviceAddress, status;

    if (count>=VL53L0X_MAX_I2C_XFER_SIZE){
        return VL53L0X_ERROR_INVALID_PARAMS;
    }

    deviceAddress = Dev->I2cDevAddr;
	
	status = i2c_send_start_bit();
	error = (status == I2C_STATUS_START ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE);
	
	if (error == VL53L0X_ERROR_NONE)
	{
		status = i2c_send_data(deviceAddress);
		error = (status == I2C_STATUS_SLA_W_ACK ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE);
	}
	
	if (error == VL53L0X_ERROR_NONE)
	{
		status = i2c_send_data(index);
		error = (status == I2C_STATUS_DATA_TRANS_ACK ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE);
	}
	
	if (error == VL53L0X_ERROR_NONE)
	{
		status = i2c_send_stop_start_bit();
		error = (status == I2C_STATUS_START ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE);
	}
	
	if (error == VL53L0X_ERROR_NONE)
	{
		status = i2c_send_data(deviceAddress | 0x01);
		error = (status == I2C_STATUS_SLA_R_ACK ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE);
	}
	
	for (uint32_t i = 0; i < count - 1; ++i)
	{
		if (error == VL53L0X_ERROR_NONE)
		{
			status = i2c_receive_data(pdata + i, 1);
			error = (status == I2C_STATUS_DATA_REC_ACK ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE);
		}
	}
	
	if (error == VL53L0X_ERROR_NONE)
	{
		status = i2c_receive_data(pdata + count - 1, 0);
		error = (status == I2C_STATUS_DATA_REC_NACK ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE);
	}
	
	i2c_send_stop_bit();
	//utilities_busy_wait_ms(1);
	return error;
}


VL53L0X_Error VL53L0X_WrByte(VL53L0X_DEV Dev, uint8_t index, uint8_t data){
    VL53L0X_Error error;
	uint8_t deviceAddress, status;

    deviceAddress = Dev->I2cDevAddr;
	
	status = i2c_send_start_bit();
	error = (status == I2C_STATUS_START ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE);
	
	if (error == VL53L0X_ERROR_NONE)
	{
		status = i2c_send_data(deviceAddress);
		error = (status == I2C_STATUS_SLA_W_ACK ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE);
	}
	
	if (error == VL53L0X_ERROR_NONE)
	{
		status = i2c_send_data(index);
		error = (status == I2C_STATUS_DATA_TRANS_ACK ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE);
	}
	
	if (error == VL53L0X_ERROR_NONE)
	{
		status = i2c_send_data(data);
		error = (status == I2C_STATUS_DATA_TRANS_ACK ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE);
	}
	
	i2c_send_stop_bit();
	//utilities_busy_wait_ms(1);
    return error;
}

VL53L0X_Error VL53L0X_WrWord(VL53L0X_DEV Dev, uint8_t index, uint16_t data){
	return VL53L0X_WrByte(Dev, index, (data >> 8) & 0xFF)
			| VL53L0X_WrByte(Dev, index + 1, data & 0xFF);
}

VL53L0X_Error VL53L0X_WrDWord(VL53L0X_DEV Dev, uint8_t index, uint32_t data){
	return VL53L0X_WrByte(Dev, index, (data >> 24) & 0xFF)
			| VL53L0X_WrByte(Dev, index + 1, (data >> 16) & 0xFF)
			| VL53L0X_WrByte(Dev, index + 2, (data >> 8) & 0xFF)
			| VL53L0X_WrByte(Dev, index + 3, data & 0xFF);
}

VL53L0X_Error VL53L0X_UpdateByte(VL53L0X_DEV Dev, uint8_t index, uint8_t AndData, uint8_t OrData){
	VL53L0X_Error status = VL53L0X_ERROR_NONE;
	uint8_t data;
	
	status = VL53L0X_RdByte(Dev, index, &data);
	if (status != VL53L0X_ERROR_NONE)
	{
		return status;
	}
	
	data = (data & AndData) | OrData;
	
	status = VL53L0X_WrByte(Dev, index, data);
	return status;
}

VL53L0X_Error VL53L0X_RdByte(VL53L0X_DEV Dev, uint8_t index, uint8_t *data){
    VL53L0X_Error error;
	uint8_t deviceAddress, status;

    deviceAddress = Dev->I2cDevAddr;
	
	status = i2c_send_start_bit();
	error = (status == I2C_STATUS_START ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE);
	
	if (error == VL53L0X_ERROR_NONE)
	{
		i2c_send_data(deviceAddress);
		error = (status == I2C_STATUS_START ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE);
	}

	if (error == VL53L0X_ERROR_NONE)
	{
		i2c_send_data(index);
		error = (status == I2C_STATUS_START ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE);
	}

	if (error == VL53L0X_ERROR_NONE)
	{
		i2c_send_stop_start_bit();
		error = (status == I2C_STATUS_START ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE);
	}

	if (error == VL53L0X_ERROR_NONE)
	{
		i2c_send_data(deviceAddress | 0x01);
		error = (status == I2C_STATUS_START ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE);
	}

	if (error == VL53L0X_ERROR_NONE)
	{
		i2c_receive_data(data, 0);
		error = (status == I2C_STATUS_START ? VL53L0X_ERROR_NONE : VL53L0X_ERROR_CONTROL_INTERFACE);
	}

	i2c_send_stop_bit();
	//utilities_busy_wait_ms(1);
    return error;
}

VL53L0X_Error VL53L0X_RdWord(VL53L0X_DEV Dev, uint8_t index, uint16_t *data) {
	uint8_t* byte_ptr = (uint8_t*) data;
	return VL53L0X_RdByte(Dev, index, byte_ptr + 1)
			| VL53L0X_RdByte(Dev, index + 1, byte_ptr);
}

VL53L0X_Error  VL53L0X_RdDWord(VL53L0X_DEV Dev, uint8_t index, uint32_t *data){
	uint8_t* byte_ptr = (uint8_t*) data;
	return VL53L0X_RdByte(Dev, index, byte_ptr + 3)
		| VL53L0X_RdByte(Dev, index + 1, byte_ptr + 2)
		| VL53L0X_RdByte(Dev, index + 2, byte_ptr + 1)
		| VL53L0X_RdByte(Dev, index + 3, byte_ptr);
}

#define VL53L0X_POLLINGDELAY_LOOPNB  250
VL53L0X_Error VL53L0X_PollingDelay(VL53L0X_DEV Dev){
	/*
    VL53L0X_Error status = VL53L0X_ERROR_NONE;
    LOG_FUNCTION_START("");

    const DWORD cTimeout_ms = 1;
    HANDLE hEvent = CreateEvent(0, TRUE, FALSE, 0);
    if(hEvent != NULL)
    {
        WaitForSingleObject(hEvent,cTimeout_ms);
    }

    LOG_FUNCTION_END(status);
    return status;
	*/
	
	return VL53L0X_ERROR_NONE;
}
