#ifndef _TYPEFRAM_H
#define	_TYPEFRAM_H

//FM25CL64
#define	FRAM_START		0x0000
#define	FRAM_SIZE		0x2000
#define	FRAMBAK         0x0A00
#define FRAM_END  0x1400

//#define LOAD_DATE_  FRAM_END
//preserve total days of recording overload curve .<65535 D311
#define LOAD_DATE_  FRAM_END  //bnthang:	0x1400
#define LOAD_DATE_END  LOAD_DATE_+2048//bnthang: 0x1400 + 0x800 = 0x1c00
#define EV_STAR LOAD_DATE_END//bnthang: 0x1c00
#define EV_END EV_STAR+455//+550+5 bnthang: 0x1c00 + 0x1c7 = 0x1dc7
#define NEV_STAR EV_END//bnthang: 0x1dc7
#define NEV_END NEV_STAR+551//7*50+7*3+3*60 bnthang: 0x1dc7 + 0x227 = 0x1fee

//remaining the last 18 bytes, and the last 8 bytes are fixed preserve calculating chip check code

//#define ATT7022_ADJCHK (FRAM_SIZE-8)
//add in record calculating chip check, remains 8 bytes, and this position can not be changed later on, or recalibration of meter needs to be done
#define ATT7022_ADJCHK (FRAM_SIZE-8) //bnthang: 0x2000 - 0x0008 = 0x1ff8
#define ATT7022_ADJCHK_END ATT7022_ADJCHK+4//bnthang: 0x1ff8+0x4 = 0x1ffc

#define Adj_Para        FRAM_START			    //128  //bnthang:0x0000
#define Temp_Back		Adj_Para+128+0		    //192//bnthang:0x0000 + 128 = 0x0080
#define	EC_Back         Temp_Back+192		    //452=162+102+88+88+12 = 0x0140
#define	MD_Back         EC_Back+452      	    //470 = 0x304
#define	Para_Back       MD_Back+470			    //555 = 0x04DA
#define	TestMode		Para_Back+555		    //136 = 0x0705
#define MD_CUMU         TestMode+136            // 98=22*4+10 = 0x78D
#define LOADPROFILEPARA MD_CUMU+98              //180=(130+50) = 0x7ef
#define LOADPROFILEPARA_END LOADPROFILEPARA+180  // = 0x8A3

#define NET_PARA   LOADPROFILEPARA_END+1// =0x8a4
#define NET_PARA_END NET_PARA+30// 0x08c2



//modifying preserve current average power position
/*
 //preserve current average power
 #define AVR_MD_ST   NET_PARA_END
 #define AVR_MD_END   AVR_MD_ST+43  //5*7 + 6 +2
 */
#ifdef SINGLE_PHASE_MULTI_TARIFF


#else
#define NET_SEC_IP      NET_PARA_END//AVR_MD_END
#define NET_SEC_IP_END  NET_SEC_IP+6

#define		BillingDateTwo			NET_SEC_IP_END	
#define		BillingDateTwoEnd		BillingDateTwo+6
#endif

//preserve current and last average power
#define AVR_MD_ST    BillingDateTwoEnd//NET_PARA_END
#define AVR_MD_END   AVR_MD_ST+60  //
//preserve user defined register module
#define USER_DEFINE_STAT AVR_MD_END
#define USER_DEFINE_END  USER_DEFINE+10

//preserve configuration parameter of RF module
#define RF_PARA       USER_DEFINE_END
#define RF_PARA_END   RF_PARA+15

//preserve newly-added the forth password
//permission of the forth password, it can read parameter, but only can write IP, PORT, APN parameter

#ifdef SINGLE_PHASE_MULTI_TARIFF

#else
#define PASSNEW       RF_PARA_END
#define PASSNEW_END   PASSNEW+10// 0x092d
#endif

//--------------------add by bnthang-----------
#ifdef BNTHANG
#define OPEN_COVER				PASSNEW_END + 1// add by bnthang =0X092e
#define OPEN_COVER_END			OPEN_COVER+32// add by bnthang = 0X94A
#define OPEN_COVER_COUNT_BYTE	OPEN_COVER + 1
#define OPEN_COVER_SAVE_BYTE	OPEN_COVER_COUNT_BYTE + 1
#define SAVE_BLOCK_TIME			OPEN_COVER_SAVE_BYTE + 1
#endif
//----------------------------------------------

/*----  Adj_Para   117/128 ------------------------------------------------------*/
#define Adj_Para_GAINA0     (Adj_Para +0)   		//3
#define Adj_Para_GAINA1     (Adj_Para_GAINA0+3) 	//3
#define	Adj_Para_CHKGA		(Adj_Para_GAINA1+3)		//2
#define Adj_Para_GAINB0     (Adj_Para_CHKGA +2)  	//3
#define Adj_Para_GAINB1     (Adj_Para_GAINB0+3)  	//3
#define	Adj_Para_CHKGB		(Adj_Para_GAINB1+3)		//2
#define Adj_Para_GAINC0   	(Adj_Para_CHKGB+2)  	//3
#define Adj_Para_GAINC1   	(Adj_Para_GAINC0+3)  	//3
#define	Adj_Para_CHKGC		(Adj_Para_GAINC1+3)		//2
#define Adj_Para_PHASEA0    (Adj_Para_CHKGC+2)  	//3
#define Adj_Para_PHASEA1    (Adj_Para_PHASEA0+3)  	//3
#define	Adj_Para_CHKPA		(Adj_Para_PHASEA1+3)	//2
#define Adj_Para_PHASEB0    (Adj_Para_CHKPA+2)  	//3
#define Adj_Para_PHASEB1    (Adj_Para_PHASEB0+3)  	//3
#define	Adj_Para_CHKPB		(Adj_Para_PHASEB1+3)	//2	
#define Adj_Para_PHASEC0    (Adj_Para_CHKPB+2)  	//3
#define Adj_Para_PHASEC1    (Adj_Para_PHASEC0+3) 	//3
#define	Adj_Para_CHKPC		(Adj_Para_PHASEC1+3)	//2

#define Adj_Para_VRAM_A		(Adj_Para_CHKPC+2)		//3
#define Adj_Para_VRAM_B		(Adj_Para_VRAM_A+3)		//3	
#define Adj_Para_VRAM_C		(Adj_Para_VRAM_B+3)		//3	
#define	Adj_Para_CHKV		(Adj_Para_VRAM_C+3)		//2
#define Adj_Para_IRAM_A		(Adj_Para_CHKV+2)		//3
#define Adj_Para_IRAM_B		(Adj_Para_IRAM_A+3)		//3
#define Adj_Para_IRAM_C		(Adj_Para_IRAM_B+3)		//3
#define	Adj_Para_CHKI		(Adj_Para_IRAM_C+3)		//2
#define	Adj_Para_Iregchg	(Adj_Para_CHKI+2)		//3
#define	Adj_Para_Iregion	(Adj_Para_Iregchg+3)	//3
#define Adj_Para_ChkIreg	(Adj_Para_Iregion+3)	//2
#define	Adj_Para_FHConst	(Adj_Para_ChkIreg+2)	//3
#define	Adj_Para_StartI		(Adj_Para_FHConst+3)	//3
#define	Adj_Para_CHKConst	(Adj_Para_StartI+3)

