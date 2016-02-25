/*
 * RN8209.c
 *
 *  Created on: Jan 12, 2016
 *      Author: User
 */

#include "..\inc\includes.h"

#ifdef SINGLE_PHASE_MULTI_TARIFF
//#include "..\inc\RN8209.h"
extern ENERGY vse1t_de;
volatile RN8209_RMS rn8209a_rms;
volatile RN8209_RMS_BCD rn8209a_rms_bcd;
volatile RN8209_CALIB rn8209a_calib;
#endif

unsigned long PoldTemp; //ENERGY CUMULATIVE NUMBER
unsigned int PTemp; //ENERGY CUMULATIVE REGISTER READING DATA
unsigned int Ku, Ka, Kb; //VOLTAGE FACTOR,A PHASE AND B PHASE CURRENT FACTOR
unsigned char Current_ID;
STRUDataComm DataComm;
unsigned int Power, Power_comp;
unsigned long Current;
unsigned long Vol;
volatile FLAG Flag_RN;

#ifdef SINGLE_PHASE_MULTI_TARIFF

//delay function
void RN8209_DelayUs(unsigned char ucTime) {
	for (; ucTime > 0; ucTime--) {
		_NOP();_NOP();_NOP();_NOP();_NOP();
		_NOP();_NOP();_NOP();_NOP();_NOP();
	}
}
/********************************************************************

INIT SPI PORT, AND RESET 8209

 ********************************************************************/
void SPI_Init_RN(void) {
	RN8209_CLR_CS();
	RN8209_CLR_CLK();
	RN8209_CLR_SI();
    RN8209_SET_CS();
}

/********************************************************************


SPI WRITE FUNCTION

 ********************************************************************/
void SPI_WriteByte(unsigned char ucData) {
	unsigned char i;
//	RN8209_SET_REST();
	for (i = 0; i < 8; i++) {
		if ((ucData & 0x80) == 0x80)
			RN8209_SET_SI();
		else
			RN8209_CLR_SI();
		RN8209_SET_CLK();
		ucData <<= 1;
		RN8209_CLR_CLK();
	}
}

/********************************************************************
 SPI READ FUNCTION

 ********************************************************************/
unsigned char SPI_ReadByte(void) {
	unsigned char ucData = 0;
	unsigned char i;
//	RN8209_SET_REST();
	for (i = 0; i < 8; i++) {
		RN8209_SET_CLK();
		ucData <<= 1;
		RN8209_CLR_CLK();
		if (RN8209_RET_SO)
			ucData |= 0x01;
	}
	return ucData;
}

/********************************************************************

WRITE 8209 DATA FUNCTION

 ********************************************************************/


void RN8209_WriteData(unsigned char wReg, unsigned char *pBuf, unsigned char ucLen) {
    unsigned char i;
    RN8209_CLR_CS();
//    SPI_WriteByte(0xEA);
//    SPI_WriteByte(0xE5);
    SPI_WriteByte((wReg | 0x80)); //WRITE COMMAND AND REGISTER ADDRESS
    for (i = ucLen; i > 0; i--)
        SPI_WriteByte(pBuf[i - 1]);
//    SPI_WriteByte(0xEA);
//    SPI_WriteByte(0xDC);
    RN8209_SET_CS();
}
/********************************************************************

READ 8209 DATA FUNCTION

 ********************************************************************/
void RN8209_ReadData(unsigned short wReg, unsigned char *pBuf, unsigned char ucLen) {
    unsigned char i;
    RN8209_CLR_CS();
    SPI_WriteByte((wReg & 0x7F)); //WRITE COMMAND AND REGISTER ADDRESS
    for (i = ucLen; i > 0; i--)
        pBuf[i - 1] = SPI_ReadByte();
    RN8209_SET_CS();
}

/********************************************************************
CAPTURE CUMULATIVE POSITIVE TOTAL ENERGY, RETURN VALUE INCLUDES TWO DECIMALS,AND IT IS DIVIDED BY 100 TO GET INTEGER

 ********************************************************************/
