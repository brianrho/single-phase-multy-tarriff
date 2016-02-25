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
//  I2C SCL���
//**********************************************************************
void I2C_SCL_DIR(int8u cha,int8u Com)	
{
	if(Com==I2C_BUS_1)
	{
		if(cha==I2C_OUT)
		{
		//input
			P1DIR|=BIT5;				//����
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
			P2DIR|=BIT2;				//����
		}
		else
		{
			P2DIR&=~BIT2;
		}
	}
}
//**********************************************************************
//I2C SDA output
//  I2C SDA���
//**********************************************************************
void I2C_SDA_DIR(int8u cha,int8u Com)
{
	if(Com==I2C_BUS_1)
	{
		if(cha==I2C_OUT)			
		{
		//input
			P1DIR|=BIT4;				//����
		}
		else
		{
		//input
			P1DIR&=~BIT4;				//����
		}
	}
	else
	{
		if(cha==I2C_OUT)			
		{
		//input
			P2DIR|=BIT3;				//����
		}
		else
		{
		//input
			P2DIR&=~BIT3;				//����
		}	
	}
}
//**********************************************************************
//I2C write-protect
//  I2C д����
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
//  I2C SCL���
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
//  I2C SDA���
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
//  I2C SDA��
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
//------------------------------------------------ ������ -------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------//
//function performance:I2C bus delay
//�������ܣ�I2C������ʱ
//---------------------------------------------------------------------------------------------------------------//
void  I2C_Delay(unsigned char nns)
{
   unsigned char temp;
   for(temp=nns; temp>0; temp--);
}


//---------------------------------------------------------------------------------------------------------------//
//function performance:I2C bus initialization
//�������ܣ�I2C���߳�ʼ��
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
//�������ܣ�����I2C�����ź�
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
//�������ܣ�����I2C�����ź�
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
//�������ܣ�ͨ��I2C����һ���ֽ�
//entrance parameters:SdByte-----the byte need to be sent
//��ڲ�����SdByte-----Ҫ���͵��ֽ�
//exit parameters:return responds end,zero responds zero, or respons non-zero;
//���ڲ���������Ӧ������0--Ӧ��Ϊ0������Ӧ��Ϊ��0��
//Note:return value is integral data, prevent some IO on high position lead to no response data to be received
//ע�⣺	����ֵΪ�������ݣ���ֹĳ��IO�ڷ��ڸ�λ����û�н��յ�Ӧ������
//---------------------------------------------------------------------------------------------------------------//
int8u  I2C_WriteByte(int8u SdByte,int8u Com)
{
	int8u temp=8;
//use to return response result
    int8u Acktemp;                               //��������Ӧ����
    
    do
    {
    //send data signal
        if (SdByte & 0x80)                               //���������ź�
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
        I2C_SCL(0,Com);                                    //һ���ֽڷ�����֮��SCLΪ�͵�ƽ
    }
    while (--temp!=0);

    I2C_SDA (0,Com);
 	I2C_SDA_DIR(I2C_IN,Com);
    I2C_Delay(I2C_DELAYWT);
	//add delay time of low level 
    I2C_Delay(2);                                     //���ӵ͵�ƽ��ʱʱ��
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
//�������ܣ�ͨ��I2C��ȡһ���ֽ�
//��ڲ�����ACK---ָ�����պ����Ƿ���Ӧ��0--����Ӧ�𣬷��򲻷���Ӧ��
//���ڲ��������ض�ȡ�õ����ֽ�
//---------------------------------------------------------------------------------------------------------------//
unsigned char   I2C_ReadByte(unsigned char Ack,int8u Com)
{
    unsigned char temp=8;
	//use to store received bytes
    unsigned char Rtemp=0x00;                             //������Ž��յ����ֽ�
 
    I2C_SDA_DIR(I2C_IN,Com);
    do
    {
        I2C_Delay(I2C_DELAYWT);
		//add time of low level
        I2C_Delay(2);                                    //���ӵ͵�ƽʱ��
        I2C_SCL(1,Com);
        Rtemp <<= 1;
		//the level of data bit is high level
        if (I2C_SDA_R(Com))                                   //����λ��ƽΪ�ߵ�ƽ
        {
             Rtemp |= 0x01;
        }
		//the level of data bit is low level
        else                                              //����λ��ƽΪ�͵�ƽ
        {
             Rtemp &= 0xfe;
        }
        I2C_Delay(I2C_DELAYWT);
        I2C_SCL(0,Com);      
    }
    while (--temp!=0);

    I2C_SDA_DIR(I2C_OUT,Com);
	//need to send response signal
    if (Ack==0)                                          //��Ҫ����Ӧ���ź�
    {
        I2C_SDA(0,Com);
    }
    else
    {
        I2C_SDA(1,Com);
    }     
    I2C_Delay(I2C_DELAYWT);
	//add delay time of low level
    I2C_Delay(2);                                       //���ӵ͵�ƽ��ʱʱ��
    I2C_SCL(1,Com);
    I2C_Delay(I2C_DELAYWT);
    I2C_SCL(0,Com); 
  
    return (Rtemp);
}
