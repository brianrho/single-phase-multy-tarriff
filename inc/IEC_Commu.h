//#define	NULL	0x00
//3 times of password error within 5 minutes is allowed
#define PASSERRDELAYT 5  //5���������������3��
//it will be restored 30 minutes later after locked for password error
#define PASSERRLOCKT  30 //�������������30���Ӻ�Żָ�

#define	SOH		0x01
#define	STX		0x02
#define	ETX		0x03
#define	EOT		0x04
#define	ENQ		0x05
#define	ACK		0x06
#define	BEL		0x07
#define	BS		0x08
#define	TAB		0x09
#define	LF		0x0A
#define	VT		0x0B
#define	FF		0x0C
#define	CR		0x0D
#define	SO		0x0E
#define	SI		0x0F
#define	DLE		0x10
#define	DC1		0x11
#define	DC2		0x12
#define	DC3		0x13
#define	DC4		0x14
#define	NAK		0x15
#define	SYN		0x16
#define	ETB		0x17
#define	CAN		0x18
#define	EM		0x19
#define	SUB		0x1A
#define	ESC		0x1B
#define	FS		0x1C
#define	GS		0x1D
#define	RS		0x1E
#define	US		0x1F

#define	Max1stSize (5+32)
#define	Min1stSize 5

//CommMode
//reading mode
#define DataOut 	'0'		//����ģʽ
//program mode
#define	Program 	'1'		//���ģʽ
//binary mode(HDLC)
#define	HDLC		'2'		//������ģʽ(HDLC)
//factory self-defined 6
#define	Factory6 	'6'		//�����Զ���6
//factory self-defined 7
#define	Factory7 	'7'		//�����Զ���7
//factory self-defined 8
#define	Factory8 	'8'		//�����Զ���8
//factory self-defined 9
#define	Factory9 	'9'		//�����Զ���9 
//no connection
#define	NoCnt		0xFF	//δ����
//Flag
#define	DeviceIDOK		0x01
#define	PasswordP1OK	0x02
#define	PassWordP2OK	0x20

#define	Comm_writed	0x04
#define	Comm_readed	0x08
//ignore programming limitation
#define DeviceOMIT  0x10 //���Ա������


//C Mode BaudRate
#define CBuad_3		'0'
#define	CBaud_6		'1'
#define	CBaud_12	'2'
#define	CBaud_24 	'3'
#define	CBaud_48	'4'
#define	CBaud_96 	'5'
#define	CBaud_192	'6'

//data numbers of readout mode
#define DaOutAllNum	(sizeof(DaOutTab)/sizeof(COMMTAB))
#define DaOutDLANum	10
#define	DaOutDLRNum	10
#define	DaOutDLNum	(DaOutDLANum+DaOutDLRNum)
#define	DaOutXLANum	10
#define	DaOutXLRNum	10
#define	DaOutXLNum	(DaOutXLANum+DaOutXLRNum)
#define DaOutINum	3
#define DaOutVNum	3
#define	DaOutVINum	(DaOutVNum+DaOutINum)
#define	DaOutkWNum	3
#define	DaOutkvarNum 3
#define	DaOutkVANum	3
#define	DaOutPFNum	3
#define	DaOutPowerNum (DaOutkWNum +DaOutkvarNum +DaOutkVANum +DaOutPFNum)

//
#define	DaOutDL_LEN (DaOutDLNum)
#define	DaOutXL_LEN (DaOutDLNum+DaOutXLNum)
#define	DaOutVI_LEN (DaOutDLNum+DaOutXLNum+DaOutVINum)
#define	DaOutPW_LEN (DaOutDLNum+DaOutXLNum+DaOutVINum+DaOutPowerNum)

#define DaOutI_LEN  (DaOutDLNum+DaOutXLNum+DaOutINum)
#define DaOutV_LEN  (DaOutDLNum+DaOutXLNum+DaOutINum+DaOutVNum)

#define	DaOutkW_LEN     (DaOutDLNum+DaOutXLNum+DaOutVINum+DaOutkWNum)
#define	DaOutkvar_LEN   (DaOutDLNum+DaOutXLNum+DaOutVINum+DaOutkWNum+DaOutkvarNum)
#define	DaOutkVA_LEN    (DaOutDLNum+DaOutXLNum+DaOutVINum+DaOutkWNum+DaOutkvarNum+DaOutkVANum)
#define DaOutPF_LEN     (DaOutDLNum+DaOutXLNum+DaOutVINum+DaOutkWNum+DaOutkvarNum+DaOutkVANum+DaOutPFNum)

#define	CommNum		(sizeof(CommTab)/sizeof(IntCOMMTAB))

//0000 1110 0000 0000B
#define 	EN_WR			0x0E00
#define 	EN_FSw			0x0800
#define 	EN_W			0x0400
#define 	EN_R			0x0200
//0000 0001 1100 0000B
#define 	RS_REG			0x01C0
#define 	RS_RAM			0x0040*Mem_RAM
#define     RS_IFlash       0x0040*Mem_IFlash
#define     RS_Flash        0x0040*Mem_Flash 
#define 	RS_FRAM			0x0040*Mem_FRAM
#define 	RS_E2PROM		0x0040*Mem_E2PROM
#define     RS_DFlash       0x0040*Mem_DFlash
//0000 0000 0011 1111B
#define 	RS_LEN			0x003F
#if 1
#define		CommBufSize		250
#else
#define		CommBufSize		120
#endif
#define		EndFrame		0xED
typedef struct
{
	unsigned char Buf[CommBufSize+1];	
	//timing of reception intervals
	unsigned int MdTmr;		//���ռ����ʱ
	//timing of communication connection
	unsigned int CntTmr;	//ͨѶ���Ӷ�ʱ
    unsigned int BufCHK;    //
    //operation mode
	unsigned char Mode;		//����ģʽ
	//buffer pointer
	unsigned char Ptr;		//����ָ��
	//mark the register
	unsigned char Flag;		//��־�Ĵ���
	//communication mode
	unsigned char CommMode;	//ͨѶģʽ
	//readout data and send count
	unsigned char DaOutCnt;	//�������ݷ��ͼ���
	//the BCC when sending
	unsigned char BCC;		//����ʱ��BCC
    unsigned char CHKTM;    //
    //serial port number,serial port 1 is 485, serial port 2 is external module, serial port 0 is infrared virtual serial port
    unsigned char ComId;	//���ںţ�����1��485������2�����ģ�飬����0�Ǻ������⴮��
	unsigned int ProgCnt;
	//password permission     new added level 4 password on 20150630
	unsigned char PassAcc;	//����Ȩ��	20150630�������ļ�����

}IEC_COMM;

typedef struct
{
	unsigned long	ComID;
	char*           Addr;
  	unsigned int 	ComInfo;
} COMMTAB;
typedef struct
{
	unsigned int	ComID;
	char*           Addr;
  	unsigned int 	ComInfo;
} IntCOMMTAB;

extern void IEC_CommProcess(void);
extern void CommInit(void);









