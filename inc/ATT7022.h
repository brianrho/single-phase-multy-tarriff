/******************************************************************************
 ATT7022.h - ATT7022 driver
 * ATT7022.h - ATT7022驱动
 * 
 * Copyright Hangzhou East Smart Technology Co.,Ltd.
 * 
 * DESCRIPTION: - 
 *      
 * modification history
 * --------------------
 * 01a, 09feb2011,  written
 * --------------------
 ******************************************************************************/
/*amplification split-phase, two phases maximum, segment point sampling voltage <0.35v*/
#define		ATT7022_STEP_EN		1

#define		METER_UN			FC_Un
#define		METER_IB			FC_Ib
#define		METER_CONST			FC_CP	//
#define		ATT7022_Vu			0.522	//1.2/2000 *230=138mv*ATT7022_UnG
#define		ATT7022_Vi			0.06	//5*12=60MV	
//define		ATT7022_UnG			1//		0,1,2,3 equals to two times, four times, eight times, sixteen times
#define		ATT7022_UnG			1//
//define		ATT7022_Ik			12		//ten ohm
#define		ATT7022_Ik			12		//
//(5760000000*ATT7022_UnG*ATT7022_UnG*ATT7022_Vu*ATT7022_Vi)\(METER_UN*METER_IB*METER_CONST)
#define		ATT7022_HF		//576000000*/
#define		PHASE_A0			0x00
#define		PHASE_B0			0x01
#define		PHASE_C0			0x02

#define		PHASE_A1			0x03
#define		PHASE_B1			0x04
#define		PHASE_C1			0x05

/*register definition*/

//*************output register address  *************
//active power
#define		ATT7022_r_Pa			0x01
#define		ATT7022_r_Pb			0x02
#define		ATT7022_r_Pc			0x03
#define		ATT7022_r_Pt			0x04
//reactive power
#define		ATT7022_r_Qa			0x05
#define		ATT7022_r_Qb			0x06
#define		ATT7022_r_Qc			0x07
#define		ATT7022_r_Qt			0x08
//apparent power
#define		ATT7022_r_Sa			0x09
#define		ATT7022_r_Sb			0x0a
#define		ATT7022_r_Sc			0x0b
#define		ATT7022_r_St			0x0c
//apparent frequency, current voltage phase
#define		ATT7022_freq			0x1c
#define		ATT7022_pg_a			0x18
#define		ATT7022_Pg_b			0x19
#define		ATT7022_Pg_c			0x1a
#define		ATT7022_Pg_t			0x1b
//voltage effective value
#define		ATT7022_r_URmsa		0x0d
#define		ATT7022_r_URmsb		0x0e
#define		ATT7022_r_URmsc		0x0f
//current effective value
#define		ATT7022_r_IRmsa		0x10
#define		ATT7022_r_IRmsb		0x11
#define		ATT7022_r_IRmsc		0x12

//energy register working status
#define		ATT7022_r_EFlag		0x30
//active energy zero clearing after reading
#define		ATT7022_r_Epa2		0x31
#define		ATT7022_r_Epb2		0x32
#define		ATT7022_r_Epc2		0x33
#define		ATT7022_r_Ept2		0x34
//reactive energy zero clearing after reading
#define		ATT7022_r_Eqa2		0x35
#define		ATT7022_r_Eqb2		0x36
#define		ATT7022_r_Eqc2		0x37
#define		ATT7022_r_Eqt2		0x38
//PQS apparent energy register, zero clearing after reading
#define     ATT7022_LineEpa2    0x74
#define     ATT7022_LineEpb2    0x75
#define     ATT7022_LineEpc2    0x76
//PQS conjunction apparent energy register, zero clearing after reading
#define     ATT7022_LineEpt2    0x77

//symbol marke split-phase, phase order, SIG marke and so on
#define		ATT7022_Flag		0x2c
//active factor
#define		ATT7022_PFa			0x14
#define		ATT7022_PFb			0x15
#define		ATT7022_PFc			0x16
#define		ATT7022_PFt			0x17
/************check code *****************/
/************校验值*****************/
#define		ATT7022_CHK			0x5F	

