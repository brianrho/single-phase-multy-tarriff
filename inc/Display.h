#ifndef		_DISPLAY_H
#define		_DISPLAY_H

/*******************************************************************
	Display format define table
*******************************************************************/
//*******************************************************************
// LCD character bitmap
//          0                a
//        -----            -----
//       |     |          |     |
//      4|     |1        f|     |b
//       |  5  |          |  g  |
//        -----            -----
//       |     |          |     |
//      6|     |2        e|     |c
//       |  3  |          |  d  |
//        -----  *7        -----  *dpc
//*******************************************************************
 //connecting configuration is in accordance with firmware pin
#ifdef SINGLE_PHASE_MULTI_TARIFF
//LCDM1
#define		S1_ON		(LCDM1|=0x08)
#define		S1_OFF		(LCDM1&=0xF7)
#define		S20_ON		(LCDM1|=0x04)
#define		S20_OFF		(LCDM1&=0xFB)
#define		S21_ON		(LCDM1|=0x02)
#define		S21_OFF		(LCDM1&=0xFD)
#define		S22_ON		(LCDM1|=0x01)
#define		S22_OFF		(LCDM1&=0xFE)
#define		S19_ON		(LCDM1|=0x10)
#define		S19_OFF		(LCDM1&=0xEF)
//LCDM2
#define		S27_ON		(LCDM2|=0x10)
#define		S27_OFF		(LCDM2&=0xEF)
//LCDM3
#define		S45_ON		(LCDM3|=0x10)
#define		S45_OFF		(LCDM3&=0xEF)
//LCDM4
#define		S15_ON		(LCDM4|=0x10)
#define		S15_OFF		(LCDM4&=0xEF)
//LCDM5
#define		S44_ON		(LCDM5|=0x80)
#define		S44_OFF		(LCDM5&=0x7F)
#define		S46_ON		(LCDM5|=0x20)
#define		S46_OFF		(LCDM5&=0xDF)
#define		S47_ON		(LCDM5|=0x10)
#define		S47_OFF		(LCDM5&=0xEF)
#define		S18_ON		(LCDM5|=0x40)
#define		S18_OFF		(LCDM5&=0xBF)
//LCDM6
#define		S17_ON		(LCDM6|=0x01)
#define		S17_OFF		(LCDM6&=0xFE)
//LCDM7
#define		S28_ON		(LCDM7|=0x01)
#define		S28_OFF		(LCDM7&=0xFE)
//LCDM8
#define		S53_ON		(LCDM8|=0x08)
#define		S53_OFF		(LCDM8&=0xF7)
#define		S48_ON		(LCDM8|=0x04)
#define		S48_OFF		(LCDM8&=0xFB)
#define		S49_ON		(LCDM8|=0x02)
#define		S49_OFF		(LCDM8&=0xFD)
#define		S16_ON		(LCDM8|=0x01)
#define		S16_OFF		(LCDM8&=0xFE)
#define		S29_ON		(LCDM8|=0x10)
#define		S28_OFF		(LCDM8&=0xEF)
//LCDM9
#define		S54_ON		(LCDM9|=0x80)
#define		S54_OFF		(LCDM9&=0x7F)
#define		S50_ON		(LCDM9|=0x40)
#define		S50_OFF		(LCDM9&=0xBF)
#define		S51_ON		(LCDM9|=0x20)
#define		S51_OFF		(LCDM9&=0xDF)
#define		S30_ON		(LCDM9|=0x10)
#define		S30_OFF		(LCDM9&=0xEF)
//LCDM10
#define		S31_ON		(LCDM10|=0x01)
#define		S31_OFF		(LCDM10&=0xFE)
//LCDM11
#define		S52_ON		(LCDM11|=0x01)
#define		S52_OFF		(LCDM11&=0xFE)
//LCDM12
#define		S36_ON		(LCDM12|=0x80)
#define		S36_OFF		(LCDM12&=0x7F)
#define		S37_ON		(LCDM12|=0x40)
#define		S37_OFF		(LCDM12&=0xBF)
#define		S38_ON		(LCDM12|=0x20)
#define		S38_OFF		(LCDM12&=0xDF)
#define		S32_ON		(LCDM12|=0x10)
#define		S32_OFF		(LCDM12&=0xEF)
#define		S35_ON		(LCDM12|=0x08)
#define		S35_OFF		(LCDM12&=0xF7)
#define		S34_ON		(LCDM12|=0x04)
#define		S34_OFF		(LCDM12&=0xFB)
#define		S33_ON		(LCDM12|=0x02)
#define		S33_OFF		(LCDM12&=0xFD)
#define		S55_ON		(LCDM12|=0x01)
#define		S55_OFF		(LCDM12&=0xFE)
//LCDM13
#define		S41_ON		(LCDM13|=0x08)
#define		S41_OFF		(LCDM13&=0xF7)
#define		S39_ON		(LCDM13|=0x04)
#define		S39_OFF		(LCDM13&=0xFB)
#define		S40_ON		(LCDM13|=0x02)
#define		S40_OFF		(LCDM13&=0xFD)
#define		S26_ON		(LCDM13|=0x01)
#define		S26_OFF		(LCDM13&=0xFE)
//LCDM14
#define		S12_ON		(LCDM14|=0x80)
#define		S12_OFF		(LCDM14&=0x7F)
#define		S43_ON		(LCDM14|=0x40)
#define		S43_OFF		(LCDM14&=0xBF)
#define		S11_ON		(LCDM14|=0x20)
#define		S11_OFF		(LCDM14&=0xDF)
#define		S10_ON		(LCDM14|=0x10)
#define		S10_OFF		(LCDM14&=0xEF)
#define		S42_ON		(LCDM14|=0x08)//08
#define		S42_OFF		(LCDM14&=0xF7)
// LCDM15
#define		S13_ON		(LCDM15|=0x08)
#define		S13_OFF		(LCDM15&=0xF7)
#define		S9_ON		(LCDM15|=0x04)
#define		S9_OFF		(LCDM15&=0xFB)
#define		S8_ON		(LCDM15|=0x02)
#define		S8_OFF		(LCDM15&=0xFD)
#define		S7_ON		(LCDM15|=0x01)
#define		S7_OFF		(LCDM15&=0xFE)
//LCDM16
#define		S6_ON		(LCDM16|=0x80)
#define		S6_OFF		(LCDM16&=0x7F)
#define		S25_ON		(LCDM16|=0x40)
#define		S25_OFF		(LCDM16&=0xBF)
#define		S24_ON		(LCDM16|=0x20)
#define		S24_OFF		(LCDM16&=0xDF)
#define		S23_ON		(LCDM16|=0x10)
#define		S23_OFF		(LCDM16&=0xEF)
#define		S14_ON		(LCDM16|=0x08)
#define		S14_OFF		(LCDM16&=0xF7)
//LCDM17
#define		S5_ON		(LCDM17|=0x08)
#define		S5_OFF		(LCDM17&=0xF7)
#define		S4_ON		(LCDM17|=0x04)
#define		S4_OFF		(LCDM17&=0xFB)
#define		S3_ON		(LCDM17|=0x02)
#define		S3_OFF		(LCDM17&=0xFD)
#define		S2_ON		(LCDM17|=0x01)
#define		S2_OFF		(LCDM17&=0xFE)

