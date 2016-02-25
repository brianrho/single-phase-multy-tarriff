#ifndef		_D_LAYOUT_H
#define		_D_LAYOUT_H


#define	FLS_MAXADDR		0x100000//0x00083FFF
#define	PAGE_CAP		256//(256+8)
//#define	PAGES			2048
//#define	BLOCKS			256

#define FLS_START       0x00000000UL
#define FLS_SIZE        (FLS_MAXADDR+1)

#define	LASTMON_DATA	FLS_START	        //25344=96*PAGE_CAP=96*264  0x00000000
#define	LASTMON_DATAEND	EVENTLOG+(96UL*PAGE_CAP)    

 //512K is used as load curve address
#define LOADCURVE       0x80000//EVENTLOG_END        //515328=(2048-96)*PAGE_CAP 0x00006300
#define LOADCURVE_END   FLS_SIZE            
                                            //12672=48*PAGE_CAP=48*264  0x00003180
#define FLS_MONDATA_BAK (LASTMON_DATA+48UL*PAGE_CAP)


//======  LASTMON_DATA now size = (440+12+420+2)*2 = 1748 =====================
#define SIZE_MONBLK     (440+12+420+2)
#define SIZE_EC_MONBLK  (440+12)
#define SIZE_MD_MONBLK  (420+2)

#define	LM1_EC		    LASTMON_DATA+SIZE_MONBLK*0      //440
#define LM1_ZZZZ        LM1_EC+440                      //12
#define	LM1_MD		    LM1_ZZZZ+12 	                //422=420+2
                                    
#define LM_EC_      (0)         
#define LM_ZZZZ_    (440)       
#define LM_EC_CHK_  (440+12-2)  
#define Mon_Time    (440+12-10)
#define LM_MD_      (440+12)    
#define LM_MD_CHK_  (440+12+420)    
                                    
#define	LM2_EC		    LASTMON_DATA+SIZE_MONBLK*1      //440
#define LM2_ZZZZ        LM2_EC+440                      //12
#define	LM2_MD		    LM2_ZZZZ+12		                //422=420+2


//------  LM1_EC+LM1MD  ------------------------------------------------------
//#define	LM1_EC_Back1	 		LM1_EC					//162 active, reactive, apparent forward reverse total power quantity and tariff power quantity  (5*5+2)*3*2=162
#define	LM1_EC_Back1	 		LM1_EC					//162有功、无功、视在的正反向总电量和费时电量   (5*5+2)*3*2=162
//#define	LM1_EC_Back2 			LM1_EC_Back1+162        //102 active, reactive, apparent forward reverse split-phase total power quantity  (3*5+2)*3*2=102
#define	LM1_EC_Back2 			LM1_EC_Back1+162        //102有功、无功、视在的正反向分相总电量         (3*5+2)*3*2=102
//#define	LM1_EC_Back3 			LM1_EC_Back2+102        //88 reactive quadrant, split-phase reactive quadrant power quantity  (4*5+2)*(4)=88
#define	LM1_EC_Back3 			LM1_EC_Back2+102        //88无功象限、分相无功象限电量                  (4*5+2)*(4)=88
//#define	LM1_EC_Back4			LM1_EC_Back3+88			//88 reactive quadrant tariff power quantity    (4*5+2)*(4)=88
#define	LM1_EC_Back4			LM1_EC_Back3+88			//88无功象限费率电量						    (4*5+2)*(4)=88

 //E.C forward active
#define	LM1_EC_Pp0		    LM1_EC_Back1 + 27*0
#define	LM1_EC_Pp1		    LM1_EC_Pp0 +5
#define	LM1_EC_Pp2		    LM1_EC_Pp0 +10
#define	LM1_EC_Pp3		    LM1_EC_Pp0 +15
#define	LM1_EC_Pp4		    LM1_EC_Pp0 +20
#define	LM1_Chk_Pp		    LM1_EC_Pp0 +25
 //reverse active
#define LM1_EC_Pn0			LM1_EC_Back1 + 27*1
#define LM1_EC_Pn1			LM1_EC_Pn0 + 5
#define LM1_EC_Pn2  		LM1_EC_Pn0 + 10
#define LM1_EC_Pn3 			LM1_EC_Pn0 + 15
#define LM1_EC_Pn4 			LM1_EC_Pn0 + 20
#define LM1_Chk_Pn			LM1_EC_Pn0 + 25
 //forward reactive
#define LM1_EC_Rp0			LM1_EC_Back1 + 27*2
#define LM1_EC_Rp1 			LM1_EC_Rp0 + 5
#define LM1_EC_Rp2			LM1_EC_Rp0 + 10
#define LM1_EC_Rp3			LM1_EC_Rp0 + 15
#define LM1_EC_Rp4			LM1_EC_Rp0 + 20
#define LM1_Chk_Rp			LM1_EC_Rp0 + 25
 //reverse reactive
