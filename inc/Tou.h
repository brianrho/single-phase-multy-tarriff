#ifndef 	_TOU_H
#define		_TOU_H
//	Clock Timer Variable
typedef struct
{
	char	Sec_64;	
	BCD1 	Sec;
	BCD1 	Min;
	BCD1 	Hour;	
	BCD1 	Day;
	BCD1 	Mon;
	BCD1 	Year;
	BCD1	Week;
	int		Check;    
//} CLK_T;	//time
} CLK_T;	//
//--------------------add by bnthang-----------
#ifdef BNTHANG
typedef struct
{
	char number_open;
	char no_new_open;
	CLK_T time;
}time_open;
#endif
//----------------------------------------------
typedef struct
{
    unsigned long   CorrectGene;
    signed long     CorrectGeneBK;

//}CLKCORRECT;//clock factor
}CLKCORRECT;//时钟英子

//extern	unsigned int  gRTCOutCnt;//simulate clock output
extern	unsigned int  gRTCOutCnt;//模拟时钟输出

void Init_CLK_Gene(void);
void Clock(void);
char GetFeeNum( void );
char DayTableCHG(void);
void Time_TH(void);

extern	int8u GetBillAdr(int8u id,int16u da,int8u Type,int32u *pAddr,int16u *Info);

extern unsigned int GetGmDay( char  * Addr );
extern unsigned long GetGmMin( char  * Addr );
extern unsigned long GetGmSec( char  * Addr );
extern unsigned char GetWeek( char  * BCDDay );
extern void Min_Date( char  * Sec, unsigned long Min );

extern unsigned char CheckBill(void);
extern unsigned char AutoSaveTime(void);

#endif


