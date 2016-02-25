/******************************************************************************
 //SoftUart.C - this function module has one UART

 * SoftUart.C - 该函数模块一个UART
 * 
 * Copyright Hangzhou East Smart Technology Co.,Ltd.
 * 
 * DESCRIPTION: - 
 *      
 * modification history
 * --------------------
 * 01a, 14feb2011,  written
 * --------------------
 ******************************************************************************/

#define		SOFT_UATT_RX		(P1IN&BIT6)

#define		SOFT_UART_TX(ON)	(ON==1)?(P1OUT|=BIT7):(P1OUT&=~BIT7)			//P1.4

void SoftUartSend(int8u ucCha) {

}

/******************************************************************************
 //SoftUartRx -interrupt vector function

 * SoftUartRx - 中断向量函数
 * DESCRIPTION: - 
 *      
 * Input: 
 * Output: 
 * Returns: 
 * 
 * modification history
 * --------------------
 * 01a, 14feb2011,  written
 * --------------------
 ******************************************************************************/
int8u SoftUartRx(void) {

	return 0;
}

