/*
 * RN8209.h
 *
 *  Created on: Jan 12, 2016
 *      Author: User
 */
//#include "..\inc\includes.h"


#ifndef RN8209_H_
#define RN8209_H_

//Meter calibration parameter and metering control register
#define SYSCON    0x00    //System control register
#define EMUCON    0x01    //Metering control register
#define HFCONST   0x02    //Pulse frequency register
#define PSTART    0x03    //Positive start power setting
#define QSTART    0x04    //Reactive start power setting
#define GPQA      0x05    //Channel A power gain calibration register
#define GPQB      0x06    //Channel B power gain calibration register
#define PHSA      0x07    //Channel A phase calibration register 1
#define PHSB      0x08    //Channel B phase calibration register 1
#define QPHSCAL   0x09    //Reactive phase compensation
#define APOSA     0x0A    //Channel A active power bias calibration register
#define APOSB     0x0B    //Channel B active power bias calibration register
#define RPOSA     0x0C    //Channel A reactive power bias calibratio register
#define RPOSB     0x0D    //Channel B reactive power bias calibratio register
#define IARMSOS   0x0E    //Current Channel A valid values bias compensation
#define IBRMSOS   0x0F    //Current Channel B valid values bias compensation
#define IBGAIN    0x10    //Current Channel B gain setting

//Metering parameter and state register
#define PFCNT     0x20    //Fast active pulse counting *
#define QFCNT     0x21    //Fast reactive pulse counting
#define IARMS     0x22    //Channel A current valid value *
#define IBRMS     0x23    //Channel A current valid value *
#define URMS      0x24    //Voltage valid value *
#define UFREQ     0x25    //Voltage frequency *
#define POWERPA   0x26    //Active power A *
#define POWERPB   0x27    //Active power B *
#define POWERQ    0x28    //Reactive power *
#define ENERGYP   0x29    //Active energy, no clear after reading *
#define ENERGYP2  0x2A    //Active energy, no clear after reading
#define ENERGYQ   0x2B    //Reactive energy, no clear after reading *
#define ENERGYQ2  0x2C    //Reactive energy, no clear after reading
#define EMUSTATUS 0x2D    //Metering state and calibration and register

//Interrupt register
#define IE        0x40    //Interrupt allow register
#define IF        0x41    //Interrupt flag register
#define RIF       0x42    //Reset interrupt state register

//System state register
#define SYSSTATUS 0x43    //System state register
#define RDATA     0x44    //Last time SPI/RSIO read-out data
#define WDATA     0x45    //Last time SPI/RSIO written data
#define DEVICEID  0x7F    //RN8209 deviceID


//#define MISO     RG1
//#define SPI_SS(x)    ((x) ? (RG0 = 1) : (RG0 = 0))
//#define SPI_SCLK(x)  ((x) ? (RG3 = 1) : (RG3 = 0))
//#define SPI_MISO(x)  ((RG1) ? (x |= 0x01) : (x &= 0xFE))
//#define SPI_MOSI(x)  ((x) ? (RG2 = 1) : (RG2 = 0))


#define Pulse_select //RD3
#define Meteradj_int //RC4
#define IRQ0         //RG5

//#define RN8209_RESET(x) ((x) ? (RD6 = 1) : (RD6 = 0))

#ifdef METER_TYPE == 2
    #define Ib         1000     //Basic current
    #define START_THOLD   0x00C5      // 127
#else
    #define Ib         2000     //Basic current
    #define START_THOLD   0x0057
#endif


#ifdef SINGLE_PHASE_MULTI_TARIFF
#ifdef DIREC
#define    CONST_E   0x0A10//800
#else
#define    CONST_E    3200
#endif

#define    true    1
#define    TRUE    1
#define    false   0
#define    FALSE   0

#endif

typedef struct
{
    unsigned int 	delay;
    unsigned char 	receive_length;
    unsigned char 	receive[37];
    unsigned char 	receive_start;
    unsigned char 	send_length;
    unsigned char 	send[25];
}COM;

//Define domain
typedef struct
{
    unsigned char clear: 1;          //Clear power flag
    unsigned char reset: 1;          //Reset flag
    unsigned char supply: 1;         //Power supply flag
    unsigned char battery: 1;        //Battery under voltage
    unsigned char lock: 1;			//Password protection flag
    unsigned char communication: 1;  //Communication status flag
    unsigned char display: 1;        //Refresh display flag
    unsigned char steal: 1;          //Power stealing  flag
    unsigned char pulse_change: 1;   //Pulse constant change flag
    unsigned char reverse: 1;		//Reverse operation
    unsigned char use_a: 1;          //Metering phase A
    unsigned char use_b: 1;          //Metering phase B
    unsigned char apc_modle: 1;      //Successful setting flag of wireless module
    unsigned char TX_SW: 1;			//The send switch flag
    unsigned char key_p: 1;			//Button flag
    unsigned char error: 1;          //EEPROM error flag
    unsigned char disp_error: 1;     //Display error flag
    unsigned char vol_error: 1;      //Volatage error flag
    unsigned char energy_error: 1;   //Energy Chip error flag
}FLAG;
typedef struct {
	unsigned char I_CAL[4];
	unsigned long ka;
	unsigned long kb;
	unsigned char V_CAL[4];
	unsigned int kv;
	unsigned char P_RMS[4];
	char P_Cal_10L[4];
	char P_Cal_05L[4];
	char P_Cal_10LM[4];
	char Q_Cal_10L[4];
	char Q_Cal_05L[4];
	char Q_Cal_10LM[4];
	unsigned char ID[2];
	unsigned char Channel;
	unsigned char buf[10];
	unsigned int ID_IEC[10];
	unsigned char count_id;
	unsigned char Status_Cal;
	unsigned long lTemp32A;
	unsigned int wTemp16;
} RN8209_CALIB;

