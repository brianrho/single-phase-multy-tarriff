/*************************************************************************************
 //document type: universal function library
 //document function:
 //change permissions: lower driver-maintain personel
 //document association:


 //founder: chenbo
 //creation date: 01/06/207
 //current version: Ver0.1
 //version information: Ver0.1					GeminiKQ
 **************************************************************************************/
#include "include.h"

#include "Gfunction.h"

unibuf_t ugBuf;

#ifdef 	chs_debug
//int8u	gWorkUsed;		//track service condition of gWorkTmp, every usage ++
int8u gWorkUsed; //跟踪gWorkTmp使用情况，每次使用++
#endif

//#define		MEM_WORK_USED0		0x01
//#define		MEM_WORK_USED1		0x02
//#define		MEM_WORK_USED2		0x04
//#define		MEM_WORK_USED3		0x08


int8u code MamBitTbl[] = { 0x01, 0x02, 0x04, 0x08 };

int8u xdata gWorkTmp[64]; /*	*/

int16u code MamTbl[2] = { &gWorkTmp[0], &gWorkTmp[32],
//	&gWorkTmp[64],
		//	&gWorkTmp[96],
		};

void gWorkFreeAll(void) {
	gWorkUsed = 0;
}

//*distribute public area      */
int8u xdata *gWorkMalloc() {
	int8u i, tmp;

	if ((gWorkUsed & 0x03) == 0x03) {
		while (1)
			;
	}

	tmp = gWorkUsed;
	for (i = 0; i < 2; i++) {
		if (!(tmp & 0x01)) {
			break;
		}
		tmp >>= 1;
	}

	while (i > 1)
		;

	gWorkUsed |= MamBitTbl[i];

	return (MamTbl[i]);
}
//*release public area    */
void gWorkFree(int8u xdata *ptr)
{
	int8u i;

	for(i=0;i<2;i++)
	{
		if(ptr==MamTbl[i])
		{
			gWorkUsed&=~MamBitTbl[i];
		}
	}
}

void Invert(int8u *str, int8u *sou, int8u len) {
	for (; len > 0; len--) {
		str[len - 1] = *sou++;
	}
}

int8u BtoA(int8u BCD) {
	int8u Tmp;

	if (BCD < 10)
		Tmp = BCD + 0x30;
	else if (BCD >= 10)
		Tmp = BCD + 0x37;
	return Tmp;
}
//**********************************************************************
// Turn BCD to ASCII data
//**********************************************************************
void BCD_Asc(int8u *Asc, int8u *BCD, int8u Lenth) {
	int8u *Ptr;

	Ptr = BCD;
	for (; Lenth > 0; Lenth--) {
		//   Ptr = BCD + i ;
		*Asc++ = BtoA((*Ptr >> 4) & 0x0F);
		*Asc++ = BtoA(*Ptr & 0x0F);
		Ptr++;
	}

	/*
	 #ifdef	BIG_ENDIAN
	 for( i=Lenth; i>0; i-- )
	 {
	 Ptr = BCD + i-1 ;
	 *Asc++ = BtoA( (*Ptr>>4) & 0x0F );
	 *Asc++ = BtoA( *Ptr & 0x0F );
	 }
	 #else
	 for( i=0; i<Lenth; i++ )
	 {
	 Ptr = BCD + i ;
	 *Asc++ = BtoA( (*Ptr>>4) & 0x0F );
	 *Asc++ = BtoA( *Ptr & 0x0F );
	 }
	 #endif
	 */
}

//**********************************************************************
// turn 1 ASCII to 1 BCD
//**********************************************************************
int8u AtoB(int8u Asc) {
	int8u data Tmp;

	if (Asc >= 0x30 && Asc <= 0x39)
		Tmp = Asc - 0x30;
	else if (Asc >= 0x41 && Asc <= 0x46)
		Tmp = Asc - 0x37;
	return Tmp;
}

