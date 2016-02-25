#include "..\inc\includes.h"
#include "CDdata.c"
#include "..\inc\RN8209.h"

//locking time of password error
int8u passerr_locktime; //
//delay time of password error
int8u passerr_delaytime; //

//serial port initialization
void CommInit(void); //

extern unsigned char display_mod;
//communication completed command
const char CommEnd[] = { 0x01, 'B', '0', 0x03, 0x76, 0xFF }; //
//password reply
const char CommPass[] = { 0x01, 'P', '0', 0x02, '(', '1', '1', '1', '1', '1',
		'1', '1', '1', ')', 0x03, 0x60, EndFrame }; //
//useless
const char CommIdentify[] = { '/', 'N', 'E', 'G', '3', 'H', 'X', 0x0D, 0x0A,
		0xFF }; //
//const  	char  NotSupport[]={ 0x02,'E','R',':','N','O','T',' ','S',
//						'U','P','P','O','R','T',0X03,0X14,0xFF };

#ifdef BNTHANG
char ucBuf[20], id[12] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
		'1', '2' };
extern volatile RN8209_RMS rn8209a_rms;
extern volatile RN8209_CALIB rn8209a_calib;
#endif
//**********************************************************************
// X decimal turns to ASCII code
//**********************************************************************
unsigned char *itoaA(n, BufEndAdr, base)
long n;
unsigned char *BufEndAdr;
int base;
{
	register unsigned char *p;
	char minus=0x00;
	unsigned long Un;

	p=BufEndAdr;
	*p = 0x00;
	Un = n;
	if ((n < 0) && (base<=10)) {
		minus = 1;
		Un = -n;
	}
	else
	minus = 0;
	if (Un == 0)
	*--p = '0';
	else
	while (Un > 0) {
		*--p = "0123456789ABCDEF"[Un % base];
		Un /= base;
	}
	if (minus)
	*--p = '-';
	return p;
}

//**********************************************************************
//meter number address comparison
//**********************************************************************
signed int CmpDeviceAddr(unsigned char * yourBuf, unsigned int StartID,
		unsigned int EndID) {
	//register unsigned int i;

	if (FAC_KEY() == 0x00) {
		IEC_Comm.Flag &= ~DeviceOMIT;
		return 0;
	}

	if (StartID > EndID) {
		if (FAC_KEY() == 0x00)
			IEC_Comm.Flag &= ~DeviceOMIT;
		else
			IEC_Comm.Flag |= DeviceOMIT;
		return (0);
	}
#ifdef NO_FRAM
	E_Read((char*) &Buffer[0], DeviceAddr, 12);
#else
	FRAM_Read((char*) &Buffer[0], DeviceAddr, 12);
#endif
	if ((memcmp(&Buffer[0], yourBuf + StartID, 12) != 0) && (memcmp(
			"000000000001", yourBuf + StartID, 12) != 0))
		return (-1);

	if (IEC_Comm.ProgCnt == 0) {
		IEC_Comm.Flag |= DeviceOMIT;
		return 0;
	} else {
		IEC_Comm.Flag &= ~DeviceOMIT;
	}

	return (0);

}
//**********************************************************************
//password comparison
//**********************************************************************
char IEC_CommP1(void) {
	unsigned char i = 0;
	//password error times
	static unsigned char passerr_count = 0; //
	for (i = 0; i < 8; i++) {
		Buffer[i] = IEC_Comm.Buf[5 + i];
	}
#ifdef NO_FRAM
	E_Read((char*) &Buffer[8], PassWord, 24);
	E_Read((char*) &Buffer[32], PASSWORD_NEW, 8); //
#else
	FRAM_Read((char*) &Buffer[8], PassWord, 24);
	//obtain new added password
	FRAM_Read((char*) &Buffer[32], PASSWORD_NEW, 8); //
#endif
	//*GPRS, or PLC, not judge password*/
	if (IEC_Comm.ComId == 2) {
		IEC_Comm.Flag |= PasswordP1OK;
		IEC_Comm.Buf[0] = ACK;
		IEC_Comm.Buf[1] = EndFrame;
		//Liao Bin
		IEC_Comm.PassAcc = 3; //廖斌
		return 0;
	}
	//factory mode,the errors less than 3 times within error delay time or error locking time to

	if ((FAC_KEY() == 0) || ((passerr_count < 3) && (passerr_delaytime == 0))
			|| ((passerr_count >= 3) && (passerr_locktime == 0))) {
		passerr_count = 0;
		passerr_delaytime = 0;
		passerr_locktime = 0;
	}

	//Liao Bin
	//廖斌20111228
	if (passerr_count < 3) {
		//level 3 password
		if ((memcmp((char*) &Buffer[0], (char*) &Buffer[8], 8) == 0)
				|| (FAC_KEY() == 0)) //
		{
			IEC_Comm.Flag |= PasswordP1OK;
			IEC_Comm.Buf[0] = ACK;
			IEC_Comm.Buf[1] = EndFrame;
			//Liao Bin
			IEC_Comm.PassAcc = 3; //
			passerr_count = 0;
		}
		//level 2 password
		else if (memcmp((char*) &Buffer[0], (char*) &Buffer[16], 8) == 0) //
		{
			IEC_Comm.Flag |= PasswordP1OK;
			IEC_Comm.Buf[0] = ACK;
			IEC_Comm.Buf[1] = EndFrame;
			//Liao Bin
			IEC_Comm.PassAcc = 2; //
			passerr_count = 0;
		}
		//level 1 password
		else if (memcmp((char*) &Buffer[0], (char*) &Buffer[24], 8) == 0) //
		{
			IEC_Comm.Flag |= PasswordP1OK;
			IEC_Comm.Buf[0] = ACK;
			IEC_Comm.Buf[1] = EndFrame;
			//Liao Bin
			IEC_Comm.PassAcc = 1; //廖斌
			passerr_count = 0;
			//level 4 password
		} else if (memcmp((char*) &Buffer[0], (char*) &Buffer[32], 8) == 0) //
		{
			//level 4 password authority,  can read parameter, but can only write IP,PORT,APN parameter
			IEC_Comm.Flag |= PasswordP1OK;
			IEC_Comm.Buf[0] = ACK;
			IEC_Comm.Buf[1] = EndFrame;
			//Ji Zejiang
			IEC_Comm.PassAcc = 4; //
			passerr_count = 0;
		} else {
			//password error
			IEC_Comm.Flag &= ~PasswordP1OK;
			IEC_Comm.Buf[0] = NAK;
			IEC_Comm.Buf[1] = EndFrame;
			//Liao Bin
			IEC_Comm.PassAcc = 0; //
			passerr_count++;
		}
	} else {
		IEC_Comm.Flag &= ~PasswordP1OK;
		IEC_Comm.Buf[0] = NAK;
		IEC_Comm.Buf[1] = EndFrame;
		//Liao Bin
		IEC_Comm.PassAcc = 0; //
		if (passerr_count < 4)
			passerr_count++;
	}
	//it starts the count down of error delay from the first to error inputted
	if ((passerr_count == 1) && (passerr_delaytime == 0)) //
		//delay of 5 minutes
		passerr_delaytime = PASSERRDELAYT; //
	//it starts the count down of error lock  if error inputted for three times
	if ((passerr_count == 3) && (passerr_locktime == 0)) //
		//lock for 30 minutes
		passerr_locktime = PASSERRLOCKT; //
	return (0);
}
//**********************************************************************
//no use of function
//**********************************************************************
/*
 char IEC_CommP2(void)
 {


 Asc_BCDA( (char*)&Buffer[0], (char*)&IEC_Comm.Buf[5], 8);
 FRAM_Read( (char*)&Buffer[4], PassWord+4, 4);
 if ((memcmp((char*)&Buffer[0], (char*)&Buffer[4], 4) == 0)||(FAC_KEY()==0))
 {
 IEC_Comm.Flag |= PassWordP2OK;
 IEC_Comm.Buf[0] = ACK;
 IEC_Comm.Buf[1] = EndFrame;
 }
 else
 {
 IEC_Comm.Flag &= ~PassWordP2OK;
 IEC_Comm.Buf[0] = NAK;
 IEC_Comm.Buf[1] = EndFrame;
 }
 return(0);
 }
 */

//**********************************************************************
//IEC check calculation
// BNTHANG: this funtion compute BCC (Block Character Check)
//**********************************************************************
unsigned char GetCHK(unsigned char * yourBuf, unsigned int StartID,
		unsigned int EndID) {
	unsigned int i;
	unsigned char Tmp = 0x00;
	for (i = StartID; i <= EndID; i++) {
		Tmp ^= *(yourBuf + i);
	}
	return Tmp;
}
//**********************************************************************
//IEC response function
//**********************************************************************
//the first communication data prepare and startup response, firstly responds after connection
void IEC_1stAnswer(void) {
	switch (IEC_Comm.CommMode) {
	//readout mode,no response,leave it for IEC_CommRespond() to handle
	case DataOut: //
		break;
	case Program:
		memcpy(IEC_Comm.Buf, CommPass, sizeof(CommPass));
		/*
		 IEC_Comm.Buf[0] = SOH;
		 IEC_Comm.Buf[1] = 'P'; IEC_Comm.Buf[2]='0';
		 IEC_Comm.Buf[3] = STX;
		 IEC_Comm.Buf[4] = '(';
		 IEC_Comm.Buf[5] = 'H'; IEC_Comm.Buf[6]='X'; IEC_Comm.Buf[7]='G'; IEC_Comm.Buf[8]='P'; IEC_Comm.Buf[9]='R'; IEC_Comm.Buf[10]='S';
		 IEC_Comm.Buf[11] = ')';
		 IEC_Comm.Buf[12] = ETX;
		 IEC_Comm.Buf[13] = GetCHK(IEC_Comm.Buf, 1, 12);
		 IEC_Comm.Buf[14] = EndFrame;
		 */
		IEC_Comm.Mode = 2;
		break;
	case HDLC:
		break;
	case Factory6:
		break;
	case Factory7:
		break;
	case Factory8:
		break;
	case Factory9:
		break;
	}
}