#define	Adj_Para_LEN		(Adj_Para_CHKConst+2)

#define Adj_Para_CALIED     (Adj_Para+117)  	//4


// modify by bnthang
#ifdef SINGLE_PHASE_MULTI_TARIFF

#else
/*----  Temp_Back 84/192 --------------------------------------------------------*/
//#define	Clk_Back        Temp_Back           //8 clock 8
#define	Clk_Back        Temp_Back           //0x0080
//#define ClockBuf        Clk_Back		    // clock nickname
#define ClockBuf        Clk_Back		    //
//#define CLK_GENE        Clk_Back+8          //6 clock correction factor (4+2)
#define CLK_GENE        Clk_Back+8          //
//#define PARA_PTCT       CLK_GENE+6          //22 PT,CT first second total variable-ratio PT CT variable-ratio
#define PARA_PTCT       CLK_GENE+6          //
//#define Ram_Pulse		PARA_PTCT+22  		//42 impulse times storage
#define Ram_Pulse		PARA_PTCT+22  		//
//#define Battery_CUMU    Ram_Pulse+42        //6 battery usage time
#define Battery_CUMU    Ram_Pulse+42        //
#endif


/*----  EC_Back  452/452 --------------------------------------------------------*/
//#define	EC_Back1 		EC_Back             //162 active, reactive, apparent forward reverse total power quantity and time-consuming power quantity  (5*5+2)*3*2=162
#define	EC_Back1 		EC_Back             //0x0140
//#define	EC_Back2 		EC_Back1+162        //active, reactive, apparent forward reverse split-phase total power quantity  (3*5+2)*3*2=102
#define	EC_Back2 		EC_Back1+162        //
//#define	EC_Back3 		EC_Back2+102        //88 reactive quadrant, split-phase reactive quadrant power quantity  (4*5+2)*(1+3)=88
#define	EC_Back3 		EC_Back2+102        //
//#define	EC_Back4		EC_Back3+88			//88 reactive quadrant tariff power quantity
#define	EC_Back4		EC_Back3+88			//
//#define MON_ZZZZ        EC_Back4+88         //12 month hour flag
#define MON_ZZZZ        EC_Back4+88         //
/*----  MD_Back  434/470 --------------------------------------------------------*/
//#define	MD_Back1 		MD_Back             //420 active, reactive, apparent forwar reverse demand   42*10=420
#define	MD_Back1 		MD_Back             //
#define MON_MD_CHK_     MD_Back1+420        //  2
//#define EC_Back5        MON_MD_CHK_+2       //12 power quantity buffer of one minute  notice:EC_Back5 put here, connecting the calculating data
#define EC_Back5        MON_MD_CHK_+2       //
/*----  Para_Back  555/555 ------------------------------------------------------*/
#define	Para_Back1 		Para_Back           //  0
//#define	Para_Back2 		Para_Back1+0		//192 demand parameter, display parameter
#define	Para_Back2 		Para_Back1+0		//
//#define	Para_Back3 		Para_Back2+180      //80 meter parameter
#define	Para_Back3 		Para_Back2+180      //
//#define	Para_Back4		Para_Back3+92		//70 overload curve parameter 28+32+10=70
#define	Para_Back4		Para_Back3+92		//
//#define Para_Back5      Para_Back4+70       //213 event record parameter 213
#define Para_Back5      Para_Back4+70       //

/*....  EC_Back1  ...............................................................*/
//E.C forward active 162
#define	EC_Pp0 			EC_Back1 + 27*0
#define	EC_Pp1			EC_Pp0 +5
#define	EC_Pp2			EC_Pp0 +10
#define	EC_Pp3			EC_Pp0 +15
#define	EC_Pp4			EC_Pp0 +20
#define	Chk_Pp			EC_Pp0 +25
//reverse active
#define EC_Pn0          EC_Back1 + 27*1
#define EC_Pn1			EC_Pn0 + 5
#define EC_Pn2  		EC_Pn0 + 10
#define EC_Pn3 			EC_Pn0 + 15
#define EC_Pn4 			EC_Pn0 + 20
#define Chk_Pn			EC_Pn0 + 25
//forward reactive
#define EC_Rp0			EC_Back1 + 27*2
#define EC_Rp1 			EC_Rp0 + 5
#define EC_Rp2			EC_Rp0 + 10
#define EC_Rp3			EC_Rp0 + 15
#define EC_Rp4			EC_Rp0 + 20
#define Chk_Rp			EC_Rp0 + 25
//reverse reactive
#define EC_Rn0			EC_Back1 + 27*3
#define EC_Rn1			EC_Rn0 + 5
#define EC_Rn2  		EC_Rn0 + 10
#define EC_Rn3			EC_Rn0 + 15
#define EC_Rn4			EC_Rn0 + 20
#define Chk_Rn			EC_Rn0 + 25
//forward apparent
#define EC_Qp0			EC_Back1 + 27*4
#define EC_Qp1 			EC_Qp0 + 5
#define EC_Qp2			EC_Qp0 + 10
#define EC_QP3			EC_Qp0 + 15
#define EC_Qp4			EC_Qp0 + 20
#define Chk_Qp			EC_Qp0 + 25
//reverse apparent
#define EC_Qn0			EC_Back1 + 27*5
#define EC_Qn1			EC_Qn0 + 5
#define EC_Qn2  		EC_Qn0 + 10
#define EC_Qn3			EC_Qn0 + 15
#define EC_Qn4			EC_Qn0 + 20
#define Chk_Qn			EC_Qn0 + 25

