//#include "..\inc\includes.h"
#include "..\inc\E2_Layout.h"// add by bnthang
//************************************************************
//check table
//校验表
const CHECKTAB ChkTab[CHK_TAB_NUM] = {

(char*) Adj_Para_GAINA0, 6,
		Chk_FRAM + Init_Clr, //GAINA0
		(char*) Adj_Para_GAINB0, 6,
		Chk_FRAM + Init_Clr, //GAINA1
		(char*) Adj_Para_GAINC0, 6,
		Chk_FRAM + Init_Clr, //GAINB0
		(char*) Adj_Para_PHASEA0, 6,
		Chk_FRAM + Init_Clr, //PHASEA0
		(char*) Adj_Para_PHASEB0, 6,
		Chk_FRAM + Init_Clr, //PHASEB1
		(char*) Adj_Para_PHASEC0, 6,
		Chk_FRAM + Init_Clr, //PHASEC0
		(char*) Adj_Para_VRAM_A, 9,
		Chk_FRAM + Init_Clr, //IRMA
		(char*) Adj_Para_IRAM_A, 9,
		Chk_FRAM + Init_Clr, //VRMSB
		(char*) Adj_Para_Iregchg, 6,
		Chk_FRAM + Init_Clr, //VRMSC
		(char*) Adj_Para_FHConst, 6,
		Chk_FRAM + Init_Clr,
		//FRAM area data 11============================================================

		//clock impulse split-phase power quantity four quadrants restain power quantity register 5

		(char*) (ClockBuf), 6,
		Chk_FRAM + Init_FRAMClk,

		(char*) (PARA_PTCT), 20,
		Chk_FRAM + Init_Clr, (char*) (Ram_Pulse), 40,
		Chk_FRAM + Comm_Clr + Init_Clr,

		//active forward reverse reactive forward reverse apparent forward reverse 6
		(char*) (EC_Pp0), 25,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (EC_Pn0), 25,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (EC_Rp0), 25,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (EC_Rn0), 25,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (EC_Qp0), 25,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (EC_Qn0), 25,
		Chk_FRAM + Comm_Clr + Init_Clr,

		//split-phase active forward reverse reactive forward reverse apparent forward reverse 6
		(char*) (EC_PpL1), 15,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (EC_PnL1), 15,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (EC_RpL1), 15,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (EC_RnL1), 15,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (EC_QpL1), 15,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (EC_QnL1), 15,
		Chk_FRAM + Comm_Clr + Init_Clr,

		//four quadrants reactive and split-phase power quantity 4
		(char*) (EC_Rq1), 20,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (EC_Rq2), 20,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (EC_Rq3), 20,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (EC_Rq4), 20,
		Chk_FRAM + Comm_Clr + Init_Clr,

		//four quadrants reactive power tariff 5
		(char*) (EC_Rq1F1), 20,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (EC_Rq2F1), 20,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (EC_Rq3F1), 20,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (EC_Rq4F1), 20,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (EC_Pp1Min), 10,
		Chk_FRAM + Comm_Clr + Init_Clr,

		//active forward reverse reactive forward reverse apparent forward reverse maximum demand and taking place time tariff 6
		(char*) (MD_Pp), 40,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (MD_Pn), 40,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (MD_Rp), 40,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (MD_Rn), 40,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (MD_Qp), 40,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (MD_Qn), 40,
		Chk_FRAM + Comm_Clr + Init_Clr,

		//reactive four quadrants maximum demand and taking place time tariff 4
		(char*) (MD_Rq1), 40,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (MD_Rq2), 40,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (MD_Rq3), 40,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (MD_Rq4), 40,
		Chk_FRAM + Comm_Clr + Init_Clr,

		//accumulated demand active forward reverse reactive forward reverse 5
		(char*) (cMD_Pp), 20,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (cMD_Pn), 20,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (cMD_Rp), 20,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (cMD_Rn), 20,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) (CUMU_Num), 8,
		Chk_FRAM + Comm_Clr + Init_Clr,

#if 0        
		//time frame
		(char*)EXPDAYS, 481, Chk_E2PROM + Init_Clr,
		(char*)SEASONS, 37, Chk_E2PROM + Init_Clr,
		(char*)WEEKTABS, 85, Chk_E2PROM + Init_Clr,
		(char*)DAYTABSNUM, 52, Chk_E2PROM + Init_Clr,
		(char*)DAYTAB2_SEGSNUM, 49, Chk_E2PROM + Init_Clr,
		(char*)DAYTAB3_SEGSNUM, 49, Chk_E2PROM + Init_Clr,
		(char*)DAYTAB4_SEGSNUM, 49, Chk_E2PROM + Init_Clr,
		(char*)DAYTAB5_SEGSNUM, 49, Chk_E2PROM + Init_Clr,
		(char*)DAYTAB6_SEGSNUM, 49, Chk_E2PROM + Init_Clr,
		(char*)DAYTAB7_SEGSNUM, 49, Chk_E2PROM + Init_Clr,
		(char*)DAYTAB8_SEGSNUM, 49, Chk_E2PROM + Init_Clr,