const unsigned char NotSupport[] = { "NOT SUPPORT" };
const unsigned char kWhUnit[] = { "kWh" };
const unsigned char kvarhUnit[] = { "kvarh" };
const unsigned char kVAhUnit[] = { "kVAh" };
//**********************************************************************
//readout mode use, but the readout mode has been canceled
//**********************************************************************
//obtain simplified OBIS from 4 bytes OBIS
void GetASC_OBIS(char *yourBuf, unsigned char *yourID, char *yourOBIS) {
	BCD_Asc((char*) Buffer, (char*) yourOBIS, 4);

	if (Buffer[0] != '0')
		yourBuf[(*yourID)++] = Buffer[0];
	yourBuf[(*yourID)++] = Buffer[1];
	yourBuf[(*yourID)++] = '.';
	if (Buffer[2] != '0')
		yourBuf[(*yourID)++] = Buffer[2];
	yourBuf[(*yourID)++] = Buffer[3];
	yourBuf[(*yourID)++] = '.';
	if (Buffer[4] != '0')
		yourBuf[(*yourID)++] = Buffer[4];
	yourBuf[(*yourID)++] = Buffer[5];
	yourBuf[(*yourID)++] = '*';
	//0xFF indicates no this byte
	if (Buffer[6] == 'F' && Buffer[7] == 'F') //
		yourBuf[--(*yourID)] = 0x00;
	else {
		if (Buffer[6] != '0')
			yourBuf[(*yourID)++] = Buffer[6];
		yourBuf[(*yourID)++] = Buffer[7];
	}
}
//**********************************************************************
//readout mode use, but the readout mode has been canceled
//**********************************************************************
//data readout mode handling
void DataOutRead(void) {
	register unsigned int i;
	unsigned int DaLen;
	unsigned char MemType;
	unsigned char Tmp;
	//*if all the readout mode data has been sent
	if (IEC_Comm.DaOutCnt >= DaOutAllNum) {
		//IEC_Comm.DaOutCnt = 0;
		//IEC_Comm.CommMode = NoCnt;
		IEC_Comm.MdTmr = TM_500ms;
		Flag.Run &= ~R_ComOK;
		IEC_Comm.Mode = 0;
		return;
	}
	DaLen = DaOutTab[IEC_Comm.DaOutCnt].ComInfo & RS_LEN;
	MemType = (DaOutTab[IEC_Comm.DaOutCnt].ComInfo & RS_REG) >> 6;

	Tmp = 0;
	if (IEC_Comm.DaOutCnt == 0) {
		IEC_Comm.Buf[Tmp++] = STX;
		IEC_Comm.BCC = 0x00;
	}

	GetASC_OBIS((char*) IEC_Comm.Buf, &Tmp,
			(char*) &DaOutTab[IEC_Comm.DaOutCnt].ComID); //OBIS

	IEC_Comm.Buf[Tmp++] = '(';
	//read data to Buffer,the longest is considered to be 6 bytes
	MEM_Read(&Buffer[2 * DaLen], (int) DaOutTab[IEC_Comm.DaOutCnt].Addr, DaLen,
			MemType); //
	BCD_Asc((char*) &Buffer[0], (char*) &Buffer[2 * DaLen], DaLen);

	//electricity quantity
	if (IEC_Comm.DaOutCnt < DaOutDL_LEN) //电量
	{
		for (i = 0; i < 8; i++)
			IEC_Comm.Buf[Tmp++] = Buffer[i];

		IEC_Comm.Buf[Tmp++] = '.';
		for (i = 8; i < 10; i++)
			IEC_Comm.Buf[Tmp++] = Buffer[i];

		IEC_Comm.Buf[Tmp++] = '*';
		if (IEC_Comm.DaOutCnt < DaOutDLANum) {
			memcpy(&IEC_Comm.Buf[Tmp], (char*) kWhUnit, 3);
			Tmp += 3;
		} else {
			memcpy(&IEC_Comm.Buf[Tmp], (char*) kvarhUnit, 5);
			Tmp += 5;
		}
	}
	//demand
	else if (IEC_Comm.DaOutCnt < DaOutXL_LEN) //
	{
		for (i = 0; i < 3; i++)
			IEC_Comm.Buf[Tmp++] = Buffer[i];

		IEC_Comm.Buf[Tmp++] = '.';

		for (i = 3; i < 6; i++)
			IEC_Comm.Buf[Tmp++] = Buffer[i];

		IEC_Comm.Buf[Tmp++] = '*';

		if (IEC_Comm.DaOutCnt < DaOutDLNum + DaOutXLANum) {
			memcpy(&IEC_Comm.Buf[Tmp], (char*) kWhUnit, 2);
			Tmp += 2;
		} else {
			memcpy(&IEC_Comm.Buf[Tmp], (char*) kvarhUnit, 4);
			Tmp += 4;
		}
	}
	//voltage current
	else if (IEC_Comm.DaOutCnt < DaOutVI_LEN) //
	{
		//current
		if (IEC_Comm.DaOutCnt < DaOutI_LEN) //
		{
			for (i = 0; i < 4; i++)
				IEC_Comm.Buf[Tmp++] = Buffer[i];

			IEC_Comm.Buf[Tmp++] = '.';

			for (i = 4; i < 6; i++)
				IEC_Comm.Buf[Tmp++] = Buffer[i];

			IEC_Comm.Buf[Tmp++] = '*';
			IEC_Comm.Buf[Tmp++] = 'A';
		}
		//voltage
		else //
		{
			for (i = 0; i < 3; i++)
				IEC_Comm.Buf[Tmp++] = Buffer[i];

			IEC_Comm.Buf[Tmp++] = '.';

			for (i = 3; i < 4; i++)
				IEC_Comm.Buf[Tmp++] = Buffer[i];

			IEC_Comm.Buf[Tmp++] = '*';
			IEC_Comm.Buf[Tmp++] = 'V';
		}
	} else if (IEC_Comm.DaOutCnt < DaOutPW_LEN) {
		//power
		if (IEC_Comm.DaOutCnt < DaOutkVA_LEN) //
		{
			for (i = 0; i < 3; i++)
				IEC_Comm.Buf[Tmp++] = Buffer[i];
			IEC_Comm.Buf[Tmp++] = '.';

			for (i = 3; i < 6; i++)
				IEC_Comm.Buf[Tmp++] = Buffer[i];

			IEC_Comm.Buf[Tmp++] = '*';
			if (IEC_Comm.DaOutCnt < DaOutkW_LEN) //kW
			{
				memcpy(&IEC_Comm.Buf[Tmp], (char*) kWhUnit, 2);
				Tmp += 2;
				if ((Flag.Power_dir & ByteBit[3 - (DaOutkW_LEN
						- IEC_Comm.DaOutCnt)]) != 0x00)
					IEC_Comm.Buf[1]++;
			} else if (IEC_Comm.DaOutCnt < DaOutkvar_LEN) //kvar
			{
				memcpy(&IEC_Comm.Buf[Tmp], (char*) kvarhUnit, 4);
				Tmp += 4;
				if ((Flag.Power_dir & ByteBitTail[3 - (DaOutkvar_LEN
						- IEC_Comm.DaOutCnt)]) != 0x00)
					IEC_Comm.Buf[1]++;
			} else if (IEC_Comm.DaOutCnt < DaOutkVA_LEN) //kVA
			{
				memcpy(&IEC_Comm.Buf[Tmp], (char*) kVAhUnit, 3);
				Tmp += 3;
				if ((Flag.APPA_dir & ByteBit[3 - (DaOutkVA_LEN
						- IEC_Comm.DaOutCnt)]) != 0x00) {
					IEC_Comm.Buf[0]++;
					IEC_Comm.Buf[1] = 0x30;
				}
			}
		} else if (IEC_Comm.DaOutCnt < DaOutPF_LEN) //PF
		{
			for (i = 0; i < 1; i++)
				IEC_Comm.Buf[Tmp++] = Buffer[i];
			IEC_Comm.Buf[Tmp++] = '.';
			for (i = 1; i < 4; i++)
				IEC_Comm.Buf[Tmp++] = Buffer[i];
			IEC_Comm.Buf[Tmp++] = '*';
		}
	}

	IEC_Comm.Buf[Tmp++] = ')';
	IEC_Comm.Buf[Tmp++] = CR;
	IEC_Comm.Buf[Tmp++] = LF;

	IEC_Comm.BCC ^= GetCHK(IEC_Comm.Buf, 0, Tmp - 1);
	IEC_Comm.DaOutCnt++;

	//if it is the last data array+ETX+BBC
	if (IEC_Comm.DaOutCnt == DaOutAllNum) //
	{
		IEC_Comm.Buf[Tmp++] = '!';
		IEC_Comm.Buf[Tmp++] = CR;
		IEC_Comm.Buf[Tmp++] = LF;
		IEC_Comm.Buf[Tmp++] = ETX;
		IEC_Comm.Buf[Tmp++] = IEC_Comm.BCC ^ '!' ^ CR ^ LF ^ ETX ^ STX;
	}
	IEC_Comm.Buf[Tmp] = EndFrame;
	IEC_Comm.Mode = 2;
}

//**********************************************************************
//IEC protocol  command performace
//**********************************************************************
char IEC_CommReadE1(void) {
	unsigned int ID;
	char RLT = 0x00;

	//need to enter into program mode
	if (IEC_Comm.Flag & DeviceOMIT) {
		RLT = 0x01;
		IEC_Comm.Buf[0] = RLT != 0x00 ? NAK : ACK;
		IEC_Comm.Buf[1] = EndFrame;
		return (RLT);
	}

	Asc_BCD((char*) &ID, (char*) &IEC_Comm.Buf[4], 4);
	switch (ID) {
	//zero clearing of total
	case 0xF00A: //
		RLT = 0x01;
		//factory no use
		if (FAC_KEY() == 0x00) //
		{
			Flag.ClearAllData = 0xAA;
			RLT = 0x00;
		}
		break;
		//put out production mode
	case 0xF0EE:
		RLT = 0x00;
		gFactMode = 0;
		E2P_Write(FACT_MODE, (char*) &gFactMode, 2);
		break;
		//electricity quantity settlement(include demand)
	case 0xF0F1: //
		if ((RunDly.DLBillDely < DLBillDelyTM) || (RunDly.PowerDely
				< PowerDelyTM)) {
			RLT = 0x01;
		} else {
#ifdef NO_FRAM
			E_Read((char *) &Buffer[0], BillingDate, 1);
#else
			FRAM_Read((char *) &Buffer[0], BillingDate, 1);
#endif
			if (Buffer[0] <= 0x28) {
				RLT = 0x01;
			} else {
				Flag.Fee |= F_BillAll;
			}
		}
		break;
		//demand settlement
	case 0xF0F2: //
		if ((RunDly.MBillDely < MBillDelyTM)
				|| (RunDly.PowerDely < PowerDelyTM)) {
			RLT = 0x01;
		} else {
			Flag.Fee |= F_BillMD;
		}
		//it is main invoke MEM _Clr to clear two more bytes everytime
		break; //
		//clear power on,power off events
	case 0xF0F3: //
		//clear power on and down events
		MEM_Clr(EVENT_POFF_PTR, 300, Mem_FRAM); //清上掉电事件
		break;
		//clear program events
	case 0xF0F4: //
		//clear events
		MEM_Clr(EVENT_PROG_PTR, 150, Mem_FRAM); //清事件
		break;
		//clear time modification events
	case 0xF0F5: //
		//clear events
		MEM_Clr(EVENT_MDF_TIME, 25 + 14, Mem_E2PROM); //清事件
		break;
		//clear zero clearing events
	case 0xF0F6: //
		//clear events
		MEM_Clr(EVENT_RST_CLR, 53, Mem_E2PROM); //清事件
		break;
	default:
		RLT = 0xFF;
		break;
	}

	IEC_Comm.Buf[0] = RLT != 0x00 ? NAK : ACK;
	IEC_Comm.Buf[1] = EndFrame;

	return (RLT);
}

extern unsigned char net_rest_time;