#define LM1_EC_Rn0			LM1_EC_Back1 + 27*3
#define LM1_EC_Rn1			LM1_EC_Rn0 + 5
#define LM1_EC_Rn2  		LM1_EC_Rn0 + 10
#define LM1_EC_Rn3			LM1_EC_Rn0 + 15
#define LM1_EC_Rn4			LM1_EC_Rn0 + 20
#define LM1_Chk_Rn			LM1_EC_Rn0 + 25
 //forward apparent
#define LM1_EC_Qp0			LM1_EC_Back1 + 27*4
#define LM1_EC_Qp1 			LM1_EC_Qp0 + 5
#define LM1_EC_Qp2			LM1_EC_Qp0 + 10
#define LM1_EC_QP3			LM1_EC_Qp0 + 15
#define LM1_EC_Qp4			LM1_EC_Qp0 + 20
#define LM1_Chk_Qp			LM1_EC_Qp0 + 25
 //reverse apparent
#define LM1_EC_Qn0			LM1_EC_Back1 + 27*5
#define LM1_EC_Qn1			LM1_EC_Qn0 + 5
#define LM1_EC_Qn2  		LM1_EC_Qn0 + 10
#define LM1_EC_Qn3			LM1_EC_Qn0 + 15
#define LM1_EC_Qn4			LM1_EC_Qn0 + 20
#define LM1_Chk_Qn			LM1_EC_Qn0 + 25

/**  EC_Back2  **/
 //active forward split-phase power quantity
#define	LM1_EC_PpL1         LM1_EC_Back2 + 17*0
#define	LM1_EC_PpL2			LM1_EC_PpL1 +5
#define	LM1_EC_PpL3			LM1_EC_PpL1 +10
#define	LM1_Chk_ECPpL       LM1_EC_PpL1 +15
 //active reverse split-phase power quantity
#define	LM1_EC_PnL1         LM1_EC_Back2 + 17*1
#define	LM1_EC_PnL2			LM1_EC_PnL1 +5
#define	LM1_EC_PnL3			LM1_EC_PnL1 +10
#define	LM1_Chk_ECPnL       LM1_EC_PnL1 +15
 //reactive forward split-phase power quantity
#define	LM1_EC_RpL1         LM1_EC_Back2 + 17*2
#define	LM1_EC_RpL2			LM1_EC_RpL1 +5
#define	LM1_EC_RpL3			LM1_EC_RpL1 +10
#define	LM1_Chk_ECRpL       LM1_EC_RpL1 +15
 //reactive reverse split-phase power quantity
#define	LM1_EC_RnL1         LM1_EC_Back2 + 17*3
#define	LM1_EC_RnL2			LM1_EC_RnL1 +5
#define	LM1_EC_RnL3			LM1_EC_RnL1 +10
#define	LM1_Chk_ECRnL       LM1_EC_RnL1 +15
 //apparent forward split-phase power quantity
#define	LM1_EC_QpL1         LM1_EC_Back2 + 17*4
#define	LM1_EC_QpL2			LM1_EC_QpL1 +5
#define	LM1_EC_QpL3			LM1_EC_QpL1 +10
#define	LM1_Chk_ECQpL       LM1_EC_QpL1 +15
 //apparent reverse split-phase power quantity
#define	LM1_EC_QnL1         LM1_EC_Back2 + 17*5
#define	LM1_EC_QnL2			LM1_EC_QnL1 +5
#define	LM1_EC_QnL3			LM1_EC_QnL1 +10
#define	LM1_Chk_ECQnL       LM1_EC_QnL1 +15

/**  EC_Back3  **/
 //reactive first quadrant and split-phase
#define LM1_EC_Rq1			LM1_EC_Back3 + 22*0
#define LM1_EC_Rq1L1		LM1_EC_Rq1 + 5
#define LM1_EC_Rq1L2		LM1_EC_Rq1 + 10
#define LM1_EC_Rq1L3		LM1_EC_Rq1 + 15
#define LM1_Chk_Rq1			LM1_EC_Rq1 + 20
 //reactive second quadrant and split-phase
#define LM1_EC_Rq2 			LM1_EC_Back3 + 22*1
#define LM1_EC_Rq2L1 		LM1_EC_Rq2 + 5
#define LM1_EC_Rq2L2		LM1_EC_Rq2 + 10
#define LM1_EC_Rq2L3		LM1_EC_Rq2 + 15
#define LM1_Chk_Rq2			LM1_EC_Rq2 + 20
 //reactive third quadrant and split-phase
#define LM1_EC_Rq3			LM1_EC_Back3 + 22*2
#define LM1_EC_Rq3L1 		LM1_EC_Rq3 + 5
#define LM1_EC_Rq3L2		LM1_EC_Rq3 + 10
#define LM1_EC_Rq3L3		LM1_EC_Rq3 + 15
#define LM1_Chk_Rq3			LM1_EC_Rq3 + 20
 //reactive four quadrant and split-phase
