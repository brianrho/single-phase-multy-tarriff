#include "..\inc\includes.h"

#define		ON		1
#define		OFF		0
//**************************************
//SPI delay
//SPI延时
//*************************************
void SPI_Delay(int8u time) {
	//int8u i;

	time = time;
	_NOP();
	/*
	 for(;time>0;time--)
	 {
	 //for(i=1;i>0;i--);
	 _NOP();
	 }
	 */
}
//**************************************
//SPI control
//*************************************
void SPI_CS(SPI_IC_T ICNo) {

	DF_SET_CS();
	FM_SET_CS();

	SPI_Delay(1);
	SPI_SET_CLK();
	SPI_SET_SI();
	//write protection
	//写保护
	DF_SET_WP();
	FM_SET_WP();

	if (ICNo == SPI_FLASH) {
		//DF_CLR_CS();	//chip selection
		DF_CLR_CS(); //片选
	} else if (ICNo == SPI_FRAM) {
		FM_CLR_CS(); //
	} else if (ICNo == ATT7022) {
		ATT7022_CLR_CS();
	} else {
		DF_SET_CS();
		FM_SET_CS();
		//SPI_Delay(16);		 //delay enough time to ensure chip operation to be finished
		SPI_Delay(16); //
	}

}

//**************************************
//SPI power control
//*************************************
void SPI_POWON(int8u Sta, int8u Type) {

	if (Sta == ON) {
		//FLASH_CLR_POW();	//start power
		FLASH_CLR_POW(); //开启电源
		FM_CLR_POW();
		SPI_Delay(1);
	} else {

		FLASH_SET_POW();
		FM_SET_POW();
		SPI_Delay(1);
		//ensure low consumption
		//保证低功耗
		SPI_CLR_CLK();
		SPI_CLR_SI();
		DF_CLR_CS();
		DF_CLR_WP();
		FM_CLR_CS();
		FM_CLR_WP();

	}

	DelayMs(1);

}
//**************************************
//SPI initialization
//*************************************
void SPI_Init(void) {
	SPI_POWON(OFF, FM_POW);
}

//**************************************
//SPI write byte
//SPI 写字节 
//*************************************
void SPI_WByte(int8u cha) {
	int8u i;

	for (i = 8; i > 0; i--) {
		SPI_CLR_CLK();
		SPI_Delay(1);
		if (cha & 0x80) {
			SPI_SET_SI();
		} else {
			SPI_CLR_SI();
		}
		SPI_SET_CLK();
		SPI_Delay(1);
		cha <<= 1;
	}
}
//**************************************
//SPI read  byte
//*************************************
int8u SPI_Read(void) {
	int8u i;
	int8u ucData = 0;

	for (i = 8; i > 0; i--) {
		ucData <<= 1;
		SPI_CLR_CLK();
		SPI_Delay(1);

		if (SPI_RET_SO) {
			ucData |= 0x01;
		}
		SPI_SET_CLK();
		SPI_Delay(1);
	}
	return ucData;
}

/*
 void SPI_Rest(SPI_IC_T ICNo )
 {
 if(ICNo==FRAM)
 {

 }
 }
 */

#undef	ON
#undef	OFF