extern unsigned int InvalidCLK(unsigned char *cCLK);
//**********************************************************************
//IEC read data
//**********************************************************************
char IEC_CommReadW1(void) {
	unsigned int ID, Addr, Info, Len;
	register unsigned int i;
	char MemType;
	unsigned int uintTmp;
	unsigned long ulTmp;
	int Ptr;

	Asc_BCD((char*) &ID, (char*) &IEC_Comm.Buf[4], 4);

	//no program limitation when reading load curve and writing IP,port,APN,RF parameter
	if (((ID > 0xD300) && (ID < 0xD303)) || (ID == 0xD31F) || (ID == 0xC105)
			|| (ID == 0xC108) || (ID == 0xC106) || (ID == 0xC107) || (ID
			== 0xC109) || (ID == 0xC10A)) {

	} else {
		if ((IEC_Comm.Flag & DeviceOMIT) && (IEC_Comm.ComId != 2))// if (IEC_Comm.Flag & DeviceOMIT)
		//if (0)
		{
			NOTPERMIT: IEC_Comm.Buf[0] = NAK;
			IEC_Comm.Buf[1] = EndFrame;
			return (0);
		}
	}

	//20111228Liao Bin 20150630 amended by Ji Zejiang
	//C001:write time
	//D301:load curve channel number
	//D302:load curve read pointer
	//D31F:write load curve time intervals
	//D301\D302\D31F:it can be write only if the password is correct
	//the level 2 password only can write the time
	if (IEC_Comm.PassAcc == 2) //
	{
		if (ID == 0xC001) {
			//write time
			goto ID_WRITE;
		} else if ((ID == 0xD301) || (ID == 0xD302) || (ID == 0xD31F)) {
		} else {
			goto NOTPERMIT;
		}
	}
	//the new added level 4 password can only write IP,port,APN,RF parameter
	if (IEC_Comm.PassAcc == 4) //
	{
		if ((ID >= 0xC105) && (ID <= 0xC10A)) {
			//write parameter
			goto ID_WRITE;
		} else if ((ID == 0xD301) || (ID == 0xD302) || (ID == 0xD31F)) {
		} else {
			goto NOTPERMIT;
		}
	}
	if (
	//level 1,2 password can only write time
	((IEC_Comm.PassAcc == 2) || (IEC_Comm.PassAcc == 1)) //
			&& ((ID != 0xD31F) && (ID != 0xD301) && (ID != 0xD302))) {
		goto NOTPERMIT;
	}

	//meter calibration must under factory mode
	if ((ID <= 0x2015) && (ID >= 0x2000)) //
	{
		if (FAC_KEY())
			goto NOTPERMIT;
	}

	switch (ID) {
	case 0xF0EE:
		Asc_BCD((char*) &Buffer[0], (char*) &IEC_Comm.Buf[9], 4);
		if (FAC_KEY()) {
			goto NOTPERMIT;
		}
		//factory mode 0xf001
		E2P_Write(FACT_MODE, (char*) &Buffer[0], 2);
		E2P_Read((char*) &gFactMode, FACT_MODE, 2);
		break;
		//load curve
		//write channel code
	case 0xD301: //
		Asc_BCDA((char*) &Buffer[0], (char*) &IEC_Comm.Buf[9], 2);
		if (Buffer[0] > 7)
			goto NOTPERMIT;
		else {
			EevenLPPtr.LoadProCh = Buffer[0];
			FRAM_Read((char*) &Ptr,
			RecPtr1_ + SIZE_LoadINFORUN * EevenLPPtr.LoadProCh, 2);
			if (Ptr > 0)
				Ptr--;
			else {
				FRAM_Read((char*) &Ptr,
				MaxRecNUM1_ + SIZE_LoadINFO * EevenLPPtr.LoadProCh, 2);
				Ptr -= 1;
			}

			if (EevenLPPtr.LoadProCh >= LP_MaxChNum) {
				EevenLPPtr.LoadProCh = 0;
			}

			MEM_DBWrite(ReadPtr1_ + SIZE_LoadINFORUN * EevenLPPtr.LoadProCh,
					(char*) &Ptr, 2, Mem_FRAM);

		}
		break;

		//load table read operation pointer
	case 0xD302: //
		Asc_BCD((char*) &Buffer[0], (char*) &IEC_Comm.Buf[9], 4);
		Ptr = Buffer[1] * 0x100 + Buffer[0];

		if (EevenLPPtr.LoadProCh >= LP_MaxChNum) {
			EevenLPPtr.LoadProCh = 0;
		}

		MEM_DBWrite( ReadPtr1_ + SIZE_LoadINFORUN * EevenLPPtr.LoadProCh,
				(char*) &Ptr, 2, Mem_FRAM);

		break;
		//load table register code(7Reg+Num)
	case 0xD304: //
		Asc_BCDA((char*) &Buffer[0], (char*) &IEC_Comm.Buf[9], 16);

		if (EevenLPPtr.LoadProCh >= LP_MaxChNum) {
			EevenLPPtr.LoadProCh = 0;
		}

		MEM_DBWrite( RegNUM1_ + SIZE_LoadINFO * EevenLPPtr.LoadProCh,
				&Buffer[0], 8, Mem_FRAM);
		//reset corresponding channel
		memset(&Buffer[0], 0x00, SIZE_LoadINFORUN); //
		MEM_DBWrite(LoadInfoRun_ + SIZE_LoadINFORUN * EevenLPPtr.LoadProCh,
				&Buffer[0], SIZE_LoadINFORUN, Mem_FRAM);
		break;
		//record time intervals
	case 0xD305: //
		Asc_BCD((char*) &Buffer[0], (char*) &IEC_Comm.Buf[9], 4);

		if (EevenLPPtr.LoadProCh >= LP_MaxChNum) {
			EevenLPPtr.LoadProCh = 0;
		}

		MEM_DBWrite( TimeInv1_ + SIZE_LoadINFO * EevenLPPtr.LoadProCh,
				&Buffer[0], 2, Mem_FRAM);
		break;
		//load table record capacity(piece)
	case 0xD306: //
		//factory no use
		if (FAC_KEY() != 0x00) //
			goto NOTPERMIT;
		Asc_BCD((char*) &Buffer[0], (char*) &IEC_Comm.Buf[9], 4);

		if (EevenLPPtr.LoadProCh >= LP_MaxChNum) {
			EevenLPPtr.LoadProCh = 0;
		}

		MEM_DBWrite( MaxRecNUM1_ + SIZE_LoadINFO * EevenLPPtr.LoadProCh,
				&Buffer[0], 2, Mem_FRAM);
		break;
		//distribution of data block address
	case 0xD307: //
		//factory no use
		if (FAC_KEY() != 0x00) //
			goto NOTPERMIT;

		Asc_BCD((char*) &Buffer[0], (char*) &IEC_Comm.Buf[9], 8);

		memcpy((char*) &ulTmp, Buffer, 4);
		//addone start address
		ulTmp += LOADCURVE; //
		memcpy(Buffer, (char*) &ulTmp, 4);

		if (EevenLPPtr.LoadProCh >= LP_MaxChNum) {
			EevenLPPtr.LoadProCh = 0;
		}

		MEM_DBWrite( RecAddr1_ + SIZE_LoadINFO * EevenLPPtr.LoadProCh,
				&Buffer[0], 4, Mem_FRAM);
		break;
		//reset load table
	case 0xD30F: //
		memset(&Buffer[0], 0x00, 48);
		MEM_DBWrite(LoadInfoRun_, &Buffer[0], 48, Mem_FRAM);

		FRAM_Write(LOAD_DATE_SET_COUNT, &Buffer[0], 48);
		// FRAM_Write(LOAD_DATE_R_COUNT,&Buffer[0], 1);

		break;

	case 0xD31F: {
		unsigned int lc_max = 0;
		unsigned int lc_curr = 0;
		unsigned char lc_f = 0;
		unsigned int i = 0;
		unsigned int s_rec = 0;
		unsigned int e_rec = 0;
		unsigned long long day_c = 0;
		unsigned long long day_f = 0;
		unsigned long long day_d = 0;

		//if the end time less than start time
		Asc_BCDA((char*) &Buffer[0], (char*) &IEC_Comm.Buf[9], 12); //
		if ((((unsigned long long) Buffer[0]) * 1000
				+ ((unsigned long long) Buffer[1]) * 0x31
				+ ((unsigned long long) Buffer[2]))
				<= (((unsigned long long) Buffer[3]) * 1000
						+ ((unsigned long long) Buffer[4]) * 0x31
						+ ((unsigned long long) Buffer[5]))) {

			/*if((Buffer[0] == Buffer[3])
			 &&(Buffer[1] == Buffer[4])
			 //add 1 to the day next the date
			 &&(Buffer[2] == Buffer[5]))*///
			{
				Buffer[5] = BCD_Byte(Buffer[5]);
				Buffer[4] = BCD_Byte(Buffer[4]);
				Buffer[3] = BCD_Byte(Buffer[3]);
				Buffer[5] += 1;
				if (((Buffer[4] == 4) || (Buffer[4] == 6) || (Buffer[4] == 9)
				//a solar month of 30days
						|| (Buffer[4] == 11))) //
				{
					if ((Buffer[5] > 30)) {
						Buffer[5] = 1;
						Buffer[4] += 1;
						if (Buffer[4] > 12) {
							Buffer[4] = 1;
							Buffer[3] += 1;
						}
					}
				} else if (Buffer[4] == 2) {
					if (
					//leap year
					(Buffer[3] & 0x03) == 0x00 //
					) {
						if ((Buffer[5] > 29)) {
							Buffer[5] = 1;
							Buffer[4] += 1;
							if (Buffer[4] > 12) {
								Buffer[4] = 1;
								Buffer[3] += 1;
							}
						}
					} else if (
					//not leap year
					(Buffer[3] & 0x03) != 0x00 //
					) {
						if ((Buffer[5] > 28)) {
							Buffer[5] = 1;
							Buffer[4] += 1;
							if (Buffer[4] > 12) {
								Buffer[4] = 1;
								Buffer[3] += 1;
							}
						}
					}
				}
				//a solar month of 31 days
				else //
				{
					if ((Buffer[5] > 31)) {
						Buffer[5] = 1;
						Buffer[4] += 1;
						if (Buffer[4] > 12) {
							Buffer[4] = 1;
							Buffer[3] += 1;
						}
					}
				}
				Buffer[5] = Byte_BCD(Buffer[5]);
				Buffer[4] = Byte_BCD(Buffer[4]);
				Buffer[3] = Byte_BCD(Buffer[3]);
			}

			FRAM_Read((char *) &Buffer[10], LOAD_DATE_C_COUNT, 4);
			lc_curr = (((unsigned int) Buffer[10]) << 8)
					| (((unsigned int) Buffer[11]) & 0x00FF);
			lc_max = (((unsigned int) Buffer[12]) << 8)
					| (((unsigned int) Buffer[13]) & 0x00FF);
			if (lc_max != lc_curr) {
				FRAM_Read((char *) &Buffer[20], LOAD_DATE_DATA + lc_curr * 5, 5);
			} else {
				FRAM_Read((char *) &Buffer[20], LOAD_DATE_DATA, 5);
			}
			day_c = ((((unsigned long long) Buffer[20]) * 1000)
					+ (((unsigned long long) Buffer[21]) * 0x31)
					+ ((unsigned long long) Buffer[22]));
			day_f = (((((unsigned long long) Buffer[0]) * 1000)
					+ (((unsigned long long) Buffer[1]) * 0x31)
					+ ((unsigned long long) Buffer[2])));
			//if start date<earliest record date

			if (day_c > day_f) //
			{
				s_rec = (((unsigned int) Buffer[23]) << 8)
						| (((unsigned int) Buffer[24]) & 0x00FF);
				if (s_rec > 0) {
					s_rec--;
				}
				lc_f |= 0x01;
			}
			if (lc_max > LOAD_DATE_MAX) {
				lc_max = 0;
			}
			for (i = 0; i < lc_max; i++) {
				FRAM_Read((char *) &Buffer[30], LOAD_DATE_DATA + i * 5, 10);
				if ((lc_f & 0x01) != 0x01) {
					if ((Buffer[2] == Buffer[32]) && (Buffer[1] == Buffer[31])
							&& (Buffer[0] == Buffer[30])) {
						//FRAM_Read( (char *)&Buffer[23], LOAD_DATE_DATA+i*5+3, 2);
						s_rec = (((unsigned int) Buffer[33]) << 8)
								| (((unsigned int) Buffer[34]) & 0x00FF);
						if (s_rec > 0) {
							s_rec--;
						}
						lc_f |= 0x01;
						//if the start date is today
						if ((Buffer[0] == Clk.Year[0]) && (Buffer[1]
								== Clk.Mon[0]) && (Buffer[2] == Clk.Day[0])) //
						{
							FRAM_Read(
									&Buffer[33],
									RecNUM1_ + SIZE_LoadINFORUN
											* EevenLPPtr.LoadProCh + 2, 2);
							e_rec = (((unsigned int) Buffer[34]) << 8)
									| (((unsigned int) Buffer[33]) & 0x00FF);

							if (e_rec > s_rec) {
								//e_rec--;
							}
							lc_f |= 0x02;
						}
					} else if ((Buffer[2] == Buffer[37]) && (Buffer[1]
							== Buffer[36]) && (Buffer[0] == Buffer[35])) {
						s_rec = (((unsigned int) Buffer[38]) << 8)
								| (((unsigned int) Buffer[39]) & 0x00FF);
						if (s_rec > 0) {
							s_rec--;
						}
						lc_f |= 0x01;
						//if the start date is today
						if ((Buffer[0] == Clk.Year[0]) && (Buffer[1]
								== Clk.Mon[0]) && (Buffer[2] == Clk.Day[0])) //
						{
							FRAM_Read(
									&Buffer[33],
									RecNUM1_ + SIZE_LoadINFORUN
											* EevenLPPtr.LoadProCh + 2, 2);
							e_rec = (((unsigned int) Buffer[34]) << 8)
									| (((unsigned int) Buffer[33]) & 0x00FF);
							if (e_rec > s_rec) {
								//e_rec--;
							}
							lc_f |= 0x02;
						}
					} else if (((((unsigned long long) Buffer[0]) * 1000
							+ ((unsigned long long) Buffer[1]) * 0x31
							+ ((unsigned long long) Buffer[2]))
							> (((unsigned long long) Buffer[30]) * 1000
									+ ((unsigned long long) Buffer[31]) * 0x31
									+ ((unsigned long long) Buffer[32])))
							&& ((((unsigned long long) Buffer[0]) * 1000
									+ ((unsigned long long) Buffer[1]) * 0x31
									+ ((unsigned long long) Buffer[2]))
									< (((unsigned long long) Buffer[35]) * 1000
											+ ((unsigned long long) Buffer[36])
													* 0x31
											+ ((unsigned long long) Buffer[37])))) {
						s_rec = (((unsigned int) Buffer[38]) << 8)
								| (((unsigned int) Buffer[39]) & 0x00FF);
						if (s_rec > 0) {
							s_rec--;
						}
						lc_f |= 0x01;
					}
				}
				if ((lc_f & 0x02) != 0x02) {
					day_c = ((((unsigned long long) Buffer[3]) * 1000)
							+ (((unsigned long long) Buffer[4]) * 0x31)
							+ (((unsigned long long) Buffer[5])));
					day_f = ((((unsigned long long) Buffer[30]) * 1000)
							+ (((unsigned long long) Buffer[31]) * 0x31)
							+ (((unsigned long long) Buffer[32])));
					day_d = ((((unsigned long long) Buffer[35]) * 1000)
							+ (((unsigned long long) Buffer[36]) * 0x31)
							+ (((unsigned long long) Buffer[37])));
					if ((Buffer[5] == Buffer[32]) && (Buffer[4] == Buffer[31])
							&& (Buffer[3] == Buffer[30])) {
						{
							//FRAM_Read( (char *)&Buffer[23], LOAD_DATE_DATA+i*5+3, 2);
							e_rec = (((unsigned int) Buffer[33]) << 8)
									| (((unsigned int) Buffer[34]) & 0x00FF);
							e_rec--;
						}
						//if(i>0)e_rec--;
						lc_f |= 0x02;
					} else if ((Buffer[5] == Buffer[37]) && (Buffer[4]
							== Buffer[36]) && (Buffer[3] == Buffer[35])) {
						{
							//FRAM_Read( (char *)&Buffer[23], LOAD_DATE_DATA+i*5+3, 2);
							e_rec = (((unsigned int) Buffer[38]) << 8)
									| (((unsigned int) Buffer[39]) & 0x00FF);
							e_rec--;
						}
						//if(i>0)e_rec--;
						lc_f |= 0x02;
					}
					/*
					 else if(
					 (((((unsigned long)Buffer[3])*365) + (((unsigned long)Buffer[4])*31)+(((unsigned long)Buffer[5]))) > ((((unsigned long)Buffer[20])*365) + (((unsigned long)Buffer[21])*31)+(((unsigned long)Buffer[22]))))
					 &&
					 (((((unsigned long)Buffer[3])*365) + (((unsigned long)Buffer[4])*31)+(((unsigned long)Buffer[5]))) < ((((unsigned long)Buffer[25])*365) + (((unsigned long)Buffer[26])*31)+(((unsigned long)Buffer[27]))))
					 )*/
					else if (((day_c > day_f) && (day_c < day_d)) && (i
							< (lc_max - 1))) {
						e_rec = (((unsigned int) Buffer[38]) << 8)
								| (((unsigned int) Buffer[39]) & 0x00FF);
						// if(i>0)e_rec--;
						e_rec--;
						lc_f |= 0x02;
					}
				}
				//i+=1;
			}
			if ((lc_f & 0x02) != 0x02) {
				if ((((unsigned long long) Clk.Year[0]) * 1000
						+ ((unsigned long long) Clk.Mon[0]) * 0x31
						+ ((unsigned long long) Clk.Day[0]))
				//the end date bigger than today
						<= //
						(((unsigned long long) Buffer[3]) * 1000
								+ ((unsigned long long) Buffer[4]) * 0x31
								+ ((unsigned long long) Buffer[5]))) {
					FRAM_Read(&Buffer[23],
					RecNUM1_ + SIZE_LoadINFORUN * EevenLPPtr.LoadProCh + 2, 2);
					e_rec = (((unsigned int) Buffer[24]) << 8)
							| (((unsigned int) Buffer[23]) & 0x00FF);
					//e_rec--;
					lc_f |= 0x02;
				}
			}
			if ((e_rec == 0) && (s_rec > 0)) {
				FRAM_Read(&Buffer[23],
				RecNUM1_ + SIZE_LoadINFORUN * EevenLPPtr.LoadProCh + 2, 2);
				e_rec = (((unsigned int) Buffer[24]) << 8)
						| (((unsigned int) Buffer[23]) & 0x00FF);
				//e_rec--;
				lc_f |= 0x02;
			}
			if ((lc_f & 0x03) == 0x03) {
				if (e_rec >= s_rec) {
					s_rec = e_rec - s_rec;
				} else {
					unsigned int max_len = 0;
					FRAM_Read(&Buffer[25],
					MaxRecNUM1_ + SIZE_LoadINFO * EevenLPPtr.LoadProCh, 2);
					max_len = (((unsigned int) Buffer[26]) << 8)
							| (((unsigned int) Buffer[25]) & 0x00FF);
					s_rec = e_rec + max_len - s_rec;
				}
			} else {
				s_rec = 0;
				e_rec = 0;
			}
		}
		if (e_rec > 0) {
			e_rec--;
		}
		Buffer[0] = (unsigned char) (e_rec >> 8);
		Buffer[1] = (unsigned char) (e_rec & 0x00FF);
		Buffer[2] = (unsigned char) (s_rec >> 8);
		Buffer[3] = (unsigned char) (s_rec & 0x00FF);
		FRAM_Write(LOAD_DATE_SET_COUNT, &Buffer[0], 4);
		break;
	}

		//clock correction factor
	case 0xE106: //
		Asc_BCD((char*) &Buffer[0], (char*) &IEC_Comm.Buf[9], 8);
		MEM_DBWrite(CLK_GENE, (char*) &Buffer[0], 4, Mem_FRAM);

		Init_CLK_Gene();
		break;

	case 0xC100: //Device Addr id save here
		Addr = DeviceAddr;
		Len = 32;
		MemType = Mem_FRAM;

		for (i = 0; i < 12; i++) {
			Buffer[i] = '0';
		}
		memcpy(&Buffer[0], &IEC_Comm.Buf[9], 12);

#ifdef SINGLE_PHASE_MULTI_TARIFF
		memcpy(Buffer, &IEC_Comm.Buf[9], 12);
		MemType = Mem_E2PROM;
		MEM_Write(Addr, (char*) &Buffer[0], 12, MemType);

#else
		memcpy(Buffer, &IEC_Comm.Buf[9], 12);
		MemType = Mem_FRAM;
		MEM_Write(Addr, (char*) &Buffer[0], 12, MemType);
#endif
		break;
	default:
		//Liao Bin 20111228
		ID_WRITE: //
		//look up communication list
		//
		for (i = 0; i < CommNum; i++) {
			if (ID == CommTab[i].ComID) {
				Addr = (unsigned int) CommTab[i].Addr;
				Info = CommTab[i].ComInfo;
				Len = Info & RS_LEN;
				MemType = (Info >> 6) & 0x07;
				break;
			}
		}
		if (i >= CommNum)
			return (0xFF);
		if ((Info & (EN_FSw | EN_W)) == 0x0000)
			goto NOTPERMIT;

		switch (ID) {
		case 0xE0A0:
		case 0xE0B0:
		case 0xE0C0:
		case 0xE0D0:
		case 0xE0E0:
		case 0xE0E1:
		case 0xE0E2:
		case 0xE0E3:
		case 0xE0E4:
		case 0xE0E5:
		case 0xE0E6:
		case 0xE0E7:
		case 0xE105:
			//all are one byte HEX such as 32 30 34 indicate 204 turn to  Hex is 0xCC
			IEC_Comm.Buf[IEC_Comm.Ptr - 3] = 0x00;
			// Buffer[0] = atoi( (char *)&IEC_Comm.Buf[9] );
			MEM_Write(Addr, (char*) &Buffer, Len, MemType);
			break;
		default:
#if 0        
			//meter calibration
			if ((ID <= 0x202F) && (ID>=0x2000))//校表
			if ( (P2IN & P_SW) != 0x00 )
			goto NOTPERMIT;
#endif                    

			//if set PT CT parameter to record the total electricity quantity data before amendment
			if (ID == 0xA080) //
			{
				MEM_MEM( CTPTCHANGE2, CTPTCHANGE1, 31, Mem_E2PROM);
				MEM_MEM( CTPTCHANGE2 + E2P_BAK, CTPTCHANGE1 + E2P_BAK, 31,
						Mem_E2PROM);

				memcpy((char*) &Buffer[0], Clk.Min, 5);
#ifdef SINGLE_PHASE_MULTI_TARIFF
				MemType = Mem_E2PROM;
				E2P_Read((char*) &Buffer[5], PARA_PTCT, 8);
				E2P_Read((char*) &Buffer[13], EC_Pp0, 4);
				E2P_Read((char*) &Buffer[17], EC_Pn0, 4);
				E2P_Read((char*) &Buffer[21], EC_Rp0, 4);
				E2P_Read((char*) &Buffer[25], EC_Rn0, 4);
#else
				FRAM_Read((char*) &Buffer[5], PARA_PTCT, 8);
				FRAM_Read((char*) &Buffer[13], EC_Pp0, 4);
				FRAM_Read((char*) &Buffer[17], EC_Pn0, 4);
				FRAM_Read((char*) &Buffer[21], EC_Rp0, 4);
				FRAM_Read((char*) &Buffer[25], EC_Rn0, 4);
#endif
				MEM_DBWrite(CTPTCHANGE1, (char*) &Buffer[0], 29, Mem_E2PROM);
			}

			//meter calibration parameter, it must be operated under factory mode
			//
			if (ID >= 0x2000 && ID <= 0x2015) {
#ifdef SINGLE_PHASE_MULTI_TARIFF
				if (ID == 0x200A) {
					Asc_BCDA((char*) &rn8209a_calib.I_CAL[2],
							(char*) &IEC_Comm.Buf[9], 4);
					rn8209a_calib.ID_IEC[rn8209a_calib.count_id] = ID;
					rn8209a_calib.count_id++;
				}
				if (ID == 0x200B) {
					Asc_BCDA((char*) &rn8209a_calib.V_CAL[2],
							(char*) &IEC_Comm.Buf[9], 4);
					rn8209a_calib.ID_IEC[rn8209a_calib.count_id] = ID;
					rn8209a_calib.count_id++;
				}
				if (ID == 0x200C) {
					Asc_BCDA((char*) &rn8209a_calib.P_RMS[2],
							(char*) &IEC_Comm.Buf[9], 4);
					rn8209a_calib.ID_IEC[rn8209a_calib.count_id] = ID;
					rn8209a_calib.count_id++;
				}
				if ((ID == 0x2003) && (rn8209a_calib.count_id == 3)) {
					Asc_BCDA((char*) &rn8209a_calib.P_Cal_10L[2],
							(char*) &IEC_Comm.Buf[9], 4);

					rn8209a_calib.ID_IEC[rn8209a_calib.count_id] = ID;
					rn8209a_calib.count_id = 0;
					rn8209a_calib.Status_Cal = 1;
					goto next;
				}
				if ((ID == 0x2003) && (rn8209a_calib.count_id == 0)) {
					Asc_BCDA((char*) &rn8209a_calib.P_Cal_10L[2],
							(char*) &IEC_Comm.Buf[9], 4);
					rn8209a_calib.ID_IEC[0] = ID;
					rn8209a_calib.Status_Cal = 2;
					goto next;
				}
				if ((ID == 0x2004) && (rn8209a_calib.count_id == 0)) {
					Asc_BCDA((char*) &rn8209a_calib.P_Cal_05L[2],
							(char*) &IEC_Comm.Buf[9], 4);
					rn8209a_calib.ID_IEC[0] = ID;
					rn8209a_calib.Status_Cal = 3;
					goto next;
				}
				if ((ID == 0x2005) && (rn8209a_calib.count_id == 0)) {
					Asc_BCDA((char*) &rn8209a_calib.P_Cal_10LM[2],
							(char*) &IEC_Comm.Buf[9], 4);
					rn8209a_calib.ID_IEC[0] = ID;
					rn8209a_calib.Status_Cal = 4;
					goto next;
				}
				if (rn8209a_calib.count_id >= 4) {
					rn8209a_calib.Status_Cal = 1;
					goto next;
				}
				next:
#endif
				E2P_Read((char*) &gFactMode, FACT_MODE, 2);
				if (gFactMode != 0xF001) {
					//goto NOTPERMIT;
				}
				Asc_BCDA((char*) &Buffer[0], (char*) &IEC_Comm.Buf[9], Len << 1);
			}

			//electricity quantity demand time <=0xA052 event parameter
			else if ((ID <= 0xC001) && (ID > 0x2030)) //
				Asc_BCD((char*) &Buffer[0], (char*) &IEC_Comm.Buf[9], Len << 1);
			//parameter
			else
				//
				Asc_BCDA((char*) &Buffer[0], (char*) &IEC_Comm.Buf[9], Len << 1);

			MEM_Write(Addr, (char*) &Buffer[0], Len, MemType);
			MEM_Write(Addr, (char*) &Buffer[0], Len, MemType);
			MEM_Write(Addr, (char*) &Buffer[0], Len, MemType);

			//if it is PT CT numerator and denominator, calculate PCT PT CT
			if (ID == 0xA080) //
			{
				/*
				 float fltTmp, fltTmpB;
				 long lngTmp1, lngTmp2;
				 //CT
				 reg = BCD2_Word((unsigned char*)&Buffer[0]);
				 uintTmp = BCD2_Word((unsigned char*)&Buffer[2]);
				 lngTmp1 = reg;
				 lngTmp2 = uintTmp;
				 fltTmp = reg;
				 fltTmp = fltTmp/uintTmp;
				 reg = BCD2_Word((unsigned char*)&Buffer[4]);
				 uintTmp = BCD2_Word((unsigned char*)&Buffer[6]);
				 fltTmpB = i;
				 fltTmpB = fltTmpB/uintTmp;
				 FRAM_Write( PARA_PTCT+12, (char*)&fltTmp, 4);
				 FRAM_Write( PARA_PTCT+16, (char*)&fltTmpB, 4);

				 lngTmp1 *= reg;
				 lngTmp2 *= uintTmp;
				 fltTmp = lngTmp1;
				 fltTmp = fltTmp/lngTmp2;
				 FRAM_Write( PARA_PTCT+8, (char*)&fltTmp, 4);
				 */
			}
			break;
		}
		break;
	}

	if ((ID == 0xC100) || (ID == 0xC105) || (ID == 0xC106) || (ID == 0xC107)
			|| (ID == 0xC108) || (ID == 0xC109) || (ID == 0xC10A)) {
		//P5OUT&=~BIT1;
		net_rest_time = 3;
		//P5OUT^=BIT1;

	}

	//ReCheck and write backup
	for (i = 0; i < ChkTabNum; i++) {
		if ((Addr >= (unsigned long) ChkTab[i].BlkAddr && Addr
				< (unsigned long) ChkTab[i].BlkAddr + ChkTab[i].Lenth)
				&& (MemType == ((ChkTab[i].Type >> 5) & 0x07))) {
			uintTmp = ChkMem((unsigned long) ChkTab[i].BlkAddr,
					ChkTab[i].Lenth, MemType);
			MEM_Write((unsigned int) ChkTab[i].BlkAddr + ChkTab[i].Lenth,
					(char*) &uintTmp, 2, MemType);

			if (MemBakTab[MemType] != 0x00000000) {
				MEM_MEM(Addr + MemBakTab[MemType], Addr, Len, MemType);
				MEM_Write(
						(unsigned int) ChkTab[i].BlkAddr + ChkTab[i].Lenth
								+ MemBakTab[MemType], (char*) &uintTmp, 2,
						MemType);
			}
			break;
		}
	}
	if (ID == 0xC711) {
		E2P_Read((char*) &display_mod, SysSW, 1);
	}

	if (ID == 0xC111)
		MDParaInit();
	else if (ID == 0xE101) {
		FRAM_Read(&Flag.PortDf, PortDefine, 1);
	} else if ((ID >= 0xE102) && (ID <= 0xE104)) {
		//active/reactive metering method  electricity quantity accumulating calculation method
		FRAM_Read((char*) &gsAttPara.Mode[0], kWCumuMode, 3); //
	} else if (ID == 0xE105) {
		//Get_ShutDispTm();
	} else if ((ID <= 0x201F) && ID >= 0x2000) //((ID <=0x202F) && ID>=0x2000)20150124
	{
		// set meter calibration parameter , need to initialize  metering chip
		gsAttPara.InvalidPowerOnRead = 5;
	}
	//set time
	else if (ID == 0xC001) //
	{
		//clock setting error
		if (InvalidCLK((unsigned char*) &Clk.Sec[0]) == 0x0001) //时钟设置错误
		{
			unsigned char buf[7];
			//read clock
			RX8025_Read(buf, 0, 7);
			Clk.Sec[0] = buf[0];
			Clk.Min[0] = buf[1];
			Clk.Hour[0] = buf[2];
			Clk.Day[0] = buf[4];
			Clk.Mon[0] = buf[5];
			Clk.Year[0] = buf[6];
			Clk.Week[0] = buf[3];
			//calculate correction code
			Clk.Check = ChkNum(&Clk.Min[0], 6);
		}
		//clock setting correct
		else //
		{
			Clk.Check = ChkNum(Clk.Min, 6);
			FRAM_Write( ClockBuf, (char*) Clk.Min, 8);
			FRAM_Write( ClockBuf + FRAMBAK, (char*) Clk.Min, 8);
			MDParaInit();

			//write clock
			{
				unsigned char buf[7];
				buf[0] = Clk.Sec[0];
				buf[1] = Clk.Min[0];
				buf[2] = Clk.Hour[0];
				buf[4] = Clk.Day[0];
				buf[5] = Clk.Mon[0];
				buf[6] = Clk.Year[0];
				buf[3] = Clk.Week[0];
				RX8025_Write(0, buf, 7);
			}
			//record time amendment times
			{
				unsigned int time_count = 0;
				E2P_Read((char*) &time_count, EVENT_MDF_TIME_COUNT, 2);
				time_count++;
				if (time_count == 0)
					time_count = 1;
				E2P_Write(EVENT_MDF_TIME_COUNT, (char*) &time_count, 2);
				time_count = (time_count - 1) % 5;
				E2P_Read((char*) &Buffer[0], EVENT_MDF_TIME_DATA, 21 + 14);
				memcpy(Buffer + 21 + 14, (char*) &Clk.Sec[0], 7);
				E2P_Write(EVENT_MDF_TIME_DATA, Buffer + 7, 21 + 14);
			}

		}
	}
	//decimal places and unit setting
	else if (ID == 0xC710) //
	{
		E2P_Read((char*) &DOT[0], EnDot, 2);
	} else if (ID == 0xC713) {
		E2P_Read((char*) &BillDely[0], _MBillDelyTM, 2);
		//FRAM_Read((char*) &BillDely[0], _MBillDelyTM, 2);
	} else if (ID == 0xE107) {
		E2P_Read((char*) &PowerDnDisp, PowerDnDisp_, 1);
		//FRAM_Read((char*) &PowerDnDisp, PowerDnDisp_, 1);
	}

	if ((ID != 0xD301) && (ID != 0xD302) && (ID != 0xC001) && (ID != 0xD31F)) {
		//mark the update symbol of tariff table->set any parameter
		Flag.Run |= R_FeeTbChg; //
		RunDly.FeeTbDely = 0;
	}
	IEC_Comm.Buf[0] = ACK;
	IEC_Comm.Buf[1] = EndFrame;

	return (0);
}