#define LM1_EC_Rq4			LM1_EC_Back3 + 22*3
#define LM1_EC_Rq4L1 		LM1_EC_Rq4 + 5
#define LM1_EC_Rq4L2		LM1_EC_Rq4 + 10
#define LM1_EC_Rq4L3		LM1_EC_Rq4 + 15
#define LM1_Chk_Rq4			LM1_EC_Rq4 + 20

 //reactive quadrant tariff power quantity 72
 //reactive first quadrant tariff power quantity 
#define	LM1_EC_Rq1F1		LM1_EC_Back4 + 22*0
#define	LM1_EC_Rq1F2		LM1_EC_Rq1F1 + 5
#define	LM1_EC_Rq1F3		LM1_EC_Rq1F1 + 10
#define	LM1_EC_Rq1F4		LM1_EC_Rq1F1 + 15
#define	LM1_Chk_RQ1F		LM1_EC_Rq1F1 + 20
 //reactive second tariff power quantity
#define	LM1_EC_Rq2F1		LM1_EC_Back4 + 22*1
#define	LM1_EC_Rq2F2		LM1_EC_Rq2F1 + 5
#define	LM1_EC_Rq2F3		LM1_EC_Rq2F1 + 10
#define	LM1_EC_Rq2F4		LM1_EC_Rq2F1 + 15
#define	LM1_Chk_RQ2F		LM1_EC_Rq2F1 + 20
 //reactive third quadrant tariff power quantity
#define	LM1_EC_Rq3F1		LM1_EC_Back4 + 22*2
#define	LM1_EC_Rq3F2		LM1_EC_Rq3F1 + 5
#define	LM1_EC_Rq3F3		LM1_EC_Rq3F1 + 10
#define	LM1_EC_Rq3F4		LM1_EC_Rq3F1 + 15
#define	LM1_Chk_RQ3F		LM1_EC_Rq3F1 + 20
 //reactive forth quadrant tariff power quantity
#define	LM1_EC_Rq4F1		LM1_EC_Back4 + 22*3
#define	LM1_EC_Rq4F2		LM1_EC_Rq4F1 + 5
#define	LM1_EC_Rq4F3		LM1_EC_Rq4F1 + 10
#define	LM1_EC_Rq4F4		LM1_EC_Rq4F1 + 15
#define	LM1_Chk_RQ4F		LM1_EC_Rq4F1 + 20

 //**active forward demand ** 42
#define	LM1_MD_Pp			LM1_MD +42*0
#define	LM1_MD_PpTme        LM1_MD_Pp +3
#define LM1_MD_PpF1			LM1_MD_Pp +8
#define	LM1_MD_PpF1Tme		LM1_MD_Pp +11
#define	LM1_MD_PpF2			LM1_MD_Pp +16
#define	LM1_MD_PpF2Tme		LM1_MD_Pp +19
#define	LM1_MD_PpF3			LM1_MD_Pp +24
#define	LM1_MD_PpF3Tme		LM1_MD_Pp +27
#define	LM1_MD_PpF4			LM1_MD_Pp +32
#define	LM1_MD_PpF4Tme		LM1_MD_Pp +35
#define	ChkLM1_MD_Pp        LM1_MD_Pp +40
 //**active reverse demand ** 42
#define	LM1_MD_Pn			LM1_MD +42*1
#define	LM1_MD_PnTme        LM1_MD_Pn +3
#define LM1_MD_PnF1			LM1_MD_Pn +8
#define	LM1_MD_PnF1Tme		LM1_MD_Pn +11
#define	LM1_MD_PnF2			LM1_MD_Pn +16
#define	LM1_MD_PnF2Tme		LM1_MD_Pn +19
#define	LM1_MD_PnF3			LM1_MD_Pn +24
#define	LM1_MD_PnF3Tme		LM1_MD_Pn +27
#define	LM1_MD_PnF4			LM1_MD_Pn +32
#define	LM1_MD_PnF4Tme		LM1_MD_Pn +35
#define	ChkLM1_MD_Pn        LM1_MD_Pn +40
 //**reactive forward demand ** 42
#define	LM1_MD_Qp			LM1_MD +42*2
#define	LM1_MD_QpTme        LM1_MD_Qp +3
#define LM1_MD_QpF1			LM1_MD_Qp +8
#define	LM1_MD_QpF1Tme		LM1_MD_Qp +11
#define	LM1_MD_QpF2			LM1_MD_Qp +16
#define	LM1_MD_QpF2Tme		LM1_MD_Qp +19
#define	LM1_MD_QpF3			LM1_MD_Qp +24
#define	LM1_MD_QpF3Tme		LM1_MD_Qp +27
#define	LM1_MD_QpF4			LM1_MD_Qp +32
#define	LM1_MD_QpF4Tme		LM1_MD_Qp +35
#define	ChkLM1_MD_Qp       	LM1_MD_Qp +40
 //**reactive reverse demand ** 42
