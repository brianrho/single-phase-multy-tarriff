#include "..\inc\includes.h"
//*****************************************************************
//ferroelectric status reading
//*****************************************************************
int8u FM_ReadState(void) {
	int8u ucRet;

	SPI_CS(SPI_FRAM);
	SPI_WByte(0x05);

	ucRet = SPI_Read();

	SPI_CS(SPI_NULL);

	return ucRet;
}

//*****************************************************************
//write ferroelectric status
//*****************************************************************
void FM_WriteState(int8u ucSta) {

	SPI_CS(SPI_FRAM);
	SPI_WByte(0x05);

	SPI_WByte(ucSta);

	SPI_CS(SPI_NULL);

}

//*****************************************************************
//ferroelectric write commad
//*****************************************************************
void FM_WriteCmd(int8u Cmd) {
	SPI_CS(SPI_FRAM);

	SPI_WByte(Cmd);

	SPI_CS(SPI_NULL);
}
//*****************************************************************
//ferroelectric write data
//*****************************************************************
void _FM_Write(int32u uiAdr, int8u *ucBuf, int16u uiLen) {
	int8u ucTmp = 0;

	ucTmp = ucTmp;

	SPI_POWON(ON, FM_POW);

	FM_WriteCmd(FM_WREN);

	SPI_CS(SPI_FRAM);

	//FM_SET_WP();			//write protection
	FM_SET_WP();			//Ð´±£»¤

	SPI_WByte(0x02);

	ucTmp = (char) (uiAdr >> 8);
	SPI_WByte(ucTmp);

	ucTmp = (char) uiAdr;
	SPI_WByte(ucTmp);

	for (; uiLen > 0; uiLen--) {
		SPI_WByte(*ucBuf);
		ucBuf++;
	}

	DelayMs(1);
	SPI_CS(SPI_NULL);

	SPI_POWON(OFF, FM_POW);

}
//*****************************************************************
//ferroeletric read data
//*****************************************************************
void _FM_Read(int8u *ucBuf, int32u ulAdr, int16u uiLen) {

	int8u ucTmp = 0;

	ucTmp = ucTmp;

	SPI_POWON(ON, FM_POW);

	SPI_CS(SPI_FRAM);

	SPI_WByte(0x03);

	ucTmp = (char) (ulAdr >> 8);
	SPI_WByte(ucTmp);

	ucTmp = (char) ulAdr;
	SPI_WByte(ucTmp);

	for (; uiLen > 0; uiLen--) {
		*ucBuf = SPI_Read();
		ucBuf++;
	}

	SPI_CS(SPI_NULL);

	SPI_POWON(OFF, FM_POW);
}
//*****************************************************************
//ferroelectric write data
//*****************************************************************
int8u FM_Write(int32u ulAdr, int8u *ucBuf, int16u uiLen) {

	int16u uiTmp;
	int8u i;
	int8u Buf[32];
	WDTClr();
	while (uiLen > 0) {
		if (uiLen < 32) {
			uiTmp = uiLen;
		} else {

			uiTmp = 32;
		}
		for (i = 0; i < 3; i++) {

			_FM_Write(ulAdr, ucBuf, uiTmp);
			_FM_Read(Buf, ulAdr, uiTmp);
			if (0 == memcmp(ucBuf, Buf, uiTmp)) {
				break;
			}
		}
		if (i > 2) {
			//gErrState|=ERR_FRAM;
			return 0;
		}
		ucBuf += uiTmp;
		uiLen -= uiTmp;
		ulAdr += uiTmp;
	}
	return 0;

}
//*****************************************************************
//ferroeletric read data
//*****************************************************************
int8u FM_Read(int8u *ucBuf, int32u ulAdr, int16u uiLen) {
	int8u i;
	int16u uiTmp;
	int8u Buf[32];

	while (uiLen > 0) {
		if (uiLen > 32) {
			uiTmp = 32;
		} else {

			uiTmp = uiLen;

		}
		for (i = 0; i < 3; i++) {
			_FM_Read(ucBuf, ulAdr, uiTmp);
			_FM_Read(Buf, ulAdr, uiTmp);
			if (0 == memcmp(Buf, ucBuf, uiTmp)) {
				break;

			}
		}
		if (i > 2) {
			gHardErr |= ERR_FRAM_F;
			return 0;
		}
		ucBuf += uiTmp;
		uiLen -= uiTmp;
		ulAdr += uiTmp;
	}

	gHardErr &= ~ERR_FRAM_F;
	return uiLen;
}

//*****************************************************************
//alternating current test
//*****************************************************************
void FM_Test(void) {

#if 1
	int8u ucBuf[4];
	ucBuf[0] = 0x55;
	ucBuf[1] = 0x85;
	ucBuf[0] = 0x55;
	ucBuf[0] = 0x55;

	while (1) {
		ucBuf[0] = 0x55;
		ucBuf[1] = 0x85;
		ucBuf[0] = 0x55;
		ucBuf[0] = 0x55;
		WDTClr();
		FM_Write(0, ucBuf, 2);
		memset(ucBuf, 0, 4);
		FM_Read(ucBuf, 0, 2);
	}
#endif	
}

