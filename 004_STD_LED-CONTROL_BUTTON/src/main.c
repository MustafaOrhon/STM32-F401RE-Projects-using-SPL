
#include "stm32f4xx.h"
GPIO_InitTypeDef GPIO_InitStruct;
int count=0;
void delay (uint32_t  time)
{
	while(time--);
}
void GPIO_Config(void)
{
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
   RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);

   GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
   GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
   GPIO_InitStruct.GPIO_Pin= GPIO_Pin_10;
   GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_DOWN;
   GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;

   GPIO_Init(GPIOC,&GPIO_InitStruct);

   GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;
   GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
   GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
   GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
   GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;

   GPIO_Init(GPIOA,&GPIO_InitStruct);



}
int main(void)
{

 GPIO_Config();

  while (1)
  {
    if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10))
    {
    	while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10));
    	delay(168000);
    	count++;

    }
    if(count==1)
    {
    	GPIO_SetBits(GPIOA,GPIO_Pin_0);
    }
    else if(count==2)
        {
        	GPIO_SetBits(GPIOA,GPIO_Pin_1);
        }
    else if(count==3)
        {
        	GPIO_SetBits(GPIOA,GPIO_Pin_4);
        }
    else if(count==4)
        {
        	GPIO_SetBits(GPIOA,GPIO_Pin_5);
        }
    else
    {
    	count =0 ;
    	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
    	delay(1680000);
    	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
    	delay(1680000);
    	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
    	delay(1680000);
    	GPIO_ResetBits(GPIOA,GPIO_Pin_0);

    }
  }
}
