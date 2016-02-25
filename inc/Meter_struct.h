/******************************************************************************
//meter_struct.h - define meter structure
 * meter_struct.h -
 * 
 * Copyright Hangzhou East Smart Technology Co.,Ltd.
 * 
 * DESCRIPTION: - 
 *      
 * modification history
 * --------------------
 * 01a, 11feb2011,  written
 * --------------------
 ******************************************************************************/
#ifndef		_METER_STRUCT_H
#define		_METER_STRUCT_H

#define DEBUGING
//#undef DEBUGING //20150707 is for test, it should be shielded when using it
#undef DEBUGING //20150707

#define	MAX_BUF	150
#define	BufUbd	(MAX_BUF-1)
//*******************************************************************
// Data type define
//*******************************************************************
typedef char BCD1[1];
typedef char BCD2[2];
typedef char BCD3[3];
typedef char BCD4[4];
typedef char BCD5[5];
typedef char BCD6[6];
typedef char BCD7[7];
typedef char BCD8[8];

/*******************************************************************
	Global data in RAM that not cleared when Reset
*******************************************************************/
#define	PowerDelyTM	    3   
#define	MBillDelyTM    3// (BillDely[0])
#define DLBillDelyTM   3// (BillDely[1])
// Power flags define
#define	F_PwrInt    0x01
#define	F_PwrUp     0x02
#define	F_LowBAT    0x04
#define R_DispShut  0x08
#define F_PwrOK     0x10
// Run flags define
#define	R_Sec       0x01
//#define	R_Tst		0x02	//test mode mark
#define	R_Tst		0x02	//
#define	R_ComOK     0x04
#define	R_Pulse		0x08
//#define	R_HalfS		0x10	//half a second mark
#define	R_HalfS		0x10	//
#define	R_Disp		0x20
//#define	R_FeeTbChg	0x40    //->set any parameter
#define	R_FeeTbChg	0x40    //
//#define R_INT32     0x80    //interrup oriented
#define R_INT32     0x80    //
// Clk flags define
#define	F_5S		0x01
#define	F_Min       0x02
#define	F_Hour      0x04
#define	F_Day       0x08
//#define	F_1sCircle	0x10	//TimerA cycle times when finishing one second
#define	F_1sCircle	0x10	//
//Fee
#define FeeSW_DL	0x01
#define	FeeSW_XL	0x02
#define	F_BillAll	0x04
#define	F_BillMD	0x08
//OP7753
#define	IRQSTATUS	0x01
#define	init_7753	0x02
#define	Rset_7753	0x04
//#define	Acti_dir	0x08  //total active direction
#define	Acti_dir	0x08  //
//#define	Reacti_dir	0x10  //total reactive direction
#define	Reacti_dir	0x10  //
//#define VA_dir		0x20  //total apparent direction
#define VA_dir		0x20  //
// Power_dir
//#define	WA_DIR		0X01  //split-phase active direction
#define	WA_DIR		0X01  //
#define	WB_DIR		0X02
#define	WC_DIR		0X04
//#define	VARA_DIR	0X10  //split-phase reactive direction
#define	VARA_DIR	0X10  //
#define	VARB_DIR	0X20
#define	VARC_DIR	0X40
// VA_DIR
//#define	VAA_DIR		0X01  //split-phase apparent direction
#define	VAA_DIR		0X01  //
#define	VAB_DIR		0X02
#define	VAC_DIR		0X04
 //CYCEND interrupt mark main programme cleared after reading 7753 data
