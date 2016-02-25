/******************************************************************************
 //key process
 * KeyProcess.C - 按键处理
 * 
 * Copyright Hangzhou East Smart Technology Co.,Ltd.
 * 
 * DESCRIPTION: - 
 *      
 * modification history
 * --------------------
 * 01a, 20feb2011,  written
 * --------------------
 ******************************************************************************/
#include "..\inc\includes.h"
//parameters related to key
KEY_T gsKey;//

//**********************************************************************
//key initialization
// 按键初始化
//**********************************************************************
void KeyInit(void) {
	gsKey.uckeyFlag = 0;

	DisK.MPtr = 0;
	DisK.SPtr = 0;
	DisK.DisMode = DISP_MODE_AUTO;

	P1IES |= BIT2;
	P1IFG &= ~BIT2;
	P1IE |= BIT2;

}
/******************************************************************************
 //mian processing program of key
 * KeyProcess - 按键主处理程序
 * DESCRIPTION: - 
 //invoke once 1S
 * Input: 
 * Output: 
 * Returns: 
 * 
 * modification history
 * --------------------
 * 01a, 20feb2011,  written
 * --------------------
 ******************************************************************************/

/******************************************************************************
 //get key value
 * GetKeyVal -
 * DESCRIPTION: - 
 //process it once of half a second
 * Input: 
 * Output: 
 * Returns: 
 * 
 * modification history
 * --------------------
 * 01a, 20feb2011,  written
 * --------------------
 ******************************************************************************/
void GetKeyVal(void) {

	if (gsKey.uckeyFlag & KEY_START_F) {

		if (Flag.Power & F_PwrUp) {
			if (gsKey.ucTm > 1) {
				return;
			} else if (gsKey.ucTm == 1) {
				gsKey.ucTm = 0;

				if (KEY_UP_RET) {
					gsKey.uckeyFlag &= ~KEY_START_F;
					return;
				}
			}
		}

		if (!KEY_UP_RET) {
			if (gsKey.uckeyFlag & KEY_UNVAL_F) {
				return;
			}

			gsKey.ucHafeSCnt++;
			if (gsKey.ucHafeSCnt > 70)//3*31)
			{
				gsKey.ucVal = KEY_VAL1;
				gsKey.uckeyFlag |= KEY_UNVAL_F;
			}
		}
		//key release
		else {
			gsKey.uckeyFlag &= ~KEY_START_F;
			if (gsKey.uckeyFlag & KEY_UNVAL_F) {
				return;
			}
			//0.5S anti-shaking
			if (1)//gsKey.ucTm==0)	//0.5S,防抖
			{
				gsKey.ucVal = KEY_VAL0;
			}
		}
	} else {
		if (!KEY_UP_RET) {
			gsKey.uckeyFlag |= KEY_START_F;
			gsKey.ucHafeSCnt = 0;
			gsKey.ucTm = 12;
			gsKey.uckeyFlag &= ~KEY_UNVAL_F;
		}
	}
}

#ifdef HARDWARE_TWO
const int8u ucPageTbl[8] = { DISP_PAGE1, DISP_PAGE2, DISP_PAGE3, DISP_PAGE4,
		DISP_PAGE5, DISP_PAGE6, DISP_PAGE7, DISP_PAGE8, };
#else
const int8u ucPageTbl[7]= {
	DISP_PAGE1,DISP_PAGE2,DISP_PAGE3,DISP_PAGE4,
	DISP_PAGE5,DISP_PAGE6,DISP_PAGE7,
};
#endif
//**********************************************************************
//key processing progress
//**********************************************************************
void KeyProcess(void) {

	int8u ucKeyVal;
	int8u ucMaxPtr;

	ucKeyVal = gsKey.ucVal;

	gsKey.ucVal = 0;
	if (gsKey.ucTo > 0) {
		gsKey.ucTo--;
	} else {
		DisK.DisMode = DISP_MODE_AUTO;
		DisK.MPtr = 0;
		DisK.SPtr = 0;
	}
	if (ucKeyVal == KEY_NULL) {
		return;
	}
	//single key processing 
	if (ucKeyVal == KEY_VAL0) {
		//Flag.Run |= R_Disp;
		gsKey.KeyDisp = 1;

		if (DisK.DisMode != DISP_MODE_KEY) {
			if (DisK.DisMode == DISP_MODE_AUTO) {
				DisK.DisPtr = DISP_AUTO_NUM;
			}
			DisK.DisMode = DISP_MODE_CLICK;

			DisK.DisPtr += 1;

			if (DisK.DisPtr > DISP_AUTO_NUM) {
				DisK.DisPtr = 0;
			}
			gsKey.ucTo = KEY_EXIT_INV;
			return;
		}

		gsKey.ucTo = KEY_EXIT_INV;
		DisK.DisMode = DISP_MODE_KEY;

		if (DisK.SPtr == 0) {
			DisK.MPtr++;
			if (DisK.MPtr > DISP_PARA_7) {

				DisK.MPtr = DISP_PARA_1;
			}
			return;
		} else {
			ucMaxPtr = DisK.MPtr - DISP_PARA_1;
			if (ucMaxPtr >= sizeof(ucPageTbl)) {
				ucMaxPtr = 1;
			}
			ucMaxPtr = ucPageTbl[ucMaxPtr];
			DisK.SPtr++;
			if (DisK.SPtr > ucMaxPtr) {

				DisK.SPtr = 1;
			}
		}
	}
	//continue to press the OK key  for 3S
	else if (ucKeyVal == KEY_VAL1) {
		//		Flag.Run |= R_Disp;
		gsKey.KeyDisp = 1;

		DisK.ErrCnt = 60;

		gsKey.ucTo = KEY_EXIT_INV;

		if (DisK.DisMode != DISP_MODE_KEY) {
			DisK.DisMode = DISP_MODE_KEY;

			DisK.MPtr = DISP_PARA_1; //
			DisK.SPtr = 0;
		} else {
			// in the main catalogue
			if (DisK.SPtr == 0) {
				DisK.SPtr = 1;
			}
			//in the secondary catalogue
			else
			//exit key
			{ //
				ucMaxPtr = DisK.MPtr - DISP_PARA_1;
				if (ucMaxPtr >= sizeof(ucPageTbl)) {
					ucMaxPtr = 1;
				}
				ucMaxPtr = ucPageTbl[ucMaxPtr];

				if (DisK.SPtr >= ucMaxPtr) {
					DisK.SPtr = 0;
					DisK.MPtr = DISP_PARA_1;
				}
				//invalid key
				else {

				}
			}
		}
	}
}

