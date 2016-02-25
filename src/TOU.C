#include "..\inc\includes.h"

#ifdef SINGLE_PHASE_MULTI_TARIFF
#include "..\inc\RN8209.h"
ENERGY vse1t_de;
#endif


//20111228Liao Bin
extern unsigned char bill_count;//20111228廖斌
unsigned char bill_rest = 255;
extern unsigned char display_mod;
#define		COM_HIS_CE_LEN		22
const IntCOMMTAB ComHisCETbl[COM_HIS_CE_LEN] = {

0x0000, (char*) LM1_EC_Pp0, EN_R + RS_DFlash + 25, 0x0010, (char*) LM1_EC_Pn0,
		EN_R + RS_DFlash + 25, 0x0020, (char*) LM1_EC_Rp0, EN_R + RS_DFlash
				+ 25, 0x0030, (char*) LM1_EC_Rn0, EN_R + RS_DFlash + 25,
		0x0040, (char*) LM1_EC_Qp0, EN_R + RS_DFlash + 25, 0x0050,
		(char*) LM1_EC_Qn0, EN_R + RS_DFlash + 25,

		0x0060, (char*) LM1_EC_PpL1, EN_R + RS_DFlash + 15, 0x0070,
		(char*) LM1_EC_PnL1, EN_R + RS_DFlash + 15, 0x0080,
		(char*) LM1_EC_RpL1, EN_R + RS_DFlash + 15, 0x0090,
		(char*) LM1_EC_RnL1, EN_R + RS_DFlash + 15, 0x00A0,
		(char*) LM1_EC_QpL1, EN_R + RS_DFlash + 15, 0x00B0,
		(char*) LM1_EC_QnL1, EN_R + RS_DFlash + 15,

		0x00C0, (char*) LM1_EC_Rq1, EN_R + RS_DFlash + 20, 0x00D0,
		(char*) LM1_EC_Rq2, EN_R + RS_DFlash + 20, 0x00E0, (char*) LM1_EC_Rq3,
		EN_R + RS_DFlash + 20, 0x00F0, (char*) LM1_EC_Rq4, EN_R + RS_DFlash
				+ 20,

		0x0100, (char*) LM1_EC_Rq1F1, EN_R + RS_DFlash + 20, 0x0110,
		(char*) LM1_EC_Rq2F1, EN_R + RS_DFlash + 20, 0x0120,
		(char*) LM1_EC_Rq3F1, EN_R + RS_DFlash + 20, 0x0130,
		(char*) LM1_EC_Rq4F1, EN_R + RS_DFlash + 20, 0x01A0, (char*) Mon_Time,
		EN_R + RS_DFlash + 6,
		//empty
		0xffff, (char*) Mon_Time, EN_R + RS_DFlash + 6, //空
		};

#define		COM_HIS_MD_LEN		12
const IntCOMMTAB ComHisMDTbl[COM_HIS_MD_LEN] = { 0x0000, (char*) LM1_MD_Pp,
		EN_R + RS_DFlash + 40, 0x0010, (char*) LM1_MD_Pn,
		EN_R + RS_DFlash + 40, 0x0020, (char*) LM1_MD_Rp,
		EN_R + RS_DFlash + 40, 0x0030, (char*) LM1_MD_Rn,
		EN_R + RS_DFlash + 40, 0x0040, (char*) LM1_MD_Qp,
		EN_R + RS_DFlash + 40, 0x0050, (char*) LM1_MD_Qn,
		EN_R + RS_DFlash + 40, 0x0060, (char*) LM1_MD_Rq1, EN_R + RS_DFlash
				+ 40, 0x0070, (char*) LM1_MD_Rq2, EN_R + RS_DFlash + 40,
		0x0080, (char*) LM1_MD_Rq3, EN_R + RS_DFlash + 40, 0x0090,
		(char*) LM1_MD_Rq4, EN_R + RS_DFlash + 40, 0x00A0, (char*) Mon_Time,
		EN_R + RS_DFlash + 6, 0xffff, (char*) Mon_Time, EN_R + RS_DFlash + 6,

};

const signed char MonTab[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30,
		31 };
const signed int DayTab[13] = { 0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273,
		304, 334 };
const signed int DayTabR[13] = { 0, 0, 31, 60, 91, 121, 152, 182, 213, 244,
		274, 305, 335 };

unsigned int gRTCOutCnt = 0;

/*****************************************************************
 Real Time Clock
 *****************************************************************/
//get clock amendment gene,when resetting, perform this once a day
void Init_CLK_Gene(void) {
	signed long lngTmp;
#ifdef NO_FRAM
	E2P_Read((char*) &lngTmp, CLK_GENE, 4);
#else
	FRAM_Read((char*) &lngTmp, CLK_GENE, 4);
#endif
	if ((lngTmp != 0) && (lngTmp <= 3278000) && (lngTmp >= -3278000))
		ClkC.CorrectGeneBK = 3276800 / (lngTmp - 3276800);
	else
		ClkC.CorrectGeneBK = 0;

	if (ClkC.CorrectGeneBK > 0)
		ClkC.CorrectGene = ClkC.CorrectGeneBK;
	else if (ClkC.CorrectGeneBK < 0)
		ClkC.CorrectGene = -ClkC.CorrectGeneBK;
}
//**************************************
//time reading
//*************************************
void Clock(void) {
	if (((Clk.Sec[0] & 0x0F) == 0x05) || ((Clk.Sec[0] & 0x0F) == 0x00))
		Flag.Clk |= F_5S;

	{
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
	}
	{
		static unsigned char old_min = 0xFF;
		//minute
		if (old_min == Clk.Min[0]) {
			return;
		}//分
		old_min = Clk.Min[0];
		Flag.Clk |= F_Min;
		Clk.Check = ChkNum(Clk.Min, 6);
#ifdef NO_FRAM
#else
		FRAM_Write( ClockBuf, (char*) Clk.Min, 8);
		FRAM_Write( ClockBuf + FRAMBAK, (char*) Clk.Min, 8);
#endif
		//hour
		{//
			static unsigned char old_hour = 0xFF;
			if (old_hour != Clk.Hour[0]) {
				old_hour = Clk.Hour[0];
				Flag.Clk |= F_Hour;
				//day*******
				{//
					static unsigned char old_day = 0xFF;
					if (old_day != Clk.Day[0]) {
						old_day = Clk.Day[0];
						Flag.Clk |= F_Day;
					}
				}//

			}
		}//***************
		//DayTableCHG();//**********test
	}
}
//**************************************
//get rate
//*************************************
char GetFeeNum(void) {
	unsigned int CurrentTM = 0x0000;
	unsigned int NextSegTM = 0x0000;
	unsigned int NextSegTM2 = 0x0000;

	CurrentTM = Clk.Hour[0];
	CurrentTM <<= 8;
	CurrentTM += Clk.Min[0];
	//the condition that the current time is less than the first period when in the last period
	if (Fee.CurrentDTSeg == Fee.CurrentDTSegs) //
	{
		//and the current period numbers of period table are more than one,or no need retest
		if (Fee.CurrentDTSegs > 1) //
		{
			//get the time of next period
			E2P_Read(Buffer,
			DAYTAB_ENTRY + (Fee.CurrentDT - 1) * 51 + 1 + (1 - 1) * 3, 6); //

			NextSegTM = Buffer[0];
			NextSegTM <<= 8;
			NextSegTM += Buffer[1];
			NextSegTM2 = Buffer[3];
			NextSegTM2 <<= 8;
			NextSegTM2 += Buffer[4];

			//current time >=the time of the first period
			if ((CurrentTM >= NextSegTM) && (CurrentTM < NextSegTM2))//
			{

				Fee.PreviousFee = Fee.CurrentFee;

				Fee.CurrentFee = Buffer[2];
				Fee.CurrentDTSeg = 1;
				if (Fee.PreviousFee != Fee.CurrentFee)
					Flag.Fee |= (FeeSW_DL + FeeSW_XL);
				goto RTCURRENTFEE;
			}
		}
	}
	if (Fee.CurrentDTSeg < Fee.CurrentDTSegs) {
		//get the time of next period
		E2P_Read(
				Buffer,
				DAYTAB_ENTRY + (Fee.CurrentDT - 1) * 51 + 1 + (Fee.CurrentDTSeg
						- 1 + 1) * 3, 3); //


		NextSegTM = Buffer[0];
		NextSegTM <<= 8;
		NextSegTM += Buffer[1];
		if (CurrentTM >= NextSegTM)		{
			if ((Buffer[2] > 0) && (Buffer[2] <= 4)) {
				Fee.PreviousFee = Fee.CurrentFee;
				Fee.CurrentFee = Buffer[2];
				if (Fee.PreviousFee != Fee.CurrentFee)
					Flag.Fee |= (FeeSW_DL + FeeSW_XL);
			}
			Fee.CurrentDTSeg++;
		}
	}

	RTCURRENTFEE: if ((Fee.CurrentFee == 0) || (Fee.CurrentFee > 0x04))
		Fee.CurrentFee = 1;
	return Fee.CurrentFee;
}