/******************************************************************
 //function:to prepare the response data for reading the command
 //parameter: no
 //return value:0x00=normal response  0x01= under waiting state  0xFF=the read command is not supported
 ******************************************************************/
char IEC_CommReadR1(void) {
	unsigned long ulTmp;
	unsigned long Addr;
	unsigned int ii;
	unsigned int ID, Info, Len = 0xFFFF;
	register unsigned int i;
	char MemType;
	unsigned char *chrPtr;
	unsigned char EVENT_Ptr;
	// unsigned char LMPtr;//,ucLMNum;

	Asc_BCD((char*) &ID, (char*) &IEC_Comm.Buf[4], 4);
	switch (ID) {
	//frozen times
	case 0xD200:
		Len = 2;
		FRAM_Read(Buffer, BILLCnt, 2);
		BCD_Asc((char*) &IEC_Comm.Buf[2], (char*) &Buffer[0], Len);
		Len = Len * 2;
		break;
		//whole number decimal places
	case 0xC040:
		Buffer[0] = 0x06;
		Buffer[1] = 0x02;
		Len = 2;
		BCD_AscA((char*) &IEC_Comm.Buf[2], (char*) &Buffer[0], Len);
		Len = Len * 2;
		break;
		//read load table data
	case 0xD300: //
		Len = LoadPro_Read((unsigned char*) &Buffer[0], EevenLPPtr.LoadProCh);// DMS-> doc do thi phu tai "doc tat ca"
		if (Len > 0) {
			BCD_AscA((char*) &IEC_Comm.Buf[2], (char*) &Buffer[0], Len);
		}
		Len = Len * 2;
		break;
		//read channel code
	case 0xD301: //
		BCD_AscA((char*) &IEC_Comm.Buf[2], (char*) &EevenLPPtr.LoadProCh, 1);
		Len = 2 * 1;
		break;
		//load table read operation pointer
	case 0xD302: //
		FRAM_Read(&Buffer[0],
		ReadPtr1_ + SIZE_LoadINFORUN * EevenLPPtr.LoadProCh, 2);
		BCD_Asc((char*) &IEC_Comm.Buf[2], (char*) &Buffer[0], 2);

		Len = 2 * 2;
		break;
		//recorded numbers
	case 0xD303: //
		FRAM_Read(&Buffer[0],
		RecNUM1_ + SIZE_LoadINFORUN * EevenLPPtr.LoadProCh, 2);
		BCD_Asc((char*) &IEC_Comm.Buf[2], (char*) &Buffer[0], 2);
		Len = 2 * 2;
		break;
		//load table register code(7Reg+Num)
	case 0xD304: //
		FRAM_Read(&Buffer[0], RegNUM1_ + SIZE_LoadINFO * EevenLPPtr.LoadProCh,
				8);
		BCD_AscA((char*) &IEC_Comm.Buf[2], (char*) &Buffer[0], 8);
		Len = 2 * 8;
		break;
		//record time intervals(minutes)
	case 0xD305: //
		FRAM_Read(&Buffer[0], TimeInv1_ + SIZE_LoadINFO * EevenLPPtr.LoadProCh,
				2);
		BCD_Asc((char*) &IEC_Comm.Buf[2], (char*) &Buffer[0], 2);
		Len = 2 * 2;
		break;
		//load table record capacity(piece)
	case 0xD306: //
		FRAM_Read(&Buffer[0],
		MaxRecNUM1_ + SIZE_LoadINFO * EevenLPPtr.LoadProCh, 2);
		BCD_Asc((char*) &IEC_Comm.Buf[2], (char*) &Buffer[0], 2);
		Len = 2 * 2;
		break;
		//distribution of data block address
	case 0xD307: //
		FRAM_Read(&Buffer[0], RecAddr1_ + SIZE_LoadINFO * EevenLPPtr.LoadProCh,
				4);
		memcpy((char*) &ulTmp, Buffer, 4);
		ulTmp -= LOADCURVE;
		memcpy(Buffer, (char*) &ulTmp, 4);
		BCD_Asc((char*) &IEC_Comm.Buf[2], (char*) &Buffer[0], 4);
		Len = 2 * 4;
		break;
		//recorded numbers
	case 0xD308: //
		//FRAM_Read(&Buffer[0], RecNUM1_+SIZE_LoadINFORUN*EevenLPPtr.LoadProCh, 2);
		//BCD_Asc( (char*)&IEC_Comm.Buf[2], (char*)&Buffer[0], 2 );
		FRAM_Read(&Buffer[0],
		RecNUM1_ + SIZE_LoadINFORUN * EevenLPPtr.LoadProCh + 2, 2);
		BCD_Asc((char*) &IEC_Comm.Buf[2], (char*) &Buffer[0], 2);
		Len = 2 * 2;
		break;
#if 1
	case 0x9FFF:
		/*(current) positive active total energy(5byte)+(current)positive active total energy of each tariff(4*5byte)+
		 (current)positive reactive total energy(5byte)+PTCT(8byte)+
		 meter operation state word(2byte)+
		 last one month frozen date(6byte)(ssmmhhDDMMyy)+
		 last one month frozen positive active energy:total+4 tariffs (5*5byte)+
		 last one month frozen positive reactive energy:total+4 tariffs(5*5byte) */
		Len = 0;
		//reactive frozen
		if (TRUE == GetBillAdr(0, 0x0020, 0, &Addr, &Info)) {
			unsigned int m_len;
			m_len = Info & RS_LEN;
			MemType = (Info >> 6) & 0x07;
			MEM_Read((char*) &Buffer[Len], Addr, m_len, MemType);
		} else {
			memset(&Buffer[Len], 0x00, 25);
		}
		Len += 25;
		//active frozen
		if (TRUE == GetBillAdr(0, 0x0000, 0, &Addr, &Info)) {
			unsigned int m_len;
			m_len = Info & RS_LEN;
			MemType = (Info >> 6) & 0x07;
			MEM_Read((char*) &Buffer[Len], Addr, m_len, MemType);
		} else {
			memset(&Buffer[Len], 0x00, 25);
		}
		Len += 25;
		//frozen time
		if (TRUE == GetBillAdr(0, 0x01A0, 0, &Addr, &Info)) {
			unsigned int m_len;
			m_len = Info & RS_LEN;
			MemType = (Info >> 6) & 0x07;
			MEM_Read((char*) &Buffer[Len], Addr, m_len, MemType);
		} else {
			memset(&Buffer[Len], 0x00, 6);
		}
		Len += 6;
		MEM_Read((char*) &Buffer[Len], (unsigned long) meter_state, 2, Mem_RAM);
		Len += 2;
		MEM_Read((char*) &Buffer[Len], (unsigned long) PARA_PTCT, 8, Mem_FRAM);
		Len += 8;
		MEM_Read((char*) &Buffer[Len], (unsigned long) (EC_Rp0), 5, Mem_FRAM);
		Len += 5;
		MEM_Read((char*) &Buffer[Len], (unsigned long) (EC_Pp4), 5, Mem_FRAM);
		Len += 5;
		MEM_Read((char*) &Buffer[Len], (unsigned long) (EC_Pp3), 5, Mem_FRAM);
		Len += 5;
		MEM_Read((char*) &Buffer[Len], (unsigned long) (EC_Pp2), 5, Mem_FRAM);
		Len += 5;
		MEM_Read((char*) &Buffer[Len], (unsigned long) (EC_Pp1), 5, Mem_FRAM);
		Len += 5;
		MEM_Read((char*) &Buffer[Len], (unsigned long) (EC_Pp0), 5, Mem_FRAM);
		Len += 5;

		BCD_Asc((char*) &IEC_Comm.Buf[2], (char*) &Buffer[0], Len);
		Len <<= 1;

		break;
	case 0x9FF0:
		/*(current) positive active total energy(5byte)+(current)positive active total energy of each tariff(4*5byte)+
		 (current)positive reactive total energy(5byte)+PTCT(8byte)+
		 meter operation state word(2byte)+
		 last one month frozen date(6byte)(ssmmhhDDMMyy)+
		 last one month frozen positive active energy:total+4 tariffs (5*5byte)+
		 last one month frozen positive reactive energy:total+4 tariffs(5*5byte) */
		Len = 0;
#if 0
		//reactive frozen
		//无功冻结
		if(TRUE==GetBillAdr(0, 0x0020, 0, &Addr,&Info))
		{
			unsigned int m_len;
			m_len = Info & RS_LEN;
			MemType = (Info >> 6) & 0x07;
			MEM_Read((char*)&Buffer[Len], Addr, m_len, MemType);
		}
		else
		{
			memset(&Buffer[Len], 0x00, 25);
		}
		Len += 25;
		//active frozen
		//有功冻结
		if(TRUE==GetBillAdr(0, 0x0000, 0, &Addr,&Info))
		{
			unsigned int m_len;
			m_len = Info & RS_LEN;
			MemType = (Info >> 6) & 0x07;
			MEM_Read((char*)&Buffer[Len], Addr, m_len, MemType);
		}
		else
		{
			memset(&Buffer[Len], 0x00, 25);
		}
		Len += 25;
		//frozen time
		//冻结时间
		if(TRUE==GetBillAdr(0, 0x01A0, 0, &Addr,&Info))
		{
			unsigned int m_len;
			m_len = Info & RS_LEN;
			MemType = (Info >> 6) & 0x07;
			MEM_Read((char*)&Buffer[Len], Addr,m_len, MemType);
		}
		else
		{
			memset(&Buffer[Len], 0x00, 6);
		}
		Len += 6;
#endif             

		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (&gsAttBCDVal.IRMS[2][0]), 3, Mem_RAM);
		Len += 3;
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (&gsAttBCDVal.IRMS[1][0]), 3, Mem_RAM);
		Len += 3;
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (&gsAttBCDVal.IRMS[0][0]), 3, Mem_RAM);
		Len += 3;
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (&gsAttBCDVal.VRMS[2][0]), 2, Mem_RAM);
		Len += 2;
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (&gsAttBCDVal.VRMS[1][0]), 2, Mem_RAM);
		Len += 2;
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (&gsAttBCDVal.VRMS[0][0]), 2, Mem_RAM);
		Len += 2;
		MEM_Read((char*) &Buffer[Len], (unsigned long) meter_state, 2, Mem_RAM);
		Len += 2;
		MEM_Read((char*) &Buffer[Len], (unsigned long) PARA_PTCT, 8, Mem_FRAM);
		Len += 8;
		MEM_Read((char*) &Buffer[Len], (unsigned long) (EC_Rp0), 5, Mem_FRAM);
		Len += 5;
		MEM_Read((char*) &Buffer[Len], (unsigned long) (EC_Pp4), 5, Mem_FRAM);
		Len += 5;
		MEM_Read((char*) &Buffer[Len], (unsigned long) (EC_Pp3), 5, Mem_FRAM);
		Len += 5;
		MEM_Read((char*) &Buffer[Len], (unsigned long) (EC_Pp2), 5, Mem_FRAM);
		Len += 5;
		MEM_Read((char*) &Buffer[Len], (unsigned long) (EC_Pp1), 5, Mem_FRAM);
		Len += 5;
		MEM_Read((char*) &Buffer[Len], (unsigned long) (EC_Pp0), 5, Mem_FRAM);
		Len += 5;
		//MEM_Read((char*)&Buffer[Len],(unsigned long)(EC_Pp0),5,Mem_FRAM);Len += 5;
		BCD_Asc((char*) &IEC_Comm.Buf[2], (char*) &Buffer[0], Len);
		Len <<= 1;

		break;
	case 0x9FF1:
		/*(current) positive active total energy(5byte)+(current)positive active total energy of each tariff(4*5byte)+
		 (current)positive reactive total energy(5byte)+PTCT(8byte)+
		 meter operation state word(2byte)+
		 last one month frozen date(6byte)(ssmmhhDDMMyy)+
		 last one month frozen positive active energy:total+4 tariffs (5*5byte)+
		 last one month frozen positive reactive energy:total+4 tariffs(5*5byte) */

		Len = 0;

		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (&gsAttBCDVal.IRMS[2][0]), 3, Mem_RAM);
		Len += 3;
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (&gsAttBCDVal.IRMS[1][0]), 3, Mem_RAM);
		Len += 3;
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (&gsAttBCDVal.IRMS[0][0]), 3, Mem_RAM);
		Len += 3;
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (&gsAttBCDVal.VRMS[2][0]), 2, Mem_RAM);
		Len += 2;
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (&gsAttBCDVal.VRMS[1][0]), 2, Mem_RAM);
		Len += 2;
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (&gsAttBCDVal.VRMS[0][0]), 2, Mem_RAM);
		Len += 2;
		MEM_Read((char*) &Buffer[Len], (unsigned long) meter_state, 2, Mem_RAM);
		Len += 2;
		MEM_Read((char*) &Buffer[Len], (unsigned long) PARA_PTCT, 8, Mem_FRAM);
		Len += 8;
		//reactive frozen
		if (TRUE == GetBillAdr(0, 0x0020, 0, &Addr, &Info)) {
			// unsigned int m_len;
			//m_len = Info & RS_LEN;
			MemType = (Info >> 6) & 0x07;
			//MEM_Read((char*)&Buffer[Len], Addr, m_len, MemType);
			//reactive only need total
			MEM_Read((char*) &Buffer[Len], Addr, 5, MemType);
		} else {
			memset(&Buffer[Len], 0x00, 5);
		}
		Len += 5;
		//active frozen
		if (TRUE == GetBillAdr(0, 0x0000, 0, &Addr, &Info)) {
			// unsigned int m_len;
			//m_len = Info & RS_LEN;
			MemType = (Info >> 6) & 0x07;
			//MEM_Read((char*)&Buffer[Len], Addr, m_len, MemType);
			MEM_Read((char*) &Buffer[Len], Addr + 20, 5, MemType);
			MEM_Read((char*) &Buffer[Len + 5], Addr + 15, 5, MemType);
			MEM_Read((char*) &Buffer[Len + 10], Addr + 10, 5, MemType);
			MEM_Read((char*) &Buffer[Len + 15], Addr + 5, 5, MemType);
			MEM_Read((char*) &Buffer[Len + 20], Addr, 5, MemType);
		} else {
			memset(&Buffer[Len], 0x00, 25);
		}
		Len += 25;

