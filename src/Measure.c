#include "..\inc\includes.h"
//**********************************************************************
//clearing one minute power record
//**********************************************************************
void EC_1Min_Clear(void) {
	int i;
	for (i = 0; i < 10; i++)
		Buffer[i] = 0x00;
	MEM_DBWrite( EC_Pp1Min, (char*) &Buffer[0], 10, Mem_FRAM);
}
//**********************************************************************
//one minute forward active power add 1
//**********************************************************************
void EC_Pp1Min_INC(void) {
	FRAM_Read((char*) &Buffer[0], EC_Pp1Min, 5);
	_BCD5INC((char *) &Buffer[0]);
	MEM_DBWrite( EC_Pp1Min, (char *) &Buffer[0], 5, Mem_FRAM);
}

//**********************************************************************
//one minute reverse active power add 1
//**********************************************************************
void EC_Pn1Min_INC(void) {
	FRAM_Read((char*) &Buffer[0], EC_Pn1Min, 5);
	_BCD5INC((char *) &Buffer[0]);
	MEM_DBWrite( EC_Pn1Min, (char *) &Buffer[0], 5, Mem_FRAM);
}

/******************************************************************/
//function: accumulate total power quantity of FRAM and ecah tariff power quantity
//entrance:Adr_EC_Single: FRAM address                                  */
/******************************************************************/
void EC_INC(unsigned int Adr_EC) {
	int ID_ECFee;

	FRAM_Read((char *) &Buffer[0], Adr_EC, 25);
	_BCD5INC((char *) &Buffer[0]);
	//corresponding tariff of power quantity accumulates at the same time
	ID_ECFee = (Fee.CurrentFee) * 5;
	_BCD5INC((char *) &Buffer[ID_ECFee]);
	MEM_DBWrite(Adr_EC, (char *) &Buffer[0], 25, Mem_FRAM);
}
/*******************************************************************/
//function: accumulate split-phase power quantity in FRAM
//entrance: Adr_EC_Single: FRAM address
//Phase: bit0 bit1 bit2 represents split-phase, being 1 accumulates, being 0 non-accumulates
/*******************************************************************/
void EC_INC_Single(int Adr_EC_Single, unsigned char Phase) {
	FRAM_Read((char*) &Buffer[0], Adr_EC_Single, 15);
	if (Phase & 0x01)
		_BCD5INC((char*) &Buffer[0]);
	if (Phase & 0x02)
		_BCD5INC((char*) &Buffer[5]);
	if (Phase & 0x04)
		_BCD5INC((char*) &Buffer[10]);
	MEM_DBWrite((unsigned int) Adr_EC_Single, (char*) &Buffer[0], 15, Mem_FRAM);
}
/*******************************************************************/
//function: accumulate total/split-phase power quantity of four quadrants in FRAM
//entrance:Adr_EC_Q: FRAM address
//Phase: bit0 bit1 bit2 Bit3 represents total and split-phase, being 1 acuumulates, being 0 non-accumulates
/*******************************************************************/
void EC_INC_Q(int Adr_EC_Q, unsigned char Phase) {
	int Adr_EC_Q_Fee;
	int ID_EC_Q_Fee;

	FRAM_Read((char*) &Buffer[0], Adr_EC_Q, 20);
	if (Phase & 0x01) //总
		_BCD5INC((char*) &Buffer[0]);
	if (Phase & 0x02) //A
		_BCD5INC((char*) &Buffer[5]);
	if (Phase & 0x04) //B
		_BCD5INC((char*) &Buffer[10]);
	if (Phase & 0x08) //C
		_BCD5INC((char*) &Buffer[15]);
	MEM_DBWrite((unsigned int) Adr_EC_Q, (char*) &Buffer[0], 20, Mem_FRAM);

	//accumulates reactive quadrant total tariff power quantity
	if (Phase & 0x01) {
		if (Fee.CurrentFee > 0) {
			Adr_EC_Q_Fee = EC_Rq1F1 + (Adr_EC_Q - (EC_Rq1)); // (Adr_EC_Q - EC_Rq1)/18*18
			FRAM_Read((char*) &Buffer[0], Adr_EC_Q_Fee, 20);
			ID_EC_Q_Fee = (Fee.CurrentFee - 1) * 5; //CurrentFee 1 2 3 4
			_BCD5INC((char*) &Buffer[ID_EC_Q_Fee]);
			MEM_DBWrite((unsigned int) Adr_EC_Q_Fee, (char*) &Buffer[0], 20,
					Mem_FRAM);
		}
	}
}
/**********************************************************/
//function: accumulates power quantity base on impulse number, execute every second.
//entrance:                                                   */
/**********************************************************/
void ECMeas(void) {
	char i;

	register unsigned int Index;
	register unsigned int intTmp1;
	unsigned char Ph[3] = { 0x00, 0x00, 0x00 };

	if ((Flag.Power & F_PwrUp) == 0x00)
		return;

#if 0	
	//if (Flag.Run & R_Tst)	//if it's test module, only accumulates to TestMode buffer. active forward total reactive forward total
	if (Flag.Run & R_Tst) //如果是测试模式 只累计到TestMode 缓存中 有功正向总 无功正向总
	{
		if ((SM.PpCnt >= FC_CPD_Tst) || (SM.RpCnt >= FC_CPD_Tst))
		{
			FRAM_Read((char*)Buffer, Tst_EC_Pp0, 10);
			if (SM.PpCnt >= FC_CPD_Tst)
			{
				_DINT();
				SM.PpCnt -= FC_CPD_Tst;
				_EINT();
				_BCD5INC((char*)&Buffer[0] );
			}
			if (SM.RpCnt >= FC_CPD_Tst)
			{
				_DINT();
				SM.RpCnt -= FC_CPD_Tst;
				_EINT();
				_BCD5INC((char*)&Buffer[5] );
			}
			MEM_DBWrite( (unsigned int)Tst_EC_Pp0, (char*)Buffer, 10, Mem_FRAM );
		}
		return;
	}
#endif	

	i = 0;
	while (SM.PpCnt >= FC_CPD) {
		i++;
		if (i > 10) {
			break;
		}
		//if (SM.PpCnt >= FC_CPD)	//forward active power quantity
		if (SM.PpCnt >= FC_CPD) //
		{
			_DINT();
			SM.PpCnt -= FC_CPD;
			_EINT();
			EC_INC(EC_Pp0);
			EC_Pp1Min_INC();
			//if(Buffer[21]!=0xFF)		
			//	_BCD4INC((char*)&DLLoadReg.Reg[Buffer[21]][0]);	
		}
	}

	i = 0;
	while (SM.PnCnt >= FC_CPD) {
		i++;
		if (i > 10) {
			break;
		}
		//if (SM.PnCnt >= FC_CPD)	//reverse active total power quantity 
		if (SM.PnCnt >= FC_CPD) //反向有功电量总
		{
			_DINT();
			SM.PnCnt -= FC_CPD;
			_EINT();
			EC_INC(EC_Pn0);
			EC_Pn1Min_INC();
		}
	}

	i = 0;
	while (SM.RpCnt >= FC_CPD) {
		i++;
		if (i > 10) {
			break;
		}
		//if (SM.RpCnt >= FC_CPD)	//forward reactive total power quantity
		if (SM.RpCnt >= FC_CPD) //
		{
			_DINT();
			SM.RpCnt -= FC_CPD;
			_EINT();
			EC_INC(EC_Rp0);
		}
	}
	i = 0;
	while (SM.RnCnt >= FC_CPD) {
		i++;
		if (i > 10) {
			break;
		}
		//if (SM.RnCnt >= FC_CPD)	//reverse reactive total power quantity
		if (SM.RnCnt >= FC_CPD) //反向无功电量总
		{
			_DINT();
			SM.RnCnt -= FC_CPD;
			_EINT();
			EC_INC(EC_Rn0);
		}
	}
	i = 0;
	while (SM.VApCnt >= FC_CPD) {

		i++;
		if (i > 10) {
			break;
		}
		//if (SM.VApCnt >= FC_CPD)	//forward apparent total power quantity  2006.3.9
		if (SM.VApCnt >= FC_CPD) //正向视在电量总	2006.3.9
		{
			SM.VApCnt -= FC_CPD;
			EC_INC(EC_Qp0);
		}
	}
	i = 0;
	while (SM.VAnCnt >= FC_CPD) {
		i++;
		if (i > 10) {
			break;
		}
		//if (SM.VAnCnt >= FC_CPD)	//reverse apparent total power quantity
		if (SM.VAnCnt >= FC_CPD) //反向视在电量总
		{
			SM.VAnCnt -= FC_CPD;
			EC_INC(EC_Qn0);
		}
	}

	for (Index = 0; Index < 3; Index++) {
		Ph[Index] = 0x00;
	}
	for (Index = 0; Index < 3; Index++) {
		//if (SM.PpCntABC[Index] >= FC_CPD)//active forward power quantity split-phase
		if (SM.PpCntABC[Index] >= FC_CPD)//有功正向电量 分相
		{
			SM.PpCntABC[Index] -= FC_CPD;
			Ph[0] |= ByteBit[Index];
		}
		//if (SM.PnCntABC[Index] >= FC_CPD)//active reverse power quantity split-phase
		if (SM.PnCntABC[Index] >= FC_CPD)//有功反向电量 分相
		{
			SM.PnCntABC[Index] -= FC_CPD;
			Ph[0] |= ByteBitTail[Index];
		}

		//if (SM.RpCntABC[Index] >= FC_CPD)//reactive forward power quantity split-phase
		if (SM.RpCntABC[Index] >= FC_CPD)//无功正向电量 分相
		{
			SM.RpCntABC[Index] -= FC_CPD;
			Ph[1] |= ByteBit[Index];
		}
		//if (SM.RnCntABC[Index] >= FC_CPD)//reactive reverse power quantity split-phase
		if (SM.RnCntABC[Index] >= FC_CPD)//无功反向电量 分相
		{
			SM.RnCntABC[Index] -= FC_CPD;
			Ph[1] |= ByteBitTail[Index];
		}

		//if (SM.VApCntABC[Index] >= FC_CPD)//apparent forward power quantity split-phase
		if (SM.VApCntABC[Index] >= FC_CPD)//视在正向电量 分相
		{
			SM.VApCntABC[Index] -= FC_CPD;
			Ph[2] |= ByteBit[Index];
		}
		//if (SM.VAnCntABC[Index] >= FC_CPD)//apparent reverse power quantity split-phase
		if (SM.VAnCntABC[Index] >= FC_CPD)//视在反向电量 分相
		{
			SM.VAnCntABC[Index] -= FC_CPD;
			Ph[2] |= ByteBitTail[Index];
		}
	}
	for (Index = 0; Index < 3; Index++) {
		intTmp1 = 34 * Index;
		if ((Ph[Index] & 0x0F) != 0x00)
			EC_INC_Single( EC_PpL1 + intTmp1, Ph[Index]);
		Ph[Index] >>= 4;
		if ((Ph[Index] & 0x0F) != 0x00)
			EC_INC_Single( EC_PnL1 + intTmp1, Ph[Index]);
	}

	//four quadrants reactive total/split-phase
	for (Index = 0; Index < 3; Index++) {
		Ph[Index] = 0x00;
	}
	for (Index = 0; Index < 2; Index++) {
		intTmp1 = Index << 1; //*2
		if (SM.RQ[intTmp1] >= FC_CPD) {
			SM.RQ[intTmp1] -= FC_CPD;
			Ph[Index] |= 0x01;
		}
		intTmp1 = (Index << 1) + 1;
		if (SM.RQ[intTmp1] >= FC_CPD) {
			SM.RQ[intTmp1] -= FC_CPD;
			Ph[Index] |= 0x10;
		}
	}

	for (Index = 0; Index < 3; Index++) {
		if (SM.RQ1ABC[Index] >= FC_CPD) {
			SM.RQ1ABC[Index] -= FC_CPD;
			Ph[0] |= ByteBit[Index + 1];
		}
		if (SM.RQ2ABC[Index] >= FC_CPD) {
			SM.RQ2ABC[Index] -= FC_CPD;
			Ph[0] |= ByteBit[Index + 4 + 1];
		}
		if (SM.RQ3ABC[Index] >= FC_CPD) {
			SM.RQ3ABC[Index] -= FC_CPD;
			Ph[1] |= ByteBit[Index + 1];
		}
		if (SM.RQ4ABC[Index] >= FC_CPD) {
			SM.RQ4ABC[Index] -= FC_CPD;
			Ph[1] |= ByteBit[Index + 4 + 1];
		}
	}
	for (Index = 0; Index < 2; Index++) {
		intTmp1 = 44 * Index;
		if ((Ph[Index] & 0x0F) != 0x00)
			EC_INC_Q( EC_Rq1 + intTmp1, Ph[Index]);
		Ph[Index] >>= 4;
		if ((Ph[Index] & 0x0F) != 0x00)
			EC_INC_Q( EC_Rq2 + intTmp1, Ph[Index]);
	}

	//recount check code
	SM.CntChk = CHECKWORD;
	for (Index = 0; Index < 40; Index++) {
		SM.CntChk += *(&SM.PpCnt + Index);
	}
#if 0	
	if (P53.Freq_Real[0][0]!=0x00 || P53.Freq_Real[0][1]!=0x00)
	{	Freq[0]=P53.Freq_Real[0][0]; Freq[1]=P53.Freq_Real[0][1];}
	else if (P53.Freq_Real[1][0]!=0x00 || P53.Freq_Real[1][1]!=0x00)
	{	Freq[0]=P53.Freq_Real[1][0]; Freq[1]=P53.Freq_Real[1][1];}
	else
	{	Freq[0]=P53.Freq_Real[2][0]; Freq[1]=P53.Freq_Real[2][1];}
#endif	
}
/**********************************************************/
//function:update user defined register value
//entrance:
//notice: call this function after updating ECMeas is necessary
/**********************************************************/
const int16u UserRegister[10] = { EC_Pp0, EC_Pn0, EC_Rp0, EC_Rn0, EC_Rq1,
		EC_Rq2, EC_Rq3, EC_Rq4, EC_Qp0, EC_Qn0 };
