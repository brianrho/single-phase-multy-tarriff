/******************************************************************************
 // PortConfig.h - IO mouth configuration
 * PortConfig.h - IOø⁄≈‰÷√
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

//Port1
#define     P_PwDn  BIT0    //DYJC
#define     P_ZXC   BIT2
#define     P_ZXB   BIT3
#define     P_ZXA   BIT4
#define     P_IRQC  BIT5
#define     P_IRQB  BIT6
#define     P_IRQA  BIT7

 //*I2C configuration*/
 //E2 I2C bus
#define		I2C0_SCL_SET		(P1OUT|=BIT5)
#define		I2C0_SCL_CLR		(P1OUT&=~BIT5)
#define		I2C0_SDA_SET		(P1OUT|=BIT4)
#define		I2C0_SDA_DIR		(P1DIR&=~BIT4)

//

/*********************************
//IO mouth definition
*********************************/
#ifdef SINGLE_PHASE_MULTI_TARIFF
//RN8209SPI
#define		RN8209_SET_CLK()		(P4OUT|=BIT5)
#define		RN8209_CLR_CLK()		(P4OUT&=~BIT5)
#define		RN8209_SET_SI()			(P4OUT|=BIT3)
#define		RN8209_CLR_SI()			(P4OUT&=~BIT3)
#define		RN8209_RET_SO			P4IN&BIT4
#define		RN8209_SET_CS()			(P3OUT|=BIT0)
#define		RN8209_CLR_CS()			(P3OUT&=~BIT0)

#define		RN8209_SET_REST()		(P2OUT|=BIT6)
#define		RN8209_CLR_REST()		(P2OUT&=~BIT6)
#define		SPI_RET_ATSIG			(P2IN&BIT7)


#define		ATT7022_RET_SO			P4IN&BIT4
#define		ATT7022_SET_CS()		(P3OUT|=BIT0)
#define		ATT7022_CLR_CS()		(P3OUT&=~BIT0)

#define		DF_SET_CS()				(P6OUT|=BIT5)
#define		DF_CLR_CS()				(P6OUT&=~BIT5)
#define		DF_SET_WP()				(P6OUT|=BIT6)
#define		DF_CLR_WP()				(P6OUT&=~BIT6)
#define		FLASH_SET_POW()			(P6OUT|=BIT3)
#define		FLASH_CLR_POW()			(P6OUT&=~BIT3)


#define		FM_SET_CS()				(P4OUT|=BIT2)
#define		FM_CLR_CS()				(P4OUT&=~BIT2)
#define		FM_SET_WP()				(P2OUT|=BIT0)
#define		FM_CLR_WP()				(P2OUT&=~BIT0)
#define		FM_SET_POW()			(P6OUT|=BIT1)
#define		FM_CLR_POW()			(P6OUT&=~BIT1)

#else
//AT722SPI
#define		ATT7022_SET_CLK()		(P4OUT|=BIT5)
#define		ATT7022_CLR_CLK()		(P4OUT&=~BIT5)
#define		ATT7022_SET_SI()		(P4OUT|=BIT3)
#define		ATT7022_CLR_SI()		(P4OUT&=~BIT3)
#define		ATT7022_RET_SO			P4IN&BIT4
#define		ATT7022_SET_CS()		(P3OUT|=BIT0)
#define		ATT7022_CLR_CS()		(P3OUT&=~BIT0)

#define		ATT7022_SET_REST()		(P2OUT|=BIT6)
#define		ATT7022_CLR_REST()		(P2OUT&=~BIT6)
#define		SPI_RET_ATSIG	(P2IN&BIT7)


#define		DF_SET_CS()		(P5OUT|=BIT3)
#define		DF_CLR_CS()		(P5OUT&=~BIT3)

#define		DF_SET_WP()		(P5OUT|=BIT2)
#define		DF_CLR_WP()		(P5OUT&=~BIT2)

#define		FM_SET_CS()		(P4OUT|=BIT2)
#define		FM_CLR_CS()		(P4OUT&=~BIT2)

#define		FM_SET_WP()		(P2OUT|=BIT0)
#define		FM_CLR_WP()		(P2OUT&=~BIT0)

#define		FM_SET_POW()	(P6OUT|=BIT1)
#define		FM_CLR_POW()	(P6OUT&=~BIT1)

#define		FLASH_SET_POW()	(P5OUT|=BIT4)
#define		FLASH_CLR_POW()	(P5OUT&=~BIT4)
#endif

//FRAM,DATAFLASH SPI
#define		SPI_SET_SI()	(P3OUT|=BIT1)
#define		SPI_CLR_SI()	(P3OUT&=~BIT1)
#define		SPI_SET_CLK()	(P3OUT|=BIT3)
#define		SPI_CLR_CLK()	(P3OUT&=~BIT3)
#define		SPI_RET_SO		P3IN&BIT2
/*
#define		DF_SET_REST()	P1OUT|=BIT0		//
#define		DF_CLR_REST()	P1OUT&=~BIT0
*/
 //menu key
#define		KEY_UP_RET		(P1IN&BIT2)
 //factory short circuit
#define		FAC_KEY()		(P3IN&BIT4)

 //AN4 programme key
#define		PROG_KEY()		(P3IN&BIT6)

 //frozen
#define		BILL_REST()		(P3IN&BIT7)	

 //clear key
#define		SYC_CLR()		(P6IN&BIT3)

 //RTC output
#define		RTC_OUT_SET()		(P6OUT|=BIT7)
#define		RTC_OUT_CLR()		(P6OUT&=~BIT7)






