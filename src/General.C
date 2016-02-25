/**********************************************************************
 //bytes switch to BCD
 **********************************************************************/
char Byte_BCD(char Data) {
	if (Data > 99)
		return 0x00;
	return (Data / 10 * 0x10 + Data % 10);
}

/**********************************************************************
 //BCD switch to bytes
 **********************************************************************/
char BCD_Byte(char Data) {
	return (((Data >> 4) & 0x0f) * 10 + (Data & 0x0f));
}
//**********************************************************************
//word switch to BCD
//**********************************************************************
void Word_BCD2(char *Ptr, unsigned int Data) {
	if (Data > 9999) {
		*(Ptr + 1) = 0x00;
		*Ptr = 0x00;
		return;
	}

	*(Ptr + 1) = Byte_BCD((char) (Data / 100));
	*Ptr = Byte_BCD((char) (Data % 100));
}
unsigned int BCD2_Word(unsigned char *Ptr) {
	return ((int) BCD_Byte(*Ptr) + (int) BCD_Byte(*(Ptr + 1)) * 100);
}
//**********************************************************************
//long type switch to BCD
//**********************************************************************
unsigned long BCD4_Long(char *Ptr2BCD4) {
	return ((long) BCD_Byte(*(Ptr2BCD4)) + (long) BCD_Byte(*(Ptr2BCD4 + 1))
			* 100 + (long) BCD_Byte(*(Ptr2BCD4 + 2)) * 10000 + (long) BCD_Byte(
			*(Ptr2BCD4 + 3)) * 1000000);
}

//**********************************************************************
//BCD switch to LONG
//**********************************************************************
unsigned long BCD4_LongA(char *Ptr2BCD4) {
	return ((long) BCD_Byte(*(Ptr2BCD4 + 3)) + (long) BCD_Byte(*(Ptr2BCD4 + 2))
			* 100 + (long) BCD_Byte(*(Ptr2BCD4 + 1)) * 10000 + (long) BCD_Byte(
			*(Ptr2BCD4)) * 1000000);
}

//*****************************************************************
//LONG switch to BCD4
//*****************************************************************
void Long_BCD4(char *Ptr, unsigned long Data) {
	if (Data > 99999999) {
		*(Ptr + 3) = 0x00;
		*(Ptr + 2) = 0x00;
		*(Ptr + 1) = 0x00;
		*Ptr = 0x00;
		return;
	}
	Word_BCD2(Ptr + 2, Data / 10000);
	Word_BCD2(Ptr, Data % 10000);
}
//*****************************************************************
//LONG switch to BCD4
//*****************************************************************
void Long_BCD4aA(char *Ptr, unsigned long Data) {
	unsigned char ucBuf[4];
	unsigned char i;

	if (Data > 99999999) {
		*(Ptr + 3) = 0x00;
		*(Ptr + 2) = 0x00;
		*(Ptr + 1) = 0x00;
		*Ptr = 0x00;
		return;
	}
	Word_BCD2((char*) &ucBuf[2], Data / 10000);
	Word_BCD2((char*) &ucBuf[0], Data % 10000);

	for (i = 0; i < 4; i++) {
		*Ptr = ucBuf[3 - i];
		Ptr++;
	}
}

//*****************************************************************
//HEX switch to BCD
//*****************************************************************
void HexToBcd(unsigned char * buf, unsigned long value) {
	char ucBuf[4], i;

	Long_BCD4(ucBuf, value);

	for (i = 0; i < 4; i++) {
		buf[3 - i] = ucBuf[i];
	}
}

//*****************************************************************
//LONG switch to BCD3
//*****************************************************************
void Long_BCD3(char *Ptr, unsigned long Data) {
	if (Data > 999999) {
		*(Ptr + 2) = 0x00;
		*(Ptr + 1) = 0x00;
		*Ptr = 0x00;
		return;
	}
	*(Ptr + 2) = Byte_BCD(Data / 10000);
	Word_BCD2(Ptr, Data % 10000);
}
//*****************************************************************
//ASCII switch to decimal
//*****************************************************************
char AtoB(char Asc) {
	char Tmp = 0x00;

	if (Asc >= 0x30 && Asc <= 0x39)
		Tmp = Asc - 0x30;
	else if (Asc >= 0x41 && Asc <= 0x46)
		Tmp = Asc - 0x37;
	return Tmp;
}
//*****************************************************************
//decimal switch to ASCII
//*****************************************************************
char BtoA(char BCD) {
	char Tmp = 0x00;

	if (BCD < 10)
		Tmp = BCD + 0x30;
	else if (BCD >= 10)
		Tmp = BCD + 0x37;
	return Tmp;
}

/**********************************************************************
 //ASCII switch to BCD Lenth  the length of Asc data is fixed to two times of BCD's
 **********************************************************************/
void Asc_BCD(char *BCD, char *Asc, int Lenth) {
	int i;
	char *Ptr;

	for (i = (Lenth >> 1); i > 0; i--) {
		Ptr = BCD + i - 1;
		*Ptr = AtoB(*Asc++) << 4;
		*Ptr += AtoB(*Asc++);
	}
}
/**********************************************************************
 //ASCII switch to BCD Lenth   the length of Asc data is fixed to two times of BCD's
 **********************************************************************/
void Asc_BCDA(char *BCD, char *Asc, int Lenth) {
	int i;
	char *Ptr;

	Lenth >>= 1;
	for (i = 0; i < Lenth; i++) {
		Ptr = BCD + i;
		*Ptr = AtoB(*Asc++) << 4;
		*Ptr += AtoB(*Asc++);
	}
}
//**********************************************************************
//BCD switch to ASCII
//**********************************************************************
void BCD_Asc(char *Asc, char *BCD, int Lenth) {
	int i;
	char *Ptr;

	for (i = Lenth; i > 0; i--) {
		Ptr = BCD + i - 1;
		*Asc++ = BtoA((*Ptr >> 4) & 0x0F);
		*Asc++ = BtoA(*Ptr & 0x0F);
	}
}
//**********************************************************************
//BCD switch to ASCII
//**********************************************************************
void BCD_AscA(char *Asc, char *BCD, int Lenth) {
	int i;
	char *Ptr;

	for (i = 0; i < Lenth; i++) {
		Ptr = BCD + i;
		*Asc++ = BtoA((*Ptr >> 4) & 0x0F);
		*Asc++ = BtoA(*Ptr & 0x0F);
	}
}