//**********************************************************************
// turn 2n ASCII to n BCD
//**********************************************************************
void Asc_BCD(int8u *BCD, int8u *Asc, char Lenth) {
	int8u data i;
	int8u *Ptr;

	//	Lenth>>=1;		//Lenth/2

	Ptr = BCD;
	for (i = 0; i < Lenth; i++) {
		*Ptr = AtoB(*Asc++) << 4;
		*Ptr |= AtoB(*Asc++);
		Ptr++;
	}

}

int8u Asc_HEX8(int8u *Asc, int8u *ucRet) {
	int16u uiTmp = 0;
	int8u i = 0, ucLen = 0;

	if ((*Asc == ',') && (*(Asc + 1) == ',')) {
		Asc = 0;
		*ucRet = 0;
		return 2;
	}

	i = 0;
	while (i < 3) {
		if ((*Asc > '9') || (*Asc < '0')) {
			Asc++;
			ucLen++;
		} else {
			break;
		}
		i++;
	}
	i = 0;
	while (i < 4) {

		i++;
		ucLen++;
		uiTmp *= 10;
		uiTmp += AtoB(*Asc);
		Asc++;
		if ((*Asc > '9') || (*Asc < '0')) {
			break;
		}

	}
	*ucRet = (int8u) uiTmp;

	return ucLen;

}

int8u Asc_HEX16(int8u * Asc, int16u *uiRet) {
	int16u uiTmp = 0;
	int8u i = 0, ucLen = 0;

	if ((*Asc == ',') && (*(Asc + 1) == ',')) {
		Asc = 0;
		*uiRet = 0;
		return 2;
	}

	i = 0;
	while (i < 3) {
		if ((*Asc > '9') || (*Asc < '0')) {
			Asc++;
			ucLen++;
		} else {
			break;
		}
		i++;
	}

	i = 0;
	while (i < 5) {

		i++;
		ucLen++;
		uiTmp *= 10;
		uiTmp += AtoB(*Asc);
		Asc++;
		if ((*Asc > '9') || (*Asc < '0')) {
			break;
		}
	}

	*uiRet = uiTmp;

	return ucLen;

}

int8u HEX16_ASC(int8u *Asc, int16u Data) {
	int8u i, ucLen;
	int8u ucBuf[10];

	if (Data == 0) {
		*Asc = '0';
		return 1;
	}
	i = 0;
	while (Data > 0) {
		ucBuf[i] = Data % 10;
		Data /= 10;
		i++;
	}
	ucLen = i;
	for (; i > 0; i--) {
		*Asc = ucBuf[i - 1] + '0';
		Asc++;
	}
	return ucLen;
}

int8u HEX8_ASC(int8u *Asc, int8u Data) {
	int8u i, ucLen;
	int8u ucBuf[10];

	if (Data == 0) {
		*Asc = '0';
		return 1;
	}
	i = 0;
	while (Data > 0) {
		ucBuf[i] = Data % 10;
		Data /= 10;
		i++;
	}
	ucLen = i;
	for (; i > 0; i--) {
		*Asc = ucBuf[i - 1] + '0';
		Asc++;
	}
	return ucLen;

}
/*
 int8u HEX08_ASC(int8u *Asc,int8u Data)
 {


 }

 int8u HEX32_ASC(int8u *Asc,int32u Data)
 {


 }
 */

//**********************************************************************
// turn 4 HEX to 4 BCD
//**********************************************************************
void HEX_BCD(char *BCD, unsigned long Data) {
	int8u data i;

	if (Data > 99999999) {
		*(BCD + 3) = 0x00;
		*(BCD + 2) = 0x00;
		*(BCD + 1) = 0x00;
		*BCD = 0x00;
		return;
	}
	for (i = 0; i < 4; i++) {
		*BCD = Data % 10;
		Data = (Data - *BCD) / 10;
		*BCD += ((Data % 10) << 4) & 0xf0;
		Data = (Data - Data % 10) / 10;
		BCD++;
	}
}

//**********************************************************************
// turn 1 HEX to 1 BCD
//**********************************************************************
unsigned char Byte_BCD(unsigned char Data) {
	if (Data > 99)
		return 0x00;
	return (Data / 10 * 0x10 + Data % 10);
}

