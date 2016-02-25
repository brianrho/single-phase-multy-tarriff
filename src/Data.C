
#include "..\inc\includes.h"

/*****************************************************************
	Define global data
*****************************************************************/
//#pragma memory = dataseg(DATA16_N) //dataseg=DATA16_N
__no_init SRAM_T	SM;//186
__no_init CLK_T		Clk;		//14
//__no_init
//6 keypad
DISKEY				DisK;		//
//__no_init
//rate
FEE_T				Fee;//
//__no_init
//operation delay
RUNDLY_T			RunDly;//
//__no_init 
//15 system flag
FLAG_T 			Flag;		//
//#pragma memory = default
#pragma pack(2)
//32xbuffer
char			Buffer[MAX_BUF];	//
#pragma pack()
//720 maximum demand
MAXDEMAND_T       MaxD;				//
//demand slip validity
MDFEESW_T			MDFeeSw;//
//serial port
IEC_COMM		IEC_Comm;//串口
//LOADPROFILE		LoadProfile;
//not use
unsigned char	Status[4];    //
//phase sequence
unsigned char	ZX[7];//相序
//frequency support communication display
char			Freq[2];			//
unsigned char 	keytime[2];
//keypress time
CALITMR_T			CaliTmr;//
//no use
PULSETMR_T		PulseTmr;//
//events delay
EVENTDLY_T        EventDly;//
//event flag
EVENTFLAG       EventFlag;//
CLKCORRECT      ClkC;//
//no use
unsigned int    BAT_V;//
//battery voltage
//ZXARRAY         ZXArray;
//alarm
unsigned char   ALARM[4];    //E001 A001 A002 A003报警
//event pointer
EVENLPPTR_T       EevenLPPtr;//
//decimal point digts
unsigned char   DOT[5];         //En kW V A PF//小数点位数
//freeze delay
unsigned char   BillDely[2];//冻结延时
//power down display
unsigned char   PowerDnDisp;//
//factory mode

unsigned int	gFactMode;//
//hardware detection

unsigned int	gHardErr;		//
//user defined register

int8u UserdeBCD[3][6];//

/*****************************************************************
//define version number
**software
//it needs to recalibrate the meter after the version before 20141229 updated.
**hardware
//the version before 20131111(include 20131111)is LCD without M display.

*****************************************************************/
const VERSION_T Version = { 
  /*  Type    */
  // 'H','X','G','P','R','S','0','1',
  /*  Software    */
  0X20160111,
  /*  Hardware    */
  0X20150210,
#if METER_TYPE == 1
0x02300005
#endif
#if METER_TYPE == 2
0x02300050
#endif
#if METER_TYPE == 3
0x01100005
#endif
#if METER_TYPE == 4
0x00570005 
#endif
#if METER_TYPE == 5
0x02300010
#endif
};

const char ByteBit[8] = { 
	0x01, 0x02, 0x04, 0x08, 
	0x10, 0x20, 0x40, 0x80 
};

const char ByteBitTail[4] = {
	0x10, 0x20, 0x40, 0x80
};

const unsigned char DefaultDOT[5]=
{   0x0E,0x00,0x00,0x00,0x00    };

