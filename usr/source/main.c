#include "led.h"
#include "includes.h"
#define LED_STK_SIZE 64
#define TASK_LED_PRIO 2

OS_STK taskledstk[LED_STK_SIZE];
void taskled(void *pdata);

void CreatTask()
{
	ledInit();
	OS_CPU_SysTickInit(400000);
	OSTaskCreate(taskled,(void *)0,&taskledstk[LED_STK_SIZE-1],TASK_LED_PRIO);
}

void taskled(void *pdata)
{
	while(1)
	{
		ledon();
		OSTimeDly (50);
		ledoff();
		OSTimeDly (50);
	}
}

int main(void)
{
	OSInit ();
	CreatTask ();
	OSStart ();
}