void POWERSUM_get(void) {
    unsigned long gettemp;
    unsigned char i;
    static unsigned char arenum = 0;
    RN8209_ReadData(ENERGYP, DataComm.ucTempBuf, 3);
    for (gettemp = 0, i = 3; i > 0; i--) {
        gettemp <<= 8;
        gettemp |= DataComm.ucTempBuf[i - 1];
    }
    if (gettemp >= 8)
        gettemp = 0;
    PTemp += gettemp;
#ifdef  METER_TYPE == 2
	Power += ((PTemp / 8) | ((PTemp / 8) << 8));
	PTemp %= 8;
#else
	Power += ((PTemp / 16) | ((PTemp / 16) << 8));
	PTemp %= 16;
#endif
    Power_comp = Power;
    //RN8209_ReadData(EMUSTATUS,DataComm.ucTempBuf,3);
    /*
    if(DataComm.ucTempBuf[2]&0x02)
    {
    if(arenum>1)Flag_RN.reverse=true;
    else arenum++;
    }
    else arenum=0,Flag_RN.reverse=false;
     */
#ifdef  METER_TYPE == 2
    if (POWERP_get(POWERPA) < (-82992) || POWERP_get(POWERPB) < (-82992))//10(40)A  IN 2W,REVERSE POWER IS NOT JUDGED
#else
    if (POWERP_get(POWERPA) < (-110000) || POWERP_get(POWERPB) < (-110000))//20(80)A   IN 2W,REVERSE POWER IS NOT JUDGED
#endif
    {
        if (arenum > 1)
            Flag_RN.reverse = true; //READ REVERSE POLARITY ENERGY FOR THREE TIMES(1s),THEN OPEN THE REVERSE LED
        else
            arenum++;
    } else {
        arenum = 0;
        Flag_RN.reverse = false; //IF THE PORALITY IS NORMAL, CLOSE REVERSE LED
    }
    RN8209_ReadData(DEVICEID, DataComm.ucTempBuf, 3); // READ 8209's ID
    if ((DataComm.ucTempBuf[0] != 0x00) ||
            (DataComm.ucTempBuf[1] != 0x09) ||
            (DataComm.ucTempBuf[2] != 0x82)) {
        RN8209_ReadData(DEVICEID, DataComm.ucTempBuf, 3);
        if ((DataComm.ucTempBuf[0] != 0x00) ||
                (DataComm.ucTempBuf[1] != 0x09) ||
                (DataComm.ucTempBuf[2] != 0x82))
            Flag_RN.energy_error = 1;
    } else
        Flag_RN.energy_error = 0;

}

/********************************************************************
CAPTURE A/B PHASE POSITIVE POWER VALID VALUE, RETURN THE REGISTER READING DATA
PARAMETER x IS POWERPA/POWERPB
 ********************************************************************/
long POWERP_get(unsigned char x) {
    long gettemp;
    unsigned char i;
    RN8209_ReadData(x, DataComm.ucTempBuf, 4);
    for (gettemp = 0, i = 4; i > 0; i--) {
        gettemp <<= 8;
        gettemp |= DataComm.ucTempBuf[i - 1];
    }
    return (gettemp);
}

/******************************************************************
CAPTURE RMS OF A PHASE AND B PHASE, RETURN VALUE INCLUDES THREE DECIMALS,AND IT IS DIVIDED BY 1000 TO GET INTEGER
PARAMETER IS IARMS/IBRMS
 ********************************************************************/
unsigned long CURRENT_get(unsigned char x) {
    unsigned long gettemp;
    unsigned char i, ubuf[3];
    RN8209_ReadData(x, &ubuf[0], 3);
    for (gettemp = 0, i = 3; i > 0; i--) {
        gettemp <<= 8;
        gettemp |= ubuf[i - 1];
    }
    if ((gettemp >> 16) >= 0x80)
        gettemp = 0; //THE NEGATIVE DATA IS INVALID, AND HAS ZERO DEAL
    if (x == IARMS)
        gettemp = ((gettemp * 100) / (unsigned long)rn8209a_calib.ka);
    else if (x == IBRMS)
        gettemp = ((gettemp * 100) / (unsigned long)rn8209a_calib.kb);
    return (gettemp);
}

/******************************************************************
CAPTURE RMS OF VOLTAGE, RETURN VALUE INCLUDES TWO DECIMALS,AND IT IS DIVIDED BY 100 TO GET INTEGER
 ********************************************************************/
unsigned long VOLTAGE_get(void) {
    unsigned long gettemp;
    unsigned char i, ubuf[3];
    RN8209_ReadData(URMS, &ubuf[0], 3);
    for (gettemp = 0, i = 3; i > 0; i--) {
        gettemp <<= 8;
        gettemp |= ubuf[i - 1];
    }
    if ((gettemp >> 16) >= 0x80)
        gettemp = 0; //THE NEGATIVE DATA IS INVALID, AND HAS ZERO DEAL
    gettemp = ((gettemp * 100) / rn8209a_calib.kv);
    return (gettemp);
}

/******************************************************************
VOLTAGE GAIN CALIBRATION
PARAMETER IS THE GIVEN VOLTAGE VALUE FOR CALIBRATION TABLE(INCLUDING TWO DECIMALS)
 ********************************************************************/
void VGAIN_adj(unsigned long v_cal) {
	unsigned long v_temp;//
	v_temp = VOLTAGE_get();
	rn8209a_calib.kv = ((v_temp * (unsigned long)rn8209a_calib.kv) / 100)/v_cal;
	if (rn8209a_calib.kv < 1)
		rn8209a_calib.kv = 6800;
	E2P_Write(Adj_Para_Kv, (char*) &rn8209a_calib.kv, 2);

}

/******************************************************************
A/B PHASE CURRENT GAIN CALIBRATION
PARAMETER adj_value IS THE GIVEN CURRENT VALUE FOR CALIBRATION TABLE(INCLUDING TWO DECIMALS)
PARAMETER x IS IARMS/IBRMS
 ********************************************************************/
