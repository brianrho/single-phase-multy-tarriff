
#define	Mem_RAM                  0
#define	Mem_IFlash               1
#define	Mem_Flash                2
#define	Mem_FRAM                 3
#define	Mem_E2PROM               4
#define	Mem_DFlash               5

#define	FRAM_E2P        Mem_FRAM*0x10 +Mem_E2PROM
#define	FRAM_FRAM       Mem_FRAM*0x10 +Mem_FRAM
#define	FRAM_DFls       Mem_FRAM*0x10 +Mem_DFlash
#define	E2P_E2P         Mem_E2PROM*0x10 +Mem_E2PROM
#define	E2P_DFls    	Mem_E2PROM*0x10 +Mem_DFlash

void FRAM2Flash(unsigned long Dst, unsigned int FRAMSrc, unsigned int Cnt);

void Flash_Write(int32u ulAdr,int8u *ucBuf,int16u uiLen);

void DF_Write(int32u ulAdr,int8u *ucBuf,int16u uiLen);

extern int _E2P_Write( unsigned int Dest, char *Src, int Lenth );
extern int E2P_Read( char *Dest, unsigned int Src, int Lenth );

extern int FRAM_Write( unsigned int Dest, char *Src, int Lenth );
extern int FRAM_Read( char *Dest, unsigned int Src, int Lenth );

void Flash_Read(int8u *ucBuf,int32u ulAdr,int16u uiLen);
void Flash_Read(int8u *ucBuf,int32u ulAdr,int16u uiLen);

int E2P_Write( unsigned int Dest, char *Src, int Lenth );


void FRAMtoE2P(unsigned int E2PDest, unsigned int FRAMSrc, unsigned int Length);
void MEM_MEM( unsigned long Dest, unsigned long Src, int Lenth, char MemType );
//void MEM_ChkBack( char* Addr, char MemType );
void MEM_Write( unsigned long Dest, char *Src, int Lenth,char MemType );
void MEM_Read( char *Dest, unsigned long Src, int Lenth,char MemType );
void MEM_DBWrite( unsigned long Dest, char *Src, unsigned int Lenth, char MemType );
void MEM_Clr( unsigned long Dest, int Lenth, char MemType );
extern	const unsigned long MemBakTab[6];