#if 0
		MEM_Read((char*)&Buffer[Len],(unsigned long)meter_state,2,Mem_RAM); Len +=2;
		MEM_Read((char*)&Buffer[Len],(unsigned long)PARA_PTCT,8,Mem_FRAM);Len += 8;
		MEM_Read((char*)&Buffer[Len],(unsigned long)(EC_Rp0),5,Mem_FRAM); Len += 5;
		MEM_Read((char*)&Buffer[Len],(unsigned long)(EC_Pp4),5,Mem_FRAM);Len += 5;
		MEM_Read((char*)&Buffer[Len],(unsigned long)(EC_Pp3),5,Mem_FRAM);Len += 5;
		MEM_Read((char*)&Buffer[Len],(unsigned long)(EC_Pp2),5,Mem_FRAM);Len += 5;
		MEM_Read((char*)&Buffer[Len],(unsigned long)(EC_Pp1),5,Mem_FRAM);Len += 5;
		MEM_Read((char*)&Buffer[Len],(unsigned long)(EC_Pp0),5,Mem_FRAM);Len += 5;
#endif           
		BCD_Asc((char*) &IEC_Comm.Buf[2], (char*) &Buffer[0], Len);
		Len <<= 1;

		break;
	case 0x9FF2:
		/*(current) positive active total energy(5byte)+(current)positive active total energy of each tariff(4*5byte)+
		 (current)positive reactive total energy(5byte)+PTCT(8byte)+
		 meter operation state word(2byte)+
		 last one month frozen date(6byte)(ssmmhhDDMMyy)+
		 last one month frozen positive active energy:total+4 tariffs (5*5byte)+
		 last one month frozen positive reactive energy:total+4 tariffs(5*5byte) */
		Len = 0;

		MEM_Read((char*) &Buffer[Len], (unsigned long) meter_state, 2, Mem_RAM);
		Len += 2;
		MEM_Read((char*) &Buffer[Len], (unsigned long) PARA_PTCT, 8, Mem_FRAM);
		Len += 8;
		//reactive frozen
		if (TRUE == GetBillAdr(0, 0x0020, 0, &Addr, &Info)) {
			// unsigned int m_len;
			//m_len = Info & RS_LEN;
			MemType = (Info >> 6) & 0x07;
			//MEM_Read((char*)&Buffer[Len], Addr, m_len, MemType);
			//reactive only need total
			MEM_Read((char*) &Buffer[Len], Addr, 5, MemType); //
		} else {
			memset(&Buffer[Len], 0x00, 5);
		}
		Len += 5;
		//active frozen
		if (TRUE == GetBillAdr(0, 0x0000, 0, &Addr, &Info)) {
			//unsigned int m_len;
			//m_len = Info & RS_LEN;
			MemType = (Info >> 6) & 0x07;
			//MEM_Read((char*)&Buffer[Len], Addr, m_len, MemType);
			MEM_Read((char*) &Buffer[Len], Addr + 20, 5, MemType);
			MEM_Read((char*) &Buffer[Len + 5], Addr + 15, 5, MemType);
			MEM_Read((char*) &Buffer[Len + 10], Addr + 10, 5, MemType);
			MEM_Read((char*) &Buffer[Len + 15], Addr + 5, 5, MemType);
			MEM_Read((char*) &Buffer[Len + 20], Addr, 5, MemType);
		} else {
			memset(&Buffer[Len], 0x00, 25);
		}
		Len += 25;
		//frozen time
		if (TRUE == GetBillAdr(0, 0x01A0, 0, &Addr, &Info)) {
			unsigned int m_len;
			m_len = Info & RS_LEN;
			MemType = (Info >> 6) & 0x07;
			MEM_Read((char*) &Buffer[Len], Addr, m_len, MemType);
		} else {
			memset(&Buffer[Len], 0x00, 6);
		}
		Len += 6;

