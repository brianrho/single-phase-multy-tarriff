
/**************************************************************************
 //document type: target.c
 //document function: all firmwares driver port
 //change permission:
 //document association:
 //founder:
 //creation date:
 //current version:

 //version information:
 //introduction: firmware environment: CPU MSP43F448
 //software environment: IAR4.20
 **************************************************************************/
#include "..\inc\includes.h"

#define		DELAY_US()		_NOP();\
							_NOP();\
							_NOP();\
							_NOP();\
							_NOP();\
							_NOP();\
							_NOP();\
							_NOP();\
							_NOP();\
							_NOP();

//**************************************
//delay
//*************************************
void DelayUs(int16u time) {
	for (; time > 0; time--) {
		DELAY_US();
		//	DELAY_US();
	}
}
//**************************************
//mS delay
//*************************************
void DelayMs(int16u time) {
	for (; time > 0; time--) {
		DelayUs(100);
	}
}

void DelayInt(int8u time) {

	for (; time > 0; time--) {
		DelayUs(1000); //1ms
	}
}

void UnWTD(void) {
	WDTCTL = WDTPW + WDTHOLD;
}

void WDTClr(void) {
	WDTCTL = WDT_ARST_1000;
	//WDTCTL=WDTPW+WDTHOLD;
}
/*********************************************************
 //name:  void SetPLL(void)
 //function:system on-power initialization
 //input parameter: no
 //backspace: no
 //introduction: set frequency doubling parameter
 ********************************************************/
void SetPLL(int cl, int fsystem, int fcrystal) {
	unsigned int cint, d, dco_div_bits;
	int nplus1;
	volatile int i, j;
	//  /\  Prevent variables from being "optimized".

	// Choose internal load capacitors Cint for LFXT1 depending on the
	// load capacitor CL ("cl") required by the crystal

	if (cl <= 3) // 0pF < CL =< 3pF?
		cint = XCAP0PF; // Use Cint = 0pF
	else if (cl <= 7) // 3pF < CL =< 7pF?
		cint = XCAP10PF; // Use Cint = 10pF
	else if (cl <= 9) // 7pF < CL =< 9pF?
		cint = XCAP14PF; // Use Cint = 14pF
	else
		//  CL > 9pF!
		cint = XCAP18PF; // Use Cint = 18pF and external Cs

	// Choose the system frequency divider
	if ((fsystem / fcrystal) < 121)
		d = 1; // D = 0 (fDCOCLK/1)
	else if ((fsystem / fcrystal) < 240)
		d = 2; // D = 1 (fDCOCLK/2)
	else if ((fsystem / fcrystal) < 480)
		d = 4; // D = 2 (fDCOCLK/4)
	else
		d = 8; // D = 3 (fDCOCLK/8)

	nplus1 = (fsystem / fcrystal) / d;

	switch (d) {
	case 1:
		dco_div_bits = FLLD_1;
		break; // fDCOCLK/1
	case 2:
		dco_div_bits = FLLD_2;
		break; // fDCOCLK/2
	case 4:
		dco_div_bits = FLLD_4;
		break; // fDCOCLK/4
	default:
		dco_div_bits = FLLD_8; // fDCOCLK/8
	}

	if (fsystem < 3000) // fsystem < 3MHz
		SCFI0 = 0 | dco_div_bits;
	else if (fsystem < 6000) // 3MHz <= fsystem <  6MHz
		SCFI0 = FN_2 | dco_div_bits;
	else if (fsystem < 9000) // 6MHz <= fsystem <  9MHz
		SCFI0 = FN_3 | dco_div_bits;
	else if (fsystem < 13000) // 9MHz <= fsystem < 13MHz
		SCFI0 = FN_4 | dco_div_bits;
	else
		SCFI0 = FN_8 | dco_div_bits;

	FLL_CTL0 = DCOPLUS | cint;
	SCFQCTL = nplus1 - 1;

	// Allow FLL+ to settle at the correct DCO tap
	for (i = 32 * d * nplus1; i > 0; i--)
		for (j = 8; j > 0; j--)
			;

}

/******************************************************************************
 //SysChkPW - judge if system is on power or not
 * DESCRIPTION: - 
 *      
 * Input: 
 * Output: 
 //Returns: on power, back to 1, no power back to 0
 * 
 * modification history
 * --------------------
 * 01a, 13feb2011,  written
 * --------------------
 ******************************************************************************/
int8u SysChkPW(void) {
	if (P2IN & BIT1) {
		return 1;
	} else {
		return 0;
	}
}