#endif

#define		s1_a		0x10
#define		s1_b	    0x20
#define		s1_c		0x40
#define		s1_d		0x80
#define		s1_e		0x04
#define		s1_f		0x01
#define		s1_g		0x02
#define		s1_dp		0x08

#define		s2_a		0x80
#define		s2_b	    0x40
#define		s2_c		0x20
#define		s2_d		0x10
#define		s2_e		0x02
#define		s2_f		0x08
#define		s2_g		0x04
#define		s2_dp		0x01
//New LCD
//										  hcbadegf
#define DS_Chr_0     0xB7 //0xDE // 0: 0000 0001 b 
#define DS_Chr_1     0x06 //0x06 // 1: 0000 0110 b
#define DS_Chr_2     0xE5 //0x7A // 2: 0110 1100 b
#define DS_Chr_3     0XC7 //0x3E // 3: 0011 1110 b
#define DS_Chr_4     0X56 //0xA6 // 4: 1010 0110 b
#define DS_Chr_5     0XD3 //0xBC // 5: 1011 1100 b
#define DS_Chr_6     0XF3 //0xFC // 6: 1111 1100 b
#define DS_Chr_7     0X07 //0x0E // 7: 0000 1110 b
#define DS_Chr_8     0XF7 //0xFE // 8: 1111 1110 b
#define DS_Chr_9     0XD7 //0xBE // 9: 1011 1110 b
#define DS_Chr_A     0X77 //0xEE // A: 1110 1110 b
#define DS_Chr_b     0XF2 //0xF4 // B: 1111 0100 b
#define DS_Chr_C     0XB1 //0xD8 // C: 1101 1000 b
#define DS_Chr_d     0XE6 //0x76 // D: 0111 0110 b
#define DS_Chr_E     0XF1 //0xF8 // E: 1111 1000 b
#define DS_Chr_F     0X71 //0xE8 // F: 1110 1000 b

