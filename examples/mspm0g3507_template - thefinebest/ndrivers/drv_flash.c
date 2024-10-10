#include "drv_flash.h"


#define NO_ERROR 0
#define ERROR_ERASE 1
#define ERROR_WRITE_8_BIT 2
#define ERROR_READ_8_BIT 3
#define ERROR_WRITE_16_BIT 4
#define ERROR_READ_16_BIT 5
#define ERROR_WRITE_32_BIT 6
#define ERROR_READ_32_BIT 7
#define ERROR_WRITE_64_BIT 8
#define ERROR_READ_64_BIT 9
#define ERROR_EXPECTED_FAIL 10
#define ERROR_UNEXPECTED 11
#define ERROR_WRITE_64_OVERRIDE 12
#define ERROR_READ_64_OVERRIDE 13
#define ERROR_EXPECTED_FAIL_OVERRIDE 14

volatile uint8_t gErrorType = NO_ERROR;
volatile DL_FLASHCTL_COMMAND_STATUS gCmdStatus;

uint8_t gData8[3];
uint16_t gData16[3];
uint32_t gData32[3];

void flash_init(void)
{
	flash_read8(MAIN_ADDRESS_8U,gData8,3);
	flash_read16(MAIN_ADDRESS_16U,gData16,3);
	flash_read32(MAIN_ADDRESS_32U,gData32,3);
}

//页擦除
uint8_t flash_clear(uint32_t address)
{
	//解锁Flash
	DL_FlashCTL_unprotectSector(FLASHCTL, address, DL_FLASHCTL_REGION_SELECT_MAIN);
	//擦除页数据
	gCmdStatus = DL_FlashCTL_eraseMemoryFromRAM(FLASHCTL, address, DL_FLASHCTL_COMMAND_SIZE_SECTOR);
	if (gCmdStatus != DL_FLASHCTL_COMMAND_STATUS_PASSED) {
			/* If command did not pass, set error flag. */
			return ERROR_ERASE;
	}
	return NO_ERROR;
}

//写入8位
//成功为0，其它：失败
uint8_t flash_write8(uint32_t address, uint8_t* data,char size)
{
	char i;
	for(i = 0; i < size; i++) {
		//解锁Flash
		DL_FlashCTL_unprotectSector(FLASHCTL, address, DL_FLASHCTL_REGION_SELECT_MAIN);
		gCmdStatus = DL_FlashCTL_programMemoryFromRAM8WithECCGenerated(FLASHCTL, address, &data[i]);
	  if (gCmdStatus != DL_FLASHCTL_COMMAND_STATUS_PASSED) {
            /* If command did not pass, set error flag. */
        return ERROR_WRITE_8_BIT;
		}
		address +=8;
		DL_FlashCTL_waitForCmdDone(FLASHCTL);
	}
	return NO_ERROR;
}

//写入16位
//成功为0，其它：失败
uint8_t flash_write16(uint32_t address, uint16_t* data,char size)
{
	char i;
	for(i = 0; i < size; i++) {
		//解锁Flash
		DL_FlashCTL_unprotectSector(FLASHCTL, address, DL_FLASHCTL_REGION_SELECT_MAIN);
		gCmdStatus = DL_FlashCTL_programMemoryFromRAM16WithECCGenerated(FLASHCTL, address, &data[i]);
	  if (gCmdStatus != DL_FLASHCTL_COMMAND_STATUS_PASSED) {
            /* If command did not pass, set error flag. */
        return ERROR_WRITE_16_BIT;
		}
		address +=8;
		 DL_FlashCTL_waitForCmdDone(FLASHCTL);
	}
	return NO_ERROR;
}


//写入32位
//成功为0，其它：失败
uint8_t flash_write32(uint32_t address, uint32_t* data,char size)
{
	char i;
	for(i = 0; i < size; i++) {
		//解锁Flash
		DL_FlashCTL_unprotectSector(FLASHCTL, address, DL_FLASHCTL_REGION_SELECT_MAIN);
		gCmdStatus = DL_FlashCTL_programMemoryFromRAM32WithECCGenerated(FLASHCTL, address, &data[i]);
	  if (gCmdStatus != DL_FLASHCTL_COMMAND_STATUS_PASSED) {
            /* If command did not pass, set error flag. */
        return ERROR_WRITE_32_BIT;
		}
		address +=8;
		 DL_FlashCTL_waitForCmdDone(FLASHCTL);
	}
	return NO_ERROR;
}

//读取8位
void flash_read8(uint32_t address, uint8_t* data,char size)
{
	char i;
	for(i = 0; i < size; i++) {
		data[i] = *(uint8_t *)address;
		address += 8;
	}
}


//读取16位
void flash_read16(uint32_t address, uint16_t* data,char size)
{
	char i;
	for(i = 0; i < size; i++) {
		data[i] = *(uint16_t *)address;
		address += 8;
	}
}

//读取32位
void flash_read32(uint32_t address, uint32_t* data,char size)
{
	char i;
	for(i = 0; i < size; i++) {
		data[i] = *(uint32_t *)address;
		address += 8;
	}
}

//全读一遍
void flash_data_updata(void)
{
		flash_read8(MAIN_BASE_ADDRESS,gData8,3);
	  flash_read16(MAIN_BASE_ADDRESS+24,gData16,3);
		flash_read32(MAIN_BASE_ADDRESS+48,gData32,3);
}