//**************************************
//set serial port baud rate
//*************************************
void SetBaud(UART_NO_T ComNo, UART_BAUD_T Baud) {
	if (ComNo == UART0) {
		switch (Baud) {
		/*
		 case BAUD4800:
		 U0TCTL &= ~0xc0;
		 U0TCTL |= SSEL0;
		 U0BR0 = 0x6;
		 U0BR1 = 0x0;
		 U0MCTL =0x6f;// 0x0e;
		 break;
		 */
		case BAUD2400:
			U0TCTL &= ~0xc0;
			U0TCTL |= SSEL0;
			U0BR0 = 13;
			U0BR1 = 0;
			//U0MCTL = 0xa;
			U0MCTL = 0x6b;
			break;
		case BAUD1200:
			U0TCTL &= ~0xc0;
			U0TCTL |= SSEL0;
			U0BR0 = 27;
			U0BR1 = 0;
			U0MCTL = 0x3;
			break;
		case BAUD300:
			U0TCTL &= ~0xc0;
			U0TCTL |= SSEL0;
			U0BR0 = 109;
			U0BR1 = 0;
			U0MCTL = 0x4;
			break;
		}
	} else {
		switch (Baud) {
		/*
		 case BAUD4800:
		 U1TCTL &= ~0xc0;
		 U1TCTL |= SSEL0;
		 U1BR0 = 0x6;
		 U1BR1 = 0x0;
		 U1MCTL = 0x6f;
		 break;
		 */
		case BAUD2400:
			U1TCTL &= ~0xc0;
			U1TCTL |= SSEL0;
			U1BR0 = 13;
			U1BR1 = 0;
			//U1MCTL = 0xa;
			U1MCTL = 0x6b;
			break;
		case BAUD1200:
			U1TCTL &= ~0xc0;
			U1TCTL |= SSEL0;
			U1BR0 = 27;
			U1BR1 = 0;
			U1MCTL = 0x3;
			break;
		case BAUD300:
			U1TCTL &= ~0xc0;
			U1TCTL |= SSEL0;
			U1BR0 = 109;
			U1BR1 = 0;
			U1MCTL = 0x4;
			break;
		}
	}

}

/*******************************************************
 //function name: void SetUart(U08 ComNo,uart_baud_t Baud,uart_mode_t mode)
 //function performance: set serial port 0 baud rate
 //entrance parameter: ComNo: serial port number
 //                       Baud: baud rate
 //                       mode: serial port mode
 //exit parameter: no
 //introduction: baud rate is 9600. to be clock source, 32.768 is not stable, thus adopt SMCLK
 // support main frequency, 8M and 16 M.
 //baud rate calculation formula
 ********************************************************/
void SetUart(UART_NO_T ComNo, UART_BAUD_T Baud, UART_MODE_T mode) {
	const int8u UartModeTbl[] = { 0, PENA + PEV + CHAR, PENA + PEV,
			PENA + CHAR, PENA + CHAR, CHAR, 0, 0 };

	if (ComNo == UART0) {

		P2SEL |= BIT4 + BIT5;//作为LCDseg
		P2DIR |= BIT4;

		U0CTL |= SWRST;

		U0CTL |= UartModeTbl[mode];

		switch (Baud) {
		/*
		 case BAUD4800:
		 U0TCTL &= ~0xc0;
		 U0TCTL |= SSEL0;
		 U0BR0 = 0x6;
		 U0BR1 = 0x0;
		 U0MCTL =0x6f;// 0x0e;
		 break;
		 */
		case BAUD2400:
			U0TCTL &= ~0xc0;
			U0TCTL |= SSEL0;
			U0BR0 = 13;
			U0BR1 = 0;
			//U0MCTL = 0xa;
			U0MCTL = 0x6b;
			break;
		case BAUD1200:
			U0TCTL &= ~0xc0;
			U0TCTL |= SSEL0;
			U0BR0 = 27;
			U0BR1 = 0;
			U0MCTL = 0x3;
			break;
		case BAUD300:
			U0TCTL &= ~0xc0;
			U0TCTL |= SSEL0;
			U0BR0 = 109;
			U0BR1 = 0;
			U0MCTL = 0x4;
			break;
		}
		//ME1|=URXE0+UTXE0;		//open RF receive
		ME1 |= URXE0 + UTXE0; //
		U0CTL &= ~SWRST;
		//U0IE|=URXIE0;	//operation receive
		U0IE |= URXIE0; //
	} else {

		//P4SEL|=BIT0+BIT1;//being LCDseg
		P4SEL |= BIT0 + BIT1;//
		P4DIR |= BIT0;
		U1CTL |= SWRST;
		P5DIR |= BIT0;
		P5OUT &= ~BIT0;
		U1CTL |= UartModeTbl[mode];

		switch (Baud) {
		/*
		 case BAUD4800:
		 U1TCTL &= ~0xc0;
		 U1TCTL |= SSEL0;
		 U1BR0 = 0x6;
		 U1BR1 = 0x0;
		 U1MCTL = 0x6f;
		 break;
		 */
		case BAUD2400:
			U1TCTL &= ~0xc0;
			U1TCTL |= SSEL0;
			U1BR0 = 13;
			U1BR1 = 0;
			//U1MCTL = 0xa;
			U1MCTL = 0x6b;
			break;
		case BAUD1200:
#if 1
			U1TCTL &= ~0xc0;
			U1TCTL |= SSEL0;
			U1BR0 = 27;
			U1BR1 = 0;
			U1MCTL = 0x3;
#else
			U1TCTL &= ~0xc0;
			U1TCTL |= SSEL1;
			U1BR0 = 0x69;
			U1BR1 = 0x3;
			U1MCTL =0xFF;
#endif		
			break;
		case BAUD300:
			U1TCTL &= ~0xc0;
			U1TCTL |= SSEL0;
			U1BR0 = 109;
			U1BR1 = 0;
			U1MCTL = 0x4;
			break;
		}
		//ME2|=URXE1+UTXE1;//open RF receive
		ME2 |= URXE1 + UTXE1;//
		U1CTL &= ~SWRST;
		//U1IE|=URXIE1;	//operation receive
		U1IE |= URXIE1; //
	}
}
//**************************************
//set timier B
//*************************************
void TimeB(void) {

	TBCTL = TBCLR;
	TBCTL |= TBSSEL_1 + ID_0 + MC_2; //SMCLK
	TBCCTL0 = CCIE;
	TBCCR0 = TBR + 655; //10MS:     32768/1000=x/20MS
	//TBCCTL1 = CCIE;
	//TBCCR1 = TBR + 10000;
	//TBCCTL2 = CCIE;
	//TBCCR2 = 0;//TBR + 10000;

}