#endif
		//demand counting period slip frequency time 1
		(char*) (MD_Para), 2,
		Chk_FRAM + Init_Clr,
		//cycle displaying table 3
		(char*) Disp_ScTab, 65,
		Chk_FRAM + Init_Clr, (char*) Disp_KeyTab, 65,
		Chk_FRAM + Init_Clr, (char*) DspInv, 1,
		Chk_FRAM + Init_Clr,

		//meter address user number
		(char*) MeterAddr, 77,
		Chk_FRAM + Init_Clr,

		(char*) LastMonPtr, 3,
		Chk_FRAM + Comm_Clr + Init_Clr,

		//load curve parameter 14
		(char*) LPPara, 26,
		Chk_FRAM + Init_Clr, (char*) LP_CurrentD_Qp, 30,
		Chk_FRAM + Comm_Clr + Init_Clr, (char*) LP_DeltaPp, 8,
		Chk_FRAM + Comm_Clr + Init_Clr,


		(char*) Val_VFailure, 22,
		Chk_FRAM + Init_Clr,

		//(char*)Val_IUnder,       5,         Chk_FRAM + Init_Clr,
		//(char*)VFailureNumC,    60,         Chk_FRAM +Comm_Clr + Init_Clr,
		//(char*)VUnderPnAll,     13,         Chk_FRAM +Comm_Clr + Init_Clr,
		//(char*)VUnderPnA,       13,         Chk_FRAM +Comm_Clr + Init_Clr,
		//(char*)VUnderPnB,       13,         Chk_FRAM +Comm_Clr + Init_Clr,
		//(char*)VUnderPnC,       13,         Chk_FRAM +Comm_Clr + Init_Clr,
		//(char*)VUnderPnAB,      13,         Chk_FRAM +Comm_Clr + Init_Clr,
		//(char*)VUnderPnAC,      13,         Chk_FRAM +Comm_Clr + Init_Clr,
		//(char*)VUnderPnBC,      13,         Chk_FRAM +Comm_Clr + Init_Clr,
		//(char*)VUnderPnABC,     13,         Chk_FRAM +Comm_Clr + Init_Clr,

		//RAM area data 1==========================================================

		//(char*)(&Clk.Min),		 6,			Chk_RAM + Init_RAMClk,

		//EEPROM area data 3=======================================================
		(char*) CTPTCHANGE1, 29, Chk_E2PROM + Comm_Clr + Init_Clr,
		(char*) CTPTCHANGE2, 29, Chk_E2PROM + Comm_Clr + Init_Clr,
		(char*) COMM_LAST, 24, Chk_E2PROM + Comm_Clr + Init_Clr,
		//4
		(char*) (LoadInfo_), 128,
		Chk_FRAM,				//+ Init_Clr,
		(char*) (LoadInfoRun_), 48,
		Chk_FRAM + Comm_Clr,				//+ Init_Clr,
		(char*) (FuncSW), 13, Chk_E2PROM + Init_Clr, (char*) (EnDot), 2,
		Chk_E2PROM + Init_Clr, (char*) (Tst_EC_Pulse), 88, Chk_FRAM + Init_Clr,
#if 0    
		//history power quantity 4
		//历史电量4
		(char*)LM1_EC, SIZE_EC_MONBLK-2, Chk_DFlash +Comm_Clr + Init_Clr,
		(char*)LM1_MD, SIZE_MD_MONBLK-2, Chk_DFlash +Comm_Clr + Init_Clr,
		(char*)LM2_EC, SIZE_EC_MONBLK-2, Chk_DFlash +Comm_Clr + Init_Clr,
		(char*)LM2_MD, SIZE_MD_MONBLK-2, Chk_DFlash +Comm_Clr + Init_Clr,
#endif	
	};

//const char def_md_time[] ={0x05,0x04};//demand period
const char def_md_time[] = { 0x05, 0x04 };				//
//const char def_BillingDate[] = {0x01};//frozen date
const char def_BillingDate[] = { 0x01 };				//

#if METER_TYPE == 1
//const char def_SysSW[] = {0x1F,0x08,0x00,0x00};//trun on C711 system, with PTCT display, allow load curve // with PTCT display 
const char def_SysSW[] = {0x1F,0x08,0x00,0x00};	//
//const char def_Val_IOver[] = {0x00,0x12};//A001 overvoltage threshold value //overcurrent threshold value
const char def_Val_IOver[] = {0x00,0x12};				//
#endif
#if METER_TYPE == 2
//const char def_SysSW[] = {0x0F,0x08,0x00,0x00};//turn on C711 system, without PTCT display, allow load curve // without PTCT display
const char def_SysSW[] = { 0x0F, 0x08, 0x00, 0x00 };//
//const char def_Val_IOver[] = {0x00,0x20};//A001 overvolate threshold value //overcurrent threshold value//20140612 modification, 50（100) A meter, overcurrent 200.0%
const char def_Val_IOver[] = { 0x00, 0x20 };//
#endif
#if METER_TYPE == 3
//const char def_SysSW[] = {0x1F,0x08,0x00,0x00};//turn on C711 system, with PTCT display, allow load curve // with PTCT display
const char def_SysSW[] = {0x1F,0x08,0x00,0x00};	//
//const char def_Val_IOver[] = {0x00,0x12};//A001 overvoltage threshold //overcurrent threshold
const char def_Val_IOver[] = {0x00,0x12};				//
#endif
#if METER_TYPE == 4
//const char def_SysSW[] = {0x1F,0x08,0x00,0x00};//turn on C711 system, with PTCT display, allow load curve // with PTCT display
const char def_SysSW[] = {0x1F,0x08,0x00,0x00};	//
//const char def_Val_IOver[] = {0x00,0x12};//A001 overvoltage threshold //overcurrent threshold value
const char def_Val_IOver[] = {0x00,0x12};				//
#endif
#if METER_TYPE == 5
//const char def_SysSW[] = {0x0F,0x08,0x00,0x00};//turn on C711 system, without PTCT display, allow load curve // without PTCT display
const char def_SysSW[] = {0x0F,0x08,0x00,0x00};	//
//const char def_Val_IOver[] = {0x00,0x20};//A01 overvoltage threshold value //overcurrent  threshold value //20140612 modification, 50（100）A meter, overcurrent 200.0%
const char def_Val_IOver[] = {0x00,0x20};//
#endif

