
#include "stm32f4xx.h"

GPIO_InitTypeDef GPIO_InitStruct;    //GPIO STRUCTURE
TIM_TimeBaseInitTypeDef TIM_InitStruct;  // Timer Structure
TIM_OCInitTypeDef TIMOC_InitStruct;  //Structure for PWM value

void GPIO_Config()
{
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

   GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2);
   GPIO_PinAFConfig(GPIOA,GPIO_PinSource1,GPIO_AF_TIM2);   // We indicated that we will use


   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; // we use them as timer so it is alternate
   GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1;//   We use GPIOA Pin 0,1 cause
                                                     //  they are connected to channel 1-2


	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA,&GPIO_InitStruct);

}
void TIM_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = 9999;
	TIM_InitStruct.TIM_Prescaler = 1599;
	TIM_InitStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM2,&TIM_InitStruct);

	TIM_Cmd(TIM2,ENABLE);

	TIMOC_InitStruct.TIM_OCMode = TIM_OCMode_PWM1; // We will use Mode-1 PWM
	TIMOC_InitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIMOC_InitStruct.TIM_OCPolarity = TIM_OCNPolarity_High;

}


int main(void)
{

	GPIO_Config();
	TIM_Config();

  while (1)
  {
     TIMOC_InitStruct.TIM_Pulse = 9999;
     TIM_OC1Init(TIM2,&TIMOC_InitStruct);
     TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable); // TIM2 Channel-1 Enable

     TIMOC_InitStruct.TIM_Pulse = 9000;
     TIM_OC2Init(TIM2,&TIMOC_InitStruct);  //Channel-2 Struct
     TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Enable); // TIM2 Channel-2 Enable


  }
}
