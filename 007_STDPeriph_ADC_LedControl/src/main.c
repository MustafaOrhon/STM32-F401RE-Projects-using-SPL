
#include "stm32f4xx.h"
GPIO_InitTypeDef GPIO_InitStruct;
ADC_InitTypeDef ADC_InitStruct;
ADC_CommonInitTypeDef ADC_CommonInitStruct;
uint8_t adc_value;

void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;

	GPIO_Init(GPIOA,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;

	GPIO_Init(GPIOC,&GPIO_InitStruct);


}
void ADC_Config(void)
{
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);

  ADC_CommonInitStruct.ADC_Mode=ADC_Mode_Independent;
  ADC_CommonInitStruct.ADC_Prescaler= ADC_Prescaler_Div4;

  ADC_CommonInit(&ADC_CommonInitStruct);

  ADC_InitStruct.ADC_Resolution = ADC_Resolution_8b;

  ADC_Init(ADC1,&ADC_InitStruct);

  ADC_Cmd(ADC1,ENABLE);//ADC1 ACTIVE


}
uint8_t Read_ADC()
{
  ADC_RegularChannelConfig(ADC1,ADC_Channel_10,1,ADC_SampleTime_56Cycles);

  ADC_SoftwareStartConv(ADC1);

  while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) == RESET);

  return ADC_GetConversionValue(ADC1);


}

int main(void)
{
GPIO_Config();
ADC_Config();
  while (1)
  {
    adc_value = Read_ADC();

    if(adc_value <= 80)
    {
    	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5);

    }
    else if(adc_value >= 80 && adc_value <= 180)
    {
    	GPIO_SetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1);
    	GPIO_ResetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5);

    }
    else
    {
    	GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1);
    	GPIO_SetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5);
    }


  }
}
