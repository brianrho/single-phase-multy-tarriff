
/**************************************************************************
 //document type:target.c
 //document function:all firmware driver port
 //change permission:
 document association:
 //author:
 //creation date:
 //current version
 //version information:
 //introduction: firmware condition:CPU MSP43F448
 //software condition: IAR4.20
 **************************************************************************/

#include "includes.h"

void DispErrCode(int8u v) {
	v = v;

	stDisp.ModeBak = stDisp.Mode;
	stDisp.Mode = ERR;
}

void DispClrErr(int8u v) {
	v = v;

	stDisp.Mode = stDisp.ModeBak;
	stDisp.Mode = LCD_OFF;
}
void DISP_FLASH(void) {
	stDisp.Mode = KEY;
	stDisp.Ptr = 0;
	OPenLCD();
	stDisp.OffCnt = 3;
	//stGasCom.RFEnCnt=20;
}
/*******************************************************************************************************
 //function name:extern	void DispTask(void)
 //function discription:meter display mission
 //input:
 //output: no
 //introduction:
 ********************************************************************************************************/
extern void DispInit(void) {
	stDisp.Cnt = 0;
	stDisp.Mode = LOGO;
	stDisp.ModeBak = LOGO;
	stDisp.Ptr = 0;
	stDisp.Flag |= DISP_UPDATA;
	stDisp.OffCnt = 6;
	stDisp.Inv = 0;
	stDisp.DispErrCnt = 0;
	gErrRF = 0;
}

int8u GetErrNo(void) {

	int8u i, ucTmp;

	ucTmp = gErrState;
	for (i = 0; i < 8; i++) {
		if (ucTmp & 0x01) {
			return i + 1;
		}
		ucTmp >>= 1;
	}
	//return 0xff;	//no mistake
	return 0xff;	//没有错误
}

/*******************************************************************************************************
 //function name: extern void DispTask(void)
 //function discription: meter display mission
 //input:
 //output: no
 //introduction: support automatic rotator and key display, display option can be set
 ********************************************************************************************************/
