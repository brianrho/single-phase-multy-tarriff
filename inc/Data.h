#ifndef	_DATA_H
#define	_DATA_H


/*******************************************************************
	Declare global data in RAM
*******************************************************************/
//extern 	CLK_T             Clk;//time
extern 	CLK_T             Clk;//
//extern	char              Buffer[MAX_BUF];//buffer
extern	char              Buffer[MAX_BUF];//
//extern	MAXDEMAND_T       MaxD;//maximum demand
extern	MAXDEMAND_T       MaxD;//
//extern  MDFEESW_T			MDFeeSw;//demand slip
extern  MDFEESW_T			MDFeeSw;//

//extern 	DISKEY			DisK;//key  9010
extern 	DISKEY			DisK;//
//extern 	FLAG_T           Flag;//system flag
extern 	FLAG_T           Flag;//
//extern 	SRAM_T            SM;//power impulse
extern 	SRAM_T            SM;//
//extern	char			Volt_Tmer[3];//no usage
extern	char			Volt_Tmer[3];//
extern 	char 			test;
//extern 	char			Fee;
//extern 	FEE_T				Fee;//tariff
extern 	FEE_T				Fee;//
//extern	IEC_COMM		IEC_Comm;//serial port
extern	IEC_COMM		IEC_Comm;//

extern	unsigned char	ZX[7];//

//extern	LOADPROFILE		LoadProfile;
//extern	unsigned char	Status[4];//status
extern	unsigned char	Status[4];//
//extern	char Freq[2];//frequency
extern	char Freq[2];//
//extern unsigned char 	keytime[2];//no usage
extern unsigned char 	keytime[2];//
//extern CALITMR_T		CaliTmr;//keystrokes
extern CALITMR_T		CaliTmr;//
//extern RUNDLY_T			RunDly;//operation delay
extern RUNDLY_T			RunDly;//
//extern PULSETMR_T		PulseTmr;//no usage
extern PULSETMR_T		PulseTmr;//
//extern EVENTDLY_T    	 EventDly;//event delay
extern EVENTDLY_T    	 EventDly;//
//extern EVENTFLAG    EventFlag;//event flag
extern EVENTFLAG    EventFlag;//
//extern CLKCORRECT   ClkC;//no usage
extern CLKCORRECT   ClkC;//
//extern unsigned int BAT_V;//battery voltage
extern unsigned int BAT_V;//
//extern unsigned char   ALARM[4];	    //E001 A001 A002 A003 alarm
extern unsigned char   ALARM[4];	    //E001 A001 A002 A003±¨¾¯
//extern EVENLPPTR_T       EevenLPPtr;//event pointer
extern EVENLPPTR_T       EevenLPPtr;//
//extern unsigned char   DOT[5];//decimal places
extern unsigned char   DOT[5];//
//extern unsigned char   BillDely[2];//frozen delay
extern unsigned char   BillDely[2];//
//extern unsigned char   PowerDnDisp;//off-power display
extern unsigned char   PowerDnDisp;//

//extern	unsigned int	gFactMode;//factory mode
extern	unsigned int	gFactMode;//

#define			ERR_FRAM_F		0x01
#define			ERR_EEPROM_F	0x02
#define			ERR_DFLASH_F	0x04
#define			ERR_ATT7022_F	0x08

//extern	unsigned int	gHardErr;		//firmware detection
extern	unsigned int	gHardErr;		//

//extern int8u UserdeBCD[3][6];//user defined register
extern int8u UserdeBCD[3][6];//

//extern int8u passerr_locktime;//wrong password locking time
extern int8u passerr_locktime;//
//extern int8u passerr_delaytime;//wrong password delay time
extern int8u passerr_delaytime;//

/*******************************************************************
	Declare global constant
*******************************************************************/
extern const VERSION_T  Version;//
extern const char     ByteBit[8];
extern const char     ByteBitTail[4];
extern const unsigned char DefaultDOT[5];//
#define MAX_EN_DOT      2
#define MAX_KW_DOT      3
#define MAX_V_DOT       1
#define MAX_A_DOT       2
#define MAX_PF_DOT      3

#endif