//**************************************
//set timer A
//*************************************
void TimeA(void) {
	TACTL = TACLR;
	TACTL |= TASSEL_1 + ID_0 + MC_2; //ACLK=32768
	TACCTL0 = CCIE;
	TACCR0 = TAR + 0x2000; //3276
	TACCTL1 = CCIE;

	//	CACTL2 = P2CA0;//if this order is not added, battery power consumption will be extremely high when power is off after reseting
	//	CACTL2 = P2CA0;//

}

/*********************************************************
 //set base timer
 //this timer is configurated 16 places
 ********************************************************/

void SetBaseTime(int8u type) {
	if (type == 0) {
		BTCTL = BTDIV + BTFRFQ0; //ACK/2
	} else {
		BTCTL = BTDIV + BTFRFQ1; //ACK/4
	}
}

//**************************************
//turn off ADC
//*************************************
//unsigned int TestC;
void ADCClose(void) {
	//CACTL1=0x00;                                        //turn off comparer
	//CACTL1 = 0x00;			                        //
	//CACTL2 = 0x00;
	//ADC12IE = 0x0000;                                   //there is interrupt after it's finished
	ADC12IE = 0x0000; //
	//ADC12CTL0 &= ~ENC;                                  //disable
	ADC12CTL0 &= ~ENC; //
	//  P6SEL &= ~P_BATT;
	ADC12CTL0 = 0x0000;
	ADC12CTL1 = 0x0000;
	//ADC12MCTL0 = 0x00;
	//ADC12IFG = 0x0000;

}

/******************************************************************************
 //SysOSC - switch clock
 ******************************************************************************/
