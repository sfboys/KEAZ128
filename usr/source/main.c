#include "HalADC.h"
#include "HalIO.h"
#include "HalUart.h"

#include "includes.h"
#define LED_STK_SIZE 64
#define UART_STK_SIZE 64

#define TASK_LED_PRIO 3
#define TASK_UART_PRIO 2


OS_STK taskLedstk[LED_STK_SIZE];
OS_STK taskUartstk[UART_STK_SIZE];

OS_EVENT *kbiMsgQueue; 
void *queueMsgBuffer[5];


void appLedTask(void *pdata);
void appUartTask(void *pdata);

int main(void)
{
    HalUartInit();
    HalKBIInit();
    HalGpioInit();
	OSInit ();
	OSTaskCreate(appUartTask,(void *)0,&taskUartstk[LED_STK_SIZE-1],TASK_UART_PRIO);
    OSTaskCreate(appLedTask,(void *)0,&taskLedstk[LED_STK_SIZE-1],TASK_LED_PRIO);
    OS_CPU_SysTickInit(400000);
	OSStart ();
    return 0;
}

void appLedTask(void *pdata)
{
    uint16 adcValue =0;
    LED_ENUM ledStatus = LED_OFF ;
    while(1)
    {
        adcValue = GetRheostatVol();
        if(adcValue >3800)
        {
            ledStatus = LED_WHITE ;
        }else if(adcValue > 3000)
        {
            ledStatus = LED_BLUE;
        }else if (adcValue > 2400)
        {
            ledStatus = LED_GREEN;
        }else if (adcValue > 1200)
        {
            ledStatus = LED_RED;
        }else
        {
            ledStatus = LED_OFF;
        }

        SetLedDisplay(ledStatus);

        OSTimeDly (10); //10ms 一个tick ，当前延时100ms
    }
}
//const char *stringA = " SW2 PRESSED" ;
//const char *stringB = " SW2 PRESSED" ;    
void appUartTask(void *pdata)
{
    void *queueMsgPend =NULL ;
    INT8U err= 0; 
    while(1)
    {

        queueMsgPend = OSQPend(kbiMsgQueue, 0, &err); 
        if (err == OS_ERR_NONE)
        { 
            if(*(uint8 *)queueMsgPend == 1)
            {
                 printf("\n  SW2 PRESSED \n");
            }else if(*(uint8 *)queueMsgPend == 2)
            {
                 printf("\n  SW3 PRESSED \n");
            }else 
            {
                printf("\n  errors \n");
            }
        } else
        { 
            printf("\n wait for data err \n");
        } 
    }
}

