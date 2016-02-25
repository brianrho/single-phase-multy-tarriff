
/*
//name: Config.h
//function:meter calculating function configuration
//author:
//version:
//time:

#ifndef 	_CONFIG_H_
#define		_CONFIG_H_


//#define		DEBUG											/*debugging function*/
#define		DEBUG											/*���Թ���*/

//*****************calculating function ********************************/
/*****************��������********************************/
#define		METER_CONSTANT							1600
#define		PHASE_ENERGY_PULSES_PER_10W_HOUR	(METER_CONSTANT/100)

//#define		PHASE_FREQUENCY							50		/*power grid frequency HZ*/
#define		PHASE_FREQUENCY							50		/*����Ƶ��HZ*/

#define		MAX_CURRENT								100		//(A)
#define		METER_Ib								10		//(A)
#define		METER_Un								230		//(V)

//#define		RMS_CURRENT_SUPPORT						1	   /*equivalent voltage*/
#define		RMS_CURRENT_SUPPORT						1	   /*��Ч��ѹ*/
//#define		RMS_VOlTAGE_SUPPORT						1	   /*equivalent current*/
#define		RMS_VOlTAGE_SUPPORT						1	   /*��Ч����*/
//#define		RMS_ACTIVE_POWER_SUPPORT				1		/*active power*/
#define		RMS_ACTIVE_POWER_SUPPORT				1		/*�й�����*/
//#define		RMS_REACTIVE_POWER_SUPPORT				1		/*reactive power*/
#define		RMS_REACTIVE_POWER_SUPPORT				1		/*�޹�����*/
//#define		NEUTRAL_MONITOR_SUPPORT			   		0		/*bypass support*/
#define		NEUTRAL_MONITOR_SUPPORT			   		0		/*��·֧��*/

//#define		ADC_M_SUPPORT							0		/*M channel support*/
#define		ADC_M_SUPPORT							0		/*	Mͨ��ʹ��	*/

//*****************other functions of meter calculating ********************************/
/*****************�����������********************************/
//#define		MULTI_TARIFFS_SUPPORT					0		/*support muti-tariff function*/
#define		MULTI_TARIFFS_SUPPORT					0		/*����ʹ���֧��*/
//#define		DST_SUPPORT								0		/*support daylight saving time*/
#define		DST_SUPPORT								0		/*����ʱ֧��*/
//#define		PREPAYMENT_SUPPORT						0		/*prepayment function*/
#define		PREPAYMENT_SUPPORT						0		/*Ԥ���ѹ���*/
//#define		HOST_RELAY_SUPPORT						0		/*main relay function*/
#define		HOST_RELAY_SUPPORT						0		/*���̵�������*/
//#define		ASS_RELAY_SUPPORT						0		/*auxiliary relay function*/
#define		ASS_RELAY_SUPPORT						0		/*�����̵�������*/
//#define		MD_SUPPORT								0		/*needed quantity function*/
#define		MD_SUPPORT								0		/*��������*/
//#define		STS_SUPPORT								0		/*STS prepayment function*/
#define		STS_SUPPORT								0		/*STSԤ���ѹ���*/
//#define		FREEZE_SUPPOR							0		/*frozen function*/
#define		FREEZE_SUPPOR							0		/*���Ṧ��*/
//*****************communication regulating definition********************************/
/*****************ͨѶ��Լ����********************************/
#define		IEC62056_21			0
#define		DTL645_1997			1
#define		DTL645_2007			2

#define		DMLS				3
#undef		DMLS

//#define		LOCAT_PROTOCOL		IEC62056_21		/*local communication regulation*/
#define		LOCAT_PROTOCOL		IEC62056_21		/*����ͨѶ��Լ*/
#define		PLC_PROTOCOL		DTL645_1997

//#define		COM_XPORT_SUPPROT	1				/* support Ethernet */
#define		COM_XPORT_SUPPROT	1				/* ֧����̫�� */
//*****************others********************************/
/*****************����********************************/
#define		LCD_CHIIN_SUPPORT					0


 //DMLS links needed to be defined
//DMLS��·����Ҫ����
#ifdef		DMLS

#endif

//*****************meter calculating firmware configuration********************************/
/*****************���Ӳ������********************************/
 //define storage size=0 means no such device
//����洢 size=0��ʾ�޸�����
//#define		EEPORM_DRIVE_START						0x0000		  /*EEROM storage start address*/
#define		EEPORM_DRIVE_START						0x0000		  /*EEROM�洢��ʼ��ַ*/
//#define		EEPORM_DRIVE_SIZE						0x2000		  /*EEROM size*/
#define		EEPORM_DRIVE_SIZE						0x2000		  /*EEROM��С*/

//#define		FRAM_DRIVE_START						0x00000		  /*ferroelectric memory start address*/
#define		FRAM_DRIVE_START						0x00000		  /*����洢����ʼ��ַ*/
//#define		FRAM_DRIVE_SIZE							0			  /*ferroelectric storage size*/
#define		FRAM_DRIVE_SIZE							0			  /*����洢��С*/

//#define		DATAFALSH_DRIVE_START 					0			 /*flash storage start address*/
#define		DATAFALSH_DRIVE_START 					0			 /*flash�洢��ʼ��ַ*/	
//#define		DATAFLASH_DRIVE_SIZE					0			 /*flash storage start address*/	
#define		DATAFLASH_DRIVE_SIZE					0			 /*flash�洢��ʼ��С*/	

 //support firmware RTC or not
//�Ƿ�֧��Ӳ��RTC
//#define		RTC_HARD_SUPPORT						1			/*support firmware RTC*/
#define		RTC_HARD_SUPPORT						1			/*֧��Ӳ��RTC*/




#define  off(st,n)   (unsigned int)(&(((st*)0)->n))
#define  size(st,n)  (unsigned int)(sizeof((((st*)0)->n)))

#endif
