#include "..\inc\includes.h"// add by bnthang

/******************************************************************/
#define	MeterPara		0x001000
/*******************************************************************
	Factory parameter define
*******************************************************************/
#define METER_TYPE 2

#if METER_TYPE == 1
#define  FC_CP		5000			//xxxx imp/kWh			3600*1000 /（FC_Un*FC_Imax)
#define	 FC_Un	        230.0
#define  FC_Ib          5  				//XXX.x A				Ib*10
#define  FC_Imax        6.0 			//XXX.x A	Imax*10
#endif

#if  METER_TYPE == 2
#define	 FC_Un	        230.0
#define  FC_CP			500
//#define  FC_Ib          50 				//XXX.x A
#define  FC_Ib          10 				//XXX.x A
#define  FC_Imax        100.0 			//XXX.x A				Imax*10
#endif

#if  METER_TYPE == 3
#define  FC_Un          110.0			//XXX.x V	
#define  FC_CP			10000
#define  FC_Ib          5  				//XXX.x A				Ib*10
#define  FC_Imax        6.0 			//XXX.x A	Imax*10
#endif

#if  METER_TYPE == 4
#define  FC_Un          57.7			//XXX.x V	
#define  FC_CP		20000	
#define  FC_Ib          5  				//XXX.x A				Ib*10
#define  FC_Imax        10.0 			//XXX.x A	Imax*10
#endif

#if  METER_TYPE == 5
#define	 FC_Un	        230.0
#define  FC_CP		500	
#define  FC_Ib          10 				//XXX.x A	
#define  FC_Imax        100.0 			//XXX.x A				Imax*10
#endif

/*******************************************************************
	Hardware define
//the undefined firmware type is default as
//the oldes version before 20140226 V1.8.6 of the company can all use LCD with "M" and "P.on"
//HARDWARE-ONE
//add LCD with "M" and "P.on"
//HARDWARE TWO
//add four quadrants reactive, "improt" and "export"
*******************************************************************/
//#define HARDWARE_ONE
#ifdef SINGLE_PHASE_MULTI_TARIFF
#else
#define HARDWARE_TWO
#endif

//#undef HARDWARE_ONE
//#undef HARDWARE_TWO

//#define  FC_CP		    500	
//#define  FC_CP		    10000			
//#define  FC_Un          110.0			//XXX.x V				Un*1.1
			
//#define  FC_Ib          50 				//XXX.x A				Ib*10
//#define  FC_Imax        100.0 			//XXX.x A				Imax*10
#define	 FC_PW			(FC_Ib*FC_Un)

//#define  FC_Ps          (float)FC_CP/1000*230*5*(ADJ_TM*5)/1000/3600     //the impulse needed to be output during meter calibration time
#define  FC_Ps          (float)FC_CP/1000*230*5*(ADJ_TM*5)/1000/3600     //在校表时间内应输出的脉冲数
#define  ADJ_TM         1200   //6s

//1000*3600*10/FC_CP
#define  FC_CP_MDCalc   36000

#define		METER_3H3W		0
#define		METER_CTPT_EN	1

//#define	 FC_CPD		    FC_CP/100 //xxxxxx.xxkwh
#define	 FC_CPD		    FC_CP/100	  //xxxxxxx.xkwh
#define  FC_CPD_Tst		FC_CP/100	  //TestMode xxxxxx.xxkwh
#define	 FC_S0Out       FC_CP/10
/*******************************************************************/
#define  FC_IPs			(0.002*0x1000000*0.6/(FC_Imax/FC_Ib)) 		//	Active Start current
#define  FC_IQs         (0.003*0x1000000*0.6/(FC_Imax/FC_Ib)) 		//	Reactive Start current
#define  FC_IP0			(0.6*FC_IPs) 	//	Active Zero current
#define  FC_IQ0			(0.6*FC_IQs) 	//	Reactive Zero current

#define  FC_fCP                 (double)FC_CP
#define  FC_fCQ                 (double)FC_CQ
#define  FC_fUmax               (double)FC_Umax
#define  FC_fImax               (double)FC_Imax

/*******************************************************************/
#define	Check_Delay		20
//#define	PowOn_Delay		250		//on-power full display delay machine times
#define	PowOn_Delay		250		//上电全显延迟 机器周期数
#define	BatCHKTmr		250

/*
#define ActiImpThreshold (long)(4680000*(1+ 0.0/100))
#define AppaImpThreshold (long)(4680000*(1+ 0.0/100))
#define ReacImpThreshold (long)(4680000*(1+ 0.0/100))
*/

#define ActiImpThreshold (long)(5760000)
#define AppaImpThreshold (long)(5760000)
#define ReacImpThreshold (long)(5760000)



