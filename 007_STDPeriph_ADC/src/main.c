
#include "stm32f4xx.h"
GPIO_InitTypeDef GPIO_InitStruct;
ADC_InitTypeDef ADC_InitStruct;
ADC_CommonInitTypeDef ADC_CommonInitStruct;
uint16_t adc_value;
float adc_voltage;
void GPIO_Config(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AN; // MODE SETS AS ANALOG
  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
  GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;

  GPIO_Init(GPIOB,&GPIO_InitStruct);

}
void ADC_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);

	ADC_CommonInitStruct.ADC_Mode=ADC_Mode_Independent;
	ADC_CommonInitStruct.ADC_Prescaler=ADC_Prescaler_Div4; //It must be lower than 36MHZ

	ADC_CommonInit(&ADC_CommonInitStruct);

	ADC_InitStruct.ADC_Resolution=ADC_Resolution_12b; // Resulution will be 12 bits
    ADC_Init(ADC1,&ADC_InitStruct);
	//ADC_InitStruct.ADC_ContinuousConvMode = ENABLE;

    ADC_Cmd(ADC1,ENABLE); //We need to enable ADC1 to work
}

uint16_t Read_ADC()
{

	ADC_RegularChannelConfig(ADC1,ADC_Channel_8,1,ADC_SampleTime_56Cycles);
	ADC_SoftwareStartConv(ADC1);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) ==RESET); //Wait until conversion ends

	return ADC_GetConversionValue(ADC1); //Return the ADC value;

}

int main(void)
{
GPIO_Config();
ADC_Config();
  while (1)
  {
    adc_value=Read_ADC();
    adc_voltage=adc_value*(0.00080586);
  }
}
