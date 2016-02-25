/******************************************************************************
 //EEP_Driver.c - E2PROM read and write order
 // Copyright Hangzhou East Smart Technology Co.,Ltd.
 // DESCRIPTION: - this function can only be applied to 64
 //modification history
 //--------------------
 //01a, 12feb2011,  written
 // --------------------
 
 *EEP_Driver.c - E2PROM读写时序
 * 
 * Copyright Hangzhou East Smart Technology Co.,Ltd.
 * 
 * DESCRIPTION: - 
 *     本函数只合适64
 * modification history
 * --------------------
 * 01a, 12feb2011,  written
 * --------------------
 ******************************************************************************/

#include "..\inc\includes.h"


#define		EEP_DELAY	1
//*****************************************************************
 //12C read function
//*****************************************************************
static	int8s   __E_Read(int8u *Obj, int16u Addr, int8u Len)
{
    int8u temp,cmd;

       //cmd = EEPROM_ADDR ;	//acquire device address
	cmd = EEPROM_ADDR ;

    temp = 0;
    
       //I2C_Start(I2C_BUS_1);    //starting 12C communication
	I2C_Start(I2C_BUS_1);

       //while ( I2C_WriteByte(cmd,I2C_BUS_1) && (temp<3) ) //send device address
	while ( I2C_WriteByte(cmd,I2C_BUS_1) && (temp<3) )
    {
        I2C_Stop(I2C_BUS_1);
             //DelayMs(EEP_DELAY);   //delay some time to ensure EEP page to be finished
		DelayMs(EEP_DELAY);
        I2C_Start(I2C_BUS_1);
        temp++;
    }
       //if (temp >= 3)       //device might be abnormal
	if (temp >= 3)
    {   
        I2C_Stop(I2C_BUS_1); 
        return(-1); 
    }

    temp = (int8u)((Addr&0x1FFF)>>8);
       //if ( I2C_WriteByte(temp,I2C_BUS_1))   //send subaddress high-order
	if ( I2C_WriteByte(temp,I2C_BUS_1))
    {
        I2C_Stop(I2C_BUS_1);
        return(-1);
    }
    temp =(int8u)(Addr);
       //if ( I2C_WriteByte(temp,I2C_BUS_1) )   //send subaddress low-order
	if ( I2C_WriteByte(temp,I2C_BUS_1) )
    {
        I2C_Stop(I2C_BUS_1);
        return(-1);
    }

    I2C_Start(I2C_BUS_1);
       //if ( I2C_WriteByte(cmd|0x01,I2C_BUS_1) )  //send device address read command
	if ( I2C_WriteByte(cmd|0x01,I2C_BUS_1) )
    {   
        I2C_Stop(I2C_BUS_1);
        return(-1); 
    }

    while (Len-->0)
    {
              //temp = (Len!=0?0x00 : 0x01);       //if receives the last byte, then no sending of response
		temp = (Len!=0?0x00 : 0x01);
        *Obj = I2C_ReadByte( temp,I2C_BUS_1 );
        Obj++;
    }
    I2C_Stop(I2C_BUS_1);
    return(0x00);
}
//*****************************************************************
 //12C write function