void IGAIN_adj(unsigned long adj_value) {
	unsigned long i_temp_a, i_temp_b;
	CF_OUT(0);// select channel A
	i_temp_a = CURRENT_get(IARMS);
	CF_OUT(1);// select channel B
	i_temp_b = CURRENT_get(IBRMS);

	if (i_temp_a > i_temp_b)
	{
		rn8209a_calib.ka = (((i_temp_a * rn8209a_calib.ka) / adj_value) / 10);
		if (rn8209a_calib.ka < 1)
			rn8209a_calib.ka = 4040;
		E2P_Write(Adj_Para_Ka, (char*) &rn8209a_calib.ka, 2);
	}
	else {
		rn8209a_calib.kb = (((i_temp_b * rn8209a_calib.kb) / adj_value) / 10);
		if (rn8209a_calib.kb < 1)
			rn8209a_calib.kb = 4040;
		E2P_Write(Adj_Para_Kb, (char*) &rn8209a_calib.kb, 2);
	}
}
/******************************************************************
A/B PHASE CALIBRATION,PARAMETER IS THE REGISTERED VALUE A/B AFTER CALIBRATION
PARAMETER adj_value IS THE REGISTERED VALUE AFTER CALIBRATION
PARAMETER x IS PHSA/PHSB
 ********************************************************************/
void store_PHSx(unsigned char x, unsigned char eex) {
    if (x == PHSA)
        store_data(1, eex, DataComm.ucTemp8);
    else if (x == PHSB)
        store_data(1, eex + 2, DataComm.ucTemp8);
}

void PHCAL_adj(int adj_value, unsigned char x) {
    char tmp;
    int temp;
    RN8209_ReadData(x, DataComm.ucTempBuf, 1);
    tmp = DataComm.ucTemp8;
    temp = (adj_value + (int) tmp);
    if (temp > 127)
        DataComm.ucTemp8 = 127;
    else if (temp < (-128))
        DataComm.ucTemp8 = (-128);
    else
        DataComm.ucTemp8 = temp;
    RN8209_WriteData(x, DataComm.ucTempBuf, 1);
    if (Current < (Ib / 5 + 25))
        store_PHSx(x, 28); //SAVE THE CALIBRATION VALUE OF Ib(SMALL CURRENT) FOR LESS THAN 20%
#ifdef METER_TYPE == 2
    else if (Current < (Ib + 500)) //SAVE 20%-150% CALIBRATION VALUE OF Ib
#else
    else if (Current < (Ib + 1000)) //SAVE THE CALIBRATION VALUE OF Ib FOR LESS THAN 150%
#endif
    {
        store_PHSx(x, 29);
//        delay_ms(1);
//        if (ReadEE(x * 2 + 14) == 0)
//            store_PHSx(x, 28);
////        delay_ms(1);
//        if (ReadEE(x * 2 + 38) == 0)
//            store_PHSx(x, 52);
    }
    else
        store_PHSx(x, 52); //SAVE 150% OR MORE THAN 150% CALIBRATION VALUE OF Ib
}

/******************************************************************
A/B PHASE TOTAL POSITIVE ENERGY GAIN CALIBRATION
PARAMETER adj_value IS THE GIVEN ERROR VALUE FOR CALIBRATION TABLE
PARAMETER x?IS GPQA/GPQB
 ********************************************************************/
void store_GPQx(unsigned char x, unsigned char eex) {
    if (x == GPQA)
        store_data(2, eex, DataComm.wTemp16);
    else if (x == GPQB)
        store_data(2, eex + 2, DataComm.wTemp16);
}

void WGAIN_adj(int adj_value, unsigned char x) {
    int tmp;
    long temp;
    unsigned int adjFlag;
    read_data(2, (x * 2 + 38));
    adjFlag = DataComm.wTemp16;
    if (Current < (Ib / 5 + 25)) //CALIBRATE LESS THAN 20%Ib (SMALL CURRENT),ADJUST POSITIVE POWER BIAS SLIGHTLY
    {
#ifdef METER_TYPE == 2
        temp = (long) adj_value * (Vol / 10) * (Ib / 10);
#else
        temp = (long) adj_value * (Vol / 10) * (Ib / 20);
#endif
        temp /= 100;
        RN8209_ReadData(x + 0x05, DataComm.ucTempBuf, 2);
        tmp = DataComm.wTemp16;
        temp = (long) tmp - temp;
        if (temp > 32767)
            DataComm.wTemp16 = 32767;
        else if (temp < (-32768))
            DataComm.wTemp16 = (-32768);
        else
            DataComm.wTemp16 = temp;
        RN8209_WriteData(x + 0x05, DataComm.ucTempBuf, 2);
        store_GPQx(x, 20);
    } else //SAVE 20% OR MORE THAN 20% Ib
    {
        temp = (((long) (-adj_value) * 32768) / (10000 + adj_value));
        RN8209_ReadData(x, DataComm.ucTempBuf, 2);
        tmp = DataComm.wTemp16;
        temp += (long) tmp;
        if (temp > 32767)
            DataComm.wTemp16 = 32767;
        else if (temp < (-32768))
            DataComm.wTemp16 = (-32768);
        else
            DataComm.wTemp16 = temp;
        RN8209_WriteData(x, DataComm.ucTempBuf, 2);
#ifdef METER_TYPE == 2
        if (Current < (Ib + 500)) //SAVE LESS THAN 150% CALIBRATION VALUE OF Ib
#else
        if (Current < (Ib + 1000)) //SAVE LESS THAN 150% CALIBRATION VALUE OF Ib
#endif
        {
            store_GPQx(x, 24);
            if (adjFlag == 0)
                store_GPQx(x, 48);
        }
        else
            store_GPQx(x, 48); //SAVE 150% AND MORE THAN 150% CALIBRATION VALUE OF Ib
    }
}

