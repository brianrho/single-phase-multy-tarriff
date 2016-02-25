#include "..\inc\includes.h"
time_open open_cover;// add by bnthang
/*****************************************************************
 Timer_A0 interrupt
 *****************************************************************/
unsigned int i;
//useless variable
signed long Ws_SUM1 = 0;
signed long Rs_SUM1 = 0;
signed long Ws_SUM2 = 0;
signed long VAs_SUM1 = 0;
signed long VAs_SUM2 = 0;

//**********************************************************************
//baud rate table
//**********************************************************************
const char BitDly[][9] = { 163, 109, 109, 109, 110, 109, 109, 109, 109, //300
		81, 54, 55, 54, 55, 54, 54, 55, 55,//600
		41, 27, 27, 27, 28, 27, 27, 27, 27, //1200
		21, 13, 14, 14, 13, 14, 13, 14, 14, //2400
		11, 7, 7, 7, 7, 6, 7, 7, 7 //4800
		};
//**********************************************************************
//baud rate delay
//**********************************************************************
const char SendBitDly[] = { 109, //300
		55,//600
		27, //1200
		14, //2400
		7, //4800
		};

//simulated serial port variable
UART_SIM_T gUartSim;//


// this variable used in debug data receive from uart
#ifdef BNTHANG
extern char var_test;// added by bnthang 
//CUR_RTC_T rtc;// added by bnthang
#endif
//**********************************************************************
//indicator B0 interrupted
//**********************************************************************
//#pragma vector=TIMERB0_VECTOR	// added by bnthang
//__interrupt void Int_TimerB0(void) {
//
//	unsigned char buf[7];
//	RX8025_Read(buf, 0, 7);
//
//}

//**********************************************************************
//indicator B1 interrupted
//**********************************************************************
#pragma vector=TIMERB1_VECTOR
__interrupt void Int_TimerB1(void) {

	switch (TBIV) {
	case 2:
		TBCCR1 += T_1ms;
#if 1
		if (gsKey.ucTm > 1) {
			gsKey.ucTm--;
		}
#endif
		if (PulseTmr.P_OutCkVTmr > 1)
			PulseTmr.P_OutCkVTmr--;

		if (IEC_Comm.MdTmr > 0)
			IEC_Comm.MdTmr--;

		if (gRTCOutCnt > 0) {
			gRTCOutCnt--;

			if (gRTCOutCnt == 0) {
				RTC_OUT_CLR();
			}
		}
		break;
	case 4:
		TBCCR2 += T_1ms;
		if (PulseTmr.P_OutCkTmr > 1)
			PulseTmr.P_OutCkTmr--;

		break;
//--------------------add by bnthang-----------
#ifdef BNTHANG
	case 8:// added by bnthang on January 9th 2016
		// interrupt routine when open cover
		unsigned char buf[7];
		RX8025_Read(buf, 0, 7);
		open_cover.time.Sec[0] = buf[0];
		open_cover.time.Min[0] = buf[1];
		open_cover.time.Hour[0] = buf[2];
		open_cover.time.Day[0] = buf[4];
		open_cover.time.Mon[0] = buf[5];
		open_cover.time.Year[0] = buf[6];
		open_cover.time.Week[0] = buf[3];
		//calculate correction code
		open_cover.time.Check = ChkNum(&open_cover.time.Min[0], 6);
		open_cover.number_open++;
		if (open_cover.number_open == 0xff)
			open_cover.number_open = 0;

		FRAM_Write( OPEN_COVER_COUNT_BYTE, (char*) &open_cover.number_open,
				1);
		open_cover.no_new_open++;
		if (open_cover.no_new_open > 4)
			open_cover.no_new_open = 0;
		FRAM_Write( OPEN_COVER_SAVE_BYTE, (char*) &open_cover.no_new_open,
				1);
		FRAM_Write( SAVE_BLOCK_TIME + open_cover.no_new_open * 6,
				(char*) &open_cover.time.Min[0], 6);
		break;
#endif
//----------------------------------------------
	default:
		break;
	}

}