void CustomRegister(void) {
	int8u ucBuf[5], i;
	int32u ulTmp;
	long long udTmp[10];
	long long Userde[3];

	for (i = 0; i < 10; i++) {
		//FRAM_Read((char*)ucBuf, UserRegister[i] , 5);//default two decimals
		FRAM_Read((char*) ucBuf, UserRegister[i], 5);//默认是2位小数
		ulTmp = BCD4_Long((char*) ucBuf);
		udTmp[i] = (unsigned long long) ulTmp + ((unsigned long long) BCD_Byte(
				ucBuf[4])) * (unsigned long long) 100000000;
	}
	for (i = 0; i < 3; i++) {
		Userde[i] = 0;
		FRAM_Read((char*) ucBuf, USER_DEFINE + i * 2, 2);
		if ((ucBuf[1] != 0) || (ucBuf[0] != 0)) {
			// if(ucBuf[0]&0x02)//forward active
			if (ucBuf[0] & 0x02)//正向有功
				Userde[i] += udTmp[0];
			//if(ucBuf[0]&0x01)//reverse active
			if (ucBuf[0] & 0x01)//反向有功
				Userde[i] += udTmp[1];
			// if(ucBuf[1]&0x80)//forward reactive
			if (ucBuf[1] & 0x80)//正向无功
				Userde[i] += udTmp[2];
			//if(ucBuf[1]&0x40)//reverse reactive
			if (ucBuf[1] & 0x40)//反向无功
				Userde[i] += udTmp[3];
			// if(ucBuf[1]&0x20)//reactive first quadrant
			if (ucBuf[1] & 0x20)//无功一象限
				Userde[i] += udTmp[4];
			// if(ucBuf[1]&0x10)//reactive second quadrant
			if (ucBuf[1] & 0x10)//无功二象限
				Userde[i] += udTmp[5];
			//if(ucBuf[1]&0x08)//reactive third quadrant
			if (ucBuf[1] & 0x08)//无功三象限
				Userde[i] += udTmp[6];
			//if(ucBuf[1]&0x04)//reactive forth quadrant
			if (ucBuf[1] & 0x04)//无功四象限
				Userde[i] += udTmp[7];
			//if(ucBuf[1]&0x02)//forward apparent
			if (ucBuf[1] & 0x02)//正向视在
				Userde[i] += udTmp[8];
			// if(ucBuf[1]&0x01)//reverse apparent
			if (ucBuf[1] & 0x01)//反向视在
				Userde[i] += udTmp[9];
		}
		Long_BCD4((char*) UserdeBCD[i], (unsigned long) (Userde[i] % 100000000));
		Word_BCD2((char*) (&UserdeBCD[i][4]),
				(unsigned int) ((Userde[i] / 100000000) % 10000));
	}
}

