/**************************************************************************
//document type:
//document function:
//modification permission:
//document reference:

//founder:
//creation date:
//current version:

//version information:

//instruction:
**************************************************************************/


#ifndef _INCLUDES_H
#define _INCLUDES_H

#include <msp430x44x.h>

#include "Typedef.h"      

//#define TEST
#define BNTHANG
#define NO_FRAM
#define SINGLE_PHASE_MULTI_TARIFF
#define DIREC
//#define INDEREC

#include "8025T_Driver.h"

#define STA_SW_LOCK 0x01
#define STA_POW_LOW 0x02
//current reversal
#define STA_FX_CURR 0x04 //

//current reversal
#define LOG_CURRFX   0  //
//low voltage and voltage loss events
#define LOG_LOSTU   1  //
//overvoltage events
#define LOG_OVERU   2  //
//hardware error events
#define LOG_HDERR   3  //
//phase sequence error events
#define LOG_XXERR    4  //
//battery events
#define LOG_BARERR    5  //
//overcurrent events
#define LOG_OVERI   6  //

#define LOG_MAX  7

//record time delay
#define LOG_CRD_TIME 61  //

#include <string.h>
#include <math.h>
//#include "RTC.h"
#include "interrupt.h"
#include "meter_struct.h"
#include "E2_Layout.h"
#include "PortConfig.h"
#include "Common.h"
#include "General.h"

//DRIVER
#include "c_Target.h"
#include "I2C_Driver.h"
#include "EEP_Driver.h"
#include "SPI_Driver.h"
#include "DataFlash_Driver.h"
#include "Fram_Driver.h"
#include "ATT7022.h"
#include "BU9792_Driver.h"
#include "RN8209.h"
#include "Meter_struct.h"

//
#include "Events.h"
#include "Events2.h"
#include "Display.h"

#include "Tou.h"
#include "LoadCurve.h"
#include "Display.h"
#include "KeyProcess.h"
//
#include "Measure.h"
#include "IEC_Commu.h"
//
#include "F_Layout.h"
#include "F_Layout.h"
#include "D_Layout.h"
#include "Mem.h"
#include "Check.h"
#include "Data.h"



#define  off(st,n)   (unsigned int)(&((( t*)0)->n))
#define  size(st,n)  (unsigned int)(sizeof((((st*)0)->n)))

//#define 	debug
#undef		debug

//contrast the PCB chart given by user
#define		VER_CUSTOM_HARD		1		//
//the function of hardware test valve state enable:1,enabled;0 invalid(1 corresponding to with reed switch;0 corresponding to no reed switch)
#define		GATE_DETECT_EN		0		//
//reset function
#define		VER_RES				0		//

//#define		GATE_DETECT_EN		0

//software simulation
#define			UART_SIM_EN		1		//


#ifdef SINGLE_PHASE_MULTI_TARIFF
typedef union {
	unsigned char byte[2];
	int dbyte;

} WORD;
typedef union {
	unsigned char byte[4];
	WORD w_val[2];
	long long_val;
} DWORD;

typedef struct {
	DWORD total_p;
	DWORD total_p_rate1;
	DWORD total_p_rate2;
	DWORD total_p_rate3;
	DWORD total_p_rate4;
	DWORD total_q_lag;
	DWORD total_q_lag_rate1;
	DWORD total_q_lag_rate2;
	DWORD total_q_lag_rate3;
	DWORD total_q_lag_rate4;
	DWORD total_q_lead;
	DWORD total_q_lead_rate1;
	DWORD total_q_lead_rate2;
	DWORD total_q_lead_rate3;
	DWORD total_q_lead_rate4;
} ENERGY;
#endif
#endif