//
#define	CYC_ReadA	0x01	
#define	CYC_ReadB	0x02	
#define	CYC_ReadC	0x04
//#define	CYC_Adj		0x08	//mark of meter setting
#define	CYC_Adj		0x08	//
//#define	CYC_Hz60	0x10	//position when frequency is 60 Hz
#define	CYC_Hz60	0x10	//
#define	CYC_MPunish	0x20
//FlsLP
#define	FlsLP_DT_RBsy	0x01
#define	FlsLP_DT_WBsy	0x02
#define	FlsLP_DA_RBsy	0x04
#define	FlsLP_DA_WBsy	0x08
#define	FlsLP_Com_RBsy	0x10
#define	FlsLP_Com_WBsy	0x20
//#define	FlsLP_Rec1_W	0x40	       // record the first flag writing
#define	FlsLP_Rec1_W	0x40	//
//#define	FlsLP_DA_W		0x80	//DataEntry write flag
#define	FlsLP_DA_W		0x80	//
//LPFlag
//#define	DemandExist		0x01	//there is demand data in the load curve
#define	DemandExist		0x01	//
//#define	TimeInvIs0		0x02	//spacing time is 0
#define	TimeInvIs0		0x02	//
//Event Flag1
#define	F_Ev_Prog		0x01
#define	F_Ev_PwrOff		0x02
#define	F_Ev_PwrOn		0x04
#define	F_Ev_AllClr		0x08
#define	F_Ev_CoverOp	0x10
#define	F_Ev_CoverCl	0x20
#define	F_Ev_DisOrd		0x40
#define	F_Ev_Magic		0x80
//Event Flag2
#define	F_Ev_MaMDRST	0x01
#define	F_Ev_MaBill		0x02
//Alarm
#define	F_Al_DisOrd			0x01
#define	F_Al_BatLow			0x02
#define	F_Al_EEPero			0x04
#define	F_Al_DisOrd_Disp	0x10
#define	F_Al_BatLow_Disp	0x20
#define	F_Al_EEPero_Disp	0x40
//PortDf
#define	Port_actiF		0x01
#define	Port_reactiF	0x02
//IntTmStart
#define MDSTART         0x01
#define LPSTART         0x02

typedef struct
{
	char 	Run;
	char 	Power;
	char	Clk;
	char	Fee;	
	//char	op7753;
	//char	Op7022;
	char	Reactive;
	char	Power_dir;
	char	APPA_dir;
	//char	CYC7753;
	//char	FlsLoadCurve;
	char	FlsLP;
	char	LPFlag;
	char	EventFlg1;
	char	EventFlg2;
	char	PortDf;
   	char	Alarm;
    char    IntTmStart;
  	char 	ClearAllData;
	char 	MDClrFlag;
	char    ClearKeyFree;
} FLAG_T;

typedef struct
{
       //char PreviousFee;	//previous tariff 
	char PreviousFee;	//
	//char CurrentFee;	//current tariff
	char CurrentFee;	//
	//char CurrentDT;		//current day tariff meter
	char CurrentDT;		//
	char CurrentDTSegs;	//
	char CurrentDTSeg;	//
} FEE_T;

typedef struct
{
	char	Key1Tmr;            //Act
	char	Key2Tmr;    		//React
	char	Key3Tmr;    		//Phcal
	char	Key4Tmr;			//APOS
	char	Key5Tmr;			//VRMSOS
	char	Key6Tmr;			//IRMSOS
	char	Key7Tmr;			//K
	char	Key8Tmr;			//ReactL	
} CALITMR_T;

typedef struct
{
	char    P_OutCkTmr;
	char    P_OutCkVTmr;
} PULSETMR_T;

typedef struct
{
       //char	Cover_Dly;		//open cover close cover delay
	char	Cover_Dly;			//
	//char	Magic_Dly;		//magnetic field test delay
	char	Magic_Dly;			//
	//char	BLight_Dly;		//backlight delay
	char	BLight_Dly;			//
	//char	PowerDely;		//power up delay x minute
	char	PowerDely;			//
	//char	MBillDely;		//demand manual settlement is greater than xx minutes
	char	MBillDely;			//
	//char	FeeTbDely;		//delay 5 seconds after tariff update->set any parameter
	char	FeeTbDely;			//
	//char	AllDspDly;		//full display delay
	char	AllDspDly;			//
	//char	DLBillDely;		//delay 10 seconds after power quantity manual settlement 
	char	DLBillDely;			//
    // char    PowerRunDly;        //power on mode operation delay times
    char    PowerRunDly;        //
    //char    ShutDispHour;       //power off x hour, turn off all display
    char    ShutDispHour;       //
} RUNDLY_T;