//==================================================================
//compare if the demand of current slip frequency register is the maximum demand, and update maximum demand
//entrance parameter: unsigned long * ptrSlide points to the pointer of slip frequency register
// unsigned int srcFram correspond to maximum demand position in Fram
//char noChk whether add check when writing it
//backspace result:if Fram is written, then back to 1, or back to 0
//==================================================================
char MaxD2Fram(unsigned int *ptrSlide, unsigned int srcFram,
		unsigned long DCumu, unsigned int LPMD, CLK_T *pt_clk) {

	unsigned long long lngTmp;

	unsigned long lngTmp2;

	unsigned long long lnglngtmp;
	unsigned long *lngPtr;
	unsigned int *intPtr;
	//signed char i;
	signed int i;
	char RLT = 0x00;
	char Num;

	lngPtr = (unsigned long*) ptrSlide;
	intPtr = ptrSlide;
	lngTmp = 0;
	lngTmp2 = 0;
	//if (MaxD.SlidingT>=1200)    //>20 minutes
	if (MaxD.SlidingT >= 1200) //>20分钟
	{
		for (i = 0; i < MaxD.SlideNum; i++)
			lngTmp += *(lngPtr++);
		lngTmp = lngTmp - *((unsigned long*) ptrSlide + MaxD.SldStartID)
				+ DCumu;
	} else {

		for (i = 0; i < MaxD.SlideNum; i++)
			lngTmp += *(intPtr++);
		lngTmp = lngTmp - *(ptrSlide + MaxD.SldStartID) + DCumu;
	}

	lnglngtmp = lngTmp * 3600 * 1000 / MaxD.DemandT / FC_CP;

	lngTmp = (unsigned long) lnglngtmp;

	Long_BCD4((char*) &lngTmp2, (unsigned long) lngTmp);

	FRAM_Read((char*) Buffer, srcFram, 40);
	Buffer[50] = Buffer[3];
	Buffer[3] = 0x00;
	lngPtr = (unsigned long *) Buffer;

	lngTmp = 0;
	for (i = 0; i < 2; i++) {

		lngTmp |= Buffer[2 - i];

		lngTmp <<= 8;
	}

	lngTmp |= Buffer[0];

	//if ( lngTmp2 >lngTmp)	//BCD code save to Long type, compare size directly
	if (lngTmp2 > lngTmp) //BCD码存入Long型直接比较大小
	{

		memcpy(Buffer, (int8u*) &lngTmp2, 3);
		//...... Buffer[3]-Buffer[7]taking place time of updating maximum demand
		//...... Buffer[3]-Buffer[7]更新最大需量发生时间
		for (i = 0; i < 5; i++) {
			Buffer[3 + i] = *((*pt_clk).Min + i);
		}

		RLT = 0x01;
	} else {
		Buffer[3] = Buffer[50];
	}
	//preserve demand for load curve
	MEM_DBWrite(LPMD, (char*) &lngTmp2, 3, Mem_FRAM);

	if ((MDFeeSw.FeeCnt >= MaxD.SlideNum) || (Flag.Fee & FeeSW_XL)) {
		Num = MDFeeSw.FeeCnt;
		lngTmp = 0;
		lngTmp2 = 0;
		// if (MaxD.SlidingT>=1200)    //>20 minutes
		if (MaxD.SlidingT >= 1200) //>20分钟
		{
			lngPtr = (unsigned long*) ptrSlide + (MaxD.SldStartID);
			for (i = MaxD.SldStartID; i >= 0; i--) {
				lngTmp += *(lngPtr--);
				Num--;
				if (Num == 0)
					break;
			}
			if (Num > 0) {
				lngPtr = (unsigned long*) ptrSlide + (MaxD.SlideNum - 1);
				for (i = MaxD.SlideNum - 1; i >= 0; i--) {
					lngTmp += *(lngPtr--);
					Num--;
					if (Num == 0)
						break;
				}
			}
			lngTmp = lngTmp - *((unsigned long*) ptrSlide + MaxD.SldStartID)
					+ DCumu;
		} else {
			intPtr = ptrSlide + (MaxD.SldStartID);
			for (i = MaxD.SldStartID; i >= 0; i--) {
				lngTmp += *(intPtr--);
				Num--;
				if (Num == 0)
					break;
			}
			if (Num > 0) {
				intPtr = ptrSlide + (MaxD.SlideNum - 1);
				for (i = MaxD.SlideNum - 1; i >= 0; i--) {
					lngTmp += *(intPtr--);
					Num--;
					if (Num == 0)
						break;
				}
			}
			lngTmp = lngTmp - *(ptrSlide + MaxD.SldStartID) + DCumu;
		}

		lnglngtmp = lngTmp * 3600 * 1000 / MaxD.DemandT / FC_CP;

		lngTmp = (unsigned long) lnglngtmp;
		Long_BCD4((char*) &lngTmp2, (unsigned long) lngTmp);

		if (Flag.Fee & FeeSW_XL)
			Num = Fee.PreviousFee * 8 + 3;
		else
			Num = Fee.CurrentFee * 8 + 3;

		Buffer[50] = Buffer[Num];
		Buffer[Num] = 0x00;
		//lngPtr = (unsigned long *)(&Buffer[Num-3]);

		lngTmp = 0;
		for (i = 0; i < 2; i++) {

			lngTmp |= Buffer[Num - 1 - i];

			lngTmp <<= 8;
		}
		lngTmp |= Buffer[Num - 3];

		if (lngTmp2 > lngTmp) {

			memcpy(&Buffer[Num - 3], (int8u*) &lngTmp2, 3);

			//...... Buffer[3]-Buffer[7]taking place time of updating maximum demand
			//...... Buffer[3]-Buffer[7]更新最大需量发生时间
			for (i = 0; i < 5; i++) {
				Buffer[Num + i] = *((*pt_clk).Min + i);
			}
			RLT = 0x01;
		} else {
			Buffer[Num] = Buffer[50];
		}
	}

	if (RLT)
		MEM_DBWrite(srcFram, (char*) Buffer, 40, Mem_FRAM);

	//return RLT;     //if Fram has not been written, then back to 0
	return RLT; //如果没有写过Fram返回 0
}