//**********************************************************************
//simulative clock processing
//**********************************************************************
void Clk_Correct(void) {
	ClkC.CorrectGene--;
	if (ClkC.CorrectGene == 0) {
		if (ClkC.CorrectGeneBK > 0) {
			ClkC.CorrectGene = ClkC.CorrectGeneBK;
			Clk.Sec_64--;
		} else if (ClkC.CorrectGeneBK < 0) {
			ClkC.CorrectGene = -ClkC.CorrectGeneBK;
			Clk.Sec_64++;
		}
	}
}
//**********************************************************************
//timer A0,half a second interrupted
//**********************************************************************
#pragma vector=TIMERA0_VECTOR
__interrupt void Int_TimerA0(void) {
	Clk.Sec_64++; //+ 1/32s
	Clk_Correct();

	TACCR0 += 1024;

	if (Clk.Sec_64 == 16) {
		Flag.Run |= R_HalfS;
		//cpu awake for one time each half a second
		LPM3_EXIT; //
	}

	if ((Clk.Sec_64 >= 32))//&& ( ~Flag.Run & R_Sec ) )
	{
		Clk.Sec_64 -= 32;
		Flag.Run |= (R_Sec + R_HalfS);

		gRTCOutCnt = 500;

		LPM3_EXIT;
	}

	GetKeyVal();

}

//
//**********************************************************************
//simulative serial port reception
//**********************************************************************
void SimRX(int8u Cha) {

	if (IEC_Comm.Mode != 1) {
		return;
	}
	if ((IEC_Comm.CommMode != NoCnt) && (IEC_Comm.ComId != 0)) {
		return;
	}
	IEC_Comm.Buf[IEC_Comm.Ptr] = Cha;
	if (((IEC_Comm.CommMode == NoCnt) && (IEC_Comm.Buf[0] != '/'
			&& IEC_Comm.Buf[0] != ACK)) || ((IEC_Comm.CommMode != NoCnt)
			&& (IEC_Comm.Buf[0] != SOH && IEC_Comm.Buf[0] != NAK
					&& IEC_Comm.Buf[0] != ACK))) {
		IEC_Comm.Ptr = 0;
		return;
	}
	IEC_Comm.MdTmr = TM_500ms;
	IEC_Comm.Ptr++;

	if (IEC_Comm.CommMode != NoCnt) {
		if ((IEC_Comm.Ptr == 1) && (IEC_Comm.Buf[0] == NAK || IEC_Comm.Buf[0]
				== ACK))
			goto INTCOMMOK_S;
		if ((IEC_Comm.Ptr > 2) && (IEC_Comm.Buf[IEC_Comm.Ptr - 2] == ETX
				|| IEC_Comm.Buf[IEC_Comm.Ptr - 2] == EOT))
			goto INTCOMMOK_S;
	} else {
		if (IEC_Comm.Ptr > 1 && (IEC_Comm.Buf[IEC_Comm.Ptr - 1] == LF))
			goto INTCOMMOK_S;
	}
	return;

	INTCOMMOK_S:
	//	IE2 &= ~( URXIE1 + UTXIE1 );
	Flag.Run |= R_ComOK;
	IEC_Comm.ComId = 0;
	IEC_Comm.Buf[CommBufSize]++;
	//LPM1_EXIT;
}

//**********************************************************************
//simulative serial port send characters
//**********************************************************************
void SimSendChar(int8u ucChar) {
	int8u ucTmp, i, Cnt;

	gUartSim.BitCount = 12;
	//resend
	gUartSim.TxStart = 1; //
	PSUartOUT |= P_SimTXD;

	ucTmp = ucChar;
	Cnt = 0;
	for (i = 0; i < 7; i++) {
		if (ucTmp & 0x01) {
			Cnt++;
		}
		ucTmp >>= 1;
	}
	ucChar &= 0x7f;
	gUartSim.SendChar = ucChar;
	gUartSim.SendChar <<= 2;
	gUartSim.SendChar &= 0xfffd;

	if (Cnt & 0x01) {
		gUartSim.SendChar |= 0x0601;
	} else {

		gUartSim.SendChar |= 0x0401;
	}
	PSUartOUT |= P_SimTXD;
	//send stop bit
	//发送停止位
	TACCR2 = TAR + SendBitDly[gUartSim.Baud];
	TACCTL2 = CCIE;

}
//**********************************************************************
//simulative serial port sending
//**********************************************************************
void SimTx(void) {

	if ((IEC_Comm.Buf[IEC_Comm.Ptr] == EndFrame) || (IEC_Comm.Ptr
			>= CommBufSize))
		goto TRANSMITOVER_S;

	SimSendChar(IEC_Comm.Buf[IEC_Comm.Ptr++]);

	return;

	TRANSMITOVER_S:
	//stop sending
	TACCTL2 = 0;
	gUartSim.TxStart = 0;
	gUartSim.BitCount = 0;

	Flag.Run |= R_ComOK;
	/*if (IEC_Comm.CommMode == DataOut)
	 {
	 //PSUartOUT&=~P_SimTXD ;
	 IEC_Comm.Mode = 1;
	 IEC_Comm.MdTmr = TM_1500ms;
	 //IFG2 &= ~( UTXIFG1 + URXIFG1 );
	 //   	LPM1_EXIT;
	 return;
	 }*/
	Flag.Run &= ~R_ComOK;
	IEC_Comm.Mode = 1;
	IEC_Comm.Ptr = 0;
	IEC_Comm.MdTmr = TM_1500ms;
	//IFG2 &= ~( UTXIFG1 + URXIFG1 );
	//IE2 |= URXIE1;	
	IEC_Comm.Buf[CommBufSize]++;
	//restart to receive
	PSUartIFG &= ~P_SimRXD;
	PSUartIE |= P_SimRXD;
	//	PSUartOUT&=~P_SimTXD ;

	//LPM1_EXIT;
}

