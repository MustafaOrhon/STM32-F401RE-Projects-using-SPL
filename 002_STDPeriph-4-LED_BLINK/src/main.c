
#include "stm32f4xx.h"

GPIO_InitTypeDef GPIO_InitStruct;

void delay (uint32_t  time)
{
	while(time--);
}
void GPIO_Config()
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);  //Enable AHB1 For Gate A

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA,&GPIO_InitStruct);


}

int main(void)
{

 GPIO_Config();
  while (1)
  {
   GPIO_SetBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5);
   delay(1680000);
   GPIO_ResetBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5);
   delay(1680000);

  }
}
