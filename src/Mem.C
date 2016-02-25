#include "..\inc\includes.h"

#include "..\inc\Check.h"

#define	E2P_PAGE	32

//#include	"E2PROM.c"
/**********************************************************************
 Move Data from Memory to Memory(FRAM,EEPROM)
 **********************************************************************/
const unsigned long MemBakTab[] = { 0x00000000, // RAM
		0x00000000, // InfoFlash
		0x00000000, // Flash
		FRAMBAK, // FRAM
		E2P_BAK, // E2PROM
		FLS_MONDATA_BAK, // Data Flash
		};

/**********************************************************************
 Asm Subroutine
 Source File in Asms.s43
 **********************************************************************/
//extern int _E2P_Write( unsigned int E2P_Dest, char* RAM_Src, int Lenth );
/**********************************************************************
 Ð´ E2PROM
 **********************************************************************/
int E2P_Write(unsigned int E2P_Dest, char* RAM_Src, int Lenth) {

	E_Write(E2P_Dest, (int8u*) RAM_Src, Lenth);

	return 0;
}
/**********************************************************************
 //read E2PROM
 ¶Á E2PROM
 **********************************************************************/
int E2P_Read(char *Dest, unsigned int Src, int Lenth) {
	E_Read((int8u*) Dest, Src, Lenth);
	return 0;
}

/**********************************************************************
 //FRAM copy to E2PROM
 **********************************************************************/
void FRAMtoE2P(unsigned int E2PDest, unsigned int FRAMSrc, unsigned int Length) {
	int Len;

	while (Length > 0) {
		if (Length > MAX_BUF)
			Len = MAX_BUF;
		else
			Len = Length;
		FRAM_Read((char*) Buffer, FRAMSrc, Len);
		E2P_Write(E2PDest, (char*) Buffer, Len);
		E2PDest += Len;
		FRAMSrc += Len;
		Length -= Len;
	}
}
/**********************************************************************
 //FRAM copy to FLASH
 **********************************************************************/
void FRAM2Flash(unsigned long Dst, unsigned int FRAMSrc, unsigned int Cnt) {
	//int8u i;
	int16u uiLen;
	while (Cnt > 0) {
		if (Cnt > 64) {
			uiLen = 64;
		} else {
			uiLen = Cnt;
		}

		FRAM_Read((char*) Buffer, FRAMSrc, uiLen);
		DF_Write(Dst, (int8u*) Buffer, uiLen);

		FRAMSrc += uiLen;
		Dst += uiLen;
		Cnt -= uiLen;
	}
}
/**********************************************************************
 //write FLASH
 **********************************************************************/
void Flash_Write(int32u ulAdr, int8u *ucBuf, int16u uiLen) {
	DF_Write(ulAdr, ucBuf, uiLen);
}

/**********************************************************************
 //read FLASH
 **********************************************************************/
void Flash_Read(int8u *ucBuf, int32u ulAdr, int16u uiLen) {
	DF_Read(ucBuf, ulAdr, uiLen);
}

/**********************************************************************
 //write ferroelectric
 **********************************************************************/
int FRAM_Write(unsigned int Dest, char *Src, int Lenth) {
	FM_Write(Dest, (int8u*) Src, Lenth);
	return 0;
}
/**********************************************************************
 //read ferroelectric
 **********************************************************************/
int FRAM_Read(char *Dest, unsigned int Src, int Lenth) {
	FM_Read((int8u*) Dest, Src, Lenth);
	return 0;
}
/**********************************************************************
 //memory data write into storage
 **********************************************************************/
void MEM_Write(unsigned long Dest, char *Src, int Lenth, char MemType) {
	switch (MemType) {
	case Mem_RAM:
		memcpy((char*) (unsigned int) Dest, Src, Lenth);
		break;
	case Mem_FRAM:
		FRAM_Write(Dest, Src, Lenth);
		break;
	case Mem_E2PROM:
		E2P_Write(Dest, Src, Lenth);
		break;
	case Mem_DFlash:
		Flash_Write(Dest, (unsigned char*) Src, Lenth);
		break;
	default:
		break;
	}
}
/**********************************************************************
 //storage data read to memory
 **********************************************************************/
void MEM_Read(char *Dest, unsigned long Src, int Lenth, char MemType) {
	switch (MemType) {
	case Mem_RAM:
		memcpy(Dest, (char*) (unsigned int) Src, Lenth);
		break;
	case Mem_FRAM:
		FRAM_Read((char*) Dest, Src, Lenth);
		break;
	case Mem_E2PROM:
		E2P_Read((char*) Dest, Src, Lenth);
		break;
	case Mem_DFlash:
		Flash_Read((unsigned char*) Dest, Src, Lenth);
		break;
	default:
		break;
	}
}
/**********************************************************************
 Write and Backup the Data in Memory ( FRAM, EEPROM )
 **********************************************************************/