/*******************************************************************************
 //function name:DayTableCHG
 //description:period table test
 //input:
 //output:
 //return:
 //note:special holidays, season table, week table, day period meter
 *******************************************************************************/
char DayTableCHG(void) {
	unsigned char Num = 0x00;
	unsigned char i;
	unsigned char RLT = 0x00;
	unsigned int StartTM = 0x0000, EndTM = 0x0000, CurrentTM = 0x0000;
	//search exception day
	//look up special holiday
	E2P_Read((char *) &Num, EXPDAYSNUM, 1);
	if (Num == 255) {
		Num = 0;
	}
	for (i = 0; i < Num; i++) {
		E2P_Read(Buffer, EXPDAY1 + i * 4, 4);
		if ((Buffer[0] == 0xAA && Buffer[1] == Clk.Mon[0] && Buffer[2]
				== Clk.Day[0]) || (Buffer[0] == Clk.Year[0] && Buffer[1]
				== Clk.Mon[0] && Buffer[2] == Clk.Day[0])) {
			RLT = BCD_Byte(Buffer[3]); //RLT is Day Table
			break;
		}
	}
	//RLT=0x02;//test*********************
	//search Season Table right along
	//look up season table
	if (RLT == 0x00) {
		unsigned long curtm = 0, statm = 0;//endtm = 0;
		curtm = Clk.Year[0];
		curtm <<= 8;
		curtm += Clk.Mon[0];
		curtm <<= 8;
		curtm += Clk.Day[0];
		E2P_Read((char *) &Num, SEASONSNUM, 1);
		if (Num > 4)
			Num = 0;
		for (i = Num; i > 0; i--) {
			E2P_Read(Buffer, SEASON1 + (i - 1) * 4, 4);
			statm = Buffer[0];
			statm <<= 8;
			statm += Buffer[1];
			statm <<= 8;
			statm += Buffer[2];
			if ((curtm >= statm) && (statm != 0)) {
				//RLT is Week Table week table
				RLT = BCD_Byte(Buffer[3]); //
				break;
			}

		}
		//no device use time table, default to read week table 1
		if ((RLT == 0) || (RLT > 16))
			RLT = 1;//

		if (RLT >= 1) {
			E2P_Read(Buffer, WEEKTAB1 + 7 * (RLT - 1), 7);
			for (i = 0; i < 7; i++) {
				if (((unsigned char) 0x01 << i) >= Clk.Week[0]) {
					//RLT is Day Table day period table
					RLT = BCD_Byte(Buffer[i]); //
					break;
				}
			}
		}
		if ((RLT > 16) || (RLT == 0)) {
			Fee.PreviousFee = 0;
			Fee.CurrentFee = 0;
			Fee.CurrentDT = 0;
			Fee.CurrentDTSegs = 0;
			Fee.CurrentDTSeg = 0;
			//period is not set
			goto RTFEENUM;
		}
	}
	E2P_Read((char *) &Num, DAYTAB_SEGSNUM + (RLT - 1), 1);

	CurrentTM = Clk.Hour[0];
	CurrentTM <<= 8;
	CurrentTM += Clk.Min[0];
	for (i = 0; i < 16; i++) {
		E2P_Read(Buffer, DAYTAB_ENTRY + ((RLT - 1) * 51) + 1 + (i * 3), 6);

		StartTM = Buffer[0];
		StartTM <<= 8;
		StartTM += Buffer[1];
		EndTM = Buffer[3];
		EndTM <<= 8;
		EndTM += Buffer[4];

		//in the last period
		if (i == 0 && CurrentTM < StartTM) //在最后一个时段			//current time < the first seg
		{

			//so current time is in the last seg
			unsigned char j = 1;
			//read the last time period
			E2P_Read(Buffer, DAYTAB_ENTRY + (RLT - 1) * 51 + 1 + (Num - j) * 3,
					3);//

			while (((Buffer[2] == 0) || (Buffer[2] > 4)) && (j < Num)) {
				j++;
				//read the last time period
				E2P_Read(Buffer,
				DAYTAB_ENTRY + (RLT - 1) * 51 + 1 + (Num - j) * 3, 3);//
			}

			if (((Buffer[2] > 0) && (Buffer[2] <= 4)) && (j <= Num)) {
				Fee.PreviousFee = Fee.CurrentFee;
				if (Fee.PreviousFee > 4)
					Fee.PreviousFee = 0;

				Fee.CurrentFee = Buffer[2]; //Buffer[2] is Fee Num
				Fee.CurrentDT = RLT;
				Fee.CurrentDTSegs = Num - j;
				Fee.CurrentDTSeg = Num - j;
				if (Fee.PreviousFee != Fee.CurrentFee)
					Flag.Fee |= (FeeSW_DL + FeeSW_XL);
				break;
			}

			//break;
		}
		if ((CurrentTM >= StartTM && CurrentTM < EndTM) || ((CurrentTM
				>= StartTM) && (EndTM == 0))) {

			if ((Buffer[2] > 0) && (Buffer[2] <= 4)) {
				Fee.PreviousFee = Fee.CurrentFee;
				if (Fee.PreviousFee > 4)
					Fee.PreviousFee = 0;
				Fee.CurrentFee = Buffer[2];
				Fee.CurrentDT = RLT;
				Fee.CurrentDTSegs = Num;
				Fee.CurrentDTSeg = i + 1;
				if (Fee.PreviousFee != Fee.CurrentFee)
					Flag.Fee |= (FeeSW_DL + FeeSW_XL);
				break;
			}
		}
	}

	RTFEENUM: if ((Fee.CurrentFee == 0x00) || (Fee.CurrentFee > 0x04)) {
		Fee.PreviousFee = 0;
		Fee.CurrentFee = 1;
		Fee.CurrentDT = 0;
		Fee.CurrentDTSegs = 0;
		Fee.CurrentDTSeg = 0;
	}
	return Fee.CurrentFee;
}