//turn on load curve
//负荷曲线打开
//const char def_Val_VFailure[] = {0x00,0x08};//split-phase threshold value
const char def_Val_VFailure[] = { 0x00, 0x08 };				//
//const char def_Val_VOver[] = {0x00,0x12};//A000 overvoltage threshold value
const char def_Val_VOver[] = { 0x00, 0x12 };				//
//const char def_Val_Newdly[] = {0x10,0x00};//new event delay time
const char def_Val_Newdly[] = { 0x10, 0x00 };				//
//const char def_Val_UnBalance[] = {0x00,0x08};//A006 three-phase unbalanced threshold value Val-UnbV
const char def_Val_UnBalance[] = { 0x00, 0x08 };	//
//const char def_Val_Dot[] = {0x02,0x00};//C710 decimal places
const char def_Val_Dot[] = { 0x02, 0x00 };				//
//const char def_Val_PTCT[] = {0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00};//PTCT specific value
const char def_Val_PTCT[] = { 0x01, 0x00, 0x01, 0x00, 0x01, 0x00, 0x01, 0x00 };	//
//const char def_Val_PASS1[] = {0x31,0x31,0x31,0x31,0x31,0x31,0x31,0x31};//level password
const char def_Val_PASS1[] = { 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31, 0x31 };//
//const char def_Val_PASS2[] = {0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32};//level password
const char def_Val_PASS2[] = { 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32, 0x32 };//
//const char def_Val_PASS3[] = {0x33,0x33,0x33,0x33,0x33,0x33,0x33,0x33};//level password
const char def_Val_PASS3[] = { 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33 };//
//const char def_Val_PASS4[] = {0x34,0x34,0x34,0x34,0x34,0x34,0x34,0x34};//level password
const char def_Val_PASS4[] = { 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34, 0x34 };//
//const char def_Val_IP1[] = {0x71,0xA1,0x45,0x7D};//IP1 address
const char def_Val_IP1[] = { 0x71, 0xA1, 0x45, 0x7D };				//
//const char def_Val_IP2[] = {0x0E,0xA1,0x01,0xC2};//IP2 address
const char def_Val_IP2[] = { 0x0E, 0xA1, 0x01, 0xC2 };				//
//const char def_Val_ID[] = {0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x31};//meter number
const char def_Val_ID[] = { 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30,
		0x30, 0x30, 0x30, 0x31 };				//表号
//const char def_Val_MD[] = {0x00,0x05};//sliding frequency 5 minutes
const char def_Val_MD[] = { 0x00, 0x05 };				//
const char def_Val_APN[] = { 0x6d, 0x2d, 0x77, 0x61, 0x70, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };				//APN
//const char def_Val_Port[] = {0x06,0xA8};//port
const char def_Val_Port[] = { 0x06, 0xA8 };				//
//const char def_var_fee_num[]={0x03};//three tariff number C200
const char def_var_fee_num[] = { 0x03 };				//
//const char def_var_Day_num[]={0x02};//two C24 day time frame meter 
const char def_var_Day_num[] = { 0x02 };				//
//const char def_var_Spare_num[]={0x01};//one C22 back up time frame
const char def_var_Spare_num[] = { 0x01 };				//
//const char def_var_week_num[]={0x02};//two C203 week meter
const char def_var_week_num[] = { 0x02 };				//
//const char def_var_Hods_num[]={0x00};//zero C201 public holidays meter
const char def_var_Hods_num[] = { 0x00 };				//
//const char def_var_Time1_1_8[]={0x00,0x00,0x03,0x04,0x00,0x01,0x09,0x30,0x02,0x11,0x30,0x01,0x17,0x00,0x02,0x20,0x00,0x01,0x22,0x00,0x03,0,0,0};//C250 day time fram meter 1,1-8
const char def_var_Time1_1_8[] = { 0x00, 0x00, 0x03, 0x04, 0x00, 0x01, 0x09,
		0x30, 0x02, 0x11, 0x30, 0x01, 0x17, 0x00, 0x02, 0x20, 0x00, 0x01, 0x22,
		0x00, 0x03, 0, 0, 0 };				//C250日时段表1,1_8
//const char def_var_Time1_9_16[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//C251 day time frame meter 1,9-16
const char def_var_Time1_9_16[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0 };				//C251日时段表1,9_16
//const char def_var_Time2_1_8[]={0x00,0x00,0x03,0x04,0x00,0x01,0x22,0x00,0x3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//C 254 day time frame meter 2,1-8
const char def_var_Time2_1_8[] = { 0x00, 0x00, 0x03, 0x04, 0x00, 0x01, 0x22,
		0x00, 0x3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };//C254日时段表2,1_8
//const char def_var_Time2_9_16[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//C255 day time frame meter 2,9-16
const char def_var_Time2_9_16[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0 };				//C255日时段表2,9_16
//const char def_var_week1_3[]={2,1,1,1,1,1,1,2,1,1,1,1,1,1,0,0,0,0,0,0,0};//C248 week meter 1~3//week meter 2
const char def_var_week1_3[] = { 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 0, 0,
		0, 0, 0, 0, 0 };				//C248周表1~3//周表2
//const char def_var_spare[]={0x20,0x01,0x01,0x02,0,0,0,0,0,0,0,0,0,0,0,0,0,0};//0xC240 backup frame 1, specified week meter 2
const char def_var_spare[] = { 0x20, 0x01, 0x01, 0x02, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0 };				//0xC240备用时段1，指定周表2
//const char def_var_Disp_Time[]={0x03};//C602 rotator time spacing
const char def_var_Disp_Time[] = { 0x03 };				//C602轮显时间间隔
//const char def_var_ATDisp_Num[]={0x0B};//C600 automatic rotate display number
const char def_var_ATDisp_Num[] = { 0x0B };				//C600自动轮显个数
//const char def_var_ATDisp_Val[]={0x00,0x00,0x00,0x01,0x00,0x02,0x00,0x03,0x00,0x04,0x00,0x05,0x00,0x06,0x00,0x08,0x00,0x12,0x00,0x13,0x00,0x14,0x10,0x71,0x10,0x33,0x00,0x00,0x00,0x00,0x00,0x00};//C610 rotate display data option
const char def_var_ATDisp_Val[] = { 0x00, 0x00, 0x00, 0x01, 0x00, 0x02, 0x00,
		0x03, 0x00, 0x04, 0x00, 0x05, 0x00, 0x06, 0x00, 0x08, 0x00, 0x12, 0x00,
		0x13, 0x00, 0x14, 0x10, 0x71, 0x10, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00 };				//C610轮显数据项
