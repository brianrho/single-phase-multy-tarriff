#include "..\inc\includes.h"

#define	U08x		unsigned char 
//**********************************************************************
//load curve data table
//**********************************************************************
const LOADREG LoadReg[] = {
//total active positive demand 13 
		(U08x*) LP_CurrentD_Pp, 3, Mem_FRAM, //总有功正向需量	13
		//total active reverse demand14
		(U08x*) LP_CurrentD_Pn, 3, Mem_FRAM, //总有功反向需量	14
		//total reactive positive demand 15
		(U08x*) LP_CurrentD_Rp, 3, Mem_FRAM, //总无功正向需量	15
		//total reactive reverse demand 16
		(U08x*) LP_CurrentD_Rn, 3, Mem_FRAM, //总无功反向需量	16


		};
//**********************************************************************
//load curve 8 channel pointer
//**********************************************************************
const unsigned int LoadInfoRun[8] = {
LoadInfoRun1_ + 6 * 0, LoadInfoRun1_ + 6 * 1, LoadInfoRun1_ + 6 * 2,
		LoadInfoRun1_ + 6 * 3,
		LoadInfoRun1_ + 6 * 4, LoadInfoRun1_ + 6 * 5, LoadInfoRun1_ + 6 * 6,
		LoadInfoRun1_ + 6 * 7, };
/*the number of data to be read by one time,if it is 1 register, then read 4 groups by one time,by that analogy
 */
//**********************************************************************
//load curve data length
//**********************************************************************
const LOADLEN LoadLen[8] = { 11, 4, 16, 3, 21, 2, 26, 2, 31, 1, 36, 1, 41, 1,
		46, 1, };
//**********************************************************************
//read load curve
//**********************************************************************
unsigned int LoadPro_Read(unsigned char *Dest, unsigned char Ch) {
	unsigned int LPAddr;
	unsigned int ReadPtr, CommLen, CommNUM;
	unsigned long RecAddr;
	unsigned char LEN;

	LPAddr = LoadInfoRun[Ch] + LP_ReadPtr;
	FRAM_Read((char *) &ReadPtr, LPAddr, 2);

	FRAM_Read((char *) &RecAddr, RecAddr1_ + SIZE_LoadINFO * Ch, 4);

	CommLen = 0x0000;
	FRAM_Read((char *) &CommLen, RegNUM1_ + SIZE_LoadINFO * Ch, 1);
	if (CommLen == 0)
		return (0);
	CommNUM = LoadLen[CommLen - 1].CommNUM;
	CommLen = LoadLen[CommLen - 1].CommLen;
	LEN = CommNUM * CommLen;

	while (CommNUM > 0) {
		MEM_Read((char*) Dest, RecAddr + (unsigned long) ReadPtr * CommLen,
				CommLen, Mem_DFlash);
		if (ReadPtr == 0)
			FRAM_Read((char *) &ReadPtr, MaxRecNUM1_ + SIZE_LoadINFO * Ch, 2);
		ReadPtr--;
		Dest += CommLen;
		CommNUM--;
	}

	MEM_DBWrite(LPAddr, (char *) &ReadPtr, 2, Mem_FRAM);
	return (LEN);
}

