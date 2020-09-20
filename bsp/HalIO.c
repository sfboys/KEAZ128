#include "includes.h"
#include "HalIO.h"

void HalGpioInit(void)
{
	GPIO_Init(GPIOB, GPIO_PTE7_MASK|GPIO_PTH0_MASK|GPIO_PTH1_MASK, GPIO_PinOutput);
}

void SetLedDisplay(LED_ENUM status)
{
	switch(status)
	{
		case OFF :
            GPIO_PinSet(GPIO_PTE7_MASK);
            GPIO_PinSet(GPIO_PTH0_MASK);
            GPIO_PinSet(GPIO_PTH1_MASK);
			break;
		case RED :
            GPIO_PinSet(GPIO_PTE7_MASK);
            GPIO_PinClear(GPIO_PTH0_MASK);
            GPIO_PinSet(GPIO_PTH1_MASK);
			break;
		case GREEN :
            GPIO_PinSet(GPIO_PTE7_MASK);
            GPIO_PinSet(GPIO_PTH0_MASK);
            GPIO_PinClear(GPIO_PTH1_MASK);
			break;
		case BLUE :
            GPIO_PinClear(GPIO_PTE7_MASK);
            GPIO_PinSet(GPIO_PTH0_MASK);
            GPIO_PinSet(GPIO_PTH1_MASK);
			break;
        case WHITE:
            GPIO_PinClear(GPIO_PTE7_MASK);
            GPIO_PinClear(GPIO_PTH0_MASK);
            GPIO_PinClear(GPIO_PTH1_MASK);       
        default :
            break;
	}
}
//void KBI_Init(KBI_Type *pKBI, KBI_ConfigType *pConfig);
//void KBI_SetCallback(KBI_Type *pKBI, KBI_CallbackType pfnCallback);

void HalKBHandle(void)
{
    OSIntEnter();
    if(KBI1->SP &(1<<4) != 0)
    {

    }

    if(KBI1->SP &(1<<5) != 0)
    {

    }
    KBI1->SC |= 0x24;//clear ackflag 
    OSIntExit();
}
void HalKBIInit(void)
{
    KBI_ConfigType KBI1Config;
    KBI1Config.sBits.bMode = 1;
    KBI1Config.sBits.bIntEn = 1;
    KBI1Config.sBits.bKbspEn = 1;
    KBI1Config.sPin[4].bEdge =1; //BTN0
    KBI1Config.sPin[4].bEn = 1;
    KBI1Config.sPin[5].bEdge =1; //BTN0
    KBI1Config.sPin[5].bEn = 1;
	KBI_Init(KBI1,&KBI1Config);
}