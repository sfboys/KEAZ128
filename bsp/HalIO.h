#ifndef  __HALIO_H_
#define  __HALIO_H_

#include "common.h"
#include "gpio.h"
#include "kbi.h"
#include "ics.h"

typedef enum
{
	LED_OFF =0,
	LED_RED,
	LED_GREEN,
	LED_BLUE,
    LED_WHITE
}LED_ENUM;

void SetLedDisplay(LED_ENUM status);
void HalKBIInit(void);
void HalGpioInit(void);
void HalClkInit(void);
#endif

