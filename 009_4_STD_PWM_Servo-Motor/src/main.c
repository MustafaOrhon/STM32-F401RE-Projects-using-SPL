
#include "stm32f4xx.h"

GPIO_InitTypeDef GPIO_InitStruct;    //GPIO STRUCTURE
TIM_TimeBaseInitTypeDef TIM_InitStruct;  // Timer Structure
TIM_OCInitTypeDef TIMOC_InitStruct;  //Structure for PWM value
uint32_t count;
void delay_ms(uint32_t time)
{
   	count=time;
   	while(count);

}
void SysTick_Handler()
{
  if(count>0)
  {
	  count--;

  }

}
void GPIO_Config()
{
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

   GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM2);


   GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; // we use them as timer so it is alternate
   GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;


	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA,&GPIO_InitStruct);

}
void TIM_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_InitStruct.TIM_Period = 19999;
	TIM_InitStruct.TIM_Prescaler = 83;
	TIM_InitStruct.TIM_RepetitionCounter = 0;

	TIM_TimeBaseInit(TIM2,&TIM_InitStruct);

	TIM_Cmd(TIM2,ENABLE);

	TIMOC_InitStruct.TIM_OCMode = TIM_OCMode_PWM1; // We will use Mode-1 PWM
	TIMOC_InitStruct.TIM_OutputState = TIM_OutputState_Enable;
	TIMOC_InitStruct.TIM_OCPolarity = TIM_OCNPolarity_High;

	SysTick_Config(SystemCoreClock/1000);
}



int main(void)
{
GPIO_Config();
TIM_Config();



  while (1)
  {
      for(int i=200;i<=860;i++)
      {
 	     TIMOC_InitStruct.TIM_Pulse = i;
 	     TIM_OC1Init(TIM2,&TIMOC_InitStruct);
 	     TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable); // TIM2 Channel-1 Enable
         delay_ms(2);

      }

         for(int i=860;i>=200;i--)
         {
    	     TIMOC_InitStruct.TIM_Pulse = i;
    	     TIM_OC1Init(TIM2,&TIMOC_InitStruct);
    	     TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable); // TIM2 Channel-1 Enable
             delay_ms(2);

         }



  }
}
