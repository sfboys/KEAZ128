#include "HalUart.h"

void HalUartInit(void)
{
    UART_ConfigType UART_Config={{0}};	
    UART_Config.sctrl1settings.bits.bM=0;  	/* 8 bit mode*/	
    UART_Config.sctrl1settings.bits.bPe=0;	/* No hardware parity generation or checking*/	
    UART_Config.bSbns=0;					/* One stop bit*/	
    UART_Config.sctrl2settings.bits.bRe=1;	/* Enable Receiver*/	
    UART_Config.sctrl2settings.bits.bTe=1;	/* Enable Transmitter*/	
    UART_Config.u32SysClkHz = 20000000;   	/* Bus clock in Hz*/	
    UART_Config.u32Baudrate = 19200;     	/* UART baud rate */	
    UART_Init(UART2,&UART_Config);			/*Initialization of UART utilities*/
}