/************reference address **************/
//#define		ATT7022_UADCPg		0x3f//voltage channel ADC amplification choice
#define		ATT7022_UADCPg		0x3f//
//#define		ATT7022_HFConst		0x20//high frequency impulse output configuration
#define		ATT7022_HFConst		0x20//
//#define		ATT7022_HFDouble	0x3e//impulse constant double choice
#define		ATT7022_HFDouble	0x3e//
//#define		ATT7022_IStartup	0x1f//starting current threshold value configuration
#define		ATT7022_IStartup	0x1f//
//#define		ATT7022_Irechg		0x1e//ratio error compensation area configuration
#define		ATT7022_Irechg		0x1e//
//#define		ATT7022_FAILVoltage	0x29//loss of voltage threshold value configuration
#define		ATT7022_FAILVoltage	0x29//
//#define		ATT7022_Iregion1	0x02//phase compensation area configuration 1
#define		ATT7022_Iregion1	0x02//
//#define		ATT7022_Iregion2	0x03//phase compensation area configuration 2
#define		ATT7022_Iregion2	0x03//
//#define		ATT7022_Iregion3	0x04//phase compensation area configuration 3
#define		ATT7022_Iregion3	0x04//
//#define		ATT7022_Iregion4	0x05//phase compensation area configuration 4
#define		ATT7022_Iregion4	0x05//
//#define     ATT7022_EnlineFreq  0x2d//fundamental wave measurement used to control register
#define     ATT7022_EnlineFreq  0x2d//
/*
 notice:
 注:
 ATT7022_EnlineFreq = 0x007812 fundamental wave meter/hamonic meter
 ATT7022_EnlineFreq = 0x007812 基波表/谐波表
 ATT7022_EnlineFreq = 0x008127 RMS apparent energy meter
 ATT7022_EnlineFreq = 0x008127 RMS视在能量表
 ATT7022_EnlineFreq = 0x005523 PQS apparent energy meter
 ATT7022_EnlineFreq = 0x005523 PQS视在能量表
 other value is prohibited to adopt the above function
 其他值 禁止以上功能
 currently adopts PQS
 目前采用PQS
 */

