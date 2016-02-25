/******************************************************************************
 //ATT7022.c-ATT7022driver programme
 * ATT7022.c -
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

#include "..\inc\includes.h"



/*
 //defined variable
 */
//BCD type actual measurement data storage
ATT7022_REAL_BCD_T gsAttBCDVal;//
//decimal type actual measurement data storage
ATT7022_REAL_VAL_T gsAttRealVal;//
//configuration parameter
ATT7022_PARA_T gsAttPara;//
//check storage saving cache
unsigned char guAttChk[3];//

/*
 //problem
 //1.starting current
 //2.phase failure threshold

 //3.phase compensation G*Is*2^23 section
 //voltage channel G,G 0.648
 */




#define DFSPI_RD    0
#define DFSPI_WR    1

#define		ATT7022_G	0.648

#define	HF_VAL_T	(5760000000*ATT7022_G*ATT7022_G*ATT7022_Vu*ATT7022_Vi)
#define	HF_VAL	 	(HF_VAL_T/(METER_UN*METER_IB*METER_CONST))

#define	HF_SS		100

/*
 const unsigned char HFTbl[3]={
 0,0,0,
 };
 */
//gain voltage channel 
const unsigned char UGTbl[3] = { 0x46, 0x55, ATT7022_UnG, };

/*Istartup=INT[ATT7022_G*Io*2^23]
 0.648*0.06*0.0016*8388608=521
 */
const unsigned char IStartUPTab[3] = { 0x00, 0x02, 0x09 //IB 100MV,0.2%Ib起动
		};

#define		FV_VAL_T	(8192*METER_UN)
#define		FV_VAL		(FV_VAL_T*0.1)

//list of voltage register
const unsigned char VRMSTbl[] = { ATT7022_r_URmsa, ATT7022_r_URmsb,
		ATT7022_r_URmsc };
//list of current register
const unsigned char IRMSTbl[] = { ATT7022_r_IRmsa, ATT7022_r_IRmsb,
		ATT7022_r_IRmsc };
//list of power register
const unsigned char PTbl[] = { ATT7022_r_Pa, ATT7022_r_Pb, ATT7022_r_Pc,
		ATT7022_r_Pt };
//active power direction
const unsigned char PDirTbl[4] = { ATT7022_DIR_PA, ATT7022_DIR_PB,
		ATT7022_DIR_PC, ATT7022_DIR_PT };
//list of reactive power register
const unsigned char QTbl[] = { ATT7022_r_Qa, ATT7022_r_Qb, ATT7022_r_Qc,
		ATT7022_r_Qt };
//reactive power direction
const unsigned char QDirTbl[4] = { ATT7022_DIR_QA, ATT7022_DIR_QB,
		ATT7022_DIR_QC, ATT7022_DIR_QT };
//phase angle 
const unsigned int ADirTbl[4] = { ATT7022_DIR_ANGLEA, ATT7022_DIR_ANGLEB,
		ATT7022_DIR_ANGLEC, ATT7022_DIR_ANGLET };
//apparent power
const unsigned char STbl[] = { ATT7022_r_Sa, ATT7022_r_Sb, ATT7022_r_Sc,
		ATT7022_r_St };
//active power
const unsigned char Epa2Tbl[] = { ATT7022_r_Epa2, ATT7022_r_Epb2,
		ATT7022_r_Epc2, ATT7022_r_Ept2 };
//reactive power
const unsigned char Eqa2Tbl[] = { ATT7022_r_Eqa2, ATT7022_r_Eqb2,
		ATT7022_r_Eqc2, ATT7022_r_Eqt2 };
//apparent
const unsigned char LEpa2Tbl[] = { ATT7022_LineEpa2, ATT7022_LineEpb2,
		ATT7022_LineEpc2, ATT7022_LineEpt2 };


#ifdef SINGLE_PHASE_MULTI_TARIFF



#else

//SPI trunk SO control
void ATT7022_SPI_SO(int8u ucMode) {

	if (ucMode == 1) {
		ATT7022_SET_SI();
	} else {
		ATT7022_CLR_SI();
	}
}
//SPI bus CLK control
void ATT7022_SPI_CLK(int8u ucMode) {
	if (ucMode == 1) {
		ATT7022_SET_CLK();
	} else {
		ATT7022_CLR_CLK();
	}
}
//SPI bus , input
int8u ATT7022_SPI_SIG(void) {
	if (SPI_RET_ATSIG) {
		return 1;
	} else {
		return 0;
	}
}
//SPI bus input
int8u ATT7022_SPI_SI(void) {
	if (ATT7022_RET_SO) {
		return 1;
	} else {
		return 0;
	}
}
//SPI bus, CS control
void ATT7022_SPI_CS(int8u ucMode) {
	if (ucMode == 1) {
		ATT7022_SET_CS();
	} else {
		ATT7022_CLR_CS();
	}
}

//delay function
void ATT7022_DelayUs(unsigned char ucTime) {
	for (; ucTime > 0; ucTime--) {
		_NOP();
	}
}

/******************************************************************************
 * //ATT7022_RWSPI - ATT7022SPI reading time slots
 ATT7022_RWSPI - ATT7022SPI读时序

 ******************************************************************************/