//const char def_var_DYDisp_Num[]={0x0D};//C601manual rotate display number
const char def_var_DYDisp_Num[] = { 0x0D };				//C601手动轮显个数
//const char def_var_DYDisp_Val[]={0x00,0x00,0x00,0x01,0x00,0x02,0x00,0x03,0x00,0x04,0x00,0x05,0x00,0x06,0x00,0x08,0x00,0x12,0x00,0x13,0x00,0x14,0x10,0x71,0x10,0x33,0x00,0x00,0x00,0x00,0x00,0x00};//C612 rotate display data
//const char def_var_DYDisp_Val[]={0x00,0x00,0x00,0x01,0x00,0x02,0x00,0x03,0x00,0x04,0x00,0x05,0x00,0x06,0x00,0x08,0x00,0x12,0x00,0x13,0x00,0x14,0x10,0x71,0x10,0x33,0x00,0x00,0x00,0x00,0x00,0x00};//C612轮显数据项

const DEF_PARA def_para[] = {
//{def_var_ATDisp_Val,Disp_KeyTab,RS_FRAM,32},//rotate display option
		{ def_var_ATDisp_Val, Disp_KeyTab, RS_FRAM, 32 },				//
		// {def_var_DYDisp_Num,Disp_KeyNum,RS_FRAM,1},//rotate display number
		{ def_var_DYDisp_Num, Disp_KeyNum, RS_FRAM, 1 },		//
		//{def_var_ATDisp_Val,Disp_ScTab,RS_FRAM,32},//rotate display option
		{ def_var_ATDisp_Val, Disp_ScTab, RS_FRAM, 32 },		//
		//{def_var_ATDisp_Num,Disp_ScNum,RS_FRAM,1},//rotate display number
		{ def_var_ATDisp_Num, Disp_ScNum, RS_FRAM, 1 },		//
		//{def_var_Disp_Time,DspInv,RS_FRAM,1},//rotate display time
		{ def_var_Disp_Time, DspInv, RS_FRAM, 1 },		//
		//{def_var_spare,SEASON1,RS_E2PROM,18},//backup time table
		{ def_var_spare, SEASON1, RS_E2PROM, 18 },		//
		//{def_var_week1_3,WEEKTAB1,RS_E2PROM,21},//week table 1~3
		{ def_var_week1_3, WEEKTAB1, RS_E2PROM, 21 },		//
		//{def_var_Time2_9_16,(DAYTAB2_SEG1+24*1),RS_E2PROM,24},//day time frame table 2
		{ def_var_Time2_9_16, (DAYTAB2_SEG1 + 24 * 1), RS_E2PROM, 24 },	//
		//{def_var_Time2_1_8,(DAYTAB2_SEG1+24*0),RS_E2PROM,24},//day time frame table 2
		{ def_var_Time2_1_8, (DAYTAB2_SEG1 + 24 * 0), RS_E2PROM, 24 },//
		//{def_var_Time1_9_16,(DAYTAB1_SEG1+24*1),RS_E2PROM,24},//day time frame table 1
		{ def_var_Time1_9_16, (DAYTAB1_SEG1 + 24 * 1), RS_E2PROM, 24 },	//
		//{def_var_Time1_1_8,(DAYTAB1_SEG1),RS_E2PROM,24},//day time frame table 1
		{ def_var_Time1_1_8, (DAYTAB1_SEG1), RS_E2PROM, 24 },		//
		//{def_var_Hods_num,(EXPDAYSNUM),RS_E2PROM,1},//public holiday number
		{ def_var_Hods_num, (EXPDAYSNUM), RS_E2PROM, 1 },		//
		// {def_var_week_num,(WEEKTABSNUM),RS_E2PROM,1},//week table number
		{ def_var_week_num, (WEEKTABSNUM), RS_E2PROM, 1 },		//
		//{def_var_Spare_num,(SEASONSNUM),RS_E2PROM,1},//back up timing
		{ def_var_Spare_num, (SEASONSNUM), RS_E2PROM, 1 },		//
		//{def_var_Day_num,(DAYTABSNUM),RS_E2PROM,1},//day time period number
		{ def_var_Day_num, (DAYTABSNUM), RS_E2PROM, 1 },		//
		//{def_var_fee_num,(TOU_FEE_NUM),RS_E2PROM,1},//tariff number
		{ def_var_fee_num, (TOU_FEE_NUM), RS_E2PROM, 1 },		//
		// {def_Val_Port,(NET_PORT),RS_FRAM,2},//port
		{ def_Val_Port, (NET_PORT), RS_FRAM, 2 },		//
		{ def_Val_APN, (NET_APN), RS_FRAM, 16 },		//APN
		{ def_Val_IP1, (NET_IP), RS_FRAM, 4 },		//IP1
		{ def_Val_IP2, (NET_SEC_IP_STAR), RS_FRAM, 4 },		//IP2
		// {def_Val_ID,(DeviceAddr),RS_FRAM,12},//table number
		{ def_Val_ID, (DeviceAddr), RS_FRAM, 12 },		//
		//{def_Val_MD,(MD_BlockTm),RS_FRAM,2},//sliding frequency time
		{ def_Val_MD, (MD_BlockTm), RS_FRAM, 2 },		//
		//{def_Val_PASS3,(PassWord),RS_FRAM,8},//level password
		{ def_Val_PASS3, (PassWord), RS_FRAM, 8 },		//
		// {def_Val_PASS2,(PassWord+8),RS_FRAM,8},//level password
		{ def_Val_PASS2, (PassWord + 8), RS_FRAM, 8 },		//
		// {def_Val_PASS1,(PassWord+16),RS_FRAM,8},//level password
		{ def_Val_PASS1, (PassWord + 16), RS_FRAM, 8 },		//
		{ def_Val_PTCT, PARA_PTCT, RS_FRAM, 8 },		//PTCT
		//{def_Val_Dot,EnDot,RS_E2PROM,2},//decimal places
		{ def_Val_Dot, EnDot, RS_E2PROM, 2 },		//
		//{def_Val_UnBalance,Val_UnbV,RS_FRAM,2},//three phase unbalaced
		{ def_Val_UnBalance, Val_UnbV, RS_FRAM, 2 },		//
		//{def_Val_IOver,Val_IOver,RS_FRAM,2},//overcurrent threshold value
		{ def_Val_IOver, Val_IOver, RS_FRAM, 2 },		//
		// {def_Val_VOver,Val_VOver,RS_FRAM,2},//overvoltage threshold value
		{ def_Val_VOver, Val_VOver, RS_FRAM, 2 },		//
		//{def_Val_VFailure,Val_VFailure,RS_FRAM,2},//loss of voltage, split-phase threshold value
		{ def_Val_VFailure, Val_VFailure, RS_FRAM, 2 },		//
		//{def_Val_Newdly,Dly_UnbV,RS_FRAM,2},//new event delay time
		{ def_Val_Newdly, Dly_UnbV, RS_FRAM, 2 },		//
		//{def_SysSW,SysSW,RS_E2PROM,4},//system switch
		{ def_SysSW, SysSW, RS_E2PROM, 4 },		//
		//{def_md_time,MD_BlockTm,RS_FRAM,2},//demand period
		{ def_md_time, MD_BlockTm, RS_FRAM, 2 },		//
		//{def_BillingDate,BillingDate,RS_FRAM,1},//frozen day
		{ def_BillingDate, BillingDate, RS_FRAM, 1 },		//
		//{def_Val_PASS4,(PASSWORD_NEW),RS_FRAM,8},//level password
		{ def_Val_PASS4, (PASSWORD_NEW), RS_FRAM, 8 }, //

		};

