#include "..\inc\includes.h"
//#include "inc\Events.h"

unsigned char pw_on_cout = 0;
/******************************************************************************
 //EventsRead-read latest events
 * EventsRead - 读最近已经事件
 * DESCRIPTION: - 
 *      
 * Input: 
 * Output: 
 * Returns: 
 * 
 * modification history
 * --------------------
 * 01a, 22feb2011,  written
 * --------------------
 ******************************************************************************/
void EventsRead(int8u *ucBuf, unsigned int E_ENTRY, unsigned char Num) {
	int8u EPtr;
	FRAM_Read((char*) &EPtr, E_ENTRY, 1);

	if (EPtr > Num) {
		EPtr -= Num;
	} else {
		EPtr = EPtr + 10 - Num;
	}

	//FRAM_Read((char*)ucBuf, E_ENTRY+1+(EPtr-1)*5, 5);//preserve time
	FRAM_Read((char*) ucBuf, E_ENTRY + 1 + (EPtr - 1) * 5, 5);//存时间

}
//*****************************************************************
//write event times
//*****************************************************************
void EventsTimes(unsigned int uiAdr) {
	int16u ucCnt;
	FRAM_Read((char*) &ucCnt, uiAdr, 2);

	if (ucCnt > 9999) {
		ucCnt = 0;
	}
	if (ucCnt < 9999)
		ucCnt++;

	FRAM_Write(uiAdr, (char*) &ucCnt, 2);

}

//*****************************************************************
//read event times
//*****************************************************************
void EventsReadTimes(unsigned int uiAdr, unsigned char *ucCnt) {
	FRAM_Read((char*) ucCnt, uiAdr, 2);

}

//*****************************************************************
//event pointer and time preservation
//*****************************************************************
void EventsHandle(unsigned int E_ENTRY) {
	register unsigned char i;
	register char * ptr;
	char EPtr = 0x00;

	FRAM_Read(&EPtr, E_ENTRY, 1);

	EPtr++;
	if (EPtr <= 0x00 || EPtr > 10) //
		EPtr = 0x01;

	FRAM_Write(E_ENTRY, &EPtr, 1);
	//update store buffer pointer

	ptr = Clk.Year;
	for (i = 0; i < 5; i++) {
		Buffer[i] = *(ptr--);
	}

	// FRAM_Write( E_ENTRY+1+(EPtr-1)*5, Buffer, 5);//preserve time
	FRAM_Write(E_ENTRY + 1 + (EPtr - 1) * 5, Buffer, 5);//存时间
}
//*****************************************************************
//event record
//*****************************************************************
void Events(void) {
#if  0
	//if(P6IN & BIT6)		//open meter cover
	if(P6IN & BIT6) //表盖打开
	{
		if(RunDly.Cover_Dly < 250)
		RunDly.Cover_Dly++;
		else if(RunDly.Cover_Dly == 250)
		{	RunDly.Cover_Dly++; Flag.EventFlg1 |= F_Ev_CoverOp;}
	}
	//else			 //close meter cover
	else //表盖关闭
	{
		if(RunDly.Cover_Dly > 1)
		RunDly.Cover_Dly--;
		else if(RunDly.Cover_Dly == 1)
		{	RunDly.Cover_Dly--; Flag.EventFlg1 |= F_Ev_CoverCl;}
	}
#endif

	if (Flag.EventFlg1 & F_Ev_Prog) {
		Flag.EventFlg1 &= ~F_Ev_Prog;

		EventsTimes(EVENT_PROG_TIMES);
		EventsHandle(EVENT_PROG_PTR);
	}

	if (Flag.EventFlg1 & F_Ev_PwrOn) {
		{
			Flag.EventFlg1 &= ~F_Ev_PwrOn;

			EventsTimes(EVENT_PON_TIMES);
			EventsHandle( EVENT_PON_PTR);
			pw_on_cout = 1;
		}
	}
	if ((Flag.EventFlg1 & F_Ev_PwrOff) && (pw_on_cout > 0)) {
		Flag.EventFlg1 &= ~F_Ev_PwrOff;
		EventsHandle( EVENT_POFF_PTR);
		pw_on_cout = 0;
	}
}

const unsigned short evelog_add[] = { NEV_CURRFX_CNT, NEV_LOSTU_CNT,
		NEV_OVERU_CNT, NEV_HDERR_CNT, NEV_XXERR_CNT, NEV_BARERR_CNT,
		NEV_OVERI_CNT };