/*....  EC_Back2  ...............................................................*/
//active forward split-phase power quantity 102
#define	EC_PpL1         EC_Back2 + 17*0
#define	EC_PpL2			EC_PpL1 +5
#define	EC_PpL3			EC_PpL1 +10
#define	Chk_ECPpL       EC_PpL1 +15
//active reverse split-phase power quantity
#define	EC_PnL1         EC_Back2 + 17*1
#define	EC_PnL2			EC_PnL1 +5
#define	EC_PnL3			EC_PnL1 +10
#define	Chk_ECPnL       EC_PnL1 +15
//reactive forward split-phase power quantity
#define	EC_RpL1         EC_Back2 + 17*2
#define	EC_RpL2			EC_RpL1 +5
#define	EC_RpL3			EC_RpL1 +10
#define	Chk_ECRpL       EC_RpL1 +15
//reactive reverse split-phase power quantity
#define	EC_RnL1         EC_Back2 + 17*3
#define	EC_RnL2			EC_RnL1 +5
#define	EC_RnL3			EC_RnL1 +10
#define	Chk_ECRnL       EC_RnL1 +15
//apparent forward split-phase power quantity
#define	EC_QpL1         EC_Back2 + 17*4
#define	EC_QpL2			EC_QpL1 +5
#define	EC_QpL3			EC_QpL1 +10
#define	Chk_ECQpL       EC_QpL1 +15
//apparent reverse split-phase power  quantity
#define	EC_QnL1         EC_Back2 + 17*5
#define	EC_QnL2			EC_QnL1 +5
#define	EC_QnL3			EC_QnL1 +10
#define	Chk_ECQnL       EC_QnL1 +15

/*....  EC_Back3  ...............................................................*/
//reactive first quadrant and split-phase 88
#define EC_Rq1			EC_Back3 + 22*0
#define EC_Rq1L1		EC_Rq1 + 5
#define EC_Rq1L2		EC_Rq1 + 10
#define EC_Rq1L3		EC_Rq1 + 15
#define Chk_Rq1			EC_Rq1 + 20
//reactive second quadrant and split-phase
#define EC_Rq2 			EC_Back3 + 22*1
#define EC_Rq2L1 		EC_Rq2 + 5
#define EC_Rq2L2		EC_Rq2 + 10
#define EC_Rq2L3		EC_Rq2 + 15
#define Chk_Rq2			EC_Rq2 + 20
//reactive third quadrant and split-phase
#define EC_Rq3			EC_Back3 + 22*2
#define EC_Rq3L1 		EC_Rq3 + 5
#define EC_Rq3L2		EC_Rq3 + 10
#define EC_Rq3L3		EC_Rq3 + 15
#define Chk_Rq3			EC_Rq3 + 20
//reactive forth quadrant and split-phase
#define EC_Rq4			EC_Back3 + 22*3
#define EC_Rq4L1 		EC_Rq4 + 5
#define EC_Rq4L2		EC_Rq4 + 10
#define EC_Rq4L3		EC_Rq4 + 15
#define Chk_Rq4			EC_Rq4 + 20

//*....reactive quadrant tariff power quantity 88...................................................*/
//reactive first quadrant tariff power quantity
#define	EC_Rq1F1		EC_Back4 + 22*0
#define	EC_Rq1F2		EC_Rq1F1 + 5
#define	EC_Rq1F3		EC_Rq1F1 + 10
#define	EC_Rq1F4		EC_Rq1F1 + 15
#define	Chk_RQ1F		EC_Rq1F1 + 20
//reactive second quadrant tariff power quantity
#define	EC_Rq2F1		EC_Back4 + 22*1
#define	EC_Rq2F2		EC_Rq2F1 + 5
#define	EC_Rq2F3		EC_Rq2F1 + 10
#define	EC_Rq2F4		EC_Rq2F1 + 15
#define	Chk_RQ2F		EC_Rq2F1 + 20
//reactive third quadrant tariff power quantity
#define	EC_Rq3F1		EC_Back4 + 22*2
#define	EC_Rq3F2		EC_Rq3F1 + 5
#define	EC_Rq3F3		EC_Rq3F1 + 10
#define	EC_Rq3F4		EC_Rq3F1 + 15
#define	Chk_RQ3F		EC_Rq3F1 + 20
//reactive forth quadrant tariff power quantity
#define	EC_Rq4F1		EC_Back4 + 22*3
#define	EC_Rq4F2		EC_Rq4F1 + 5
#define	EC_Rq4F3		EC_Rq4F1 + 10
#define	EC_Rq4F4		EC_Rq4F1 + 15
#define	Chk_RQ4F		EC_Rq4F1 + 20
//*.... calculating month hour flag............................................................*/
#define MonPF           MON_ZZZZ        //2
#define BILLYMDHms      MonPF+2         //6
#define BILLCnt         BILLYMDHms+6    //2
#define MON_EC_CHK      BILLCnt+2       //2
/*....  MD_Back1  420 ...........................................................*/
//**active forward demand** 42
#define	MD_Pp			MD_Back1 +42*0
#define	MD_PpTme        MD_Pp +3
#define MD_PpF1			MD_Pp +8
#define	MD_PpF1Tme		MD_Pp +11
#define	MD_PpF2			MD_Pp +16
#define	MD_PpF2Tme		MD_Pp +19
#define	MD_PpF3			MD_Pp +24
#define	MD_PpF3Tme		MD_Pp +27
#define	MD_PpF4			MD_Pp +32
#define	MD_PpF4Tme		MD_Pp +35
#define	ChkMD_Pp        MD_Pp +40
//**active reverse demand** 42
#define	MD_Pn			MD_Back1 +42*1
#define	MD_PnTme        MD_Pn +3
#define MD_PnF1			MD_Pn +8
#define	MD_PnF1Tme		MD_Pn +11
#define	MD_PnF2			MD_Pn +16
#define	MD_PnF2Tme		MD_Pn +19
#define	MD_PnF3			MD_Pn +24
#define	MD_PnF3Tme		MD_Pn +27
#define	MD_PnF4			MD_Pn +32
#define	MD_PnF4Tme		MD_Pn +35
#define	ChkMD_Pn        MD_Pn +40
//**apparent forward demand** 42
#define	MD_Qp			MD_Back1 +42*2
#define	MD_QpTme        MD_Qp +3
#define MD_QpF1			MD_Qp +8
#define	MD_QpF1Tme		MD_Qp +11
#define	MD_QpF2			MD_Qp +16
#define	MD_QpF2Tme		MD_Qp +19
#define	MD_QpF3			MD_Qp +24
#define	MD_QpF3Tme		MD_Qp +27
#define	MD_QpF4			MD_Qp +32
#define	MD_QpF4Tme		MD_Qp +35
#define	ChkMD_Qp        MD_Qp +40
//**apparent reverse demand** 42
#define	MD_Qn			MD_Back1 +42*3
#define	MD_QnTme        MD_Qn +3
#define MD_QnF1			MD_Qn +8
#define	MD_QnF1Tme		MD_Qn +11
#define	MD_QnF2			MD_Qn +16
#define	MD_QnF2Tme		MD_Qn +19
#define	MD_QnF3			MD_Qn +24
#define	MD_QnF3Tme		MD_Qn +27
#define	MD_QnF4			MD_Qn +32
#define	MD_QnF4Tme		MD_Qn +35
#define	ChkMD_Qn        MD_Qn +42
//**reactive forward demand** 42
#define	MD_Rp			MD_Back1 +42*4
#define	MD_RpTme        MD_Rp +3
#define MD_RpF1			MD_Rp +8
#define	MD_RpF1Tme		MD_Rp +11
#define	MD_RpF2			MD_Rp +16
#define	MD_RpF2Tme		MD_Rp +19
#define	MD_RpF3			MD_Rp +24
#define	MD_RpF3Tme		MD_Rp +27
#define	MD_RpF4			MD_Rp +32
#define	MD_RpF4Tme		MD_Rp +35
#define	ChkMD_Rp        MD_Rp +40
//**reactive reverse demand** 42
#define	MD_Rn			MD_Back1 +42*5
#define	MD_RnTme        MD_Rn +3
#define MD_RnF1			MD_Rn +8
#define	MD_RnF1Tme		MD_Rn +11
#define	MD_RnF2			MD_Rn +16
#define	MD_RnF2Tme		MD_Rn +19
#define	MD_RnF3			MD_Rn +24
#define	MD_RnF3Tme		MD_Rn +27
#define	MD_RnF4			MD_Rn +32
#define	MD_RnF4Tme		MD_Rn +35
#define	ChkMD_Rn        MD_Rn +40