#define DEF_PARA_NUM ((sizeof(def_para))/(sizeof(DEF_PARA)))

/**********************************************************************
 //acquire check table pointer
 得到校验表指针
 **********************************************************************/
unsigned int GetChkPtr(char *Addr, char MemType) {
	unsigned int i, Len;
	char *BlkAddr;

	for (i = 0; i < ChkTabNum; i++) {
		if (((ChkTab[i].Type >> 5) & 0x07) == MemType) {
			BlkAddr = ChkTab[i].BlkAddr;
			Len = ChkTab[i].Lenth;
			if ((Addr >= BlkAddr) && (Addr < (BlkAddr + Len)))
				return i;
		}
	}
	return 0xFFFF;
}
/**********************************************************************
 Security Check
 **********************************************************************/
#define	S_FC			0x80		// Factory Setup
#define	S_LB			0x40		// Laboratory State
#define	S_PK			0x20		// Program Key Enable
#define	S_LK			0x10		// Data Lock
#define	S_S3			0x08		// Program A
#define	S_S2			0x04		// Program B
#define	S_S1			0x02		// M.D Reset
#define	S_S0			0x01		// Read
/**********************************************************************
 Calculate the checksum Of Data in RAM
 **********************************************************************/
int ChkNum(char *Ptr, int Len) {
	int Num = CHECKWORD;

	while (Len > 0) {
		Num += *Ptr++;
		Len--;
	}
	return Num;
}
/**********************************************************************
 Calculate the checksum Of Data in FRAM, EEPORM, DFlash
 **********************************************************************/
//notice: this function will cover the last 32 bytes of global variable, if Buffer is 110 bytes, then the last 32 bytes will be covered from buffer 78,
//if buffer is 32 bytes,then the last 32  bytes will be cover from 0, meaning the whole
//notice:MEM-DBWrite will call this function, and cover the last 32 bytes of buffer,
//do not cover the data when using data of MEM-DBWrite storage
int ChkMem(unsigned long Ptr, int Lenth, char MemType) {
	int Num = CHECKWORD, Size;
	int StartID;

	StartID = MAX_BUF - 32;
	while (Lenth > 0) {
		if (Lenth >= 32)
			Size = 32;
		else
			Size = Lenth;

		MEM_Read((char*) &Buffer[StartID], Ptr, Size, MemType);
		Num += (ChkNum((char*) &Buffer[StartID], Size) - CHECKWORD);
		Ptr += Size;
		Lenth -= Size;
	}
	return Num;
}

/*--------------------------------------------------------
 //clean one option of contend from ChkTab
 //if CommClear=0xFF,then clear all data marked Comm-Clr from ChkTab
 --------------------------------------------------------*/
void MEM_DBClear(unsigned char CommClear) {
	unsigned int BlkAddr, MemBak;
	char i, MemType;
	unsigned int Len;

	if (CommClear != 0xFF) {
		if (CommClear >= ChkTabNum)
			return;

		BlkAddr = (int) ChkTab[CommClear].BlkAddr;
		Len = ChkTab[CommClear].Lenth;
		MemType = ChkTab[CommClear].Type;
		MemType = (MemType >> 5) & 0x07;
		MemBak = MemBakTab[MemType];

		//MEM_Clr( BlkAddr, Len, MemType );               //clear data of the storage area and write check code
		MEM_Clr(BlkAddr, Len, MemType); //
		if (MemBak != 0x0000)
			//MEM_Clr( BlkAddr+MemBak, Len, MemType );    //clear data of the storage area and write check code
			MEM_Clr(BlkAddr + MemBak, Len, MemType); //
	} else
		for (i = 0; i < ChkTabNum; i++) {
			WDTClr();

			BlkAddr = (unsigned int) ChkTab[i].BlkAddr;
			Len = ChkTab[i].Lenth;
			MemType = ChkTab[i].Type;
			if ((MemType & Comm_) != Comm_Clr)
				continue;
			MemType = (MemType >> 5) & 0x07;
			MemBak = MemBakTab[MemType];

			//MEM_Clr( BlkAddr, Len, MemType );               //clear data of the storage area and write check code
			MEM_Clr(BlkAddr, Len, MemType); //
			if (MemBak != 0x0000)
				//MEM_Clr( BlkAddr+MemBak, Len, MemType );    //clear data of the storage area and write check code
				MEM_Clr(BlkAddr + MemBak, Len, MemType); //
		}
}

