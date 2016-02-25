#ifndef __LOADCURVE_H
#define __LOADCURVE_H
#define	LP_MaxChNum			1//8
#define	LP_MaxRegNum		34

/* Time Stamp */
typedef struct
{
	BCD1 	Year;
   	BCD1 	Mon;
   	BCD1 	Day;
   	BCD1 	Hour;
	BCD1 	Min;
   	BCD1 	Sec;
} YMDhmsL;

// Load profile Unit for Record
typedef struct
{
//record time
	YMDhmsL	    	RecTime;			//
	//data
	BCD5            Data[7];			//
} LOADUNIT;

typedef struct
{
//data length
	unsigned char	CommLen;			//
	//data numbers
	unsigned char	CommNUM;			//
} LOADLEN;

typedef struct
{
//register
	unsigned char   	*Register;//
	//length
	unsigned char       RegLen;//
	//type
	unsigned char		RegType;//
} LOADREG;


// Load Profile Channel Define
typedef struct
{
//data block first address 
	unsigned long		RecAddr;		//
	//record time intervals(Min)
	unsigned int	    TimeInv;		//
	//maximum record munber
	unsigned int	    MaxRecNum;	    //
	//number of register
	unsigned char       RegNum;		    //
	//data register code
	unsigned char       RegCode[7];	    //
} LOADINFO;
// Load profile Unit for Manage
typedef struct
{
//current read start pointer(pointer of item number)
	unsigned int	    ReadPtr;		//
	//number of record items
	unsigned int	    RecNum;		    //
	//the last time record pointer
	unsigned int	    RecPtr;		    //
} LOADINFORUN;

#define	SIZE_LoadINFO		(unsigned int)sizeof(LOADINFO)		// 16
#define	SIZE_LoadINFORUN	(unsigned int)sizeof(LOADINFORUN) 	// 6
#define	LP_ReadPtr		0		// int
#define	LP_RecNum		2		// int
#define	LP_RecPtr		4		// int

#define	LP_RecAddrOF	0
#define	LP_TimeInvOF	4
#define	LP_MaxRecNumOF	6
#define	LP_RegNumOF		8
#define	LP_RegCodeOF	9

extern unsigned int LoadPro_Read(unsigned char *Dest, unsigned char Ch );
void LoadPro_Rec( char Ch ,CLK_T *pt_clk);




#endif

