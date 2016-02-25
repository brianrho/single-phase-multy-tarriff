#include "..\inc\includes.h"

#ifdef SINGLE_PHASE_MULTI_TARIFF
#include "..\inc\RN8209.h"
extern volatile RN8209_RMS rn8209a_rms;
extern volatile RN8209_CALIB rn8209a_calib;
extern ENERGY vse1t_de;
#endif
//*****************************************************************
//event recording stops
//*****************************************************************
void Events2EndRecord(unsigned int E_ENTRY) {
	char EPtr = 0x00;

	E2P_Read(&EPtr, E_ENTRY, 1);
	if (EPtr <= 0x00 || EPtr > 0x28)
		EPtr = 0x01;
	//E2P_Write( E_ENTRY+1+(EPtr-1)*11, Clk.Min, 5);	//storage ending time
	E2P_Write(E_ENTRY + 1 + (EPtr - 1) * 11, Clk.Min, 5);	//存结束时间
}
//*****************************************************************
//event recording starts
//*****************************************************************
void Events2StartRecord(unsigned int E_ENTRY) {
	char EPtr = 0x00;
	char i;

	E2P_Read(&EPtr, E_ENTRY, 1);
	EPtr++;
	if (EPtr <= 0x00 || EPtr > 0x28)
		EPtr = 0x01;
	E2P_Write(E_ENTRY, &EPtr, 1);

	//E2P_Write( E_ENTRY+1+(EPtr-1)*11+5, Clk.Min, 5);	//storage starting time
	E2P_Write(E_ENTRY + 1 + (EPtr - 1) * 11 + 5, Clk.Min, 5);	//存开始时间
	for (i = 1; i <= 5; i++)
		Buffer[i] = 0x00;
	//E2P_Write( E_ENTRY+1+(EPtr-1)*11, &Buffer[1], 5);	    //ending time area zero clearing
	E2P_Write(E_ENTRY + 1 + (EPtr - 1) * 11, &Buffer[1], 5);	//结束时间区清零
	//E2P_Write( E_ENTRY+1+(EPtr-1)*11+10, &Buffer[0], 1);	//storage loss of phase mark
	E2P_Write(E_ENTRY + 1 + (EPtr - 1) * 11 + 10, &Buffer[0], 1);	//存失压标志
}
//*****************************************************************
//event record
//*****************************************************************
void Events2StartEnd(void) {
	char chTmp, chTmpBk;
	int RLT = 0x0000;
	register unsigned int i;

	//there is split-phase event
	chTmp = EventFlag.EFlag1 & 0x0F;
	chTmpBk = EventFlag.EFlagBk1 & 0x0F;
	for (i = 0; i < 3; i++) {
		if (((chTmp ^ chTmpBk) & ByteBit[i]) != 0x00) {
			if ((chTmp & ByteBit[i]) == ByteBit[i])
			//split-phase record starts
					{
						//FRAM_Read(&Buffer[0] ,VFailureNumC, 8);     //split-phase times
				FRAM_Read(&Buffer[0], VFailureNumC, 8);     //
				_BCD2INC(&Buffer[6]);
				_BCD2INC(&Buffer[4 - i * 2]);
				FRAM_Write(VFailureNumC, &Buffer[0], 8);
				// FRAM_Write(VFailureLast1SAll, Clk.Min, 5);  //split-phase starting time
				FRAM_Write(VFailureLast1SAll, Clk.Min, 5);  //
				FRAM_Write(VFailureLast1SA - i * 5, Clk.Min, 5);
				RLT = 0x01;
			} else
			//turn off split-phase record
			{
				//FRAM_Write(VFailureLast1PAll, Clk.Min, 5);  //split-phase stoping time
				FRAM_Write(VFailureLast1PAll, Clk.Min, 5);  //
				FRAM_Write(VFailureLast1PA - i * 5, Clk.Min, 5);
				RLT = 0x01;
			}
		}
	}
	//check backup
	if (RLT != 0x00) {
		RLT = ChkMem(VFailureNumC, 60, Mem_FRAM);
		FRAM_Write(VF_Chk, (char*) &RLT, 2);
		MEM_MEM(VFailureNumC + FRAMBAK, VFailureNumC, 62, Mem_FRAM);
	}
	EventFlag.EFlagBk1 = ((EventFlag.EFlagBk1 & 0xF0) | chTmp);

	//loss of voltage event
	chTmp = EventFlag.EFlag1 & 0xF0;
	chTmpBk = EventFlag.EFlagBk1 & 0xF0;
	// if ((chTmpBk!=0x00) && (chTmp!=chTmpBk))  //if there is loss of voltage and it's different from current loss of voltage status, then ends the original status
	if ((chTmpBk != 0x00) && (chTmp != chTmpBk)) //
			{
		Events2EndRecord (EVENT_VUnder_PTR);
	}
	//if ((chTmp!=0x00) && (chTmp!=chTmpBk))    //if there is loss of voltage and it's different from current loss of voltage status, then start new loss of voltage record
	if ((chTmp != 0x00) && (chTmp != chTmpBk)) //
			{
		Buffer[0] = (chTmp >> 4);
		Events2StartRecord (EVENT_VUnder_PTR);

		//FRAM_Read(&Buffer[1], VUnderNumAll, 2);//total loss of voltage accumulated times
		FRAM_Read(&Buffer[1], VUnderNumAll, 2);                 //
		_BCD2INC(&Buffer[1]);
		MEM_DBWrite(VUnderNumAll, &Buffer[1], 2, Mem_FRAM);
		//FRAM_Read(&Buffer[1], VUnderNumA+(Buffer[0]-1)*15, 2);  //corresponding loss of voltage accumulated times
		FRAM_Read(&Buffer[1], VUnderNumA + (Buffer[0] - 1) * 15, 2); //
		_BCD2INC(&Buffer[1]);
		MEM_DBWrite(VUnderNumA + (Buffer[0] - 1) * 15, &Buffer[1], 2, Mem_FRAM);
	}
	EventFlag.EFlagBk1 = ((EventFlag.EFlagBk1 & 0x0F) | chTmp);

	//overvoltage
	chTmp = EventFlag.EFlag2 & 0x0F;
	chTmpBk = EventFlag.EFlagBk2 & 0x0F;
	if ((chTmpBk != 0x00) && (chTmp != chTmpBk)) {
		Events2EndRecord (EVENT_VOver_PTR);
	}
	if ((chTmp != 0x00) && (chTmp != chTmpBk)) {
		Buffer[0] = (chTmp);
		Events2StartRecord (EVENT_VOver_PTR);
	}
	EventFlag.EFlagBk2 = ((EventFlag.EFlagBk2 & 0xF0) | chTmp);

	//overpower
	chTmp = EventFlag.EFlag2 & 0xF0;
	chTmpBk = EventFlag.EFlagBk2 & 0xF0;
	if ((chTmpBk != 0x00) && (chTmp != chTmpBk)) {
		Events2EndRecord (EVENT_OverLoad_PTR);
	}
	if ((chTmp != 0x00) && (chTmp != chTmpBk)) {
		Buffer[0] = (chTmp >> 4);
		Events2StartRecord (EVENT_OverLoad_PTR);
	}
	EventFlag.EFlagBk2 = ((EventFlag.EFlagBk2 & 0x0F) | chTmp);

	//low power factor
	chTmp = EventFlag.EFlag3 & 0x0F;
	chTmpBk = EventFlag.EFlagBk3 & 0x0F;
	if ((chTmpBk != 0x00) && (chTmp != chTmpBk)) {
		Events2EndRecord (EVENT_LowPF_PTR);
	}
	if ((chTmp != 0x00) && (chTmp != chTmpBk)) {
		Buffer[0] = (chTmp);
		Events2StartRecord (EVENT_LowPF_PTR);
	}
	EventFlag.EFlagBk3 = ((EventFlag.EFlagBk3 & 0xF0) | chTmp);

	//loss of current
	chTmp = EventFlag.EFlag3 & 0xF0;
	chTmpBk = EventFlag.EFlagBk3 & 0xF0;
	if ((chTmpBk != 0x00) && (chTmp != chTmpBk)) {
		Events2EndRecord (EVENT_IUnder_PTR);
	}
	if ((chTmp != 0x00) && (chTmp != chTmpBk)) {
		Buffer[0] = (chTmp >> 4);
		Events2StartRecord (EVENT_IUnder_PTR);
	}
	EventFlag.EFlagBk3 = ((EventFlag.EFlagBk3 & 0x0F) | chTmp);
}
extern void NewLogProc(int16u state);
//*****************************************************************
//event record
//*****************************************************************
void Events2PS(void) {
	long lngTmp;
	long MaxU, MinU, Fu, Ou,Uu, Oi;
	register int i;
	int8u ucBuf[10];

	if ((Flag.Power & F_PwrUp) == 0x00)
		return;

	EventFlag.States = 0;

	MaxU = 0;


	for (i = 0; i < 3; i++) {
#if (METER_3H3W==1)
		if(i==1)
		{
			continue;

		}
#endif

		if (gsAttRealVal.VRMS[i] > MaxU) {
			MaxU = gsAttRealVal.VRMS[i];
		}
	}
	MinU = 0xfffff;
	for (i = 0; i < 3; i++) {
#if (METER_3H3W==1)
		if(i==1)
		{
			continue;

		}
#endif
		if (gsAttRealVal.VRMS[i] < MinU) {
			MinU = gsAttRealVal.VRMS[i];
		}
	}
//#ifdef SINGLE_PHASE_MULTI_TARIFF
//#else
//	//xx.xx%
//	FRAM_Read((char*) ucBuf, Val_UnbV, 2);
//	lngTmp = BCD2_Word(ucBuf);
//
//	if (MaxU > MinU) {
//		MaxU -= MinU;
//		MaxU *= 1000;
//		if (MinU != 0) {
//			MaxU /= MinU;
//		}
//		if (MaxU > lngTmp) {
//			if (EventDly.DUnBala < 3) {
//				EventDly.DUnBala++;
//			}
//			if (EventDly.DUnBala >= 3) {
//				EventFlag.States |= F_UnBala;
//			}
//		} else {
//			if (EventDly.DUnBala > 0) {
//				EventDly.DUnBala--;
//			}
//		}
//	}
//
//	//loss of phase  xxx.x%
//	//0.001 unit
//	FRAM_Read((char*) ucBuf, Val_VFailure, 2);
//	Fu = (unsigned long) FC_Un * BCD2_Word(ucBuf);
//
//#endif

	//overvoltage
	//0.001 unit
//	FRAM_Read((char*) ucBuf, Val_VOver, 2);
	E2P_Read((char*) ucBuf, Val_VOver, 2);
	Ou = (unsigned long) FC_Un;
	Ou = Ou * (unsigned long) BCD2_Word(ucBuf);
	//undervoltage
	E2P_Read((char*) ucBuf, Val_VUnder, 2);
	Uu = (unsigned long) FC_Un;
	Uu = Uu * (unsigned long) BCD2_Word(ucBuf);

	//overcurrent
	//0.001 unit
//	FRAM_Read((char*) ucBuf, Val_IOver, 2);
	E2P_Read((char*) ucBuf, Val_IOver, 2);
	Oi = (unsigned long) FC_Ib;
	Oi = Oi * (unsigned long) BCD2_Word(ucBuf);

	for (i = 0; i < 3; i++) {
#if (METER_3H3W==1)
		if(i==1)
		{
			continue;

		}
#endif


		//lngTmp=gsAttRealVal.VRMS[i];//when zero clearing of meter, zero clearing of voltage happens, which might result in wrong event record

		lngTmp = ((rn8209a_rms.V_RMS.val * 100) / rn8209a_calib.kv);

		lngTmp *= 100;		//0.001

		if (lngTmp > Ou) {
			if (EventDly.DUOver[i] < 3) {
				EventDly.DUOver[i]++;

			}
			if (EventDly.DUOver[i] >= 3) {
				EventFlag.States |= F_UOver;
			}
		} else {
			if (EventDly.DUOver[i] > 0) {
				EventDly.DUOver[i]--;
			}
		}

		if (lngTmp < Uu) {
			if (EventDly.DUOver[i] < 3) {
				EventDly.DUOver[i]++;

			}
			if (EventDly.DUOver[i] >= 3) {
				EventFlag.States |= F_UUnder;
			}
		} else {
			if (EventDly.DUOver[i] > 0) {
				EventDly.DUOver[i]--;
			}
		}

		//overcurrent 0.01
		lngTmp = rn8209a_rms.I_RMS.val;
		lngTmp *= 10;		//0.001

		if (lngTmp > Oi) {
			if (EventDly.DIOver[i] < 3) {
				EventDly.DIOver[i]++;
			}
			if (EventDly.DIOver[i] >= 3) {
				EventFlag.States |= F_IOver;
			}
		} else {
			if (EventDly.DIOver[i] > 0) {
				EventDly.DIOver[i]--;
			}

		}
	}
	//judge battery
	if (gHardErr != 0) {
		if (EventDly.DHerr < 3) {
			EventDly.DHerr++;
		}

//		if (EventDly.DHerr >= 3) {
//			EventFlag.States |= F_HardErr;
//		}
	} else {
		if (EventDly.DHerr > 0) {
			EventDly.DHerr--;
		}
	}

	NewLogProc(EventFlag.States);  //新事件处理
}