#define DS_Chr_Dot		0x08 //01    // .: 0000 0001 b
#define DS_Chr_Neg		0x40 //20    //-   0010 0000 B



// Display Unit Segment
#define Unit_kWh        0X9E //0x97    // 1001 0111
#define Unit_kvArh		0XF6 //0xF6    // 1111 0110
#define Unit_kVAh		0XD6 //0xB6    // 1011 0110
#define Unit_kW         0X1E //0x87	// 1000 0111
#define	Unit_kvar		0X76 //0xE6    // 1110 0110
#define Unit_kVA		0X56 //0xA6    // 1010 0110
#define Unit_V			0X02 //0x04    // 0000 0100
#define Unit_A			0X50 //0xA0    // 1010 0000
#define Unit_h			0X80 //0x10    // 0001 0000
#define Unit_z			0X01 //0x08    // 0000 1000
#define Phase_A			0X10 //0x80    // 1000 0000
#define Phase_B			0X40 //0x20    // 0010 0000
#define Phase_C			0X20 //0x40    // 0100 0000
#define Unit_MWh        0X9B //0x9D    // 1001 1101
#define Unit_MvArh      0XF3 //0xFC    // 1111 1100
#define Unit_MVAh       0XD3 //0xBC    // 1011 1100
//
#define DS_CONT     0X10 //0x80    // 1000 0000
#define DS_CUM      0X40 //0x20    // 0010 0000
#define DS_MD       0X20 //0x40    // 0100 0000
#define DS_RESET    0X80 //0x10    // 0001 0000
#define DS_PREV     0X01 //0x08    // 0000 1000
#define DS_TARIFF   0X04 //0x02    // 0000 0010
#define DS_DATE     0X02 //0x04    // 0000 0100
#define DS_TIME     0X08 //0x01    // 0000 0001

//
#define DS_Litt1    0X10 //0x80    // 1000 0000
#define DS_Litt2    0X40 //0x20    // 0010 0000
#define DS_Litt3    0X20 //0x40    // 0100 0000
#define DS_Litt4    0X80 //0x10    // 0001 0000
#define DS_LittQ1   0X01 //0x08    // 0000 1000
#define DS_LittQ2   0X04 //0x02    // 0000 0010
#define DS_LittQ3   0X02 //0x04    // 0000 0100
#define DS_LittQ4   0X08 //0x01    // 0000 0001

//
#define DS_TOTAL    0X10 //0x80    // 1000 0000
#define DS_REV      0X40 //0x20    // 0010 0000


/*******************************************************************
 	Display & Key Operating Bit
*******************************************************************/

