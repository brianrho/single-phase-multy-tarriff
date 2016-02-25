
#ifndef		_C_TARGET_H
#define		_C_TARGET_H

#define	MCLK_FREQ		8

typedef enum {
	//REST,//reset
	REST,//复位
	//POWN,//off-power
	POWN,//掉电
	// WAKEUP  //working
	WAKEUP
//工作

} SYS_INT_T;

typedef enum {
	//UART0,//serial port 0
	UART0,//串口0
	//UART1,//serial port 1
	UART1,//串口1
	//UART2//serial port 2
	UART2
//串口2

} UART_NO_T;

typedef enum {
	BAUD9600 = '5', /*9600*/
	BAUD4800 = '4', /*4800*/
	BAUD2400 = '3', /*2400*/
	BAUD1200 = '2', /*1200*/
	BAUD600 = '1', /*1200*/
	BAUD300 = '0'
/*300*/
} UART_BAUD_T;

typedef enum {
	EVEN_8BIT = 1,
	EVEN_7BIT = 2,
	ODD_8BIT = 3,
	ODD_7BIT = 4,
	NO_8BIT = 5,
	NO_7BIT = 6,

} UART_MODE_T;

/*****************************************************************
 System Parameter Initiation
 *****************************************************************/
#define	System_Reset	0x00
#define	Power_Off		0x01
#define	Power_On		0x02
/*******************************************************
 串口
 *******************************************************/
#define     UART0_RX_BUF         U0RXBUF
#define     UART0_TX_BUF         U0TXBUF

#define     UART1_RX_BUF         U1RXBUF
#define     UART1_TX_BUF         U1TXBUF
/*
 #define     UART0_RX_ON()       (U0IE|=URXIE0)
 #define     UART0_RX_OFF()      (U0IE&=~URXIE0)
 #define     UART0_TX_ON()       (U0IE|=UTXIE0)
 #define     UART0_TX_OFF()      (U0IE&=~UTXIE0)
 ME1|=UTXE0|URXE0;
 */
/*
 #define     UART0_RX_ON()       (ME1|=URXE0)
 #define     UART0_RX_OFF()      (ME1&=~URXE0)
 */
#define     UART0_RX_ON()       (U0IE|=URXIE0)
#define     UART0_RX_OFF()      (U0IE&=~URXIE0)

#define     UART0_TX_ON()       (U0IE|=UTXIE0)
#define     UART0_TX_OFF()      (U0IE&=~UTXIE0)

#define     UART1_RX_ON()       (U1IE|=URXIE1)
#define     UART1_RX_OFF()      (U1IE&=~URXIE1)

#define     UART1_TX_ON()       (U1IE|=UTXIE1)
#define     UART1_TX_OFF()      (U1IE&=~UTXIE1)

#define       TB_DELAY_ON       TBCCTL0 = CCIE
#define       TB_DELAY_OFF      TBCCTLO=0

//#define		BASE_TIME_ON()		BTCTL&=~BTHOLD	//starting BASEtime
#define		BASE_TIME_ON()		BTCTL&=~BTHOLD	//起动BASEtime
//#define		BASE_TIME_OFF()		BTCTL|=BTHOLD	//starting BASEtme
#define		BASE_TIME_OFF()		BTCTL|=BTHOLD	//起动BASEtime

void Beep(int8u Val);

////#define		POW_UP		0x01	//currently on-power
//#define		POW_UP		0x01	//当前有电
//#define		
/*********************************
 //external quoted function
 *********************************/
void DelayUs(int16u time);

void DelayMs(int16u time);

void SysInit(SYS_INT_T type);

void SetUart(UART_NO_T ComNo, UART_BAUD_T Baud, UART_MODE_T mode);

void SysInit(SYS_INT_T type);

void UnWTD(void);

void WDTClr(void);

int8u SysChkPW(void);
void LcdInit();
void SystemInit(char Mode);
int8u SysChkPW(void);

void SetBaud(UART_NO_T ComNo, UART_BAUD_T Baud);

int8u ComparaStata(void);

#endif