#define	LM1_MD_Qn			LM1_MD +42*3
#define	LM1_MD_QnTme        LM1_MD_Qn +3
#define LM1_MD_QnF1			LM1_MD_Qn +8
#define	LM1_MD_QnF1Tme		LM1_MD_Qn +11
#define	LM1_MD_QnF2			LM1_MD_Qn +16
#define	LM1_MD_QnF2Tme		LM1_MD_Qn +19
#define	LM1_MD_QnF3			LM1_MD_Qn +24
#define	LM1_MD_QnF3Tme		LM1_MD_Qn +27
#define	LM1_MD_QnF4			LM1_MD_Qn +32
#define	LM1_MD_QnF4Tme		LM1_MD_Qn +35
#define	ChkLM1_MD_Qn        LM1_MD_Qn +42
 //**apparent forward demand ** 42
#define	LM1_MD_Rp			LM1_MD +42*4
#define	LM1_MD_RpTme        LM1_MD_Rp +3
#define LM1_MD_RpF1			LM1_MD_Rp +8
#define	LM1_MD_RpF1Tme		LM1_MD_Rp +11
#define	LM1_MD_RpF2			LM1_MD_Rp +16
#define	LM1_MD_RpF2Tme		LM1_MD_Rp +19
#define	LM1_MD_RpF3			LM1_MD_Rp +24
#define	LM1_MD_RpF3Tme		LM1_MD_Rp +27
#define	LM1_MD_RpF4			LM1_MD_Rp +32
#define	LM1_MD_RpF4Tme		LM1_MD_Rp +35
#define	ChkLM1_MD_Rp        LM1_MD_Rp +40
 //**apparent reverse demand ** 42
#define	LM1_MD_Rn			LM1_MD +42*5
#define	LM1_MD_RnTme        LM1_MD_Rn +3
#define LM1_MD_RnF1			LM1_MD_Rn +8
#define	LM1_MD_RnF1Tme		LM1_MD_Rn +11
#define	LM1_MD_RnF2			LM1_MD_Rn +16
#define	LM1_MD_RnF2Tme		LM1_MD_Rn +19
#define	LM1_MD_RnF3			LM1_MD_Rn +24
#define	LM1_MD_RnF3Tme		LM1_MD_Rn +27
#define	LM1_MD_RnF4			LM1_MD_Rn +32
#define	LM1_MD_RnF4Tme		LM1_MD_Rn +35
#define	ChkLM1_MD_Rn        LM1_MD_Rn +40

 //reactive four quadrants demand 168=42*4
#define	LM1_MD_Rq1			LM1_MD +42*6
#define	LM1_MD_Rq1Tme       LM1_MD_Rq1 +3
#define LM1_MD_Rq1F1		LM1_MD_Rq1 +8
#define	LM1_MD_Rq1F1Tme		LM1_MD_Rq1 +11
#define	LM1_MD_Rq1F2		LM1_MD_Rq1 +16
#define	LM1_MD_Rq1F2Tme		LM1_MD_Rq1 +19
#define	LM1_MD_Rq1F3		LM1_MD_Rq1 +24
#define	LM1_MD_Rq1F3Tme		LM1_MD_Rq1 +27
#define	LM1_MD_Rq1F4		LM1_MD_Rq1 +32
#define	LM1_MD_Rq1F4Tme		LM1_MD_Rq1 +35
#define	LM1_MD_Rq1_Chk		LM1_MD_Rq1 +40

#define	LM1_MD_Rq2			LM1_MD +42*7
#define	LM1_MD_Rq2Tme       LM1_MD_Rq2 +3
#define LM1_MD_Rq2F1		LM1_MD_Rq2 +8
#define	LM1_MD_Rq2F1Tme		LM1_MD_Rq2 +11
#define	LM1_MD_Rq2F2		LM1_MD_Rq2 +16
#define	LM1_MD_Rq2F2Tme		LM1_MD_Rq2 +19
#define	LM1_MD_Rq2F3		LM1_MD_Rq2 +24
#define	LM1_MD_Rq2F3Tme		LM1_MD_Rq2 +27
#define	LM1_MD_Rq2F4		LM1_MD_Rq2 +32
#define	LM1_MD_Rq2F4Tme		LM1_MD_Rq2 +35
#define	LM1_MD_Rq2_Chk		LM1_MD_Rq2 +40

#define	LM1_MD_Rq3			LM1_MD +42*8
#define	LM1_MD_Rq3Tme       LM1_MD_Rq3 +3
#define LM1_MD_Rq3F1		LM1_MD_Rq3 +8
#define	LM1_MD_Rq3F1Tme		LM1_MD_Rq3 +11
#define	LM1_MD_Rq3F2		LM1_MD_Rq3 +16
#define	LM1_MD_Rq3F2Tme		LM1_MD_Rq3 +19
#define	LM1_MD_Rq3F3		LM1_MD_Rq3 +24
#define	LM1_MD_Rq3F3Tme		LM1_MD_Rq3 +27
#define	LM1_MD_Rq3F4		LM1_MD_Rq3 +32
#define	LM1_MD_Rq3F4Tme		LM1_MD_Rq3 +35
#define	LM1_MD_Rq3_Chk		LM1_MD_Rq3 +40