//notice: this function will call ChkMem, and ChkMem will change the whole situation. 32 bytes after variable
//use this function to save data of the Bufffer, and please note
//if, Buffer 110 bytes, the data after Buffer[78] will be changed
//if, Buffer 32 bytes, the data after  Buffer[0] will be changed
//notice: this function will inquire check table, if storage address is not included in any option data address and 
//check address, then data will not be saved

void MEM_DBWrite(unsigned long Dest, char *Src, unsigned int Lenth,
		char MemType) {
	unsigned int MemBak, Temp;
	char *ChkAddres;
	char *BLKAddres;
	unsigned int BlkLen;
	//#if 0	                          //if write meter calibration parameter area, there should be an ON in SW1 SW2
#if 0
	if ((MemType == Mem_FRAM) && (Dest <(Adj_Para+128)) )
	{
		if ( (P2IN & P_SW) != 0x00 )
		return;
	}
#endif	
	//Temp = GetChkPtr( (char*)(unsigned int)Dest, MemType );   //acquire position that save data in the check table
	Temp = GetChkPtr((char*) (unsigned int) Dest, MemType); //
	if (Temp == (0xFFFF))
		return;
	//BlkLen = ChkTab[Temp].Lenth;		//acquire length of the need-to-be checked length block
	BlkLen = ChkTab[Temp].Lenth; //
	//BLKAddres = ChkTab[Temp].BlkAddr;	//acquire initial address of check block
	BLKAddres = ChkTab[Temp].BlkAddr; //
	//ChkAddres = BLKAddres + BlkLen;	//acquire store address of check code
	ChkAddres = BLKAddres + BlkLen; //
	MemBak = MemBakTab[MemType];

#ifdef DEBUGING
	if ((Dest+Lenth) > ((unsigned int)BLKAddres+BlkLen))
	while (1)
	WDTClr();
#endif

	//MEM_Write( Dest, Src, Lenth, MemType );	                            //write in data in main session
	MEM_Write(Dest, Src, Lenth, MemType); //
	//Temp = ChkMem( (unsigned long)BLKAddres, BlkLen, MemType );		    //calculate check code
	Temp = ChkMem((unsigned long) BLKAddres, BlkLen, MemType); //
	//Temp = ChkNum( Src, Lenth);
	//MEM_Write( (unsigned long)ChkAddres, (char*)&Temp, 2, MemType );	//write check code
	MEM_Write((unsigned long) ChkAddres, (char*) &Temp, 2, MemType); //
	if (MemBak != 0) {
		//MEM_Write( (unsigned long)Dest+MemBak, Src, Lenth, MemType );	            //write in data in backup area
		MEM_Write((unsigned long) Dest + MemBak, Src, Lenth, MemType); //
		//MEM_Write( (unsigned long)ChkAddres+MemBak, (char*)&Temp, 2, MemType );     //write in check code in backup area
		MEM_Write((unsigned long) ChkAddres + MemBak, (char*) &Temp, 2, MemType); //
	}
}
/**********************************************************************
 //srorage data transfer to storage
 **********************************************************************/
void MEM_MEM(unsigned long Dest, unsigned long Src, int Lenth, char Mode) {
	int Size;

	while (Lenth > 0) {
		if (Lenth > MAX_BUF)
			Size = MAX_BUF;
		else
			Size = Lenth;

		/*MEM_Read( (char*)&Buffer, Src, Size, (Mode>>4)&0x0F ); 
		 MEM_Write( Dest, (char*)&Buffer, Size, Mode&0x0F ); */

		MEM_Read((char*) Buffer, Src, Size, Mode);
		MEM_Write(Dest, (char*) Buffer, Size, Mode);
		Dest += Size;
		Src += Size;
		Lenth -= Size;
	}
}
/**********************************************************************
 //zero clearing
 **********************************************************************/
void MEM_Clr(unsigned long Dest, int Lenth, char MemType) {
	int Size;

	memset((char*) &Buffer[0], 0x00, MAX_BUF);

	while (Lenth > 0) {
		if (Lenth > MAX_BUF)
			Size = MAX_BUF;
		else
			Size = Lenth;

		MEM_Write(Dest, (char*) &Buffer, Size, MemType);

		Dest += Size;
		Lenth -= Size;

		//add in check code at the end
		if ((Lenth == 0) && (Buffer[0] == 0) && (Buffer[1] == 0)) {
			Lenth = 2;
			Buffer[0] = (char) CHECKWORD;
			Buffer[1] = (char) (CHECKWORD >> 8);
		}
	}
}
/*****************************************************************************/
