#include "..\inc\includes.h"// add by bnthang

// data save in eeprom 24lc64
#ifndef		_E2_LAYOUT_H
#define		_E2_LAYOUT_H

#define	E2PStAddr	0x0000
#define	E2PEndAddr	(0x0000+0x1FFF)
#define	E2PCAP		0x2000
#define	E2PPGSIZE	32

#define	E2P_START	0x0000
#define	E2P_SIZE	E2PCAP
#define	E2P_BAK		0x0900  //
#define	E2P_BAK_END	0x1200  //
 
//===== DOUBLE SAVE SIZE now =(1020+62+26+180+320)=1608 ======================
#define	TOU_TABLE			E2P_START			//1020 =483+(39+87+411)     //1565 = 483+(39+87+411)*2 + 8
//#define	TOU_TABLE_END		(TOU_TABLE+1050+1)	//add one tariff number
#define	TOU_TABLE_END		(TOU_TABLE+1050+1)	//
//
#define CTPTCHANGE          TOU_TABLE_END       //62 =31*2=(5+8+16+2)*2
#define CTPTCHANGE_END      CTPTCHANGE+62   
//
#define COMM_LAST           CTPTCHANGE_END      //26
#define COMM_LAST_END       COMM_LAST+26
//
#define SYSPARA             COMM_LAST_END       //320
#define SYSPARA_END         SYSPARA+320         

//===== EVENTLOG SIZE now =201*6+441*5=3411 ==================================
#define	EVENTLOG		    E2P_BAK_END	        //3584
#define	EVENTLOG_END	    EVENTLOG+3584// 0x2000

//----- TOU_TABEL ------------------------------------------------------------
//483+1
#define	TOU_FEE_NUM	TOU_TABLE			// 0x0000
#define	EXPDAYS		TOU_FEE_NUM+1
#define	EXPDAYSNUM	EXPDAYS			//1
#define	EXPDAY1		EXPDAYSNUM+1+4*0//4
#define	EXPDAY2		EXPDAY1+4*1		//4
#define	EXPDAY120	EXPDAY1+4*119	//4
#define	EXPDAY_CHK	EXPDAY1+4*120	//2
//39
#define	SEASONS		EXPDAYS+483
#define	SEASONSNUM	SEASONS			//1
#define	SEASON1		SEASONSNUM+1+3*0//3
#define	SEASON2		SEASON1+3*1		//3
#define	SEASON12	SEASON1+3*11	//3
#define	SEASON_CHK	SEASON1+3*12	//2
//87
#define	WEEKTABS	SEASONS+39
#define	WEEKTABSNUM	WEEKTABS		    //1
#define	WEEKTAB1	WEEKTABSNUM+1+7*0   //7
#define	WEEKTAB2	WEEKTAB1+7*1	    //7
#define	WEEKTAB12	WEEKTAB1+7*11	    //7
#define	WEEKTAB_CHK	WEEKTAB1+7*12	    //2
//411=3+51*8
#define	DAYTABS		WEEKTABS+87
#define	DAYTABSNUM	DAYTABS			    //1
#define	DAYTABSNUM_CHK	DAYTABSNUM+1    //2
#define	DAYTAB_ENTRY	DAYTABSNUM+3	// 0x0265
//51
 //session number of each session, one is 12 session table, 12 bytes in total

#define	DAYTAB1_SEGSNUM	DAYTAB_ENTRY+51*0		//1 -> 0x0265

#define	DAYTAB1_SEG1	DAYTAB1_SEGSNUM+1	//3


#define	DAYTAB1_SEG2	DAYTAB1_SEG1+3*1		//3
#define	DAYTAB1_SEG16	DAYTAB1_SEG1+3*15		//3
#define	DAYTAB1_CHK		DAYTAB1_SEG1+3*16		//2


#define	DAYTAB2_SEGSNUM	DAYTAB_ENTRY+51*1		//1
#define	DAYTAB2_SEG1	DAYTAB2_SEGSNUM+1     //+1+3*0	//3


#define	DAYTAB2_SEG2	DAYTAB2_SEG1+3*1		//3
#define	DAYTAB2_SEG16	DAYTAB2_SEG1+3*15		//3
#define	DAYTAB2_CHK		DAYTAB2_SEG1+3*16		//2