//*****************************************************************
//event record
//*****************************************************************
void Events2PM(void) {
	char chTmp;
	register int i;

	chTmp = EventFlag.EFlag1 & 0x07;
	//chTmpBk = EventFlag.EFlagBk1 & 0x0F;
	if (chTmp != 0x00) {
		FRAM_Read(&Buffer[0], VFailureTimC, 12);
		_BCD3INC(&Buffer[9]);
		for (i = 0; i < 3; i++) {
			if ((chTmp & ByteBit[i]) == ByteBit[i]) {
				_BCD3INC(&Buffer[6 - i * 3]);
			}
		}
		MEM_DBWrite(VFailureTimC, &Buffer[0], 12, Mem_FRAM);
	}

	chTmp = EventFlag.EFlag1 & 0x70;
	chTmp >>= 4;
	if (chTmp != 0x00) {
		Buffer[0] = chTmp;
		FRAM_Read(&Buffer[1], VUnderPnAll, 11);
		//_BCD3INC(&Buffer[9]);                   //total loss of voltage accumulated time
		_BCD3INC(&Buffer[9]);                   //
		FRAM_Read(&Buffer[12], EC_Pp1Min, 4);
		FRAM_Read(&Buffer[16], EC_Pn1Min, 4);  //...............................

		//_BCD4ADD(&Buffer[5], &Buffer[12]);      //total loss of voltage accumulated power quantity
		_BCD4ADD(&Buffer[5], &Buffer[12]);      //
		_BCD4ADD(&Buffer[1], &Buffer[16]);
		MEM_DBWrite(VUnderPnAll, &Buffer[1], 11, Mem_FRAM);

		//FRAM_Read(&Buffer[1], VUnderPnA+(Buffer[0]-1)*15, 11);  //corresponding loss of voltage accumulated time
		FRAM_Read(&Buffer[1], VUnderPnA + (Buffer[0] - 1) * 15, 11); //
		_BCD3INC(&Buffer[9]);
		FRAM_Read(&Buffer[12], EC_Pp1Min, 4);
		FRAM_Read(&Buffer[16], EC_Pn1Min, 4);

		//_BCD4ADD(&Buffer[5], &Buffer[12]);      //loss of phase power quantity accumulation
		_BCD4ADD(&Buffer[5], &Buffer[12]);      //
		_BCD4ADD(&Buffer[1], &Buffer[16]);
		MEM_DBWrite(VUnderPnA + (Buffer[0] - 1) * 15, &Buffer[1], 11, Mem_FRAM);
	}

}

