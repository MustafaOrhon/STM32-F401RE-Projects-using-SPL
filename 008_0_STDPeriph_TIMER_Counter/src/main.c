
#include "stm32f4xx.h"
TIM_TimeBaseInitTypeDef TIM_InitStruct;
GPIO_InitTypeDef GPIO_InitStruct;
int count = 0;
void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

	GPIO_Init(GPIOA,&GPIO_InitStruct);

}
void TIMER_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	TIM_InitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // TIMER DIVISION SETS 1
	TIM_InitStruct.TIM_CounterMode = TIM_CounterMode_Up; // TIMER COUNTS UP
	TIM_InitStruct.TIM_Period = 15999; //IT WILL COUNT UNTIL 9999
	TIM_InitStruct.TIM_Prescaler = 9999;
	TIM_InitStruct.TIM_RepetitionCounter= 0;

	TIM_TimeBaseInit(TIM2,&TIM_InitStruct);

	TIM_Cmd(TIM2,ENABLE);

}
int main(void)
{


TIMER_Config();
GPIO_Config();
  while (1)
  {
	  count=TIM_GetCounter(TIM2);
	  if(count == 7999)
	  {
		  GPIO_SetBits(GPIOA,GPIO_Pin_0 |GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5);

	  }
	  else if(count==15999)
	  {

		  GPIO_ResetBits(GPIOA,GPIO_Pin_0 |GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5);
	  }


  }
}