void Cali_Meter(void) {

}
//**************************************
//frozen test by hand
//*************************************
void CheckManualBill(void) {

	int8u ucTmp;

	if ((Flag.Power & F_PwrUp) == 0x00)
		return;

	if (IEC_Comm.ProgCnt > 0) {
#if 0
		//manual demand settlement
		if ((P6IN & P_Key1) && (~P6IN & P_Key2)) // 需量手动结算
		{
			if ((RunDly.MBillDely < MBillDelyTM) || (RunDly.PowerDely < PowerDelyTM))
			return;
			else
			http://www.baidu.com/CaliTmr.Key4Tmr++;
		}
		else
		{	CaliTmr.Key4Tmr=0;}
#endif        

		//electricity quantity   manual demand settlement
		if (!BILL_REST()) {

			if ((RunDly.DLBillDely < DLBillDelyTM) || (RunDly.PowerDely
					< PowerDelyTM)) {
				//bill_rest = 0x0F;
				return;
			} else {
				CaliTmr.Key2Tmr++;
				bill_rest = 1;
			}
			//CaliTmr.Key2Tmr = 5;//******************
		} else {
			CaliTmr.Key2Tmr = 0;
		}

#if 0        
		//manual demand settlement
		if ( CaliTmr.Key4Tmr>4 )
		{
			Flag.Fee |= F_BillMD;
			CaliTmr.Key4Tmr=0;
		}
#endif		
		//electricity quantity     manual demand settlement
		if (CaliTmr.Key2Tmr > 4) {
			//	unsigned char BDate=0x00;
			bill_rest = 2;
			E2P_Read((char *) &ucTmp, SysSW, 1);

			if (ucTmp & 0x01)//****************************
			{
				Flag.Fee |= F_BillAll;
				bill_rest = 3;
			}
			CaliTmr.Key2Tmr = 0;
		}
	}

}

unsigned char CheckBill(void) {
	/*
	 unsigned char BDate;
	 unsigned char DayNow;

	 DayNow = Clk.Day[0];
	 BDate = 0x00;
	 FRAM_Read((char *)&BDate, BillingDate, 1);

	 //manual settlement
	 if (BDate > 0x28) return(BDate); //手动结算
	 if (BDate == 0x00 && (DayNow != 0x01)) return(BDate);

	 //_BCD1DEC((char *)&DayNow);
	 if (BDate != 0x00 && BDate != DayNow ) return(BDate);

	 if (Clk.Hour[0]!=0x00 && Clk.Min[0] != 0x00) return(BDate);
	 */

	return (0);
}

