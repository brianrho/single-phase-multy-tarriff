/******************************************************************************
 * BU9792_Driver.c - BU9792LCD driver
 BU9792_Driver.c - BU9792LCD驱动
 * 
 * Copyright Hangzhou East Smart Technology Co.,Ltd.
 * 
 * DESCRIPTION: - 
 *      
 * modification history
 * --------------------
 * 01a, 25nov2010,  written
 * --------------------
 ******************************************************************************/
#include "..\inc\includes.h"

//------------------------------------//
//function performance:setting up working parameter of LCD driver
//---------------------------------------------------------------------------
//------------------------------------// 
unsigned char BU9792_Set(unsigned char mode) {
	unsigned char temp = 0;

	//I2C_Stop(I2C_BUS_0);

	I2C_Start(I2C_BUS_0);

	while (I2C_WriteByte(BU9799_ADDR, I2C_BUS_0) && (temp < 218)) {
		I2C_Stop(I2C_BUS_0);
		DelayMs(1);
		I2C_Start(I2C_BUS_0);
		temp++;
	}
	if (temp >= 218) {
		I2C_Stop(I2C_BUS_0);
		return (0xff);
	}

	I2C_WriteByte(mode | 0x80, I2C_BUS_0);

	I2C_Stop(I2C_BUS_0);

	return 0;
}
//************************************************************
//BU9792 initialization
unsigned char BU9792_Init(void) {
	unsigned char temp = 0, i;

	//BU9792_Set(LCD_OFF);					//turn off display first
	BU9792_Set(LCD_OFF);					//先关闭显示

	//I2C_Stop(I2C_BUS_0);

	I2C_Start(I2C_BUS_0);

	while (I2C_WriteByte(BU9799_ADDR, I2C_BUS_0) && (temp < 3)) {
		I2C_Stop(I2C_BUS_0);
		DelayMs(1);
		I2C_Start(I2C_BUS_0);
		temp++;
	}

	if (temp >= 3) {
		I2C_Stop(I2C_BUS_0);
		return (0xff);
	}

	//I2C_WriteByte(LCD_ICSET|0x80,I2C_BUS_0) ;				//reset
	I2C_WriteByte(LCD_ICSET | 0x80, I2C_BUS_0);				//复位

	//I2C_WriteByte(LCD_POWER_NORMAL|0x80,I2C_BUS_0) ;		//normal power consumption
	I2C_WriteByte(LCD_POWER_NORMAL | 0x80, I2C_BUS_0);		//正常功耗

	// I2C_WriteByte(LCD_BLINK_OFF|0x80,I2C_BUS_0) ;			//turn off flicker
	I2C_WriteByte(LCD_BLINK_OFF | 0x80, I2C_BUS_0);			//关闭闪烁

	I2C_WriteByte(LCD_PIXEL_NORMAL | 0x80, I2C_BUS_0);		//

	I2C_WriteByte(LCD_ICSET_M | 0x80, I2C_BUS_0);			//

	//I2C_WriteByte(0x00,I2C_BUS_0) ;						/*send data low address*/
	I2C_WriteByte(0x00, I2C_BUS_0); /* 发送数据低地址*/

	for (i = 0; i < 18; i++) {
		// I2C_WriteByte(0xff,I2C_BUS_0) ;					/* send device address
		I2C_WriteByte(0xff, I2C_BUS_0); /* 发送器件地址 */
	}
	I2C_Stop(I2C_BUS_0);

	//BU9792_Set(LCD_ON);							//start LCD
	BU9792_Set(LCD_ON);							//开启LCD

	return 0;

}
//************************************************************
//BU9792 refresh display
unsigned char BU9792_Refresh(unsigned char * Src, unsigned int Len) {
	unsigned char temp = 0, i;

	Len = Len;
	//I2C_Stop(I2C_BUS_0);

	I2C_Start(I2C_BUS_0);

	while (I2C_WriteByte(BU9799_ADDR, I2C_BUS_0) && (temp < 218)) {
		I2C_Stop(I2C_BUS_0);
		DelayMs(1);
		I2C_Start(I2C_BUS_0);
		temp++;
	}

	if (temp >= 218) {
		I2C_Stop(I2C_BUS_0);
		return (0xff);
	}

	//I2C_WriteByte(LCD_ICSET_M|0x80,I2C_BUS_0) ;	/*high address*/
	I2C_WriteByte(LCD_ICSET_M | 0x80, I2C_BUS_0); /* 高地址 */

	//I2C_WriteByte(0x00,I2C_BUS_0) ;				/*send data low address*/
	I2C_WriteByte(0x00, I2C_BUS_0); /* 发送数据低地址*/

	for (i = 0; i < 18; i++) {
		//I2C_WriteByte(*Src++,I2C_BUS_0) ;			/*send device address*/
		I2C_WriteByte(*Src++, I2C_BUS_0); /* 发送器件地址 */
	}

	I2C_Stop(I2C_BUS_0);

	return 0;
}