//**********************************************************************
//timer A1 interrupted, simulative serial port
//**********************************************************************
//interrupt [TIMERA1_VECTOR] void Int_TimerA1(void)
#pragma vector=TIMERA1_VECTOR
__interrupt void Int_TimerA1(void) {
	int8u cha;

	switch (TAIV) {
	//channel 1 interrupted
	case 2: //
		//simulative read
		if (gUartSim.RxStart) //
		{
			if (gUartSim.BitCount--) {
				TACCR1 = TAR + BitDly[gUartSim.Baud][8 - gUartSim.BitCount];

				//not sent completely
				if (gUartSim.BitCount) {
					if (PSUartIN & P_SimRXD) {
						gUartSim.BufTmp |= 0x80;
						gUartSim.ParityBit++;
					} else {
						gUartSim.BufTmp &= ~0x80;
					}

					gUartSim.BufTmp >>= 1;
				}
				//the last bit--》EVEN calibration BIT
				else {
					//bytes received completely
					gUartSim.RxStart = 0;//
					if (PSUartIN & P_SimRXD) {
						gUartSim.ParityBit++;
					}
					//calibration error
					if (gUartSim.ParityBit & 0x01) {
						IEC_Comm.Mode = 0;
						return;
					}

					PSUartIFG &= ~P_SimRXD;
					PSUartIE |= P_SimRXD;
					cha = gUartSim.BufTmp & 0x7f;
					SimRX(cha);

					PSUartIFG &= ~P_SimRXD;

					if (Flag.Run & R_ComOK)
					//close P_SimRXD IO interruption
					{//
						PSUartIE &= ~P_SimRXD;

					} else
					//open P_SimRXD IO interruption
					{//
						PSUartIE |= P_SimRXD;
					}

					TACCTL1 = 0;
				}
			}
		}
		break;
		//send
		//channel 2 interrupted
	case 4: //
		//simulate sending
		if (gUartSim.TxStart) {
			if (gUartSim.BitCount--) {
				TACCR2 = TAR + SendBitDly[gUartSim.Baud];
				//not send completely
				if (gUartSim.BitCount) {
					if (gUartSim.SendChar & 0x01) {
						PSUartOUT |= P_SimTXD;
					} else {
						PSUartOUT &= ~P_SimTXD;
					}
					gUartSim.SendChar >>= 1;
				}
				//the last bit--》EVEN calibration BIT
				else//
				{
					SimTx();
					//LPM1_EXIT;
				}
			}
		}
		break;
	default:
		break;
	}
}

/*****************************************************************
 Uart1 Receiver of RS485 or IrDA or RS232
 *****************************************************************/
//**********************************************************************
//serial port 1 receive
//**********************************************************************
#pragma vector=UART1RX_VECTOR
__interrupt void Int_Uart1Rx(void) {
	if (IEC_Comm.Mode != 1) {
		char a;
		a = U1RXBUF;
		a = a;
		return;
	}
	if ((IEC_Comm.CommMode != NoCnt) && (IEC_Comm.ComId != 2)) {
		char a;
		a = U1RXBUF;
		a = a;
		return;
	}
	IEC_Comm.Buf[IEC_Comm.Ptr] = U1RXBUF;
	if (((IEC_Comm.CommMode == NoCnt) && (IEC_Comm.Buf[0] != '/'
			&& IEC_Comm.Buf[0] != ACK)) || ((IEC_Comm.CommMode != NoCnt)
			&& (IEC_Comm.Buf[0] != SOH && IEC_Comm.Buf[0] != NAK
					&& IEC_Comm.Buf[0] != ACK))) {
		IEC_Comm.Ptr = 0;
		return;
	}
	IEC_Comm.MdTmr = TM_500ms;
	IEC_Comm.Ptr++;

	if (IEC_Comm.CommMode != NoCnt) {
		if ((IEC_Comm.Ptr == 1) && (IEC_Comm.Buf[0] == NAK || IEC_Comm.Buf[0]
				== ACK))
			goto INTCOMMOK;
		if ((IEC_Comm.Ptr > 2) && (IEC_Comm.Buf[IEC_Comm.Ptr - 2] == ETX
				|| IEC_Comm.Buf[IEC_Comm.Ptr - 2] == EOT))
			goto INTCOMMOK;
	} else {
		if (IEC_Comm.Ptr > 1 && (IEC_Comm.Buf[IEC_Comm.Ptr - 1] == LF))
			goto INTCOMMOK;
	}
	return;

	INTCOMMOK: IE2 &= ~(URXIE1 + UTXIE1);
	Flag.Run |= R_ComOK;
	IEC_Comm.ComId = 2;
	IEC_Comm.Buf[CommBufSize]++;
	//LPM1_EXIT;
}