#define		DISP_PARA_NULL	0	
#define		DISP_SPTR_NULL	0
 //exit page
#define		DISP_PARA_0		1
#define		DISP_PARA_1		2

#define		DISP_PARA_2		3
#define		DISP_PARA_3		4

#define		DISP_PARA_4		5
#define		DISP_PARA_5		6
#define		DISP_PARA_6		7

#ifdef HARDWARE_TWO
#define		DISP_PARA_7		9
#else
#define     DISP_PARA_7     8
#endif


 //content data of subdirecroty
#define		DISP_PAGE1		13//11+1+1

#ifdef  HARDWARE_TWO
#define		DISP_PAGE2		13//8+1+4
#else
#define		DISP_PAGE2		9//8+1
#endif

#define		DISP_PAGE3		13//12+1

#ifdef  HARDWARE_TWO
#define		DISP_PAGE4		45//9+1+20+5+10
#else
#define		DISP_PAGE4		10//9+1
#endif

#define		DISP_PAGE5		10//3+1+6
#define		DISP_PAGE6		7//3+1+3
#define		DISP_PAGE7		3//2+1
#define		DISP_PAGE8		4//3+1

#define		DISP_PARA_0_LEN		7
#define		DISP_PARA_1_LEN		11

// Display  & Key registers
typedef struct
{
	char 	DisMode;			// 
	char 	DipKeyPara;			//
       //char	DisPtr;				// rotator meter pointer
	char	DisPtr;				//
       //char	DisInv;				//rotator spacing counter
	char	DisInv;				//
  	int8u 	KeyId;
  	int8u 	MPtr;
  	int8u 	SPtr;
       //int8u  FlashSige;			//flashing sign
	int8u  FlashSige;			//
  	int8u 	UIFg;
  	int8u 	ErrPtr;				//
  	int8u 	ErrCnt;
       //int8u 	ErrNum;				//display
	int8u 	ErrNum;				//
  	int16u 	ShutDnInv;
  	int16u 	ShutDnCnt;
} DISKEY;

typedef struct
{
	char*	Addr;
	char	DisInfo;
} DISTAB;

typedef struct
{
	unsigned int DisPag;
	char OBIS[4];
}OBISTbl;


#define		DISP_AUTO_NUM		16

#define		DISP_MODE_AUTO		0
//#define		DISP_MODE_KEY		1	//enter into button menu mode
#define		DISP_MODE_KEY		1	//
#define		DISP_MODE_ERR		2
//#define		DISP_MODE_CLICK		3	//single button mode
#define		DISP_MODE_CLICK		3	//

void AllDisplay(void);
void DisplayData(void);
void Get_ShutDispTm(void);
void DispFull(void);


//cancle the following
///以下取消------------------------------aju
#define DS_Date			0x04 // .: 00000100 b
#define DS_Time			0x08 // .: 00001000 b
#define DS_Neg			0x02 // .: 00000010 b
#define DS_Revs			0x80 //  : 10000000 b
#define DS_RevsS		0x80 //  : 10000000 b
#define DS_temper1		0x02 // .: 00000010 b
#define DS_temper2		0x80 //  : 10000000 b
// Display digit
#define DS_Unit		16
#define DS_BDig		8
#define DS_BDig0	2


#define		DISP_PARA()		(gDispBuf[17]|=0x80)
#define		DISP_POWER()	(gDispBuf[5]|=0x10)
#define		DISP_HMD()		(gDispBuf[15]|=0xf0)
#define		DISP_HBI()		gDispBuf[13]|=0x0c;gDispBuf[13]|=0x40
#define		DISP_PROG()		(gDispBuf[0]|=0x40)
#define		DISP_PCUT()		(gDispBuf[0]|=0x80)
#define		DISP_VTPT()		gDispBuf[16]|=0x06;gDispBuf[17]|=0x40
#define		DISP_Userde()	gDispBuf[16]|=0x10;gDispBuf[5]|=0x10

#endif
