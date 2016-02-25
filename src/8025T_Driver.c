#include "..\inc\includes.h"

#define		EEP_DELAY	1
#define		RX8025_ADDR		0x64		/*device address	*/
//************************************************************
//function performance: clock chip 8025T reading function
extern int8s RX8025_Read(int8u *Obj, int8u Addr, int8u Len) {
	int8u temp, cmd;
//acquire device address
	cmd = RX8025_ADDR;						                      //

	temp = 0;
	//starting 12C communication
	I2C_Start(I2C_BUS_1);                                          //
//sending device address
	while (I2C_WriteByte(cmd, I2C_BUS_1) && (temp < 3))           //
	{
		I2C_Stop(I2C_BUS_1);
		//time delay for ensuring EEP page to be finished
		DelayMs(EEP_DELAY);                    //
		I2C_Start(I2C_BUS_1);
		temp++;
	}                                      	//device might be abnormal
	if (temp >= 3)                                              //
			{
		I2C_Stop(I2C_BUS_1);
		return (-1);
	}

	temp = Addr;
	//sending sub-address
	if (I2C_WriteByte(temp, I2C_BUS_1))                             //
			{
		I2C_Stop(I2C_BUS_1);
		return (-1);
	}

	I2C_Start(I2C_BUS_1);
	//sending device address reading orders
	if (I2C_WriteByte(cmd | 0x01, I2C_BUS_1))              //
			{
		I2C_Stop(I2C_BUS_1);
		return (-1);
	}

	while (Len-- > 0) { //if receives the last byte, then there is no sending of ack
		temp = (Len != 0 ? 0x00 : 0x01); //
		*Obj = I2C_ReadByte(temp, I2C_BUS_1);
		Obj++;
	}
	I2C_Stop(I2C_BUS_1);
	return (0x00);
}
//************************************************************
//function performance: writing function using clock chip 8025T
extern int8u RX8025_Write(int8u Dst, int8u *Src, int8u Len) {
	int8u temp;
	//command buffer
	int8u cmdtemp;    //
	//acquire device address command
	cmdtemp = RX8025_ADDR; // | ((Dst>>12)&0x0E); //

	temp = 0;
	//starting 12C communication
	I2C_Start(I2C_BUS_1); //
//sending device address
	while (I2C_WriteByte(cmdtemp, I2C_BUS_1) && (temp < 3))       //
	{
		I2C_Stop(I2C_BUS_1);
		//time delay for ensuring EEP page to be finished
		DelayMs(EEP_DELAY);   //
		I2C_Start(I2C_BUS_1);
		temp++;
	}                                      	//device might abnormal
	if (temp >= 3)          //
			{
		I2C_Stop(I2C_BUS_1);
		return (0xff);
	}

	temp = (int8u) (Dst);
	//sending sub-address
	if (I2C_WriteByte(temp, I2C_BUS_1))  //
			{
		I2C_Stop(I2C_BUS_1);
		return (0xff);
	}

	while (Len-- > 0) {
		I2C_WriteByte(*Src, I2C_BUS_1);
		Src++;
	}
	I2C_Stop(I2C_BUS_1);
	return (0);
}