#define	LM1_MD_Rq4			LM1_MD +42*9
#define	LM1_MD_Rq4Tme       LM1_MD_Rq4 +3
#define LM1_MD_Rq4F1		LM1_MD_Rq4 +8
#define	LM1_MD_Rq4F1Tme		LM1_MD_Rq4 +11
#define	LM1_MD_Rq4F2		LM1_MD_Rq4 +16
#define	LM1_MD_Rq4F2Tme		LM1_MD_Rq4 +19
#define	LM1_MD_Rq4F3		LM1_MD_Rq4 +24
#define	LM1_MD_Rq4F3Tme		LM1_MD_Rq4 +27
#define	LM1_MD_Rq4F4		LM1_MD_Rq4 +32
#define	LM1_MD_Rq4F4Tme		LM1_MD_Rq4 +35
#define	LM1_MD_Rq4_Chk		LM1_MD_Rq4 +40

//------ LM2_EC+LM2_MD  ------------------------------------------------------
//#define	LM2_EC_Back1	 		LM2_EC					//162 active, reactive, apparent forward reverse total power quantity and tariff power quantity (5*5+2)*3*2=162
#define	LM2_EC_Back1	 		LM2_EC					//162有功、无功、视在的正反向总电量和费时电量   (5*5+2)*3*2=162
//#define	LM2_EC_Back2 			LM2_EC_Back1+162        //102 active, reactive, apparent forward reverse split-phase total power quantity
#define	LM2_EC_Back2 			LM2_EC_Back1+162        //102有功、无功、视在的正反向分相总电量         (3*5+2)*3*2=102
//#define	LM2_EC_Back3 			LM2_EC_Back2+102        //88 reactive quadrant, split-phase reactive quadrant power quantity  (4*5+2)*(4)=88
#define	LM2_EC_Back3 			LM2_EC_Back2+102        //88无功象限、分相无功象限电量                  (4*5+2)*(4)=88
//#define	LM2_EC_Back4			LM2_EC_Back3+88			//88 reactive quadrant tariff power quantity
#define	LM2_EC_Back4			LM2_EC_Back3+88			//88无功象限费率电量

 //E.C forward active
#define	LM2_EC_Pp0		    LM2_EC_Back1 + 27*0
#define	LM2_EC_Pp1		    LM2_EC_Pp0 +5
#define	LM2_EC_Pp2		    LM2_EC_Pp0 +10
#define	LM2_EC_Pp3		    LM2_EC_Pp0 +15
#define	LM2_EC_Pp4		    LM2_EC_Pp0 +20
#define	LM2_Chk_Pp		    LM2_EC_Pp0 +25
 //reverse active
#define LM2_EC_Pn0			LM2_EC_Back1 + 27*1
#define LM2_EC_Pn1			LM2_EC_Pn0 + 5
#define LM2_EC_Pn2  		LM2_EC_Pn0 + 10
#define LM2_EC_Pn3 			LM2_EC_Pn0 + 15
#define LM2_EC_Pn4 			LM2_EC_Pn0 + 20
#define LM2_Chk_Pn			LM2_EC_Pn0 + 25
 //forward reactive
#define LM2_EC_Rp0			LM2_EC_Back1 + 27*2
#define LM2_EC_Rp1 			LM2_EC_Rp0 + 5
#define LM2_EC_Rp2			LM2_EC_Rp0 + 10
#define LM2_EC_Rp3			LM2_EC_Rp0 + 15
#define LM2_EC_Rp4			LM2_EC_Rp0 + 20
#define LM2_Chk_Rp			LM2_EC_Rp0 + 25
 //reverse reactive
#define LM2_EC_Rn0			LM2_EC_Back1 + 27*3
#define LM2_EC_Rn1			LM2_EC_Rn0 + 5
#define LM2_EC_Rn2  		LM2_EC_Rn0 + 10
#define LM2_EC_Rn3			LM2_EC_Rn0 + 15
#define LM2_EC_Rn4			LM2_EC_Rn0 + 20
#define LM2_Chk_Rn			LM2_EC_Rn0 + 25
 //forward apparent
#define LM2_EC_Qp0			LM2_EC_Back1 + 27*4
#define LM2_EC_Qp1 			LM2_EC_Qp0 + 5
#define LM2_EC_Qp2			LM2_EC_Qp0 + 10
#define LM2_EC_QP3			LM2_EC_Qp0 + 15
#define LM2_EC_Qp4			LM2_EC_Qp0 + 20
#define LM2_Chk_Qp			LM2_EC_Qp0 + 25
 //reverse apparent
#define LM2_EC_Qn0			LM2_EC_Back1 + 27*5
#define LM2_EC_Qn1			LM2_EC_Qn0 + 5
#define LM2_EC_Qn2  		LM2_EC_Qn0 + 10
#define LM2_EC_Qn3			LM2_EC_Qn0 + 15
#define LM2_EC_Qn4			LM2_EC_Qn0 + 20
#define LM2_Chk_Qn			LM2_EC_Qn0 + 25