#if 0
		MEM_Read((char*)&Buffer[Len],(unsigned long)meter_state,2,Mem_RAM); Len +=2;
		MEM_Read((char*)&Buffer[Len],(unsigned long)PARA_PTCT,8,Mem_FRAM);Len += 8;
		MEM_Read((char*)&Buffer[Len],(unsigned long)(EC_Rp0),5,Mem_FRAM); Len += 5;
		MEM_Read((char*)&Buffer[Len],(unsigned long)(EC_Pp4),5,Mem_FRAM);Len += 5;
		MEM_Read((char*)&Buffer[Len],(unsigned long)(EC_Pp3),5,Mem_FRAM);Len += 5;
		MEM_Read((char*)&Buffer[Len],(unsigned long)(EC_Pp2),5,Mem_FRAM);Len += 5;
		MEM_Read((char*)&Buffer[Len],(unsigned long)(EC_Pp1),5,Mem_FRAM);Len += 5;
		MEM_Read((char*)&Buffer[Len],(unsigned long)(EC_Pp0),5,Mem_FRAM);Len += 5;
#endif              
		BCD_Asc((char*) &IEC_Comm.Buf[2], (char*) &Buffer[0], Len);
		Len <<= 1;

		break;
	case 0x9FF3:
		/*the data items to be read by one of RF three phase meter ID for one time:
		 (current) positive active total energy(5byte)+(current)positive active total energy of each tariff(4*5byte)+
		 (current)positive reactive total energy(5byte)+PTCT(8byte)+
		 meter operation state word(2byte)+last one month frozen date(6byte)(ssmmhhDDMMyy)+
		 last one month frozen positive active energy:total+4 tariffs (5*5byte)+
		 last one month frozen positive reactive total energy:（5byt）+
		 voltage of A,B,C phase(3*2byte)+current of A,B,C phase(3*3byte)+
		 transient total and active power of A,B,C phase(4*3byte)+
		 transient total and reactive power of A,B,C phase(4*3byte)+
		 total and power factor of A,B,C phase(3byte)+//total and power factor of A,B,C phase(4*3byte)+
		 program times(2byte)=125byte*/
		Len = 0;

		//program times
		MEM_Read((char*) &Buffer[Len], (unsigned long) EVENT_PROG_TIMES, 2,
				Mem_FRAM);
		Len += 2; //
		//power factor of C phase
		//MEM_Read((char*)&Buffer[Len],(unsigned long)(gsAttBCDVal.PF[2]),3,Mem_RAM);Len += 3;//C相功率因素
		//power factor of B phase
		//MEM_Read((char*)&Buffer[Len],(unsigned long)(gsAttBCDVal.PF[1]),3,Mem_RAM);Len += 3;//B相功率因素
		//power factor of A phase
		//MEM_Read((char*)&Buffer[Len],(unsigned long)(gsAttBCDVal.PF[0]),3,Mem_RAM);Len += 3;//A相功率因素
		//power factor of total phase
		MEM_Read((char*) &Buffer[Len], (unsigned long) (gsAttBCDVal.PF[3]), 3,
				Mem_RAM);
		Len += 3; //

		//reactive power of C phase
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (gsAttBCDVal.Var_Real[3]), 3, Mem_RAM);
		Len += 3; //
		//reactive power of B phase
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (gsAttBCDVal.Var_Real[2]), 3, Mem_RAM);
		Len += 3; //
		//reactive power of A phase
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (gsAttBCDVal.Var_Real[1]), 3, Mem_RAM);
		Len += 3; //
		//reactive power of A total phase
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (gsAttBCDVal.Var_Real[0]), 3, Mem_RAM);
		Len += 3; //

		//reactive power of C phase
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (gsAttBCDVal.Power_Real[3]), 3, Mem_RAM);
		Len += 3; //
		//reactive power of B phase
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (gsAttBCDVal.Power_Real[2]), 3, Mem_RAM);
		Len += 3; //
		//reactive power of A phase
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (gsAttBCDVal.Power_Real[1]), 3, Mem_RAM);
		Len += 3; //
		//reactive power of A total phase
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (gsAttBCDVal.Power_Real[0]), 3, Mem_RAM);
		Len += 3; //
		//voltage and current
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (&gsAttBCDVal.IRMS[2][0]), 3, Mem_RAM);
		Len += 3;
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (&gsAttBCDVal.IRMS[1][0]), 3, Mem_RAM);
		Len += 3;
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (&gsAttBCDVal.IRMS[0][0]), 3, Mem_RAM);
		Len += 3;
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (&gsAttBCDVal.VRMS[2][0]), 2, Mem_RAM);
		Len += 2;
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (&gsAttBCDVal.VRMS[1][0]), 2, Mem_RAM);
		Len += 2;
		MEM_Read((char*) &Buffer[Len],
				(unsigned long) (&gsAttBCDVal.VRMS[0][0]), 2, Mem_RAM);
		Len += 2;

		//reactive frozen
		if (TRUE == GetBillAdr(0, 0x0020, 0, &Addr, &Info)) {
			// unsigned int m_len;
			//m_len = Info & RS_LEN;
			MemType = (Info >> 6) & 0x07;
			//MEM_Read((char*)&Buffer[Len], Addr, m_len, MemType);
			//reactive only need total
			MEM_Read((char*) &Buffer[Len], Addr, 5, MemType); //

		} else {
			memset(&Buffer[Len], 0x00, 5);
		}
		Len += 5;
		//active frozen
		if (TRUE == GetBillAdr(0, 0x0000, 0, &Addr, &Info)) {
			//unsigned int m_len;
			//m_len = Info & RS_LEN;
			MemType = (Info >> 6) & 0x07;
			//MEM_Read((char*)&Buffer[Len], Addr, m_len, MemType);
			MEM_Read((char*) &Buffer[Len], Addr + 20, 5, MemType);
			MEM_Read((char*) &Buffer[Len + 5], Addr + 15, 5, MemType);
			MEM_Read((char*) &Buffer[Len + 10], Addr + 10, 5, MemType);
			MEM_Read((char*) &Buffer[Len + 15], Addr + 5, 5, MemType);
			MEM_Read((char*) &Buffer[Len + 20], Addr, 5, MemType);
		} else {
			memset(&Buffer[Len], 0x00, 25);
		}
		Len += 25;
		//frozen time
		if (TRUE == GetBillAdr(0, 0x01A0, 0, &Addr, &Info)) {
			unsigned int m_len;
			m_len = Info & RS_LEN;
			MemType = (Info >> 6) & 0x07;
			MEM_Read((char*) &Buffer[Len], Addr, m_len, MemType);
		} else {
			memset(&Buffer[Len], 0x00, 6);
		}
		Len += 6;
		MEM_Read((char*) &Buffer[Len], (unsigned long) meter_state, 2, Mem_RAM);
		Len += 2;
		MEM_Read((char*) &Buffer[Len], (unsigned long) PARA_PTCT, 8, Mem_FRAM);
		Len += 8;

		MEM_Read((char*) &Buffer[Len], (unsigned long) (EC_Rp0), 5, Mem_FRAM);
		Len += 5;
		MEM_Read((char*) &Buffer[Len], (unsigned long) (EC_Pp4), 5, Mem_FRAM);
		Len += 5;
		MEM_Read((char*) &Buffer[Len], (unsigned long) (EC_Pp3), 5, Mem_FRAM);
		Len += 5;
		MEM_Read((char*) &Buffer[Len], (unsigned long) (EC_Pp2), 5, Mem_FRAM);
		Len += 5;
		MEM_Read((char*) &Buffer[Len], (unsigned long) (EC_Pp1), 5, Mem_FRAM);
		Len += 5;
		MEM_Read((char*) &Buffer[Len], (unsigned long) (EC_Pp0), 5, Mem_FRAM);
		Len += 5;

		BCD_Asc((char*) &IEC_Comm.Buf[2], (char*) &Buffer[0], Len);
		Len <<= 1;

		break;