#define	DAYTAB3_SEGSNUM	DAYTAB_ENTRY+51*2		//1
#define	DAYTAB3_SEG1	DAYTAB3_SEGSNUM+1//+1+3*0	//3


#define	DAYTAB3_SEG2	DAYTAB3_SEG1+3*1		//3
#define	DAYTAB3_SEG16	DAYTAB3_SEG1+3*15		//3
#define	DAYTAB3_CHK		DAYTAB3_SEG1+3*16		//2



#define	DAYTAB4_SEGSNUM	DAYTAB_ENTRY+51*3		//1
#define	DAYTAB4_SEG1	DAYTAB4_SEGSNUM+1//+1+3*0	//3


#define	DAYTAB4_SEG2	DAYTAB4_SEG1+3*1		//3
#define	DAYTAB4_SEG16	DAYTAB4_SEG1+3*15		//3
#define	DAYTAB4_CHK		DAYTAB4_SEG1+3*16		//2



#define	DAYTAB5_SEGSNUM	DAYTAB_ENTRY+51*4		//1
#define	DAYTAB5_SEG1	DAYTAB5_SEGSNUM+1//+1+3*0	//3


#define	DAYTAB5_SEG2	DAYTAB5_SEG1+3*1		//3
#define	DAYTAB5_SEG16	DAYTAB5_SEG1+3*15		//3
#define	DAYTAB5_CHK		DAYTAB5_SEG1+3*16		//2


#define	DAYTAB6_SEGSNUM	DAYTAB_ENTRY+51*5		//1
#define	DAYTAB6_SEG1	DAYTAB6_SEGSNUM+1//+1+3*0	//3


#define	DAYTAB6_SEG2	DAYTAB6_SEG1+3*1		//3
#define	DAYTAB6_SEG16	DAYTAB6_SEG1+3*15		//3
#define	DAYTAB6_CHK		DAYTAB6_SEG1+3*16		//2


#define	DAYTAB7_SEGSNUM	DAYTAB_ENTRY+51*6		//1
#define	DAYTAB7_SEG1	DAYTAB7_SEGSNUM+1//+1+3*0	//3


#define	DAYTAB7_SEG2	DAYTAB7_SEG1+3*1		//3
#define	DAYTAB7_SEG16	DAYTAB7_SEG1+3*15		//3
#define	DAYTAB7_CHK		DAYTAB7_SEG1+3*16		//2


#define	DAYTAB8_SEGSNUM	DAYTAB_ENTRY+51*7		//1
#define	DAYTAB8_SEG1	DAYTAB8_SEGSNUM+1//+1+3*0	//3


#define	DAYTAB8_SEG2	DAYTAB8_SEG1+3*1		//3
#define	DAYTAB8_SEG16	DAYTAB8_SEG1+3*15		//3
#define	DAYTAB8_CHK		DAYTAB8_SEG1+3*16		//2

#define DAYTAB_SEGSNUM      DAYTAB8_CHK+10 //0x0405