const unsigned short evelog_ptr[] = { NEV_CURRFX_PRT, NEV_LOSTU_PRT,
		NEV_OVERU_PRT, NEV_HDERR_PRT, NEV_XXERR_PRT, NEV_BARERR_PRT,
		NEV_OVERI_PRT };
const unsigned short evelog_save[] = { NEV_CURRFX_CRD, NEV_LOSTU_CRD,
		NEV_OVERU_CRD, NEV_HDERR_CRD, NEV_XXERR_CRD, NEV_BARERR_CRD,
		NEV_OVERI_CRD };
//unsigned long eve_vls[3] = {0,0,0};//record low voltage overvoltage value
unsigned long eve_vls[3] = { 0, 0, 0 };//记录低压过压值
//unsigned long eve_vov[3] = {0,0,0};//record low voltage overvoltage value
unsigned long eve_vov[3] = { 0, 0, 0 };//记录低压过压值
//unsigned long eve_voi[3] = {0,0,0};//record overcurrent value
unsigned long eve_voi[3] = { 0, 0, 0 };//记录过流值
struct NEWLOGSTA NewLogSta[LOG_MAX] = { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 },
		{ 0, 0 }, { 0, 0 }, { 0, 0 } };
#define LOG_CNTS  0
#define LOG_TIME   1

//************************************************************
//new  event storage
//************************************************************
void save_evelog(unsigned char type, unsigned char Way) {
	unsigned short times;
	unsigned char ptrs;
	if (type >= LOG_MAX)
		return;
	//E_Read((int8u *)&Buffer,evelog_add[type],2);


	// if(Way == LOG_TIME)//store time
	if (Way == LOG_TIME)//
	{
		FRAM_Read((char *) &ptrs, evelog_ptr[type], 1);
		if (ptrs > 9) {
			ptrs = 0;
		}
		Buffer[0] = Clk.Min[0];
		Buffer[1] = Clk.Hour[0];
		Buffer[2] = Clk.Day[0];
		Buffer[3] = Clk.Mon[0];
		Buffer[4] = Clk.Year[0];

		FRAM_Write(evelog_save[type] + (5 * ptrs), Buffer, 5);
		//if((type == LOG_LOSTU))//store voltage value
		if ((type == LOG_LOSTU))//
		{
			eve_vls[0] /= NewLogSta[LOG_LOSTU].Time;
			eve_vls[1] /= NewLogSta[LOG_LOSTU].Time;
			eve_vls[2] /= NewLogSta[LOG_LOSTU].Time;
			Buffer[5] = (unsigned char) (eve_vls[0] >> 8);
			Buffer[6] = (unsigned char) eve_vls[0];
			Buffer[7] = (unsigned char) (eve_vls[1] >> 8);
			Buffer[8] = (unsigned char) eve_vls[1];
			Buffer[9] = (unsigned char) (eve_vls[2] >> 8);
			Buffer[10] = (unsigned char) eve_vls[2];
			FRAM_Write(NEV_LOSTU_VAL + (6 * ptrs), Buffer + 5, 6);
		}
		//else if(type == LOG_OVERU)//store voltage value
		else if (type == LOG_OVERU)//
		{
			eve_vov[0] /= NewLogSta[LOG_OVERU].Time;
			eve_vov[1] /= NewLogSta[LOG_OVERU].Time;
			eve_vov[2] /= NewLogSta[LOG_OVERU].Time;
			Buffer[5] = (unsigned char) (eve_vov[0] >> 8);
			Buffer[6] = (unsigned char) eve_vov[0];
			Buffer[7] = (unsigned char) (eve_vov[1] >> 8);
			Buffer[8] = (unsigned char) eve_vov[1];
			Buffer[9] = (unsigned char) (eve_vov[2] >> 8);
			Buffer[10] = (unsigned char) eve_vov[2];
			FRAM_Write(NEV_OVERU_VAL + (6 * ptrs), Buffer + 5, 6);
			//}else if(type == LOG_OVERI)//store current value
		} else if (type == LOG_OVERI)//
		{
			eve_voi[0] /= NewLogSta[LOG_OVERI].Time;
			eve_voi[1] /= NewLogSta[LOG_OVERI].Time;
			eve_voi[2] /= NewLogSta[LOG_OVERI].Time;
			Buffer[5] = (unsigned char) (eve_voi[0] >> 8);
			Buffer[6] = (unsigned char) eve_voi[0];
			Buffer[7] = (unsigned char) (eve_voi[1] >> 8);
			Buffer[8] = (unsigned char) eve_voi[1];
			Buffer[9] = (unsigned char) (eve_voi[2] >> 8);
			Buffer[10] = (unsigned char) eve_voi[2];
			FRAM_Write(NEV_OVERI_VAL + (6 * ptrs), Buffer + 5, 6);
		}
		ptrs++;
		FRAM_Write((unsigned int) evelog_ptr[type], (char *) &ptrs, 1);
	}
	//else if(Way == LOG_CNTS)//store times
	else if (Way == LOG_CNTS)//
	{
		FRAM_Read((char *) &Buffer[0], evelog_add[type], 2);
		times = (unsigned short) (Buffer[0] << 8)
				| ((unsigned short) (Buffer[1]));
		//if((times >9999)||(times == 0))//wrong times
		if ((times > 9999) || (times == 0))//
		{
			times = 0;
		}
		times++;
		Buffer[0] = (unsigned char) (times >> 8);
		Buffer[1] = (unsigned char) (times);
		FRAM_Write((unsigned int) evelog_add[type], (char *) Buffer, 2);
	}

}
//************************************************************
//zero clearing events
//************************************************************
void clr_log(char i) {
	//zero clearing all events

	unsigned short cnt = 0;
	if (i >= LOG_MAX)
		return;
	{
		FRAM_Write((unsigned int) evelog_add[i], (char *) &cnt, 2);
		FRAM_Write((unsigned int) evelog_ptr[i], (char *) &cnt, 1);
		memset(Buffer, 0, 60);
		FRAM_Write(evelog_save[i], Buffer, 50);
		if (i == LOG_LOSTU) {
			FRAM_Write(NEV_LOSTU_VAL, Buffer, 60);
		} else if (i == LOG_OVERU) {
			FRAM_Write(NEV_OVERU_VAL, Buffer, 60);
		}
	}

}
extern unsigned char meter_state[];

