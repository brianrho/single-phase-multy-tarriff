#include "..\inc\includes.h"

#define	I2C_DELAYWT		2

#define		I2C_OUT		1
#define		I2C_IN		0
/*
#define	I2C_WP(ON)		(ON==1)?(P1OUT|=BIT0):(P1OUT&=~BIT0)			//P1.4
#define	I2C_SCL(ON)		(ON==1)?(P1OUT|=BIT5):(P1OUT&=~BIT5)			//P1.4
#define	I2C_SDA(ON)		(ON==1)?(P1OUT|=BIT4):(P1OUT&=~BIT4)			//P1.3

#define		I2C_SDA_R		(P1IN&BIT4)
#define		OUT		1
#define		IN		0

//#define	I2C2_WP(ON)		(ON==1)?(P2OUT|=BIT0):(P1OUT&=~BIT0)			//P1.4
#define	I2C2_SCL(ON)	(ON==1)?(P2OUT|=BIT2):(P2OUT&=~BIT2)			//P1.4
#define	I2C2_SDA(ON)	(ON==1)?(P2OUT|=BIT3):(P2OUT&=~BIT3)			//P1.3

#define		I2C2_SDA_R		(P2IN&BIT3)
*/
//**********************************************************************
//I2C SCL output
//  I2C SCL输出
//**********************************************************************
void I2C_SCL_DIR(int8u cha,int8u Com)	
{
	if(Com==I2C_BUS_1)
	{
		if(cha==I2C_OUT)
		{
		//input
			P1DIR|=BIT5;				//输入
		}
		else
		{
			P1DIR&=~BIT5;
		}
	}
	else
	{

		if(cha==I2C_OUT)
		{
		//input
			P2DIR|=BIT2;				//输入
		}
		else
		{
			P2DIR&=~BIT2;
		}
	}
}
//**********************************************************************
//I2C SDA output
//  I2C SDA输出
//**********************************************************************
void I2C_SDA_DIR(int8u cha,int8u Com)
{
	if(Com==I2C_BUS_1)
	{
		if(cha==I2C_OUT)			
		{
		//input
			P1DIR|=BIT4;				//输入
		}
		else
		{
		//input
			P1DIR&=~BIT4;				//输入
		}
	}
	else
	{
		if(cha==I2C_OUT)			
		{
		//input
			P2DIR|=BIT3;				//输入
		}
		else
		{
		//input
			P2DIR&=~BIT3;				//输入
		}	
	}
}
//**********************************************************************
//I2C write-protect
//  I2C 写保护
//**********************************************************************
void I2C_WP(int8u On,int8u Com)
{

	P1DIR|=BIT3;
	if(Com==I2C_BUS_1)
	{
		if(On==1)
		{
			P1OUT|=BIT3;
		}
		else
		{

			P1OUT&=~BIT3;
		}
	}
	
}
//**********************************************************************
//I2C SCL output
//  I2C SCL输出
//**********************************************************************
void I2C_SCL(int8u On,int8u Com)
{
	if(Com==I2C_BUS_1)
	{

		if(On==1)
		{
			P1OUT|=BIT5;
		}
		else
		{
			P1OUT&=~BIT5;			//P1.4		

		}
	}
	else
	{
		if(On==1)
		{
			P2OUT|=BIT2;
		}
		else
		{
			P2OUT&=~BIT2;
		}
	}

}
//**********************************************************************
//I2C SDA output
//  I2C SDA输出
//**********************************************************************
void I2C_SDA(int8u On,int8u Com)
{
	if(Com==I2C_BUS_1)
	{

		if(On==1)
		{
			P1OUT|=BIT4;
		}
		else
		{
			P1OUT&=~BIT4;			//P1.4		

		}
	}
	else
	{
		if(On==1)
		{
			P2OUT|=BIT3;
		}
		else
		{
			P2OUT&=~BIT3;
		}
	}

}
//**********************************************************************
//I2C SDA read
//  I2C SDA读
//**********************************************************************
int8u I2C_SDA_R(int8u Com)
{
	if(Com==I2C_BUS_1)
	{
		if(P1IN&BIT4)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		if(P2IN&BIT3)
		{
			return 1;
		}

		else
		{
			return 0;
		}
	}
}
//------------------------------------------------function section-----------------------------------------------------//
//------------------------------------------------ 函数区 -------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------//
//function performance:I2C bus delay
//函数功能：I2C总线延时
//---------------------------------------------------------------------------------------------------------------//
void  I2C_Delay(unsigned char nns)
{
   unsigned char temp;
   for(temp=nns; temp>0; temp--);
}


//---------------------------------------------------------------------------------------------------------------//
//function performance:I2C bus initialization
//函数功能：I2C总线初始化
//---------------------------------------------------------------------------------------------------------------//
void  I2C_Init(int8u Com)
{
    I2C_SDA(1,Com);				/*	*/
    I2C_SCL(1,Com);
    I2C_SDA(1,Com);				/*	*/
    I2C_SCL(1,Com);

    I2C_SDA_DIR(I2C_OUT,Com);                                   
    I2C_SDA_DIR(I2C_OUT,Com);                                   
    I2C_SCL_DIR(I2C_OUT,Com);
    I2C_SCL_DIR(I2C_OUT,Com);
}