void SysOSC(int8u ucMode) {
	if (ucMode == 0)
	//    on power switch to 1.024MHZ*/
	{
		FLL_CTL0 |= XCAP10PF; /* Configure load caps */
		SCFI0 = FLLD_1; /* Freq = 1.024MHz */
		SCFQCTL = 32 - 1;
		FLL_CTL0 |= DCOPLUS;
	} else {
		//SetPLL(10, 1024*MCLK_FREQ, 32);//set to 8m
		SetPLL(10, 1024 * MCLK_FREQ, 32);//
	}
}
//**************************************
//timer A configuration
//*************************************
void TimeAConfig(void) {
	TACTL = TACLR;
	//TACTL |= TASSEL_1 + ID_0 + MC_2;	//ACLK=32768, continueous counting mode 0~FFFF
	TACTL |= TASSEL_1 + ID_0 + MC_2; //ACLK=32768
	// TACCTL0 = CCIE;                   //open timer A0  interrupt
	TACCTL0 = CCIE; //
	//TACCR0 = TAR+1024;			    //1024 clocks period enters into one interrupt, that is 1/32s one interrupt
	TACCR0 = TAR + 1024; //
	//TACCTL1 = CCIE;                   //open timer A1 interrupt
	TACCTL1 = CCIE; //
}
//**************************************
//timer B congiguration
//*************************************
void TimeBConfig(int8u ucMode) {
	if (ucMode) {
		//TBCTL = TBCLR;//clear time B counter
		TBCTL = TBCLR;//
		// TBCTL |= TBSSEL_1 +ID_0 +MC_2;	        //ACLK=32768 contineous counting mode
		TBCTL |= TBSSEL_1 + ID_0 + MC_2; //ACLK=32768
		//TBCCTL1 = CCIE;                             //open timer B1 interrupt
		TBCCTL1 = CCIE; //
		//TBCCTL2 = CCIE;				//open timer B2 interrupt
		TBCCTL2 = CCIE; //

		TBCCR1 = TBR + T_1ms; //1MS:     32768/1000=x/1MS
		TBCCR2 = TBR + T_5ms; //5MS:     32768/1000=x/5MS

#ifdef BNTHANG
		TBCCTL4 = CAP + SCS + CM_2 + CCIE + CCIS0; //add by bnthang
		TBCCTL4 &= ~CCIS1;
#endif
	} else {

		TBCTL = TBCLR;
		//TBCTL =MC_0;					//stop
		TBCTL = MC_0; //停止
	}
}
//**************************************
//port off power configuration
//*************************************
void PortConfigPwd(void) {
#if 1
	//IO mouth configuration
	//SPI
	P1DIR = 0;
	P1DIR |= BIT3 + BIT4 + BIT5 + BIT7;
	P1OUT |= BIT3 + BIT4 + BIT5;
	P1OUT &= ~BIT7;
	P1IES = 0x00;
	P1IE = 0x04;
	P1SEL = 0x00;
	//
	P2DIR = 0;
	P2DIR |= BIT0 + BIT2 + BIT3 + BIT4 + BIT6 + BIT7;
	P2OUT &= ~(BIT0 + BIT4 + BIT5 + BIT6 + BIT7);
	P2OUT |= BIT2 + BIT3;
	//P2OUT&=~BIT6;		//reset ATT7022	//ATT7022_CLR_REST
	P2OUT &= ~BIT6; //复位ATT7022	//ATT7022_CLR_REST
	//
	P3DIR = 0;
	P3DIR = 0x0f;
	P3DIR &= ~BIT2;
	P3OUT = 0;
#ifdef BNTHANG
	P3SEL |= BIT5;	// add by bnthang for function open cover
	P3DIR &= ~BIT5;	// add by bnthang
#endif
	//
	// P4SEL&=~(BIT0+BIT1);//being LCDseg
	P4SEL &= ~(BIT0 + BIT1);//
	P4DIR = 0;
	P4DIR |= BIT0 + BIT2 + BIT3 + BIT4 + BIT5;
	P4OUT = 0;
	//
#ifdef SINGLE_PHASE_MULTI_TARIFF
	P5SEL  = 0xFF;
	P6SEL  = 0x00;
	P6DIR = 0;
	P6DIR |= BIT0 + BIT2 + BIT4 + BIT5 + BIT6 + BIT7;
	P6DIR &= ~BIT3;
#else
	P5DIR = 0;
	P5DIR |= BIT1 + BIT2 + BIT3 + BIT4;//********
	P5OUT = BIT4;

	P6DIR = 0;
	P6DIR |= BIT1;
	P6OUT |= BIT1;
#endif
	//??


	//RTC output
	//RTC输出
	//P6DIR|=BIT7;
	//P6OUT=0;

#endif	
}
//**************************************
//port on power configuration
//*************************************
void PortConfigPwU(void) {
	//IO mouth configuration
	//SPI
	P1DIR = 0;
	P1DIR |= BIT1 + BIT3 + BIT4 + BIT5 + BIT7;
	P1OUT |= BIT7;
	P1IES = 0x00;
	P1IE = 0x04;
	P1SEL = 0x00;
	//
	P2DIR = 0;
	P2DIR |= BIT0 + BIT2 + BIT3 + BIT4 + BIT6;
	//P2OUT&=~BIT6;		//reset ATT7022	//ATT7022_CLR_REST
	P2OUT &= ~BIT6; //复位ATT7022	//ATT7022_CLR_REST
	//
	P3DIR = 0;
	P3DIR |= BIT0 + BIT1 + BIT3;
//	P3SEL |= BIT5;// add by bnthang
//	P3DIR &= ~BIT5;// add by bnthang

	//
	P4DIR = 0;
	P4DIR |= BIT0 + BIT2 + BIT3 + BIT5 + BIT6 + BIT7;
	//
#ifdef SINGLE_PHASE_MULTI_TARIFF
	P5SEL = 0xFF;
	P6SEL = 0x00;
	P6DIR = 0;
	P6DIR |= BIT0 + BIT2 + BIT4 + BIT5 + BIT6 + BIT7;
	P6DIR &= ~BIT3;
#else
	P5DIR = 0;
	P5DIR |= BIT1 + BIT2 + BIT3 + BIT4;
	P5OUT |= BIT1;

	P6DIR = 0;
	P6DIR |= BIT1 + BIT4 + BIT5 + BIT7;
#endif

	RN8209_SET_REST();

	//??


}