/******************************************************************
A/B PHASE CURRENT VALID VALUE BIAS CALIBRATION,PARAMETER IS IARMSOS/IBRMSOS
 ********************************************************************/
void IOFFSET(unsigned char x) {
    unsigned char i;
    long lave = 0;
    DataComm.wTemp16 = 0;
    RN8209_WriteData(x, DataComm.ucTempBuf, 2);
    for (i = 0; i < 11; i++) {
    	UnWTD(); //
        do {
            RN8209_ReadData(IF, DataComm.ucTempBuf, 1);
        }        while ((DataComm.ucTempBuf[0] & 0x01) < 1);
        if (i > 0) {
            RN8209_ReadData(x + 0x14, DataComm.ucTempBuf, 3);
            if (DataComm.ucTempBuf[2] >= 0x80)
                DataComm.ucTempBuf[3] = 0xFF;
            else
                DataComm.ucTempBuf[3] = 0x00;
            lave += DataComm.lTemp32;
        }
    }
    lave /= 10;
    lave = (-(lave * lave));
    DataComm.wTemp16 = ((lave >> 8) & 0x0000FFFF);
    RN8209_WriteData(x, DataComm.ucTempBuf, 2);
	if (x == IARMSOS)
		E2P_Write(Adj_Para_IARMSOS, DataComm.ucTempBuf, 2); //     store_data(2, 16, DataComm.wTemp16);
	else if (x == IBRMSOS)
		E2P_Write(Adj_Para_IBRMSOS, DataComm.ucTempBuf, 2);//
}

/******************************************************************
A/B PHASE POSITIVE POWER BIAS CALIBRATION,PARAMETER IS APOSA/APOSB
 ********************************************************************/
void POFFSET() {

}

/******************************************************************
READ EEPOME DATA
 ********************************************************************/
void read_data(unsigned char lenth, unsigned char add) {
    unsigned char i;
//    delay_ms(1);
//    for (i = 0; i < lenth; i++)
//        DataComm.ucTempBuf[i] = ReadEE(add + i);
}

/******************************************************************
SAVE EEPOME DATA
 ********************************************************************/
void store_data(unsigned char lenth, unsigned char add, unsigned long data) {
    unsigned char i;
    unsigned char store_d[6];
    for (i = 0; i < lenth; i++) {
        store_d[i] = data;
        data >>= 8;
    }
    for (i = 0; i < lenth; i++) {
        if (WriteEE(add + i, store_d[i]) == 0) {
            if (WriteEE(add + i, store_d[i]) == 0) {
                Flag_RN.error = 1;
                break;
            } else
                Flag_RN.error = 0;
        } else
            Flag_RN.error = 0;
    }
}

/******************************************************************
WHEN THE ELECTRONIC METER IS CUMULATED TO 1 kWH,SAVE THE FUNCTION
 ********************************************************************/
void store_old(void) {
    read_data(4, 42); //READ EEPROM ENERGY DATA
    PoldTemp = DataComm.lTemp32 + (Power >> 8); //UPDATE ENERGY DATA
    store_data(4, 42, PoldTemp); //SAVE ENERGY DATA
    Power_comp = Power = 0; //CLEAR 1 kWH ENERGY DATA
    //  store_data(1, 71, Power >> 8);                          //SAVE ENERGY DATA FOR LESS THAN 1 kWH
    RN8209_ReadData(PFCNT, DataComm.ucTempBuf, 2); //READ RN8209 PFCNT
    store_data(2, 38, DataComm.wTemp16); //SAVE PFCNT
}

/******************************************************************
 ********************************************************************/
void store_energerdata(void) {
    store_data(1, 71, Power >> 8); //SAVE ENERGY DATA FOR LESS THAN 1 kWH
    store_data(2, 46, PTemp); //THE IMPLUSE NUMBER WITH LESS 0.01 kWH ENERGY
    RN8209_ReadData(PFCNT, DataComm.ucTempBuf, 2); //READ RN8209 PFCNT
    store_data(2, 38, DataComm.wTemp16); //SAVE PFCNT
}

/******************************************************************
 READ EEPOM RECOVERED 8209 SET VALUE
 ********************************************************************/