//**************************************
//automatic frozen test
//*************************************
unsigned char AutoSaveTime(void) {
	// char HistPtr;
	///   unsigned long Addr;
	int Month, CHour, LHour, JHour;
	YMDhms_T LMon_Time;

	int JHour2, JHour3;
	unsigned char cnt = 0;

	if ((Flag.Power & F_PwrUp) == 0x00)
		return (0);
	/*
	 FRAM_Read( &HistPtr, LastMonPtrLoca, 1);
	 Addr = LM1_EC + HistPtr * SIZE_MONBLK;
	 Flash_Read( (int8u*)&LMon_Time, Addr+Mon_Time, 6 );
	 */
#ifdef NO_FRAM
#else
	//write time mark
	FRAM_Read((char*) &LMon_Time, BILLYMDHms, 6); //写时标
#endif

	Month = BCD_Byte(Clk.Year[0]) * 12 + BCD_Byte(Clk.Mon[0]);
	Month -= (BCD_Byte(LMon_Time.Year[0]) * 12 + BCD_Byte(LMon_Time.Mon[0]));
	CHour = BCD_Byte(Clk.Day[0]) * 24 + BCD_Byte(Clk.Hour[0]);
	LHour = BCD_Byte(LMon_Time.Day[0]) * 24 + BCD_Byte(LMon_Time.Hour[0]);

#ifdef NO_FRAM
	E2P_Read(&Buffer[0], BillingDate, 1);
#else
	FRAM_Read(&Buffer[0], BillingDate, 1);
#endif

	if ((Buffer[0] == 0) || (Buffer[0] > 0x28)) {
		//the first frozen is defaulted on the first date of each month
		Buffer[0] = 1;//
	}
	JHour = (int) BCD_Byte(Buffer[0]) * 24;
	Buffer[1] = Buffer[0];

#ifdef NO_FRAM
#else
	FRAM_Read(&Buffer[0], BillingDate2, 1);
#endif
	if ((Buffer[0] == 0) || (Buffer[0] > 0x28) || (Buffer[0] < Buffer[1])) {
		//the first frozen is defaulted on the first date of each month
		Buffer[0] = Buffer[1];//
	}
	JHour2 = (int) BCD_Byte(Buffer[0]) * 24;
	Buffer[1] = Buffer[0];

#ifdef NO_FRAM
#else
	FRAM_Read(&Buffer[0], BillingDate3, 1);
#endif
	if ((Buffer[0] == 0) || (Buffer[0] > 0x28) || (Buffer[0] < Buffer[1])) {
		//the first frozen is defaulted on the first date of each month
		Buffer[0] = Buffer[1];//
	}
	JHour3 = (int) BCD_Byte(Buffer[0]) * 24;

	Buffer[0] = 0x00;
	Buffer[1] = 0x00;

	if (Month == 0) {
		if (((CHour >= JHour) && (LHour < JHour))) {
			cnt++;
		}
		if (((CHour >= JHour2) && (LHour < JHour2))) {
			cnt++;
		}
		if (((CHour >= JHour3) && (LHour < JHour3))) {
			cnt++;
		}

	} else if (Month > 3) {
		cnt++;
	} else if (Month > 0) {
		cnt += ((Month - 1) * 3);

		if ((LHour < JHour3) && (LHour >= JHour2)) {
			cnt += 1;
		} else if ((LHour < JHour2) && (LHour >= JHour)) {
			cnt += 2;
		} else if ((LHour < JHour)) {
			cnt += 3;
		}

		if (((CHour >= JHour))) {
			cnt++;
		}
		if (((CHour >= JHour2))) {
			cnt++;
		}
		if (((CHour >= JHour3))) {
			cnt++;
		}

	}

	return cnt;

}
//**************************************
//reset demand 
//*************************************
void ResetMD(void) {
	WDTClr();
#ifdef NO_FRAM

#else
	MEM_Clr(MD_Pp, 42 - 2, Mem_FRAM);
	MEM_Clr(MD_Pp + FRAMBAK, 42 - 2, Mem_FRAM);
	MEM_Clr(MD_Pn, 42 - 2, Mem_FRAM);
	MEM_Clr(MD_Pn + FRAMBAK, 42 - 2, Mem_FRAM);
	MEM_Clr(MD_Qp, 42 - 2, Mem_FRAM);
	MEM_Clr(MD_Qp + FRAMBAK, 42 - 2, Mem_FRAM);
	MEM_Clr(MD_Qn, 42 - 2, Mem_FRAM);
	MEM_Clr(MD_Qn + FRAMBAK, 42 - 2, Mem_FRAM);
	MEM_Clr(MD_Rp, 42 - 2, Mem_FRAM);
	MEM_Clr(MD_Rp + FRAMBAK, 42 - 2, Mem_FRAM);
	MEM_Clr(MD_Rn, 42 - 2, Mem_FRAM);
	MEM_Clr(MD_Rn + FRAMBAK, 42 - 2, Mem_FRAM);
	WDTClr();
	MEM_Clr(MD_Rq1, 42 - 2, Mem_FRAM);
	MEM_Clr(MD_Rq1 + FRAMBAK, 42 - 2, Mem_FRAM);
	MEM_Clr(MD_Rq2, 42 - 2, Mem_FRAM);
	MEM_Clr(MD_Rq2 + FRAMBAK, 42 - 2, Mem_FRAM);
	MEM_Clr(MD_Rq3, 42 - 2, Mem_FRAM);
	MEM_Clr(MD_Rq3 + FRAMBAK, 42 - 2, Mem_FRAM);
	MEM_Clr(MD_Rq4, 42 - 2, Mem_FRAM);
	MEM_Clr(MD_Rq4 + FRAMBAK, 42 - 2, Mem_FRAM);
#endif
	WDTClr();
	Flag.MDClrFlag = 1;

	MDParaInit();
	Flag.IntTmStart |= MDSTART;
}
//**************************************
//obtain the address that the frozen data saved
//*************************************
int8u GetBillAdr(int8u id, int16u da, int8u Type, int32u *pAddr, int16u *Info) {
	unsigned char i;

	unsigned long Addr;

	//unsigned int  Info, Len=0xFFFF;
	//char MemType;
	//unsigned char EVENT_Ptr;
	unsigned char LMPtr, ucLMNum;

	if (Type == 0) {
		for (i = 0; i < COM_HIS_CE_LEN; i++) {
			if (ComHisCETbl[i].ComID == da) {
				break;
			}
		}
		if (i == COM_HIS_CE_LEN) {
			return FALSE;
		}
		Addr = (unsigned int) ComHisCETbl[i].Addr;
		*Info = ComHisCETbl[i].ComInfo;
		//pointer of electricity quantity
#ifdef NO_FRAM
#else
		FRAM_Read((char*) &LMPtr, LastMonPtrLoca, 1); //
#endif

	} else {
		for (i = 0; i < COM_HIS_MD_LEN; i++) {
			if (ComHisMDTbl[i].ComID == da) {
				break;
			}
		}
		if (i == COM_HIS_MD_LEN) {
			return FALSE;
		}
		Addr = (unsigned int) ComHisMDTbl[i].Addr;
		*Info = ComHisMDTbl[i].ComInfo;
		//pointer of electricity quantity 
#ifdef NO_FRAM
#else
		FRAM_Read((char*) &LMPtr, LastMonPtrMDLoca, 1); //
#endif
	}

	ucLMNum = (LMPtr >> 4) & 0x0f;
	LMPtr &= 0x0f;

	if (LMPtr > 0) {
		LMPtr--;
	} else {
		LMPtr = 11;
	}

	if (id < ucLMNum) {
		if (id <= LMPtr) {
			LMPtr -= id;
		} else {
			LMPtr = LMPtr + 12 - id;
		}
		Addr = LMPtr * SIZE_MONBLK + Addr;

		*pAddr = Addr;
		return TRUE;
	} else {
		return FALSE;
	}
}
//**************************************
//data frozen 
//*************************************
void BillALL(void) {
	unsigned char chTmp[3], ucNum, ucPtr, i;
	unsigned int intTmp;
	unsigned long destAdr;
	YMDhms_T LMon_Time, NMon_Time;
	int CHour, LHour, JHour;
	int JHour2, JHour3;
	char DjFlag = 0;

	//it can perform the settlement x minutes later after power on
	if (RunDly.PowerDely < PowerDelyTM)
		return; //
	if (!(Flag.Fee & F_BillAll)) {
		bill_count = 0;
		return;
	}

	if (bill_count > 0) {
		DjFlag = 1;
	}
	if (bill_count > 1) {
		bill_count--;
	} else {
		Flag.Fee &= ~(F_BillAll);
		bill_count = 0;
	}
	WDTClr();
	RunDly.MBillDely = 0;
	RunDly.DLBillDely = 0;

	chTmp[2] = 0x33;

#ifdef NO_FRAM
	WDTClr();
#else
	//it must clear this byte after settlement
	MEM_DBWrite(LastBillOK, (char*) &chTmp[2], 1, Mem_FRAM); //
	WDTClr();
	FRAM_Read((char*) &intTmp, BILLCnt, 2);
	_BCD2INC((char*) &intTmp);
	WDTClr();
	FRAM_Write(BILLCnt, (char*) &intTmp, 2);
#endif

	//write time mark
	// FRAM_Write(BILLYMDHms, &Clk.Sec[0], 6);                         //写时标
	//write time mark
#ifdef NO_FRAM

#else
	FRAM_Read((char*) &LMon_Time, BILLYMDHms, 6); //
#endif
	LHour = (int) BCD_Byte(LMon_Time.Day[0]) * 24 + (int) BCD_Byte(
			LMon_Time.Hour[0]);
	NMon_Time.Year[0] = LMon_Time.Year[0];
	NMon_Time.Mon[0] = LMon_Time.Mon[0];
	NMon_Time.Day[0] = LMon_Time.Day[0];

	//CHour = BCD_Byte( Clk.Day[0] )*24 + BCD_Byte( Clk.Hour[0] );
#ifdef NO_FRAM

#else
	FRAM_Read(&Buffer[0], BillingDate, 1);
#endif
	if ((Buffer[0] == 0) || (Buffer[0] > 0x28)) {
		//the first frozen is defaulted on the first date of each month
		Buffer[0] = 1;//
	}
	JHour = (int) BCD_Byte(Buffer[0]) * 24;
	Buffer[1] = Buffer[0];

#ifdef NO_FRAM

#else
	FRAM_Read(&Buffer[0], BillingDate2, 1);
#endif
	if ((Buffer[0] == 0) || (Buffer[0] > 0x28) || (Buffer[0] < Buffer[1])) {
		//the first frozen is defaulted on the first date of each month
		Buffer[0] = Buffer[1];//
	}
	JHour2 = (int) BCD_Byte(Buffer[0]) * 24;
	Buffer[1] = Buffer[0];

#ifdef NO_FRAM

#else
	FRAM_Read(&Buffer[0], BillingDate3, 1);
#endif
	if ((Buffer[0] == 0) || (Buffer[0] > 0x28) || (Buffer[0] < Buffer[1])) {
		//the first frozen is defaulted on the first date of each month
		Buffer[0] = Buffer[1];//
	}
	JHour3 = (int) BCD_Byte(Buffer[0]) * 24;

	Buffer[0] = 0x00;
	Buffer[1] = 0x00;
	if (bill_count > 0) {
		if ((LHour >= JHour3)) {
			LMon_Time.Mon[0] = BCD_Byte(LMon_Time.Mon[0]) + 1;
			if (LMon_Time.Mon[0] > 12) {
				LMon_Time.Mon[0] = 1;
				LMon_Time.Year[0] = Byte_BCD(BCD_Byte(LMon_Time.Year[0]) + 1);
			}
			LMon_Time.Mon[0] = Byte_BCD(LMon_Time.Mon[0]);
			LMon_Time.Day[0] = Byte_BCD(JHour / 24);
			LMon_Time.Hour[0] = 0;
			LMon_Time.Min[0] = 0;
			LMon_Time.Sec[0] = 0;
		} else if (LHour >= JHour2) {
			LMon_Time.Day[0] = Byte_BCD(JHour3 / 24);
			LMon_Time.Hour[0] = 0;
			LMon_Time.Min[0] = 0;
			LMon_Time.Sec[0] = 0;
		} else if (LHour >= JHour) {
			LMon_Time.Day[0] = Byte_BCD(JHour2 / 24);
			LMon_Time.Hour[0] = 0;
			LMon_Time.Min[0] = 0;
			LMon_Time.Sec[0] = 0;
		} else if (LHour < JHour) {
			LMon_Time.Day[0] = Byte_BCD(JHour / 24);
			LMon_Time.Hour[0] = 0;
			LMon_Time.Min[0] = 0;
			LMon_Time.Sec[0] = 0;
		}

		if (((unsigned long) BCD_Byte(LMon_Time.Year[0]) * (unsigned long) 12
				* (unsigned long) 30 + (unsigned long) BCD_Byte(
				LMon_Time.Mon[0]) * (unsigned long) 30
				+ (unsigned long) BCD_Byte(LMon_Time.Day[0]))
				> ((unsigned long) BCD_Byte(Clk.Year[0]) * (unsigned long) 12
						* (unsigned long) 30 + (unsigned long) BCD_Byte(
						Clk.Mon[0]) * (unsigned long) 30
						+ (unsigned long) BCD_Byte(Clk.Day[0]))) {
			Flag.Fee &= ~(F_BillAll);
			bill_count = 0;
			return;
		} else {
#ifdef NO_FRAM

#else
			//write time mark, add settlement
			FRAM_Write(BILLYMDHms, &LMon_Time.Sec[0], 6); //
#endif
		}
#ifdef NO_FRAM

#else
		FRAM_Read((char*) &LMon_Time, BILLYMDHms, 6);
#endif
		if ((NMon_Time.Year[0] == LMon_Time.Year[0]) && (NMon_Time.Mon[0]
				== LMon_Time.Mon[0]) && (NMon_Time.Day[0] == LMon_Time.Day[0]))
			return;

	}
	//the last time to add frozen
	else if (DjFlag == 1)//
	{
		CHour = BCD_Byte(Clk.Day[0]) * 24;
		LMon_Time.Year[0] = Clk.Year[0];
		LMon_Time.Mon[0] = Clk.Mon[0];
		if (CHour >= JHour3) {
			LMon_Time.Day[0] = Byte_BCD(JHour3 / 24);
			LMon_Time.Hour[0] = 0;
			LMon_Time.Min[0] = 0;
			LMon_Time.Sec[0] = 0;
		} else if (CHour >= JHour2) {
			LMon_Time.Day[0] = Byte_BCD(JHour2 / 24);
			LMon_Time.Hour[0] = 0;
			LMon_Time.Min[0] = 0;
			LMon_Time.Sec[0] = 0;
		} else if (CHour >= JHour) {
			LMon_Time.Day[0] = Byte_BCD(JHour / 24);
			LMon_Time.Hour[0] = 0;
			LMon_Time.Min[0] = 0;
			LMon_Time.Sec[0] = 0;
		} else {
			if (LMon_Time.Mon[0] == 0x01) {

				LMon_Time.Mon[0] = 0x12;
				LMon_Time.Year[0] = Byte_BCD(BCD_Byte(LMon_Time.Year[0]) - 1);
				if (LMon_Time.Year[0] > 0x99) {
					LMon_Time.Year[0] = 0;
				}
			} else {
				LMon_Time.Mon[0] = Byte_BCD(BCD_Byte(LMon_Time.Mon[0]) - 1);
			}
			LMon_Time.Day[0] = Byte_BCD(JHour3 / 24);
			LMon_Time.Hour[0] = 0;
			LMon_Time.Min[0] = 0;
			LMon_Time.Sec[0] = 0;
		}
		//write time mark, add settlement
#ifdef NO_FRAM

#else
		FRAM_Write(BILLYMDHms, &LMon_Time.Sec[0], 6); //
		FRAM_Read((char*) &LMon_Time, BILLYMDHms, 6);
#endif
		if ((NMon_Time.Year[0] == LMon_Time.Year[0]) && (NMon_Time.Mon[0]
				== LMon_Time.Mon[0]) && (NMon_Time.Day[0] == LMon_Time.Day[0]))
			return;
	}
	//frozen by hand
	else//
	{
		//write time mark, current time
#ifdef NO_FRAM

#else
		FRAM_Write(BILLYMDHms, &Clk.Sec[0], 6); //
#endif
	}

	WDTClr();
#ifdef NO_FRAM

#else
	intTmp = ChkMem(EC_Back1, SIZE_EC_MONBLK - 2, Mem_FRAM);
	FRAM_Write(MON_EC_CHK, (char*) &intTmp, 2);
	intTmp = ChkMem(MD_Back1, SIZE_MD_MONBLK - 2, Mem_FRAM);
	FRAM_Write(MON_MD_CHK, (char*) &intTmp, 2);
	WDTClr();
	FRAM_Read((char*) &chTmp[0], LastMonPtrLoca, 2);
#endif
	ucNum = (chTmp[0] >> 4) & 0x0f;
	ucPtr = (chTmp[0]) & 0x0f;

	if (ucPtr > 11) {
		ucPtr = 0;
	}
	WDTClr();
	destAdr = LASTMON_DATA + SIZE_MONBLK * ucPtr + LM_EC_;
	FRAM2Flash(destAdr, EC_Back1, SIZE_EC_MONBLK);
	WDTClr();
	destAdr = LASTMON_DATA + SIZE_MONBLK * ucPtr + LM_MD_;
	FRAM2Flash(destAdr, MD_Back1, SIZE_MD_MONBLK);
	WDTClr();
	for (i = 0; i < 2; i++) {
		ucNum = (chTmp[i] >> 4) & 0x0f;
		ucPtr = (chTmp[i]) & 0x0f;

		ucPtr++;
		if (ucPtr > 11) {
			ucPtr = 0;
		}
		if (ucNum < 12) {
			ucNum++;
		}
		chTmp[i] = ((ucNum << 4) & 0xf0) + (ucPtr & 0x0f);
	}

	ResetMD();
	WDTClr();
	chTmp[2] = 0x00;
	//clear LastBillOK after finished the settlementand rewrite the settlement pointer of 12 months
#ifdef NO_FRAM

#else
	MEM_DBWrite(LastMonPtrLoca, (char*) &chTmp[0], 3, Mem_FRAM); //
#endif

}