/*
//39											---for switch
#define	SEASONS_SW		SEASONS+537
#define	SEASONSNUM_SW	SEASONS_SW			//1
#define	SEASON1_SW		SEASONSNUM_SW+1+5*0	//5
#define	SEASON2_SW		SEASON1_SW+5*1		//5
#define	SEASON12_SW		SEASON1_SW+5*11		//5
#define	SEASON_SW_CHK	SEASON1_SW+5*12		//2
//87
#define	WEEKTABS_SW		SEASONS_SW+39
#define	WEEKTABSNUM_SW	WEEKTABS_SW			//1
#define	WEEKTAB1_SW		WEEKTABSNUM_SW+1+7*0//8
#define	WEEKTAB2_SW		WEEKTAB1_SW+7*1		//8
#define	WEEKTAB12_SW	WEEKTAB1_SW+7*11	//8
#define	WEEKTAB_SW_CHK	WEEKTAB1_SW+7*12	//2
//411=3+51*8
#define	DAYTABS_SW		WEEKTABS_SW+87
#define	DAYTABSNUM_SW	DAYTABS_SW			//1
#define	DAYTAB_SW_CHK	DAYTABSNUM+1		//2
#define	DAYTAB_ENTRY_SW	DAYTABSNUM_SW+3
//51
#define	DAYTAB1_SEGSNUM_SW	DAYTAB_ENTRY_SW+51*0		//1
#define	DAYTAB1_SEG1_SW		DAYTAB1_SEGSNUM_SW+1+3*0	//3
#define	DAYTAB1_SEG2_SW		DAYTAB1_SEG1_SW+3*1			//3
#define	DAYTAB1_SEG16_SW	DAYTAB1_SEG1_SW+3*15		//3
#define	DAYTAB1_SW_CHK		DAYTAB1_SEG1_SW+3*16		//2

#define	DAYTAB2_SEGSNUM_SW	DAYTAB_ENTRY_SW+51*1		//1
#define	DAYTAB2_SEG1_SW		DAYTAB2_SEGSNUM_SW+1+3*0	//3
#define	DAYTAB2_SEG2_SW		DAYTAB2_SEG1_SW+3*1			//3
#define	DAYTAB2_SEG16_SW	DAYTAB2_SEG1_SW+3*15		//3
#define	DAYTAB2_SW_CHK		DAYTAB2_SEG1_SW+3*16		//2

#define	DAYTAB3_SEGSNUM_SW	DAYTAB_ENTRY_SW+51*2		//1
#define	DAYTAB3_SEG1_SW		DAYTAB3_SEGSNUM_SW+1+3*0	//3
#define	DAYTAB3_SEG2_SW		DAYTAB3_SEG1_SW+3*1			//3
#define	DAYTAB3_SEG16_SW	DAYTAB3_SEG1_SW+3*15		//3
#define	DAYTAB3_SW_CHK		DAYTAB3_SEG1_SW+3*16		//2

#define	DAYTAB4_SEGSNUM_SW	DAYTAB_ENTRY_SW+51*3		//1
#define	DAYTAB4_SEG1_SW		DAYTAB4_SEGSNUM_SW+1+3*0	//3
#define	DAYTAB4_SEG2_SW		DAYTAB4_SEG1_SW+3*1			//3
#define	DAYTAB4_SEG16_SW	DAYTAB4_SEG1_SW+3*15		//3
#define	DAYTAB4_SW_CHK		DAYTAB4_SEG1_SW+3*16		//2

#define	DAYTAB5_SEGSNUM_SW	DAYTAB_ENTRY_SW+51*4		//1
#define	DAYTAB5_SEG1_SW		DAYTAB5_SEGSNUM_SW+1+3*0	//3
#define	DAYTAB5_SEG2_SW		DAYTAB5_SEG1_SW+3*1			//3
#define	DAYTAB5_SEG16_SW	DAYTAB5_SEG1_SW+3*15		//3
#define	DAYTAB5_SW_CHK		DAYTAB5_SEG1_SW+3*16		//2

#define	DAYTAB6_SEGSNUM_SW	DAYTAB_ENTRY_SW+51*5		//1
#define	DAYTAB6_SEG1_SW		DAYTAB6_SEGSNUM_SW+1+3*0	//3
#define	DAYTAB6_SEG2_SW		DAYTAB6_SEG1_SW+3*1			//3
#define	DAYTAB6_SEG16_SW	DAYTAB6_SEG1_SW+3*15		//3
#define	DAYTAB6_SW_CHK		DAYTAB6_SEG1_SW+3*16		//2

#define	DAYTAB7_SEGSNUM_SW	DAYTAB_ENTRY_SW+51*6		//1
#define	DAYTAB7_SEG1_SW		DAYTAB7_SEGSNUM_SW+1+3*0	//3
#define	DAYTAB7_SEG2_SW		DAYTAB7_SEG1_SW+3*1			//3
#define	DAYTAB7_SEG16_SW	DAYTAB7_SEG1_SW+3*15		//3
#define	DAYTAB7_SW_CHK		DAYTAB7_SEG1_SW+3*16		//2

#define	DAYTAB8_SEGSNUM_SW	DAYTAB_ENTRY_SW+51*7		//1
#define	DAYTAB8_SEG1_SW		DAYTAB8_SEGSNUM_SW+1+3*0	//3
#define	DAYTAB8_SEG2_SW		DAYTAB8_SEG1_SW+3*1			//3
#define	DAYTAB8_SEG16_SW	DAYTAB8_SEG1_SW+3*15		//3
#define	DAYTAB8_SW_CHK		DAYTAB8_SEG1_SW+3*16		//2

#define	TOU_SWITCH_TIME		SEASONS_SW+537				//6 YY/MM/DD/HH/mm/SS  SS=0x00 no use
#define	TOU_SWITCH_T_CHK	TOU_SWITCH_TIME+6			//2
*/

