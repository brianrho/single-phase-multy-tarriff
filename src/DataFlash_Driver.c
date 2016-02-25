/**************************************************************************
       //document type:DataFlash-Driver.c
       //document function:DTATFLASH driver programme:MX25L6445E
       //change permissions:
       //document association:

	//founder:
	//creation date:
	//current version:

	//version information:
	

       //introduction:firmware condition: CPU MSP43F448
       //software condition:IAR4.20

//operation introduction:SPI bus, 8M Byte, BLOCK=64k total 128PCS:Secor=4K, 16 each Secor, PAGE=256, each Secor includes 64
操作说明：SPI总线，8M Byte,BLOCK=64k共128块 :Secor=4K,每块有16个Secor,PAGE=256,每个Secor包含64
             //characteristic:whole-chip erase, piece erase, sectors erase, page programme, 
             STATE structure: bit7:SRWD,bi6:QE,bit5: BP3,bit4:BP2,bit3:BP1,bit2:BP2,bit1:BP1:bit0:WIP
             protection mode can be divided into firmware protection mode and software protection mode, QE=1:software mode, WP protection is effective, BP2~BP0 protection is ineffective, QE=0;WP ineffective, P2~BP0 effective
             SRWD place, combined with WP, SRWD=1&&WP=0,write inhibit

**************************************************************************/
#include "..\inc\includes.h"


//#define	STATE_SRWD	0x80		//reading and writing enable
#define	STATE_SRWD	0x80		//读写使能
//#define	STATE_WIP	0x01		//1:write operation
#define	STATE_WIP	0x01		//1:写操作
//#define	STATE_WEL	0x02		//1:write enable
#define	STATE_WEL	0x02		//1:写使能，
//#define	STATE_QE	0x40		//1:four times operation enable
#define	STATE_QE	0x40		//1:4倍操作使能
#define	STSTE_BP0	0x02
#define	STSTE_BP1	0x04
#define	STSTE_BP2	0x10
#define	STSTE_BP3	0x20


#define		D_PAGE_CAP	512


#define		ON		1
#define		OFF		0
//*****************************************************************
 //delay programme
//*****************************************************************
void DF_DelayMs(int8u ucTime)
{
	int16u i;
	
	for(;ucTime>0;ucTime--)
	{
		for(i=0;i<1000;i++);
	}

}


//*****************************************************************
 //DATAFLASH write statement
//*****************************************************************
void DF_WriteState(int8u State)
{
	
	SPI_CS(SPI_FLASH);

	SPI_WByte(0x01);
	
	SPI_WByte(State);

	SPI_CS(SPI_NULL);

}
//*****************************************************************
 //DATAFLASH read statement
//*****************************************************************
int8u DF_ReadState(void)
{
	int8u ucCmd;
	
	SPI_CS(SPI_FLASH);


	SPI_WByte(0x05);
	
	ucCmd=SPI_Read();

	SPI_CS(SPI_NULL);

	return ucCmd;

}
//*****************************************************************
 //read DATAFLASH ID number
//*****************************************************************
void DF_ReadID(int8u *buf)
{

	
	SPI_POWON(ON,FLASH_POW);
	
	SPI_CS(SPI_FLASH);

	SPI_WByte(0x9f);
	*buf++=SPI_Read();
	*buf++=SPI_Read();
	*buf++=SPI_Read();

	SPI_CS(SPI_NULL);

	SPI_POWON(OFF,FLASH_POW);
}

//*****************************************************************
 //DATAFLASH read data
//*****************************************************************
void _DF_ReadData(int8u *ucBuf,int32u ulAdr, int16u uiLen)
{
	int8u ucTmp;
	
	SPI_CS(SPI_FLASH);

	SPI_WByte(0x03);
        //send address
	//发送地址
	ucTmp=(char)(ulAdr>>16);
	SPI_WByte(ucTmp);
	ucTmp=(char)(ulAdr>>8);
	SPI_WByte(ucTmp);
	ucTmp=(char)(ulAdr);
	SPI_WByte(ucTmp);

	for(;uiLen>0;uiLen--)
	{
		*ucBuf++=SPI_Read();
	}

	SPI_CS(SPI_NULL);
	
}
	
//#define	DF_WREN		0x06		//write enable
#define	DF_WREN		0x06		//写使能
//#define	DF_WRDI		0x04		//write inhibit
#define	DF_WRDI		0x04		//写禁止
//*****************************************************************
 //DATAFLASH write command
//*****************************************************************
//void DF_WriteCmd(int8u Cmd)		//write enable
void DF_WriteCmd(int8u Cmd)		//写使能
{


	SPI_CS(SPI_FLASH);

	SPI_WByte(Cmd);

	SPI_CS(SPI_NULL);

}
//*****************************************************************
 //waite DATAFLASH free