//reactive forth quadrant demand 168=42*4
#define	MD_Rq1			MD_Back1 +42*6
#define	MD_Rq1Tme       MD_Rq1 +3
#define MD_Rq1F1		MD_Rq1 +8
#define	MD_Rq1F1Tme		MD_Rq1 +11
#define	MD_Rq1F2		MD_Rq1 +16
#define	MD_Rq1F2Tme		MD_Rq1 +19
#define	MD_Rq1F3		MD_Rq1 +24
#define	MD_Rq1F3Tme		MD_Rq1 +27
#define	MD_Rq1F4		MD_Rq1 +32
#define	MD_Rq1F4Tme		MD_Rq1 +35
#define	MD_Rq1_Chk		MD_Rq1 +40

#define	MD_Rq2			MD_Back1 +42*7
#define	MD_Rq2Tme       MD_Rq2 +3
#define MD_Rq2F1		MD_Rq2 +8
#define	MD_Rq2F1Tme		MD_Rq2 +11
#define	MD_Rq2F2		MD_Rq2 +16
#define	MD_Rq2F2Tme		MD_Rq2 +19
#define	MD_Rq2F3		MD_Rq2 +24
#define	MD_Rq2F3Tme		MD_Rq2 +27
#define	MD_Rq2F4		MD_Rq2 +32
#define	MD_Rq2F4Tme		MD_Rq2 +35
#define	MD_Rq2_Chk		MD_Rq2 +40

#define	MD_Rq3			MD_Back1 +42*8
#define	MD_Rq3Tme       MD_Rq3 +3
#define MD_Rq3F1		MD_Rq3 +8
#define	MD_Rq3F1Tme		MD_Rq3 +11
#define	MD_Rq3F2		MD_Rq3 +16
#define	MD_Rq3F2Tme		MD_Rq3 +19
#define	MD_Rq3F3		MD_Rq3 +24
#define	MD_Rq3F3Tme		MD_Rq3 +27
#define	MD_Rq3F4		MD_Rq3 +32
#define	MD_Rq3F4Tme		MD_Rq3 +35
#define	MD_Rq3_Chk		MD_Rq3 +40

#define	MD_Rq4			MD_Back1 +42*9
#define	MD_Rq4Tme       MD_Rq4 +3
#define MD_Rq4F1		MD_Rq4 +8
#define	MD_Rq4F1Tme		MD_Rq4 +11
#define	MD_Rq4F2		MD_Rq4 +16
#define	MD_Rq4F2Tme		MD_Rq4 +19
#define	MD_Rq4F3		MD_Rq4 +24
#define	MD_Rq4F3Tme		MD_Rq4 +27
#define	MD_Rq4F4		MD_Rq4 +32
#define	MD_Rq4F4Tme		MD_Rq4 +35
#define	MD_Rq4_Chk		MD_Rq4 +40
/*....  MD_Back1  2 .............................................................*/
#define MON_MD_CHK      MON_MD_CHK_ //2
//*....active forward reverse power quantity in one minute 12 ...............................................*/
#define EC_Pp1Min       EC_Back5        //5
#define EC_Pn1Min       EC_Pp1Min+4     //5
#define EC_1Min_Chk     EC_Pn1Min+4     //2

/*----  Para_Back1  0/0 ---------------------------------------------------------*/
#ifdef SINGLE_PHASE_MULTI_TARIFF


#else
/*----  Para_Back2  141/192 -----------------------------------------------------*/
//4
#define	MD_Para         Para_Back2
//#define	MD_BlockTm		MD_Para	              maximum demand counting period unit min BCD code
#define	MD_BlockTm		MD_Para				//
//#define	MD_SlidingTm	MD_BlockTm+1             maximum demand block time unit min BCD code
#define	MD_SlidingTm	MD_BlockTm+1		//
//#define MD_Para_Chk		MD_SlidingTm+1	demand parameter check code
#define MD_Para_Chk		MD_SlidingTm+1		//
//67
//#define	Disp_ScTab      Para_Back2+4       	//64 rotator displaying chart
#define	Disp_ScTab      Para_Back2+4       	//
//#define	Disp_ScNum      Disp_ScTab+64  rotator displaying number (32 maximum)           one byte BCD code
#define	Disp_ScNum      Disp_ScTab+64       //
#define	Chk_ScTab       Disp_ScNum+1		//2  
//67
//#define	Disp_KeyTab     Disp_ScTab+67       //64 inquiry display
#define	Disp_KeyTab     Disp_ScTab+67       //
//#define	Disp_KeyNum     Disp_KeyTab+64  inquiry display number       (32 maximum)
#define	Disp_KeyNum     Disp_KeyTab+64      //
#define	Chk_KeyTab      Disp_KeyNum+1		//2
//3
//#define	DspInv          Disp_KeyTab+67      //rotator time one  byte BCD code
#define	DspInv          Disp_KeyTab+67      //
//#define	Chk_DspInv		DspInv+1			//check code two bytes
#define	Chk_DspInv		DspInv+1			//
/*----  Para_Back3 79/80 --------------------------------------------------------*/
//#define     Meter_Para        	Para_Back3              //meter parameter
#define     Meter_Para        	Para_Back3              //
//#define     MeterAddr		  	Meter_Para				//meter address 6
#define     MeterAddr		  	Meter_Para				//
//#define     UserNo			  	MeterAddr+6				//user number 6
#define     UserNo			  	MeterAddr+6				//
//#define     SeqNo			  	UserNo+6				//device number
#define     SeqNo			  	UserNo+6				//
//#define     PassWord          	SeqNo +6			       level password  12 length
#define     PassWord          	SeqNo +6				//
//#define		DeviceAddr			PassWord+24				//device address 32 for IEC1107
#define		DeviceAddr			PassWord+24				//
//#define		BillingDate			DeviceAddr+31			//calculating date 10=automatic calculation at the end of a month 1-28=automatic calculate at the appointed date >28 calculate by hand
#define		BillingDate			DeviceAddr+31			//
#endif

