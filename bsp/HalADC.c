#include "HalADC.h"

void HalADCInit(void)
{
        ADC_ConfigType  ADC_Config={{0}};    /* Initialization of ADC module */    
        ADC_Config.u8ClockDiv = ADC_ADIV_DIVIDE_4;    
        ADC_Config.u8ClockSource = CLOCK_SOURCE_BUS_CLOCK;    
        ADC_Config.u8Mode = ADC_MODE_12BIT;    
        ADC_Config.sSetting.bContinuousEn=1;    
        ADC_Config.u16PinControl= 0x0400; /* Disable I/O control on ADC channel 10*/    
        ADC_Init( ADC, &ADC_Config);
}

uint16 GetRheostatVol(void)
{
    return (ADC_PollRead(ADC,ADC_CHANNEL_AD10));
}

