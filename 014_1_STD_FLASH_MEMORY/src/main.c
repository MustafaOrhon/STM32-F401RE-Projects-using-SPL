
#include "stm32f4xx.h"
uint32_t data;
void FLASH_Write(uint32_t flashAddress,uint32_t flashData)
{
	 FLASH_Unlock();

	 FLASH_EraseSector(FLASH_Sector_7,VoltageRange_3);

	 FLASH_ProgramWord(flashAddress,flashData);

	 FLASH_Lock();

}

void FLASH_Read(uint32_t address)
{
    uint32_t myFlashData = *(uint32_t *)address;

    return myFlashData;

}


int main(void)
{

FLASH_Write(0x08060000,55);

  while (1)
  {
     data=FLASH_Read(0x08060000);
  }
}