/**  EC_Back2  **/
 //active forward split-phase power quantity
#define	LM2_EC_PpL1         LM2_EC_Back2 + 17*0
#define	LM2_EC_PpL2			LM2_EC_PpL1 +5
#define	LM2_EC_PpL3			LM2_EC_PpL1 +10
#define	LM2_Chk_ECPpL       LM2_EC_PpL1 +15
 //active reverse split-phase power quantity
#define	LM2_EC_PnL1         LM2_EC_Back2 + 17*1
#define	LM2_EC_PnL2			LM2_EC_PnL1 +5
#define	LM2_EC_PnL3			LM2_EC_PnL1 +10
#define	LM2_Chk_ECPnL       LM2_EC_PnL1 +15
 //reactive forward split-phase power quantity
#define	LM2_EC_RpL1         LM2_EC_Back2 + 17*2
#define	LM2_EC_RpL2			LM2_EC_RpL1 +5
#define	LM2_EC_RpL3			LM2_EC_RpL1 +10
#define	LM2_Chk_ECRpL       LM2_EC_RpL1 +15
 //reactive reverse split-phase power quantity
#define	LM2_EC_RnL1         LM2_EC_Back2 + 17*3
#define	LM2_EC_RnL2			LM2_EC_RnL1 +5
#define	LM2_EC_RnL3			LM2_EC_RnL1 +10
#define	LM2_Chk_ECRnL       LM2_EC_RnL1 +15
 //apparent forward split-phase power quantity
#define	LM2_EC_QpL1         LM2_EC_Back2 + 17*4
#define	LM2_EC_QpL2			LM2_EC_QpL1 +5
#define	LM2_EC_QpL3			LM2_EC_QpL1 +10
#define	LM2_Chk_ECQpL       LM2_EC_QpL1 +15
 //apparent reverse split-phase power quantity
#define	LM2_EC_QnL1         LM2_EC_Back2 + 17*5
#define	LM2_EC_QnL2			LM2_EC_QnL1 +5
#define	LM2_EC_QnL3			LM2_EC_QnL1 +10
#define	LM2_Chk_ECQnL       LM2_EC_QnL1 +15

/**  EC_Back3  **/
 //reactive first quadrant and split-phase
#define LM2_EC_Rq1			LM2_EC_Back3 + 22*0
#define LM2_EC_Rq1L1		LM2_EC_Rq1 + 5
#define LM2_EC_Rq1L2		LM2_EC_Rq1 + 10
#define LM2_EC_Rq1L3		LM2_EC_Rq1 + 15
#define LM2_Chk_Rq1			LM2_EC_Rq1 + 20
 //reactive second quadrant and split-phase
#define LM2_EC_Rq2 			LM2_EC_Back3 + 22*1
#define LM2_EC_Rq2L1 		LM2_EC_Rq2 + 5
#define LM2_EC_Rq2L2		LM2_EC_Rq2 + 10
#define LM2_EC_Rq2L3		LM2_EC_Rq2 + 15
#define LM2_Chk_Rq2			LM2_EC_Rq2 + 20
 //reactive third quadrant and split-phase
#define LM2_EC_Rq3			LM2_EC_Back3 + 22*2
#define LM2_EC_Rq3L1 		LM2_EC_Rq3 + 5
#define LM2_EC_Rq3L2		LM2_EC_Rq3 + 10
#define LM2_EC_Rq3L3		LM2_EC_Rq3 + 15
#define LM2_Chk_Rq3			LM2_EC_Rq3 + 20
 //reactive forth quadrant and split-phase
#define LM2_EC_Rq4			LM2_EC_Back3 + 22*3
#define LM2_EC_Rq4L1 		LM2_EC_Rq4 + 5
#define LM2_EC_Rq4L2		LM2_EC_Rq4 + 10
#define LM2_EC_Rq4L3		LM2_EC_Rq4 + 15
#define LM2_Chk_Rq4			LM2_EC_Rq4 + 20

 //reactive quadrant tariff power quantity 72
 //reactive first quadrant tariff power quantity
#define	LM2_EC_Rq1F1		LM2_EC_Back4 + 22*0
#define	LM2_EC_Rq1F2		LM2_EC_Rq1F1 + 5
#define	LM2_EC_Rq1F3		LM2_EC_Rq1F1 + 10
#define	LM2_EC_Rq1F4		LM2_EC_Rq1F1 + 15
#define	LM2_Chk_RQ1F		LM2_EC_Rq1F1 + 20
 //reactive second quadrant tariff power quantity
#define	LM2_EC_Rq2F1		LM2_EC_Back4 + 22*1
#define	LM2_EC_Rq2F2		LM2_EC_Rq2F1 + 5
#define	LM2_EC_Rq2F3		LM2_EC_Rq2F1 + 10
#define	LM2_EC_Rq2F4		LM2_EC_Rq2F1 + 15
#define	LM2_Chk_RQ2F		LM2_EC_Rq2F1 + 20
 //reactive third quadrant tariff power quantity