//==================================================================
//execute every minute
//calculate current demand register
//if sliding time to settle slip frequency register of this time, and compare size, change maximum demand storage of FRAM
//==================================================================
void MDCumuCalc(CLK_T *pt_clk) {
	char i;
	char wrFram;

	if ((Flag.Power & F_PwrUp) == 0x00)
		return;

	// if (Flag.Run & R_Tst)	//backspace directly if it's test module
	if (Flag.Run & R_Tst) //如果是测试模式 直接返回
		return;

	if (MDFeeSw.FeeCnt < MaxD.SlideNum)
		MDFeeSw.FeeCnt++;

	//if sliding time to settle sliding register
	//MaxD.SlidingTm = MaxD.SlidingT; //update sliding counter
	MaxD.SlidingTm = MaxD.SlidingT; //更新滑差计时器

	//lngCumuMUL = 294912000/MaxD.DemandT; //294912000=36000*8192=3600<<13
	//MaxD2Fram(MaxD.D_Qp_Slide, MD_Qp, MaxD.D_Qp_Cumu, LP_CurrentD_Qp,pt_clk); //apparent forward demand
	MaxD2Fram(MaxD.D_Qp_Slide, MD_Qp, MaxD.D_Qp_Cumu, LP_CurrentD_Qp, pt_clk); //视在正向需量

	//MaxD2Fram(MaxD.D_Qn_Slide, MD_Qn, MaxD.D_Qn_Cumu, LP_CurrentD_Qn,pt_clk); //apparent reverse demand
	MaxD2Fram(MaxD.D_Qn_Slide, MD_Qn, MaxD.D_Qn_Cumu, LP_CurrentD_Qn, pt_clk); //视在反向需量

	//MaxD2Fram(MaxD.D_Pp_Slide, MD_Pp, MaxD.D_Pp_Cumu, LP_CurrentD_Pp,pt_clk); //active forward demand
	MaxD2Fram(MaxD.D_Pp_Slide, MD_Pp, MaxD.D_Pp_Cumu, LP_CurrentD_Pp, pt_clk); //有功正向需量

	//MaxD2Fram(MaxD.D_Pn_Slide, MD_Pn, MaxD.D_Pn_Cumu, LP_CurrentD_Pn,pt_clk); //active reverse demand
	MaxD2Fram(MaxD.D_Pn_Slide, MD_Pn, MaxD.D_Pn_Cumu, LP_CurrentD_Pn, pt_clk); //有功反向需量

	//MaxD2Fram(MaxD.D_Rp_Slide, MD_Rp, MaxD.D_Rp_Cumu, LP_CurrentD_Rp,pt_clk); //reactive forward demand
	MaxD2Fram(MaxD.D_Rp_Slide, MD_Rp, MaxD.D_Rp_Cumu, LP_CurrentD_Rp, pt_clk); //无功正向需量

	//MaxD2Fram(MaxD.D_Rn_Slide, MD_Rn, MaxD.D_Rn_Cumu, LP_CurrentD_Rn,pt_clk); //reactive reverse demand
	MaxD2Fram(MaxD.D_Rn_Slide, MD_Rn, MaxD.D_Rn_Cumu, LP_CurrentD_Rn, pt_clk); //无功反向需量

	wrFram = 0x00;
	for (i = 0; i < 4; i++) {
		wrFram |= MaxD2Fram(MaxD.D_Qdr_Slide[i], MD_Rq1 + i * 42,
				MaxD.D_Qdr_Cumu[i], LP_CurrentD_Qdr1 + i * 3, pt_clk); //无功四象限需量
	}

	// if (MaxD.SlidingT>=1200)    //>20 minutes
	if (MaxD.SlidingT >= 1200) //>20分钟
	{
		wrFram = MaxD.SldStartID << 2; // *2
		*((unsigned long*) &MaxD.D_Qp_Slide[wrFram]) = MaxD.D_Qp_Cumu;
		*((unsigned long*) &MaxD.D_Qn_Slide[wrFram]) = MaxD.D_Qn_Cumu;
		*((unsigned long*) &MaxD.D_Pp_Slide[wrFram]) = MaxD.D_Pp_Cumu;
		*((unsigned long*) &MaxD.D_Pn_Slide[wrFram]) = MaxD.D_Pn_Cumu;
		*((unsigned long*) &MaxD.D_Rp_Slide[wrFram]) = MaxD.D_Rp_Cumu;
		*((unsigned long*) &MaxD.D_Rn_Slide[wrFram]) = MaxD.D_Rn_Cumu;
		for (i = 0; i < 4; i++) {
			*((unsigned long*) &MaxD.D_Qdr_Slide[i][wrFram])
					= MaxD.D_Qdr_Cumu[i];
		}
	} else {
		MaxD.D_Qp_Slide[MaxD.SldStartID] = MaxD.D_Qp_Cumu;
		MaxD.D_Qn_Slide[MaxD.SldStartID] = MaxD.D_Qn_Cumu;
		MaxD.D_Pp_Slide[MaxD.SldStartID] = MaxD.D_Pp_Cumu;
		MaxD.D_Pn_Slide[MaxD.SldStartID] = MaxD.D_Pn_Cumu;
		MaxD.D_Rp_Slide[MaxD.SldStartID] = MaxD.D_Rp_Cumu;
		MaxD.D_Rn_Slide[MaxD.SldStartID] = MaxD.D_Rn_Cumu;
		for (i = 0; i < 4; i++) {
			MaxD.D_Qdr_Slide[i][MaxD.SldStartID] = MaxD.D_Qdr_Cumu[i];
		}
	}

	//Long accumulate register zero clearing
	//Long累积寄存器清零
	MaxD.D_Qp_Cumu = 0;
	MaxD.D_Qn_Cumu = 0;
	MaxD.D_Pp_Cumu = 0;
	MaxD.D_Pn_Cumu = 0;
	MaxD.D_Rp_Cumu = 0;
	MaxD.D_Rn_Cumu = 0;
	for (i = 0; i < 4; i++) {
		MaxD.D_Qdr_Cumu[i] = 0;
	}

	MaxD.SldStartID++;
	if (MaxD.SldStartID > MaxD.SlideNum - 1)
		MaxD.SldStartID = 0;

	MaxD.MDchk = ChkNum((char*) &MaxD, sizeof(MAXDEMAND_T) - 2);

	//if (Flag.Fee & FeeSW_XL)	//if there is tariff switch
	if (Flag.Fee & FeeSW_XL) //如果有费率切换
	{
		Flag.Fee &= ~FeeSW_XL;
		MDFeeSw.FeeCnt = 0;
	}

	//demand has already happened
	//需量已经发生
	Flag.MDClrFlag = 0;
}