// I2C写函数
//*****************************************************************
static int8u  __E_Write(int16u Dst, int8u  *Src, int8u Len)
{
    int8u  temp;
       //int8u  cmdtemp;            //command buffer
	int8u  cmdtemp;
    
       //cmdtemp = EEPROM_ADDR;// | ((Dst>>12)&0x0E);        //acquire device address command
	cmdtemp = EEPROM_ADDR;// | ((Dst>>12)&0x0E);

    temp = 0;
    
       //I2C_Start(I2C_BUS_1);               //starting 12C communication
	I2C_Start(I2C_BUS_1);

       //while ( I2C_WriteByte(cmdtemp,I2C_BUS_1) && (temp<3) )   //send device address
	while ( I2C_WriteByte(cmdtemp,I2C_BUS_1) && (temp<3) )
    {
        I2C_Stop(I2C_BUS_1);
             //DelayMs(EEP_DELAY);           //delay some time to ensure EEP page to be finished
		DelayMs(EEP_DELAY);
        I2C_Start(I2C_BUS_1);
        temp++;
    }
       //if (temp >= 3)  //device might be abnormal
	if (temp >= 3)
    {   
        I2C_Stop(I2C_BUS_1); 
        return(0xff); 
    }

    temp = (int8u)((Dst&0x1FFF)>>8);
       //if ( I2C_WriteByte(temp,I2C_BUS_1))   //send subaddress high-order
	if ( I2C_WriteByte(temp,I2C_BUS_1))
    {
        I2C_Stop(I2C_BUS_1);
        return(0xff);
    }
    temp =(int8u)(Dst);
       //if ( I2C_WriteByte(temp,I2C_BUS_1) )     //send subaddress low-order
	if ( I2C_WriteByte(temp,I2C_BUS_1) )
    {
        I2C_Stop(I2C_BUS_1);
        return(0xff);
    }

    while (Len-->0)
    {        
        I2C_WriteByte(*Src,I2C_BUS_1);
        Src++;
    }
    I2C_Stop(I2C_BUS_1);
    return(0);
}

/*********************************************************/
//name:int8u	E_Write(int16u Addr,int8u *buf,int8u len)
//function:write EEROM data, can be written contineously
//input parameter:target address,data buffer area address, read data length
//output parameter:success 0. failure-1
//introduction: write in 64 bytes at a time maximum
/*********************************************************/
extern int8u	E_Write(int16u Addr,int8u *Obj,int8u Len)
{

	int8u k,tlen,adr;
	int8u ucBuf[32];

	while (Len > 0 )
	{

		WDTClr();
		adr=Addr&0x1f;
		tlen=EEROM_PAGES-adr;
		
		if(Len<tlen)		tlen=Len;

        for(k=4;k>0;k--)
        {
          __E_Write(Addr,Obj,tlen );
		  	DelayMs(40);
          __E_Read(ucBuf,Addr,tlen );

          if(memcmp(Obj,ucBuf,tlen)==0)   break;
        }
										   
        if(k==0)  
		{
			//return FALSE;
		}
		
		Addr += tlen;
		Obj += tlen;
		Len -= tlen;
		
		DelayMs(40);
	}
    return TRUE;       
}



//*****************************************************************
 //12C read data
//*****************************************************************
extern	int8u  E_Read(int8u *Obj, int16u Addr, int8u Len)
{   
	int8u adr,tlen;
	int8u k;
	int8u ucBuf[32];
		
	
	while ( Len > 0 )
	{
		 WDTClr();
		adr=Addr&0x1f;
		tlen=EEROM_PAGES-adr;
		
		if(Len<tlen)		tlen=Len;

		
		for(k=4;k>0;k--)
		{	 
			__E_Read(Obj,Addr,tlen );
			__E_Read(ucBuf,Addr,tlen );
			if(memcmp(Obj,ucBuf,tlen)==0)   break;
		}
		
		if(k==0)  
		{
			gHardErr|=ERR_EEPROM_F;
			return FALSE;
		}

		Addr += tlen;
		Obj += tlen;
		Len -= tlen;
	}

	gHardErr&=~ERR_EEPROM_F;
    return TRUE;
}


#if 0
int E2P_Write( unsigned int Dest, char* Src, int Lenth )
{
	E_Write(Dest,(int8u*)Src,Lenth);
	return 0;
}
int E2P_Read( char* Dest, unsigned int Src, int Lenth )
{
	E_Read((int8u*)Dest, Src, Lenth);
	return 0;
}
#endif
//*****************************************************************
 //12C test function
//*****************************************************************
void E2_Test(void)
{

	int8u ucBuf[32];
	

	while(1)
	{
		//WDTClr();		
		ucBuf[0]=0x12;
		ucBuf[1]=0x34;
		ucBuf[2]=0x56;
		ucBuf[3]=0x78;
		ucBuf[19]=0x98;
		ucBuf[20]=0x09;
		ucBuf[31]=0x36;
		E_Write(524, ucBuf, 32);
		memset(ucBuf,0,32);
		E_Read(ucBuf, 524, 32);
	}
}
