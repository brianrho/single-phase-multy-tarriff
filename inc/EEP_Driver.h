
#ifndef		_EEP_DRIVER_H_
#define		 _EEP_DRIVER_H_


//对应AT24C01 AT24C02
#define		AT24C01			0			
//对应AT24C04,AT24C08,AT24C16
#define		AT24C04			2
//对应AT24C64
#define		AT24C64			3

#define		EEPROM_TYPE		AT24C64
		
//#define		EEPROM_ADDR		0xa0		/*device address           */
#define		EEPROM_ADDR		0xa0		/*	器件地址	*/

#if (EEPROM_TYPE==AT24C01)
//#define		EEROM_PAGES		8		/*	page size        */	
#define		EEROM_PAGES		8			/*	页大小	*/	
#elif (EEPROM_TYPE==AT24C04)
#define		EEROM_PAGES		16
#elif (EEPROM_TYPE==AT24C64)
#define		EEROM_PAGES		32
#endif

extern int8u	E_Write(int16u Addr,int8u *buf,int8u len);
extern int8u	E_Read(int8u *buf,int16u Addr,int8u len); 


	

#endif


		