//**********************************************************************
//maximum demand initialization
//**********************************************************************
void MDParaInit(void) {
	char Tmp[2];
	char i;
	char *ptr;
	char j;

	ptr = (char*) &MaxD.D_Qp_Cumu;
	for (i = 0; i < 70; i++) {
		*ptr = 0x00;
		ptr++;
	}
	for (i = 0; i < 2; i++) {
		MaxD.D_Pp_Slide[i] = 0x0000;
		MaxD.D_Pn_Slide[i] = 0x0000;
		MaxD.D_Rp_Slide[i] = 0x0000;
		MaxD.D_Rn_Slide[i] = 0x0000;
		MaxD.D_Qp_Slide[i] = 0x0000;
		MaxD.D_Qn_Slide[i] = 0x0000;
		for (j = 0; j < 4; j++) {
			MaxD.D_Qdr_Slide[j][i] = 0x0000;
		}
	}

	MaxD.SldStartID = 0;
#ifdef NO_FRAM
	E2P_Read((char*) Tmp, MD_BlockTm, 2);
#else
	FRAM_Read((char*) Tmp, MD_BlockTm, 2);
#endif
	if (Tmp[0] == 0 && Tmp[1] == 0) {
		Tmp[0] = 1;
		Tmp[1] = 1;
#ifdef NO_FRAM
		MEM_DBWrite(MD_BlockTm, (char*) Tmp, 2, Mem_E2PROM);
#else
		MEM_DBWrite(MD_BlockTm, (char*) Tmp, 2, Mem_FRAM);
#endif
	}
	Tmp[0] = BCD_Byte(Tmp[0]);
	Tmp[1] = BCD_Byte(Tmp[1]);

	MaxD.DemandT = Tmp[0];
	MaxD.DemandT = MaxD.DemandT * 60;
	MaxD.SlidingT = MaxD.DemandT;
	MaxD.SlidingTm = MaxD.SlidingT;
	MaxD.SlideNum = MaxD.DemandT / MaxD.SlidingT;

	MaxD.MDchk = ChkNum((char*) &MaxD.D_Qp_Cumu, sizeof(MAXDEMAND_T) - 2);

	MDFeeSw.FeeCnt = 0;
	Flag.Fee &= ~FeeSW_XL;
	Flag.IntTmStart &= ~MDSTART;
}

