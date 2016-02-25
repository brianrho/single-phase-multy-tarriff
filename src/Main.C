/**********************************************************************************
 * project name  :three-meter
 * description    :source programme of three-phase smart meter
 * firmware platform:MSP430F449
 * research environment:IAR_FOR_MSP430_V5.3 
 * author :zhuhai yujian science and technology co, ltd
 * remarks :this source programme includes all the source programmes of the whole company, and the followings are the detailed specifications
 230V 5(6)A
 230V 50(100)A
 230V 10(100)A
 110V 5(6)A
 57.7 5(10)A
 the definition of the specifications are in the Common.h file, including the definition of the version of the firmware, so you are kindly requested to read the file first
 **********************************************************************************/
/**********************************************************************************
 230V 5(6)A
 230V 50(100)A
 230V 10(100)A
 110V 5(6)A
 57.7 5(10)A
 **********************************************************************************/

#include "..\inc\includes.h"

#ifdef SINGLE_PHASE_MULTI_TARIFF
#include "..\inc\RN8209.h"
extern ENERGY vse1t_de;
extern volatile RN8209_RMS rn8209a_rms;
extern volatile RN8209_CALIB rn8209a_calib;
#endif

//frozen times of Liao Bing
unsigned char bill_count = 0;//20111226

//external modules of decimal dots
unsigned char net_rest_time = 0;//
//displaying modules
extern unsigned char display_mod;//



//--------------------add by bnthang-----------
#ifdef BNTHANG
extern time_open open_cover;// add by bnthang
extern char ucBuf[20], id[12];
int var_test[5];// added by bnthang 
void Init_Vars();
//unsigned long t;

#endif
//---------------------------------------------



//recording status of last reset affairs
extern void InitNewLog(void);//
//storage of sincere words
unsigned char meter_state[2] = { 0x00, 0x00 };//
// this variable used in debug data receive from uart

/*******************************************************************************
 * function name : RAMInit
 * description : funcion of internal storage initialization, used in different conditions of internal storage initialization
 * input: function status of the programme:status of decimal dots, on power status and off power status
 * output:
 * backspace:
 * notice:
 *******************************************************************************/
