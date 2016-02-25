
#define		COM_BIT_R	0
#define		COM_BIT_W	2
#define		COM_BIT_r	4

#define		COM_R0		0x00
#define		COM_R1		0x01
#define		COM_R2		0x02
#define		COM_R3		0x03

#define		COM_W0		0x00//
#define		COM_W1		0x04//
#define		COM_W2		0x08//
#define		COM_W3		0x0c//

#define		COM_r0		0x00//
#define		COM_r1		0x10//
#define		COM_r2		0x20//
#define		COM_r3		0x30//


////////////////

 //this displaying meter order can not be changed randomly The data should be gotten in order when reading modules
const  int16u   code  ComDisTab[] =
{

//0x1800 ,            /*total power quantity*/
	0x1800 ,        /*总电电量*/
 // 0x1810           /*total power quantity*/
//	0x1810         /*总电电量*/
 //0x1820            /*total power quantity*/
//	0x1820         /*总电电量*/
 //0x1830           /*total power quantity*/
//	0x1830         /*总电电量*/
 //0x1840           /*total power quantity*/
//	0x1840         /*总电电量*/

};

typedef struct 
{
	int16u ID;
	int16u	Addr;	//
       //int16u  Size;	//communication places
	int16u  Size;	//通讯位数
	int8u 	MemType;
	int8u	Flag;
	
}com_tbl_t;

const com_tbl_t code	ComTbl[]=
{
 //total power quantity
	0x9010,CE_TOTAL_KWH,8,CE_NO,COM_R3+COM_W3,
 //meter number
	0xC004,PARA_ID_OFS,11,PARA_NO,COM_R3+COM_W3,
#if (STS_SUPPORT==1)	
 //download token
//下载token
	0xC400,&ugBuf.gStsRam.gToken,20,RAM_NO,COM_W3,
 //sts key
//sts密钥
	0xC403,STS_NKHO,16,STS_NO,COM_R1+COM_W1,
 //sts key interval time of modification
//sts密钥修改间隔时间	
	0xC402,STS_KEY_TIME,2,STS_NO,COM_R3+COM_W3,
//sgc
	0xC401,STS_SGC,6,STS_NO,COM_R1+COM_W1,
#endif
//RTC
	0xC180,0,14,0,COM_R1+COM_W1,
//	0xC181,0,0,0COM_R1+COM_W1,
 //display parameter
	0xC160,DISP_AUTO_NUM,2,DISP_NO,COM_R1+COM_W1,
	0xC161,DISP_AUTO_TBL0,32,DISP_NO,COM_R1+COM_W1,
	0xC162,DISP_AUTO_TBL1,32,DISP_NO,COM_R1+COM_W1,
	0xC163,DISP_AUTO_TBL2,32,DISP_NO,COM_R1+COM_W1,
	0xC189,DISP_AUTO_INVL,2,DISP_NO,COM_R1+COM_W1,
 //meter calibration parameter
	0xCA00,CE_ADJ_RMS_UK,8,CE_NO,COM_R1+COM_W1,
	0xCA01,CE_ADJ_RMS_IK,8,CE_NO,COM_R1+COM_W1,
	0xCA02,CE_ADJ_RMS_PK,8,CE_NO,COM_R1+COM_W1,
	0xCA03,CE_ADJ_RMS_OFS,8,CE_NO,COM_R1+COM_W1,
	0xCA04,CE_ADJ_RMS_PH,2,CE_NO,COM_R1+COM_W1,
//XPORT 
	0xCB00,IP_CONFIG_OFS,42,XPORT_NO,COM_R1+COM_W1,
	0xCB01,IC_CONFIG_OFS,28,XPORT_NO,COM_R1+COM_W1,
	//0xCB02,0,28,RAM_NO,COM_R1+COM_W1,
	//0xCB03,0,28,RAM_NO,COM_R1+COM_W1,
};

#define			COMTBL_SIZE		(sizeof(ComTbl)/sizeof(com_tbl_t))

