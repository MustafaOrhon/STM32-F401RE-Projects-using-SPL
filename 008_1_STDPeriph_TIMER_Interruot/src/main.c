
#include "stm32f4xx.h"
GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef TIM_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;
int count;
void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;

	GPIO_Init(GPIOA,&GPIO_InitStruct);

}
void TIM_Config()
{
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

  TIM_InitStruct.TIM_ClockDivision= TIM_CKD_DIV1;
  TIM_InitStruct.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_InitStruct.TIM_Period= 15999;
  TIM_InitStruct.TIM_Prescaler = 9999 ;
  TIM_InitStruct.TIM_RepetitionCounter=0;

  TIM_TimeBaseInit(TIM2,&TIM_InitStruct);



  TIM_Cmd(TIM2,ENABLE);

}
void NVIC_Config()
{
  NVIC_InitStruct.NVIC_IRQChannel= TIM2_IRQn;
  NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;

  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

  NVIC_Init(&NVIC_InitStruct);




}
void TIM2_IRQHandler(void)
{
	GPIO_ToggleBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5);

	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);


}
int main(void)
{
	GPIO_Config();
	TIM_Config();
	NVIC_Config();




  while (1)
  {
    count=TIM_GetCounter(TIM2);

  }
}
