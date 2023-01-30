#include "stm32f4xx.h"
GPIO_InitTypeDef GPIO_InitStruct;
EXTI_InitTypeDef EXTI_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;
void delay(uint32_t time){while(time--);}
void EXTI_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE); //ENABLE SYSCFG FOR EXTI LINE
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource0);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource13);

	EXTI_InitStruct.EXTI_Line = EXTI_Line0 ;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;

	EXTI_Init(&EXTI_InitStruct);
	EXTI_InitStruct.EXTI_Line =EXTI_Line13 ;
	EXTI_InitStruct.EXTI_LineCmd=ENABLE;
	EXTI_InitStruct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTI_Init(&EXTI_InitStruct);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitStruct.NVIC_IRQChannel=EXTI0_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;

	NVIC_Init(&NVIC_InitStruct);

	NVIC_InitStruct.NVIC_IRQChannel=EXTI15_10_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=0;

	NVIC_Init(&NVIC_InitStruct);
}
void GPIO_Config(void)
{
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);

  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;

  GPIO_Init(GPIOA,&GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_13;
  GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_DOWN;
  GPIO_InitStruct.GPIO_Speed=GPIO_Speed_100MHz;

  GPIO_Init(GPIOC,&GPIO_InitStruct);




}
void EXTI15_10_IRQHandler()
{

	if(EXTI_GetITStatus(EXTI_Line13)!=RESET)
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5);
		  GPIO_SetBits(GPIOA,GPIO_Pin_5);
		  delay(1680000);
		  GPIO_SetBits(GPIOA,GPIO_Pin_4);
		  delay(1680000);
		  GPIO_SetBits(GPIOA,GPIO_Pin_1);
		  delay(1680000);
		  GPIO_SetBits(GPIOA,GPIO_Pin_0);
		  delay(1680000);
		  EXTI_ClearITPendingBit(EXTI_Line13);

	}

}
void EXTI0_IRQHandler()
{
  if(EXTI_GetITStatus(EXTI_Line0)!=RESET)
  {
	  GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5);
	  GPIO_SetBits(GPIOA,GPIO_Pin_0);
	  delay(1680000);
	  GPIO_SetBits(GPIOA,GPIO_Pin_1);
	  delay(1680000);
	  GPIO_SetBits(GPIOA,GPIO_Pin_4);
	  delay(1680000);
	  GPIO_SetBits(GPIOA,GPIO_Pin_5);
	  delay(1680000);
	  EXTI_ClearITPendingBit(EXTI_Line0);

  }

}



int main(void)
{
GPIO_Config();
EXTI_Config();
  while (1)
  {
    GPIO_ResetBits(GPIOA,GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5);

  }
}