//----- CTPTCHANGE -----------------------------------------------------------
#define CTPTCHANGE1         CTPTCHANGE			// 0x041B
#define CTPTCHANGE1TM       CTPTCHANGE1         //5 YYMMDDHHmm
#define CTPTCHANGE1PT1      CTPTCHANGE1TM+5     //2 xxxx
#define CTPTCHANGE1PT2      CTPTCHANGE1PT1+2    //2 xxxx
#define CTPTCHANGE1CT1      CTPTCHANGE1PT2+2    //2 xxxx
#define CTPTCHANGE1CT2      CTPTCHANGE1CT1+2    //2 xxxx
#define CTPTCHANGE1Pp       CTPTCHANGE1CT2+2    //4 xxxxxxx.x kWh
#define CTPTCHANGE1Pn       CTPTCHANGE1Pp+4     //4 xxxxxxx.x kWh
#define CTPTCHANGE1Rp       CTPTCHANGE1Pn+4     //4 xxxxxxx.x kvarh
#define CTPTCHANGE1Rn       CTPTCHANGE1Rp+4     //4 xxxxxxx.x kvarh
#define CTPTCHANGE1_CHK     CTPTCHANGE1Rn+4     //2 CHK

#define CTPTCHANGE2         CTPTCHANGE1+31
#define CTPTCHANGE2TM       CTPTCHANGE2         //5 YYMMDDHHmm
#define CTPTCHANGE2PT1      CTPTCHANGE2TM+5     //2 xxxx
#define CTPTCHANGE2PT2      CTPTCHANGE2PT1+2    //2 xxxx
#define CTPTCHANGE2CT1      CTPTCHANGE2PT2+2    //2 xxxx
#define CTPTCHANGE2CT2      CTPTCHANGE2CT1+2    //2 xxxx
#define CTPTCHANGE2Pp       CTPTCHANGE2CT2+2    //4 xxxxxxx.x kWh
#define CTPTCHANGE2Pn       CTPTCHANGE2Pp+4     //4 xxxxxxx.x kWh
#define CTPTCHANGE2Rp       CTPTCHANGE2Pn+4     //4 xxxxxxx.x kvarh
#define CTPTCHANGE2Rn       CTPTCHANGE2Rp+4     //4 xxxxxxx.x kvarh
#define CTPTCHANGE2_CHK     CTPTCHANGE2Rn+4     //2 CHK -> 0x0457

//----- COMM_LAST ------------------------------------------------------------
//#define Comm_Num            COMM_LAST         communication times
#define Comm_Num            COMM_LAST           //4  -> 0x0459
#define Comm_Time           Comm_Num+4          //6 YYMMDDHHmmss
#define Comm_kWh_z          Comm_Time+6         //4
#define Comm_kvarh_z        Comm_kWh_z+4        //4
#define Comm_MD_kW_z        Comm_kvarh_z+4      //3
#define Comm_MD_kvar_z      Comm_MD_kW_z+3      //3
#define Comm_CHK            Comm_MD_kvar_z+3    //2 ->0x0471

//----- SYSPARA --------------------------------------------------------------
/*----  Soft SW  (15/15)  -------------------------------------*/
#define 	FuncSW	        	SYSPARA     //function switch ->0x0473
#define		SysSW				FuncSW+2	//system switch
#define     ECK_Close           SysSW+4     //turn off artificial mouth
#define     MeterConstant   	ECK_Close+1      		//3
#define 	En0p1Wh         	MeterConstant+3         //2 10000(0.1Wh) and impulse constant divides maximum common divisor  2BCD
#define 	ImpNum          	En0p1Wh+2  //impulse constant and 10000(0.1Wh) divides maximum common divisor      1 HEX
#define		SW_CHK				ImpNum+1 				//2
/*----  DOT PARA  (7/7)  -------------------------------------*/
#define     EnDot               SW_CHK+2                //2
#define     DOT_CHK             EnDot+2         //2
#define		FACT_MODE			DOT_CHK+2			//2
#define		SYS_CLR_CNT			FACT_MODE+2			//1 -> 0x0488