//#define		ATT7022_PgainA0		0x06//A phase power gain 0
#define		ATT7022_PgainA0		0x06//A 相功率增益 0
//#define		ATT7022_PgainB0		0x07//B phase power gain 0
#define		ATT7022_PgainB0		0x07//B 相功率增益 0
//#define		ATT7022_PgainC0		0X08//C phase power gain 0
#define		ATT7022_PgainC0		0X08//C 相功率增益 0
//#define		ATT7022_PgainA1		0x09//A phase power gain 1
#define		ATT7022_PgainA1		0x09//A 相功率增益 1
//#define		ATT7022_PgainB1		0x0A//B phase power gain 1
#define		ATT7022_PgainB1		0x0A//B 相功率增益 1
//#define		ATT7022_PgainC1		0x0B//C phase power gain 1
#define		ATT7022_PgainC1		0x0B//C 相功率增益 1
//#define		ATT7022_PhsregA0	0x0c//A phase area 0 phase calibration
#define		ATT7022_PhsregA0	0x0c//A 相区域 0 相位校正
//#define		ATT7022_PhsregA1	0x0d//A phase area 1 phase calibration
#define		ATT7022_PhsregA1	0x0d//A 相区域 1 相位校正
//#define		ATT7022_PhsregA2	0x0e//A phase area 2 phase calibration
#define		ATT7022_PhsregA2	0x0e//A 相区域 2 相位校正
//#define		ATT7022_PhsregA3	0x0f//A phase area 3 phase calibration
#define		ATT7022_PhsregA3	0x0f//A 相区域 3 相位校正
//#define		ATT7022_PhsregA4	0x10//A phase area 4 phase calibration
#define		ATT7022_PhsregA4	0x10//A 相区域 4 相位校正
//#define		ATT7022_PhsregB0	0x11//B phase area 0 phase calibration
#define		ATT7022_PhsregB0	0x11//B 相区域 0 相位校正
//#define		ATT7022_PhsregB1	0x12//B phase area 1 phase calibration
#define		ATT7022_PhsregB1	0x12//B 相区域 1 相位校正
//#define		ATT7022_PhsregB2	0x13//B phase area 2 phase calibration
#define		ATT7022_PhsregB2	0x13//B 相区域 2 相位校正
//#define		ATT7022_PhsregB3	0x14//B phase area 3 phase calibration
#define		ATT7022_PhsregB3	0x14//B 相区域 3 相位校正
//#define		ATT7022_PhsregB4	0x15//B phase area 4 phase calibration
#define		ATT7022_PhsregB4	0x15//B 相区域 4 相位校正
//#define		ATT7022_PhsregC0	0x16//C phase area 0 phase calibration
#define		ATT7022_PhsregC0	0x16//C 相区域 0 相位校正
//#define		ATT7022_PhsregC1	0x17//C phase area 1 phase calibration
#define		ATT7022_PhsregC1	0x17//C 相区域 1 相位校正
//#define		ATT7022_PhsregC2	0x18//C phase area 2 phase calibration
#define		ATT7022_PhsregC2	0x18//C 相区域 2 相位校正
//#define		ATT7022_PhsregC3	0x19//C phase area 3 phase calibration
#define		ATT7022_PhsregC3	0x19//C 相区域 3 相位校正
//#define		ATT7022_PhsregC4	0x1A//C phase area 4 phase calibration
#define		ATT7022_PhsregC4	0x1A//C 相区域 4 相位校正
//#define		ATT7022_UgainA		0x1B//A phase voltage calibration
#define		ATT7022_UgainA		0x1B//A 相电压校正
//#define		ATT7022_UgainB		0x1c//B phase voltage calibration
#define		ATT7022_UgainB		0x1c//B 相电压校正
//#define		ATT7022_UgainC		0x1D//C phase voltage calibration
#define		ATT7022_UgainC		0x1D//C 相电压校正
//#define		ATT7022_IgainA		0x26//A phase current calibration
#define		ATT7022_IgainA		0x26//A 相电流校正
//#define		ATT7022_IgainB		0x27//B phase current calibration
#define		ATT7022_IgainB		0x27//B 相电流校正
//#define		ATT7022_IgainC		0x28//C phase current calibration
#define		ATT7022_IgainC		0x28//C 相电流校正	
//#define		ATT7022_EAndMode	0x2a//combine-phase accumulation module choice
#define		ATT7022_EAndMode	0x2a//合相能量累加模式选择

//50Hz 
#define HalfCYC 0x64
#define HzDigit 8959
#define	HzConst 447950

#define		ATT7022_DIR_PA		0x0001
#define		ATT7022_DIR_PB		0x0002
#define		ATT7022_DIR_PC		0x0004
#define		ATT7022_DIR_PT		0x0008

#define		ATT7022_DIR_QA		0x0010
#define		ATT7022_DIR_QB		0x0020
#define		ATT7022_DIR_QC		0x0040
#define		ATT7022_DIR_QT		0x0080

#define		ATT7022_DIR_ANGLEA	0x0100
#define		ATT7022_DIR_ANGLEB	0x0200
#define		ATT7022_DIR_ANGLEC	0x0400
#define		ATT7022_DIR_ANGLET	0x0800

#define		QUADRANT_I			0
#define		QUADRANT_II			1
#define		QUADRANT_III		2
#define		QUADRANT_IV			3

//loss of voltage symbol is 0, meaning loss of voltage, =1 meaning no loss of voltage
#define		ATT7022Flag_LOWUA_ERR	0x01
#define		ATT7022Flag_LOWUB_ERR	0x02
#define		ATT7022Flag_LOWUC_ERR	0x04
//voltage dislocation
#define		ATT7022Flag_VPHASE_ERR	0x08
//current dislocation
#define		ATT7022Flag_IPHASE_ERR	0x10

