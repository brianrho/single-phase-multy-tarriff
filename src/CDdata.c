#include "..\inc\includes.h"

#ifdef SINGLE_PHASE_MULTI_TARIFF
//#include "..\inc\RN8209.h"
extern ENERGY vse1t_de;
extern volatile RN8209_RMS rn8209a_rms;
extern volatile RN8209_RMS_BCD rn8209a_rms_bcd;
extern volatile RN8209_CALIB rn8209a_calib;
#endif

const COMMTAB DaOutTab[] = {
		//========
		0x010800FF, (char*) EC_Pp0, EN_R + RS_FRAM + 5, 0x010801FF,
		(char*) EC_Pp1, EN_R + RS_FRAM + 5, 0x010802FF, (char*) EC_Pp2, EN_R
				+ RS_FRAM + 5, 0x010803FF, (char*) EC_Pp3, EN_R + RS_FRAM + 5,
		0x010804FF, (char*) EC_Pp4, EN_R + RS_FRAM + 5,

		0x020800FF, (char*) EC_Pn0, EN_R + RS_FRAM + 5, 0x020801FF,
		(char*) EC_Pn1, EN_R + RS_FRAM + 5, 0x020802FF, (char*) EC_Pn2, EN_R
				+ RS_FRAM + 5, 0x020803FF, (char*) EC_Pn3, EN_R + RS_FRAM + 5,
		0x020804FF, (char*) EC_Pn4, EN_R + RS_FRAM + 5,

		0x030800FF, (char*) EC_Rp0, EN_R + RS_FRAM + 5, 0x030801FF,
		(char*) EC_Rp1, EN_R + RS_FRAM + 5, 0x030802FF, (char*) EC_Rp2, EN_R
				+ RS_FRAM + 5, 0x030803FF, (char*) EC_Rp3, EN_R + RS_FRAM + 5,
		0x030804FF, (char*) EC_Rp4,
		EN_R + RS_FRAM + 5,

		0x040800FF, (char*) EC_Rn0,
		EN_R + RS_FRAM + 5, 0x040801FF, (char*) EC_Rn1,
		EN_R + RS_FRAM + 5, 0x040802FF, (char*) EC_Rn2,
		EN_R + RS_FRAM + 5, 0x040803FF, (char*) EC_Rn3,
		EN_R + RS_FRAM + 5, 0x040804FF, (char*) EC_Rn4,
		EN_R + RS_FRAM + 5,
		//=======
		0x010600FF, (char*) MD_Pp, EN_R + RS_FRAM + 3, 0x010601FF,
		(char*) MD_PpF1, EN_R + RS_FRAM + 3, 0x010602FF, (char*) MD_PpF2, EN_R
				+ RS_FRAM + 3, 0x010603FF, (char*) MD_PpF3, EN_R + RS_FRAM + 3,
		0x010604FF, (char*) MD_PpF4, EN_R + RS_FRAM + 3,

		0x020600FF, (char*) MD_Pn, EN_R + RS_FRAM + 3, 0x020601FF,
		(char*) MD_PnF1, EN_R + RS_FRAM + 3, 0x020602FF, (char*) MD_PnF2, EN_R
				+ RS_FRAM + 3, 0x020603FF, (char*) MD_PnF3, EN_R + RS_FRAM + 3,
		0x020604FF, (char*) MD_PnF4, EN_R + RS_FRAM + 3,

		0x030600FF, (char*) MD_Rp, EN_R + RS_FRAM + 3, 0x030601FF,
		(char*) MD_RpF1, EN_R + RS_FRAM + 3, 0x030602FF, (char*) MD_RpF2, EN_R
				+ RS_FRAM + 3, 0x030603FF, (char*) MD_RpF3, EN_R + RS_FRAM + 3,
		0x030604FF, (char*) MD_RpF4, EN_R + RS_FRAM + 3,

		0x040600FF, (char*) MD_Rn, EN_R + RS_FRAM + 3, 0x040601FF,
		(char*) MD_RnF1, EN_R + RS_FRAM + 3, 0x040602FF, (char*) MD_RnF2,
		EN_R + RS_FRAM + 3, 0x040603FF, (char*) MD_RnF3,
		EN_R + RS_FRAM + 3, 0x040604FF, (char*) MD_RnF4,
		EN_R + RS_FRAM + 3,

		//=======
		0x310700FF, (char*) gsAttBCDVal.IRMS[0], EN_R + RS_RAM + 3, 0x510700FF,
		(char*) gsAttBCDVal.IRMS[1], EN_R + RS_RAM + 3, 0x710700FF,
		(char*) gsAttBCDVal.IRMS[2], EN_R + RS_RAM + 3,

		0x320700FF, (char*) gsAttBCDVal.VRMS[0],
		EN_R + RS_RAM + 2, 0x520700FF, (char*) gsAttBCDVal.VRMS[1],
		EN_R + RS_RAM + 2, 0x720700FF, (char*) gsAttBCDVal.VRMS[2],
		EN_R + RS_RAM + 2,
		//actice power
		//有功功率
		0x210700FF, (char*) gsAttBCDVal.Power_Real[0], EN_R + RS_RAM + 3,
		0x410700FF, (char*) gsAttBCDVal.Power_Real[1],
		EN_R + RS_RAM + 3, 0x610700FF, (char*) gsAttBCDVal.Power_Real[2],
		EN_R + RS_RAM + 3,
		//reactive power
		//无功功率
		0x230700FF, (char*) gsAttBCDVal.Var_Real[0], EN_R + RS_RAM + 3,
		0x430700FF, (char*) gsAttBCDVal.Var_Real[1], EN_R + RS_RAM + 3,
		0x630700FF, (char*) gsAttBCDVal.Var_Real[2], EN_R + RS_RAM + 3,
#if 0	
		//apparent power
		0x290700FF, (char*)&gsAttBCDVal.APPA_Real[0][1], EN_R +RS_RAM +3,
		0x490700FF, (char*)&gsAttBCDVal.APPA_Real[1][1], EN_R +RS_RAM +3,
		0x690700FF, (char*)&gsAttBCDVal.APPA_Real[2][1], EN_R +RS_RAM +3,
		//power factor
		0x330700FF, (char*)&gsAttBCDVal.PF[0], EN_R +RS_RAM +2,
		0x530700FF, (char*)&gsAttBCDVal.PF[1], EN_R +RS_RAM +2,
		0x730700FF, (char*)&gsAttBCDVal.PF[2], EN_R +RS_RAM +2,
#endif	
	};

extern unsigned char meter_state[];
extern unsigned char bill_rest;

