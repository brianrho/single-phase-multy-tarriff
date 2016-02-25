
#ifndef		_KEY_PROCESS_H
#define		_KEY_PROCESS_H


#define			KEY_EXIT_INV		20

#define			KEY_NULL		0x00
#define			KEY_VAL0		0x01
#define			KEY_VAL1		0x02
#define			KEY_VAL2		0x03

#define			KEY_START_F		0x01
#define			KEY_UNVAL_F		0x02

typedef struct
{

	int8u 	uckeyFlag;
	int16u  	ucHafeSCnt;
	int8u 	ucVal;
	//close time
	int8u 	ucTo;	//
	int8u 	ucTm;	//
	int8u 	KeyDisp;
	//int8u 	ErrCnt;
}KEY_T;

//key
extern	KEY_T	gsKey;//

#ifdef HARDWARE_TWO
//page
extern const int8u  ucPageTbl[8];//ҳ
#else
//page
extern const int8u  ucPageTbl[7];//ҳ
#endif


void KeyInit(void);

void GetKeyVal(void);
void KeyProcess(void);

#endif

