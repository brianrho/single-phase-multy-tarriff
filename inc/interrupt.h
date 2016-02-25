#ifndef	_INTERRUPT_H
#define	_INTERRUPT_H

#define TM_20ms           20
#define TM_35ms           35
#define	TM_100ms          100

#define	TM_200ms          200
#define TM_500ms          500//5000
#define TM_600ms          600
#define	TM_1000ms         1000
#define	TM_1500ms         3000//1500//9000
#define TM_10000ms        3000//10000

#define	T_1ms             32
#define	T_5ms             160




#define         PSUartIN        P1IN
#define 		PSUartOUT       P1OUT
#define         PSUartIFG       P1IFG
#define         PSUartIES       P1IES
#define         PSUartIE        P1IE
#define         PSUartDIR       P1DIR

#define			P_SimRXD		BIT0
#define			P_SimTXD		BIT7

typedef struct
{
	int8u 	BitCount;
	int8u	Baud;
	int8u 	Flag;
	int8u 	ParityBit;
	int16u 	BufTmp;
	int16u 	SendChar;
	int8u	RxStart;
	int8u 	TxStart;	
}UART_SIM_T;

//simulative serial port
extern	UART_SIM_T		gUartSim;//Ä£Äâ´®¿Ú
void SimSendChar(int8u ucChar);

#endif