//**************************************
//use time of battery add 1
//*************************************
void CumuBATTERY(void) {
	if ((Flag.Power & F_PwrUp) == F_PwrUp)
		return;
#ifdef NO_FRAM

#else
	FRAM_Read(&Buffer[0], Battery_CUMU, 4);
	_BCD4INC(&Buffer[0]);
	MEM_DBWrite(Battery_CUMU, &Buffer[0], 4, Mem_FRAM);
#endif
}

extern void clr_log(char i);
//the record state of power on zero clearing events
extern void InitNewLog(void);//
//**************************************
//clear fully 0 functions
//*************************************
void fClearAllData(void) {
	unsigned int uiTmp;
	unsigned char ucTmp;
	static unsigned char rest_flag = 0;
	if (SYC_CLR() != 0) {
		rest_flag = 1;
	}

	//zero clearing of hardware or software
	if (((IEC_Comm.ProgCnt > 0) && (((SYC_CLR() == 0) && (rest_flag == 1))
			|| ((Flag.ClearAllData == 0xAB)))) || (Flag.ClearAllData == 0xAA))//硬件清0或软件清0
	{
		rest_flag = 0;
		E2P_Read((char *) &ucTmp, SysSW, 1);
		if ((ucTmp & 0x02) == 0x00) {
			return;
		}

		if (Flag.ClearAllData == 0xAA) {
			E2P_Read((char*) &ucTmp, SysSW + 3, 1);

			if (ucTmp & 0x01) {
				return;
			}
		}

		Flag.ClearAllData = 0xAB;
	} else {
		return;
	}

	E2P_Read((char*) &uiTmp, FACT_MODE, 2);
	if (uiTmp == 0xf001) {
		ucTmp = 0;
		E2P_Write(SYS_CLR_CNT, (char*) &ucTmp, 1);
	}

	//total clear data
#ifdef SINGLE_PHASE_MULTI_TARIFF
//RN8209SPI
#else
	ATT7022_RAMClear();
#endif
	PulseClear();
	MDParaInit();
	MEM_DBClear(0xFF);

#ifdef NO_FRAM

#else
	//clear power on and down events
	MEM_Clr(EVENT_POFF_PTR, 300, Mem_FRAM);//

	//write frozen time node
	FM_Write(BILLYMDHms, (int8u*) &Clk.Sec[0], 6);//

	memset(&Buffer[0], 0x00, 48);
	//clear frozen data
	FM_Write(LastMonPtrLoca, (int8u*) Buffer, 2); //
	//clear frozen data
	FM_Write(LastMonPtrMDLoca, (int8u*) Buffer, 2); //
#endif

	WDTClr();
	memset(&Buffer[0], 0x00, 48);

#ifdef NO_FRAM

#else
	FRAM_Write(LOAD_DATE_SET_COUNT, &Buffer[0], 48);
#endif
	WDTClr();
	{
		unsigned int time_count = 0;
		register char * ptr;
		unsigned short i = 0;
		//read original zero clearing times
		E2P_Read((char*) &time_count, EVENT_RST_CLR_COUNT, 2);//
		time_count++;
		if (time_count == 0)
			time_count = 1;
		//save zero clearing times
		E2P_Write(EVENT_RST_CLR_COUNT, (char*) &time_count, 2);//
		time_count = (time_count - 1) % 10;
		E2P_Read((char*) &Buffer[0], EVENT_RST_CLR_DATA, 50);

		ptr = Clk.Year;
		for (i = 0; i < 5; i++) {
			Buffer[i + 50] = *(ptr--);
		}

		//memcpy(Buffer+50,(char*)&Clk.Sec[0],5);
		E2P_Write(EVENT_RST_CLR_DATA, Buffer + 5, 50);
	}
	{
		char i = 0;
		for (i = 0; i < LOG_MAX; i++) {
			clr_log(i);
		}

	}

	Flag.ClearAllData = 0x00;
	Flag.IntTmStart |= MDSTART;
}