//---------------------------------------------------------------------------------------------------------------//
//function performance: send I2C start signal
//函数功能：发送I2C启动信号
//---------------------------------------------------------------------------------------------------------------//
void    I2C_Start(int8u Com)
{
    I2C_SDA_DIR(I2C_OUT,Com);                                   
    I2C_SCL_DIR(I2C_OUT,Com);

	I2C_WP(0,Com);	
    I2C_SDA(1,Com);
    I2C_SCL(1,Com);
    I2C_Delay(I2C_DELAYWT);
    I2C_SDA(0,Com);
    I2C_Delay(I2C_DELAYWT);
    I2C_SCL(0,Com);
    I2C_Delay(I2C_DELAYWT);
}

//---------------------------------------------------------------------------------------------------------------//
//function performance:send I2C end signal
//函数功能：发送I2C结束信号
//---------------------------------------------------------------------------------------------------------------//
void     I2C_Stop(int8u Com)
{
    I2C_SDA(0,Com);
    I2C_Delay(I2C_DELAYWT);
    I2C_SCL(1,Com);
    I2C_Delay(I2C_DELAYWT);
    I2C_SDA(1,Com); 
    I2C_WP(1,Com);
}

//---------------------------------------------------------------------------------------------------------------//
//function performance:send a byte through I2C
//函数功能：通过I2C发送一个字节
//entrance parameters:SdByte-----the byte need to be sent
//入口参数：SdByte-----要发送的字节
//exit parameters:return responds end,zero responds zero, or respons non-zero;
//出口参数：返回应答结果，0--应答为0，否则应答为非0；
//Note:return value is integral data, prevent some IO on high position lead to no response data to be received
//注意：	返回值为整型数据，防止某个IO口放在高位导致没有接收到应答数据
//---------------------------------------------------------------------------------------------------------------//
int8u  I2C_WriteByte(int8u SdByte,int8u Com)
{
	int8u temp=8;
//use to return response result
    int8u Acktemp;                               //用作返回应答结果
    
    do
    {
    //send data signal
        if (SdByte & 0x80)                               //发送数据信号
        {
             I2C_SDA(1,Com);
        }
        else
        {
             I2C_SDA(0,Com); 
        }

        I2C_Delay(I2C_DELAYWT);
        I2C_SCL(1,Com);
        I2C_Delay(I2C_DELAYWT);
        SdByte <<= 1;
	//SCL turns to low level after one byte to be sent
        I2C_SCL(0,Com);                                    //一个字节发送完之后SCL为低电平
    }
    while (--temp!=0);

    I2C_SDA (0,Com);
 	I2C_SDA_DIR(I2C_IN,Com);
    I2C_Delay(I2C_DELAYWT);
	//add delay time of low level 
    I2C_Delay(2);                                     //增加低电平延时时间
    I2C_SCL (1,Com);
    if(I2C_SDA_R(Com))
    {
    	Acktemp=1;
    }
    else
    {

		Acktemp=0;
    }
    I2C_Delay(I2C_DELAYWT);
   	I2C_SCL (0,Com);
    I2C_SDA_DIR(I2C_OUT,Com);
	
    return (Acktemp);
}

//---------------------------------------------------------------------------------------------------------------//
//function performance: read one byte by I2C
//entrance parameter:ACK---indicate whether receiver function send response,0--send response, or don't send
//exit parameter:return to read the obtained bytes
//函数功能：通过I2C读取一个字节
//入口参数：ACK---指明接收函数是否发送应答，0--发送应答，否则不发送应答
//出口参数：返回读取得到的字节
//---------------------------------------------------------------------------------------------------------------//
unsigned char   I2C_ReadByte(unsigned char Ack,int8u Com)
{
    unsigned char temp=8;
	//use to store received bytes
    unsigned char Rtemp=0x00;                             //用做存放接收到的字节
 
    I2C_SDA_DIR(I2C_IN,Com);
    do
    {
        I2C_Delay(I2C_DELAYWT);
		//add time of low level
        I2C_Delay(2);                                    //增加低电平时间
        I2C_SCL(1,Com);
        Rtemp <<= 1;
		//the level of data bit is high level
        if (I2C_SDA_R(Com))                                   //数据位电平为高电平
        {
             Rtemp |= 0x01;
        }
		//the level of data bit is low level
        else                                              //数据位电平为低电平
        {
             Rtemp &= 0xfe;
        }
        I2C_Delay(I2C_DELAYWT);
        I2C_SCL(0,Com);      
    }
    while (--temp!=0);

    I2C_SDA_DIR(I2C_OUT,Com);
	//need to send response signal
    if (Ack==0)                                          //需要发送应答信号
    {
        I2C_SDA(0,Com);
    }
    else
    {
        I2C_SDA(1,Com);
    }     
    I2C_Delay(I2C_DELAYWT);
	//add delay time of low level
    I2C_Delay(2);                                       //增加低电平延时时间
    I2C_SCL(1,Com);
    I2C_Delay(I2C_DELAYWT);
    I2C_SCL(0,Com); 
  
    return (Rtemp);
}