unsigned char ATT7022_RSPI(unsigned char *ucBuff, unsigned char ucAdr) {

	unsigned char i, j, ucTmp;

	ATT7022_SPI_CS(1);
	ATT7022_SPI_CLK(0);
	ATT7022_SPI_CS(0);

	ucTmp = ucAdr;

	for (i = 8; i > 0; i--) {
		ATT7022_SPI_CLK(1);
		if (ucTmp & 0x80) {
			ATT7022_SPI_SO(1);
		} else {
			ATT7022_SPI_SO(0);
		}
		ATT7022_SPI_CLK(0);
		ucTmp <<= 1;
	}
	ATT7022_DelayUs(3);
	//reading 24 places data
	for (j = 3; j > 0; j--) {
		ucTmp = 0;
		for (i = 8; i > 0; i--) {
			ucTmp <<= 1;
			ATT7022_SPI_CLK(1);
			if (ATT7022_SPI_SI()) {
				ucTmp |= 0x01;
			} else {
				ucTmp &= ~0x01;
			}
			ATT7022_SPI_CLK(0);
		}
		*ucBuff = ucTmp;
		ucBuff++;
	}

	ATT7022_SPI_CS(1);
	return TRUE;
}
//************************************************************
//SPI writting data
unsigned char ATT7022_WSPI(unsigned char *ucBuff, unsigned char ucAdr) {

	unsigned char i, j, ucTmp;

	DF_SET_CS();
	FM_SET_CS();
	ATT7022_SPI_CS(1);
	ATT7022_SPI_CLK(0);
	ATT7022_SPI_CS(0);

	ucTmp = ucAdr | 0x80;

	for (i = 8; i > 0; i--) {
		ATT7022_SPI_CLK(1);
		if (ucTmp & 0x80) {
			ATT7022_SPI_SO(1);
		} else {
			ATT7022_SPI_SO(0);
		}
		ATT7022_SPI_CLK(0);
		ucTmp <<= 1;
	}
	ATT7022_DelayUs(10);
	//write 24 places data
	for (j = 3; j > 0; j--) {
		ucTmp = *ucBuff++;
		for (i = 8; i > 0; i--) {
			ATT7022_SPI_CLK(1);
			if (ucTmp & 0x80) {
				ATT7022_SPI_SO(1);
			} else {
				ATT7022_SPI_SO(0);
			}
			ATT7022_SPI_CLK(0);
			ucTmp <<= 1;
		}
	}

	ATT7022_SPI_CS(1);
	return TRUE;
}
//************************************************************
//7022 write register
unsigned char ATT7022_WReg(unsigned char *ucBuf, unsigned char ucAdr) {
	unsigned char i;
	unsigned char ucBak[3];

	for (i = 0; i < 3; i++) {
		ATT7022_WSPI(ucBuf, ucAdr);
		ATT7022_RSPI(ucBak, 0x2d);
		if (memcmp(ucBuf, ucBak, 3) == 0) {
			break;
		}
	}

	if (i == 3) {
		gHardErr |= ERR_ATT7022_F;
		return FALSE;

	} else {
		gHardErr &= ~ERR_ATT7022_F;
		return TRUE;

	}
}
//************************************************************
//7022 read register
unsigned char ATT7022_RReg(unsigned char *ucBuf, unsigned char ucAdr) {
	unsigned char i;
	unsigned char ucBak[3];

	for (i = 0; i < 3; i++) {
		ATT7022_RSPI(ucBuf, ucAdr);
		ATT7022_RSPI(ucBak, 0x28);
		if ((memcmp(ucBuf, ucBak, 3) == 0) && ((ucBuf[0] != 0xFF) || (ucBuf[1]
				!= 0xFF) || (ucBuf[2] != 0xFF))) {
			break;
		}
	}

	if (i == 3) {
		gHardErr |= ERR_ATT7022_F;
		return FALSE;
	} else {
		gHardErr &= ~ERR_ATT7022_F;
		return TRUE;
	}
}

//the following is the AT7022 special command

/******************************************************************************
 * //ATT7022_ADJClr -clearing calibration meter parameter
 ATT7022_ADJClr -
 ******************************************************************************/
void ATT7022_ADJClr(void) {
	unsigned char ucBuf[3];
	ucBuf[0] = 0;
	ucBuf[1] = 0;
	ucBuf[2] = 0;
	ATT7022_WSPI(ucBuf, 0xc3);
}

/******************************************************************************
 * //ATT7022_ADJRead-data register or calibration meter register swithover
 ATT7022_ADJRead -
 ******************************************************************************/