void RAMInit(char Mode) {
	unsigned char i;

	switch (Mode) {//status of decimal
	case System_Reset://
		//symbol of on power decimal
		Flag.Power &= ~F_PwrUp;//
		//status character of decimal programme
		EventFlag.States = 0; //
		//symbol of decimal programme
		for (i = 0; i < 14; i++) //
			*(&Flag.Run + i) = 0x00;

		RunDly.AllDspDly = 0;
		RunDly.PowerRunDly = 0;
		Flag.Run |= R_Disp;
		gsKey.KeyDisp = 0;
		DisK.ShutDnInv = 10;
		DisK.ShutDnCnt = 0;
		DisK.DisInv = 0;
		IEC_Comm.MdTmr = 0;
		IEC_Comm.Ptr = 0;
		IEC_Comm.Mode = 0;
		IEC_Comm.CommMode = NoCnt;

		_DINT();
		//number of pulses of reset memory storage
		memset((char*) &SM.PpCnt, 0, sizeof(SM) - 2);//
		_EINT();
		//reading decimal places and energy unit
		E2P_Read((char*) &DOT[0], EnDot, 2); //
		//reading displaying modules
		E2P_Read((char*) &display_mod, SysSW, 1); //

#ifdef SINGLE_PHASE_MULTI_TARIFF
		Init_Vars();
#else
		//data of cleaning storage memory
		ATT7022_RAMClear(); //
#endif
		break;
		//statis of off power
	case Power_Off://
		IEC_Comm.MdTmr = 0;
		IEC_Comm.Ptr = 0;
		IEC_Comm.Mode = 0;
		IEC_Comm.CommMode = NoCnt;
		gsKey.KeyDisp = 0;
		RunDly.PowerDely = 0;
		RunDly.PowerRunDly = 0;
		EventFlag.States = 0;
//		DelayMs(200);
		//reading decimal places and energy unit, used to display off-power
		E2P_Read((char*) &DOT[0], EnDot, 2);//
		//recount check code
		_DINT();
		// storage of the number of impulses
		SM.CntChk = CHECKWORD;
		for (i = 0; i < 40; i++) {
			SM.CntChk += *(&SM.PpCnt + i);
		}
#ifdef NO_FRAM

#else
		FRAM_Write(Ram_Pulse, (char*) &SM.PpCnt, 42);
		FRAM_Write(Ram_Pulse + FRAMBAK, (char*) &SM.PpCnt, 42);
#endif
		_EINT();
		//reading displaying modules, used to display off-power
		E2P_Read((char*) &display_mod, SysSW, 1);//

#ifdef SINGLE_PHASE_MULTI_TARIFF
#else
		//clean memory storage data
		ATT7022_RAMClear(); //
#endif
		break;
		//on-power status
	case Power_On://
		gsKey.KeyDisp = 0;

#ifdef SINGLE_PHASE_MULTI_TARIFF
#else
		ATT7022_RAMClear();
#endif
		RunDly.PowerDely = 0;
		RunDly.Magic_Dly = 0;
		RunDly.BLight_Dly = 0;
		IEC_Comm.Mode = 0;
		IEC_Comm.CommMode = NoCnt;
		DisK.DisPtr = 0;
		DisK.DisInv = 0;
		gsAttPara.InvalidPowerOnRead = 2;
		EventDly.DIOver[0] = 0;
		EventDly.DIOver[1] = 0;
		EventDly.DIOver[2] = 0;
		EventDly.DLostPhase[0] = 0;
		EventDly.DLostPhase[1] = 0;
		EventDly.DLostPhase[2] = 0;
		EventDly.DUnBala = 0;
		EventDly.DUOver[0] = 0;
		EventDly.DUOver[1] = 0;
		EventDly.DUOver[2] = 0;
		gHardErr = 0;
//		_DINT();
		//reading porgramme related configuration information
//		E2P_Read((char*) &DOT[0], EnDot, 2);
#ifdef NO_FRAM

#else
		FRAM_Read((char*) &BillDely[0], _MBillDelyTM, 2);
#endif
//		E2P_Read((char*) &display_mod, SysSW, 1);
//		E2P_Read((char*) &gFactMode, FACT_MODE, 2);
		_DINT();
		//record of initialization new affairs
		InitNewLog();
#ifdef NO_FRAM

#else
		//recovery of the number of impulses
		FRAM_Read((char*) &SM.PpCnt, Ram_Pulse, sizeof(SM) - 2);
#endif
		if (SM.PpCnt > (unsigned char) (FC_S0Out)) {
			SM.PpCnt = 0;
		}
		if (SM.PnCnt > (unsigned char) (FC_S0Out)) {
			SM.PnCnt = 0;
		}
		if (SM.RpCnt > (unsigned char) (FC_S0Out)) {
			SM.RpCnt = 0;
		}
		if (SM.RnCnt > (unsigned char) (FC_S0Out)) {
			SM.RnCnt = 0;
		}
		if (SM.VApCnt > (unsigned char) (FC_S0Out)) {
			SM.VApCnt = 0;
		}
		if (SM.VAnCnt > (unsigned char) (FC_S0Out)) {
			SM.VAnCnt = 0;
		}
//--------------------add by bnthang-------------------------------
#ifdef BNTHANG

#ifdef NO_FRAM
		E2P_Read(&open_cover.number_open, OPEN_COVER_COUNT_BYTE, 1);
		if (open_cover.number_open == 0xff)
			open_cover.number_open = 0;
		E2P_Read(&open_cover.no_new_open, OPEN_COVER_SAVE_BYTE, 1);
		if (open_cover.no_new_open > 4)
			open_cover.no_new_open = 0;
#else
		FRAM_Read(&open_cover.number_open, OPEN_COVER_COUNT_BYTE, 1);
		if (open_cover.number_open == 0xff)
			open_cover.number_open = 0;
		FRAM_Read(&open_cover.no_new_open, OPEN_COVER_SAVE_BYTE, 1);
		if (open_cover.no_new_open > 4)
			open_cover.no_new_open = 0;
#endif

#endif
//----------------------------------------------

		_EINT();
		break;
	}
}
//usless
void FM_Test(void);//
//usless
void DF_Test(void);//
//usless
void E2_Test(void);//
//useless
void DispTest(void);//
//DF check code

void DF_Check(void);//


