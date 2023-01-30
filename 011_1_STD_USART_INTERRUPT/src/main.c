
#include "stm32f4xx.h"
GPIO_InitTypeDef GPIO_InitStruct;
USART_InitTypeDef USART_InitStruct;
NVIC_InitTypeDef NVIC_InitStruct;
char str[50];
char rx_buff[50];
int i=0;
void NVIC_Config()
{
   NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn; // USART2 Channel Selected
   NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
   NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority =0;
   NVIC_InitStruct.NVIC_IRQChannelSubPriority= 0;

   NVIC_Init(&NVIC_InitStruct);


}
char str[50];
void GPIO_Config()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);

	GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); //Pin Source Enabled for USART2
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); // Pin Source 3 Enabled For USART

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;  // Port Enabled for Alternate Function
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3; // TX pin selected
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

    GPIO_Init(GPIOA,&GPIO_InitStruct);


}
void USART_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE); //

	USART_InitStruct.USART_BaudRate = 9600; // Baud Rate Set To 9600
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; // Mode Set To Tx and Rx
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b; // 8 bit data will be send

	USART_Init(USART2,&USART_InitStruct);

	USART_Cmd(USART2,ENABLE);

	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
}
void USART_Puts(USART_TypeDef* USARTx,volatile char *s)
{
   while(*s)
   {
	   while(!(USARTx->SR & 0x00000040)); // Wait Usart to be filled

	   USART_SendData(USARTx,*s);
	   *s++;

   }



}
void USART2_IRQHandler()
{
	if(USART_GetITStatus(USART2,USART_IT_RXNE)) // Check that if interrupt is really came
	{
		char rx_buffer = USART_ReceiveData(USART2); // Message taken from data register

		if(rx_buffer != '\n')
		{
			rx_buff[i] = rx_buffer;
			i++;

		}
		else
		{
			rx_buff[i] = '\0';
			i=0;
			USART_Puts(USART2,rx_buff);
		}

	}


}


int main(void)
{
NVIC_Config();
GPIO_Config();
USART_Config();
  while (1)
  {

  }
}