typedef struct {
	//7 forward active, apparent
	unsigned char Pulse_Acti[4];
	unsigned char Pulse_Appa[4];
	//7 reverse active, apparent
	unsigned char Pulse_ActiF[4];
	unsigned char Pulse_AppaF[4];
	//12 reactive four quadrants
	unsigned char Pulse_ReacRQ1[4];
	unsigned char Pulse_ReacRQ2[4];
	unsigned char Pulse_ReacRQ3[4];
	unsigned char Pulse_ReacRQ4[4];
	//reactive forward/reverse
	unsigned char Pulse_ReacRQ;
	unsigned char Pulse_ReacRQF;
	//HEX format preservation
	//unsigned char 	Quadrant[4];	//four quadrant
	unsigned char Quadrant[4]; //
	unsigned int DIR_Flag;
	unsigned long IRMS[3]; //A,B,C
	unsigned long VRMS[3]; //A,B,C
	//unsigned long	Power_Real[4];	//total active power A,B,C                                               
	unsigned long Power_Real[4]; //
	//unsigned long	Var_Real[4];	//total reactive power A,B,C
	unsigned long Var_Real[4]; //
	//unsigned long	APPA_Real[4];	//total apparent power A,B,C //char changed to long 20150528
	unsigned long APPA_Real[4]; //
	unsigned int PF[4]; //
	unsigned int FREQ[3];
	unsigned int PG[4];
	unsigned long Att7022Flag;
	//unsigned char	QuadNo;			//current quadrant
	unsigned char QuadNo; //

} ATT7022_REAL_VAL_T;

typedef struct {
	int8u IRMS[3][4];
	int8u VRMS[3][4];
	int8u Power_Real[4][4];
	int8u Var_Real[4][4];
	int8u APPA_Real[4][4];
	int8u PF[4][4]; //
	int8u FREQ[4];
	int8u PG[4][4];

} ATT7022_REAL_BCD_T;

typedef struct {
	unsigned char IRMS_Adj_A[3];
	unsigned char IRMS_Adj_B[3];
	unsigned char IRMS_Adj_C[3];

	unsigned char VRMS_Adj_A[3];
	unsigned char VRMS_Adj_B[3];
	unsigned char VRMS_Adj_C[3];
	unsigned char Phase_A[3];
	unsigned char Phase_B[3];
	unsigned char Phase_C[3];

	//unsigned char   Mode[3];            //active/reactive calculation form  energy calculation form
	unsigned char Mode[3]; //

	//unsigned char	InvalidPowerOnRead;//invalid seconds when on-power
	unsigned char InvalidPowerOnRead; //1			//
	//unsigned char	ValidTimes[3];		//3			//the data of P53 is no more than three seconds, which should be cleared
	unsigned char ValidTimes[3]; //3			//

	//unsigned char	BA_Angel[2];		//BA
	//unsigned char	CA_Angel[2];		//CA

	//volatile unsigned int    Circles;
	//unsigned int	AddCount;

} ATT7022_PARA_T;


typedef struct {
	unsigned char IRMS_Adj_A[3];
	unsigned char IRMS_Adj_B[3];

	unsigned char VRMS_Adj[3];

	unsigned char Phase_A[3];
	unsigned char Phase_B[3];

	//unsigned char   Mode[3];            //active/reactive calculation form  energy calculation form
	unsigned char Mode[3]; //

	//unsigned char	InvalidPowerOnRead;//invalid seconds when on-power
	unsigned char InvalidPowerOnRead; //1			//
	//unsigned char	ValidTimes[3];		//3			//the data of P53 is no more than three seconds, which should be cleared
	unsigned char ValidTimes[3]; //3			//

	//unsigned char	BA_Angel[2];		//BA
	//unsigned char	CA_Angel[2];		//CA

	//volatile unsigned int    Circles;
	//unsigned int	AddCount;

} RN8209_PARA_T;


extern unsigned char ATT7022_ParaChk(void);

extern const unsigned char QDirTbl[4];
extern const unsigned char PDirTbl[4];
extern const unsigned int ADirTbl[4];

extern ATT7022_REAL_BCD_T gsAttBCDVal;
extern ATT7022_REAL_VAL_T gsAttRealVal;
extern ATT7022_PARA_T gsAttPara;
extern RN8209_PARA_T gsRnPara;
extern unsigned char guAttChk[3];

void CalcPulse(void);
unsigned char ATT7022_Process(void);
void ATT7022_RAMClear(void);
void ATT7022_Init(void);

unsigned char ATT7022_RReg(unsigned char *ucBuf, unsigned char ucAdr);