#define	LM2_EC_Rq3F1		LM2_EC_Back4 + 22*2
#define	LM2_EC_Rq3F2		LM2_EC_Rq3F1 + 5
#define	LM2_EC_Rq3F3		LM2_EC_Rq3F1 + 10
#define	LM2_EC_Rq3F4		LM2_EC_Rq3F1 + 15
#define	LM2_Chk_RQ3F		LM2_EC_Rq3F1 + 20
 //reactive forth quadrant tariff power quantity
#define	LM2_EC_Rq4F1		LM2_EC_Back4 + 22*3
#define	LM2_EC_Rq4F2		LM2_EC_Rq4F1 + 5
#define	LM2_EC_Rq4F3		LM2_EC_Rq4F1 + 10
#define	LM2_EC_Rq4F4		LM2_EC_Rq4F1 + 15
#define	LM2_Chk_RQ4F		LM2_EC_Rq4F1 + 20

 //**active forward demand** 42
#define	LM2_MD_Pp			LM2_MD +42*0
#define	LM2_MD_PpTme        LM2_MD_Pp +3
#define LM2_MD_PpF1			LM2_MD_Pp +8
#define	LM2_MD_PpF1Tme		LM2_MD_Pp +11
#define	LM2_MD_PpF2			LM2_MD_Pp +16
#define	LM2_MD_PpF2Tme		LM2_MD_Pp +19
#define	LM2_MD_PpF3			LM2_MD_Pp +24
#define	LM2_MD_PpF3Tme		LM2_MD_Pp +27
#define	LM2_MD_PpF4			LM2_MD_Pp +32
#define	LM2_MD_PpF4Tme		LM2_MD_Pp +35
#define	ChkLM2_MD_Pp        LM2_MD_Pp +40
 //**active reverse demand** 42
#define	LM2_MD_Pn			LM2_MD +42*1
#define	LM2_MD_PnTme        LM2_MD_Pn +3
#define LM2_MD_PnF1			LM2_MD_Pn +8
#define	LM2_MD_PnF1Tme		LM2_MD_Pn +11
#define	LM2_MD_PnF2			LM2_MD_Pn +16
#define	LM2_MD_PnF2Tme		LM2_MD_Pn +19
#define	LM2_MD_PnF3			LM2_MD_Pn +24
#define	LM2_MD_PnF3Tme		LM2_MD_Pn +27
#define	LM2_MD_PnF4			LM2_MD_Pn +32
#define	LM2_MD_PnF4Tme		LM2_MD_Pn +35
#define	ChkLM2_MD_Pn        LM2_MD_Pn +40
 //**reactive forward demand** 42
#define	LM2_MD_Qp			LM2_MD +42*2
#define	LM2_MD_QpTme        LM2_MD_Qp +3
#define LM2_MD_QpF1			LM2_MD_Qp +8
#define	LM2_MD_QpF1Tme		LM2_MD_Qp +11
#define	LM2_MD_QpF2			LM2_MD_Qp +16
#define	LM2_MD_QpF2Tme		LM2_MD_Qp +19
#define	LM2_MD_QpF3			LM2_MD_Qp +24
#define	LM2_MD_QpF3Tme		LM2_MD_Qp +27
#define	LM2_MD_QpF4			LM2_MD_Qp +32
#define	LM2_MD_QpF4Tme		LM2_MD_Qp +35
#define	ChkLM2_MD_Qp       	LM2_MD_Qp +40
 //**reactive reverse demand** 42
#define	LM2_MD_Qn			LM2_MD +42*3
#define	LM2_MD_QnTme        LM2_MD_Qn +3
#define LM2_MD_QnF1			LM2_MD_Qn +8
#define	LM2_MD_QnF1Tme		LM2_MD_Qn +11
#define	LM2_MD_QnF2			LM2_MD_Qn +16
#define	LM2_MD_QnF2Tme		LM2_MD_Qn +19
#define	LM2_MD_QnF3			LM2_MD_Qn +24
#define	LM2_MD_QnF3Tme		LM2_MD_Qn +27
#define	LM2_MD_QnF4			LM2_MD_Qn +32
#define	LM2_MD_QnF4Tme		LM2_MD_Qn +35
#define	ChkLM2_MD_Qn        LM2_MD_Qn +42
 //**apparent forward demand** 42
#define	LM2_MD_Rp			LM2_MD +42*4
#define	LM2_MD_RpTme        LM2_MD_Rp +3
#define LM2_MD_RpF1			LM2_MD_Rp +8
#define	LM2_MD_RpF1Tme		LM2_MD_Rp +11
#define	LM2_MD_RpF2			LM2_MD_Rp +16
#define	LM2_MD_RpF2Tme		LM2_MD_Rp +19
#define	LM2_MD_RpF3			LM2_MD_Rp +24
#define	LM2_MD_RpF3Tme		LM2_MD_Rp +27
#define	LM2_MD_RpF4			LM2_MD_Rp +32
#define	LM2_MD_RpF4Tme		LM2_MD_Rp +35
#define	ChkLM2_MD_Rp        LM2_MD_Rp +40
 //**apparent reverse demand** 42