extern unsigned char net_rest_time;
extern unsigned char pw_on_cout;
const unsigned char ORDERABC[] = "ABCBCACABAAABBBCCC";

/*******************************************************************************
 *function name:Time_TH
 *description:various functional test to deal with main function, the mission is distinguished by time period of test, which is divided into the following types:
 0.5S performance
 1S performance
 5S performance
 1min performance
 1hour performance
 1day performance
 *input:
 *output:
 *return:
 *note:
 *******************************************************************************/
void Time_TH(void) {
	char i;
	//recheck the meter calibration parameter flag
	static char flag_xb = 0;//
	//load curve save the checked flag
	static char flag_fh = 0;//
	WDTClr();
	//the mission performed half a second a time
	if (Flag.Run & R_HalfS) {
		//key processing
		KeyProcess();//

		Flag.Run &= ~R_HalfS;
		if ((SysChkPW() == 1) && (RunDly.PowerRunDly < 2))
			RunDly.PowerRunDly++;
		else
			RunDly.PowerRunDly = 0;

		//solve the load curve problem,update the time by each 0.5S; under the power on state, after LCD fully displayed and when the key display under power down state, it will update the time
		if ((((Flag.Power & F_PwrUp) == F_PwrUp) && (RunDly.AllDspDly == 0))
				|| ((DisK.ShutDnCnt > 0) && ((Flag.Power & F_PwrUp) == 0)))
			//update clock
			Clock(); //

		//set the load curve to save the test mark at the third second
		if ((Clk.Sec[0] == 0x03) && (Flag.Power & F_PwrUp) && (flag_fh == 0))
			flag_fh = 1;
	}

	//run for every second
	//the mission performed once a second
	if (Flag.Run & R_Sec) {
		Flag.Run &= ~R_Sec;
		Flag.Run |= R_Disp;

		WDTClr();//
		RN8209_Process();

		//metering chip update data
		if ((Flag.Power & F_PwrUp) == F_PwrUp) {
			//reset external module
			if (net_rest_time > 0)//
			{
				net_rest_time--;
				P5OUT &= ~BIT1;
			} else {
				P5OUT |= BIT1;
			}
			if (((Flag.EventFlg1 & F_Ev_PwrOn) == 0) && (pw_on_cout == 0)) {
				static unsigned char pw_count = 0;
				//counting the power on times after power on for 5 seconds
				if ((++pw_count) > 3) //
				{
					//set the record mark of power on events,to save the power on records in the events records
					Flag.EventFlg1 |= F_Ev_PwrOn;//
					pw_count = 0;
				}
			}

			if (gsAttPara.InvalidPowerOnRead == 0) {
				//inifialize the metering chip under factory mode to read the verification value of metering chip parameter and and save it to the ferro electric
				//only calibrating the meter to update and save the verification value
				if ((FAC_KEY() == 0) && (flag_xb == 1)) //
				{
					unsigned char adjbuf[3];
#ifdef SINGLE_PHASE_MULTI_TARIFF
//RN8209SPI
#else
					//obtain the verification value
					ATT7022_RReg(adjbuf, ATT7022_CHK);//

					//save verification value
					FRAM_Write(ATT7022_ADJCHK, (char *) adjbuf, 3);//
					//avoid to read immediately after ferro electric wrote
					_NOP();
					_NOP();
					_NOP();
					_NOP();
					_NOP();//避免写完铁电后马上读取
					_NOP();
					_NOP();
					_NOP();
					_NOP();
					_NOP();
#endif
				}
				//obtain the saved verification value to avoid the exception of the memory  variable
				if (flag_xb == 1)//
				{
					flag_xb = 0;
#ifdef SINGLE_PHASE_MULTI_TARIFF
//RN8209SPI
#else
					//obtain verification value
					FRAM_Read((char*) guAttChk, ATT7022_ADJCHK, 3);//
#endif
				}
				//meter calibration test
#ifdef SINGLE_PHASE_MULTI_TARIFF
//RN8209SPI
				if(FALSE == RN8209_Check())
#else
				if (FALSE == ATT7022_ParaChk())//
#endif
				{
					//reset
					gsAttPara.InvalidPowerOnRead = 2;//
					gHardErr |= ERR_ATT7022_F;
				} else {
					//read metering data
#ifdef SINGLE_PHASE_MULTI_TARIFF
//RN8209SPI
//					RN8209_Process();
#else
					ATT7022_Process();					//
					gHardErr &= ~ERR_ATT7022_F;
#endif
				}
#ifdef SINGLE_PHASE_MULTI_TARIFF
#else
				//pulse accumulation
				CalcPulse();//
#endif
				SM.CntChk = CHECKWORD;
				for (i = 0; i < 40; i++) {
					SM.CntChk += *(&SM.PpCnt + i);
				}
#ifdef SINGLE_PHASE_MULTI_TARIFF
#else
				FRAM_Write(Ram_Pulse, (char*) &SM.PpCnt, 42);
				FRAM_Write(Ram_Pulse + FRAMBAK, (char*) &SM.PpCnt, 42);
#endif
				//electric energy accumulation
				ECMeas();//
#ifdef HARDWARE_TWO
				//self-defined register calculation
				CustomRegister();//
#endif			
				SM.CntChk = CHECKWORD;
				for (i = 0; i < 40; i++) {
					SM.CntChk += *(&SM.PpCnt + i);
				}
#ifdef SINGLE_PHASE_MULTI_TARIFF
#else
				//save the residual pulse data
				FRAM_Write(Ram_Pulse, (char*) &SM.PpCnt, 42);
				FRAM_Write(Ram_Pulse + FRAMBAK, (char*) &SM.PpCnt, 42);
#endif
			}
		}

		if (DisK.ErrCnt > 0) {
			DisK.ErrCnt--;
		}

		if (IEC_Comm.ProgCnt > 0) {
			IEC_Comm.ProgCnt--;
		}
		if ((Flag.Power & F_PwrUp) == F_PwrUp) {
			//program key test
			if (PROG_KEY() == 0)//
			{
				if (IEC_Comm.ProgCnt > 0) {
					IEC_Comm.ProgCnt = 0;
				} else {
					IEC_Comm.ProgCnt = 600;
				}
			}
		}

		if (RunDly.AllDspDly > 0)
			RunDly.AllDspDly--;
#if 0		
		if ((~P6IN & P_Key1) && (~P6IN & P_Key2)) //PgUp + PgDn
		{
			if ((P2IN & P_SW) == P_SW )
			{
				RunDly.AllDspDly=3;
			}
		}
#endif		
		if (Flag.Power & F_PwrUp) {
			//under programmable state, press slideshow and program key simultaneously, it will reset the meter and exit the program.
			if ((IEC_Comm.ProgCnt > 0) && (!KEY_UP_RET) && (PROG_KEY() == 0)
					&& (Flag.ClearKeyFree))//
			{
				Flag.ClearAllData = 0xAB;
				Flag.ClearKeyFree = 0;
			}
			if ((KEY_UP_RET) && (PROG_KEY())) {
				Flag.ClearKeyFree = 1;
			}
			//frozen the test manually
			CheckManualBill();//
			//data zero clearing test
			fClearAllData(); //

			if ((gsAttPara.InvalidPowerOnRead > 1)) {
				gsAttPara.InvalidPowerOnRead--;
			} else if ((gsAttPara.InvalidPowerOnRead == 1)) {
				gsAttPara.InvalidPowerOnRead--;
				//the inifialization of the metering chip
#ifdef SINGLE_PHASE_MULTI_TARIFF
//RN8209SPI
				RN8209_Calib();
#else
				ATT7022_Init();//
#endif
				flag_xb = 1;
			}
		}

		if ((Flag.IntTmStart & MDSTART) == MDSTART)
			//the slip time of demand will be reduced
			if (MaxD.SlidingTm > 0) //
				MaxD.SlidingTm--;
			else {
				//calculating the current demand and rolling the slip register to calculate the maximum demand on the basis of the slip time
				// MDCumuCalc(); 	//
			}
		//reload the rate table after the rate table updated for 15 seconds->set any parameter
		if (Flag.Run & R_FeeTbChg) {
			if (RunDly.FeeTbDely < 15)
				RunDly.FeeTbDely++;
			else if (RunDly.FeeTbDely >= 15) {
				RunDly.FeeTbDely = 0;
				Flag.Run &= ~R_FeeTbChg;
				Flag.EventFlg1 |= F_Ev_Prog;
				//update the rate table number here
				DayTableCHG();
			}
		}

		WDTClr();
#if 0		
		Buffer[0] = ((P2IN & P_SW1) && (P6IN & P_SW2) && !(P2IN & P_SW3));
		//enter into the test mode
		if ( (Buffer[0]) && (Flag.Run & R_Tst)==0x00 ) //进入测试模式
		{
			Flag.Run |= R_Tst;
			MEM_Clr(Tst_EC_Pp0, 8, Mem_FRAM);
			P53Clear();
			PulseBackUp();
			PulseClear();
			MDCumuBackUp();
			MDCumuClear();
		}
		//leave test mode
		else if ( !(Buffer[0]) && (Flag.Run & R_Tst)) //离开测试模式
		{
			P53Clear();
			PulseClear();
			PulseRestore();
			MDCumuRestore();
			Flag.Run &= ~R_Tst;
		}
		//if the following missions are not performed under test mode, but to perform the above metering of electricity quantity ,count it into the buffer of test mode
		else if ( (Buffer[0] ) && (Flag.Run & R_Tst)) //如果在测试模式中 下面的任务不执行 只做上面的电量计量,计入测试模式缓存
		{
			return;
		}
#endif        
		//event record overvoltage,overcurrent,phase loss,battery power off, hardware error and so on
		Events2PS();//
		//load curve save test
		if (flag_fh == 1)//
		{
			unsigned char i;
			unsigned long Min;
			unsigned char Tmp = 0;
			//avoid to save the record twice within 1 second
			flag_fh = 2;//
			for (i = 0; i < LP_MaxChNum; i++) {
#ifdef SINGLE_PHASE_MULTI_TARIFF

#else
				//read demand time
				FRAM_Read((char*) &Tmp, MD_BlockTm, 1);//读需量时间
#endif
				Tmp = BCD_Byte(Tmp);
//				Tmp = 1;
				if (Tmp != 0) {
					Min = GetGmMin(Clk.Min);
//                  Min = GetGmMin(Clk.Sec);
					Min -= (Min / (unsigned long) Tmp) * (unsigned long) Tmp;
					//demand records load curve
					if (Min == 0) //
					{
						//maximum demand
						MDCumuCalc(&Clk);//
						//record load curve
						LoadPro_Rec(i, &Clk);//

					}
				}

			}
		}

	}

	//run for every 5 second
	//the mission performed every 5 seconds
	if (Flag.Clk & F_5S) {
		Flag.Clk &= ~F_5S;
		if (Flag.Power & F_PwrUp) {
#if 1
			//reverse phase sequence check
			memcpy(Buffer, ZX, 3);
			if (memcmp(Buffer, ORDERABC + 0, 3) == 0 || memcmp(Buffer,
					ORDERABC + 3, 3) == 0 || memcmp(Buffer, ORDERABC + 6, 3)
					== 0 || memcmp(Buffer, ORDERABC + 9, 3) == 0 || memcmp(
					Buffer, ORDERABC + 12, 3) == 0 || memcmp(Buffer,
					ORDERABC + 15, 3) == 0) {
				//phase sequence correct
				Flag.Alarm &= ~(F_Al_DisOrd + F_Al_DisOrd_Disp); //
			} else {
				Flag.Alarm |= F_Al_DisOrd;
			}
			//battery check
			if (1 == ComparaStata())//
			{
				Flag.Alarm &= ~F_Al_BatLow;
			} else {

				Flag.Alarm |= F_Al_BatLow;
			}

#endif
		}
	}

	//run for every hour
	//deal with events every hour
	if (Flag.Clk & F_Hour)//
	{
		Flag.Clk &= ~F_Hour;

		if (Flag.Power & F_PwrUp) {
			//self-frozen test
			if ((CheckBill() <= 0x28) && (bill_count == 0))//
			{
				//20111228 LiaoBin
				bill_count = AutoSaveTime();//20111228廖斌
				if (bill_count > 0) {
					Flag.Fee |= F_BillAll;
				}
			}

		}
		//useless test,not used actually
		if ((RunDly.ShutDispHour > 0) && (Flag.Power & F_PwrUp) == 0x00) {
			RunDly.ShutDispHour--;
			if (RunDly.ShutDispHour == 0) {
				Flag.Power |= R_DispShut;
			}
		}
	}
	//run for every day
	//test events everyday
	if (Flag.Clk & F_Day)//
	{
		Flag.Clk &= ~F_Day;
		//update rate table number here
		DayTableCHG();
	}

	//run for every minute
	//test events every minute
	if (Flag.Clk & F_Min)//
	{
		Flag.Clk &= ~F_Min;
		flag_fh = 0;
		//period table test, update tariff
		DayTableCHG(); //

		if (Flag.Power & F_PwrUp) {
			if (RunDly.PowerDely < PowerDelyTM)
				RunDly.PowerDely++;

			E2P_Read((char*) &display_mod, SysSW, 1);
			//not started
			if ((Flag.IntTmStart & MDSTART) == 0x00) //
			{
				{
					//demand parameter initialization
					MDParaInit(); //
					Flag.IntTmStart |= MDSTART;
				}
			}
			//already started
			else //
			{

			}
		}
		//more than x minutes during demand manual settlement
		if (RunDly.MBillDely < MBillDelyTM)
			RunDly.MBillDely++;
		if (RunDly.DLBillDely < DLBillDelyTM)
			RunDly.DLBillDely++;

		//zero clearing of electric energy every minute
		EC_1Min_Clear();//
		//use time of battery add 1, not used
		CumuBATTERY();//
		if (passerr_locktime > 0)
			passerr_locktime--;
		if (passerr_delaytime > 0)
			passerr_delaytime--;
	}

	//here the program is belongs to mian cycle
	//frozen function
	BillALL();//
	//event records, program and power on and down records
	Events();//
}

