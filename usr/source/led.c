#include "led.h"

void ledInit()
{  
	CONFIG_PIN_AS_GPIO(PTH,PTH6,OUTPUT);
	OUTPUT_CLEAR(PTH,PTH6);
}


void ledoff()
{
	OUTPUT_SET(PTH,PTH6);
}

void ledon()
{
	OUTPUT_CLEAR(PTH,PTH6);
}
 
