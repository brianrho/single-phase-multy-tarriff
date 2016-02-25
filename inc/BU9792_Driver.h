/******************************************************************************
 * BU9792_Driver.h - BU9792
 * 
 * Copyright Hangzhou East Smart Technology Co.,Ltd.
 * 
 * DESCRIPTION: - 
 *      
 * modification history
 * --------------------
 * 01a, 26nov2010,  written
 * --------------------
 ******************************************************************************/

#ifndef		_BU9792_H
#define		_BU9792_H


//#define	  BU9799_ADDR		0x7c				/*device address */
#define	  BU9799_ADDR		0x7c				/*器件地址*/			


//#define   LCD_OFF    		0x40		      		       /*turn off display*/
#define   LCD_OFF    		0x40				/*显示关闭*/
//#define   LCD_ON      		0x48				/*turn on display*/
#define   LCD_ON      		0x48				/*显示开*/
//#define   LCD_POWER_NORMAL  0x22			//0b'0100010	/*normal power consumption*/
#define   LCD_POWER_NORMAL  0x22			//0b'0100010	/*正常功耗*/
//#define   LCD_POWER_SAVE    0x3C				//0b'0111000	/*low power consumption*/
#define   LCD_POWER_SAVE    0x3C				//0b'0111000	/*低功耗*/
//#define   LCD_ICSET   		0x6a				       //0b'1101010	/*device soft reset*/
#define   LCD_ICSET   		0x6a				//0b'1101010	/*器件软复位*/
//#define   LCD_ICSET_M   	0x68				//0b'1101000	/*device soft reset*/
#define   LCD_ICSET_M   	0x68				//0b'1101000	/*器件软复位*/

//#define   LCD_BLINK_OFF   	0x70				//0b'1110000	/*turn off flicker*/
#define   LCD_BLINK_OFF   	0x70				//0b'1110000	/*闪烁关*/
//#define   LCD_BLINK_0   	0x71			 	       //0b'1110000	/*flicker 0.5hz*/
#define   LCD_BLINK_0   	0x71				//0b'1110000	/*闪烁0.5hz*/
//#define   LCD_BLINK_1     	0x72				//0b'1110000	/*flicker 1hz*/
#define   LCD_BLINK_1     	0x72				//0b'1110000	/*闪烁1hz*/
//#define   LCD_BLINK_2    	0x73				  //0b'1110000	/*flicker 2hz*/
#define   LCD_BLINK_2    	0x73			  	//0b'1110000	/*闪烁2hz*/
//#define   LCD_PIXEL_OFF  	0x7d				//0b'1111101	/*turn off all pixel*/
#define   LCD_PIXEL_OFF  	0x7d				//0b'1111101	/*所有像素点关闭*/
//#define   LCD_PIXEL_ON   	0x7e				//0b'1111110	/*turn on off all pixel*/
#define   LCD_PIXEL_ON   	0x7e				//0b'1111110	/*所有像素点打开关闭*/
//#define   LCD_PIXEL_NORMAL 	0x7c			       	//0b'1111100	/*normal module*/
#define   LCD_PIXEL_NORMAL 	0x7c				//0b'1111100	/*正常模式*/


 //function statement area//	
//------------------------------------------------------------------------------------------------------//
 //function performance:setting up LCD driver working parameter
 //entrance parameter:mode-driver chip working module, HL9576-MODE-NOL-proper functioning; HL9576-MODE-LOW-low power consumption working
 //exit parameter:backspace setting result, 0-successful setup, 0xff-unsuccessful setup, LCD device might break down
extern int8u   BU9792_Set(unsigned char mode);  


extern int8u   BU9792_Refresh(unsigned char * Src, unsigned int Len);    

unsigned char  BU9792_Init(void);
  

#endif



