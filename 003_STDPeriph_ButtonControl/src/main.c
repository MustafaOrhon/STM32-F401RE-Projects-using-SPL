
#include "stm32f4xx.h"
GPIO_InitTypeDef GPIO_InitStruct;
void delay (uint32_t  time)
{
	while(time--);
}
void GPIO_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);  //AHB1 Clock ENABLED
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);  //Enable AHB1 For Gate A


	GPIO_InitStruct.GPIO_Mode = 0x00 ; // Mode Output Selected
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // Output Type PP
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10; //Pin 13 Selected
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;  //Pull-down mode enabled
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz; // Very High Speed Selected

	GPIO_Init(GPIOC,&GPIO_InitStruct);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5; //Pins Selected
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT; // OUTPUT MODE ENABLE
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;  //PUSHPULL MODE
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL; //NOPULL MODE ENABLE
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; //HIGH SPEED SELECTED

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
           delay(1680000);
    	   GPIO_ToggleBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5);
       }



  }
}