/*****************************************************************
 Uart1 Transfer of RS485 or IrDA or RS232
 *****************************************************************/
//**********************************************************************
//serial port 1 send
//**********************************************************************
#pragma vector=UART1TX_VECTOR
__interrupt void Int_Uart1Tx(void)
//interrupt [UART1TX_VECTOR] void Int_Uart1Tx(void)
{
	if ((IEC_Comm.Buf[IEC_Comm.Ptr] == EndFrame) || (IEC_Comm.Ptr
			>= CommBufSize))
		goto TRANSMITOVER_UART1;
	U1TXBUF = IEC_Comm.Buf[IEC_Comm.Ptr++];
	return;
	TRANSMITOVER_UART1:
	//change to direct processing communication mode 3
	/*
	 IE2 &= ~( URXIE1 + UTXIE1 );
	 Flag.Run |= R_ComOK;
	 LPM3_EXIT;
	 */
	//	UART1_RX_OFF();
	IE2 &= ~(URXIE1 + UTXIE1);
	Flag.Run |= R_ComOK;
	/*if (IEC_Comm.CommMode == DataOut)
	 {
	 IEC_Comm.Mode = 1;
	 IEC_Comm.MdTmr = TM_1500ms;
	 IFG2 &= ~( UTXIFG1 + URXIFG1 );
	 //LPM1_EXIT;
	 return;
	 }*/
	Flag.Run &= ~R_ComOK;
	IEC_Comm.Mode = 1;
	IEC_Comm.Ptr = 0;
	IEC_Comm.MdTmr = TM_1500ms;
	IFG2 &= ~(UTXIFG1 + URXIFG1);
	IE2 |= URXIE1;
	IEC_Comm.Buf[CommBufSize]++;

	UART1_RX_ON();
	//LPM1_EXIT;
}

/*****************************************************************
 Uart0 Receiver of RS485 or IrDA or RS232
 *****************************************************************/
//**********************************************************************
//serial port 0 reception interrupted
//**********************************************************************
#pragma vector=UART0RX_VECTOR
__interrupt void Int_Uart0Rx(void) {//bnthang: THIS UART USING IN RS485 COMMUCATION
	char a;
	if (IEC_Comm.Mode != 1) {
		char a;
		a = U0RXBUF;
		a = a;
		return;
	}
	if ((IEC_Comm.CommMode != NoCnt) && (IEC_Comm.ComId != 1)) {
		char a;
		a = U0RXBUF;
		a = a;
		return;
	}
	IEC_Comm.Buf[IEC_Comm.Ptr] = U0RXBUF;
	if (((IEC_Comm.CommMode == NoCnt) && (IEC_Comm.Buf[0] != '/'
			&& IEC_Comm.Buf[0] != ACK)) || ((IEC_Comm.CommMode != NoCnt)
			&& (IEC_Comm.Buf[0] != SOH && IEC_Comm.Buf[0] != NAK
					&& IEC_Comm.Buf[0] != ACK))) {
		IEC_Comm.Ptr = 0;
		return;
	}
	IEC_Comm.MdTmr = TM_500ms;
	IEC_Comm.Ptr++;

	if (IEC_Comm.CommMode != NoCnt) {
		if ((IEC_Comm.Ptr == 1)
				&& (IEC_Comm.Buf[0] == NAK || IEC_Comm.Buf[0] == ACK)) {
				  // this variable used in debug data receive from uart
//			var_test = U0RXBUF;//bnthang added 20/12/2015
			goto INTCOMMOK_UART0;
		}
		if ((IEC_Comm.Ptr > 2)
				&& (IEC_Comm.Buf[IEC_Comm.Ptr - 2] == ETX
						|| IEC_Comm.Buf[IEC_Comm.Ptr - 2] == EOT)){
//			var_test = U0RXBUF;//bnthang added 20/12/2015
			goto INTCOMMOK_UART0;
		}
	} else {
	  if (IEC_Comm.Ptr > 1 && (IEC_Comm.Buf[IEC_Comm.Ptr - 1] == LF)){// buf received first send from host device
//			var_test = U0RXBUF;//bnthang added 20/12/2015
			goto INTCOMMOK_UART0;
	  }
	}
	return;

	INTCOMMOK_UART0:
	//IE2 &= ~( URXIE1 + UTXIE1 );
	UART0_RX_OFF();
	UART0_TX_OFF();
	Flag.Run |= R_ComOK;
	IEC_Comm.ComId = 1;
	IEC_Comm.Buf[CommBufSize]++;
//	var_test = U0RXBUF;//bnthang added 20/12/2015
	//LPM1_EXIT;
}

