
#ifndef	_SOFT_UART_H
#define	_SOFT_UART_H


typedef struct
{
 //baud rate
//²¨ÌØÂÊ
	int8u	UartBR;	
	int8u  	UartSendFlag;
	int8u 	UartRxFlag;
	int8u 	UartBuff;
	
}SOFT_UART_T;


SOFT_UART_T		gSoftUart;


#endif