void InitNewLog(void) {
	memset((char *) NewLogSta, 0, sizeof(NewLogSta));
	memset((char *) eve_vls, 0, sizeof(eve_vls));
	memset((char *) eve_vov, 0, sizeof(eve_vov));
	memset((char *) eve_voi, 0, sizeof(eve_voi));
}

//************************************************************
//event checking
//************************************************************
void NewLogProc(int16u state) {
	//#define LOG_FS   0x01   //event occurence
#define LOG_FS   0x01   //
	//#define LOG_SCNT  0x02  //event recorded times
#define LOG_SCNT  0x02  //
	//#define LOG_SCRD  0x04  //event recorded times
#define LOG_SCRD  0x04  //
	unsigned char i = 0;
	unsigned short DlayTime = 0;
	unsigned char meterstate[2];
	//meterstate[1]=state;//acquire the latest statement
	meterstate[1] = state;//
	meterstate[0] = meter_state[0];
	//reverse
	if (meterstate[0] & STA_FX_CURR) {
		NewLogSta[LOG_CURRFX].Sta |= LOG_FS;
		if (NewLogSta[LOG_CURRFX].Time < LOG_CRD_TIME) {
			NewLogSta[LOG_CURRFX].Time++;
		}
	} else {
		NewLogSta[LOG_CURRFX].Sta = 0;
		NewLogSta[LOG_CURRFX].Time = 0;
	}
	//loss of phase
	if ((meterstate[1] & 0x08) && (NewLogSta[LOG_LOSTU].Sta != LOG_SCNT)) {
		NewLogSta[LOG_LOSTU].Sta |= LOG_FS;
		if (NewLogSta[LOG_LOSTU].Time < LOG_CRD_TIME) {
			NewLogSta[LOG_LOSTU].Time++;
			// eve_vls[0] += gsAttRealVal.VRMS[0];//record low voltage overvoltage value
			eve_vls[0] += gsAttRealVal.VRMS[0];//
			eve_vls[1] += gsAttRealVal.VRMS[1];
			eve_vls[2] += gsAttRealVal.VRMS[2];
		}
	} else if ((meterstate[1] & 0x08) == 0) {
		NewLogSta[LOG_LOSTU].Sta = 0;
		NewLogSta[LOG_LOSTU].Time = 0;
		//eve_vls[0] = 0;//record low voltage overvoltage value
		eve_vls[0] = 0;//
		//eve_vls[1] = 0;//record low voltage overvoltage value
		eve_vls[1] = 0;//
		//eve_vls[2] = 0;//record low voltage overvoltage value
		eve_vls[2] = 0;//
	}
	//overvoltage
	if ((meterstate[1] & 0x10) && (NewLogSta[LOG_OVERU].Sta != LOG_SCNT)) {
		NewLogSta[LOG_OVERU].Sta |= LOG_FS;
		if (NewLogSta[LOG_OVERU].Time < LOG_CRD_TIME) {
			NewLogSta[LOG_OVERU].Time++;
			// eve_vov[0] += gsAttRealVal.VRMS[0];//record low voltage overvoltage
			eve_vov[0] += gsAttRealVal.VRMS[0];//
			eve_vov[1] += gsAttRealVal.VRMS[1];
			eve_vov[2] += gsAttRealVal.VRMS[2];
		}
	} else if ((meterstate[1] & 0x10) == 0) {
		NewLogSta[LOG_OVERU].Sta = 0;
		NewLogSta[LOG_OVERU].Time = 0;
		//eve_vov[0] = 0;//record low voltage overvoltage value
		eve_vov[0] = 0;//
		//eve_vov[1] = 0;//record low voltage overvoltage value
		eve_vov[1] = 0;//
		//eve_vov[2] = 0;//record low voltage overvoltage value
		eve_vov[2] = 0;//
	}
	//overcurrent
	if ((meterstate[1] & 0x40) && (NewLogSta[LOG_OVERI].Sta != LOG_SCNT)) {
		NewLogSta[LOG_OVERI].Sta |= LOG_FS;
		if (NewLogSta[LOG_OVERI].Time < LOG_CRD_TIME) {
			NewLogSta[LOG_OVERI].Time++;
			//eve_voi[0] += gsAttRealVal.IRMS[0];//record overcurrent value
			eve_voi[0] += gsAttRealVal.IRMS[0];//
			eve_voi[1] += gsAttRealVal.IRMS[1];
			eve_voi[2] += gsAttRealVal.IRMS[2];
		}
	} else if ((meterstate[1] & 0x40) == 0) {
		NewLogSta[LOG_OVERI].Sta = 0;
		NewLogSta[LOG_OVERI].Time = 0;
		// eve_voi[0] = 0;//record overcurrent value
		eve_voi[0] = 0;//
		// eve_voi[1] = 0;//record overcurrent value
		eve_voi[1] = 0;//
		//eve_voi[2] = 0;//record overcurrent value
		eve_voi[2] = 0;//
	}
	//firmware
	if (meterstate[1] & 0x01) {
		NewLogSta[LOG_HDERR].Sta |= LOG_FS;
		if (NewLogSta[LOG_HDERR].Time < LOG_CRD_TIME) {
			NewLogSta[LOG_HDERR].Time++;
		}
	} else {
		NewLogSta[LOG_HDERR].Sta = 0;
		NewLogSta[LOG_HDERR].Time = 0;
	}
	//phase sequence
	if (meterstate[1] & 0x04) {
		NewLogSta[LOG_XXERR].Sta |= LOG_FS;
		if (NewLogSta[LOG_XXERR].Time < LOG_CRD_TIME) {
			NewLogSta[LOG_XXERR].Time++;
		}
	} else {
		NewLogSta[LOG_XXERR].Sta = 0;
		NewLogSta[LOG_XXERR].Time = 0;
	}
	//battery
	if (meterstate[0] & STA_POW_LOW) {
		NewLogSta[LOG_BARERR].Sta |= LOG_FS;
		if (NewLogSta[LOG_BARERR].Time < LOG_CRD_TIME) {
			NewLogSta[LOG_BARERR].Time++;
		}
	} else {
		NewLogSta[LOG_BARERR].Sta = 0;
		NewLogSta[LOG_BARERR].Time = 0;
	}
	// FRAM_Read( (char *)&Buffer[50],Dly_UnbV, 2); //read delay time // BCD code
	FRAM_Read((char *) &Buffer[50], Dly_UnbV, 2); //
	//DlayTime =(unsigned short) BCD2_Word((unsigned char *)&Buffer[50]);//transfer to decimalism
	DlayTime = (unsigned short) BCD2_Word((unsigned char *) &Buffer[50]);//
	if ((DlayTime == 0) || (DlayTime > 60)) {
		DlayTime = 5;
	}
	for (i = 0; i < LOG_MAX; i++) {
		if (NewLogSta[i].Sta & LOG_FS) {
			if ((!(NewLogSta[i].Sta & LOG_SCNT)) && (NewLogSta[i].Time
					>= DlayTime)) {
				//record times
				save_evelog(i, LOG_CNTS);
				NewLogSta[i].Sta |= LOG_SCNT;

				//}
				// if((NewLogSta[i].Sta & LOG_SCNT)&&(!(NewLogSta[i].Sta & LOG_SCRD))&&(NewLogSta[i].Time >= LOG_CRD_TIME))
				// {
				//record time
				save_evelog(i, LOG_TIME);
				NewLogSta[i].Sta |= LOG_SCRD;
			}

		}
	}

}

