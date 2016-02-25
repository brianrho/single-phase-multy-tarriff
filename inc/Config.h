
/*
//name: Config.h
//function:meter calculating function configuration
//author:
//version:
//time:

#ifndef 	_CONFIG_H_
#define		_CONFIG_H_


//#define		DEBUG											/*debugging function*/
#define		DEBUG											/*调试功能*/

//*****************calculating function ********************************/
/*****************计量功能********************************/
#define		METER_CONSTANT							1600
#define		PHASE_ENERGY_PULSES_PER_10W_HOUR	(METER_CONSTANT/100)

//#define		PHASE_FREQUENCY							50		/*power grid frequency HZ*/
#define		PHASE_FREQUENCY							50		/*电网频率HZ*/

#define		MAX_CURRENT								100		//(A)
#define		METER_Ib								10		//(A)
#define		METER_Un								230		//(V)

//#define		RMS_CURRENT_SUPPORT						1	   /*equivalent voltage*/
#define		RMS_CURRENT_SUPPORT						1	   /*等效电压*/
//#define		RMS_VOlTAGE_SUPPORT						1	   /*equivalent current*/
#define		RMS_VOlTAGE_SUPPORT						1	   /*等效电流*/
//#define		RMS_ACTIVE_POWER_SUPPORT				1		/*active power*/
#define		RMS_ACTIVE_POWER_SUPPORT				1		/*有功功率*/
//#define		RMS_REACTIVE_POWER_SUPPORT				1		/*reactive power*/
#define		RMS_REACTIVE_POWER_SUPPORT				1		/*无功功率*/
//#define		NEUTRAL_MONITOR_SUPPORT			   		0		/*bypass support*/
#define		NEUTRAL_MONITOR_SUPPORT			   		0		/*旁路支持*/

//#define		ADC_M_SUPPORT							0		/*M channel support*/
#define		ADC_M_SUPPORT							0		/*	M通道使用	*/

//*****************other functions of meter calculating ********************************/
/*****************表计其他功能********************************/
//#define		MULTI_TARIFFS_SUPPORT					0		/*support muti-tariff function*/
#define		MULTI_TARIFFS_SUPPORT					0		/*多费率功能支持*/
//#define		DST_SUPPORT								0		/*support daylight saving time*/
#define		DST_SUPPORT								0		/*夏令时支持*/
//#define		PREPAYMENT_SUPPORT						0		/*prepayment function*/
#define		PREPAYMENT_SUPPORT						0		/*预付费功能*/
//#define		HOST_RELAY_SUPPORT						0		/*main relay function*/
#define		HOST_RELAY_SUPPORT						0		/*主继电器功能*/
//#define		ASS_RELAY_SUPPORT						0		/*auxiliary relay function*/
#define		ASS_RELAY_SUPPORT						0		/*辅助继电器功能*/
//#define		MD_SUPPORT								0		/*needed quantity function*/
#define		MD_SUPPORT								0		/*需量功能*/
//#define		STS_SUPPORT								0		/*STS prepayment function*/
#define		STS_SUPPORT								0		/*STS预付费功能*/
//#define		FREEZE_SUPPOR							0		/*frozen function*/
#define		FREEZE_SUPPOR							0		/*冻结功能*/
//*****************communication regulating definition********************************/
/*****************通讯规约定义********************************/
#define		IEC62056_21			0
#define		DTL645_1997			1
#define		DTL645_2007			2

#define		DMLS				3
#undef		DMLS

//#define		LOCAT_PROTOCOL		IEC62056_21		/*local communication regulation*/
#define		LOCAT_PROTOCOL		IEC62056_21		/*本地通讯规约*/
#define		PLC_PROTOCOL		DTL645_1997

//#define		COM_XPORT_SUPPROT	1				/* support Ethernet */
#define		COM_XPORT_SUPPROT	1				/* 支持以太网 */
//*****************others********************************/
/*****************其他********************************/
#define		LCD_CHIIN_SUPPORT					0


 //DMLS links needed to be defined
//DMLS链路层需要定义
#ifdef		DMLS

#endif

//*****************meter calculating firmware configuration********************************/
/*****************表计硬件配置********************************/
 //define storage size=0 means no such device
//定义存储 size=0表示无该器件
//#define		EEPORM_DRIVE_START						0x0000		  /*EEROM storage start address*/
#define		EEPORM_DRIVE_START						0x0000		  /*EEROM存储起始地址*/
//#define		EEPORM_DRIVE_SIZE						0x2000		  /*EEROM size*/
#define		EEPORM_DRIVE_SIZE						0x2000		  /*EEROM大小*/

//#define		FRAM_DRIVE_START						0x00000		  /*ferroelectric memory start address*/
#define		FRAM_DRIVE_START						0x00000		  /*铁电存储器起始地址*/
//#define		FRAM_DRIVE_SIZE							0			  /*ferroelectric storage size*/
#define		FRAM_DRIVE_SIZE							0			  /*铁电存储大小*/

//#define		DATAFALSH_DRIVE_START 					0			 /*flash storage start address*/
#define		DATAFALSH_DRIVE_START 					0			 /*flash存储起始地址*/	
//#define		DATAFLASH_DRIVE_SIZE					0			 /*flash storage start address*/	
#define		DATAFLASH_DRIVE_SIZE					0			 /*flash存储起始大小*/	

 //support firmware RTC or not
//是否支持硬件RTC
//#define		RTC_HARD_SUPPORT						1			/*support firmware RTC*/
#define		RTC_HARD_SUPPORT						1			/*支持硬件RTC*/




#define  off(st,n)   (unsigned int)(&(((st*)0)->n))
#define  size(st,n)  (unsigned int)(sizeof((((st*)0)->n)))

#endif