#endif
		//time correction factor
	case 0xE106: //
		FRAM_Read(&Buffer[0], CLK_GENE, 4);
		BCD_Asc((char*) &IEC_Comm.Buf[2], (char*) &Buffer[0], 4);
		Len = 8;
		break;

	case 0xC100: //Device Addr = 0x05b8 save in FRAM chip which is name "chi so huu cong tong"
		Addr = DeviceAddr;
		Len = 12;
#ifdef SINGLE_PHASE_MULTI_TARIFF
		MemType = Mem_E2PROM;
#else
		MemType = Mem_FRAM;
#endif
		MEM_Read((char*) &IEC_Comm.Buf[2], Addr, 12, MemType);
		break;
	default:

		//read the highest level of level 3 password
		if ((ID == 0xC101) && (IEC_Comm.PassAcc != 3)) //
		{
			return (0xFF);
		}
		//read level2 password
		else if ((ID == 0xC103) && (IEC_Comm.PassAcc != 2) && (IEC_Comm.PassAcc
				!= 3)) //
		{
			return (0xFF);
		}
		//read level 4 password
		else if ((ID == 0xC10B) && (IEC_Comm.PassAcc != 4) && (IEC_Comm.PassAcc
				!= 3)) //
		{
			return (0xFF);
		}
		for (i = 0; i < CommNum; i++) {
			if (ID == CommTab[i].ComID) {
				Addr = (unsigned int) CommTab[i].Addr;
				Info = CommTab[i].ComInfo;
				Len = Info & RS_LEN;
				MemType = (Info >> 6) & 0x07;
				break;
			}
		}

		//history quantity
		if ((ID >= 0x0400) && (ID <= 0x1BFF)) {
			ii = ID & 0xff00;
			ii >>= 8;
			ii -= 4;
			Len = ii & 0x01;
			//history record
			ii = ii / 2; //

			ID &= 0x0ff;
			if (Len == 1) {
				ID |= 0x0100;
			}

			if (TRUE == GetBillAdr(ii, ID, 0, &Addr, &Info)) {
				Len = Info & RS_LEN;
				MemType = (Info >> 6) & 0x07;
				i = 0;
			} else {

				i = 0xffff;
			}

		} else if ((ID >= 0x2400) && (ID < 0x3000)) {
			ii = ID & 0xff00;
			ii >>= 8;
			ii -= 0x24;
			ID &= 0x00ff;
			if (TRUE == GetBillAdr(ii, ID, 1, &Addr, &Info)) {
				Len = Info & RS_LEN;
				MemType = (Info >> 6) & 0x07;
				i = 0;
			} else {
				i = 0xffff;

			}
		}

		if (i >= CommNum)
			return (0xFF);

		switch (ID) {
		case 0xE0A0:
		case 0xE0B0:
		case 0xE0C0:
		case 0xE0D0:
		case 0xE0E0:
		case 0xE0E1:
		case 0xE0E2:
		case 0xE0E3:
		case 0xE0E4:
		case 0xE0E5:
		case 0xE0E6:
		case 0xE0E7:
		case 0xE105:
			//all are 1 byte HEX
			MEM_Read((char*) &Buffer[0], Addr, Len, MemType);
			chrPtr = itoaA((long) Buffer[0], &Buffer[BufUbd], 10);
			Len = (unsigned char*) &Buffer[BufUbd] - chrPtr;
			memcpy(&IEC_Comm.Buf[2], chrPtr, Len);

			break;
		default:

			if (ID >= 0xA020 && ID <= 0xA069) {
				MEM_Read((char*) &EVENT_Ptr, (Addr - 1), 1, MemType);
				if (EVENT_Ptr <= 0x00 || EVENT_Ptr > 0x28)
					EVENT_Ptr = 0x28;
				i = (ID & 0x000F);
				i *= 4;
				if (EVENT_Ptr > i)
					EVENT_Ptr -= i;
				else
					EVENT_Ptr += (0x28 - i);
				for (i = 4; i > 0; i--) {
					MEM_Read(&Buffer[(i - 1) * 11],
							Addr + (EVENT_Ptr - 1) * 11, 11, MemType);
					EVENT_Ptr--;
					if (EVENT_Ptr <= 0x00 || EVENT_Ptr > 0x28)
						EVENT_Ptr = 0x28;
				}
			}
			//event record
			else if (ID >= 0xE200 && ID <= 0xE235) {//
				MEM_Read((char*) &EVENT_Ptr, (Addr - 1), 1, MemType);
				if (EVENT_Ptr <= 0x00 || EVENT_Ptr > 10)
					EVENT_Ptr = 10;

				for (i = 10; i > 0; i--) {
					MEM_Read(&Buffer[(i - 1) * 5], Addr + (EVENT_Ptr - 1) * 5,
							5, MemType);
					EVENT_Ptr--;
					if (EVENT_Ptr <= 0x00 || EVENT_Ptr > 10)
						EVENT_Ptr = 10;
				}
			} else {
				MEM_Read((char*) &Buffer[0], Addr, Len, MemType);
			}

			if (ID <= 0x2015 && ID >= 0x2000) {
				BCD_AscA((char*) &IEC_Comm.Buf[2], (char*) &Buffer, Len);
			} else if (ID >= 0x3000 && ID <= 0x3090) {
				BCD_AscA((char*) &IEC_Comm.Buf[2], (char*) &Buffer, Len);
			}

			else if (ID <= 0x203F && ID >= 0x2020) {
				BCD_Asc((char*) &IEC_Comm.Buf[2], (char*) &Buffer, Len);
			} else if ((ID <= 0xC001) && (ID > 0x2100))
				BCD_Asc((char*) &IEC_Comm.Buf[2], (char*) &Buffer, Len);
			else
				BCD_AscA((char*) &IEC_Comm.Buf[2], (char*) &Buffer, Len);

			Len = Len * 2;
			break;
		}
	}

	//END:
	IEC_Comm.Flag |= Comm_readed;

	if ((Len != 0x0000) && (Len != 0xFFFF)) {
		IEC_Comm.Buf[0] = STX;
		IEC_Comm.Buf[1] = '(';
		Len += 2;
		IEC_Comm.Buf[Len++] = ')';
		IEC_Comm.Buf[Len++] = ETX;
		IEC_Comm.Buf[Len] = GetCHK(IEC_Comm.Buf, 1, Len - 1);
		IEC_Comm.Buf[++Len] = EndFrame;
		return (0x00);
	} else if (Len == 0x0000) {
		IEC_Comm.Buf[0] = NAK;
		IEC_Comm.Buf[1] = EndFrame;
		return (0x01);
	} else {
		return (0xFF);
	}
}