/**********************************************************************
 //get the number of days from year,month, date
 **********************************************************************/
unsigned int GetGmDay(char * Addr) {
	unsigned int Day, Mon, Year;

	Mon = BCD_Byte(*(Addr + 1));
	Year = BCD_Byte(*(Addr + 2));
	Day = BCD_Byte(*Addr) - 1 + DayTab[Mon] + Year * 365 + (Year >> 2) + 1;
	if ((Year & 0x03) == 0 && Mon <= 2)
		Day--;
	return Day;
}

/**********************************************************************
 //get the number of minutes from date,hour,minute
 **********************************************************************/
unsigned long GetGmMin(char * Addr) {
	return (unsigned long) BCD_Byte(*Addr) + (unsigned long) BCD_Byte(
			*(Addr + 1)) * 60 + (unsigned long) GetGmDay(Addr + 2) * 60 * 24;
}

/**********************************************************************
 //get the number of seconds from year,month,date,hour,minute, second
 **********************************************************************/
unsigned long GetGmSec(char * Addr) {
	return (unsigned long) BCD_Byte(*Addr) + (unsigned long) GetGmMin(Addr + 1)
			* 60;
}

/**********************************************************************
 //get the number of weeks from year,month, date
 **********************************************************************/
//sun.7 mon.1 tues.2 wed.3 thurs.4 friday.5 sat.6
unsigned char GetWeek(char *BCDDay) {
	unsigned char week;
	week = (GetGmDay(BCDDay) + 6) % 7;
	if (week == 0)
		week = 7;
	return (week);
}

