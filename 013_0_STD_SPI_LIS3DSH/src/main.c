
#include "stm32f4xx.h"
GPIO_InitTypeDef GPIO_InitStruct;
SPI_InitTypeDef SPI_InitStruct;

uint8_t x,y,z;
uint8_t x_address = 0x29, y_address = 0x2B , z_address = 0x2D;
void GPIO_Config()
{
   	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
   	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
   	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);

   	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
   	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
   	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
   	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
   	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

   	GPIO_Init(GPIOD,&GPIO_InitStruct);

   	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
   	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
   	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

   	GPIO_Init(GPIOE,&GPIO_InitStruct);

   	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1);
   	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_SPI1);
   	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_SPI1);

   	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
   	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5 |GPIO_Pin_6 |GPIO_Pin_7 ;
   	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

   	GPIO_Init(GPIOA,&GPIO_InitStruct);
}
void SPI_Config()
{
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);

	 SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	 SPI_InitStruct.SPI_CPHA = SPI_CPHA_2Edge;
	 SPI_InitStruct.SPI_CPOL = SPI_CPOL_High;
	 SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	 SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	 SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	 SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	 SPI_InitStruct.SPI_NSS = SPI_NSS_Soft | SPI_NSSInternalSoft_Set;

	 SPI_Init(SPI1,&SPI_InitStruct);

	 SPI_Cmd(SPI1,ENABLE);

	 GPIO_SetBits(GPIOE,GPIO_Pin_3);

}
void SPI_Write(uint8_t address,uint8_t data)
{

	GPIO_ResetBits(GPIOE,GPIO_Pin_3); //

	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE));
	SPI_I2S_SendData(SPI1,address);

	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE));
	SPI_I2S_ReceiveData(SPI1);

	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE));
	SPI_I2S_SendData(SPI1,data);

	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE));
	SPI_I2S_ReceiveData(SPI1);

	GPIO_SetBits(GPIOE,GPIO_Pin_3);


}


//Tx SPI param: adress, data

void SPI_Tx(uint8_t adress, uint8_t data)

{

  GPIO_ResetBits(GPIOE,GPIO_Pin_3);

  while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE));

  SPI_I2S_SendData(SPI1,adress);

  while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE));

  SPI_I2S_ReceiveData(SPI1);

  while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE));

  SPI_I2S_SendData(SPI1,data);

  while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE));

  SPI_I2S_ReceiveData(SPI1);

  GPIO_SetBits(GPIOE,GPIO_Pin_3);



}



//Rx SPI param: adress, return data

uint8_t SPI_Read(uint8_t adress)

{

  GPIO_ResetBits(GPIOE,GPIO_Pin_3);

  adress=0x80|adress;

  while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE));

  SPI_I2S_SendData(SPI1,adress);

  while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE));

  SPI_I2S_ReceiveData(SPI1);

  while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE));

  SPI_I2S_SendData(SPI1,0x00);

  while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE));



  GPIO_SetBits(GPIOE,GPIO_Pin_3);

  return SPI_I2S_ReceiveData(SPI1);

}

int main(void)
{
GPIO_Config();
SPI_Config();
SPI_Write(0x20,0x67);
  while (1)
  {
	  x = SPI_Read(x_address);
	  y = SPI_Read(y_address);
	  z = SPI_Read(z_address);

  }
}