/*****************************************************************
 Uart1 Transfer of RS485 or IrDA or RS232
 *****************************************************************/
//**********************************************************************
//serial port 0 sending interrupted
//**********************************************************************
#pragma vector=UART0TX_VECTOR
__interrupt void Int_Uart0Tx(void)
//interrupt [UART1TX_VECTOR] void Int_Uart1Tx(void)
{

	if ((IEC_Comm.Buf[IEC_Comm.Ptr] == EndFrame) || (IEC_Comm.Ptr
			>= CommBufSize))
		goto TRANSMITOVER_UART0;

	U0TXBUF = IEC_Comm.Buf[IEC_Comm.Ptr++];
	return;

	TRANSMITOVER_UART0:
	//change to direct processing communication mode 3
	/*
	 IE2 &= ~( URXIE1 + UTXIE1 );
	 Flag.Run |= R_ComOK;
	 LPM3_EXIT;
	 */
	//	UART1_RX_OFF();
	//IE2 &= ~( URXIE1 + UTXIE1 );		
	UART0_RX_OFF();
	Flag.Run |= R_ComOK;
	/*if (IEC_Comm.CommMode == DataOut)
	 {
	 IEC_Comm.Mode = 1;
	 IEC_Comm.MdTmr = TM_1500ms;
	 IFG1 &= ~( UTXIFG0 + URXIFG0 );
	 //LPM1_EXIT;
	 return;
	 }*/
	Flag.Run &= ~R_ComOK;
	IEC_Comm.Mode = 1;
	IEC_Comm.Ptr = 0;
	IEC_Comm.MdTmr = TM_1500ms;
	IFG1 &= ~(UTXIFG0 + URXIFG0);
	IE1 |= URXIE0;
	IEC_Comm.Buf[CommBufSize]++;
	//LPM1_EXIT;
}

//**********************************************************************
//ADC input interrupted
//**********************************************************************

#pragma vector=ADC_VECTOR
__interrupt void Int_ADC12(void) {
	BAT_V = ADC12MEM[0];
}

//**********************************************************************
//
//**********************************************************************
#pragma vector=PORT2_VECTOR
__interrupt void Int_Port2(void) {

}
//#pragma vector=PORT3_VECTOR
//__interrupt void Int_Port3(void) {
//
//}
//**********************************************************************
//serial port interrupted,1, serial port received 2, keypad interrupted
//**********************************************************************
#pragma vector=PORT1_VECTOR
__interrupt void Int_Port1(void) {
	// use to obtain start bit
	if (PSUartIFG & P_SimRXD) {
		TACCR1 = TAR + BitDly[gUartSim.Baud][0];
		TACCTL1 = CCIE;
		//initialization
		gUartSim.BufTmp = 0;
		//7Bit data+1Even
		gUartSim.BitCount = 7 + 1;//7Bit数据 + 1Even
		gUartSim.ParityBit = 0;

		//start mark
		gUartSim.RxStart = 1; //开始标记
		//simulative communication
		///F_SimComm = 1;	//模拟通讯
		//close p_SimRXD IO interruption
		PSUartIE &= ~P_SimRXD;
		PSUartIFG &= ~P_SimRXD;
	}
	//key UP
	if (P1IFG & BIT2) {
		P1IFG &= ~BIT2;
		gsKey.uckeyFlag |= KEY_START_F;
		gsKey.ucVal = 0;
		gsKey.ucHafeSCnt = 0;
		gsKey.uckeyFlag &= ~KEY_UNVAL_F;
		gsKey.ucTm = 10;
		//LPM1_EXIT;
	}
}