//**********************************************************************
//all kinds of impulse zero clearing
//**********************************************************************
void PulseClear(void) {
	register int i;
	for (i = 0; i < 40; i++) {
		*(&SM.PpCnt + i) = 0;
	}
}
//**********************************************************************
//impulse backup
//**********************************************************************
void PulseBackUp(void) {
	FRAM_Write(Tst_EC_Pulse, (char*) &SM.PpCnt, sizeof(SM));
	FRAM_Write(Tst_EC_Pulse + FRAMBAK, (char*) &SM.PpCnt, sizeof(SM));
}
//**********************************************************************
//impulse restore
//**********************************************************************
void PulseRestore(void) {
	FRAM_Read((char*) &SM.PpCnt, Tst_EC_Pulse, sizeof(SM));
}
//**********************************************************************
//demand data zero clearing
//**********************************************************************
void MDCumuClear(void) {
	register int i;
	for (i = 0; i < 10; i++) {
		*(&MaxD.D_Qp_Cumu + i) = 0;
	}
}
//**********************************************************************
//demand data stored
//**********************************************************************
void MDCumuBackUp(void) {
	FRAM_Write(Tst_MD_Cumu, (char*) &MaxD.D_Qp_Cumu, 40);
	FRAM_Write(Tst_MD_Cumu + FRAMBAK, (char*) &MaxD.D_Qp_Cumu, 40);
}
//**********************************************************************
//demand data restore
//**********************************************************************
void MDCumuRestore(void) {
	FRAM_Read((char*) &MaxD.D_Qp_Cumu, Tst_MD_Cumu, 40);
}
//**********************************************************************
//off-power demand save
//**********************************************************************
void pcut_md_save(void) {
	MaxD.MDchk = ChkNum((char*) &MaxD.D_Qp_Cumu, sizeof(MAXDEMAND_T) - 2);
	FRAM_Write(Tst_EC_Pulse, (char*) &MaxD.D_Qp_Cumu, sizeof(MAXDEMAND_T));//保存需量数据
	FRAM_Write(Tst_EC_Pp0, (char*) Clk.Sec, 6); //保存需量时间
}
/*******************************************************************************
 //function name: pon_md_read
 //description: on-power demand restore
 //output:
 //input:
 //backspace:
 //notice: this function is mainly repower when power is off, adding in last time demand stopping time and current demand starting time
 *******************************************************************************/