void EEPROMdata_init(void) {
    unsigned char i,temp[5];
    WORD data;

    DataComm.ucTempBuf[1] = DataComm.ucTempBuf[0] = 0x58;
    E2P_Read((char*) &temp[0], Adj_Para_IARMSOS, 2);
    RN8209_WriteData(IARMSOS, (char*) &temp[0], 2); //A PHASE CURRENT BIAS CALIBRATION
    E2P_Read((char*) &temp[0], Adj_Para_IBRMSOS, 2);
    RN8209_WriteData(IBRMSOS, (char*) &temp[0], 2); //B PHASE CURRENT BIAS CALIBRATION
//    RN8209_WriteData(APOSA, DataComm.ucTempBuf, 2); //A PHASE ACTIVE POWER BIAS CALIBRATION
//    RN8209_WriteData(APOSB, DataComm.ucTempBuf, 2); //B PHASE ACTIVE POWER BIAS CALIBRATION
    RN8209_WriteData(GPQA, &temp[0], 2); //A PHASE ACTIVE ENERGY GAIN CALIBRATION
    RN8209_WriteData(GPQB, &temp[0], 2); //B PHASE ACTIVE ENERGY GAIN CALIBRATION
    E2P_Read((char*) &temp[0], Adj_Para_PHSA, 2);
    RN8209_WriteData(PHSA, (char*) &temp[0], 1); //A PHASE CALIBRATION;
    E2P_Read((char*) &temp[0], Adj_Para_PHSB, 2);
    RN8209_WriteData(PHSB, (char*) &temp[0], 1); //B PHASE CALIBRATION

    E2P_Read((char*) &data.byte[0], Adj_Para_Kv, 2);
	rn8209a_calib.kv = data.dbyte;

	E2P_Read((char*) &data.byte[0], Adj_Para_Ka, 2);
	rn8209a_calib.ka = data.dbyte;
	E2P_Read((char*) &data.byte[0], Adj_Para_Kb, 2);
	rn8209a_calib.kb = data.dbyte;

    data.dbyte = START_THOLD;
    RN8209_WriteData(PSTART, 0x0000, 2); //START THRESHOLD
    data.dbyte = 0x0003; // A PHASE CURRENT GAIN IS 16(SHUNTER),B PHASE CURRENT GAIN IS 1(CT),PHASE VOLTAGE GAIN IS 1,START CURRENT CHANNEL B
    RN8209_WriteData(SYSCON, &data.byte[0], 2);
#ifdef METER_TYPE == 2
    data.dbyte = 0xEE00; //B PHASE CURRENT GAIN ADJUST SLIGHTLY TO BE CONSISTENT WITH A PHASE CURRENT
#else
    DataComm.wTemp16 = 0xB334;
#endif
    RN8209_WriteData(IBGAIN, &data.byte[0], 2);
    data.dbyte = 0x0003; //INTERRUP REQUESTS TO BE SET,ENABLE THE DATA TO UPDATE INTERRUPT
    RN8209_WriteData(EMUCON, &data.byte[0], 2);
    data.byte[0] = 0x01;
    RN8209_WriteData(IE, &data.byte[0], 1);
}

/*******************************************************************
METERING CHANNEL SELECTION
PARAMETER X IS TO SELECT A CHANNEL FOR 0, AND SELECT B CHANNEL FOR ONE
 ********************************************************************/
void CF_OUT(unsigned char x) {
    RN8209_ReadData(EMUSTATUS, DataComm.ucTempBuf, 3);
    if (((DataComm.ucTempBuf[2] & 0x20) >> 5) != x) {
    	RN8209_CLR_CS();
        SPI_WriteByte(0xEA);
        SPI_WriteByte(0xE5);
        if (x) //METERING CHANNEL SELECTS B PHASE 0x100
        {
            SPI_WriteByte(0xEA);
            SPI_WriteByte(0xA5);
        } else //METERING CHANNEL SELECTS A PHASE 0x0040
        {
            SPI_WriteByte(0xEA);
            SPI_WriteByte(0x5A);
        }
        SPI_WriteByte(0xEA);
        SPI_WriteByte(0xDC);
        RN8209_SET_CS();
    }
}

//********************************************************************************
//SWITCH PULSE CONSTANT
//********************************************************************************

void select_KWh_pulse(void) {
#ifdef METER_TYPE == 2
	DataComm.wTemp16 = 0x948; //800imp
#else
			if (Pulse_select)
			DataComm.wTemp16 = 0x948; //800imp
			else
			DataComm.wTemp16 = 0x4a4;//1600imp
#endif
	RN8209_WriteData(HFCONST, DataComm.ucTempBuf, 2);
}

//********************************************************************************
//CURRENT POINT SWITCH
//********************************************************************************

void read_adjust(unsigned char x) {
    if (Flag_RN.use_a) {
        read_data(1, x);
        RN8209_WriteData(PHSA, DataComm.ucTempBuf, 1); //A PHASE CALIBRATION
        if (x < 48)
            read_data(2, 24);
        else
            read_data(2, 48);
        RN8209_WriteData(GPQA, DataComm.ucTempBuf, 2); //A PHASE ACTIVE ENERGY GAIN CALIBRATION
    } else if (Flag_RN.use_b) {
        read_data(1, x + 2);
        RN8209_WriteData(PHSB, DataComm.ucTempBuf, 1); //B PHASE CALIBRATION
        if (x < 48)
            read_data(2, 26);
        else
            read_data(2, 50);
        RN8209_WriteData(GPQB, DataComm.ucTempBuf, 2); //B PHASE ACTIVE ENERGY GAIN CALIBRATION
    }
}

void Current_select(void) {
    if (Current < (Ib / 5)) {
        if (Current_ID != 0)
            read_adjust(28);
        Current_ID = 0;
    }
#ifdef METER_TYPE == 2
else if (Current > (Ib / 5 + 25) && Current < (Ib + 500))
#else
else if (Current > (Ib / 5 + 25) && Current < (Ib + 1000))
#endif
    {
        if (Current_ID != 1)
            read_adjust(29);
        Current_ID = 1;
    }
#ifdef METER_TYPE == 2
else if (Current > (Ib + 550))
#else
else if (Current > (Ib + 1050))
#endif
    {
        if (Current_ID != 2)
            read_adjust(52);
        Current_ID = 2;
    }
}