//**********************************************************************
//transform the minute into year,month,date,hour, minute
//**********************************************************************
void Min_Date(char * Sec, unsigned long Min) {
	unsigned long Tmp;
	int Y1, Y2;

	*(Sec + 1) = Min % 60; // Minute
	Tmp = Min / 60;
	*(Sec + 2) = Tmp % 24; // Hour
	Tmp /= 24;

	Y1 = Tmp / (365 * 4 + 1);
	Y2 = Tmp % (365 * 4 + 1);
	if (Y2 >= 366) {
		*(Sec + 5) = Y1 * 4 + (Y2 - 1) / 365; // Year
		Y2 = (Y2 - 1) % 365;
	} else
		*(Sec + 5) = Y1 * 4;

	if ((*(Sec + 5) & 0x03) != 0x00) {
		for (Y1 = 12; Y1 > 0; Y1--)
			if ((Y2 - DayTab[Y1]) >= 0)
				break;
		*(Sec + 4) = Y1; // Month
		*(Sec + 3) = Y2 + 1 - DayTab[Y1]; // Day
	} else {
		for (Y1 = 12; Y1 > 0; Y1--)
			if ((Y2 - DayTabR[Y1]) >= 0)
				break;
		*(Sec + 4) = Y1; // Month
		*(Sec + 3) = Y2 + 1 - DayTabR[Y1]; // Day
	}
}