////#define		LastMon_ESWAP		BillingDate+1			//last month  last two months change power quantity storage area or not  0=nonchange  'S'=change
//#define		LastMon_ESWAP		BillingDate+1			//
//#define		LastMon_MSWAP		LastMon_ESWAP+1			//last month last two month change demand storage area or not 0=nonchange 'S'=change
//#define		LastMon_MSWAP		LastMon_ESWAP+1			//
//#define		PortDefine			LastMon_MSWAP+1			//terminal definition 1
//#define		PortDefine			LastMon_MSWAP+1			//
//#define     PowerDnDisp_        BillingDate+2           //whether turn off display when power off 1 0x01turn off 0x00 turn on
#define     PowerDnDisp_        BillingDate+2           //
//#define		PortDefine			PowerDnDisp_+1			//terminal definition 1
#define		PortDefine			PowerDnDisp_+1			//

#define		Chk_MeterAddr		PortDefine+1  

#define		kWCumuMode			Chk_MeterAddr+2
//#define		kvarCumuMode		kWCumuMode+1			//reactive power calculating form 0x00 0x01 ~ 0x05
#define		kvarCumuMode		kWCumuMode+1			//
//#define     PowerCumu           kvarCumuMode+1          //power accumulation form 0x00 algebraic sum  0x01absolute value sum
#define     PowerCumu           kvarCumuMode+1          //
//#define     ShutDispTm          PowerCumu+1             //delay after power off x hour turn off display 
#define     ShutDispTm          PowerCumu+1             //
//#define     _MBillDelyTM        ShutDispTm+1            //demand calculation delay time 1 Hex Min
#define     _MBillDelyTM        ShutDispTm+1            //
//#define     _DLBillDelyTM       _MBillDelyTM+1          //demand calculation delay time 1 Hex Min
#define     _DLBillDelyTM       _MBillDelyTM+1          //

#define		BurnFirst			_DLBillDelyTM+1	

/*....  Last Month Ptr Block define  ............................................*/
#define     LastMonPtr          BurnFirst+2
//#define		LastMonPtrLoca		LastMonPtr                   calculating pointer of 12 month power quantity
#define		LastMonPtrLoca		LastMonPtr			    //
//#define		LastMonPtrMDLoca	LastMonPtrLoca+1         calculating pointer of 12 month power quantity
#define		LastMonPtrMDLoca	LastMonPtrLoca+1    	//
//#define		LastBillOK			LastMonPtrMDLoca+1   last calculation done ==0x00,or nonzero
#define		LastBillOK			LastMonPtrMDLoca+1	    //
#define		LastMonPtrLoca_CHK	LastMonPtrLoca+1	    //2

/*----  Para_Back4  70/70 -------------------------------------------------------*/
//28
//#define		LPPara				Para_Back4				//overload curve parameter
#define		LPPara				Para_Back4				//
//#define		DT_Ptr_Save			LPPara	                    Date TimeEntry operation guidence
#define		DT_Ptr_Save			LPPara					//4 DateTimeEntry操作指针
//#define		Data_Ptr_Save		DT_Ptr_Save+4            DateEntry operation pointer
#define		Data_Ptr_Save		DT_Ptr_Save+4			//4 DataEntry操作指针
//#define		TimeInv_Para		Data_Ptr_Save+4                 spacing time parameter
#define		TimeInv_Para		Data_Ptr_Save+4			//
//#define		FieldCode_Para		TimeInv_Para+2           //14 bytes coding parameter
#define		FieldCode_Para		TimeInv_Para+2			//
//#define		FieldNum_Para		FieldCode_Para+14	 effective bytes parameter
#define		FieldNum_Para		FieldCode_Para+14		//
//#define		LP_RecLen			FieldNum_Para+1         length of one record
#define		LP_RecLen			FieldNum_Para+1			//
//#define		Chk_LP				LP_RecLen                   check
#define		Chk_LP				LP_RecLen				//2 校验
//32
//#define		LP_CurrentD_Qp		LPPara+28                   current demand being load curve buffer
#define		LP_CurrentD_Qp		LPPara+28				//
#define		LP_CurrentD_Qn		LP_CurrentD_Qp+3		//3
#define		LP_CurrentD_Pp		LP_CurrentD_Qn+3
#define		LP_CurrentD_Pn		LP_CurrentD_Pp+3
#define		LP_CurrentD_Rp		LP_CurrentD_Pn+3
#define		LP_CurrentD_Rn		LP_CurrentD_Rp+3
#define		LP_CurrentD_Qdr1	LP_CurrentD_Rn+3
#define		LP_CurrentD_Qdr2	LP_CurrentD_Qdr1+3
#define		LP_CurrentD_Qdr3	LP_CurrentD_Qdr2+3
#define		LP_CurrentD_Qdr4	LP_CurrentD_Qdr3+3
#define		Chk_LP_CurrentD		LP_CurrentD_Qdr4+3		//2
//10
//#define		LP_DeltaPp			LP_CurrentD_Qp+32      load curve active being calculating Delta value buffer
#define		LP_DeltaPp			LP_CurrentD_Qp+32		//
//#define		LP_DeltaRp			LP_DeltaPp+4       load curve active being calculating Delta value buffer
#define		LP_DeltaRp			LP_DeltaPp+4			//
//#define		Chk_LP_Delt			LP_DeltaRp+4	       check
#define		Chk_LP_Delt			LP_DeltaRp+4			//2 校验



#ifdef SINGLE_PHASE_MULTI_TARIFF
#else
/*---- Para_Back5  213/213 ------------------------------------------------------*/
//24
//#define     Val_VFailure        Para_Back5        split-phase threshold value
#define     Val_VFailure        Para_Back5          //
//#define     Val_VOver           Val_VFailure+2     overvoltage threshold value
#define     Val_VOver           Val_VFailure+2      //
//#define     Val_IOver           Val_VOver+2      overcurrent threshold value
#define     Val_IOver           Val_VOver+2     	//
//#define     Dly_VFailure        Val_IOver+2        split-phase delay time
#define     Dly_VFailure        Val_IOver+2         //
//#define     Dly_VOver           Dly_VFailure+1     overvoltage delay time
#define     Dly_VOver           Dly_VFailure+1      //
//#define     Dly_IOver           Dly_VOver+1        overcurrent delay time
#define     Dly_IOver           Dly_VOver+1         //
#define		Val_UnbV			Dly_IOver+1			//2
#define		Dly_UnbV			Val_UnbV+2			//1
//#define     Chk_Para5           Dly_UnbV+2         //check code
#define     Chk_Para5           Dly_UnbV+2         //
#endif