const IntCOMMTAB CommTab[] = {

#ifdef SINGLE_PHASE_MULTI_TARIFF

		0x2000, (char*) Adj_Para_SYSCON,
		EN_WR + RS_E2PROM + 2, //SYSCON
		0x2001, (char*) Adj_Para_EMUCON,
		EN_WR + RS_E2PROM + 2, //EMUCON
		0x2002, (char*) Adj_Para_HFCONST,
		EN_WR + RS_E2PROM + 2, //HFCONST
		0x2003, (char*) Adj_Para_PSTART,
		EN_WR + RS_E2PROM + 2, //PSTART
		0x2004, (char*) Adj_Para_QSTART,
		EN_WR + RS_E2PROM + 2, //QSTART
		0x2005, (char*) Adj_Para_GPQA,
		EN_WR + RS_E2PROM + 2, //GPQA
		0x2006, (char*) Adj_Para_GPQB,
		EN_WR + RS_E2PROM + 2, //GPQB
		0x2007, (char*) Adj_Para_PHSA,
		EN_WR + RS_E2PROM + 1, //PHSA
		0x2008, (char*) Adj_Para_PHSB,
		EN_WR + RS_E2PROM + 1, //PHSB
		0x2009, (char*) Adj_Para_QPHSCAL,
		EN_WR + RS_E2PROM + 2, //QPHSCAL
		0x200A, (char*) Adj_Para_APOSA,
		EN_WR + RS_E2PROM + 2, //APOSA
		0x200B, (char*) Adj_Para_APOSB,
		EN_WR + RS_E2PROM + 2, //APOSB
		0x200C, (char*) Adj_Para_RPOSA,
		EN_WR + RS_E2PROM + 2, //RPOSA
		0x200D, (char*) Adj_Para_RPOSB,
		EN_WR + RS_E2PROM + 2, //RPOSB
		0x200E, (char*) Adj_Para_IARMSOS,
		EN_WR + RS_E2PROM + 2, //IARMSOS
		0x200F, (char*) Adj_Para_IBRMSOS,
		EN_WR + RS_E2PROM + 2, //IBRMSOS
		0x2010, (char*) Adj_Para_IBGAIN,
		EN_WR + RS_E2PROM + 2, //Kv
		0x2011, (char*) Adj_Para_Kv,
		EN_WR + RS_E2PROM + 2, //IBGAIN
		0x2012, (char*) Adj_Para_Ka,
		EN_WR + RS_E2PROM + 2, //Ka
		0x2013, (char*) Adj_Para_Kb,
		EN_WR + RS_E2PROM + 2, //Kb


		//modification 2020-20FF read only
		0x2020, (char*) (rn8209a_rms_bcd.I_RMS),
		EN_R + RS_RAM + 3, //IRMSHex
		0x2023, (char*) (rn8209a_rms_bcd.V_RMS),
		EN_R + RS_RAM + 3, //VRMSHex
		//active power
		0x2026, (char*) (rn8209a_rms_bcd.ENERGY_P),
		EN_R + RS_RAM + 3,
		//reactive power
		0x202A, (char*) (rn8209a_rms_bcd.ENERGY_Q),
		EN_R + RS_RAM + 3,
		//power factor
		0x2030, (char*) (rn8209a_rms_bcd.PF_RMS),
		EN_R + RS_RAM + 3, //A
		0x2031, (char*) (rn8209a_rms_bcd.Angle),
		EN_R + RS_RAM + 3, //B
		0x203E, (char*) (rn8209a_rms_bcd.F_RMS),
		EN_R + RS_RAM + 4,

#else
		0x2000,
		(char*) Adj_Para_GAINA0,
		EN_WR + RS_FRAM + 3, //GAINA0
		0x2001,
		(char*) Adj_Para_GAINA1,
		EN_WR + RS_FRAM + 3,//GAINA1
		0x2002,
		(char*) Adj_Para_GAINB0,
		EN_WR + RS_FRAM + 3,//GAINB0
		0x2003,
		(char*) Adj_Para_GAINB1,
		EN_WR + RS_FRAM + 3,//GAINB1
		0x2004,
		(char*) Adj_Para_GAINC0,
		EN_WR + RS_FRAM + 3,//GAINC0
		0x2005,
		(char*) Adj_Para_GAINC1,
		EN_WR + RS_FRAM + 3,//GAINC1
		0x2006,
		(char*) Adj_Para_PHASEA0,
		EN_WR + RS_FRAM + 3,//PHASEA0
		0x2007,
		(char*) Adj_Para_PHASEA1,
		EN_WR + RS_FRAM + 3,//PHASEA1
		0x2008,
		(char*) Adj_Para_PHASEB0,
		EN_WR + RS_FRAM + 3,//PHASEB0
		0x2009,
		(char*) Adj_Para_PHASEB1,
		EN_WR + RS_FRAM + 3,//PHASEB1
		0x200A,
		(char*) Adj_Para_PHASEC0,
		EN_WR + RS_FRAM + 3,//PHASEC0
		0x200B,
		(char*) Adj_Para_PHASEC1,
		EN_WR + RS_FRAM + 3,//PHASEC1
		0x200C,
		(char*) Adj_Para_VRAM_A,
		EN_WR + RS_FRAM + 3,//IRMA
		0x200D,
		(char*) Adj_Para_VRAM_B,
		EN_WR + RS_FRAM + 3,//IRMB
		0x200E,
		(char*) Adj_Para_VRAM_C,
		EN_WR + RS_FRAM + 3,//IRMC
		0x200F,
		(char*) Adj_Para_IRAM_A,
		EN_WR + RS_FRAM + 3,//VRMSA
		0x2010,
		(char*) Adj_Para_IRAM_B,
		EN_WR + RS_FRAM + 3,//VRMSB
		0x2011,
		(char*) Adj_Para_IRAM_C,
		EN_WR + RS_FRAM + 3,//VRMSC
		0x2012,
		(char*) Adj_Para_Iregchg,
		EN_WR + RS_FRAM + 3,
		0x2013,
		(char*) Adj_Para_Iregion,
		EN_WR + RS_FRAM + 3,
		0x2014,
		(char*) Adj_Para_FHConst,
		EN_WR + RS_FRAM + 3,
		0x2015,
		(char*) Adj_Para_StartI,
		EN_WR + RS_FRAM + 3,


		//modification 2020-20FF read only
		0x2020, (char*) (gsAttBCDVal.IRMS[0]),
		EN_R + RS_RAM + 3, //IRMSHex
		0x2021, (char*) (gsAttBCDVal.IRMS[1]),
		EN_R + RS_RAM + 3, 0x2022, (char*) (gsAttBCDVal.IRMS[2]),
		EN_R + RS_RAM + 3, 0x2023, (char*) (gsAttBCDVal.VRMS[0]),
		EN_R + RS_RAM + 2, //VRMSHex
		0x2024, (char*) (gsAttBCDVal.VRMS[1]),
		EN_R + RS_RAM + 2, 0x2025, (char*) (gsAttBCDVal.VRMS[2]),
		EN_R + RS_RAM + 2,
		//active power
		0x2026, (char*) (gsAttBCDVal.Power_Real[0]),
		EN_R + RS_RAM + 3, 0x2027, (char*) (gsAttBCDVal.Power_Real[1]),
		EN_R + RS_RAM + 3, 0x2028, (char*) (gsAttBCDVal.Power_Real[2]),
		EN_R + RS_RAM + 3, 0x2029, (char*) (gsAttBCDVal.Power_Real[3]),
		EN_R + RS_RAM + 3,
		//reactive power
		0x202A, (char*) (gsAttBCDVal.Var_Real[0]),
		EN_R + RS_RAM + 3, 0x202B, (char*) (gsAttBCDVal.Var_Real[1]),
		EN_R + RS_RAM + 3, 0x202C, (char*) (gsAttBCDVal.Var_Real[2]),
		EN_R + RS_RAM + 3, 0x202D, (char*) (gsAttBCDVal.Var_Real[3]),
		EN_R + RS_RAM + 3,
		//power factor
		0x2030, (char*) (gsAttBCDVal.PF[0]),
		EN_R + RS_RAM + 3, //A
		0x2031, (char*) (gsAttBCDVal.PF[1]),
		EN_R + RS_RAM + 3, //B
		0x2032, (char*) (gsAttBCDVal.PF[2]),
		EN_R + RS_RAM + 3, //C
		0x2033, (char*) (gsAttBCDVal.PF[3]),
		EN_R + RS_RAM + 3, //总

#endif
		//apparent power
#ifdef HARDWARE_TWO
		0x2034, (char*)(gsAttBCDVal.APPA_Real[0]), EN_R +RS_RAM +3,
		0x2035, (char*)(gsAttBCDVal.APPA_Real[1]), EN_R +RS_RAM +3,
		0x2036, (char*)(gsAttBCDVal.APPA_Real[2]), EN_R +RS_RAM +3,
		0x2037, (char*)(gsAttBCDVal.APPA_Real[3]), EN_R +RS_RAM +3,
#endif
		//203A 203B 203C 203D 203F CT meter used
		//0x203E,     (char*)(gsAttBCDVal.FREQ),  EN_R +RS_RAM +4,//frequency
//		0x203E, (char*) (gsAttBCDVal.FREQ),
//		EN_R + RS_RAM + 4,		//

		0x20FF, (char*) (&gHardErr),
		EN_R + RS_RAM + 2,
		//0x202F, formatting ADE7753 parameter
		0x2100, (char*) (Adj_Para_CALIED),
		EN_WR + RS_FRAM + 4, //CAEDCAED

		//frozen times
		0xD200, (char*) (BILLCnt),
		EN_WR + RS_FRAM + 2,

#ifdef SINGLE_PHASE_MULTI_TARIFF
		//33
		0xA000,
		(char*) Val_VOver, //overvoltage threshold value
		EN_WR + RS_E2PROM + 2, //
		0xA001,
		(char*) Val_IOver, //overcurrent threshold value
		EN_WR + RS_E2PROM + 2, //
		0xA002,
//		(char*) Val_VFailure,
		(char*) Val_VUnder,
		EN_WR + RS_E2PROM + 2, ////loss of phase threshold value
		0xA003, (char*) Dly_VOver,
		EN_WR + RS_E2PROM + 2, ////useless
		0xA004,
		(char*) Dly_IOver, //useless
		EN_WR + RS_E2PROM + 2, //
		0xA005,
		(char*) Dly_VFailure, //useless
		EN_WR + RS_E2PROM + 2, //
		0xA006, (char*) Val_UnbV,
		EN_WR + RS_E2PROM + 2, ////three phase unbalanced

#else
		//33
		//0xA000,     (char*)Val_VOver,     EN_WR+RS_FRAM+2,    //overvoltage threshold value
		0xA000,
		(char*) Val_VOver,
		EN_WR + RS_FRAM + 2,//
		//0xA001,     (char*)Val_IOver,		EN_WR+RS_FRAM+2,	//overcurrent threshold value
		0xA001,
		(char*) Val_IOver,
		EN_WR + RS_FRAM + 2,//
		//0xA002,     (char*)Val_VFailure,	EN_WR+RS_FRAM+2,	//loss of phase threshold value
		0xA002,
		(char*) Val_VFailure,
		EN_WR + RS_FRAM + 2,//
		//0xA003,     (char*)Dly_VOver,		EN_WR+RS_FRAM+2,	//useless
		0xA003,
		(char*) Dly_VOver,
		EN_WR + RS_FRAM + 2,//
		//0xA004,     (char*)Dly_IOver,		EN_WR+RS_FRAM+2,	//useless
		0xA004,
		(char*) Dly_IOver,
		EN_WR + RS_FRAM + 2,//
		//0xA005,     (char*)Dly_VFailure,	EN_WR+RS_FRAM+2,	//useless
		0xA005,
		(char*) Dly_VFailure,
		EN_WR + RS_FRAM + 2,//
		//0xA006,     (char*)Val_UnbV,		EN_WR+RS_FRAM+2,	//three phase unbalanced
		0xA006,
		(char*) Val_UnbV,
		EN_WR + RS_FRAM + 2,//
#endif

#if 0	
		//0xA001,	      (char*)Val_VFailure,	EN_WR +RS_FRAM +22,	//loss of phase threshold value overvoltage threshold single phase load threshold value low power factor threshold value
		0xA001, (char*)Val_VFailure, EN_WR +RS_FRAM +22,//断相阀值 失压阀值 过压阀值 单相负荷阀值 低功率因数阀值
		//xxx.x	   xxx.x    xxx.x    xxxx.xxxx      xx.xx
		//delay loss of phase  delay loss of voltage delay overvoltage delay single phase load delay low power factor
		//断相延迟时间 失压延迟时间 过压延迟时间 单相负荷超限延迟时间 低功率因数延迟时间
		//xxxx         xxxx          xxxx         xxxx                xxxx
		//flashback BCD
		//倒序 BCD
		//0xA002,		(char*)VFailureNumC,	EN_WR +RS_FRAM +8,	//C phase loss of phase time B... A... total...flashback BCD xxxx xxxx xxxx xxxx
		0xA002, (char*)VFailureNumC, EN_WR +RS_FRAM +8,//C相断相次数 B... A... 总... 倒序 BCD xxxx xxxx xxxx xxxx
		//0xA003,		(char*)VFailureTimC,	EN_WR +RS_FRAM +12,	//C phase loss of phase accumulated time B... A...total...flashback BCD xxxxxx xxxxxx xxxxxx xxxxxx
		0xA003, (char*)VFailureTimC, EN_WR +RS_FRAM +12,//C相断相累计时间 B... A... 总... 倒序 BCD xxxxxx xxxxxx xxxxxx xxxxxx
		//0xA004,		(char*)VFailureLast1SC,	EN_WR +RS_FRAM +20, //C phase starting time of the latest loss of phase B... A...total ...flashback mmHHDDMMYY
		0xA004, (char*)VFailureLast1SC, EN_WR +RS_FRAM +20,//C相最近一次断相起始时间 B... A... 总... 倒序 mmHHDDMMYY
		//0xA005,		(char*)VFailureLast1PC, EN_WR +RS_FRAM +20, //C phase stopping time of the latest loss of phase B... A... total ...flashback mmHHDDMMYY
		0xA005, (char*)VFailureLast1PC, EN_WR +RS_FRAM +20,//C相最近一次断相结束时间 B... A... 总... 倒序 mmHHDDMMYY

		//0xA010,		(char*)VUnderPnAll,		EN_WR +RS_FRAM +13,	//total loss of voltage reverse active power total loss of voltage forward active power accumulated time  total loss of voltage time
		0xA010, (char*)VUnderPnAll, EN_WR +RS_FRAM +13,//总失压反向有功电量 总失压期间正向有功电量 总失压累计时间 总失压累计次数
		//xxxxxxx.x(scaling position changes with energy data position)xxxxxxx.x xxxxxx xxxx flashback BCD
		//xxxxxxx.x(小数点位置随电量数据的位置) xxxxxxx.x xxxxxx xxxx 倒序 BCD
		0xA011, (char*)VUnderPnA, EN_WR +RS_FRAM +13,//A...
		0xA012, (char*)VUnderPnB, EN_WR +RS_FRAM +13,//B...
		0xA013, (char*)VUnderPnC, EN_WR +RS_FRAM +13,//C...
		0xA014, (char*)VUnderPnAB, EN_WR +RS_FRAM +13,//AB...
		0xA015, (char*)VUnderPnAC, EN_WR +RS_FRAM +13,//AC...
		0xA016, (char*)VUnderPnBC, EN_WR +RS_FRAM +13,//BC...
		0xA017, (char*)VUnderPnABC, EN_WR +RS_FRAM +13,//ABC...

		//0xA020,		(char*)EVENT_VUnder_1,	EN_R +RS_E2PROM +44, //affair records of loss of phase mmHHDDMMYYmmHHDDMMYYzz flashback 4 groups
		0xA020, (char*)EVENT_VUnder_1, EN_R +RS_E2PROM +44,//失压事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA021, (char*)EVENT_VUnder_1, EN_R +RS_E2PROM +44,//失压事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA022, (char*)EVENT_VUnder_1, EN_R +RS_E2PROM +44,//失压事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA023, (char*)EVENT_VUnder_1, EN_R +RS_E2PROM +44,//失压事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA024, (char*)EVENT_VUnder_1, EN_R +RS_E2PROM +44,//失压事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA025, (char*)EVENT_VUnder_1, EN_R +RS_E2PROM +44,//失压事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA026, (char*)EVENT_VUnder_1, EN_R +RS_E2PROM +44,//失压事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA027, (char*)EVENT_VUnder_1, EN_R +RS_E2PROM +44,//失压事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA028, (char*)EVENT_VUnder_1, EN_R +RS_E2PROM +44,//失压事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA029, (char*)EVENT_VUnder_1, EN_R +RS_E2PROM +44,//失压事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组

		//0xA030,		(char*)EVENT_VOver_1,	EN_R +RS_E2PROM +44, //affair records of loss of phase mmHHDDMMYYmmHHDDMMYYzz flashback 4 groups
		0xA030, (char*)EVENT_VOver_1, EN_R +RS_E2PROM +44,//过压事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA031, (char*)EVENT_VOver_1, EN_R +RS_E2PROM +44,//过压事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA032, (char*)EVENT_VOver_1, EN_R +RS_E2PROM +44,//过压事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA033, (char*)EVENT_VOver_1, EN_R +RS_E2PROM +44,//过压事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA034, (char*)EVENT_VOver_1, EN_R +RS_E2PROM +44,//过压事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA035, (char*)EVENT_VOver_1, EN_R +RS_E2PROM +44,//过压事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA036, (char*)EVENT_VOver_1, EN_R +RS_E2PROM +44,//过压事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA037, (char*)EVENT_VOver_1, EN_R +RS_E2PROM +44,//过压事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA038, (char*)EVENT_VOver_1, EN_R +RS_E2PROM +44,//过压事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA039, (char*)EVENT_VOver_1, EN_R +RS_E2PROM +44,//过压事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组

		//0xA040,		(char*)EVENT_OverLoad_1,	EN_R +RS_E2PROM +44, //affair records of overpower mmHHDDMMYYmmHHDDMMYYzz flashback 4 groups
		0xA040, (char*)EVENT_OverLoad_1, EN_R +RS_E2PROM +44,//超功率事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA041, (char*)EVENT_OverLoad_1, EN_R +RS_E2PROM +44,//超功率事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA042, (char*)EVENT_OverLoad_1, EN_R +RS_E2PROM +44,//超功率事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA043, (char*)EVENT_OverLoad_1, EN_R +RS_E2PROM +44,//超功率事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA044, (char*)EVENT_OverLoad_1, EN_R +RS_E2PROM +44,//超功率事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA045, (char*)EVENT_OverLoad_1, EN_R +RS_E2PROM +44,//超功率事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA046, (char*)EVENT_OverLoad_1, EN_R +RS_E2PROM +44,//超功率事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA047, (char*)EVENT_OverLoad_1, EN_R +RS_E2PROM +44,//超功率事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA048, (char*)EVENT_OverLoad_1, EN_R +RS_E2PROM +44,//超功率事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA049, (char*)EVENT_OverLoad_1, EN_R +RS_E2PROM +44,//超功率事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组

		//0xA050,		(char*)EVENT_LowPF_1,	EN_R +RS_E2PROM +44, //affair records of low power factor mmHHDDMMYYmmHHDDMMYYzz flashback 4 groups
		0xA050, (char*)EVENT_LowPF_1, EN_R +RS_E2PROM +44,//低功率因数事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA051, (char*)EVENT_LowPF_1, EN_R +RS_E2PROM +44,//低功率因数事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA052, (char*)EVENT_LowPF_1, EN_R +RS_E2PROM +44,//低功率因数事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA053, (char*)EVENT_LowPF_1, EN_R +RS_E2PROM +44,//低功率因数事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA054, (char*)EVENT_LowPF_1, EN_R +RS_E2PROM +44,//低功率因数事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA055, (char*)EVENT_LowPF_1, EN_R +RS_E2PROM +44,//低功率因数事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA056, (char*)EVENT_LowPF_1, EN_R +RS_E2PROM +44,//低功率因数事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA057, (char*)EVENT_LowPF_1, EN_R +RS_E2PROM +44,//低功率因数事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA058, (char*)EVENT_LowPF_1, EN_R +RS_E2PROM +44,//低功率因数事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA059, (char*)EVENT_LowPF_1, EN_R +RS_E2PROM +44,//低功率因数事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组

		//0xA060,		(char*)EVENT_IUnder_1,	EN_R +RS_E2PROM +44, //affair records of defluidization mmHHDDMMYYmmHHDDMMYYzz flashback 4 groups
		0xA060, (char*)EVENT_IUnder_1, EN_R +RS_E2PROM +44,//失流事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA061, (char*)EVENT_IUnder_1, EN_R +RS_E2PROM +44,//失流事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA062, (char*)EVENT_IUnder_1, EN_R +RS_E2PROM +44,//失流事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA063, (char*)EVENT_IUnder_1, EN_R +RS_E2PROM +44,//失流事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA064, (char*)EVENT_IUnder_1, EN_R +RS_E2PROM +44,//失流事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA065, (char*)EVENT_IUnder_1, EN_R +RS_E2PROM +44,//失流事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA066, (char*)EVENT_IUnder_1, EN_R +RS_E2PROM +44,//失流事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA067, (char*)EVENT_IUnder_1, EN_R +RS_E2PROM +44,//失流事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA068, (char*)EVENT_IUnder_1, EN_R +RS_E2PROM +44,//失流事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
		0xA069, (char*)EVENT_IUnder_1, EN_R +RS_E2PROM +44,//失流事件记录 mmHHDDMMYYmmHHDDMMYYzz 倒序 4组
#endif
		//0xA070,     (char*)CTPTCHANGE1,     EN_R +RS_E2PROM +29, //the latest record of CT PT change mmHHDDMMYY PT1 PT2 CT1 CT2 Pp Pn Rp Rn
		0xA070, (char*) CTPTCHANGE1,
		EN_R + RS_E2PROM + 29, //最近一次换CT PT记录 mmHHDDMMYY PT1 PT2 CT1 CT2 Pp Pn Rp Rn
		//0xA071,     (char*)CTPTCHANGE2,     EN_R +RS_E2PROM +29, //the latest two records of CT PT change flashback BCD
		0xA071, (char*) CTPTCHANGE2,
		EN_R + RS_E2PROM + 29, //最近二次换CT PT记录 倒序 BCD

#ifdef SINGLE_PHASE_MULTI_TARIFF
		0xA080,
		(char*) PARA_PTCT, //PT1 PT2 CT1 CT2 flashback BCD
		EN_WR + RS_E2PROM + 8, //PT1 PT2 CT1 CT2 倒序 BCD
		0xA081, (char*) PARA_PTCT + 8, //PCT PT CT flashback (floating number four dots) BCD
		EN_R + RS_E2PROM + 12, //
#else

				//0xA080,     (char*)PARA_PTCT,       EN_WR +RS_FRAM +8,   //PT1 PT2 CT1 CT2 flashback BCD
				0xA080,
				(char*) PARA_PTCT,
				EN_WR + RS_FRAM + 8,//PT1 PT2 CT1 CT2 倒序 BCD
				//0xA081,     (char*)PARA_PTCT+8,     EN_R +RS_FRAM +12,   //PCT PT CT flashback (floating number four dots) BCD
				0xA081,
				(char*) PARA_PTCT + 8,
				EN_R + RS_FRAM + 12,//PCT PT CT 倒序 (浮点数4字节的)BCD
#endif

		0xA090, (char*) EVENT_MDF_TIME_DATA,
		EN_R + RS_E2PROM + 23 + 14, 0xA091, (char*) EVENT_MDF_TIME_COUNT,
		EN_R + RS_E2PROM + 2,
		//0xE310,	    (char*)EVENT_RST_CLR_COUNT,	  EN_WR +RS_E2PROM +2,//reset times
		0xE310, (char*) EVENT_RST_CLR_COUNT,
		EN_WR + RS_E2PROM + 2, //复位次数
		//0xE309,     (char*) (EVENT_RST_CLR_DATA), EN_WR +RS_E2PROM +52,//reset time
		0xE309, (char*) (EVENT_RST_CLR_DATA),
		EN_WR + RS_E2PROM + 52,		//复位时间

		0xD201, (char*) (BILLYMDHms),
		EN_WR + RS_FRAM + 6,

#if 0    
		//6
		//0xB000,     (char*)&gsAttRealVal.IRMS_Real[0][0],    EN_R +RS_RAM +15,	//voltage current
		0xB000, (char*)&gsAttRealVal.IRMS_Real[0][0], EN_R +RS_RAM +15,//电压 电流
		//0xB001,     (char*)&gsAttRealVal.Power_Real[0][0],   EN_R +RS_RAM +27,	//split-phase active power reactive power apparent power
		0xB001, (char*)&gsAttRealVal.Power_Real[0][0], EN_R +RS_RAM +27,//分相的有功功率 无功功率 视在功率
		//0xB002,     (char*)&gsAttRealVal.PF[0][0],           EN_R +RS_RAM +6,	//split-phase power factor
		0xB002, (char*)&gsAttRealVal.PF[0][0], EN_R +RS_RAM +6,//分相功率因数
		//0xB003,     (char*)&P53.PowerALL[0][0],     EN_R +RS_RAM +11,	//total active power total apparent power total reactive power  power factor
		0xB003, (char*)&P53.PowerALL[0][0], EN_R +RS_RAM +11,//总有功功率 总视在功率 总无功功率 功率因数
		//0xB004,     (char*)&P53.P_Angel[0][0],      EN_R +RS_RAM +10,	//A power angle B power angle C power angle BA included angle CA included angle
		0xB004, (char*)&P53.P_Angel[0][0], EN_R +RS_RAM +10,//A功率角B功率角C功率角BA夹角CA夹角
		//0XB005,     (char*)&Freq[0],                EN_R +RS_RAM +2,    //frequency
		0XB005, (char*)&Freq[0], EN_R +RS_RAM +2,//频率
#endif   

#ifdef SINGLE_PHASE_MULTI_TARIFF
		// 11
		//gsAttPara.Mode[1]
		//0xC000, 	(char*)&gsAttRealVal.DIR_Flag,	EN_R +RS_RAM +2,	//time
		0xC000, (char*) &rn8209a_rms.DIR_Flag,
		EN_R + RS_RAM + 2, //
		//0xC001, 	(char*)&Clk.Sec[0],		EN_WR +RS_RAM +7,	//time
		0xC001, (char*) &Clk.Sec[0],
		EN_WR + RS_RAM + 7, //
		//0xC100,		(char*)DeviceAddr,		EN_WR +RS_FRAM +32,	//device address
		0xC100, (char*) DeviceAddr,
		EN_WR + RS_E2PROM + 32, //
		//0xC101,		(char*)PassWord,		EN_WR +RS_FRAM +8,	//P3 password
		0xC101, (char*) PassWord,
		EN_WR + RS_E2PROM + 8, //
		//0xC103,		(char*)(PassWord+8),	EN_WR +RS_FRAM+8,	//P2 password
		0xC103, (char*) (PassWord + 8),
		EN_WR + RS_E2PROM + 8, //
		//0xC104,		(char*)(PassWord+16),	EN_WR +RS_FRAM+8,	//P1 password
		0xC104, (char*) (PassWord + 16),
		EN_WR + RS_E2PROM + 8, //
		0xC10B, (char*) (PassWord + 32),
		EN_WR + RS_E2PROM + 8, ////P4 password

		0xC105, (char*) NET_IP,
		EN_WR + RS_E2PROM + 4, //ip
		0xC106, (char*) NET_PORT,
		EN_WR + RS_E2PROM + 2, //port
		0xC107, (char*) NET_APN,
		EN_WR + RS_E2PROM + 16, //apn
		0xC108, (char*) NET_SEC_IP_STAR,
		EN_WR + RS_E2PROM + 4, //ip  2
		0xC102, (char*) SeqNo,
		EN_WR + RS_FRAM + 6, //EEQ

		//0xC109,     (char*)RF_FREQ,		    EN_WR +RS_FRAM +3,	//RF working frequency
		0xC109, (char*) RF_FREQ,
		EN_WR + RS_E2PROM + 3, //
		//0xC10A,		(char*)RF_PANID,		EN_WR +RS_FRAM +3,  //RF network ID
		0xC10A, (char*) RF_PANID,
		EN_WR + RS_E2PROM + 3, //

		0xC10B, (char*) PASSWORD_NEW,
		EN_WR + RS_E2PROM + 8, //P4 password
		0xC111, (char*) MD_BlockTm,
		EN_WR + RS_E2PROM + 2, //needed calculation period 1 slip frequency time BCD
		0xC600,
		(char*) Disp_ScNum, // add 0x051E
		EN_WR + RS_E2PROM + 1, //circulate displaying number
		0xC601, (char*) Disp_KeyNum,
		EN_WR + RS_E2PROM + 1, //key displaying number
		0xC602, (char*) DspInv,
		EN_WR + RS_E2PROM + 1, //circulate displaying space
		0xC610, (char*) Disp_ScTab + 0,
		EN_WR + RS_E2PROM + 32, //circulate displaying project, currently there is 16
		0xC611, (char*) Disp_ScTab + 32,
		EN_WR + RS_E2PROM + 32, //circulate displaying project, currently there is 16
		0xC612, (char*) Disp_KeyTab + 0,
		EN_WR + RS_E2PROM + 32, //key displaying project, currently there is 16
		0xC613, (char*) Disp_KeyTab + 32,
		EN_WR + RS_E2PROM + 32, //key displaying project currently there is 16

#else
		// 11
		//gsAttPara.Mode[1]
		//0xC000, 	(char*)&gsAttRealVal.DIR_Flag,	EN_R +RS_RAM +2,	//time
		0xC000, (char*) &gsAttRealVal.DIR_Flag, EN_R + RS_RAM + 2,//
		//0xC001, 	(char*)&Clk.Sec[0],		EN_WR +RS_RAM +7,	//time
		0xC001, (char*) &Clk.Sec[0], EN_WR + RS_RAM + 7,//
		//0xC100,		(char*)DeviceAddr,		EN_WR +RS_FRAM +32,	//device address
		0xC100, (char*) DeviceAddr, EN_WR + RS_FRAM + 32,//
		//0xC101,		(char*)PassWord,		EN_WR +RS_FRAM +8,	//P3 password
		0xC101, (char*) PassWord, EN_WR + RS_FRAM + 8,//
		//0xC103,		(char*)(PassWord+8),	EN_WR +RS_FRAM+8,	//P2 password
		0xC103, (char*) (PassWord + 8), EN_WR + RS_FRAM + 8,//
		//0xC104,		(char*)(PassWord+16),	EN_WR +RS_FRAM+8,	//P1 password
		0xC104, (char*) (PassWord + 16), EN_WR + RS_FRAM + 8,//

		0xC105, (char*) NET_IP, EN_WR + RS_FRAM + 4,//ip
		0xC106, (char*) NET_PORT, EN_WR + RS_FRAM + 2,//port
		0xC107, (char*) NET_APN, EN_WR + RS_FRAM + 16,//apn
		0xC108, (char*) NET_SEC_IP_STAR, EN_WR + RS_FRAM + 4,//ip  2
		0xC102, (char*) SeqNo, EN_WR + RS_FRAM + 6,//EEQ

		//0xC109,     (char*)RF_FREQ,		    EN_WR +RS_FRAM +3,	//RF working frequency
		0xC109, (char*) RF_FREQ, EN_WR + RS_FRAM + 3,//
		//0xC10A,		(char*)RF_PANID,		EN_WR +RS_FRAM +3,  //RF network ID
		0xC10A, (char*) RF_PANID, EN_WR + RS_FRAM + 3,//

		//0xC10B,     (char*)PASSWORD_NEW,    EN_WR +RS_FRAM+8,	//P4 password
		0xC10B, (char*) PASSWORD_NEW, EN_WR + RS_FRAM + 8,//

		//0xC111,		(char*)MD_BlockTm,		EN_WR +RS_FRAM +2,	//needed calculation period 1 slip frequency time BCD
		0xC111, (char*) MD_BlockTm, EN_WR + RS_FRAM + 2,//

		//0xC600,		(char*)Disp_ScNum,		EN_WR +RS_FRAM +1,	//circulate displaying number
		0xC600, (char*) Disp_ScNum, EN_WR + RS_FRAM + 1,//

		//0xC601,		(char*)Disp_KeyNum,		EN_WR +RS_FRAM +1,	//key displaying number
		0xC601, (char*) Disp_KeyNum, EN_WR + RS_FRAM + 1,//
		//0xC602,		(char*)DspInv,			EN_WR +RS_FRAM +1,	//circulate displaying space
		0xC602, (char*) DspInv, EN_WR + RS_FRAM + 1,//

		//0xC610,		(char*)Disp_ScTab+0,	EN_WR +RS_FRAM +32,	//circulate displaying project, currently there is 16
		0xC610, (char*) Disp_ScTab + 0, EN_WR + RS_FRAM + 32,//
		//0xC611,		(char*)Disp_ScTab+32,	EN_WR +RS_FRAM +32,	//circulate displaying project, currently there is 16
		0xC611, (char*) Disp_ScTab + 32, EN_WR + RS_FRAM + 32,//
		//0xC612,		(char*)Disp_KeyTab+0,	EN_WR +RS_FRAM +32,	//key displaying project, currently there is 16
		0xC612, (char*) Disp_KeyTab + 0, EN_WR + RS_FRAM + 32,//
		//0xC613,		(char*)Disp_KeyTab+32,	EN_WR +RS_FRAM +32,	//key displaying project currently there is 16
		0xC613, (char*) Disp_KeyTab + 32, EN_WR + RS_FRAM + 32,//
#endif
		//decimal places
		0xC710, (char*) EnDot,
		EN_WR + RS_E2PROM + 2,
		0XC711, (char*) SysSW,
		EN_WR + RS_E2PROM + 4,

		0XC712, (char*) &Version,
		EN_R + RS_RAM + 12,
		0xC713, (char*) _MBillDelyTM,
		EN_WR + RS_E2PROM + 2,

		0xC714, (char*) (meter_state),
		EN_R + RS_RAM + 2,
		0xC715, (char*) (&bill_rest),
		EN_R + RS_RAM + 1,

//		0XC712,
//		(char*) &Version,
//		EN_R + RS_RAM + 12,
//		0xC713,
//		(char*) _MBillDelyTM,
//		EN_WR + RS_FRAM + 2,
//
//		0xC714,
//		(char*) (meter_state),
//		EN_R + RS_RAM + 2,
//		0xC715,
//		(char*) (&bill_rest),
//		EN_R + RS_RAM + 1,
		//fee num
		0xC200, (char*) TOU_FEE_NUM,
		EN_WR + RS_E2PROM + 1,
		//Exception Day Table
		0xC201, (char*) EXPDAYSNUM,
		EN_WR + RS_E2PROM + 1, 0xC210, (char*) (EXPDAY1 + 32 * 0),
		EN_WR + RS_E2PROM + 32, 0xC211, (char*) (EXPDAY1 + 32 * 1),
		EN_WR + RS_E2PROM + 32, 0xC212, (char*) (EXPDAY1 + 32 * 2),
		EN_WR + RS_E2PROM + 32, 0xC213, (char*) (EXPDAY1 + 32 * 3),
		EN_WR + RS_E2PROM + 32, 0xC214, (char*) (EXPDAY1 + 32 * 4),
		EN_WR + RS_E2PROM + 32, 0xC215, (char*) (EXPDAY1 + 32 * 5),
		EN_WR + RS_E2PROM + 32, 0xC216, (char*) (EXPDAY1 + 32 * 6),
		EN_WR + RS_E2PROM + 32, 0xC217, (char*) (EXPDAY1 + 32 * 7),
		EN_WR + RS_E2PROM + 32, 0xC218, (char*) (EXPDAY1 + 32 * 8),
		EN_WR + RS_E2PROM + 32, 0xC219, (char*) (EXPDAY1 + 32 * 9),
		EN_WR + RS_E2PROM + 32, 0xC21A, (char*) (EXPDAY1 + 32 * 10),
		EN_WR + RS_E2PROM + 32, 0xC21B, (char*) (EXPDAY1 + 32 * 11),
		EN_WR + RS_E2PROM + 32, 0xC21C, (char*) (EXPDAY1 + 32 * 12),
		EN_WR + RS_E2PROM + 32, 0xC21E, (char*) (EXPDAY1 + 32 * 13),
		EN_WR + RS_E2PROM + 32, 0xC21F, (char*) (EXPDAY1 + 32 * 14),
		EN_WR + RS_E2PROM + 32,

		//Season Table
		0xC202, (char*) SEASONSNUM,
		EN_WR + RS_E2PROM + 1, 0xC240, (char*) SEASON1,
		EN_WR + RS_E2PROM + 18, 0xC241, (char*) (SEASON1 + 3 * 6),
		EN_WR + RS_E2PROM + 18,
		//Week Table
		0xC203, (char*) WEEKTABSNUM,
		EN_WR + RS_E2PROM + 1, 0xC248, (char*) WEEKTAB1 + 7 * 0,
		EN_WR + RS_E2PROM + 21, 0xC249, (char*) WEEKTAB1 + 7 * 3,
		EN_WR + RS_E2PROM + 21, 0xC24A, (char*) WEEKTAB1 + 7 * 6,
		EN_WR + RS_E2PROM + 21, 0xC24B, (char*) WEEKTAB1 + 7 * 9,
		EN_WR + RS_E2PROM + 21,
		//Day Table
		0xC204, (char*) DAYTABSNUM,
		EN_WR + RS_E2PROM + 1, 0xC205, (char*) DAYTAB_SEGSNUM,
		EN_WR + RS_E2PROM + 16,

		0xC250, (char*) DAYTAB1_SEG1,
		EN_WR + RS_E2PROM + 24, 0xC251, (char*) (DAYTAB1_SEG1 + 24 * 1),
		EN_WR + RS_E2PROM + 24, 0xC254, (char*) (DAYTAB2_SEG1 + 24 * 0),
		EN_WR + RS_E2PROM + 24, 0xC255, (char*) (DAYTAB2_SEG1 + 24 * 1),
		EN_WR + RS_E2PROM + 24, 0xC258, (char*) (DAYTAB3_SEG1 + 24 * 0),
		EN_WR + RS_E2PROM + 24, 0xC259, (char*) (DAYTAB3_SEG1 + 24 * 1),
		EN_WR + RS_E2PROM + 24, 0xC25c, (char*) (DAYTAB4_SEG1 + 24 * 0),
		EN_WR + RS_E2PROM + 24, 0xC25d, (char*) (DAYTAB4_SEG1 + 24 * 1),
		EN_WR + RS_E2PROM + 24, 0xC260, (char*) (DAYTAB5_SEG1 + 24 * 0),
		EN_WR + RS_E2PROM + 24, 0xC261, (char*) (DAYTAB5_SEG1 + 24 * 1),
		EN_WR + RS_E2PROM + 24, 0xC264, (char*) (DAYTAB6_SEG1 + 24 * 0),
		EN_WR + RS_E2PROM + 24, 0xC265, (char*) (DAYTAB6_SEG1 + 24 * 1),
		EN_WR + RS_E2PROM + 24, 0xC268, (char*) (DAYTAB7_SEG1 + 24 * 0),
		EN_WR + RS_E2PROM + 24, 0xC269, (char*) (DAYTAB7_SEG1 + 24 * 1),
		EN_WR + RS_E2PROM + 24, 0xC270, (char*) 0,
		EN_WR + RS_E2PROM + 48, 0xC271, (char*) 32,
		EN_WR + RS_E2PROM + 32,

		/*
		 0xE0E0,		(char*)DAYTAB1_SEGSNUM,	EN_WR +RS_E2PROM +1,
		 0xE0E1,		(char*)DAYTAB2_SEGSNUM,	EN_WR +RS_E2PROM +1,
		 0xE0E2,		(char*)DAYTAB3_SEGSNUM,	EN_WR +RS_E2PROM +1,
		 0xE0E3,		(char*)DAYTAB4_SEGSNUM,	EN_WR +RS_E2PROM +1,
		 0xE0E4,		(char*)DAYTAB5_SEGSNUM,	EN_WR +RS_E2PROM +1,
		 0xE0E5,		(char*)DAYTAB6_SEGSNUM,	EN_WR +RS_E2PROM +1,
		 0xE0E6,		(char*)DAYTAB7_SEGSNUM,	EN_WR +RS_E2PROM +1,
		 0xE0E7,		(char*)DAYTAB8_SEGSNUM,	EN_WR +RS_E2PROM +1,
		 */

		0xD310, (char*) LOAD_DATE_C_COUNT,
		EN_R + RS_FRAM + 2, 0xD311, (char*) LOAD_DATE_R_COUNT,
		EN_R + RS_FRAM + 2, 0xD313, (char*) LOAD_DATE_SET_COUNT,
		EN_R + RS_FRAM + 4,

		0xD314, (char*) LOAD_DATE_DATA,
		EN_R + RS_FRAM + 40, 0xD315, (char*) LOAD_DATE_DATA + 40,
		EN_R + RS_FRAM + 40, 0xD316, (char*) LOAD_DATE_DATA + 80,
		EN_R + RS_FRAM + 40, 0xD317, (char*) LOAD_DATE_DATA + 120,
		EN_R + RS_FRAM + 40, 0xD318, (char*) LOAD_DATE_DATA + 160,
		EN_R + RS_FRAM + 40, 0xD319, (char*) LOAD_DATE_DATA + 200,
		EN_R + RS_FRAM + 40, 0xD31A, (char*) LOAD_DATE_DATA + 240,
		EN_R + RS_FRAM + 40, 0xD31B, (char*) LOAD_DATE_DATA + 280,
		EN_R + RS_FRAM + 40,

#ifdef SINGLE_PHASE_MULTI_TARIFF
		//settlement date
		0xE100, (char*) BillingDate,
		EN_WR + RS_E2PROM + 1,		//0:Auto MonL <=28:Auto Date >28:Manual
		0xE108, (char*) BillingDate2,
		EN_WR + RS_E2PROM + 1,		//0:Auto MonL <=28:Auto Date >28:Manual
		0xE109, (char*) BillingDate3,
		EN_WR + RS_E2PROM + 1,		//0:Auto MonL <=28:Auto Date >28:Manual

#else
		//settlement date
		0xE100,
		(char*) BillingDate,
		EN_WR + RS_FRAM + 1,//0:Auto MonL <=28:Auto Date >28:Manual
		0xE108,
		(char*) BillingDate2,
		EN_WR + RS_FRAM + 1,//0:Auto MonL <=28:Auto Date >28:Manual
		0xE109,
		(char*) BillingDate3,
		EN_WR + RS_FRAM + 1,//0:Auto MonL <=28:Auto Date >28:Manual
#endif

		//port define
		0xE101, (char*) PortDefine,
		EN_WR + RS_FRAM + 1,
		//active power calculation form
		0xE102, (char*) kWCumuMode,
		EN_WR + RS_FRAM + 1,
		//reactive power calculation form
		0xE103, (char*) kvarCumuMode,
		EN_WR + RS_FRAM + 1,
		//power accumulation form
		0xE104, (char*) PowerCumu,
		EN_WR + RS_FRAM + 1,
		//delay after turning off power hour display turned off
		0xE105, (char*) ShutDispTm,
		EN_WR + RS_FRAM + 1,
		//time correction factor
		//时间修正因子 HEX
		0xE106, (char*) CLK_GENE,
		EN_WR + RS_FRAM + 4,
		//trun off display if off-power or not
		0xE107, (char*) PowerDnDisp_,
		EN_WR + RS_FRAM + 1,

#ifdef HARDWARE_TWO
		//user defined calculation module of register
		0xE10A, (char*)USER_DEFINE, EN_WR +RS_FRAM +6,
#endif

		//event records
		//事件记录
		0xE200, (char*) EVENT_POFF_1,
		EN_R + RS_E2PROM + 50, 0xE201, (char*) EVENT_PON_1,
		EN_R + RS_E2PROM + 50, 0xE202, (char*) EVENT_PROG_1,
		EN_R + RS_E2PROM + 50, 0xE203, (char*) EVENT_COVOP_1,
		EN_R + RS_E2PROM + 50, 0xE204, (char*) EVENT_COVCL_1,
		EN_R + RS_E2PROM + 50,
		//0xE300,		(char*)EVENT_POFF_TIMES,EN_R +RS_E2PROM +2,
		0xE300, (char*) EVENT_PON_TIMES,
		EN_R + RS_FRAM + 2, 0xE301, (char*) EVENT_PON_TIMES,
		EN_R + RS_FRAM + 2, 0xE302, (char*) EVENT_PROG_TIMES,
		EN_R + RS_FRAM + 2, 0xE303, (char*) EVENT_PROG_PTR,
		EN_R + RS_FRAM + 1, 0xE304, (char*) (EVENT_PROG_PTR + 1),
		EN_R + RS_FRAM + 50, 0xE305, (char*) EVENT_POFF_PTR,
		EN_R + RS_FRAM + 1, 0xE306, (char*) (EVENT_POFF_PTR + 1),
		EN_R + RS_FRAM + 50, 0xE307, (char*) EVENT_PON_PTR,
		EN_R + RS_FRAM + 1, 0xE308, (char*) (EVENT_PON_PTR + 1),
		EN_R + RS_FRAM + 50,
		//	0xE303,		(char*)EVENT_COVOP_TIMES,	EN_R +RS_E2PROM +1,
		//	0xE304,		(char*)EVENT_COVCL_TIMES,	EN_R +RS_E2PROM +1,
		//	0xE205,		(char*)EVENT_MAGIC_1,	EN_R +RS_E2PROM +50,
		/*
		 0xE210,		(char*)EVENT_POFF_1,	EN_R +RS_E2PROM +50,
		 0xE211,		(char*)EVENT_PON_1,	    EN_R +RS_E2PROM +50,
		 0xE212,		(char*)EVENT_PROG_1,    EN_R +RS_E2PROM +50,
		 0xE213,		(char*)EVENT_COVOP_1,   EN_R +RS_E2PROM +50,
		 0xE214,		(char*)EVENT_COVCL_1,   EN_R +RS_E2PROM +50,
		 0xE215,		(char*)EVENT_MAGIC_1,	EN_R +RS_E2PROM +50,

		 0xE220,		(char*)EVENT_POFF_1,    EN_R +RS_E2PROM +50,
		 0xE221,		(char*)EVENT_PON_1,	    EN_R +RS_E2PROM +50,
		 0xE222,		(char*)EVENT_PROG_1,    EN_R +RS_E2PROM +50,
		 0xE223,		(char*)EVENT_COVOP_1,   EN_R +RS_E2PROM +50,
		 0xE224,		(char*)EVENT_COVCL_1,   EN_R +RS_E2PROM +50,
		 0xE225,		(char*)EVENT_MAGIC_1,	EN_R +RS_E2PROM +50,

		 0xE230,		(char*)EVENT_POFF_1,    EN_R +RS_E2PROM +50,
		 0xE231,		(char*)EVENT_PON_1,	    EN_R +RS_E2PROM +50,
		 0xE232,		(char*)EVENT_PROG_1,    EN_R +RS_E2PROM +50,
		 0xE233,		(char*)EVENT_COVOP_1,   EN_R +RS_E2PROM +50,
		 0xE234,		(char*)EVENT_COVCL_1,   EN_R +RS_E2PROM +50,
		 0xE235,		(char*)EVENT_MAGIC_1,	EN_R +RS_E2PROM +50,
		 */
#ifdef SINGLE_PHASE_MULTI_TARIFF
		0xA007,
		(char*) Dly_UnbV,		//new event record delay 1-60 seconds
		EN_WR + RS_E2PROM + 2,		//
#else
				//0xA007,		(char*)Dly_UnbV,	EN_WR+RS_FRAM+2,	//new event record delay 1-60 seconds
				0xA007,
				(char*) Dly_UnbV,
				EN_WR + RS_FRAM + 2,//新事件记录延时1~60秒
#endif
		//0xE401,		(char*)NEV_CURRFX_CNT,	EN_R +RS_FRAM +2,//reverse times
		0xE401, (char*) NEV_CURRFX_CNT,
		EN_R + RS_FRAM + 2, //反向次数
		//0xE402,		(char*)NEV_CURRFX_CRD,	EN_R +RS_FRAM +50,//reverse records
		0xE402, (char*) NEV_CURRFX_CRD,
		EN_R + RS_FRAM + 50,		//反向记录

		//0xE403,		(char*)NEV_LOSTU_CNT,	EN_R +RS_FRAM +2,//reverse times
		0xE403, (char*) NEV_LOSTU_CNT,
		EN_R + RS_FRAM + 2,		//反向次数
		//0xE404,		(char*)NEV_LOSTU_CRD,	EN_R +RS_FRAM +50,//reverse records
		0xE404, (char*) NEV_LOSTU_CRD,
		EN_R + RS_FRAM + 50,		//反向记录

		//0xE405,		(char*)NEV_OVERU_CNT,	EN_R +RS_FRAM +2,//reverse times
		0xE405, (char*) NEV_OVERU_CNT,
		EN_R + RS_FRAM + 2,		//反向次数
		//0xE406,		(char*)NEV_OVERU_CRD,	EN_R +RS_FRAM +50,//reverse records
		0xE406, (char*) NEV_OVERU_CRD,
		EN_R + RS_FRAM + 50,		//反向记录

		//0xE407,		(char*)NEV_HDERR_CNT,	EN_R +RS_FRAM +2,//reverse times
		0xE407, (char*) NEV_HDERR_CNT,
		EN_R + RS_FRAM + 2,		//反向次数
		//0xE408,		(char*)NEV_HDERR_CRD,	EN_R +RS_FRAM +50,//reverse records
		0xE408, (char*) NEV_HDERR_CRD,
		EN_R + RS_FRAM + 50,		//反向记录

		//0xE409,		(char*)NEV_XXERR_CNT,	EN_R +RS_FRAM +2,//reverse times
		0xE409, (char*) NEV_XXERR_CNT,
		EN_R + RS_FRAM + 2,		//反向次数
		//0xE40A,		(char*)NEV_XXERR_CRD,	EN_R +RS_FRAM +50,//reverse records
		0xE40A, (char*) NEV_XXERR_CRD,
		EN_R + RS_FRAM + 50,		//反向记录

		//0xE40B,		(char*)NEV_BARERR_CNT,	EN_R +RS_FRAM +2,//revrese times
		0xE40B, (char*) NEV_BARERR_CNT,
		EN_R + RS_FRAM + 2,		//反向次数
		//0xE40C,		(char*)NEV_BARERR_CRD,	EN_R +RS_FRAM +50,//reverse records
		0xE40C, (char*) NEV_BARERR_CRD,
		EN_R + RS_FRAM + 50,		//反向记录

		//0xE40F,		(char*)NEV_OVERI_CNT,	EN_R +RS_FRAM +2,//overcurrent times
		0xE40F, (char*) NEV_OVERI_CNT,
		EN_R + RS_FRAM + 2,		//过流次数
		//0XE410,     (char*)NEV_OVERI_CRD,	EN_R +RS_FRAM +50,//overcurrent records
		0XE410, (char*) NEV_OVERI_CRD,
		EN_R + RS_FRAM + 50,		//过流记录

		//0xE40D,		(char*)NEV_LOSTU_VAL,	EN_R +RS_FRAM +60,//loss of voltage value
		0xE40D, (char*) NEV_LOSTU_VAL,
		EN_R + RS_FRAM + 60,		//失压值
		//0xE40E,		(char*)NEV_OVERU_VAL,	EN_R +RS_FRAM +60,//overvoltage value
		0xE40E, (char*) NEV_OVERU_VAL,
		EN_R + RS_FRAM + 60,		//过压值
		//0XE411,     (char*)NEV_OVERI_VAL,	EN_R +RS_FRAM +60,//overcurrent value
		0XE411, (char*) NEV_OVERI_VAL,
		EN_R + RS_FRAM + 60,		//过流值
		//total zero cleariing
		//OxFOEE,------do not delet this annotation
		//power quantity calculation (including needed quantity)
		//0xF0F1,   -----do not delet this annotation
		//needed quantity calculation
		//0xF0F2,   -----do not delet this annotation

		//current power quantity/needed quantity power quantity of last month/needed quantity power quantity of last two months/needed quantity
		0x9010, (char*) (EC_Pp0),
		EN_R + RS_FRAM + 5, 0x9011, (char*) (EC_Pp1),
		EN_R + RS_FRAM + 5, 0x9012, (char*) (EC_Pp2),
		EN_R + RS_FRAM + 5, 0x9013, (char*) (EC_Pp3),
		EN_R + RS_FRAM + 5, 0x9014, (char*) (EC_Pp4),
		EN_R + RS_FRAM + 5,

		0x9020, (char*) (EC_Pn0),
		EN_R + RS_FRAM + 5, 0x9021, (char*) (EC_Pn1),
		EN_R + RS_FRAM + 5, 0x9022, (char*) (EC_Pn2),
		EN_R + RS_FRAM + 5, 0x9023, (char*) (EC_Pn3),
		EN_R + RS_FRAM + 5, 0x9024, (char*) (EC_Pn4),
		EN_R + RS_FRAM + 5,

		0x9030, (char*) (EC_Rp0),
		EN_R + RS_FRAM + 5, 0x9031, (char*) (EC_Rp1),
		EN_R + RS_FRAM + 5, 0x9032, (char*) (EC_Rp2),
		EN_R + RS_FRAM + 5, 0x9033, (char*) (EC_Rp3),
		EN_R + RS_FRAM + 5, 0x9034, (char*) (EC_Rp4),
		EN_R + RS_FRAM + 5,

		0x9040, (char*) (EC_Rn0),
		EN_R + RS_FRAM + 5, 0x9041, (char*) (EC_Rn1),
		EN_R + RS_FRAM + 5, 0x9042, (char*) (EC_Rn2),
		EN_R + RS_FRAM + 5, 0x9043, (char*) (EC_Rn3),
		EN_R + RS_FRAM + 5, 0x9044, (char*) (EC_Rn4),
		EN_R + RS_FRAM + 5,

#ifdef HARDWARE_TWO
		//forward apparent
		//正向视在
		0x9050, (char*)(EC_Qp0), EN_R +RS_FRAM +5,
		0x9051, (char*)(EC_Qp1), EN_R +RS_FRAM +5,
		0x9052, (char*)(EC_Qp2), EN_R +RS_FRAM +5,
		0x9053, (char*)(EC_QP3), EN_R +RS_FRAM +5,
		0x9054, (char*)(EC_Qp4), EN_R +RS_FRAM +5,
		//reverse apparent
		//反向视在
		0x9060, (char*)(EC_Qn0), EN_R +RS_FRAM +5,
		0x9061, (char*)(EC_Qn1), EN_R +RS_FRAM +5,
		0x9062, (char*)(EC_Qn2), EN_R +RS_FRAM +5,
		0x9063, (char*)(EC_Qn3), EN_R +RS_FRAM +5,
		0x9064, (char*)(EC_Qn4), EN_R +RS_FRAM +5,

		//0x9130,	    (char*)EC_Rq1,	    EN_R +RS_FRAM +5,//reactive first total quadrant
		0x9130, (char*)EC_Rq1, EN_R +RS_FRAM +5,//无功一象限总
		//0x9131,     (char*)EC_Rq1F1,        EN_R +RS_FRAM +5,//reactive first quadrant tariff 1
		0x9131, (char*)EC_Rq1F1, EN_R +RS_FRAM +5,//无功一象限费率1
		//0x9132,     (char*)EC_Rq1F2,        EN_R +RS_FRAM +5,//reactive first quadrant tariff 2
		0x9132, (char*)EC_Rq1F2, EN_R +RS_FRAM +5,//无功一象限费率2
		//0x9133,     (char*)EC_Rq1F3,        EN_R +RS_FRAM +5,//reactive first quadrant tariff 3
		0x9133, (char*)EC_Rq1F3, EN_R +RS_FRAM +5,//无功一象限费率3
		//0x9134,     (char*)EC_Rq1F4,        EN_R +RS_FRAM +5,//reactive first quadrant tariff 4
		0x9134, (char*)EC_Rq1F4, EN_R +RS_FRAM +5,//无功一象限费率4

		//0x9150,	    (char*)EC_Rq2,	    EN_R +RS_FRAM +5,//reactive second total quadrants
		0x9150, (char*)EC_Rq2, EN_R +RS_FRAM +5,//无功二象限总
		//0x9151,     (char*)EC_Rq2F1,        EN_R +RS_FRAM +5,//reactive second quadrant tariff 1
		0x9151, (char*)EC_Rq2F1, EN_R +RS_FRAM +5,//无功二象限费率1
		//0x9152,     (char*)EC_Rq2F2,        EN_R +RS_FRAM +5,//reactive second quadrant tariff 2
		0x9152, (char*)EC_Rq2F2, EN_R +RS_FRAM +5,//无功二象限费率2
		//0x9153,     (char*)EC_Rq2F3,        EN_R +RS_FRAM +5,//reactive second quadrant tariff 3
		0x9153, (char*)EC_Rq2F3, EN_R +RS_FRAM +5,//无功二象限费率3
		//0x9154,     (char*)EC_Rq2F4,        EN_R +RS_FRAM +5,//reactive second quadrant tariff 4
		0x9154, (char*)EC_Rq2F4, EN_R +RS_FRAM +5,//无功二象限费率4

		//0x9160,	    (char*)EC_Rq3,	    EN_R +RS_FRAM +5,//reactive third total quadrant
		0x9160, (char*)EC_Rq3, EN_R +RS_FRAM +5,//无功三象限总
		//0x9161,     (char*)EC_Rq3F1,        EN_R +RS_FRAM +5,//reactive third quadrant tariff 1
		0x9161, (char*)EC_Rq3F1, EN_R +RS_FRAM +5,//无功三象限费率1
		//0x9162,     (char*)EC_Rq3F2,        EN_R +RS_FRAM +5,//reactive third quadrant tariff 2
		0x9162, (char*)EC_Rq3F2, EN_R +RS_FRAM +5,//无功三象限费率2
		//0x9163,     (char*)EC_Rq3F3,        EN_R +RS_FRAM +5,//reactive third quadrant tariff 3
		0x9163, (char*)EC_Rq3F3, EN_R +RS_FRAM +5,//无功三象限费率3
		//0x9164,     (char*)EC_Rq3F4,        EN_R +RS_FRAM +5,//reactive third quadrant tariff 4
		0x9164, (char*)EC_Rq3F4, EN_R +RS_FRAM +5,//无功三象限费率4

		//0x9140,	    (char*)EC_Rq4,	        EN_R +RS_FRAM +5,//reactive total four quadrants
		0x9140, (char*)EC_Rq4, EN_R +RS_FRAM +5,//无功四象限总
		//0x9141,     (char*)EC_Rq4F1,        EN_R +RS_FRAM +5,//reactive forth quadrant tariff 1
		0x9141, (char*)EC_Rq4F1, EN_R +RS_FRAM +5,//无功四象限费率1
		//0x9142,     (char*)EC_Rq4F2,        EN_R +RS_FRAM +5,//reactive forth quadrant tariff 2
		0x9142, (char*)EC_Rq4F2, EN_R +RS_FRAM +5,//无功四象限费率2
		//0x9143,     (char*)EC_Rq4F3,        EN_R +RS_FRAM +5,//reactive forth quadrant tariff 3
		0x9143, (char*)EC_Rq4F3, EN_R +RS_FRAM +5,//无功四象限费率3
		//0x9144,     (char*)EC_Rq4F4,        EN_R +RS_FRAM +5,//reactive forth quadrant tariff 4
		0x9144, (char*)EC_Rq4F4, EN_R +RS_FRAM +5,//无功四象限费率4

		//0x9210,     (char*)UserdeBCD[0],    EN_R +RS_RAM +6,//user defined register 0
		0x9210, (char*)UserdeBCD[0], EN_R +RS_RAM +6,//用户自定义寄存器0
		//0x9211,     (char*)UserdeBCD[1],    EN_R +RS_RAM +6,//user defined register 1
		0x9211, (char*)UserdeBCD[1], EN_R +RS_RAM +6,//用户自定义寄存器1
		//0x9212,     (char*)UserdeBCD[2],    EN_R +RS_RAM +6,//user defined register 2
		0x9212, (char*)UserdeBCD[2], EN_R +RS_RAM +6,//用户自定义寄存器2

#endif

#if 0
		//unecessary for every quadrant of split-phase , when tested it will be sheilded
		//分相各象限不需要，到时测试后屏蔽掉
		//0x9171,     (char*)EC_Rq1L1,        EN_R +RS_FRAM +5,//A phase first quadrant
		0x9171, (char*)EC_Rq1L1, EN_R +RS_FRAM +5,//A相一象限
		//0x9172,     (char*)EC_Rq2L1,        EN_R +RS_FRAM +5,//A phase second quadrant
		0x9172, (char*)EC_Rq2L1, EN_R +RS_FRAM +5,//A相二象限
		//0x9173,     (char*)EC_Rq3L1,        EN_R +RS_FRAM +5,//A phase third quadrant
		0x9173, (char*)EC_Rq3L1, EN_R +RS_FRAM +5,//A相三象限
		//0x9174,     (char*)EC_Rq4L1,        EN_R +RS_FRAM +5,//A phase forth quadrant
		0x9174, (char*)EC_Rq4L1, EN_R +RS_FRAM +5,//A相四象限

		//0x9181,     (char*)EC_Rq1L2,        EN_R +RS_FRAM +5,//B phase first quadrant
		0x9181, (char*)EC_Rq1L2, EN_R +RS_FRAM +5,//B相一象限
		//0x9182,     (char*)EC_Rq2L2,        EN_R +RS_FRAM +5,//B phase second quadrant
		0x9182, (char*)EC_Rq2L2, EN_R +RS_FRAM +5,//B相二象限
		//0x9183,     (char*)EC_Rq3L2,        EN_R +RS_FRAM +5,//B phase third quadrant
		0x9183, (char*)EC_Rq3L2, EN_R +RS_FRAM +5,//B相三象限
		//0x9184,     (char*)EC_Rq4L2,        EN_R +RS_FRAM +5,//B phase forth quadrant
		0x9184, (char*)EC_Rq4L2, EN_R +RS_FRAM +5,//B相四象限

		//0x9191,     (char*)EC_Rq1L3,        EN_R +RS_FRAM +5,//C phase first quadrant
		0x9191, (char*)EC_Rq1L3, EN_R +RS_FRAM +5,//C相一象限
		//0x9192,     (char*)EC_Rq2L3,        EN_R +RS_FRAM +5,//C phase second quadrant
		0x9192, (char*)EC_Rq2L3, EN_R +RS_FRAM +5,//C相二象限
		//0x9193,     (char*)EC_Rq3L3,        EN_R +RS_FRAM +5,//C phase third quadrant
		0x9193, (char*)EC_Rq3L3, EN_R +RS_FRAM +5,//C相三象限
		//0x9194,     (char*)EC_Rq4L3,        EN_R +RS_FRAM +5,//C phase forth quadrant
		0x9194, (char*)EC_Rq4L3, EN_R +RS_FRAM +5,//C相四象限
#endif

#if 0
		0x9000, (char*)EC_Pp0, EN_R +RS_FRAM +25,
		0x9010, (char*)EC_Pn0, EN_R +RS_FRAM +25,
		0x9020, (char*)EC_Rp0, EN_R +RS_FRAM +25,
		0x9030, (char*)EC_Rn0, EN_R +RS_FRAM +25,
		0x9040, (char*)EC_Qp0, EN_R +RS_FRAM +25,
		0x9050, (char*)EC_Qn0, EN_R +RS_FRAM +25,

		0x9060, (char*)EC_PpL1, EN_R +RS_FRAM +15,
		0x9070, (char*)EC_PnL1, EN_R +RS_FRAM +15,
		0x9080, (char*)EC_RpL1, EN_R +RS_FRAM +15,
		0x9090, (char*)EC_RnL1, EN_R +RS_FRAM +15,
		0x90A0, (char*)EC_QpL1, EN_R +RS_FRAM +15,
		0x90B0, (char*)EC_QnL1, EN_R +RS_FRAM +15,

		0x00C0, (char*)EC_Rq1, EN_R +RS_FRAM +20,
		0x00D0, (char*)EC_Rq2, EN_R +RS_FRAM +20,
		0x00E0, (char*)EC_Rq3, EN_R +RS_FRAM +20,
		0x00F0, (char*)EC_Rq4, EN_R +RS_FRAM +20,

		0x0100, (char*)EC_Rq1F1, EN_R +RS_FRAM +20,
		0x0110, (char*)EC_Rq2F1, EN_R +RS_FRAM +20,
		0x0120, (char*)EC_Rq3F1, EN_R +RS_FRAM +20,
		0x0130, (char*)EC_Rq4F1, EN_R +RS_FRAM +20,
#endif

		0x3000, (char*) MD_Pp, EN_R + RS_FRAM + 8, 0x3001, (char*) (MD_Pp + 8),
		EN_R + RS_FRAM + 8, 0x3002, (char*) (MD_Pp + 8 + 8),
		EN_R + RS_FRAM + 8, 0x3003, (char*) (MD_Pp + 8 + 8 + 8), EN_R + RS_FRAM
				+ 8, 0x3004, (char*) (MD_Pp + 8 + 8 + 8 + 8), EN_R + RS_FRAM
				+ 8,

		0x3010, (char*) MD_Pn, EN_R + RS_FRAM + 8, 0x3011, (char*) (MD_Pn + 8),
		EN_R + RS_FRAM + 8, 0x3012, (char*) (MD_Pn + 8 + 8),
		EN_R + RS_FRAM + 8, 0x3013, (char*) (MD_Pn + 8 + 8 + 8), EN_R + RS_FRAM
				+ 8, 0x3014, (char*) (MD_Pn + 8 + 8 + 8 + 8), EN_R + RS_FRAM
				+ 8,

		0x3020, (char*) MD_Rp, EN_R + RS_FRAM + 8, 0x3021, (char*) (MD_Rp + 8),
		EN_R + RS_FRAM + 8, 0x3022, (char*) (MD_Rp + 8 + 8),
		EN_R + RS_FRAM + 8, 0x3023, (char*) (MD_Rp + 8 + 8 + 8), EN_R + RS_FRAM
				+ 8, 0x3024, (char*) (MD_Rp + 8 + 8 + 8 + 8), EN_R + RS_FRAM
				+ 8,

		0x3030, (char*) MD_Rn, EN_R + RS_FRAM + 8, 0x3031, (char*) (MD_Rn + 8),
		EN_R + RS_FRAM + 8, 0x3032, (char*) (MD_Rn + 8 + 8),
		EN_R + RS_FRAM + 8, 0x3033, (char*) (MD_Rn + 8 + 8 + 8), EN_R + RS_FRAM
				+ 8, 0x3034, (char*) (MD_Rn + 8 + 8 + 8 + 8), EN_R + RS_FRAM
				+ 8,

		0x3040, (char*) MD_Qp, EN_R + RS_FRAM + 8, 0x3041, (char*) (MD_Qp + 8),
		EN_R + RS_FRAM + 8, 0x3042, (char*) (MD_Qp + 8 + 8),
		EN_R + RS_FRAM + 8, 0x3043, (char*) (MD_Qp + 8 + 8 + 8), EN_R + RS_FRAM
				+ 8, 0x3044, (char*) (MD_Qp + 8 + 8 + 8 + 8), EN_R + RS_FRAM
				+ 8,

		0x3050, (char*) MD_Qn, EN_R + RS_FRAM + 8, 0x3051, (char*) (MD_Qn + 8),
		EN_R + RS_FRAM + 8, 0x3052, (char*) (MD_Qn + 8 + 8),
		EN_R + RS_FRAM + 8, 0x3053, (char*) (MD_Qn + 8 + 8 + 8), EN_R + RS_FRAM
				+ 8, 0x3054, (char*) (MD_Qn + 8 + 8 + 8 + 8), EN_R + RS_FRAM
				+ 8,

		0x3060, (char*) MD_Rq1, EN_R + RS_FRAM + 8, 0x3061,
		(char*) (MD_Rq1 + 8), EN_R + RS_FRAM + 8, 0x3062, (char*) (MD_Rq1 + 8
				+ 8), EN_R + RS_FRAM + 8, 0x3063, (char*) (MD_Rq1 + 8 + 8 + 8),
		EN_R + RS_FRAM + 8, 0x3064, (char*) (MD_Rq1 + 8 + 8 + 8 + 8), EN_R
				+ RS_FRAM + 8,

		0x3070, (char*) MD_Rq2, EN_R + RS_FRAM + 8, 0x3071,
		(char*) (MD_Rq2 + 8), EN_R + RS_FRAM + 8, 0x3072, (char*) (MD_Rq2 + 8
				+ 8), EN_R + RS_FRAM + 8, 0x3073, (char*) (MD_Rq2 + 8 + 8 + 8),
		EN_R + RS_FRAM + 8, 0x3074, (char*) (MD_Rq2 + 8 + 8 + 8 + 8), EN_R
				+ RS_FRAM + 8,

		0x3080, (char*) MD_Rq3, EN_R + RS_FRAM + 8, 0x3081,
		(char*) (MD_Rq3 + 8), EN_R + RS_FRAM + 8, 0x3082, (char*) (MD_Rq3 + 8
				+ 8), EN_R + RS_FRAM + 8, 0x3083, (char*) (MD_Rq3 + 8 + 8 + 8),
		EN_R + RS_FRAM + 8, 0x3084, (char*) (MD_Rq3 + 8 + 8 + 8 + 8), EN_R
				+ RS_FRAM + 8,

		0x3090, (char*) MD_Rq4, EN_R + RS_FRAM + 8, 0x3091,
		(char*) (MD_Rq4 + 8), EN_R + RS_FRAM + 8, 0x3092, (char*) (MD_Rq4 + 8
				+ 8), EN_R + RS_FRAM + 8, 0x3093, (char*) (MD_Rq4 + 8 + 8 + 8),
		EN_R + RS_FRAM + 8, 0x3094, (char*) (MD_Rq4 + 8 + 8 + 8 + 8), EN_R
				+ RS_FRAM + 8,

		//0x300E,		(char*)AVR_MD,			        EN_R +RS_FRAM +52,//preserve current and last average power
		0x300E, (char*) AVR_MD, EN_R + RS_FRAM + 52,		//
		//0x300F,		(char*)AVR_MD,			        EN_R +RS_FRAM +26,//preserve current average power
		0x300F, (char*) AVR_MD, EN_R + RS_FRAM + 26, //
		// add by BNthang on January 1st, 2016
		0x30A0, (char*) OPEN_COVER, EN_R + RS_FRAM + 32, //munite: hour: day: month: year
		};