#if 0 
unsigned char ATT7022_ADJRead(unsigned char ucMode)
{

	unsigned char ucBuf[3];
	unsigned char ucString[3]= {0xaa,0xaa,0xaa};

	if(ucMode==1)
	{
		ucBuf[0]=0x0;
		ucBuf[1]=0x0;
		ucBuf[2]=0x5a;
	}
	else
	{
		ucBuf[0]=0;
		ucBuf[1]=0;
		ucBuf[2]=0;
	}
	ATT7022_WSPI(ucBuf, 0xc3);

	//0x00 address data
	//读0x00地址数据
	ATT7022_WSPI(ucBuf, 0x00);

	if(memcmp(ucBuf,ucString,3)==0)
	{
		if(ucMode==1)
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		if(ucMode==1)
		{
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}

}
#endif
//************************************************************
//7022 calibration meter permmission
unsigned char ATT7022_ADJEn(void) {
	//const	unsigned char ucString[3]={0x20,0x03,0x16};

	unsigned char ucBuf[3];

	ucBuf[0] = 0;
	ucBuf[1] = 0;
	ucBuf[2] = 0;

	ATT7022_WReg(ucBuf, 0xc9);

	return TRUE;
}
//************************************************************
//7022 calibration meter prohibition
unsigned char ATT7022_ADJUn(void) {
	unsigned char i;
	unsigned char ucBuf[3], ucBak[3];
	const unsigned char LockSring[] = { 0x20, 0x03, 0x61 };

	ucBuf[0] = 0;
	ucBuf[1] = 0;
	ucBuf[2] = 0x01;

	for (i = 0; i < 3; i++) {
		ATT7022_WSPI(ucBuf, 0xc9);
		ATT7022_RSPI(ucBak, 0x2d);
		if (memcmp(ucBak, LockSring, 3) == 0) {
			break;
		}
	}

	return TRUE;
}
//************************************************************
//7022 software reset
void ATT7022_SoftRst(void) {
	unsigned char ucBuf[3];

	ucBuf[0] = 0;
	ucBuf[1] = 0;
	ucBuf[2] = 0;

	ATT7022_WSPI(ucBuf, 0xd3);
}

//************************************************************
/*//the following is the first step of meter calibration	*/
void ATT7022_AdjSep1(void) {
	unsigned char i;
	unsigned int uiTime;
	unsigned char ucBuf[3];
	unsigned long ulTmp;

	for (i = 0; i < 3; i++) {// software reset
		ATT7022_SoftRst();
		//waite to enter into
		uiTime = 0;
		while (ATT7022_SPI_SIG()) {
			uiTime++;
			DelayMs(1);
			if (uiTime > 200) {
				break;
			}
		}
		if (uiTime < 200) {
			break;
		}
	}
	//initialization failure
	if (i == 3) {
		//while(1);	
	}

	ATT7022_ADJClr();
	ATT7022_ADJEn();
	//writing meter calibration parameter
	//voltage channel amplification
	ATT7022_WReg((int8u*) UGTbl, ATT7022_UADCPg);
	//impulse output
	/*
	 ulTmp=(unsigned char)HF_VAL;
	 ucBuf[0]=(char)(ulTmp/0x10000);
	 ucBuf[1]=(char)(ulTmp/0x100);
	 ucBuf[2]=(char)ulTmp;
	 */
	FRAM_Read((char*) ucBuf, Adj_Para_FHConst, 3);
	ATT7022_WReg(ucBuf, ATT7022_HFConst);
	//starting current
	FRAM_Read((char*) ucBuf, Adj_Para_StartI, 3);
	ATT7022_WReg((int8u*) IStartUPTab, ATT7022_IStartup);
	//loss of phase, later period judgement adopts software judgement, and there is no using chip function.
	ulTmp = (unsigned long) FV_VAL;
	ucBuf[0] = (char) (ulTmp / 0x10000);
	ucBuf[1] = (char) (ulTmp / 0x100);
	ucBuf[2] = (char) ulTmp;
	ATT7022_WReg((int8u*) ucBuf, ATT7022_FAILVoltage);
	//phase compensation, and there are two phases
	memset(ucBuf, 0, 3);
	ATT7022_WReg(ucBuf, ATT7022_Iregion1);
	ATT7022_WReg(ucBuf, ATT7022_Iregion2);
	ATT7022_WReg(ucBuf, ATT7022_Iregion3);

	FRAM_Read((char*) ucBuf, Adj_Para_Iregion, 3);
	ATT7022_WReg(ucBuf, ATT7022_Iregion4);
	//not set, all zeros
#if	(ATT7022_STEP_EN==1)//
	//amplification segment register
	FRAM_Read((char*) ucBuf, Adj_Para_Iregchg, 3);
	ATT7022_WReg(ucBuf, ATT7022_Irechg);
#else
	memset(ucBuf,0,3);
	ATT7022_WReg(ucBuf, ATT7022_Irechg);
#endif	

}
//************************************************************
/*//the following is the sixth step of meter calibration	*/
void ATT7022_AdjSep6(void) {
	ATT7022_ADJUn();
}
//register

/******************************************************************************
 * //ATT7022_AdjSep2 -writing in amplification value with segment
 ******************************************************************************/
void ATT7022_AdjSep2(unsigned char *ucBuf, unsigned char ucPhase) {
	ATT7022_WReg(ucBuf, ucPhase);

	switch (ucPhase) {
	case PHASE_A0:
		ATT7022_WReg(ucBuf, ATT7022_PgainA0);
		break;
	case PHASE_B0:
		ATT7022_WReg(ucBuf, ATT7022_PgainB0);
		break;
	case PHASE_C0:
		ATT7022_WReg(ucBuf, ATT7022_PgainC0);
		break;
	case PHASE_A1:
		ATT7022_WReg(ucBuf, ATT7022_PgainA1);
		break;
	case PHASE_B1:
		ATT7022_WReg(ucBuf, ATT7022_PgainB1);
		break;
	case PHASE_C1:
		ATT7022_WReg(ucBuf, ATT7022_PgainC1);
		break;
	default:
		break;
	}

	//
}

/******************************************************************************
 * //ATT7022_AdjSep3 -phase calibration
 ******************************************************************************/
void ATT7022_AdjSep3(unsigned char *ucBuf, unsigned char ucPhase) {

	switch (ucPhase) {
	case PHASE_A0:
		ATT7022_WReg(ucBuf, ATT7022_PhsregA0);
		ATT7022_WReg(ucBuf, ATT7022_PhsregA1);
		ATT7022_WReg(ucBuf, ATT7022_PhsregA2);
		ATT7022_WReg(ucBuf, ATT7022_PhsregA3);
		break;
	case PHASE_B0:
		ATT7022_WReg(ucBuf, ATT7022_PhsregB0);
		ATT7022_WReg(ucBuf, ATT7022_PhsregB1);
		ATT7022_WReg(ucBuf, ATT7022_PhsregB2);
		ATT7022_WReg(ucBuf, ATT7022_PhsregB3);
		break;
	case PHASE_C0:
		ATT7022_WReg(ucBuf, ATT7022_PhsregC0);
		ATT7022_WReg(ucBuf, ATT7022_PhsregC1);
		ATT7022_WReg(ucBuf, ATT7022_PhsregC2);
		ATT7022_WReg(ucBuf, ATT7022_PhsregC3);
		break;
	case PHASE_A1:
		ATT7022_WReg(ucBuf, ATT7022_PhsregA4);
		break;
	case PHASE_B1:
		ATT7022_WReg(ucBuf, ATT7022_PhsregB4);
		break;
	case PHASE_C1:
		ATT7022_WReg(ucBuf, ATT7022_PhsregC4);
		break;
	default:
		break;
	}
}

/******************************************************************************
 * //equivalent voltage calibration
 ******************************************************************************/
void ATT7022_AdjSep4(unsigned char *ucBuf, unsigned char ucPhase) {
	switch (ucPhase) {
	case PHASE_A0:
	case PHASE_A1:
		ATT7022_WReg(ucBuf, ATT7022_UgainA);
		break;
	case PHASE_B0:
	case PHASE_B1:
		ATT7022_WReg(ucBuf, ATT7022_UgainB);
		break;
	case PHASE_C0:
	case PHASE_C1:
		ATT7022_WReg(ucBuf, ATT7022_UgainC);
		break;
	default:
		break;
	}
}

/******************************************************************************
 * //ATT7022_AdjSep5 -current calibration
 ******************************************************************************/
void ATT7022_AdjSep5(unsigned char *ucBuf, unsigned char ucPhase) {
	switch (ucPhase) {
	case PHASE_A0:
	case PHASE_A1:
		ATT7022_WReg(ucBuf, ATT7022_IgainA);
		break;
	case PHASE_B0:
	case PHASE_B1:
		ATT7022_WReg(ucBuf, ATT7022_IgainB);
		break;
	case PHASE_C0:
	case PHASE_C1:
		ATT7022_WReg(ucBuf, ATT7022_IgainC);
		break;
	default:
		break;
	}
}
//************************************************************
//delay programme
void ATT7022_Delay(void) {
	int16u i;
	int16u j;

	for (i = 0; i < 1800; i++) {
		for (j = 0; j < 1000; j++) {
		}
		WDTClr();
	}

}
//************************************************************
//7022 initialization
void ATT7022_Init(void) {

	const int8u AdjPhTbl[] = { PHASE_A0, PHASE_B0, PHASE_C0, PHASE_A1,
			PHASE_B1, PHASE_C1 };

	const int16u AdjParaGainTbl[] =
			{ Adj_Para_GAINA0, Adj_Para_GAINB0, Adj_Para_GAINC0,
					Adj_Para_GAINA1, Adj_Para_GAINB1, Adj_Para_GAINC1 };

	const int16u AdjParaPhaseTbl[] = { Adj_Para_PHASEA0, Adj_Para_PHASEB0,
			Adj_Para_PHASEC0, Adj_Para_PHASEA1, Adj_Para_PHASEB1,
			Adj_Para_PHASEC1 };

	const int16u AdjParaVRAMTbl[] = { Adj_Para_VRAM_A, Adj_Para_VRAM_B,
			Adj_Para_VRAM_C };

	const int16u AdjParaIRAMTbl[] = { Adj_Para_IRAM_A, Adj_Para_IRAM_B,
			Adj_Para_IRAM_C };

	unsigned char ucBuf[3];

	unsigned char i;
	//read meter calibration parameter

	//active/reactive form of measurement form of electric energy calculation
	FRAM_Read((char*) &gsAttPara.Mode[0], kWCumuMode, 3); //
	//form of impulse terminal
	//FRAM_Read(&Flag.PortDf, PortDefine, 1);						//

	//reset
	ATT7022_CLR_REST();
	DelayMs(2);
	ATT7022_SET_REST();

	ATT7022_RReg(ucBuf, ATT7022_CHK);

	//write in synthetic model of metering
	//three phase four wire 01, corresponding algebraic sum, 00, absolute value
	//three phase three wire 01, corresponding algebraic sum, 00, corresponding algebraic sum
	ATT7022_WReg(&gsAttPara.Mode[2], ATT7022_EAndMode);

	//write in meter calibration parameter
	ATT7022_AdjSep1();
	//amplification, two segments
#if	(ATT7022_STEP_EN==1)	//6*3
	for (i = 0; i < 6; i++) {
		FRAM_Read((char*) ucBuf, AdjParaGainTbl[i], 3);
		ATT7022_AdjSep2(ucBuf, AdjPhTbl[i]);
	}
#else
	for(i=0;i<3;i++) //3*3
	{
		FRAM_Read((char*)ucBuf, AdjParaGainTbl[i], 3);
		ATT7022_AdjSep2(ucBuf,AdjPhTbl[i]);
	}
#endif	
	//phase, two segments
	for (i = 0; i < 6; i++) //6*3
	{
		FRAM_Read((char*) ucBuf, AdjParaPhaseTbl[i], 3);
		ATT7022_AdjSep3(ucBuf, AdjPhTbl[i]);
	}

	//voltage effective value
	for (i = 0; i < 3; i++) //3*3
	{
		FRAM_Read((char*) ucBuf, AdjParaVRAMTbl[i], 3);
		ATT7022_AdjSep4(ucBuf, AdjPhTbl[i]);
	}
	//current effective value
	for (i = 0; i < 3; i++) //3*4
	{
		FRAM_Read((char*) ucBuf, AdjParaIRAMTbl[i], 3);
		ATT7022_AdjSep5(ucBuf, AdjPhTbl[i]);
	}

#ifdef HARDWARE_TWO
	//write in fundamental wave measure ment to control register, with PQS apparent table
	ucBuf[0] = 0x00;
	ucBuf[1] = 0x55;
	ucBuf[2] = 0x23;
	ATT7022_WReg(&ucBuf[0], ATT7022_EnlineFreq);
#endif

	//exit meter calibration parameter configuration
	ATT7022_AdjSep6();
	//ATT7022_Delay();
	//it takes 1/3S to finish giving check code
	//reading check code
	//ATT7022_RReg(guAttChk,ATT7022_CHK);

}
//************************************************************
//7022 hexadecimal changes into decimal
void ATT7022_HEX3Long(int8u *ucBuf, int32u *Data) {
	int8u i;
	int32u ulD;

	ulD = 0;
	for (i = 0; i < 3; i++) {
		ulD <<= 8;
		ulD |= ucBuf[i];
	}
	*Data = ulD;
}

//************************************************************
//real time parameter reading
unsigned char ATT7022_RMSRead(unsigned long *ulData, unsigned char *ucDir,
		unsigned char ucType) {
	unsigned char ucBuf[3];
	unsigned long ulTmp;
	float flTmp;

	*ucDir = 0;

	switch (ucType) {
	case ATT7022_r_URmsa:
	case ATT7022_r_URmsb:
	case ATT7022_r_URmsc:
		ATT7022_RReg(ucBuf, ucType);
		ATT7022_HEX3Long(ucBuf, &ulTmp);
		//0.1 decimals
		ulTmp *= 10; //0.1小数
		//unit V
		ulTmp = ulTmp / 8192;//16384;	//单位V
		break;
	case ATT7022_r_IRmsa:
	case ATT7022_r_IRmsb:
	case ATT7022_r_IRmsc:
		ATT7022_RReg(ucBuf, ucType);
		ATT7022_HEX3Long(ucBuf, &ulTmp);
		//place decimal
		ulTmp *= 100; //2位小数
		//unit I
		ulTmp = ulTmp / (8192); //单位I
		break;
		//
	case ATT7022_r_Pa:
	case ATT7022_r_Pb:
	case ATT7022_r_Pc:
	case ATT7022_r_Pt:
		ATT7022_RReg(ucBuf, ucType);
		ATT7022_HEX3Long(ucBuf, &ulTmp);
		if (ulTmp & 0x00800000)
		//if((ulTmp&0x00FFFFFF) >  0x00800000)
		{
			ulTmp = ~ulTmp + 1;
			ulTmp &= 0x7fffff;
			*ucDir = 1;
		}
		if (ucType == ATT7022_r_Pt) {
			ulTmp /= 64;
		} else {
			ulTmp /= 256;
		}
		ulTmp = ulTmp * 3200 / FC_CP;
		break;
		//
	case ATT7022_r_Qa:
	case ATT7022_r_Qb:
	case ATT7022_r_Qc:
	case ATT7022_r_Qt:
		ATT7022_RReg(ucBuf, ucType);
		ATT7022_HEX3Long(ucBuf, &ulTmp);

		//*ucDir=1;//**************************************

		if (ulTmp & 0x00800000)
		//if((ulTmp&0x00FFFFFF) >  0x00800000)
		{
			ulTmp = ~ulTmp + 1;
			ulTmp &= 0x7fffff;
			*ucDir = 1;
		}
		if (ucType == ATT7022_r_Qt) {
			ulTmp /= 64;
		} else {
			ulTmp /= 256;
		}
		ulTmp = ulTmp * 3200 / FC_CP;
		break;
	case ATT7022_r_Sa:
	case ATT7022_r_Sb:
	case ATT7022_r_Sc:
	case ATT7022_r_St:
		ATT7022_RReg(ucBuf, ucType);
		ATT7022_HEX3Long(ucBuf, &ulTmp);

		//*ucDir=1;//**************************************

		if (ulTmp & 0x00800000)
		//if((ulTmp&0x00FFFFFF) >  0x00800000)
		{
			ulTmp = ~ulTmp + 1;
			ulTmp &= 0x7fffff;
			*ucDir = 1;
		}
		if (ucType == ATT7022_r_St) {
			ulTmp /= 64;
		} else {
			ulTmp /= 256;
		}
		ulTmp = ulTmp * 3200 / FC_CP;
		break;
	case ATT7022_freq:
		ATT7022_RReg(ucBuf, ucType);
		ATT7022_HEX3Long(ucBuf, &ulTmp);
		//place decimal
		ulTmp *= 10; //1位小数
		//unit I
		ulTmp = ulTmp / (8192); //单位I
		break;
	case ATT7022_pg_a:
	case ATT7022_Pg_b:
	case ATT7022_Pg_c:
	case ATT7022_Pg_t:
		ATT7022_RReg(ucBuf, ucType);
		ATT7022_HEX3Long(ucBuf, &ulTmp);
		*ucDir = 0;
		if (ulTmp & 0x00800000) {
			ulTmp = ~ulTmp + 1;
			ulTmp &= 0x7fffff;
			*ucDir = 1;
		}
		flTmp = ulTmp;
		flTmp = (flTmp * 2 * 180) / (3.1415926 * 8388608);
		ulTmp = (unsigned long) (flTmp * 10);
		break;
	case ATT7022_Flag:
		ATT7022_RReg(ucBuf, ucType);
		ATT7022_HEX3Long(ucBuf, &ulTmp);
		break;
	case ATT7022_PFa:
	case ATT7022_PFb:
	case ATT7022_PFc:
	case ATT7022_PFt:
		ATT7022_RReg(ucBuf, ucType);
		ATT7022_HEX3Long(ucBuf, &ulTmp);
		if ((ulTmp & 0x00FFFFFF) > 0x00800000)

		{
			ulTmp = ~ulTmp + 1;
			ulTmp &= 0x7fffff;
		}
		flTmp = ulTmp;
		flTmp = flTmp / 8388608;
		// place decimal
		ulTmp = (unsigned long) (flTmp * 1000); //1位小数
		break;
	default:
		break;
	}

	*ulData = ucType;
	*ulData = ulTmp;

	return TRUE;

}
//************************************************************
//energy reading
unsigned int ATT7022_EnergyRead(unsigned char ucType) {
	unsigned long ulTmp;
	unsigned int uiTmp;
	unsigned char ucBuf[3];

	ATT7022_RReg(ucBuf, ucType);

	ATT7022_HEX3Long(ucBuf, &ulTmp);

	uiTmp = (unsigned int) ulTmp;

	return uiTmp;
}
//************************************************************
//data zero clearing
void ATT7022_RAMClear(void) {

	//ATT7022_RAMClear();
	memset(&gsAttBCDVal, 0, sizeof(gsAttBCDVal));
	memset(&gsAttRealVal, 0, sizeof(gsAttRealVal));
	memset(&gsAttPara, 0, sizeof(gsAttPara));

}

/*******************************************************************************
 function name: ATT7022_ParaChk
 * description:  compare the meter calibration value of the measurement chip to the conserved check code and see if they are the same
 * input:
 * output:
 * backspace:
 * notice:

 *******************************************************************************/
unsigned char ATT7022_ParaChk(void) {
	int8u ucBuf[3];

	ATT7022_RReg(ucBuf, ATT7022_CHK);
	if (memcmp(guAttChk, ucBuf, 3) == 0) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/******************************************************************************
 * ATT7022_Process-calculating transient sum plus energy
 ATT7022_Process -
 ******************************************************************************/

extern unsigned char meter_state[];

unsigned char ATT7022_Process(void) {

	unsigned char const ucLowUTbl[] = { 0x01, 0x02, 0x04 };
	unsigned char i;
	unsigned char ucDir;//,ucBuf[8];
	//unsigned int uiPBit,uiQBit;
	unsigned long ulTmp;
	unsigned int uiTmp;

	unsigned long ulFu;

	if ((Flag.Power & F_PwrUp) != F_PwrUp) {
		return 0;
	}

	//loss of phase value percentage divides 100, VRMS a decimal, so equals to /10
	//FRAM_Read((char*)ucBuf,Val_VFailure,2); 
	//ulFu=(unsigned long)FC_Un*BCD2_Word(ucBuf);
	ulFu = (unsigned long) FC_Un;

	//read symbol status
	//ATT7022_Flag
	ATT7022_RMSRead(&ulTmp, &ucDir, ATT7022_Flag);

	//read ATT7022 chip mistaking standards, using software to judge decompression
	gsAttRealVal.Att7022Flag = ulTmp;
	//sign bit zero clearing first
	gsAttRealVal.DIR_Flag = 0;
	//calculate equivalent voltage
	for (i = 0; i < 3; i++) {
		ATT7022_RMSRead(&ulTmp, &ucDir, VRMSTbl[i]);
		gsAttRealVal.VRMS[i] = ulTmp;
		Long_BCD4((char*) gsAttBCDVal.VRMS[i], ulTmp);

		if (ulTmp > ulFu) {
			gsAttRealVal.Att7022Flag |= ucLowUTbl[i];
		} else {
			gsAttRealVal.Att7022Flag &= ~ucLowUTbl[i];
		}
	}

	//frequency
	ATT7022_RMSRead(&ulTmp, &ucDir, ATT7022_freq);
	gsAttRealVal.FREQ[0] = ulTmp;
	Long_BCD4((char*) &gsAttBCDVal.FREQ[0], ulTmp);
	//calculate equivalent current
	for (i = 0; i < 3; i++) {
		ATT7022_RMSRead(&ulTmp, &ucDir, IRMSTbl[i]);
		gsAttRealVal.IRMS[i] = ulTmp;
		Long_BCD4((char*) gsAttBCDVal.IRMS[i], ulTmp);
	}

	meter_state[0] &= ~STA_FX_CURR;
	//active power
	for (i = 0; i < 4; i++) {
		ATT7022_RMSRead(&ulTmp, &ucDir, PTbl[i]);
		gsAttRealVal.Power_Real[i] = ulTmp;
		Long_BCD4((char*) gsAttBCDVal.Power_Real[i], ulTmp);

		//only there is equivalent voltage, current can be judged
		if (((gsAttRealVal.Att7022Flag & ucLowUTbl[i]) || (i == 3)) && (ulTmp
				> 5)) {
			if (ucDir == 1) {
				gsAttRealVal.DIR_Flag |= PDirTbl[i];
				meter_state[0] |= STA_FX_CURR;

			}
		}
	}
	//actove power
	for (i = 0; i < 4; i++) {
		ATT7022_RMSRead(&ulTmp, &ucDir, QTbl[i]);
		gsAttRealVal.Var_Real[i] = ulTmp;
		Long_BCD4((char*) gsAttBCDVal.Var_Real[i], ulTmp);
		if (ucDir == 1) {
			gsAttRealVal.DIR_Flag |= QDirTbl[i];
		}
	}
	//apparent power
	for (i = 0; i < 4; i++) {
		ATT7022_RMSRead(&ulTmp, &ucDir, STbl[i]);
		gsAttRealVal.APPA_Real[i] = ulTmp;
		Long_BCD4((char*) gsAttBCDVal.APPA_Real[i], ulTmp);
	}
	//power factor
	for (i = 0; i < 4; i++) {
		ATT7022_RMSRead(&ulTmp, &ucDir, ATT7022_PFa + i);
		gsAttRealVal.PF[i] = ulTmp;
		Long_BCD4((char*) gsAttBCDVal.PF[i], ulTmp);
	}
	//read energy data power
	for (i = 0; i < 4; i++) {
		uiTmp = ATT7022_EnergyRead(Epa2Tbl[i]);
		if (uiTmp > 50)
			uiTmp = 0;//**************************
		if (gsAttRealVal.DIR_Flag & PDirTbl[i]) {
			gsAttRealVal.Pulse_ActiF[i] = uiTmp;
		} else {
			gsAttRealVal.Pulse_Acti[i] = uiTmp;
		}
	}
	//read energy data apparent (directionality stays the same with active power)
	for (i = 0; i < 4; i++) {
		uiTmp = ATT7022_EnergyRead(LEpa2Tbl[i]);
		if (uiTmp > 50)
			uiTmp = 0;//**************************
		if (gsAttRealVal.DIR_Flag & PDirTbl[i]) {
			gsAttRealVal.Pulse_AppaF[i] = uiTmp;
		} else {
			gsAttRealVal.Pulse_Appa[i] = uiTmp;
		}
	}
	//angle
	for (i = 0; i < 4; i++) {
		ATT7022_RMSRead(&ulTmp, &ucDir, ATT7022_pg_a + i);

		if (ucDir == 1) {
			//gsAttRealVal.DIR_Flag |= ATT7022_DIR_ANGLE;
			gsAttRealVal.DIR_Flag |= ADirTbl[i];
		}
		//quadrant judgement
		if (gsAttRealVal.DIR_Flag & PDirTbl[i]) {
			if (gsAttRealVal.DIR_Flag & QDirTbl[i]) {
				//
				gsAttRealVal.QuadNo = 3;
				ulTmp = 1800 - ulTmp;
			} else {
				//
				gsAttRealVal.QuadNo = 2;

				ulTmp = 1800 - ulTmp;
			}
		} else {
			if (gsAttRealVal.DIR_Flag & QDirTbl[i]) {
				//the forth quadrant
				gsAttRealVal.QuadNo = 4;

				ulTmp = ulTmp;
			} else {
				//the first quadrant
				gsAttRealVal.QuadNo = 1;

				ulTmp = ulTmp;
			}
		}

		gsAttRealVal.PG[i] = ulTmp;

		Long_BCD4((char*) gsAttBCDVal.PG[i], ulTmp);
	}

	//split-phase in four quadrants
	for (i = 0; i < 4; i++) {
		uiTmp = ATT7022_EnergyRead(Eqa2Tbl[i]);

		if (gsAttRealVal.DIR_Flag & PDirTbl[i]) {
			if (gsAttRealVal.DIR_Flag & QDirTbl[i]) {
				gsAttRealVal.Quadrant[i] = QUADRANT_III;
			} else {

				gsAttRealVal.Quadrant[i] = QUADRANT_II;
			}
		} else {
			if (gsAttRealVal.DIR_Flag & QDirTbl[i]) {
				gsAttRealVal.Quadrant[i] = QUADRANT_IV;
			} else {

				gsAttRealVal.Quadrant[i] = QUADRANT_I;
			}
		}

		switch (gsAttRealVal.Quadrant[i]) {
		case QUADRANT_I:
			gsAttRealVal.Pulse_ReacRQ1[i] += uiTmp;
			break;
		case QUADRANT_II:
			gsAttRealVal.Pulse_ReacRQ2[i] += uiTmp;
			break;
		case QUADRANT_III:
			gsAttRealVal.Pulse_ReacRQ3[i] += uiTmp;
			break;
		case QUADRANT_IV:
			gsAttRealVal.Pulse_ReacRQ4[i] += uiTmp;
			break;
		}
	}
	//forward and reverse reactive combination form
	//正反向无功组合方式
	/*
	 0： +R=I+II, -R=III+IV
	 1：	+R=I+IV, -R=II+III
	 5： +R=I+II+III+IV, -R=0
	 7：+R=I+II+III+IV, -R=II+III
	 */
	switch (gsAttPara.Mode[1]) {
	case 0x00:
		gsAttRealVal.Pulse_ReacRQ = gsAttRealVal.Pulse_ReacRQ1[3]\

				+ gsAttRealVal.Pulse_ReacRQ2[3];
		gsAttRealVal.Pulse_ReacRQF = gsAttRealVal.Pulse_ReacRQ3[3]\

				+ gsAttRealVal.Pulse_ReacRQ4[3];

		break;

	case 0x01:
		gsAttRealVal.Pulse_ReacRQ = gsAttRealVal.Pulse_ReacRQ1[3]\

				+ gsAttRealVal.Pulse_ReacRQ4[3];
		gsAttRealVal.Pulse_ReacRQF = gsAttRealVal.Pulse_ReacRQ2[3]\

				+ gsAttRealVal.Pulse_ReacRQ3[3];

		break;

	case 0x05:
		gsAttRealVal.Pulse_ReacRQ = gsAttRealVal.Pulse_ReacRQ1[3]\

				+ gsAttRealVal.Pulse_ReacRQ2[3]\
 + gsAttRealVal.Pulse_ReacRQ3[3]\

				+ gsAttRealVal.Pulse_ReacRQ4[3];
		gsAttRealVal.Pulse_ReacRQF = 0;
		break;
	case 0x07:
		gsAttRealVal.Pulse_ReacRQ = gsAttRealVal.Pulse_ReacRQ1[3]\

				+ gsAttRealVal.Pulse_ReacRQ2[3]\
 + gsAttRealVal.Pulse_ReacRQ3[3]\

				+ gsAttRealVal.Pulse_ReacRQ4[3];
		gsAttRealVal.Pulse_ReacRQF = gsAttRealVal.Pulse_ReacRQ2[3]
				+ gsAttRealVal.Pulse_ReacRQ3[3];
		break;
	}

	return 0;
}

/******************************************************************************
 *CalcPulse -reading chip impulse
 CalcPulse -
 ******************************************************************************/
void CalcPulse(void) {
	int8u i;

	//forward active power
	if (gsAttRealVal.Pulse_Acti[3] != 0) {
		SM.PpCnt += gsAttRealVal.Pulse_Acti[3];
		MaxD.D_Pp_Cumu += gsAttRealVal.Pulse_Acti[3];
	}
	//reverse active power
	if (gsAttRealVal.Pulse_ActiF[3] != 0) {
		SM.PnCnt += gsAttRealVal.Pulse_ActiF[3];
		MaxD.D_Pn_Cumu += gsAttRealVal.Pulse_ActiF[3];

		switch (gsAttPara.Mode[0]) {
		case 0:
			break;
		case 1:
			SM.PpCnt += gsAttRealVal.Pulse_ActiF[3];
			break;
		}

	}
	//forward apparent
	if (gsAttRealVal.Pulse_Appa[3] != 0) {
		SM.VApCnt += gsAttRealVal.Pulse_Appa[3];
		MaxD.D_Qp_Cumu += gsAttRealVal.Pulse_Appa[3];
	}
	//reverse apparent
	if (gsAttRealVal.Pulse_AppaF[3] != 0) {
		SM.VAnCnt += gsAttRealVal.Pulse_AppaF[3];
		MaxD.D_Qn_Cumu += gsAttRealVal.Pulse_AppaF[3];

		switch (gsAttPara.Mode[0]) {
		case 0:
			break;
		case 1:
			SM.VApCnt += gsAttRealVal.Pulse_AppaF[3];
			break;
		}
	}
	//reactive forward
	if (gsAttRealVal.Pulse_ReacRQ != 0) {
		SM.RpCnt += gsAttRealVal.Pulse_ReacRQ;
		MaxD.D_Rp_Cumu += gsAttRealVal.Pulse_ReacRQ;
	}
	//reactive reverse
	if (gsAttRealVal.Pulse_ReacRQF != 0) {
		SM.RnCnt += gsAttRealVal.Pulse_ReacRQF;
		MaxD.D_Rn_Cumu += gsAttRealVal.Pulse_ReacRQF;
	}
	//four quadrants reactive impulse
	SM.RQ[0] += gsAttRealVal.Pulse_ReacRQ1[3];
	MaxD.D_Qdr_Cumu[0] += gsAttRealVal.Pulse_ReacRQ1[3];

	SM.RQ[1] += gsAttRealVal.Pulse_ReacRQ2[3];
	MaxD.D_Qdr_Cumu[1] += gsAttRealVal.Pulse_ReacRQ2[3];

	SM.RQ[2] += gsAttRealVal.Pulse_ReacRQ3[3];
	MaxD.D_Qdr_Cumu[2] += gsAttRealVal.Pulse_ReacRQ3[3];

	SM.RQ[3] += gsAttRealVal.Pulse_ReacRQ4[3];
	MaxD.D_Qdr_Cumu[3] += gsAttRealVal.Pulse_ReacRQ4[3];

	for (i = 0; i < 3; i++) {
		//apparent split-phase ABC
		if (gsAttRealVal.Pulse_Appa[i] != 0) {
			SM.VApCntABC[i] += gsAttRealVal.Pulse_Appa[i];
		}
		if (gsAttRealVal.Pulse_AppaF[i] != 0) {
			SM.VAnCntABC[i] += gsAttRealVal.Pulse_AppaF[i];

			switch (gsAttPara.Mode[0]) {
			case 0:
				break;
			case 1:
				SM.VApCntABC[i] += gsAttRealVal.Pulse_AppaF[i];
				break;
			}
		}
		//active split-phase ABC
		if (gsAttRealVal.Pulse_Acti[i] != 0) {
			SM.PpCntABC[i] += gsAttRealVal.Pulse_Acti[i];
		}
		if (gsAttRealVal.Pulse_ActiF[i] != 0) {
			SM.PnCntABC[i] += gsAttRealVal.Pulse_ActiF[i];

			switch (gsAttPara.Mode[0]) {
			case 0:
				break;
			case 1:
				SM.PpCntABC[i] += gsAttRealVal.Pulse_ActiF[i];
				break;
			}
		}
		//reactive four quadrants ABC
		//I
		if (gsAttRealVal.Pulse_ReacRQ1[i] != 0) {
			SM.RQ1ABC[i] += gsAttRealVal.Pulse_ReacRQ1[i];

			switch (gsAttPara.Mode[1]) {
			case 0x00:
			case 0x01:
			case 0x05:
				SM.RpCntABC[i] += gsAttRealVal.Pulse_ReacRQ1[i];
				break;
			case 0x07:
				SM.RpCntABC[i] += gsAttRealVal.Pulse_ReacRQ1[i];
				break;
			}
		}
		//II
		if (gsAttRealVal.Pulse_ReacRQ2[i] != 0) {
			SM.RQ2ABC[i] += gsAttRealVal.Pulse_ReacRQ2[i];

			switch (gsAttPara.Mode[1]) {
			case 0x00:
			case 0x05:
				SM.RpCntABC[i] += gsAttRealVal.Pulse_ReacRQ2[i];
				break;
			case 0x01:
				SM.RnCntABC[i] += gsAttRealVal.Pulse_ReacRQ2[i];
				break;
			case 0x07:
				SM.RpCntABC[i] += gsAttRealVal.Pulse_ReacRQ2[i];
				SM.RnCntABC[i] += gsAttRealVal.Pulse_ReacRQ2[i];
				break;
			}
		}
		//III
		if (gsAttRealVal.Pulse_ReacRQ3[i] != 0) {
			SM.RQ3ABC[i] += gsAttRealVal.Pulse_ReacRQ3[i];

			switch (gsAttPara.Mode[1]) {
			case 0x00:
			case 0x01:
				SM.RnCntABC[i] += gsAttRealVal.Pulse_ReacRQ3[i];
				break;
			case 0x05:
				SM.RpCntABC[i] += gsAttRealVal.Pulse_ReacRQ3[i];
				break;
			case 0x07:
				SM.RpCntABC[i] += gsAttRealVal.Pulse_ReacRQ3[i];
				SM.RnCntABC[i] += gsAttRealVal.Pulse_ReacRQ3[i];
				break;
			}
		}
		//IV
		if (gsAttRealVal.Pulse_ReacRQ4[i] != 0) {
			SM.RQ4ABC[i] += gsAttRealVal.Pulse_ReacRQ4[i];

			switch (gsAttPara.Mode[1]) {
			case 0x00:
				SM.RnCntABC[i] += gsAttRealVal.Pulse_ReacRQ4[i];
				break;
			case 0x01:
			case 0x05:
				SM.RpCntABC[i] += gsAttRealVal.Pulse_ReacRQ4[i];
				break;
			case 0x07:
				SM.RpCntABC[i] += gsAttRealVal.Pulse_ReacRQ4[i];
				break;
			}
		}
	}
	//clear original data
	memset(gsAttRealVal.Pulse_Acti, 0, sizeof(gsAttRealVal.Pulse_Acti));
	memset(gsAttRealVal.Pulse_Appa, 0, sizeof(gsAttRealVal.Pulse_Appa));
	memset(gsAttRealVal.Pulse_ActiF, 0, sizeof(gsAttRealVal.Pulse_ActiF));
	memset(gsAttRealVal.Pulse_AppaF, 0, sizeof(gsAttRealVal.Pulse_AppaF));
	memset(gsAttRealVal.Pulse_ReacRQ1, 0, sizeof(gsAttRealVal.Pulse_ReacRQ1));
	memset(gsAttRealVal.Pulse_ReacRQ2, 0, sizeof(gsAttRealVal.Pulse_ReacRQ2));
	memset(gsAttRealVal.Pulse_ReacRQ3, 0, sizeof(gsAttRealVal.Pulse_ReacRQ3));
	memset(gsAttRealVal.Pulse_ReacRQ4, 0, sizeof(gsAttRealVal.Pulse_ReacRQ4));
	memset(&gsAttRealVal.Pulse_ReacRQ, 0, sizeof(gsAttRealVal.Pulse_ReacRQ));
	memset(&gsAttRealVal.Pulse_ReacRQF, 0, sizeof(gsAttRealVal.Pulse_ReacRQF));

}
#endif