//*****************************************************************
void DF_WaiteBusy(void)
{
	int8u Tiv;
	
	while (DF_ReadState()&STATE_WIP)
	{
		DF_DelayMs(1);//1MS
		Tiv++;
		if(Tiv>100)
		{
			_NOP();
			break;
		}
	}
}
//*****************************************************************
 //DATAFLASH erase
//*****************************************************************
void DF_EraseSec(int32u Addr)
{

	int8u	ucTmp=0;
	ucTmp=ucTmp;
//	SPI_POWON(ON);
	DF_WaiteBusy();
	
	DF_WriteCmd(DF_WREN);
	
	SPI_CS(SPI_FLASH);

	//SPI_WByte(DF_WREN);
	
	SPI_WByte(0x20);

	ucTmp=(char)(Addr>>16);
	SPI_WByte(ucTmp);

	ucTmp=(char)(Addr>>8);
	SPI_WByte(ucTmp);

	ucTmp=(char)Addr;
	SPI_WByte(ucTmp);

	SPI_CS(SPI_NULL);

	DF_WaiteBusy();
//	SPI_POWON(OFF);

}
//*****************************************************************
 //DATAFLASH write data
//*****************************************************************
void _DF_Write(int32u ulAdr,int8u *ucBuf,int16u uiLen)
{
	int8u ucTmp;

	
	DF_WaiteBusy();
	
	DF_WriteCmd(DF_WREN);
	
	SPI_CS(SPI_FLASH);

	SPI_WByte(0x02);
        //send address
	//发送地址
	ucTmp=(char)(ulAdr>>16);
	SPI_WByte(ucTmp);
	ucTmp=(char)(ulAdr>>8);
	SPI_WByte(ucTmp);
	ucTmp=(char)(ulAdr);
	SPI_WByte(ucTmp);

	for(;uiLen>0;uiLen--)
	{
		SPI_WByte(*ucBuf);
		ucBuf++;
	}
	
	SPI_CS(SPI_NULL);

}


//*****************************************************************
 //DATAFLASH write page
//*****************************************************************
void _DF_WritePage(int32u ulPage,int8u *ucBuf,int16u uiLen)
{
	
	uiLen=uiLen;
	
	ulPage<<=12;					//*8,
	ulPage&=0xfffff000;

	
	DF_EraseSec(ulPage);		
		
	DF_ReadState();
	
      //_DF_Write(ulPage,ucBuf,256);	//read dataa of one page 
	_DF_Write(ulPage,ucBuf,256);	//读取一页数据
	
	
       //ulPage+=0x100;					//data of the sector, second page 
	ulPage+=0x100;					//扇区的第二页数据
	
      //_DF_Write(ulPage,ucBuf+256,256);	//read one page data
	_DF_Write(ulPage,ucBuf+256,256);	//读取一页数据

}
//*****************************************************************
 //DATAFLASH read page data
//*****************************************************************
void _DF_ReadPage(int8u *ucBuf,int32u ulPage,int16u uiLen)
{
	
	
	uiLen=uiLen;
	
	ulPage<<=12;					//*8,
	ulPage&=0xfffff000;

      //_DF_ReadData(ucBuf,ulPage,uiLen);	//read  one page data
	_DF_ReadData(ucBuf,ulPage,uiLen);	//读取一页数据
	
}
//*****************************************************************
 //DATAFLASH write data
//*****************************************************************
void DF_Write(int32u ulAdr,int8u *ucBuf,int16u uiLen)
{
	int32u Paddr;

	int16u Baddr;
	int16u  Cnt2;

	int8u Buf[D_PAGE_CAP];

	
	SPI_POWON(ON,FLASH_POW);

      //Paddr = ulAdr/D_PAGE_CAP;													//acquire page number of the corresponding page
	Paddr = ulAdr/D_PAGE_CAP;													//得到该地址对应的页码
      //Baddr = ulAdr-Paddr*D_PAGE_CAP;											//acquire bytes number of the corresponding page
	Baddr = ulAdr-Paddr*D_PAGE_CAP;											//得到该地址下对应页码的字节数
	_DF_ReadPage(Buf,Paddr, D_PAGE_CAP);
	while (uiLen>0)
	{
             //Cnt2 = D_PAGE_CAP-Baddr;												//the remaining bytes number of the page
		Cnt2 = D_PAGE_CAP-Baddr;												//该页剩下的字节数
		if (uiLen<Cnt2) 
		{
			Cnt2 = uiLen;
		}
		memcpy(&Buf[Baddr],ucBuf,Cnt2);
		Baddr += Cnt2;
		ucBuf   += Cnt2;
             //uiLen   -= Cnt2;													//write the remaining bytes number of the page
		uiLen   -= Cnt2;													//写完该页后剩下的字节数

              //if ((Baddr>=D_PAGE_CAP) && (uiLen>0))									//execute writing page turning 
		if ((Baddr>=D_PAGE_CAP) && (uiLen>0))									//执行翻页写
		{
                    //_DF_WritePage(Paddr, Buf, D_PAGE_CAP);									//modify buffer data 
			_DF_WritePage(Paddr, Buf, D_PAGE_CAP);									//修改缓存中的数据
			Baddr -= D_PAGE_CAP;
			Paddr += 1;
			DF_WaiteBusy();
			_DF_ReadPage(Buf, Paddr, D_PAGE_CAP);
		}
	}
       //_DF_WritePage(Paddr,Buf,D_PAGE_CAP);									//modify buffer data
	_DF_WritePage(Paddr,Buf,D_PAGE_CAP);									//修改缓存中的数据

	DF_WaiteBusy();	

	SPI_POWON(OFF,FLASH_POW);
	
}