// add by bnthang
#ifdef SINGLE_PHASE_MULTI_TARIFF
/*----  Para_Back2  141/192 -----------------------------------------------------*/
//4
#define	MD_Para         SYS_CLR_CNT+1			//maximum demand counting period unit min BCD code
#define	MD_BlockTm		MD_Para	+ 1			//
#define	MD_SlidingTm	MD_BlockTm+1	//maximum demand block time unit min BCD code
#define MD_Para_Chk		MD_SlidingTm+1		//demand parameter check code
//67
#define	Disp_ScTab      MD_Para_Chk+4       	////64 rotator displaying chart
#define	Disp_ScNum      Disp_ScTab+64       //rotator displaying number (32 maximum) one byte BCD code
#define	Chk_ScTab       Disp_ScNum+1		//2
//67
#define	Disp_KeyTab     Chk_ScTab+67       //64 inquiry display
#define	Disp_KeyNum     Disp_KeyTab+64      //inquiry display number       (32 maximum)
#define	Chk_KeyTab      Disp_KeyNum+1		//2
//3
#define	DspInv          Chk_KeyTab+67      //rotator time one  byte BCD code
#define	Chk_DspInv		DspInv+1			//check code two bytes


/*----  Para_Back3 79/80 --------------------------------------------------------*/
#define     Meter_Para        	Chk_DspInv + 1          //meter parameter
#define     MeterAddr		  	Meter_Para				//meter address 6
#define     UserNo			  	MeterAddr+6				//user number 6
#define     SeqNo			  	UserNo+6				//device number
#define     PassWord          	SeqNo +6				//level password  12 length
#define		DeviceAddr			PassWord+24				////device address 32 for IEC1107
#define		BillingDate			DeviceAddr+31			//calculating date 10=automatic calculation at the end of a month 1-28=automatic calculate at the appointed date >28 calculate by hand

#define	Clk_Back        BillingDate  + 1         //8 clock 8
#define ClockBuf        Clk_Back		    //clock nickname
#define CLK_GENE        Clk_Back+8          //6 clock correction factor (4+2)
#define PARA_PTCT       CLK_GENE+6          //22 PT,CT first second total variable-ratio PT CT variable-ratio
#define Ram_Pulse		PARA_PTCT+22  		//42 impulse times storage
#define Battery_CUMU    Ram_Pulse+42        //6 battery usage time

#define NET_SEC_IP      Battery_CUMU//AVR_MD_END
#define NET_SEC_IP_END  NET_SEC_IP+6

#define		BillingDateTwo			NET_SEC_IP_END + 1
#define		BillingDateTwoEnd		BillingDateTwo+6

#define PASSNEW       BillingDateTwoEnd + 1
#define PASSNEW_END   PASSNEW+10// 0x

/*----  LOADPROFILEPARA 180/180 -------------------------------------------------*/
//----  Load Info (130/130)  --------------------------------
#define		LoadInfo_			PASSNEW_END + 1		//
#define	LoadInfo1_			LoadInfo_
#define	RecAddr1_			LoadInfo1_				//4
#define	TimeInv1_			RecAddr1_+4				//2
#define	MaxRecNUM1_			TimeInv1_+2				//2
#define	RegNUM1_			MaxRecNUM1_+2			//1
#define	RegID1_				RegNUM1_+1				//7
//#define...... 8 channels in total
#define	LoadInfo_CHK_		LoadInfo_+128			//2
//----  Load InfoRun (50/50)  --------------------------------
#define		LoadInfoRun_		LoadInfo_CHK_+2
#define	LoadInfoRun1_		LoadInfoRun_
#define	ReadPtr1_			LoadInfoRun1_			//2
#define	RecNUM1_			ReadPtr1_+2				//2
#define	RecPtr1_			RecNUM1_+2				//2
//#define...... 8 channels in total
#define	LoadInfoRun_CHK_	LoadInfoRun_+48			//2



#define NEV_CURRFX_CNT  LoadInfoRun_CHK_ + 1 //reverse times
#define NEV_CURRFX_PRT  (NEV_CURRFX_CNT+2)//pointer
#define NEV_CURRFX_CRD  (NEV_CURRFX_PRT+1)//reverse record
//50 bytes, 10 records, each record includes 5 bytes