//********************************************************************************
//INIT FUNCTION 8209 97560
//********************************************************************************

void RN8209_Init(void) {
	WORD data, ia_offset,ib_offset,pa_offset, pb_offset,\
	ra_offset,rb_offset, pha_calib,phb_calib,ga_calib,gb_calib;
	char temp[4];
	DWORD temp_data;

	E2P_Read((char*) &data.byte[0], Adj_Para_Ka, 3);
	rn8209a_calib.ka = data.dbyte;
	if ((rn8209a_calib.ka > 0x1388)||(rn8209a_calib.ka < 0x07D0)){
		temp_data.long_val =  rn8209a_calib.ka = 0x0FA0;
		E2P_Write(Adj_Para_Ka, &temp_data.byte[0], 3);
	}
	E2P_Read((char*)&data.byte[0], Adj_Para_Kb, 3);
	rn8209a_calib.kb = data.dbyte;
	if ((rn8209a_calib.kb > 0x1388)||(rn8209a_calib.kb < 0x07D0)){
		temp_data.long_val =  rn8209a_calib.kb = 0x0FA0;
		E2P_Write(Adj_Para_Kb, &temp_data.byte[0], 3);
	}
	E2P_Read((char*) &data.byte[0], Adj_Para_Kv, 2);
	rn8209a_calib.kv = data.dbyte;
	if ((rn8209a_calib.kv > 0x02BC)||(rn8209a_calib.kv < 0x012C)){
		data.dbyte = rn8209a_calib.kv = 0x0244;
		E2P_Write(Adj_Para_Kv, &data.byte[0], 2);
	}


//	E2P_Read((char*) &ia_offset.byte[0], Adj_Para_IARMSOS, 2);
//	E2P_Read((char*) &ib_offset.byte[0], Adj_Para_IBRMSOS, 2);
	ia_offset.dbyte = 0xFE00;
	ib_offset.dbyte = 0xFFFF;

//	E2P_Read((char*) &ga_calib.byte[0], Adj_Para_GPQA, 2);
//	E2P_Read((char*) &gb_calib.byte[0], Adj_Para_GPQB, 2);
//	E2P_Read((char*) &pha_calib.byte[0], Adj_Para_PHSA, 2);
//	E2P_Read((char*) &phb_calib.byte[0], Adj_Para_PHSB, 2);


	ga_calib.dbyte = 0xF7BE;
	gb_calib.dbyte = 0xFBD8;// 0x86
	pha_calib.dbyte = 0x09;
	phb_calib.dbyte = 0x13;//0x88

	pa_offset.dbyte = 0x0000;
	pb_offset.dbyte = 0x0201;
	ra_offset.dbyte = 0x0001;
	rb_offset.dbyte = 0x0001;

//	E2P_Read((char*) &pa_offset.byte[0], Adj_Para_APOSA, 2);
//	E2P_Read((char*) &pb_offset.byte[0], Adj_Para_APOSB, 2);
//	E2P_Read((char*) &ra_offset.byte[0], Adj_Para_RPOSA, 2);
//	E2P_Read((char*) &rb_offset.byte[0], Adj_Para_RPOSB, 2);


	SPI_Init_RN(); //INIT SPI
	RN8209_CLR_CS();
	SPI_WriteByte(0xEA);
	SPI_WriteByte(0xE5);
	RN8209_SET_CS();	DelayUs(1);
	RN8209_CLR_CS();
	SPI_WriteByte(0xEA);
	SPI_WriteByte(0x5A);
	RN8209_SET_CS();
	DelayUs(1);
	RN8209_CLR_CS();
	data.dbyte = CONST_E;
	RN8209_WriteData(HFCONST,(char*) & data.byte[0], 2);
	RN8209_WriteData(IARMSOS, (char*) &ia_offset.byte[0], 2); //A PHASE CURRENT BIAS CALIBRATION
	DelayMs(1);
	data.dbyte = 0x0000;
	RN8209_WriteData(APOSA, (char*) &pa_offset.byte[0], 2);
	DelayMs(1);
	RN8209_WriteData(GPQA, (char*) &ga_calib.byte[0], 2);
	DelayMs(1);
	RN8209_WriteData(PHSA, (char*) &pha_calib.byte[0], 1);
	DelayMs(1);
	RN8209_WriteData(RPOSA, (char*) &ra_offset.byte[0], 2);
	DelayMs(1);

	RN8209_WriteData(APOSB, (char*) &pb_offset.byte[0], 2);
	DelayMs(1);

	RN8209_WriteData(IBRMSOS, (char*) &ib_offset.byte[0], 2); //B PHASE CURRENT BIAS CALIBRATION
	DelayMs(1);
	RN8209_WriteData(GPQB, (char*) &gb_calib.byte[0], 2);
	DelayMs(1);
	RN8209_WriteData(PHSB, (char*) &phb_calib.byte[0], 1);
	DelayMs(1);
	RN8209_WriteData(RPOSB, (char*) &rb_offset.byte[0], 2);

	data.dbyte = 0x0000;
	RN8209_WriteData(PSTART, (char*) &data.byte[0], 2);
	RN8209_WriteData(QSTART, (char*) &data.byte[0], 2);

	data.dbyte = 0x0043;
	RN8209_WriteData(SYSCON, (char*) &data.byte[0], 2);
	data.dbyte = 0x8203;
	RN8209_WriteData(EMUCON, (char*) &data.byte[0], 2);
	data.dbyte = 0xFD9F;
	RN8209_WriteData(PFCNT, (char*) &data.byte[0], 2);
	data.dbyte = 0xAF01;
	RN8209_WriteData(IBGAIN, (char*) &data.byte[0], 2);
	RN8209_CLR_CS();
	SPI_WriteByte(0xEA);
	SPI_WriteByte(0xDC);
	RN8209_SET_CS();
	DelayMs(1);
}