/**********************************************************************
 //time and date initialization value
 **********************************************************************/
const char ClkInitTab[6] = { // Min, Hour, Day, Month, Year, Week (06-08-21 12:00 1)
		0x00, 0x12, 0x01, 0x03, 0x12, 0x10 };

/*******************************************************************************
 //function name: MemCheck
 //description:check data, check specified data block or all data
 //input:CHKType checking data block
 //output:
 //backspace:
 //notice:CHKType=0xFFFF means all check,or only check specified Memory Type data
 *******************************************************************************/
void MemCheck(unsigned int CHKType) {
	unsigned long BlkAddr, MemBak;
	unsigned int Tmp;
	unsigned char i, ErrFlag, MemType;
	unsigned int Len;

	WDTClr();
	ALARM[1] = 0x00;

	for (i = 0; i < ChkTabNum; i++) {

		//BlkAddr = (unsigned int)ChkTab[i].BlkAddr;//acquire check table
		BlkAddr = (unsigned int) ChkTab[i].BlkAddr; //
		Len = ChkTab[i].Lenth;
		MemType = ChkTab[i].Type;
		//MemType = (MemType>>5) & 0x07;          //right shift 5 places to initial Memtype data
		MemType = (MemType >> 5) & 0x07; //
		//MemBak = MemBakTab[MemType];            //acquire initial address from backup area
		MemBak = MemBakTab[MemType]; //

		if ((CHKType != Chk_ALLMemory) && (((CHKType >> 5) & 0x07) != MemType))
			continue;

		WDTClr();

		ErrFlag = 0;
		switch (MemType) {
		case Mem_FRAM:
		case Mem_E2PROM:
		case Mem_DFlash:
			MEM_Read((char*) &Tmp, BlkAddr + MemBak + Len, 2, MemType);
			if (Tmp != ChkMem(BlkAddr + MemBak, Len, MemType))
				//ErrFlag |= 0x02;  //wrong backup
				ErrFlag |= 0x02; //
		case Mem_RAM:
			MEM_Read((char*) &Tmp, BlkAddr + Len, 2, MemType);
			if (Tmp != ChkMem(BlkAddr, Len, MemType))
				//ErrFlag |= 0x01;  //wrong storage area
				ErrFlag |= 0x01; //
		default:
			break;
		}

		if (ErrFlag != 0) {
			if (MemType == Mem_RAM)
				ErrFlag = 0x03;
		} else
			//continue;   //if ErrFlag=0, skip the following process, enter into next cycle judgement
			continue;//

		ALARM[1] |= (0x01 << MemType);

		switch (ErrFlag) {
		//case 0x01:  //wrong storage area only, copy data to cover storage area from backup area
		case 0x01: //
			MEM_MEM(BlkAddr, BlkAddr + MemBak, Len + 2, MemType);
			break;
			//case 0x02:  //wrong storage area only, copy data to cover storage area from backup area
		case 0x02: //
			MEM_MEM(BlkAddr + MemBak, BlkAddr, Len + 2, MemType);
			break;
			//case 0x03: //all wrong, or wrong RAM data
		case 0x03: //
			Tmp = ChkTab[i].Type & Init_;
			switch (Tmp) {
			case Init_FRAMClk:

				//MEM_DBWrite( ClockBuf, (char*)ClkInitTab, 6, Mem_FRAM );//write time
				MEM_DBWrite( ClockBuf, (char*) ClkInitTab, 6, Mem_FRAM); //

				break;
			case Init_RAMClk:

				FRAM_Read((char*) &Clk.Min, ClockBuf, 8);
				Clk.Sec[0] = 0;

				break;
			case Init_RAMFlg:
				//FRAM_Read( (char*)&SM.PWCnt, Ram_Puls, 6 );
				break;
			default:
				//automatically add check code to the end from MEM-Clr
				//MEM_Clr( BlkAddr, Len, MemType );           //clear data of storage area and write check code
				MEM_Clr(BlkAddr, Len, MemType); //
				if (MemBak != 0x0000)
					//MEM_Clr( BlkAddr+MemBak, Len, MemType );//clear data of storage area and write check code
					MEM_Clr(BlkAddr + MemBak, Len, MemType); //

				//if ( MemType == Mem_RAM )                   //if is RAM, clear data of the backup area too
				if (MemType == Mem_RAM) //
					MEM_Clr(BlkAddr + MemBak, Len, Mem_RAM);

				break;
			}
		default:
			break;
		}
	}
}
//************************************************************
//time date check
unsigned int InvalidCLK(unsigned char *cCLK) {
	unsigned int i;
	unsigned int r;

	r = 0x0000;
	if (cCLK[0] > 0x59 || cCLK[1] > 0x59 || cCLK[2] > 0x23 || cCLK[3] > 0x31
			|| cCLK[4] > 0x12 || cCLK[3] == 0x00 || cCLK[4] == 0x00
			|| cCLK[6] == 0x00)
		r |= 0x0001;

	for (i = 0; i < 7; i++)
		if ((cCLK[i] & 0x0F) > 0x09 || (cCLK[i] & 0xF0) > 0x90) {
			r |= 0x0001;
			break;
		}
	{

		if (((cCLK[4] == 2) || (cCLK[4] == 4) || (cCLK[4] == 6)
				|| (cCLK[4] == 9) || (cCLK[4] == 0x11)) && (cCLK[3] > 0x30)) {
			r |= 0x0001;
		}
		if (cCLK[4] == 2) {
			unsigned char temp;
			temp = (((cCLK[5] & 0xF0) >> 4) * 10 + (cCLK[5] & 0x0F));
			if ((temp & 0x03) == 0x00) {
				if (cCLK[3] > 0x29)
					r |= 0x0001;
			} else if ((temp & 0x03) != 0x00) {
				if (cCLK[3] > 0x28)
					r |= 0x0001;
			}
		}

	}
	return (r);
}