#define NEV_LOSTU_CNT   (NEV_CURRFX_CRD+10*5)//loss of voltage times
#define NEV_LOSTU_PRT  (NEV_LOSTU_CNT+2)//pointer
#define NEV_LOSTU_CRD   (NEV_LOSTU_PRT + 1)//loss of voltage record
#define NEV_LOSTU_VAL  (NEV_LOSTU_CRD + 10*5)//loss of voltage value

#define NEV_OVERU_CNT   (NEV_LOSTU_VAL+10*6)//overvoltage times
#define NEV_OVERU_PRT   (NEV_OVERU_CNT + 2)
#define NEV_OVERU_CRD   (NEV_OVERU_PRT + 1)//overvoltage records

#define NEV_OVERU_VAL  (NEV_OVERU_CRD + 10*5)//overvoltage value
#define NEV_HDERR_CNT   (NEV_OVERU_VAL+10*6)//firmware error times
#define NEV_HDERR_PRT   (NEV_HDERR_CNT+2)
#define NEV_HDERR_CRD   (NEV_HDERR_PRT+1)//firmware error records
#define NEV_XXERR_CNT   (NEV_HDERR_CRD + 10*5)//phase error times
#define NEV_XXERR_PRT   (NEV_XXERR_CNT + 2)
#define NEV_XXERR_CRD   (NEV_XXERR_PRT + 1)//phase error records
#define NEV_BARERR_CNT  (NEV_XXERR_CRD + 10*5)//died-battery times
#define NEV_BARERR_PRT  (NEV_BARERR_CNT + 2)
#define NEV_BARERR_CRD  (NEV_BARERR_PRT + 1)//died-battery records
#define NEV_OVERI_CNT   (NEV_BARERR_CRD+10*5)//overcurrent times
#define NEV_OVERI_PRT   (NEV_OVERI_CNT + 2)
#define NEV_OVERI_CRD   (NEV_OVERI_PRT + 1)//overcurrent records
#define NEV_OVERI_VAL  (NEV_OVERI_CRD + 10*5)//overcurrent value

/*---- Para_Back5  213/213 ------------------------------------------------------*/
//24
#define     Val_VFailure        NEV_OVERI_VAL + 1          // split-phase threshold value
#define     Val_VOver           Val_VFailure+2      //overvoltage threshold value
#define     Val_VUnder          Val_VOver+2     	//overcurrent threshold value
#define     Val_IOver           Val_VUnder+2     	//overcurrent threshold value
#define     Dly_VFailure        Val_IOver+2         //split-phase delay time
#define     Dly_VOver           Dly_VFailure+1      //overvoltage delay time
#define     Dly_IOver           Dly_VOver+1         //overcurrent delay time
#define		Val_UnbV			Dly_IOver+1			//2
#define		Dly_UnbV			Val_UnbV+2			//1
#define     Chk_Para5           Dly_UnbV+2         //check code


#define NET_IP          Chk_Para5 + 1
#define NET_PORT       NET_IP+6
#define NET_APN        NET_PORT+4
#define NET_NED_       NET_APN+18

#define NET_SEC_IP_STAR NET_SEC_IP
#define NET_SEC_IP_END_ NET_SEC_IP_END


/*************PASSNEW*************************/
#define PASSWORD_NEW     NET_SEC_IP_END_ + 1
#define PASSWORD_NEW_CHK PASSNEW+8
#define PASSWORD_NEW_END PASSWORD_NEW_CHK+2 //reserve 2 check code bytes-> 0x064A


//Meter calibration parameter and metering control register
#define Adj_Para_SYSCON 	PASSWORD_NEW_END 	+ 1
#define Adj_Para_EMUCON		Adj_Para_SYSCON		+ 2
#define Adj_Para_HFCONST	Adj_Para_EMUCON		+ 2
#define Adj_Para_PSTART		Adj_Para_HFCONST	+ 2
#define Adj_Para_QSTART		Adj_Para_PSTART		+ 2
#define Adj_Para_GPQA		Adj_Para_QSTART		+ 2
#define Adj_Para_GPQB		Adj_Para_GPQA		+ 2
#define Adj_Para_PHSA		Adj_Para_GPQB		+ 1
#define Adj_Para_PHSB		Adj_Para_PHSA		+ 1
#define Adj_Para_QPHSCAL	Adj_Para_PHSB		+ 2
#define Adj_Para_APOSA		Adj_Para_QPHSCAL	+ 2
#define Adj_Para_APOSB		Adj_Para_APOSA		+ 2
#define Adj_Para_RPOSA		Adj_Para_APOSB		+ 2
#define Adj_Para_RPOSB		Adj_Para_RPOSA		+ 2
#define Adj_Para_IARMSOS	Adj_Para_RPOSB		+ 2
#define Adj_Para_IBRMSOS	Adj_Para_IARMSOS	+ 2
#define Adj_Para_IBGAIN		Adj_Para_IBRMSOS	+ 2
#define Adj_Para_Kv			Adj_Para_IBGAIN		+	2
#define Adj_Para_Ka			Adj_Para_Kv			+	3
#define Adj_Para_Kb			Adj_Para_Ka			+	3
#endif