void Init_Vars() {
	rn8209a_calib.ka = 0x0FA0;
	rn8209a_calib.kb = 0x0FA0;
	rn8209a_calib.kv = 0x0244;
	vse1t_de.total_q_lag.long_val = 0;
	vse1t_de.total_p.long_val = 0;
	vse1t_de.total_q_lead.long_val = 0;
	rn8209a_calib.count_id = 0;

}
/*******************************************************************************
 * function name: main
 * description:
 * input :
 * output :
 * backspace:
 * notice :
 *******************************************************************************/
void main(void) {
	//turn off watchdog
	UnWTD(); //
	//reset chip configuration
	SystemInit(System_Reset); //
	DelayMs(50);
#ifdef TEST
	RN8209_Init();
#else
	//reset memory storage
	RAMInit(System_Reset); //
	DelayMs(50);
	MemCheck(Chk_RAM); //

	DelayMs(50);
	checkClock();
	//setting up LCD displaying time
	RunDly.AllDspDly = 2; //

	E2P_Read((char*) &DOT[0], EnDot, 2);

	while (1) {//once detected off-power system and off-power symbol, LPM3 low-power consumption module is started
		if ((SysChkPW() == 0) && ((Flag.Power & F_PwrUp) == 0x00)) {
			LPM3;
		}
		WDTClr();
                
		//off-power management
		if (SysChkPW() == 0x00) {// on-powered, data needs to be stored
			if (Flag.Power & F_PwrUp) { //calculation of the number of impulses, which should be done before RAMInIt
#ifdef SINGLE_PHASE_MULTI_TARIFF
#else
				CalcPulse();//
#endif
				//off communication
				Flag.FlsLP &= ~FlsLP_Com_RBsy; //
				Flag.Power &= ~F_PwrUp;
				Flag.Power &= ~F_PwrOK;
				RunDly.PowerRunDly = 0;
				//settomg off-power symbol, used to store off-power affair record
				Flag.EventFlg1 |= F_Ev_PwrOff; //
				//conficuration of memory storage is off-power status
				RAMInit(Power_Off); //
				//needed storage space
				pcut_md_save(); //
#ifdef SINGLE_PHASE_MULTI_TARIFF
#else
				//setting LCD display enters into low-power consumption status
				BU9792_Set(LCD_POWER_SAVE); //
#endif
				//latency time of turning off LCD
				Get_ShutDispTm(); //
				//system enters into off-power status
				SystemInit(Power_Off); //
			}
		} else { //repower time reaches 1S after turning off
			if ((Flag.Power & F_PwrUp) == 0x00 && (RunDly.PowerRunDly >= 2)) {//setting on-power symbol
				Flag.Power |= F_PwrUp;//
				//system configuration is on-power status
				SystemInit(Power_On);//
				//check E2PROM data
				MemCheck(Chk_E2PROM); //
#ifdef NO_FRAM

#else
				//check FRAM data
				MemCheck(Chk_FRAM); //
#endif
				// check DFlash data
				MemCheck(Chk_DFlash); //
				//check real-time clock
				checkClock(); //
				//estimate if it's the first operation, if so, configure factory default parameter
				FirstBurn(); //
				//memory storage configuration is on-power status
				RAMInit(Power_On); //
				//check if there is any mistakes with DF
				DF_Check(); //
				//setting on-power LCD displaying time
				RunDly.AllDspDly = 3; //
				//status of reset programme
				IEC_Comm.ProgCnt = 0; //
				//needed storage space  of recovering from off-power
				pon_md_read(); //
				//check time table
				DayTableCHG(); //
				//automatically check if it's frozen, and this function remains effective
				if (CheckBill() <= 0x28)//
				{//automatically check frozen
					bill_count = AutoSaveTime();//
					//when frozen time is greater than 0, frozen is needed
					if (bill_count > 0) //
					{//setting u
						Flag.Fee |= F_BillAll;//
					}
				}
			}
		}
		//function of dealing with all kinds of functions
		//
		Time_TH();
		//function of dealing with communication
		IEC_CommProcess();
		//function of dealing with displaying
		if (((Flag.Run & R_Disp) && (~Flag.Run & R_Sec))\
				|| (gsKey.KeyDisp == 1)) {
			Flag.Run &= ~R_Disp;
			DisplayData();
			gsKey.KeyDisp = 0;
		}
	}
#endif

}