/*
 //#define     Val_VFailure        Para_Back5          //2 split phase threshod value
 #define     Val_VFailure        Para_Back5          //2 断相阀值
 //#define     Val_VUnder          Val_VFailure+2      //2 loss of voltage threshold value
 #define     Val_VUnder          Val_VFailure+2      //2 失(欠)压阀值
 //#define     Val_VOver           Val_VUnder+2        //2 overvoltage threshold value
 #define     Val_VOver           Val_VUnder+2        //2 过压阀值
 //#define     Val_OverLoad        Val_VOver+2         //4 single phase load threshold value
 #define     Val_OverLoad        Val_VOver+2         //4 单相负荷阀值
 //#define     Val_LowPF           Val_OverLoad+4      //2 low power factor threshold value
 #define     Val_LowPF           Val_OverLoad+4      //2 低功率因数阀值
 //#define     Dly_VFailure        Val_LowPF+2         //2 split-phase delay time
 #define     Dly_VFailure        Val_LowPF+2         //2 断相延迟时间
 //#define     Dly_VUnder          Dly_VFailure+2      //2 loss of voltage delay time
 #define     Dly_VUnder          Dly_VFailure+2      //2 失(欠)压延迟时间
 //#define     Dly_VOver           Dly_VUnder+2        //2 overvoltage delay time
 #define     Dly_VOver           Dly_VUnder+2        //2 过压延迟时间
 //#define     Dly_OverLoad        Dly_VOver+2         //2 single phase load overrun delay time
 #define     Dly_OverLoad        Dly_VOver+2         //2 单相负荷超限延迟时间
 //#define     Dly_LowPF           Dly_OverLoad+2      //2 low power factor delay time
 #define     Dly_LowPF           Dly_OverLoad+2      //2 低功率因数延迟时间
 //#define     Chk_Para5           Dly_LowPF+2         //check code
 #define     Chk_Para5           Dly_LowPF+2         //检验码
 */
//7
//#define     Val_IUnder          Val_VFailure+24    loss of current value
#define     Val_IUnder          Val_VFailure+24     //3 失流阀值
//#define     Dly_IUnder          Val_IUnder+3       loss of current delay time
#define     Dly_IUnder          Val_IUnder+3        //2 失流延迟时间
#define     Chk_IUnder          Dly_IUnder+2        //2
//62
//#define     VFailureNumC        Val_IUnder+7      C phase split-phase times
#define     VFailureNumC        Val_IUnder+7        //2 C相断相次数
#define     VFailureNumB        VFailureNumC+2      //2 B
#define     VFailureNumA        VFailureNumB+2      //2 A
#define     VFailureNumAll      VFailureNumA+2      //2 All
//#define     VFailureTimC        VFailureNumAll+2   C phase split-phase accumulating time min
#define     VFailureTimC        VFailureNumAll+2    //3 C相断相累计时间 min
#define     VFailureTimB        VFailureTimC+3      //3 B
#define     VFailureTimA        VFailureTimB+3      //3 A
#define     VFailureTimAll      VFailureTimA+3      //3 All
//#define     VFailureLast1SC      VFailureTimAll+3     //5 C phase the latest split-phase starting time mmHHDDMMYY
#define     VFailureLast1SC      VFailureTimAll+3     //5 C相最近一次断相起始时间 mmHHDDMMYY
#define     VFailureLast1SB      VFailureLast1SC+5    //5 B 
#define     VFailureLast1SA      VFailureLast1SB+5    //5 A
#define     VFailureLast1SAll    VFailureLast1SA+5    //5 All
//#define     VFailureLast1PC     VFailureLast1SAll+5 //5 C phase the latest split-phase stoping time
#define     VFailureLast1PC     VFailureLast1SAll+5 //5 C相最近一次断相结束时间
#define     VFailureLast1PB     VFailureLast1PC+5   //5 B
#define     VFailureLast1PA     VFailureLast1PB+5   //5 A
#define     VFailureLast1PAll   VFailureLast1PA+5   //5 All
//#define     VF_Chk  VFailureLast1PAll+5           check
#define     VF_Chk  VFailureLast1PAll+5             //2 校验
//120
//#define     VUnderPnAll     VF_Chk+2+15*0      total loss of voltage during reverse active power quantity
#define     VUnderPnAll     VF_Chk+2+15*0       //4 总失压期间反向有功电量
//#define     VUnderPpAll     VUnderPnAll+4      total loss of voltage during forward active power quantity
#define     VUnderPpAll     VUnderPnAll+4       //4 总失压期间正向有功电量
//#define     VUnderTimAll    VUnderPpAll+4      total loss of voltage accumulating time
#define     VUnderTimAll    VUnderPpAll+4       //3 总失压累计时间
//#define     VUnderNumAll    VUnderTimAll+3    total loss of voltage accumulating times
#define     VUnderNumAll    VUnderTimAll+3      //2 总失压累计次数 
#define     VUnderAll_Chk   VUnderNumAll+2      //2
//#define     VUnderPnA       VUnderPnAll+15*1   A phase loss of voltage
#define     VUnderPnA       VUnderPnAll+15*1    //4 A相失压...
#define     VUnderPpA       VUnderPnA+4         //4
#define     VUnderTimA      VUnderPpA+4         //3
#define     VUnderNumA      VUnderTimA+3        //2
#define     VUnderA_Chk     VUnderNumA+2        //2
//#define     VUnderPnB       VUnderPnAll+15*2   B phase loss of voltage
#define     VUnderPnB       VUnderPnAll+15*2    //4 B相失压...
#define     VUnderPpB       VUnderPnB+4         //4
#define     VUnderTimB      VUnderPpB+4         //3
#define     VUnderNumB      VUnderTimB+3        //2
#define     VUnderB_Chk     VUnderNumB+2        //2
//#define     VUnderPnAB       VUnderPnAll+15*3    AB phase loss of voltage
#define     VUnderPnAB       VUnderPnAll+15*3     //4 AB相失压...
#define     VUnderPpAB       VUnderPnAB+4         //4
#define     VUnderTimAB      VUnderPpAB+4         //3
#define     VUnderNumAB      VUnderTimAB+3        //2
#define     VUnderAB_Chk     VUnderNumAB+2        //2
//#define     VUnderPnC       VUnderPnAll+15*4   C phase loss of voltage
#define     VUnderPnC       VUnderPnAll+15*4    //4 C相失压...
#define     VUnderPpC       VUnderPnC+4         //4
#define     VUnderTimC      VUnderPpC+4         //3
#define     VUnderNumC      VUnderTimC+3        //2
#define     VUnderC_Chk     VUnderNumC+2        //2
//#define     VUnderPnAC       VUnderPnAll+15*5     AC phase loss of voltage 
#define     VUnderPnAC       VUnderPnAll+15*5      //4 AC相失压...
#define     VUnderPpAC       VUnderPnAC+4          //4
#define     VUnderTimAC      VUnderPpAC+4          //3
#define     VUnderNumAC      VUnderTimAC+3         //2
#define     VUnderAC_Chk     VUnderNumAC+2         //2
//#define     VUnderPnBC       VUnderPnAll+15*6     BC phase loss of voltage
#define     VUnderPnBC       VUnderPnAll+15*6      //4 BC相失压...
#define     VUnderPpBC       VUnderPnBC+4          //4
#define     VUnderTimBC      VUnderPpBC+4          //3
#define     VUnderNumBC      VUnderTimBC+3         //2
#define     VUnderBC_Chk     VUnderNumBC+2         //2
//#define     VUnderPnABC       VUnderPnAll+15*7      ABC phase loss of voltage
#define     VUnderPnABC       VUnderPnAll+15*7       //4 ABC相失压...
#define     VUnderPpABC       VUnderPnABC+4          //4
#define     VUnderTimABC      VUnderPpABC+4          //3
#define     VUnderNumABC      VUnderTimABC+3         //2
//#define     VUnderABC_Chk     VUnderNumABC+2         check code
#define     VUnderABC_Chk     VUnderNumABC+2         //2 校验码