//**********************************************************************
//IEC receiving and handling
//**********************************************************************
//deal with the received data and startup the response
void IEC_CommRespond(void) {
	unsigned char Tmp;

	Flag.FlsLP |= FlsLP_Com_RBsy;

	//BCC check
	switch (IEC_Comm.CommMode) {
	case DataOut:
		IEC_Comm.Mode = 0;
		IEC_Comm.MdTmr = 0;
		break;
	case Program:
	case HDLC:
	case Factory6:
	case Factory7:
	case Factory8:
	case Factory9:
		Tmp = GetCHK(IEC_Comm.Buf, 1, IEC_Comm.Ptr - 1);

		//calibrationerror
		if (Tmp != 0x00) //校验错
		//resend request
		{ //
			IEC_Comm.Buf[0] = NAK;
			IEC_Comm.Buf[1] = EndFrame;
			IEC_Comm.Mode = 2;
			return;
		}
		break;
	}
	//handle
	switch (IEC_Comm.CommMode) {
	case DataOut:
		// goto NOANSWER;
		break;
	case Program:
		if (IEC_Comm.Buf[0] == ACK) {
			goto NOANSWER;
		} else if (IEC_Comm.Buf[0] == NAK) {
			//resend the original content
			if (IEC_Comm.Buf[3] == STX) //
				//as only the first byte has been changed, so only the first byte to be recovered
				IEC_Comm.Buf[0] = SOH; //
			else
				IEC_Comm.Buf[0] = STX;
			IEC_Comm.Mode = 2;
		} else {
			//judge identifier of command information
			switch (IEC_Comm.Buf[1]) //
			{
			//password command
			case 'P': //
				switch (IEC_Comm.Buf[2]) {
				case '1':
					IEC_CommP1();
					IEC_Comm.Mode = 2;
					break;
				default:
					goto NOANSWER;
				}
				break;
				//write command
			case 'W': //写命令

				if ((IEC_Comm.Flag & PasswordP1OK) == 0) {
					goto ERR_PASS;
				}
				switch (IEC_Comm.Buf[2]) {
				case '1':
				case '2':
					if (IEC_CommReadW1() == 0)
						IEC_Comm.Mode = 2;
					else
						goto NOANSWER;
					break;
				case '0':
				case '3':
				case '4':
				default:
					goto NOANSWER;
				}
				break;
				//read command
			case 'R': //
				if ((IEC_Comm.Flag & PasswordP1OK) == 0) {
					goto ERR_PASS;
				}

				switch (IEC_Comm.Buf[2]) {
				case '1':
				case '2':
					if (IEC_CommReadR1() != 0xFF)
						IEC_Comm.Mode = 2;
					else
						goto NOANSWER;
					break;
				case '0':
				case '3':
				case '4':
				default:
					goto NOANSWER;
				}
				break;
				//command performance
			case 'E': //
				switch (IEC_Comm.Buf[2]) {
				case '1':
				case '2':
					if (IEC_CommReadE1() != 0xFF)
						IEC_Comm.Mode = 2;
					else
						goto NOANSWER;
					break;
				default:
					goto NOANSWER;
				}
				break;
				//exit command
			case 'B': //
				IEC_Comm.Ptr = 0;
				IEC_Comm.MdTmr = 0;
				CommInit();
				break;
				//unidentified command
			default: //
				goto NOANSWER;
			}
		}
		break;
	case HDLC:
		goto NOANSWER;
		//break;
	case Factory6:
	case Factory7:
	case Factory8:
	case Factory9:
		goto NOANSWER;
	default:
		goto NOANSWER;
	}
	return;
	NOANSWER: IEC_Comm.Buf[0] = STX;
	IEC_Comm.Buf[1] = 'E';
	IEC_Comm.Buf[2] = 'R';
	IEC_Comm.Buf[3] = ':';
	memcpy(&IEC_Comm.Buf[4], (char*) NotSupport, sizeof(NotSupport) - 1);
	Tmp = 4 + sizeof(NotSupport) - 1;

	IEC_Comm.Buf[Tmp++] = ETX;
	IEC_Comm.Buf[Tmp] = GetCHK(IEC_Comm.Buf, 1, Tmp - 1);
	IEC_Comm.Buf[++Tmp] = EndFrame;
	IEC_Comm.Mode = 2;
	IEC_Comm.Ptr = 0;
	return;
	ERR_PASS: IEC_Comm.Buf[0] = 0x02; //NAK;
	strcpy((char*) &IEC_Comm.Buf[1], "ER:PASSWORD NOT RIGHT");
	IEC_Comm.Buf[21] = 0x03;
	IEC_Comm.Buf[22] = GetCHK(IEC_Comm.Buf, 1, 21);

	IEC_Comm.Buf[23] = EndFrame;
	IEC_Comm.Mode = 2;
	return;
}

//**********************************************************************
//serial port events records
//**********************************************************************
void Comm_Record(void) {
	E2P_Read(&Buffer[0], Comm_Num, 4);
	_BCD4INC(&Buffer[0]);
	memcpy(&Buffer[4], &Clk.Sec[0], 6);
	FRAM_Read(&Buffer[10], EC_Pp0, 4);
	FRAM_Read(&Buffer[14], EC_Rp0, 4);
	FRAM_Read(&Buffer[18], MD_Pp, 3);
	FRAM_Read(&Buffer[21], MD_Rp, 3);
	MEM_DBWrite(Comm_Num, &Buffer[0], 24, Mem_E2PROM);
}
//**********************************************************************
//serial port initialization
//**********************************************************************
void CommInit(void) {
	if (IEC_Comm.MdTmr == 0) {
		//reset the variable related to serial port communication
		Flag.Run &= ~R_ComOK;
		IEC_Comm.CntTmr = 0;
		IEC_Comm.Mode = 1;
		IEC_Comm.Ptr = 0;
		IEC_Comm.CommMode = NoCnt;
		IEC_Comm.Flag = 0x00;
		IEC_Comm.DaOutCnt = 0;
		IEC_Comm.BCC = 0x00;
		IEC_Comm.PassAcc = 0x00;
		Flag.FlsLP &= ~FlsLP_Com_RBsy;
		//485 port to be initialized to 300bps
		SetUart(UART0, BAUD300, EVEN_7BIT); //
		//external module interface to be initialized to 1200bps
		SetUart(UART1, BAUD1200, EVEN_7BIT); //

		//photometer head to be initialized to 300bps
		gUartSim.Baud = 0; //
		//falling edge trigger
		PSUartIES |= P_SimRXD; //下降沿触发
		//clear
		PSUartIFG &= ~P_SimRXD; //清
		//make it can trigger and interrupt
		PSUartIE |= P_SimRXD; //
		//set to input
		PSUartDIR &= ~P_SimRXD; //
		//communication events records
		if (IEC_Comm.Flag & Comm_readed) {
			Comm_Record();
		}
		S31_ON;

	}
}
//**********************************************************************
//serial port IEC handling progress
//**********************************************************************
void IEC_CommProcess(void) {
	if ((Flag.Power & F_PwrUp) != F_PwrUp) {
		return;
	}

	switch (IEC_Comm.Mode) {
	//reset communication state
	case 0: //
		CommInit();
		break;
		//receive handling and startup sending response
	case 1: //
		if (IEC_Comm.Ptr != 0) {
			if (Flag.Run & R_ComOK) {
				if (IEC_Comm.CommMode == DataOut)
					if (IEC_Comm.DaOutCnt >= 1)
						IEC_Comm.MdTmr = 0; //TM_20ms;
					else
						IEC_Comm.MdTmr = TM_200ms;

				else if (IEC_Comm.CommMode == NoCnt)
					IEC_Comm.MdTmr = TM_200ms;
				else
					IEC_Comm.MdTmr = 20;

				//no connection
				if (IEC_Comm.CommMode == NoCnt) //
				{
					if (IEC_Comm.Buf[0] == '/' && CmpDeviceAddr(IEC_Comm.Buf,
							2, IEC_Comm.Ptr - 4) == 0) {
						//IEC communication hand shaking, request of changing communication rate, infrared and 485 into 2400bps
						IEC_Comm.Buf[0] = '/';
						IEC_Comm.Buf[1] = 'X';
						IEC_Comm.Buf[2] = 'X';
						IEC_Comm.Buf[3] = 'X';
						IEC_Comm.Buf[4] = CBaud_24;
						IEC_Comm.Buf[5] = '\\';
						IEC_Comm.Buf[6] = CBaud_24;
						IEC_Comm.Buf[7] = CR;
						IEC_Comm.Buf[8] = LF;
						IEC_Comm.Buf[9] = EndFrame;
						IEC_Comm.Mode = 2;
						//verify the qualified symbol of meter number
						IEC_Comm.Flag |= DeviceIDOK; //

						//set the baud rate of external module to 1200bps GPRS and PLC module
						if (IEC_Comm.ComId == 2) //
						{
							IEC_Comm.Buf[4] = CBaud_12;
							IEC_Comm.Buf[6] = CBaud_12;
						}
					} else if (IEC_Comm.Buf[0] == ACK) {
						if (IEC_Comm.Flag & DeviceIDOK) {
							//confirm the switch of baud rate
							if (IEC_Comm.Buf[2] == CBaud_24) {
								if (IEC_Comm.ComId == 1) {
									SetBaud(UART0, BAUD2400);
								} else if (IEC_Comm.ComId == 2) {
									SetBaud(UART1, BAUD2400);
								} else {
									gUartSim.Baud = 3;
								}
							} else if (IEC_Comm.Buf[2] == CBaud_12) {
								if (IEC_Comm.ComId == 1) {
									SetBaud(UART0, BAUD1200);
								} else if (IEC_Comm.ComId == 2) {
									SetBaud(UART1, BAUD1200);
								} else {
									gUartSim.Baud = 2;
								}
							}
							//position connection
							IEC_Comm.CommMode = IEC_Comm.Buf[3]; //

							IEC_1stAnswer();

						} else
							IEC_Comm.Mode = 0;
					} else
						IEC_Comm.Mode = 0;
				}
				//with connection
				else //
				{
					//response function, handle the read and write operation of IEC
					IEC_CommRespond(); //
				}
			} else if (IEC_Comm.MdTmr == 0)
				IEC_Comm.Mode = 0;
		} else if (IEC_Comm.CommMode != NoCnt && IEC_Comm.MdTmr == 0) {
			IEC_Comm.Mode = 0;
		}
		break;
		//send
	case 2: //
		if (IEC_Comm.MdTmr == 0) {
			Flag.Run &= ~R_ComOK;
			IEC_Comm.Mode = 3;
			IEC_Comm.Ptr = 0;

			if (IEC_Comm.ComId == 1) {
				IEC_Comm.MdTmr = TM_10000ms;
				U0TXBUF = IEC_Comm.Buf[IEC_Comm.Ptr++];
				//startup sending, adopt the interruption sending mothod
				UART0_TX_ON(); //
			} else if (IEC_Comm.ComId == 2) {
				IEC_Comm.MdTmr = TM_10000ms;
				U1TXBUF = IEC_Comm.Buf[IEC_Comm.Ptr++];
				//startup sending, adopt the interruption sending mothod
				UART1_TX_ON(); //

			} else {

				IEC_Comm.MdTmr = TM_10000ms;
				//startup sending, adopt the interruption sending mothod
				SimSendChar(IEC_Comm.Buf[IEC_Comm.Ptr++]); //
			}
		}
		break;
		//return after completed sending
	case 3: //
		//put it into the interruption program after sending completely
		if (IEC_Comm.MdTmr == 0) {
			IEC_Comm.Ptr = 0;
			IEC_Comm.Mode = 0;
			S31_OFF;
		}
		break;
	default:
		IEC_Comm.Mode = 0;
		IEC_Comm.MdTmr = 0;
		break;
	}
}

