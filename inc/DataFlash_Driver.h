
#ifndef		_DRIVER_DATAFLASH_H
#define		_DRIVER_DATAFLASH_H

/**************************************************************************
       //document type:target.c
       //document function:all firmware driver port
       //change permissions:
       //document associations:
	�ļ����ͣ�target.c
	�ļ����ã�����Ӳ�������ӿ�
	�޸�Ȩ�ޣ�
	�ļ���أ�

	//founder:
	//creation date:
	//current version:
	�� �� �ˣ�
	�������ڣ�
	��ǰ�汾��

	//version information:
	�汾��Ϣ��
	

      introduction:firmware condition: CPU MSP43F448
      software condition: IAR4.20
	˵����Ӳ��������CPU MSP43F448
              ���������IAR4.20

**************************************************************************/


/***********************/
void DF_ReadID(int8u *buf);

void DF_Write(int32u ulAdr, int8u * ucBuf, int16u uiLen);

void DF_Read(int8u * ucBuf, int32u ulAdr, int16u uiLen);
/***********************/



#endif