//for battery test        */
void ADCConfig(void) {
#if 0
	//CACTL1 = CARSEL + CAREF1 + CAON;
	//CACTL2 = P2CA0 + CAF;
	////P6SEL |= P_BATT;                                    //P_BATT is used by ADC
	//P6SEL |= P_BATT;                                    //P_BATT 给ADC使用
	ADC12CTL0 &= ~ENC; //使不能
	//ADC12CTL0 = SHT0_15+MSC+REF2_5V+REFON+ADC12ON;      //ADC12OSC internal reference voltage open 2.5V ADC 12 open
	ADC12CTL0 = SHT0_15+MSC+REF2_5V+REFON+ADC12ON; //ADC12OSC 内部参考电压开2.5V ADC12开
	//ADC12CTL1 = SHP+CONSEQ_2;                           //single channel multi-times
	ADC12CTL1 = SHP+CONSEQ_2; //单通道多次
	ADC12MCTL0 = 0x10; //Vref+ AVss ,Input =A0=P_BATT
	//ADC12IE = 0x0001;                                 //interrup after it's finished
	ADC12IE = 0x0001; //完成后有中断
	//ADC12CTL0 |= ENC;                                   //enable
	ADC12CTL0 |= ENC; //使能
	//i=0x3ff;
	while (i-->0);
	ADC12CTL0 |= ADC12SC;

	CAPD = 0;
#endif
}
//**************************************
//comparer configuration
//*************************************
void ComparaOpen(int8u sta) {
	//vref VCC
	CACTL1 = BIT2 + BIT5 + BIT6;
	//connect CA0
	CACTL2 = BIT2;
	//
	P1SEL |= BIT6;
	//
	CAPD |= BIT6;

	if (sta == 1) {
		CACTL1 |= CAON;
	}

}

//**************************************
//comparer configuration
//*************************************
int8u ComparaStata(void) {

	ComparaOpen(1);

	DelayMs(1);
	//if(CACTL1&BIT0)
	if (CACTL2 & BIT0) {
		ComparaOpen(0);
		return 1;
	} else {
		ComparaOpen(0);
		return 0;

	}
}
// add by bnthang on January 9th 2016
//**************************************
//*************************************
void LcdInit(){
	LCDCTL = 0;
	LCDCTL = LCDMX1 + LCDMX0 + LCDP2 + LCDP1  + LCDSON + LCDON;
	LCDCTL &= ~LCDP0;
	BTCTL  = BT_fLCD_DIV128;             // set LCD frame freq = ACLK
	P5SEL  = 0xFF;

	DispFull();
}

/*******************************************************************************
 //function name: SystemInit
 //description: system firmware initialization, set outer-system source based on different system configuration
 //input: system conditon
 //output:
 //backspace:
 //notice: mainly considerate for low power consumption
 //  adopt low-speed clock when reset and off-power condition, and turn off unecessary external perheral when power is off
 *******************************************************************************/
void SystemInit(char Mode) {

	// WDTClr();//clear watchdog
	WDTClr();//
	_DINT();
	switch (Mode) {
	case System_Reset:
		TimeAConfig();
#ifdef SINGLE_PHASE_MULTI_TARIFF
		LcdInit();
//		RN8209_Init();
#else
		BU9792_Init();
#endif
	case Power_Off:
		SysOSC(0);
		TimeAConfig();
		TimeBConfig(0);
		PortConfigPwd();
		KeyInit();
		break;
	case Power_On:
		SysOSC(1);
		TimeAConfig();
		TimeBConfig(1);
		PortConfigPwU();
#ifdef SINGLE_PHASE_MULTI_TARIFF
		LcdInit();
		RN8209_Init();
#else
		BU9792_Init();
#endif
		KeyInit();
		break;
	}
	_EINT();
}