//*****************************************************************
 //read one page
//*****************************************************************
void _DF_ReadRand(int8u *ucBuf,int32u ulPage,int16u uiOfs,int16u uiLen)
{
	
	uiLen=uiLen;
	
	ulPage<<=12;						//*8,
	ulPage&=0xfffff000;
	
	ulPage+=uiOfs;
	
      //_DF_ReadData(ucBuf,ulPage,uiLen);	//read one page data
	_DF_ReadData(ucBuf,ulPage,uiLen);	//读取一页数据
	
}

//*****************************************************************
 //DATAFLASH reading
//*****************************************************************
void DF_Read(int8u *ucBuf,int32u ulAdr,int16u uiLen)
{

	unsigned int Paddr;
	unsigned int Baddr;
	unsigned int Cnt2;


	
	SPI_POWON(ON,FLASH_POW);
	
       //Paddr = ulAdr/D_PAGE_CAP;													//acquire page number of the page
	Paddr = ulAdr/D_PAGE_CAP;													//得到该地址对应的页码
	Baddr = ulAdr-Paddr*D_PAGE_CAP;

	while(uiLen>0)
	{
              //Cnt2 = D_PAGE_CAP-Baddr;												//the bytes number of the page
		Cnt2 = D_PAGE_CAP-Baddr;												//该页剩下的字节数

		if (uiLen<Cnt2) 
		{
			Cnt2=uiLen;
		}

		DF_WaiteBusy();

		_DF_ReadRand(ucBuf, Paddr,Baddr,Cnt2);
		//memcpy(ucBuf,&Buf[Baddr],Cnt2);
		
		Baddr += Cnt2;
		ucBuf   += Cnt2;
		uiLen   -= Cnt2;													//写完该页后剩下的字节数

             //if ((Baddr>=D_PAGE_CAP) && (uiLen>0))									//execute writing page turning
		if ((Baddr>=D_PAGE_CAP) && (uiLen>0))									//执行翻页写
		{
			Baddr -= D_PAGE_CAP;
			Paddr += 1;
		}
	}

	DF_WaiteBusy();

	SPI_POWON(OFF,FLASH_POW);
}

//*****************************************************************
 //chip check
//*****************************************************************
void DF_Check(void)
{
	int8u ucBuf[2],ucBufBak[2];

	int8u i;
	
	ucBuf[0]=0x5a;
	ucBuf[1]=0xa5;

	for(i=0;i<3;i++)
	{
		DF_Write(D_TEST_OFS,ucBuf,2);
		memset(ucBufBak,0,2);
		DF_Read(ucBufBak,D_TEST_OFS,2);
		
		if(memcmp(ucBuf,ucBufBak,2)==0)
		{
			break;

		}
	}

	if(i==3)
	{

		gHardErr|=ERR_DFLASH_F;
	}
	else
	{
		gHardErr&=~ERR_DFLASH_F;
	}

	
}

//*****************************************************************
 //DF test
//*****************************************************************
void DF_Test(void)
{
	int8u ucBuf[100];
	ATT7022_Init();
	while(1)
	{
		/*
		WDTClr();
		ucBuf[0]=0x98;
		ucBuf[1]=0x68;
		ucBuf[63]=0x99;
		DF_Write(0xda8,ucBuf,64);
		
		WDTClr();
		memset(ucBuf,0,100);		
		DF_Read(ucBuf,0xda8,64);
		
		ucBuf[0]=0x32;
		ucBuf[1]=0x45;
		ucBuf[63]=0x12;
		DF_Write(0xda8+64,ucBuf,64);	
	*/
		memset(ucBuf,0,100);		
		DF_Read(ucBuf,0xda8+64,20);		
		
		WDTClr();
		memset(ucBuf,0,100);		
		DF_Read(ucBuf,0xda8+64,64);		
		
		memset(ucBuf,0,100);		
		DF_Read(ucBuf,0xda8+64,64);
		
		WDTClr();
	}
}

#undef ON
#undef OFF


