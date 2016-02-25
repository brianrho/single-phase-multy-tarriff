

#ifndef 	_FRAM_DRIVER_H
#define		_FRAM_DRIVER_H


#define		FM_WREN		0x06
#define		FM_WRDI		0x04

int8u	FM_ReadState(void);

int8u FM_Read(int8u *ucBuf,int32u ulAdr,int16u uiLen);

int8u FM_Write(int32u uiAdr, int8u * ucBuf, int16u uiLen);
void _FM_Write(int32u uiAdr,int8u *ucBuf,int16u uiLen);


#endif