/*******************************************************************************
 //function name:checkClock
 //description: check clock
 //input:
 //output:
 //backspace:
 //notice:if the time in the clock chip is incorrect, then adopt FRAM backup, if FRAM backup is incorrect, adopt default time
 *******************************************************************************/
void checkClock(void) {

	unsigned char buf[7];
	//read clock
	RX8025_Read(buf, 0, 7);
	Clk.Sec[0] = buf[0];
	Clk.Min[0] = buf[1];
	Clk.Hour[0] = buf[2];
	Clk.Day[0] = buf[4];
	Clk.Mon[0] = buf[5];
	Clk.Year[0] = buf[6];
	Clk.Week[0] = buf[3];
	//calculate check code
	Clk.Check = ChkNum(&Clk.Min[0], 6);
	//check if the time of the clock chip is correct
	if ((Clk.Check == ChkNum(&Clk.Min[0], 6))
			&& InvalidCLK((unsigned char*) &Clk.Sec[0]) == 0x0000) {

		//write impulse output
		buf[0] = 0x00;
		buf[1] = 0x00;
		buf[2] = 0x60;
		RX8025_Write(0x0d, buf, 3);

		return;
	}
	//read FRAM time
	MEM_Read(&Clk.Min[0], ClockBuf, 8, Mem_FRAM);
	Clk.Sec[0] = 0x00;
	//if FRAM time is incorrect
	if ((Clk.Check != ChkNum(&Clk.Min[0], 6))
			|| InvalidCLK((unsigned char*) &Clk.Sec[0]) == 0x0001) {

		MEM_Read(&Clk.Min[0], ClockBuf + FRAMBAK, 8, Mem_FRAM);
		Clk.Sec[0] = 0x00;
		//if FRAM backup time is incorrect
		if ((Clk.Check != ChkNum(&Clk.Min[0], 6))
				|| InvalidCLK((unsigned char*) &Clk.Sec[0]) == 0x0001) {
			//restore to default time
			memcpy(&Clk.Min, &ClkInitTab[0], 6);
			Clk.Check = ChkNum(&Clk.Min[0], 6);
		}

	}

	//write clock
	buf[0] = Clk.Sec[0];
	buf[1] = Clk.Min[0];
	buf[2] = Clk.Hour[0];
	buf[4] = Clk.Day[0];
	buf[5] = Clk.Mon[0];
	buf[6] = Clk.Year[0];
	buf[3] = Clk.Week[0];
	RX8025_Write(0, buf, 7);
	//write second impulse output
	buf[0] = 0x00;
	buf[1] = 0x00;
	buf[2] = 0x60;
	RX8025_Write(0x0d, buf, 3);

	_NOP();
}

//high four places means firmware type
//low four places means meter type
#ifdef  HARDWARE_TWO

#if METER_TYPE == 1
#define BFid        0xB8
#endif

#if METER_TYPE == 2
#define BFid        0xB9
#endif

#if METER_TYPE == 3
#define BFid        0xBA
#endif

#if METER_TYPE == 4
#define BFid        0xBB
#endif

#if METER_TYPE == 5
#define BFid        0xBC
#endif

#else

#if METER_TYPE == 1
#define BFid        0xA8
#endif

#if METER_TYPE == 2
#define BFid        0xA9
#endif

#if METER_TYPE == 3
#define BFid        0xAA
#endif

#if METER_TYPE == 4
#define BFid        0xAB
#endif

#if METER_TYPE == 5
#define BFid        0xAC
#endif

#endif

/*******************************************************************************
 //function name: FirstBurn
 //description: first operation of system test
 //input:
 //output:
 //backspace:
 //notice: judging if is the first operation after burner based on whether the BurnFirst in the Fram is BFid
 //because different version of the firmware and current type, default parameter of the first operation is different,
 //so the same burner of different firmware version and current type is regarded as first operation
 *******************************************************************************/
