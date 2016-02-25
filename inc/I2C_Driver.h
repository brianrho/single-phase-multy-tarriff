/******************************************************************************
//I2C_Driver.h - I2C bus
 * I2C_Driver.h - I2C×ÜÏß
 * 
 * Copyright Hangzhou East Smart Technology Co.,Ltd.
 * 
 * DESCRIPTION: - 
 *      
 * modification history
 * --------------------
 * 01a, 12feb2011,  written
 * --------------------
 ******************************************************************************/

#ifndef		_I2C_DRIVER_H
#define		_I2C_DRIVER_H

#define		I2C_BUS_0		0
#define		I2C_BUS_1		1

int8u  I2C_WriteByte(int8u SdByte,int8u Com);

unsigned char   I2C_ReadByte(unsigned char Ack,int8u Com);
void    I2C_Start(int8u Com);
void    I2C_Stop(int8u Com);



#endif
