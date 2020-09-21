#include "includes.h"
#include "HalIO.h"

void HalGpioInit(void)
{
    CONFIG_PIN_AS_GPIO(PTH,PTH0,OUTPUT);
    CONFIG_PIN_AS_GPIO(PTH,PTH1,OUTPUT);
    CONFIG_PIN_AS_GPIO(PTE,PTE7,OUTPUT);
	
    OUTPUT_CLEAR(PTH,PTH0);
    OUTPUT_CLEAR(PTH,PTH1);
    OUTPUT_CLEAR(PTE,PTE7);
}

void SetLedDisplay(LED_ENUM status)
{
	switch(status)
	{
		case LED_OFF :
            OUTPUT_CLEAR(PTH,PTH0);
            OUTPUT_CLEAR(PTH,PTH1);
            OUTPUT_CLEAR(PTE,PTE7);
			break;
		case LED_RED :
            OUTPUT_CLEAR(PTH,PTH0);
            OUTPUT_SET(PTH,PTH1);
            OUTPUT_CLEAR(PTE,PTE7);
			break;
		case LED_GREEN :
            OUTPUT_CLEAR(PTH,PTH0);
            OUTPUT_CLEAR(PTH,PTH1);
            OUTPUT_SET(PTE,PTE7);
			break;
		case LED_BLUE :
            OUTPUT_SET(PTH,PTH0);
            OUTPUT_CLEAR(PTH,PTH1);
            OUTPUT_CLEAR(PTE,PTE7);
			break;
        case LED_WHITE:
            OUTPUT_SET(PTH,PTH0);
            OUTPUT_SET(PTH,PTH1);
            OUTPUT_SET(PTE,PTE7);      
        default :
            break;
	}
}


void KBI1_Task(void)
{   
    OSIntEnter();
    if(KBI_GetSP(KBI1)== 0x0000010)    
    {           
        printf("\nSW2 pressed!\n");     
    }else if(KBI_GetSP(KBI1)== 0x0000020)
    {           
        printf("\nSW3 pressed!\n");     
    }
    OSIntExit();
    KBI_RstSP(KBI1);    
    KBI_ClrFlags(KBI1);
}

void HalKBIInit(void)
{
    uint8 i =0;
    KBI_ConfigType  KBIConfig={{0}};	/* Disable all the KBI pins */	
    for (i = 0; i < KBI_MAX_PINS_PER_PORT; i++)	
    {       
        KBIConfig.sPin[i].bEn    = 0;   
    }   
    KBIConfig.sBits.bRstKbsp   = 1;/*Writing a 1 to RSTKBSP is to clear the KBIxSP Register*/   
    KBIConfig.sBits.bKbspEn     = 1;/*The latched value in KBxSP register while interrupt flag occur to be read.*/  
    KBIConfig.sBits.bMode       = KBI_MODE_EDGE_ONLY;   
    KBIConfig.sBits.bIntEn      = 1;    /*Falling edge/low level select; KBI0_P24 channel enable(SW2 on FRDM+ board) */ 
    KBIConfig.sPin[4].bEdge = KBI_FALLING_EDGE_LOW_LEVEL;   
    KBIConfig.sPin[4].bEn   = 1;    /*Falling edge/low level select; KBI0_P25 channel enable(SW3 on FRDM+ board) */ 
    KBIConfig.sPin[5].bEdge = KBI_FALLING_EDGE_LOW_LEVEL;   
    KBIConfig.sPin[5].bEn   = 1;    
    KBI_SetCallback(KBI1, &KBI1_Task);  
    KBI_Init(KBI1, &KBIConfig);
}