typedef struct {
	union {
			unsigned char byte[4];
			unsigned long val;
		} PF_RMS;
	union {
		unsigned char byte[4];
		unsigned long val;
	} I_RMS;
	union {
		unsigned char byte[4];
		unsigned long val;
	} Ia_RMS;
	union {
		unsigned char byte[4];
		unsigned long val;
	} Ib_RMS;
	union {
		unsigned char byte[4];
		unsigned long val;
	} V_RMS;
	union {
		signed char byte[4];
		signed long val;
	} Pa_RMS;
	union {
		signed char byte[4];
		signed long val;
	} Pb_RMS;
	union {
		signed char byte[4];
		signed long val;
	} P_RMS;
	union {
		signed char byte[4];
		signed long val;
	} Q_RMS;
	union {
		unsigned char byte[4];
		unsigned long val;
	} F_RMS;
	union {
		unsigned char byte[4];
		unsigned long val;
	} ENERGY_P;
	union {
		unsigned char byte[4];
		unsigned long val;
	} ENERGY_P2;
	union {
		unsigned char byte[4];
		unsigned long val;
	} ENERGY_Q;
	union {
		unsigned char byte[4];
		unsigned long val;
	} ENERGY_Q2;
	union {
		unsigned char byte[4];
		unsigned long val;
	} ANGLE;
	unsigned char EMUSTATUS_R[2];
	union {
		unsigned char byte[4];
		unsigned long val;
	} ID;
	unsigned long Q_Lead;
	unsigned long Q_Lag;
	unsigned char Channel;
	unsigned char buf[10];
	unsigned int ID_IEC[10];
	unsigned char count_id;
	unsigned char Status_Cal;
	unsigned int DIR_Flag;
	unsigned long Active_energy;
	unsigned long ReActive_energy;
} RN8209_RMS;

typedef struct {
	unsigned char PF_RMS[4];
	unsigned char I_RMS[4];
	unsigned char Ia_RMS[4];
	unsigned char Ib_RMS[4];
	unsigned char V_RMS[4];
	signed char Pa_RMS[4];
	signed char Pb_RMS[4];
	signed char Q_RMS[4];
	unsigned char F_RMS[4];
	unsigned char Angle[4];
	unsigned char ENERGY_P[4];
	unsigned char ENERGY_P2[4];
	unsigned char ENERGY_Q[4];
	unsigned char EMUSTATUS_R[4];

} RN8209_RMS_BCD;



typedef union               //Public data operation area 8 bytes
{
    unsigned char ucTempBuf[8];
    unsigned long lTemp32;
    unsigned int  wTemp16;
    unsigned char ucTemp8;
    struct
    {
        unsigned long lTemp32A;
        unsigned long lTemp32B;
    }b32bits;
    struct
    {
        unsigned char ucTemp8L;
        unsigned char ucTemp8M;
        unsigned char ucTemp8H;
    }b24bits ;
}STRUDataComm;


void RN8209_DelayUs(unsigned char ucTime);
void delay_ms(unsigned int count);
void SPI_Init_RN(void);
void SPI_WriteByte(unsigned char ucData);
unsigned char SPI_ReadByte(void);
void RN8209_WriteData(unsigned char wReg, unsigned char *pBuf, unsigned char ucLen);
void RN8209_ReadData(unsigned short wReg, unsigned char *pBuf, unsigned char ucLen);
void POWERSUM_get(void);
long POWERP_get(unsigned char x);
unsigned long CURRENT_get(unsigned char x);
unsigned long VOLTAGE_get(void);
//int FREQ_get(void);
//void VGAIN_adj(unsigned char *adj_value) ;
void VGAIN_adj(unsigned long v_cal);
void IGAIN_adj(unsigned long adj_value) ;
void PHCAL_adj(int adj_value, unsigned char x);
void WGAIN_adj(int adj_value, unsigned char x);
void IOFFSET(unsigned char x);
void POFFSET();
void read_data(unsigned char lenth, unsigned char add);
void store_data(unsigned char lenth, unsigned char add, unsigned long data);
void store_old(void);
void EEPROMdata_init(void);
void CF_OUT(unsigned char x);
void select_KWh_pulse(void);
void Current_select(void);
void RN8209_Init(void);
unsigned char RN8209_Calib(void);
unsigned char RN8209_Check(void);
void RN8209_Process(void);
//void RN8209_repeat_init(void);
void re_power_data(void);
void store_energerdata(void);

#endif /* RN8209_H_ */