extern void DispTask(void) {
	int8u DispTlb[] = { 0x01, 0x02, 0x05, 0x06, 0x08 };	//0x09};
//	int8u	LogoTbl[]={0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19};
	int8u LogoTbl[] = { 0x16, 0x17, 0x18, 0x19 };
	int8u ErrTbl[] = { 0x20 };
	CUR_RTC_T rtc;

	int8u ucType, i;
	int8u Buf[16], BufBak[10];
	int32s slCredit;
	//int32u 	ulCredit;

	if (!(stDisp.Flag & DISP_UPDATA)) {
		return;
	}

	if (stDisp.Inv > 0)		//
			{
//		return;
	}

	if (stDisp.OffCnt > 0) {
		stDisp.OffCnt--;
	} else {
		/*
		 if(gErrState!=0)
		 {
		 stDisp.Mode=KEY;
		 stDisp.Ptr=6;
		 }
		 else
		 {
		 stDisp.Mode=LCD_OFF;
		 }
		 */
		if (stDisp.Mode != ERR) {
			stDisp.Mode = LCD_OFF;
		}
	}

	if (stGasCom.RFEnCnt > 0) {
		stGasCom.RFEnCnt--;
	}

	stDisp.Flag &= ~DISP_UPDATA;

	//if(stDisp.Mode==LOGO)		//on-power initialization
	if (stDisp.Mode == LOGO)		//上电初始
			{
		if (stDisp.Ptr >= sizeof(LogoTbl)) {
			stDisp.Ptr = 0;
		}
		ucType = LogoTbl[stDisp.Ptr];
		stDisp.Ptr++;
		if (stDisp.Ptr >= sizeof(LogoTbl) - 1) {
			stDisp.Ptr = 0;
			stDisp.Mode = KEY;
			ucType = 0xff;		//DispTlb[stDisp.Ptr];
		}
		stDisp.Inv = 1;
	} else if (stDisp.Mode == KEY) {
		if (stDisp.Flag & DISP_KEY) {
			stDisp.OffCnt = 30;
			stDisp.Flag &= ~DISP_KEY;
			stDisp.Ptr++;
			if (stDisp.Ptr >= sizeof(DispTlb)) {
				stDisp.Ptr = 0;
			}

		}
		if (stDisp.Ptr >= sizeof(DispTlb)) {
			stDisp.Ptr = 0;
		}
		ucType = DispTlb[stDisp.Ptr];

		stDisp.Inv = 1;

	} else if (stDisp.Mode == LCD_OFF) {
		ucType = 0xff;
		stDisp.Ptr = sizeof(DispTlb) - 1;
	} else if (stDisp.Mode == ERR) {
		ucType = ErrTbl[0];
	} else {
		stDisp.Inv = 1;
		stDisp.Mode = KEY;
	}
	/*
	 else
	 {
	 //if(stDisp.Inv>0)		//display space
	 if(stDisp.Inv>0)		//显示间隔
	 {
	 stDisp.Inv--;
	 }
	 else
	 {
	 stDisp.Ptr++;
	 if(stDisp.Ptr>sizeof(DispTlb))
	 {
	 stDisp.Ptr=0;
	 }
	 }
	 ucType=DispTlb[stDisp.Ptr];
	 }
	 */

	switch (ucType) {
	//case 0x01:	//display gas quantity
	case 0x01:	//显示气量
		GasRead(Buf, 0);
		LcdDisp(&Buf[1], 0, 4, 1);
		break;
		//case 0x02:	//display balance
	case 0x02:	//显示剩余金额
		FM_Read((int8u*) &slCredit, FL_CREDIT_ADR, 4);
		slCredit /= 100;
		SHEX_BCD((char*) BufBak, slCredit);
		for (i = 0; i < 4; i++) {
			Buf[3 - i] = BufBak[i];
		}
		LcdDisp(Buf, 0, 4, 2);
		break;
		//case 0x03:	//display clock
	case 0x03:	//显示时钟
		ReadRTC(&rtc);
		Buf[0] = rtc.Hour;
		Buf[1] = rtc.Min;
		Buf[2] = rtc.Sec;
		Buf[3] = 0x55;
		LcdDisp(Buf, 0, 4, 3);
		break;
		//case 0x05:	//display unit price
	case 0x05:	//显示单价
		ReadCurPir(&BufBak[0]);
		for (i = 0; i < 4; i++) {
			Buf[3 - i] = BufBak[i];
		}
		LcdDisp(Buf, 0, 4, 5);
		break;
		//case 0x06:	//display recharge amount
	case 0x06:	//显示充值金额
		memset(Buf, 0, 6);
		ReadBuyCredit(BufBak);
		for (i = 0; i < 4; i++) {
			Buf[3 - i] = BufBak[i];
		}
		LcdDisp(Buf, 0, 4, 6);
		break;
		//case 0x07:	//display consumed gas quantity
	case 0x07:	//显示消费气量
		FM_Read((int8u*) &slCredit, FL_COST_CREDT, 4);
		slCredit /= 100;
		SHEX_BCD((char*) BufBak, slCredit);
		for (i = 0; i < 4; i++) {
			Buf[3 - i] = BufBak[i];
		}
		LcdDisp(Buf, 0, 4, 7);
		break;
	case 0x08:
		FM_Read(&Buf[0], FL_COM_ADR, 6);
		for (i = 0; i < 4; i++) {
			BufBak[i] = Buf[3 - i];
		}
		LcdDisp(&BufBak[0], 0, 4, 3);
		break;
		//case 0x09:	//display mistake
	case 0x09:	//显示错误
		Buf[0] = GetErrNo();
		/*
		 if(Buf[0]==0xff)
		 {
		 //stDisp.Ptr=0;
		 //ucType=DispTlb[stDisp.Ptr];
		 }
		 *
		 else
		 {
		 DispErr(Buf[0]);
		 }
		 DispErr(Buf[0]);
		 */
		break;
		//*	case 0x08:	//display consumed amount
		/*	case 0x08:	//显示消费金额
		 memset(Buf,0,6);
		 //Buf[3]=0x78;
		 //Buf[2]=0x92;
		 LcdDisp(Buf,0,4,8);
		 break;
		 */
		//case 0x04://display date
	case 0x04:	//显示日期
		ReadRTC(&rtc);
		Buf[0] = rtc.Year;
		Buf[1] = rtc.Mon;
		Buf[2] = rtc.Day;
		Buf[3] = 0xdd;
		LcdDisp(Buf, 0, 4, 3);
		break;
	case 0x10:
		memset(Buf, 9, 8);	//9999
		DispString(Buf);
		break;
	case 0x11:
		memset(Buf, 8, 8);    //9999
		DispString(Buf);
		break;
	case 0x12:
		memset(Buf, 7, 8);	//9999
		DispString(Buf);
		break;
	case 0x13:
		memset(Buf, 6, 8);	//9999
		DispString(Buf);
		break;
	case 0x14:
		memset(Buf, 5, 8);	//9999
		DispString(Buf);
		break;
	case 0x15:
		memset(Buf, 4, 8);	//9999
		DispString(Buf);
		break;
	case 0x16:
		memset(Buf, 3, 8);	//9999
		DispString(Buf);
		break;
	case 0x17:
		memset(Buf, 2, 8);	//9999
		DispString(Buf);
		break;
	case 0x18:
		memset(Buf, 1, 8);	//9999
		DispString(Buf);
		break;
	case 0x19:
		memset(Buf, 0, 8);	//9999
		DispString(Buf);
		break;

		//display mistake
//错误显示
	case 0x20:
		memset(Buf, 0, 8);
		DispErr(Buf[0]);
		break;
	case 0xff:
		/*
		 memset(Buf,0xff,8);	//9999
		 DispString(Buf);
		 */
		CloseLCD();
		break;
	default:
		break;
	}
}

#pragma vector=PORT2_VECTOR
__interrupt void Port2_Int(void) {

	if (P2IE & BIT7)				//RXD
			{
		//if(P2IFG&BIT7)			//interrupt
		if (P2IFG & BIT7)			//有中断
				{
			P2IFG &= ~BIT7;		//
			stDisp.Flag |= DISP_KEY;
			stDisp.Inv = 0;

			//StealClr();		//clear gas-tamper flag
			StealClr();		//清楚窃气标志

			stDisp.Mode = KEY;
			OPenLCD();
			stDisp.OffCnt = 30;
			stGasCom.RFEnCnt = 20;
			g_BeepAlarm.En = 0;
			LPM3_EXIT;
		}
	}

}

