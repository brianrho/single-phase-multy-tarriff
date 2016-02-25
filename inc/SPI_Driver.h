

#ifndef _SPI_DRIVER_H
#define	_SPI_DRIVER_H


typedef enum
{
	SPI_FLASH,
	SPI_FRAM,
	ATT7022,
	SPI_NULL
}SPI_IC_T;

#define		FM_POW			0
#define		FLASH_POW		1

int8u SPI_Read(void);

void SPI_WByte(int8u cha);

void	SPI_POWON(int8u Sta,int8u Type);

void 	SPI_CS(SPI_IC_T ICNo);

void 	SPI_Init(void);

#endif