/*----  TestMode 136/136 --------------------------------------------------------*/
//12 En
#define		Tst_EC_Pp0			TestMode		//5
#define		Tst_EC_Rp0			Tst_EC_Pp0+4	//5
#define		Chk_Tst				Tst_EC_Rp0+4	//2
//124 Pulse
#define     Tst_EC_Pulse        TestMode+10     //82
#define     Tst_MD_Cumu         Tst_EC_Pulse+82 //42

/*----  TestMode 98/98 ----------------------------------------------------------*/
//**active forward demand** 22
#define	cMD_Pp			    MD_CUMU +22*0
#define cMD_PpF1			cMD_Pp +4
#define	cMD_PpF2			cMD_Pp +8
#define	cMD_PpF3			cMD_Pp +12
#define	cMD_PpF4			cMD_Pp +16
#define	ChkcMD_Pp           cMD_Pp +20
//**active reverse demand** 22
#define	cMD_Pn			    MD_CUMU +22*1
#define cMD_PnF1			cMD_Pn +4
#define	cMD_PnF2			cMD_Pn +8
#define	cMD_PnF3			cMD_Pn +12
#define	cMD_PnF4			cMD_Pn +16
#define	ChkcMD_Pn           cMD_Pn +20
//**reactive forward demand** 22
#define	cMD_Rp			    MD_CUMU +22*2
#define cMD_RpF1			cMD_Rp +4
#define	cMD_RpF2			cMD_Rp +8
#define	cMD_RpF3			cMD_Rp +12
#define	cMD_RpF4			cMD_Rp +16
#define	ChkcMD_Rp           cMD_Rp +20
//**reactive reverse demand ** 22
#define	cMD_Rn			    MD_CUMU +22*3
#define cMD_RnF1			cMD_Rn +4
#define	cMD_RnF2			cMD_Rn +8
#define	cMD_RnF3			cMD_Rn +12
#define	cMD_RnF4			cMD_Rn +16
#define	ChkcMD_Rn           cMD_Rn +20
//**calculating times flag ** 10
#define CUMU_Num            ChkcMD_Rn+2     //2
#define CUMU_Time           CUMU_Num+2      //6
#define CUMU_B_CHK          CUMU_Time+6     //2

/*----  LOADPROFILEPARA 180/180 -------------------------------------------------*/
//----  Load Info (130/130)  --------------------------------
#define		LoadInfo_			LOADPROFILEPARA 		//
#define	LoadInfo1_			LoadInfo_
#define	RecAddr1_			LoadInfo1_				//4
#define	TimeInv1_			RecAddr1_+4				//2
#define	MaxRecNUM1_			TimeInv1_+2				//2
#define	RegNUM1_			MaxRecNUM1_+2			//1
#define	RegID1_				RegNUM1_+1				//7
//#define...... 8 channels in total
//#define...... 共8通道
#define	LoadInfo_CHK_		LoadInfo_+128			//2
//----  Load InfoRun (50/50)  --------------------------------
#define		LoadInfoRun_		LoadInfo_CHK_+2
#define	LoadInfoRun1_		LoadInfoRun_
#define	ReadPtr1_			LoadInfoRun1_			//2
#define	RecNUM1_			ReadPtr1_+2				//2
#define	RecPtr1_			RecNUM1_+2				//2
//#define...... 8 channels in total
//#define...... 共8通道
#define	LoadInfoRun_CHK_	LoadInfoRun_+48			//2

/*-----------net para*************************/
//30

#define NET_IP          NET_PARA
#define NET_PORT       NET_IP+6
#define NET_APN        NET_PORT+4
#define NET_NED_       NET_APN+18

#define NET_SEC_IP_STAR NET_SEC_IP
#define NET_SEC_IP_END_ NET_SEC_IP_END

#define		BillingDate2   BillingDateTwo
#define         BillingDate2Chk   (BillingDate2+1)
#define         BillingDate2End    (BillingDate2Chk + 2)
#define		BillingDate3   BillingDate2End
#define         BillingDate3Chk   (BillingDate3+1)
#define         BillingDate3End    (BillingDate3Chk + 2)

//preserve current and last average power
#define AVR_MD  AVR_MD_ST
//#define AVR_MD_CHK (AVR_MD+52)
#define AVR_MD_END_  (AVR_MD+52)

/*************user-defined********************/
#define USER_DEFINE USER_DEFINE_STAT
#define USER_DEFINE_CHK USER_DEFINE+6

/*************RF parameter********************/
#define RF_FREQ      RF_PARA
//#define RF_PANID     RF_FREQ+3 //add 0 before 5 bytes
#define RF_PANID     RF_FREQ+3 //
#define RF_PARA_END_ RF_PANID+3

#ifdef SINGLE_PHASE_MULTI_TARIFF
#else
/*************PASSNEW*************************/
#define PASSWORD_NEW     PASSNEW
#define PASSWORD_NEW_CHK PASSNEW+8
//#define PASSWORD_NEW_END PASSWORD_NEW_CHK+2 //reserve 2 check code bytes
#define PASSWORD_NEW_END PASSWORD_NEW_CHK+2 //
#endif
//***********LC_DATE*************************/