void pon_md_read(void) {
	CLK_T tmp_clk;
	unsigned long pcut_time = 0;
	unsigned long crru_time = 0;
	unsigned char Tmp = 0;

#ifdef NO_FRAM
	E2P_Read((char*) &Tmp, MD_BlockTm, 1);//
#else
	FRAM_Read((char*) tmp_clk.Sec, Tst_EC_Pp0, 6);//read preserved demand time of last power off time
	FRAM_Read((char*) &MaxD.D_Qp_Cumu, Tst_EC_Pulse, sizeof(MAXDEMAND_T));//read demand data
	FRAM_Read((char*) &Tmp, MD_BlockTm, 1);//read demand period
#endif
	Tmp = BCD_Byte(Tmp);
	checkClock();

	crru_time = GetGmMin(Clk.Min);
	pcut_time = GetGmMin(tmp_clk.Min);

	//if((pcut_time == 0)||(crru_time == 0))//if recorded time is 0
	if ((pcut_time == 0) || (crru_time == 0))//
	{
		return;
	}

	crru_time = (crru_time / (unsigned long) Tmp);
	pcut_time = (pcut_time / (unsigned long) Tmp);
	//pcut_time = 123;

	// if(crru_time != pcut_time)//another period
	if (crru_time != pcut_time)//
	//period time has ended already
	{//
		MaxD.SlidingTm = 0;
		//add time lag
		pcut_time = Tmp - (GetGmMin(tmp_clk.Min) % (unsigned int) Tmp);
		tmp_clk.Sec[0] = 0x99;
		tmp_clk.Min[0] = BCD_Byte(tmp_clk.Min[0]) + pcut_time;
		// if(tmp_clk.Min[0] > 59)//last demand stopping time is the next hour of last demand starting time
		if (tmp_clk.Min[0] > 59)//
		{
			tmp_clk.Min[0] -= 60;
			tmp_clk.Hour[0] = BCD_Byte(tmp_clk.Hour[0]) + 1;
			if (tmp_clk.Hour[0] > 23) {
				tmp_clk.Hour[0] -= 24;
				tmp_clk.Day[0] = BCD_Byte(tmp_clk.Day[0]) + 1;

				if (((tmp_clk.Mon[0] == 4) || (tmp_clk.Mon[0] == 6)
						|| (tmp_clk.Mon[0] == 9) || (tmp_clk.Mon[0] == 11))
						&& (tmp_clk.Day[0] > 30)) {
					tmp_clk.Day[0] -= 30;
					tmp_clk.Mon[0] = BCD_Byte(tmp_clk.Mon[0]) + 1;
					if (tmp_clk.Mon[0] > 12) {
						tmp_clk.Mon[0] -= 12;
						tmp_clk.Year[0] = BCD_Byte(tmp_clk.Year[0]) + 1;
						tmp_clk.Year[0] = Byte_BCD(tmp_clk.Year[0]);
					}
					tmp_clk.Mon[0] = Byte_BCD(tmp_clk.Mon[0]);
				} else if ((tmp_clk.Mon[0] == 2) && (tmp_clk.Day[0] > 28)) {
					tmp_clk.Day[0] -= 28;
					tmp_clk.Mon[0] = BCD_Byte(tmp_clk.Mon[0]) + 1;
					if (tmp_clk.Mon[0] > 12) {
						tmp_clk.Mon[0] -= 12;
						tmp_clk.Year[0] = BCD_Byte(tmp_clk.Year[0]) + 1;
						tmp_clk.Year[0] = Byte_BCD(tmp_clk.Year[0]);
					}
					tmp_clk.Mon[0] = Byte_BCD(tmp_clk.Mon[0]);
				} else if (tmp_clk.Day[0] > 31) {
					tmp_clk.Day[0] -= 31;
					tmp_clk.Mon[0] = BCD_Byte(tmp_clk.Mon[0]) + 1;
					if (tmp_clk.Mon[0] > 12) {
						tmp_clk.Mon[0] -= 12;
						tmp_clk.Year[0] = BCD_Byte(tmp_clk.Year[0]) + 1;
						tmp_clk.Year[0] = Byte_BCD(tmp_clk.Year[0]);
					}
					tmp_clk.Mon[0] = Byte_BCD(tmp_clk.Mon[0]);
				}
				tmp_clk.Day[0] = Byte_BCD(tmp_clk.Day[0]);
			}
			tmp_clk.Hour[0] = Byte_BCD(tmp_clk.Hour[0]);
		}
		tmp_clk.Min[0] = Byte_BCD(tmp_clk.Min[0]);

		//*******************add stopping point of last demand period
		//*******************
		MDCumuCalc(&tmp_clk);
		LoadPro_Rec(0, &tmp_clk);
		MDParaInit();

		//*******************add starting point of current demand period
		//*******************
		//restore time
		tmp_clk.Sec[0] = 0x98;
		tmp_clk.Min[0] = Clk.Min[0];
		tmp_clk.Hour[0] = Clk.Hour[0];
		tmp_clk.Day[0] = Clk.Day[0];
		tmp_clk.Mon[0] = Clk.Mon[0];
		tmp_clk.Year[0] = Clk.Year[0];
		crru_time = GetGmMin(Clk.Min);
		crru_time = (crru_time % Tmp);
		tmp_clk.Sec[0] = 0x98;
		tmp_clk.Min[0] = BCD_Byte(tmp_clk.Min[0]);
		// if(tmp_clk.Min[0]<crru_time)//current demand starting time is before an hour of current time
		if (tmp_clk.Min[0] < crru_time)//当前需量开始时间在当前时间的前一个小时
		{
			tmp_clk.Min[0] += 60;
			tmp_clk.Hour[0] = BCD_Byte(tmp_clk.Hour[0]);
			if (tmp_clk.Hour[0] == 0) {
				tmp_clk.Hour[0] += 24;
				tmp_clk.Day[0] = BCD_Byte(tmp_clk.Day[0]);
				if (tmp_clk.Day[0] == 1) {
					tmp_clk.Day[0] = 1;
					tmp_clk.Hour[0] = 1;
					tmp_clk.Min[0] = crru_time;
				}
				tmp_clk.Day[0] = (tmp_clk.Day[0] - 1);
				tmp_clk.Day[0] = Byte_BCD(tmp_clk.Day[0]);
			}
			tmp_clk.Hour[0] = (tmp_clk.Hour[0] - 1);
			tmp_clk.Hour[0] = Byte_BCD(tmp_clk.Hour[0]);
		}
		tmp_clk.Min[0] = (tmp_clk.Min[0] - crru_time);
		tmp_clk.Min[0] = Byte_BCD(tmp_clk.Min[0]);

		MDCumuCalc(&tmp_clk);
		LoadPro_Rec(0, &tmp_clk);
		MDParaInit();
		Flag.IntTmStart |= MDSTART;
	}
	//else//period time has not stopped
	else//
	{
		MaxD.SlidingTm -= (crru_time - pcut_time);
		Flag.IntTmStart |= MDSTART;
	}

	tmp_clk.Sec[0] = 0;
	tmp_clk.Min[0] = 0;
	tmp_clk.Hour[0] = 0;
	tmp_clk.Day[0] = 0;
	tmp_clk.Mon[0] = 0;
	tmp_clk.Year[0] = 0;
	//FRAM_Write(Tst_EC_Pp0, (char*)tmp_clk.Sec, 6 );//record demand time
	FRAM_Write(Tst_EC_Pp0, (char*) tmp_clk.Sec, 6);//

}
