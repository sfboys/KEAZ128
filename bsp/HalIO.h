#ifndef  __HALIO_H_
#define  __HALIO_H_

#include "common.h"
#include "gpio.h"
#include "kbi.h"

typedef enum
{
	OFF =0,
	RED,
	GREEN,
	BLUE,
    WHITE
}LED_ENUM;

void SetLedDisplay(LED_ENUM status);
#endif