
#include "stm32f4xx.h"

GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIM_InitStruct;
TIM_OCInitTypeDef TIMOC_InitStruct;
ADC_InitTypeDef ADC_InitStruct;
ADC_CommonInitTypeDef ADC_CommonInitStruct;

uint16_t adc_value;
uint16_t pwm_value;
long map(long x, long in_min, long in_max, long out_min, long out_max) //Conversation between array
{   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min; }

void GPIO_Config()
{
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);

   GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2);
   GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM2);   // We indicated that we will use


   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; // we use them as timer so it is alternate
   GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1;//   We use GPIOA Pin 0,1 cause
                                                     //  they are connected to channel 1-2


	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AN;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;

	GPIO_Init(GPIOC,&GPIO_InitStruct);

}

void TIM_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = 99 ;
	TIM_InitStruct.TIM_Prescaler = 839;
	TIM_InitStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM2,&TIM_InitStruct);

	TIM_Cmd(TIM2,ENABLE);

	TIMOC_InitStruct.TIM_OCMode = TIM_OCMode_PWM1; // We will use Mode-1 PWM
	TIMOC_InitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIMOC_InitStruct.TIM_OCPolarity = TIM_OCNPolarity_High;




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

	ADC_RegularChannelConfig(ADC1,ADC_Channel_10,1,ADC_SampleTime_56Cycles);
	ADC_SoftwareStartConv(ADC1);
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC) ==RESET); //Wait until conversion ends

	return ADC_GetConversionValue(ADC1); //Return the ADC value;

}


int main(void)
{
   GPIO_Config();
   TIM_Config();
   ADC_Config();

  while (1)
  {

    adc_value= Read_ADC();
    pwm_value = map(adc_value,0,4095,0,99);
    TIMOC_InitStruct.TIM_Pulse = pwm_value;
    TIM_OC1Init(TIM2,&TIMOC_InitStruct);
    TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable); // TIM2 Channel-1 Enable

    TIMOC_InitStruct.TIM_Pulse = pwm_value;
    TIM_OC2Init(TIM2,&TIMOC_InitStruct);  //Channel-2 Struct
    TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable); // TIM2 Channel-2 Enable



  }
}