typedef struct
{
	int8u DUOver[3];
	int8u DLostPhase[3];
	int8u DIOver[3];
	int8u DHerr;
	int8u DUnBala;
	int8u DUorder;

} EVENTDLY_T;

//EF1
#define F_VFailureA 0x01
#define F_VFailureB 0x02
#define F_VFailureC 0x04
#define F_VUnderA   0x10
#define F_VUnderB   0x20
#define F_VUnderC   0x40
//EF2
#define F_VOverA    0x01
#define F_VOverB    0x02
#define F_VOverC    0x04
#define F_OverLoadA 0x10
#define F_OverLoadB 0x20
#define F_OverLoadC 0x40
//EF3
#define F_LowPFA    0x01
#define F_LowPFB    0x02
#define F_LowPFC    0x04
#define F_IUnderA   0x10
#define F_IUnderB   0x20
#define F_IUnderC   0x40
//states
#define	F_HardErr	0x01
#define	F_LowBatte	0x02
#define	F_ConPhase	0x04
#define	F_LostPhase	0x08
#define	F_UOver		0x10
#define	F_UnBala	0x20
#define	F_IOver		0x40
#define	F_UUnder	0x80

typedef struct
{
    char EFlag1;
    char EFlag2;
    char EFlag3;
    char EFlagBk1;
    char EFlagBk2;
    char EFlagBk3;
    int16u States;
} EVENTFLAG;
	
typedef struct
{
       //unsigned char PpCnt;  //active forward impulse number
	unsigned char PpCnt;  //
	//unsigned char PnCnt;  //active reverse impulse number
	unsigned char PnCnt;  //

       //unsigned char RpCnt;  //reactive forward impulse number
	unsigned char RpCnt;  //
	//unsigned char RnCnt;  //reactive reverse impulse number
	unsigned char RnCnt;  //

	//unsigned char RnCnt;  //apparent forward impulse number
	unsigned char VApCnt; //
	//unsigned char VAnCnt; //apparent reverse impulse number
	unsigned char VAnCnt; //
	
	unsigned char PpCntABC[3];
	unsigned char PnCntABC[3];
	unsigned char RpCntABC[3];
	unsigned char RnCntABC[3];
	
	unsigned char VApCntABC[3];
	unsigned char VAnCntABC[3];
	//unsigned char RQ[4];	//four quadrants reactive impulse number
	unsigned char RQ[4];	//
	//unsigned char RQ1ABC[3];//split-phase first quadrant reactive impulse number
	unsigned char RQ1ABC[3];//
	//unsigned char RQ2ABC[3];//split-phase second quadrant reactive impulse number
	unsigned char RQ2ABC[3];//
	//unsigned char RQ3ABC[3];//split-phase third quadrant reactive impulse number
	unsigned char RQ3ABC[3];//
	//unsigned char RQ4ABC[3];//split-phase forth quadrant reactive impulse number
	unsigned char RQ4ABC[3];//
	//int		CntChk; //check code in total // 42
	int		CntChk; //Ð£ÑéÂë ¹²              // 42	
} SRAM_T;

typedef struct
{
	unsigned char   EvenLogCode;
	unsigned char   EvenPtr;
	unsigned char	LoadProCh;
} EVENLPPTR_T;


typedef struct
{
	//char 	Type[8];
	long	Software;
	long	Hardware;
        long	type;
} VERSION_T;


/* Time Stamp */
typedef struct
{
   BCD1 	Sec;
   BCD1 	Min;
   BCD1 	Hour;
   BCD1 	Day;
   BCD1 	Mon;
   BCD1 	Year;
} YMDhms_T;


#endif