//********************************************************************************
//RECOVER ENERGY DATA
//********************************************************************************

void re_power_data(void) {
	//unsigned temp_p;
	read_data(2, 38);
	RN8209_WriteData(PFCNT, DataComm.ucTempBuf, 2); //RECOVER THE LAST TIME POWER-OFF PFCNT
	read_data(1, 71); //READ DECIMAL PART DATA
	Power = DataComm.ucTemp8 | (DataComm.ucTemp8 << 8);
	if ((Power >> 8) > 99) //IF THE DECIMAL PART DATA IS LARGER THAN 1KWH,PLEASE CLEAR
		Power = 0;
	Power_comp = Power;
	read_data(2, 46); //RECOVER THE PULSE NUMBER LAST TIME THAT THE ENRGY IS LESS THAN 0.01KWH

#ifdef METER_TYPE == 2
	if (DataComm.wTemp16 > 8) {
		PTemp = 0;
	} else
		PTemp = DataComm.wTemp16;
#else
	if (DataComm.wTemp16 > 16) {
		PTemp = 0;
	} else
	PTemp = DataComm.wTemp16;

#endif
}
unsigned char RN8209_Check(void){


}
unsigned char RN8209_Calib(void) {
	unsigned long v_temp, temp[4];
	unsigned char str[2] = { 0x00, 0x00 };
	DWORD data;

	if (rn8209a_calib.Status_Cal == 1) {
		if ((rn8209a_calib.ID_IEC[0] == 0x200A) && (rn8209a_calib.ID_IEC[1] == 0x200B)
				&& (rn8209a_calib.ID_IEC[2] == 0x200C)&& (rn8209a_calib.ID_IEC[3] == 0x2003)) {
			if (!memcmp((char*) &rn8209a_calib.I_CAL[2], (char*) str, 2)) {// offset current
				IOFFSET(IARMSOS);
				IOFFSET(IBRMSOS);
				rn8209a_calib.Status_Cal = 0;
				rn8209a_calib.count_id = 0;
			}
			else{// calib U, I
				v_temp = BCD4_LongA((char*)&rn8209a_calib.V_CAL[0]);
				VGAIN_adj(v_temp);
				v_temp = BCD4_LongA((char*)&rn8209a_calib.I_CAL[0]);
				IGAIN_adj(v_temp/10);
				rn8209a_calib.Status_Cal = 0;
				rn8209a_calib.count_id = 0;
			}
		}
	}
	else if (rn8209a_calib.Status_Cal == 2) {// calib at 1.0L
		rn8209a_calib.Status_Cal = 0;
		RN8209_ReadData(POWERPA, (char*)&data.byte[0],4);
		v_temp = data.long_val;
		RN8209_ReadData(POWERPB, (char*)&data.byte[0],4);
		if(v_temp > data.long_val){
			E2P_Write(Adj_Para_APOSA, (char*)&rn8209a_calib.P_Cal_10L[2], 2);
			RN8209_WriteData(APOSA, (char*) &rn8209a_calib.P_Cal_10L[2], 2); //RECOVER THE LAST TIME POWER-OFF PFCNT
		}else{
			E2P_Write(Adj_Para_APOSB, (char*)&rn8209a_calib.P_Cal_10L[2], 2);
			RN8209_WriteData(APOSB, (char*) &rn8209a_calib.P_Cal_10L[2], 2);
		}
	} else if (rn8209a_calib.Status_Cal == 3) {// calib at 0.5L
		rn8209a_calib.Status_Cal = 0;
		RN8209_ReadData(POWERPA, (char*)&data.byte[0],4);
		v_temp = data.long_val;
		RN8209_ReadData(POWERPB, (char*)&data.byte[0],4);
		if (v_temp > data.long_val){
			E2P_Write(Adj_Para_PHSA, (char*)&rn8209a_calib.P_Cal_05L[2], 2);
			RN8209_WriteData(PHSA, (char*) &rn8209a_calib.P_Cal_05L[2], 1); //RECOVER THE LAST TIME POWER-OFF PFCNT
		}else{
			E2P_Write(Adj_Para_PHSB, (char*)&rn8209a_calib.P_Cal_05L[2], 2);
			RN8209_WriteData(PHSB, (char*) &rn8209a_calib.P_Cal_05L[2], 1);
		}

	} else if (rn8209a_calib.Status_Cal == 4) {
		rn8209a_calib.Status_Cal = 0;

	}
}

