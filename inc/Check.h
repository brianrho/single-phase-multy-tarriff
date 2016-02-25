#ifndef		_CHECK_H
#define		_CHECK_H

#define	CHECKWORD			0xA55A

/*******************************************************************
	      Check Table Structure Define
*******************************************************************/
      /**1110 0000**/
#define     Chk_			0xE0
#define     Chk_RAM			0x20*Mem_RAM
#define     Chk_IFlash		0x20*Mem_IFlash
#define     Chk_Flash		0x20*Mem_Flash
#define     Chk_FRAM		0x20*Mem_FRAM
#define     Chk_E2PROM		0x20*Mem_E2PROM
#define     Chk_DFlash		0x20*Mem_DFlash
      /**0001 1000**/
#define		Comm_			0x18
#define		Comm_Clr		0x08
      /**0001 1111**/
#define 	Init_           0x07
#define 	Init_para1		0x01
#define 	Init_FRAMClk	0x02
#define 	Init_AdjClk		0x03
#define 	Init_Clr		0x04
#define 	Init_RAMClk		0x05
#define 	Init_RAMFlg     0x06

/*******************************************************************
	      Check Table Structure Define
*******************************************************************/
#define 	CHK_RTC         0X10
#define 	CHK_ClkAdj      0X20
#define 	CHK_Puls        0x30
 
typedef struct
{
	char 		       *BlkAddr;          // Block Data Address
	unsigned int		Lenth;            // Block Lenth
  	char				Type;             // Type of Memory
} CHECKTAB;

typedef struct
{
//const char *src_addr;//source data address
const char *src_addr;//源数据地址
//unsigned int dec_addr;//target address
unsigned int dec_addr;//目标地址
//short type;//types of target
short type;//目标类型
//unsigned char len;//data length
unsigned char len;//数据长度
} DEF_PARA;

#define         ChkTabNum		sizeof(ChkTab)/sizeof(CHECKTAB)
#define			CHK_TAB_NUM		(80-13)//80///69
extern const    CHECKTAB        ChkTab[CHK_TAB_NUM];


int ChkNum( char *Ptr, int Len );

 ////-----CHKType define----------------
//-----CHKType 定义----------------
 //same with Check Memory Type definition
//--同Check Memory Type定义
 //--CHKType==0xFFFF represents all checked, or only checked specific Memory Type data
//--CHKType==0xFFFF 表示全部校验,否则只校验指定的Memory Type的数据
#define Chk_ALLMemory   0xFFFF
void MemCheck(unsigned int CHKType);

unsigned int GetChkPtr( char* Addr, char MemType );
int ChkMem( unsigned long Ptr, int Lenth, char MemType );
void ClearData(void);
void FirstBurn(void);
extern void checkClock(void);

extern void MEM_DBClear(unsigned char CommClear);


#endif