//----- EVENTLOG -------------------------------------------------------------
#define	EVENT_COVOP_PTR	EVENTLOG+201+201+201	// -> 0x145B
#define EVENT_COVOP_1	EVENT_COVOP_PTR+1	//5
#define	EVENT_COVOP_2	EVENT_COVOP_PTR+5	//5
#define	EVENT_COVOP_TIMES (EVENT_COVOP_PTR+20*5)
//201
#define	EVENT_COVCL_PTR	EVENT_COVOP_PTR+201	//1
#define	EVENT_COVCL_1	EVENT_COVCL_PTR+1	//5
#define EVENT_COVCL_2	EVENT_COVCL_PTR+5	//5
#define	EVENT_COVCL_TIMES	(EVENT_COVCL_PTR+20*5)
//201
#define	EVENT_MAGIC_PTR	EVENT_COVCL_PTR+201	//1
#define	EVENT_MAGIC_1	EVENT_MAGIC_PTR+1	//5
#define	EVENT_MAGIC_2	EVENT_MAGIC_PTR+5	//5
//441 10Ìõ
#define EVENT_VUnder_PTR    EVENT_MAGIC_PTR+201     //1
#define EVENT_VUnder_1      EVENT_VUnder_PTR+1      //11    mmHHDDMMYYmmHHDDMMYYzz
#define EVENT_VUnder_2      EVENT_VUnder_PTR+12     //11
//441
#define EVENT_VOver_PTR     EVENT_VUnder_PTR+441    //1
#define EVENT_VOver_1       EVENT_VOver_PTR+1       //11
#define EVENT_VOver_2       EVENT_VOver_PTR+12      //11
//441
#define EVENT_OverLoad_PTR  EVENT_VOver_PTR+441     //1
#define EVENT_OverLoad_1    EVENT_OverLoad_PTR+1    //11
#define EVENT_OverLoad_2    EVENT_OverLoad_PTR+12   //11
//441
#define EVENT_LowPF_PTR     EVENT_OverLoad_PTR+441  //1
#define EVENT_LowPF_1       EVENT_LowPF_PTR+1       //11
#define EVENT_LowPF_2       EVENT_LowPF_PTR+12      //11
//441
#define EVENT_IUnder_PTR    EVENT_LowPF_PTR+441     //1
#define EVENT_IUnder_1      EVENT_IUnder_PTR+1      //11
#define EVENT_IUnder_2      EVENT_IUnder_PTR+12     //11 -> 0x1DA6

 //22+2*7//time modification record is modified to 5 pcs  5*7
#define EVENT_MDF_TIME           EVENT_IUnder_PTR+441// ->0x1f53
#define EVENT_MDF_TIME_DATA      EVENT_MDF_TIME+1
#define EVENT_MDF_TIME_COUNT     EVENT_MDF_TIME_DATA+35//-> 0x1f77

 //53 10 pcs  5*10
//53 10Ìõ 5*10
//#define EVENT_RST_CLR           (EVENT_MDF_TIME_COUNT+2+2)//clearing event will clear two more bytes
#define EVENT_RST_CLR           (EVENT_MDF_TIME_COUNT+2+2)// 0x1f7b
#define EVENT_RST_CLR_DATA      (EVENT_RST_CLR+1)
#define EVENT_RST_CLR_COUNT     (EVENT_RST_CLR_DATA+50)
#define EVENT_RST_CLR_END      (EVENT_RST_CLR_COUNT+2)  // 0x1fb0

#endif