//#define LOAD_DATE_SET_COUNT  LOAD_DATE_  //reserve appinted date record pointer
#define LOAD_DATE_SET_COUNT  LOAD_DATE_  // 0x1400
//#define LOAD_DATE_SET_LEN   LOAD_DATE_SET_COUNT+2//appointed period length
#define LOAD_DATE_SET_LEN   LOAD_DATE_SET_COUNT+2//
//#define LOAD_DATE_C_COUNT  LOAD_DATE_SET_LEN+2    //current preserved date pointer <180           D310
#define LOAD_DATE_C_COUNT  LOAD_DATE_SET_LEN+2    //
//#define LOAD_DATE_R_COUNT  LOAD_DATE_C_COUNT +2   //maximum pointer of load curve date sheet <180          D311
#define LOAD_DATE_R_COUNT  LOAD_DATE_C_COUNT +2   //
#define LOAD_DATE_DATA   LOAD_DATE_R_COUNT+2                                         //D310
#define LOAD_DATE_MAX   360
#define LOAD_DATE_LEN   5*LOAD_DATE_MAX

//----- EVENTLOG -------------------------------------------------------------
//150
//#define	EVENT_POFF_PTR	EV_STAR	                   preserve position of recording pointer
#define	EVENT_POFF_PTR	EV_STAR			     //
//#define	EVENT_POFF_1	EVENT_POFF_PTR+1	 //5 preserve the first record, then increase by 5 on each record later on
#define	EVENT_POFF_1	EVENT_POFF_PTR+1	 //
#define	EVENT_POFF_2	EVENT_POFF_PTR+5	 //5
//#define	EVENT_POFF_TIMES (EVENT_POFF_PTR+20*5)//preservation times
#define	EVENT_POFF_TIMES (EVENT_POFF_PTR+20*5)//
//150
#define	EVENT_PON_PTR	EVENT_POFF_PTR+151	//1
#define	EVENT_PON_1		EVENT_PON_PTR+1		//5
#define	EVENT_PON_2		EVENT_PON_PTR+5		//5
#define	EVENT_PON_TIMES	(EVENT_PON_PTR+20*5)
//150
//#define	EVENT_PROG_PTR	EVENT_PON_PTR+150+2       preserve position of recording pointer
#define	EVENT_PROG_PTR	EVENT_PON_PTR+150+2	//
//#define	EVENT_PROG_1	EVENT_PROG_PTR+1	//5 preserve the first record, then increase by 5 on each record later on
#define	EVENT_PROG_1	EVENT_PROG_PTR+1	//
#define	EVENT_PROG_2	EVENT_PROG_PTR+5	//5
//#define	EVENT_PROG_TIMES (EVENT_PROG_PTR+5*20)//preservation times
#define	EVENT_PROG_TIMES (EVENT_PROG_PTR+5*20)//
//next is 2211=0x08A3

#ifdef SINGLE_PHASE_MULTI_TARIFF

#else
//#define NEV_CURRFX_CNT  NEV_STAR  //reverse times
#define NEV_CURRFX_CNT  NEV_STAR  //
//#define NEV_CURRFX_PRT  (NEV_CURRFX_CNT+2)//pointer
#define NEV_CURRFX_PRT  (NEV_CURRFX_CNT+2)//
//#define NEV_CURRFX_CRD  (NEV_CURRFX_PRT+1)//reverse record
#define NEV_CURRFX_CRD  (NEV_CURRFX_PRT+1)//
//50 bytes, 10 records, each record includes 5 bytes

//#define NEV_LOSTU_CNT   (NEV_CURRFX_CRD+10*5)//loss of voltage times
#define NEV_LOSTU_CNT   (NEV_CURRFX_CRD+10*5)//
//#define NEV_LOSTU_PRT  (NEV_LOSTU_CNT+2)//pointer
#define NEV_LOSTU_PRT  (NEV_LOSTU_CNT+2)//
//#define NEV_LOSTU_CRD   (NEV_LOSTU_PRT + 1)//loss of voltage record
#define NEV_LOSTU_CRD   (NEV_LOSTU_PRT + 1)//
//#define NEV_LOSTU_VAL  (NEV_LOSTU_CRD + 10*5)//loss of voltage value
#define NEV_LOSTU_VAL  (NEV_LOSTU_CRD + 10*5)//

//#define NEV_OVERU_CNT   (NEV_LOSTU_VAL+10*6)//overvoltage times
#define NEV_OVERU_CNT   (NEV_LOSTU_VAL+10*6)//
#define NEV_OVERU_PRT   (NEV_OVERU_CNT + 2)
//#define NEV_OVERU_CRD   (NEV_OVERU_PRT + 1)//overvoltage records
#define NEV_OVERU_CRD   (NEV_OVERU_PRT + 1)//

//#define NEV_OVERU_VAL  (NEV_OVERU_CRD + 10*5)//overvoltage value
#define NEV_OVERU_VAL  (NEV_OVERU_CRD + 10*5)//
//#define NEV_HDERR_CNT   (NEV_OVERU_VAL+10*6)//firmware error times
#define NEV_HDERR_CNT   (NEV_OVERU_VAL+10*6)//
#define NEV_HDERR_PRT   (NEV_HDERR_CNT+2)
//#define NEV_HDERR_CRD   (NEV_HDERR_PRT+1)//firmware error records
#define NEV_HDERR_CRD   (NEV_HDERR_PRT+1)//
//#define NEV_XXERR_CNT   (NEV_HDERR_CRD + 10*5)//phase error times
#define NEV_XXERR_CNT   (NEV_HDERR_CRD + 10*5)//
#define NEV_XXERR_PRT   (NEV_XXERR_CNT + 2)
//#define NEV_XXERR_CRD   (NEV_XXERR_PRT + 1)//phase error records
#define NEV_XXERR_CRD   (NEV_XXERR_PRT + 1)//
//#define NEV_BARERR_CNT  (NEV_XXERR_CRD + 10*5)//died-battery times
#define NEV_BARERR_CNT  (NEV_XXERR_CRD + 10*5)//
#define NEV_BARERR_PRT  (NEV_BARERR_CNT + 2)
//#define NEV_BARERR_CRD  (NEV_BARERR_PRT + 1)//died-battery records
#define NEV_BARERR_CRD  (NEV_BARERR_PRT + 1)//
//#define NEV_OVERI_CNT   (NEV_BARERR_CRD+10*5)//overcurrent times
#define NEV_OVERI_CNT   (NEV_BARERR_CRD+10*5)//
#define NEV_OVERI_PRT   (NEV_OVERI_CNT + 2)
//#define NEV_OVERI_CRD   (NEV_OVERI_PRT + 1)//overcurrent records
#define NEV_OVERI_CRD   (NEV_OVERI_PRT + 1)//

//#define NEV_OVERI_VAL  (NEV_OVERI_CRD + 10*5)//overcurrent value
#define NEV_OVERI_VAL  (NEV_OVERI_CRD + 10*5)//
#endif
// add by BNthang on January 1st, 2016

//the remaining last 18 bytes
#endif