//**********************************************************************
//load curve write record
//**********************************************************************
void LoadPro_Rec(char Ch, CLK_T *pt_clk) {
	unsigned int LPAddr;// Int;
	char i;
	unsigned char RegCode;

	LOADINFORUN *LoadInfRun; //  =(LOADINFORUN*)&Buffer[0];	//LoadPro;	 6
	LOADINFO *LoadInf; //	=(LOADINFO*)&Buffer[6];	//		16
	LOADUNIT *LoadUnit; //  =(LOADUNIT*)&Buffer[22];	//		41

	LOADINFORUN sLoadInfRun; //  =(LOADINFORUN*)&Buffer[0];	//LoadPro;	 6
	LOADINFO sLoadInf; //	=(LOADINFO*)&Buffer[6];	//	         16
	LOADUNIT sLoadUnit; //  =(LOADUNIT*)&Buffer[22];	//		 41

	LoadInfRun = &sLoadInfRun;
	LoadInf = &sLoadInf;
	LoadUnit = &sLoadUnit;

	E2P_Read(&Buffer[0], SysSW + 1, 1);
	if ((Buffer[0] & BIT3) == 0x00)
		return;
	FRAM_Read((char *) LoadInf, LoadInfo1_ + SIZE_LoadINFO * Ch, SIZE_LoadINFO);
	if ((LoadInf->RegNum < 1) || (LoadInf->RegNum > 7))
		return;

	LPAddr = LoadInfoRun[Ch];
	FRAM_Read((char *) LoadInfRun, LPAddr, sizeof(LOADINFORUN));

	for (i = 0; i < 6; i++)
		*((unsigned char *) LoadUnit + i) = *(&((*pt_clk).Year[0]) - i);

	if (((*pt_clk).Sec[0]) < 60) {
		LoadUnit->RecTime.Sec[0] = 0;
	} else {
		LoadUnit->RecTime.Sec[0] = ((*pt_clk).Sec[0]);
	}

	for (i = 0; i < LoadInf->RegNum; i++) {
		LoadUnit->Data[i][0] = 0;
		LoadUnit->Data[i][1] = 0;
		LoadUnit->Data[i][2] = 0;
		LoadUnit->Data[i][3] = 0;
		LoadUnit->Data[i][4] = 0;

		RegCode = LoadInf->RegCode[i] - 1;

		if (RegCode <= LP_MaxRegNum) {
			MEM_Read((char*) &(LoadUnit->Data[i][0]),
					(int32u) LoadReg[RegCode].Register,
					LoadReg[RegCode].RegLen, LoadReg[RegCode].RegType);
		}

		RegCode = LoadUnit->Data[i][0];
		LoadUnit->Data[i][0] = LoadUnit->Data[i][4];
		LoadUnit->Data[i][4] = RegCode;
		RegCode = LoadUnit->Data[i][1];
		LoadUnit->Data[i][1] = LoadUnit->Data[i][3];
		LoadUnit->Data[i][3] = RegCode;

	}
	i = 6 + LoadInf->RegNum * 5;
	Flash_Write(
			LoadInf->RecAddr + (((unsigned long) (LoadInfRun->RecPtr))
					* ((unsigned long) i)), (U08x*) LoadUnit, i);
	if (LoadUnit->RecTime.Sec[0] != 0x98) {
		//save the current average power,and update the previous one record
		FRAM_Read((char*) &Buffer[26], AVR_MD, 52);
		memcpy(Buffer, (char*) LoadUnit, 26);
		FRAM_Write(AVR_MD, Buffer, 52);
	}

	if (LoadInfRun->RecNum < LoadInf->MaxRecNum) {
		LoadInfRun->RecNum++;
	}
	LoadInfRun->RecPtr++;
	if (LoadInfRun->RecPtr >= LoadInf->MaxRecNum) {
		LoadInfRun->RecPtr = 0;
	}
	MEM_DBWrite(LPAddr, (char*) LoadInfRun, sizeof(LOADINFORUN), Mem_FRAM);

	{
		unsigned int lc_data_max = 0;
		unsigned int lc_curr_record = 0;
		//the start numbers of load records by Year,Month and Date
		unsigned char curr_data[5];//
		FRAM_Read((char *) curr_data, LOAD_DATE_C_COUNT, 4);
		lc_curr_record = (((unsigned int) curr_data[0]) << 8)
				| (((unsigned int) curr_data[1]) & 0x00FF);
		lc_data_max = (((unsigned int) curr_data[2]) << 8)
				| (((unsigned int) curr_data[3]) & 0x00FF);

		//pointer error
		if (lc_curr_record > LOAD_DATE_MAX)//
		{
			lc_curr_record = 0;
		}
		FRAM_Read((char *) curr_data,
				LOAD_DATE_DATA + (lc_curr_record - 1) * 5, 5);
		//comparison date
		if (curr_data[2] != Clk.Day[0])//比较日期
		{
			curr_data[0] = Clk.Year[0];
			curr_data[1] = Clk.Mon[0];
			curr_data[2] = Clk.Day[0];
			curr_data[3] = (unsigned char) (LoadInfRun->RecPtr >> 8);
			curr_data[4] = (unsigned char) ((LoadInfRun->RecPtr));
			FRAM_Write(LOAD_DATE_DATA + lc_curr_record * 5, (char *) curr_data,
					5);

			lc_curr_record++;
			if ((lc_data_max < lc_curr_record) | (lc_data_max > LOAD_DATE_MAX)) {
				lc_data_max = lc_curr_record;
			}
			if (LoadInfRun->RecPtr == 0) {
				lc_data_max = lc_curr_record;
				lc_curr_record = 0;
			}
			curr_data[0] = (unsigned char) (lc_data_max >> 8);
			curr_data[1] = (unsigned char) ((lc_data_max));
			FRAM_Write(LOAD_DATE_R_COUNT, (char *) curr_data, 2);
			curr_data[0] = (unsigned char) (lc_curr_record >> 8);
			curr_data[1] = (unsigned char) ((lc_curr_record));
			FRAM_Write(LOAD_DATE_C_COUNT, (char *) &curr_data, 2);
		}
	}

}