void RN8209_Process() {

	RN8209_ReadData(URMS, (char*) &rn8209a_rms.V_RMS.byte[0], 3);
	RN8209_ReadData(IARMS, (char*) &rn8209a_rms.Ia_RMS.byte[0], 3);
	RN8209_ReadData(POWERPA, (char*) &rn8209a_rms.Pa_RMS.byte[0], 4);
	RN8209_ReadData(IBRMS, (char*) &rn8209a_rms.Ib_RMS.byte[0], 3);
	RN8209_ReadData(POWERPB, (char*) &rn8209a_rms.Pb_RMS.byte[0], 4);
	RN8209_ReadData(UFREQ, (char*) &rn8209a_rms.F_RMS.byte[0], 2);
	RN8209_ReadData(POWERPA, (char*) &rn8209a_rms.Pa_RMS.byte[0], 4);
	RN8209_ReadData(POWERQ, (char*) &rn8209a_rms.Q_RMS.byte[0], 4);
	RN8209_ReadData(ENERGYP2, (char*) &rn8209a_rms.ENERGY_P.byte[0], 3);
	RN8209_ReadData(ENERGYQ2, (char*) &rn8209a_rms.ENERGY_Q.byte[0], 3);
	RN8209_ReadData(PFCNT, (char*) &rn8209a_rms.PF_RMS.byte[0], 2);
	RN8209_ReadData(UFREQ, (char*) rn8209a_rms.F_RMS.byte, 2);
	RN8209_ReadData(DEVICEID, (char*) &rn8209a_rms.ID.byte[0], 3);

	if(rn8209a_rms.ID.val != 0x00820900)
		EventFlag.States |= F_HardErr;

	rn8209a_rms.V_RMS.val = (rn8209a_rms.V_RMS.val * 100) / rn8209a_calib.kv;
	Long_BCD4((char*) rn8209a_rms_bcd.V_RMS, rn8209a_rms.V_RMS.val);

	if (rn8209a_rms.Ia_RMS.val >= rn8209a_rms.Ib_RMS.val)
		rn8209a_rms.I_RMS.val = rn8209a_rms.Ia_RMS.val / rn8209a_calib.ka;
	else
		rn8209a_rms.I_RMS.val = rn8209a_rms.Ib_RMS.val / rn8209a_calib.kb;
	Long_BCD4((char*) rn8209a_rms_bcd.I_RMS, rn8209a_rms.I_RMS.val);

	if((rn8209a_rms.Pa_RMS.val < -8292)||(rn8209a_rms.Pb_RMS.val < -8292))
		Flag.Power_dir = 1;// revert current
	else
		Flag.Power_dir = 0;
	if(rn8209a_rms.Pa_RMS.val <= rn8209a_rms.Pb_RMS.val)
		rn8209a_rms.P_RMS.val = rn8209a_rms.Pb_RMS.val;
	else
		rn8209a_rms.P_RMS.val = rn8209a_rms.Pa_RMS.val;

	if (rn8209a_rms.Pa_RMS.val >= rn8209a_rms.Pb_RMS.val) {
		CF_OUT(0); // select channel A
		rn8209a_rms.PF_RMS.val = rn8209a_rms.Pa_RMS.val
				/ sqrt(
						rn8209a_rms.Pa_RMS.val * rn8209a_rms.Pa_RMS.val
								+ rn8209a_rms.Q_RMS.val
										* rn8209a_rms.Q_RMS.val);
		Long_BCD4((char*) rn8209a_rms_bcd.PF_RMS, rn8209a_rms.PF_RMS.val);
	} else {
		CF_OUT(1); // select channel B
		rn8209a_rms.PF_RMS.val = rn8209a_rms.Pb_RMS.val
				/ sqrt(
						rn8209a_rms.Pb_RMS.val * rn8209a_rms.Pb_RMS.val
								+ rn8209a_rms.Q_RMS.val
										* rn8209a_rms.Q_RMS.val);
		Long_BCD4((char*) rn8209a_rms_bcd.PF_RMS, rn8209a_rms.PF_RMS.val);
	}
	vse1t_de.total_p.long_val = rn8209a_rms.Active_energy += rn8209a_rms.ENERGY_P2.val/8;
	Long_BCD4((char*) rn8209a_rms_bcd.ENERGY_P, rn8209a_rms.ENERGY_P.val);

	if(rn8209a_rms.Pa_RMS.val > rn8209a_rms.Pb_RMS.val){
		if	(((rn8209a_rms.Pa_RMS.val >0)&&(rn8209a_rms.Q_RMS.val>0))||((rn8209a_rms.Pa_RMS.val <0)&&(rn8209a_rms.Q_RMS.val>0))){// lag
			vse1t_de.total_q_lag.long_val = rn8209a_rms.Q_Lag += rn8209a_rms.ENERGY_Q2.val/8;
		}
		else{
			vse1t_de.total_q_lead.long_val = rn8209a_rms.Q_Lead += rn8209a_rms.ENERGY_Q2.val/8;
		}
	}

	rn8209a_rms.F_RMS.val = 35795450/(8*rn8209a_rms.F_RMS.val);
	Long_BCD4((char*) rn8209a_rms_bcd.F_RMS, rn8209a_rms.F_RMS.val);
}
#endif