void FirstBurn(void) {
	unsigned int i;

	//judge if is the first operation
	for (i = 0; i < 8; i++) {

#ifdef NO_FRAM

#else
		FRAM_Read((char*) &Buffer[0], BurnFirst, 2);
#endif
		if ((Buffer[0] == BFid) && (Buffer[1] == BFid))
			return;
	}
	for (i = 0; i < 8; i++) {
#ifdef NO_FRAM

#else
		FRAM_Read((char*) &Buffer[0], BurnFirst + FRAMBAK, 2);
#endif
		if ((Buffer[0] == BFid) && (Buffer[1] == BFid))
			return;
	}
	//not first operation, configuration of difault parameter is necessary
#ifdef NO_FRAM

#else
	FRAM_Read((char*) &Buffer[0], kWCumuMode, 8);
#endif
	if ((Buffer[6] != BFid) && (Buffer[7] != BFid)) {
		{
			unsigned char i = 0;
			unsigned char j = 0;
			unsigned int Addr, Len;
			char MemType;
			unsigned int tmp;
			//acquire default parameter table, preserve to corresponding reservoir
			for (i = 0; i < DEF_PARA_NUM; i++) {
				WDTClr();
				memcpy(Buffer, def_para[i].src_addr, def_para[i].len);

				if (def_para[i].type == RS_E2PROM) {
					E2P_Write((unsigned int) def_para[i].dec_addr, Buffer,
							def_para[i].len);
					E2P_Write((unsigned int) def_para[i].dec_addr + E2P_BAK,
							Buffer, def_para[i].len);
				} else if (def_para[i].type == RS_FRAM) {
					FRAM_Write((unsigned int) def_para[i].dec_addr, Buffer,
							def_para[i].len);
					FRAM_Write((unsigned int) def_para[i].dec_addr + FRAMBAK,
							Buffer, def_para[i].len);
				}

				Addr = (unsigned int) def_para[i].dec_addr;
				Len = def_para[i].len;
				MemType = (def_para[i].type >> 6) & 0x07;

				//ReCheck and write backup
				for (j = 0; j < ChkTabNum; j++) {
					if ((Addr >= (unsigned long) ChkTab[j].BlkAddr
							&& Addr
									< (unsigned long) ChkTab[j].BlkAddr
											+ ChkTab[j].Lenth)
							&& (MemType == ((ChkTab[j].Type >> 5) & 0x07))) {
						tmp = ChkMem((unsigned long) ChkTab[j].BlkAddr,
								ChkTab[j].Lenth, MemType);
						MEM_Write(
								(unsigned int) ChkTab[j].BlkAddr
										+ ChkTab[j].Lenth, (char*) &tmp, 2,
								MemType);

						if (MemBakTab[MemType] != 0x00000000) {
							MEM_MEM(Addr + MemBakTab[MemType], Addr, Len,
									MemType);
							MEM_Write(
									(unsigned int) ChkTab[j].BlkAddr
											+ ChkTab[j].Lenth
											+ MemBakTab[MemType], (char*) &tmp,
									2, MemType);
						}
						break;
					}
				}

			}

//****************reset load curve
			{
				memset(&Buffer[0], 0x00, 48);
#ifdef NO_FRAM

#else
				MEM_DBWrite(LoadInfoRun_, &Buffer[0], 48, Mem_FRAM);
				FRAM_Write(LOAD_DATE_SET_COUNT, &Buffer[0], 48);
#endif
			}
			{
				int Ptr;
				EevenLPPtr.LoadProCh = Buffer[0];
#ifdef NO_FRAM

#else
				FRAM_Read((char*) &Ptr,
				RecPtr1_ + SIZE_LoadINFORUN * EevenLPPtr.LoadProCh, 2);
#endif
				if (Ptr > 0)
					Ptr--;
				else {
#ifdef NO_FRAM

#else
					FRAM_Read((char*) &Ptr,
					MaxRecNUM1_ + SIZE_LoadINFO * EevenLPPtr.LoadProCh, 2);
#endif
					Ptr -= 1;
				}

				if (EevenLPPtr.LoadProCh >= LP_MaxChNum) {
					EevenLPPtr.LoadProCh = 0;
				}
#ifdef NO_FRAM

#else
				MEM_DBWrite(
				ReadPtr1_ + SIZE_LoadINFORUN * EevenLPPtr.LoadProCh,
						(char*) &Ptr, 2, Mem_FRAM);
#endif
			}

			//********************
			{
				Buffer[0] = 0x04;
				Buffer[1] = 0x01;
				Buffer[2] = 0x02;
				Buffer[3] = 0x03;
				Buffer[4] = 0x04;
#ifdef NO_FRAM

#else
				MEM_DBWrite( RegNUM1_ + SIZE_LoadINFO * EevenLPPtr.LoadProCh,
						&Buffer[0], 8, Mem_FRAM);
#endif
				//memset(&Buffer[0], 0x00, SIZE_LoadINFORUN);    //reset corresponding channel
				memset(&Buffer[0], 0x00, SIZE_LoadINFORUN); //
#ifdef NO_FRAM

#else
				MEM_DBWrite(
				LoadInfoRun_ + SIZE_LoadINFORUN * EevenLPPtr.LoadProCh,
						&Buffer[0], SIZE_LoadINFORUN, Mem_FRAM);
#endif
			}
			//**********************
			{
				unsigned long ulTmp = 0;
				//ulTmp+=LOADCURVE;		//add one initial address
				ulTmp += LOADCURVE; //
				memcpy(Buffer, (char*) &ulTmp, 4);
#ifdef NO_FRAM

#else
				MEM_DBWrite( RecAddr1_ + SIZE_LoadINFO * EevenLPPtr.LoadProCh,
						&Buffer[0], 4, Mem_FRAM);
#endif
			}
			//****************
			{
				Buffer[1] = 0x21;
				Buffer[0] = 0xC0;
#ifdef NO_FRAM

#else
				MEM_DBWrite(
				MaxRecNUM1_ + SIZE_LoadINFO * EevenLPPtr.LoadProCh, &Buffer[0],
						2, Mem_FRAM);
#endif
			}
		}

		//active counting form forward active=forward active + reverse active
		//                         reverse active=reverse active
		//                          meaning  kWCumuMode = 0x01
		//reactive counting form forward reactive=I quadrant reactive +IV quadrant reactive
		//                         reverse reactive= II quadrant reactive + III quadranat reactive
		//                            meaning  kvarCumuMode = 0x01,default as 0x00.
		//power quantity counting form 0x00 algebraic sum 0x01:absolute value sum
		//PowerCumu
#ifdef  HARDWARE_TWO
		//Buffer[0]=0x00; //kWCumuMode  active independent counting
		Buffer[0] = 0x00; //kWCumuMode    有功独立计量
		Buffer[1] = 0x00; //kvarCumuMode
		Buffer[2] = 0x01; //PowerCumu
#else
				//Buffer[0]=0x01; //kWCumuMode  active counting accumulate reactive
				Buffer[0]=0x01;//kWCumuMode    有功计量累计无功
				Buffer[1]=0x00;//kvarCumuMode
				Buffer[2]=0x01;//PowerCumu
#endif

#ifdef NO_FRAM

#else
		FRAM_Write(kWCumuMode, (char*) &Buffer[0], 3);
		FRAM_Write(kWCumuMode + FRAMBAK, (char*) &Buffer[0], 3);

		Buffer[6] = BFid; //BurnFirst
		Buffer[7] = BFid; //BurnFirst
		//FRAM_Write(BurnFirst, (char*)&Buffer[6], 2); //preserve first operation information
		FRAM_Write(BurnFirst, (char*) &Buffer[6], 2); //
		FRAM_Write(BurnFirst + FRAMBAK, (char*) &Buffer[6], 2);
#endif
	}
}