//**********************************************************************
// turn 1 BCD to 1 HEX
//**********************************************************************
unsigned char BCD_Byte(unsigned char Data) {
	return (((Data >> 4) & 0x0f) * 10 + (Data & 0x0f));
}
//**********************************************************************
// turn 2 HEX to 2 BCD
//**********************************************************************
void Word_BCD2(unsigned char *BCD, unsigned int Data) {
	if (Data > 9999) {
		*(BCD + 1) = 0x00;
		*BCD = 0x00;
		return;
	}

	*(BCD + 1) = BCD_Byte((char) (Data / 100));
	*BCD = BCD_Byte((char) (Data % 100));
}

extern int8u BcdByteAdd(int8u *buf) {
	int8u Low, High, Cnt, cha;

	cha = *buf;
	Low = cha & 0x0f;
	High = (cha >> 4) & 0x0f;
	Cnt = 0;

	Low++;
	if (Low > 0x09) {
		Low = 0;
		High++;
		if (High > 0x09) {
			High = 0;
			Cnt = 1;
		}
	}

	*buf = (High << 4) & 0xf0;
	*buf += Low;

	return Cnt;

}

extern void BcdAdd(int8u *Obj, int8u Len) {
	int8u i;
	int8u cTmp;
	Obj += Len - 1;

	for (i = Len; i > 0; i--) {
		cTmp = BcdByteAdd(Obj);

		if (cTmp == 0) {
			break;
		}
	}

}

//=====================================================
//function performance: unsigned long switch to BCD format
//function entrance parameter: buf: BCD buffer area
//                                value:data waiting to be trancoded
//function exit parameter: reverse to effective data dots
//statement:                 value<99999999 can be effective

//函数功能：unsigned long 转化到BCD码格式,
//函数入口参数：buf:	BCD码缓存区， 
//				value:	待转换的数据
//函数出口参数：返回有效数据位数
//说明:			value<99999999才有效
//===================================================
extern int8 HexToBcd(int8u *buf, int32u value) {
	int8u i, cTmp = 0;

	if (value > 99999999) {
		//return -1;			//reverse error
		return -1; //返回错误
	}
	if (value == 0) {
		memset(buf, 0, 4);
		return 0;
	}

	for (i = 0; i < 4; i++) {
		if (value == 0) //
		{
			break;
		}

		cTmp = value % 100;
		value /= 100;
		buf[3 - i] = ((cTmp / 10) << 4) + (cTmp % 10);
	}
	cTmp = i << 1; //*2
	//effective dots management
	//有效位处理
	if ((buf[i] & 0xf0) == 0) {
		//cTmp--;			//if the highest dot is 0, then effective dot needs to be cut one more dot
		cTmp--; //如果最高位是0的话，有效位需要再减去1位
	}

	return cTmp;
}

int8u CompareData(int8u *Obj1, int8u *Obj2, int8u Len) {

	for (; Len > 0; Len--) {
		if (*Obj1 != *Obj2)
			break;
		Obj1++;
		Obj2++;
	}

	if (Len == 0)
		return TRUE;
	else
		return FALSE;

}

int8u BcdToByte(int8u cha) {
	int8u tmp;

	tmp = (cha >> 4) & 0x0f;
	tmp *= 10;
	tmp += cha & 0x0f;

	return (tmp);
}

#define		CHA_SIG		0x01
#define		CHB_SIG		0x02

int32u SignAddHex(int32u cha, int32u chb) {
	int32u tmpb, tmpa;
	int8u Flag;

	tmpa = ~cha + 1;
	tmpb = ~chb + 1;

	if (cha & INT32_SING_BIT) {
		Flag |= CHA_SIG;
	}
	if (chb & INT32_SING_BIT) {
		Flag |= CHB_SIG;
	}

	if (Flag == 0) {
		return (cha + chb);
	}

	if (tmpa > tmpb) {
		tmpa -= tmpb;
		if (Flag & CHA_SIG) {
			return ~tmpa + 1;
		} else {
			return tmpa;
		}
	} else {
		tmpb -= tmpa;
		if (Flag & CHB_SIG) {
			return ~tmpb + 1;
		} else {
			return tmpb;
		}
	}
}

#undef 	CHA_SIG
#undef	CHB_SIG

