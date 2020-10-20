#include "includes.h"
#include "HalIO.h"

extern OS_EVENT *kbiMsgQueue; 

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


uint8 g_buttonPressedName =0;
void KBI1_Task(void)
{   
    INT8U err;
    OSIntEnter();
    if(KBI_GetSP(KBI1)== 0x0000010)    
    {           
        g_buttonPressedName= 1; 
    }else if(KBI_GetSP(KBI1)== 0x0000020)
    {  
        g_buttonPressedName= 2;
    }
    err = OSQPost(kbiMsgQueue, (void *)&g_buttonPressedName); 
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
    KBIConfig.sPin[4].bEdge = KBI_RISING_EDGE_HIGH_LEVEL;   
    KBIConfig.sPin[4].bEn   = 1;    /*Falling edge/low level select; KBI0_P25 channel enable(SW3 on FRDM+ board) */ 
    KBIConfig.sPin[5].bEdge = KBI_RISING_EDGE_HIGH_LEVEL;   
    KBIConfig.sPin[5].bEn   = 1;    
    KBI_SetCallback(KBI1, &KBI1_Task);  
    KBI_Init(KBI1, &KBIConfig);
}

void HalClkInit(void)
{
    ICS_ConfigType ICS_set={0};		/* Declaration of ICS_setup structure */
    ICS_set.u8ClkMode=ICS_CLK_MODE_FEE; /* ICS in FLL engaged internal mode*/
    ICS_set.bdiv=0;					/* bdiv bit equals 0, prescaler=1*/
    ICS_set.oscConfig.bEnable=1;	/* Osc enabled*/
    ICS_set.oscConfig.bRange=1;		/* High frequency range 4-24 MHz*/
    ICS_set.oscConfig.bIsCryst=1;	/* Oscillator clock source is selected*/
    ICS_set.oscConfig.u32OscFreq=8000 ; /* 8 MHz crystal, crytal is in KHz*/

    ICS_Init(&ICS_set);            		/*Initialization of core clock at 40MHz, bus clock 20 MHz*/
}