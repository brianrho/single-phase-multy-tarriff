
#ifndef		_DRIVER_DATAFLASH_H
#define		_DRIVER_DATAFLASH_H

/**************************************************************************
       //document type:target.c
       //document function:all firmware driver port
       //change permissions:
       //document associations:
	文件类型：target.c
	文件作用：所有硬件驱动接口
	修改权限：
	文件相关：

	//founder:
	//creation date:
	//current version:
	创 建 人：
	创建日期：
	当前版本：

	//version information:
	版本信息：
	

      introduction:firmware condition: CPU MSP43F448
      software condition: IAR4.20
	说明：硬件环境：CPU MSP43F448
              软件环境：IAR4.20

**************************************************************************/


/***********************/
void DF_ReadID(int8u *buf);

void DF_Write(int32u ulAdr, int8u * ucBuf, int16u uiLen);

void DF_Read(int8u * ucBuf, int32u ulAdr, int16u uiLen);
/***********************/



#endif
