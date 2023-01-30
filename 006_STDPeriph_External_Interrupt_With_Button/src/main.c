
#include "stm32f4xx.h"
GPIO_InitTypeDef GPIO_InitStruct;
EXTI_InitTypeDef EXTI_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;
void delay(uint32_t time){while(time--);}
void EXTI_Config(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE); //ENABLE SYSCFG FOR EXTI LINE

    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource10);//Selecting port and pin for EXTI

    EXTI_InitStruct.EXTI_Line = EXTI_Line10;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;

    EXTI_Init(&EXTI_InitStruct);

    NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;

    NVIC_Init(&NVIC_InitStruct);
}
void GPIO_Config(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ENABLE A PORT FOR LEDS
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); //ENABLE C PORT FOR BUTTON

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
    GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;

    GPIO_Init(GPIOA,&GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Mode= GPIO_Mode_IN;
    GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
    GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_DOWN;
    GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;

    GPIO_Init(GPIOC,&GPIO_InitStruct);


}
void EXTI15_10_IRQHandler()
{
  	if(EXTI_GetITStatus(EXTI_Line10) != RESET)
  	{
  		GPIO_ResetBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5);
  		delay(1680000);
  		GPIO_SetBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5);
  		delay(1680000);
  		GPIO_ResetBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5);
  		delay(1680000);
  		GPIO_SetBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5);
  		delay(1680000);
  		GPIO_ResetBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5);
  		delay(1680000);

  		EXTI_ClearITPendingBit(EXTI_Line10);
  	}

}
int main(void)
{

GPIO_Config();
EXTI_Config();
  while (1)
  {
    GPIO_SetBits(GPIOA,GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5);
  }
}
