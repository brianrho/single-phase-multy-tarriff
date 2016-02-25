/******************************************************************************
//Measure.c-counting process programme

 * Measure.c - �����������
 * 
 * Copyright Hangzhou East Smart Technology Co.,Ltd.
 * 
 * DESCRIPTION: - 
 *      
 * modification history
 * --------------------
 * 01a, 07feb2011,  written
 * --------------------
 ******************************************************************************/
/***********************************************/
// Measure registers
#define	EPp		0
#define	EPn		1

// E.C. Measure Mode
#define	EF0	0x10
#define	EF1	0x01
#define	EF2	0x02
#define	EF3	0x04
#define	EF4	0x08
	
// Meter Const
typedef struct
{
	BCD3 MetConstP;
   	unsigned long 	Pimp;
   	unsigned int 	Per;
} FACT_T;

typedef struct
{
       //char 	MaxT;					//maximum demand period
	char 	MaxT;					//�����������
	//char 	MaxDT;				    //sliding period
	char 	MaxDT;				    //��������
	//int     RLoadVT;				//active forward load limitation  XX.XX kW
	int     RLoadVT;				//�й����򸺺����� XX.XX kW
	char    RMD_Flg;
}P_MD1_T;

//240 (720)
typedef	struct
{
	//40
	unsigned long	D_Qp_Cumu;
	unsigned long	D_Qn_Cumu;
	//unsigned long	D_Pp_Cumu;	//count period power quantity, accumulate every second integral, accumulate impulse number
	unsigned long	D_Pp_Cumu;	//�������ڵĵ����ۻ� ÿ����� �ۼ�������
	unsigned long	D_Pn_Cumu;
	unsigned long	D_Rp_Cumu;
	unsigned long	D_Rn_Cumu;
	unsigned long	D_Qdr_Cumu[4];
	
	//300
	unsigned int	D_Qp_Slide[2];
	unsigned int	D_Qn_Slide[2];
	//unsigned int	D_Pp_Slide[2];	//15 sliding register
	unsigned int	D_Pp_Slide[2];	//15������Ĵ���
	unsigned int	D_Pn_Slide[2];	
	unsigned int	D_Rp_Slide[2];
	unsigned int	D_Rn_Slide[2];
	unsigned int	D_Qdr_Slide[4][2];
	
	//10
	//char 	SldStartID;		//current sliding register index
	char 	SldStartID;		//��ǰʹ�õĻ���Ĵ�������
	//char	SlideNum;		//sliding register number
	char	SlideNum;		//����Ĵ���ʹ�ø���
	//unsigned int SlidingT;	//sliding time period
	unsigned int SlidingT;	//����ʱ�� ����
	//unsigned int DemandT;	//demand settlement period
	unsigned int DemandT;	//������������
	//unsigned int SlidingTm;	//sliding time reduction
	unsigned int SlidingTm;	//����ʱ�����ʱ
	int		MDchk;	
}MAXDEMAND_T;

#define MAXDEMAND_LEN (sizeof(MAXDEMAND_T))


typedef struct 
{
      //unsigned char	FeeCnt;	//before tariff switch, no switch of the last sliding register index =0xFF
	unsigned char	FeeCnt;	//
}MDFEESW_T;

typedef struct
{
	unsigned int 	MDAddr;			// EEPROM Demand Relative Address
  	unsigned char	RegPtr;			// Ecnt Register Point
  	unsigned char	Mode;           // Fee Mode
} MDMTAB_T;

//extern const FACT 	Fact;

void ECMeas(void);
void MDMeas(void);
void MDReset(void);
void ABCMeas(void);

void MDCumuCalc(CLK_T *pt_clk);
void MDParaInit(void);

void PulseClear(void);
void PulseBackUp(void);
void PulseRestore(void);

void MDCumuClear(void);
void MDCumuBackUp(void);
void MDCumuRestore(void);
void EC_1Min_Clear(void);


void pcut_md_save(void);
void pon_md_read(void);

void CustomRegister(void);



