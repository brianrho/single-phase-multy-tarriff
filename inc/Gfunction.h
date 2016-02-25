
#ifndef _GFUNCTION_H_
#define	_GFUNCTION_H_

typedef struct 
{
//add to 64-10 in operating STS,gToken is a global parameter,the former data as work buffer

	int8u buf[25];			//补到64-10 在操作 STS中，gToken是个全局参数，前面的数据作为工作缓存
	int8u MeterKey[8];
	int8u Hex[9];			
	//decode data
	int8u EnCodeData[9];	//解码数据
	//factory password
	int8u MfrCode;			//工厂密码
	int16u crc;
	//TOKEN code
	int8u gToken[10];		//TOKEN码

}sts_ram_t;



typedef	union
{
//actually can use 25 in sts module
	int8u gWork[64];			//在sts模块中实际可以用25个
	int8u UartBuf[64];
	sts_ram_t	gStsRam;

}unibuf_t;

#define	MAX_COM  	63

extern	unibuf_t	ugBuf;

extern	int8u 		gWorkTmp[64];		/*	*/

/////////////////////////////////////
extern	void	gWorkFreeAll(void);

extern	int16u code MamTbl[2];
extern	int8u	xdata *gWorkMalloc();
/*public area of release*/
/*	释放公共区 */
extern	void gWorkFree(int8u xdata *ptr);
//track gWorkTmp use condition,use ++everytime
extern	int8u	gWorkUsed;		//跟踪gWorkTmp使用情况，每次使用++
////////////////////////////////////////

extern	int8u HEX16_ASC(int8u *Asc,int16u Data);

extern	int8u  HEX8_ASC(int8u *Asc,int8u Data);

int8u Asc_HEX16(int8u * Asc,int16u *uiRet);

extern	int8u Asc_HEX8(int8u * Asc,int8u *ucRet);

extern	void BcdAdd(int8u	*Obj,int8u Len);

extern	 int8u	HexToBcd(int8u *buf,int32u value);

extern	int8u CompareData(int8u *Obj1,int8u *Obj2,int8u Len);

int8u	BcdToByte(int8u cha);

extern	int8u 	BcdByteAdd(int8u *buf);

int8u  BtoA( int8u BCD );
void Invert(int8u *str,int8u *sou,int8u len);

//**********************************************************************
// Turn BCD to ASCII data
//**********************************************************************
void BCD_Asc( int8u *Asc, int8u *BCD ,int8u Lenth );


//**********************************************************************
// turn 1 ASCII to 1 BCD
//**********************************************************************
int8u AtoB( int8u Asc );

//**********************************************************************
// turn 2n ASCII to n BCD
//**********************************************************************
void Asc_BCD( int8u *BCD, int8u *Asc, char Lenth );


//**********************************************************************
// turn 4 HEX to 4 BCD
//**********************************************************************
void HEX_BCD( char *BCD, unsigned long Data );


//**********************************************************************
// turn 1 HEX to 1 BCD
//**********************************************************************
unsigned char Byte_BCD( unsigned char Data );


//**********************************************************************
// turn 1 BCD to 1 HEX
//**********************************************************************
unsigned char BCD_Byte( unsigned char Data );

//**********************************************************************
// turn 2 HEX to 2 BCD
//**********************************************************************
void Word_BCD2( unsigned char *BCD, unsigned int Data );



#define		INT32_SING_BIT		0x80000000
int32u SignAddHex(int32u cha,int32u chb);




#endif
