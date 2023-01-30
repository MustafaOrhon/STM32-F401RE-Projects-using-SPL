
#include "stm32f4xx.h"
TIM_TimeBaseInitTypeDef TIM_InitStruct;
GPIO_InitTypeDef GPIO_InitStruct;
uint16_t count;
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
void GPIO_Config(){

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed =GPIO_Speed_100MHz;

	GPIO_Init(GPIOA,&GPIO_InitStruct);

	SysTick_Config(SystemCoreClock/1000); //Goes interrupt every 1ms

}


int main(void)
{
GPIO_Config();
  while (1)
  {

   GPIO_ToggleBits(GPIOA,GPIO_Pin_0 |GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5);
   delay_ms(1000);

  }
}