#define	LM2_MD_Rn			LM2_MD +42*5
#define	LM2_MD_RnTme        LM2_MD_Rn +3
#define LM2_MD_RnF1			LM2_MD_Rn +8
#define	LM2_MD_RnF1Tme		LM2_MD_Rn +11
#define	LM2_MD_RnF2			LM2_MD_Rn +16
#define	LM2_MD_RnF2Tme		LM2_MD_Rn +19
#define	LM2_MD_RnF3			LM2_MD_Rn +24
#define	LM2_MD_RnF3Tme		LM2_MD_Rn +27
#define	LM2_MD_RnF4			LM2_MD_Rn +32
#define	LM2_MD_RnF4Tme		LM2_MD_Rn +35
#define	ChkLM2_MD_Rn        LM2_MD_Rn +40

 //reactive four quadrant demand  168=42*4
#define	LM2_MD_Rq1			LM2_MD +42*6
#define	LM2_MD_Rq1Tme       LM2_MD_Rq1 +3
#define LM2_MD_Rq1F1		LM2_MD_Rq1 +8
#define	LM2_MD_Rq1F1Tme		LM2_MD_Rq1 +11
#define	LM2_MD_Rq1F2		LM2_MD_Rq1 +16
#define	LM2_MD_Rq1F2Tme		LM2_MD_Rq1 +19
#define	LM2_MD_Rq1F3		LM2_MD_Rq1 +24
#define	LM2_MD_Rq1F3Tme		LM2_MD_Rq1 +27
#define	LM2_MD_Rq1F4		LM2_MD_Rq1 +32
#define	LM2_MD_Rq1F4Tme		LM2_MD_Rq1 +35
#define	LM2_MD_Rq1_Chk		LM2_MD_Rq1 +40

#define	LM2_MD_Rq2			LM2_MD +42*7
#define	LM2_MD_Rq2Tme       LM2_MD_Rq2 +3
#define LM2_MD_Rq2F1		LM2_MD_Rq2 +8
#define	LM2_MD_Rq2F1Tme		LM2_MD_Rq2 +11
#define	LM2_MD_Rq2F2		LM2_MD_Rq2 +16
#define	LM2_MD_Rq2F2Tme		LM2_MD_Rq2 +19
#define	LM2_MD_Rq2F3		LM2_MD_Rq2 +24
#define	LM2_MD_Rq2F3Tme		LM2_MD_Rq2 +27
#define	LM2_MD_Rq2F4		LM2_MD_Rq2 +32
#define	LM2_MD_Rq2F4Tme		LM2_MD_Rq2 +35
#define	LM2_MD_Rq2_Chk		LM2_MD_Rq2 +40

#define	LM2_MD_Rq3			LM2_MD +42*8
#define	LM2_MD_Rq3Tme       LM2_MD_Rq3 +3
#define LM2_MD_Rq3F1		LM2_MD_Rq3 +8
#define	LM2_MD_Rq3F1Tme		LM2_MD_Rq3 +11
#define	LM2_MD_Rq3F2		LM2_MD_Rq3 +16
#define	LM2_MD_Rq3F2Tme		LM2_MD_Rq3 +19
#define	LM2_MD_Rq3F3		LM2_MD_Rq3 +24
#define	LM2_MD_Rq3F3Tme		LM2_MD_Rq3 +27
#define	LM2_MD_Rq3F4		LM2_MD_Rq3 +32
#define	LM2_MD_Rq3F4Tme		LM2_MD_Rq3 +35
#define	LM2_MD_Rq3_Chk		LM2_MD_Rq3 +40

#define	LM2_MD_Rq4			LM2_MD +42*9
#define	LM2_MD_Rq4Tme       LM2_MD_Rq4 +3
#define LM2_MD_Rq4F1		LM2_MD_Rq4 +8
#define	LM2_MD_Rq4F1Tme		LM2_MD_Rq4 +11
#define	LM2_MD_Rq4F2		LM2_MD_Rq4 +16
#define	LM2_MD_Rq4F2Tme		LM2_MD_Rq4 +19
#define	LM2_MD_Rq4F3		LM2_MD_Rq4 +24
#define	LM2_MD_Rq4F3Tme		LM2_MD_Rq4 +27
#define	LM2_MD_Rq4F4		LM2_MD_Rq4 +32
#define	LM2_MD_Rq4F4Tme		LM2_MD_Rq4 +35
#define	LM2_MD_Rq4_Chk		LM2_MD_Rq4 +40

//======  LOAD CURVE ==========================================================

 //last byte wrong check bit
#define	D_TEST_OFS			0xfffff0

#endif









