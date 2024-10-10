#ifndef __DRV_FLASH_H
#define __DRV_FLASH_H
#ifdef __cplusplus
extern "C" {
#endif
#include "main.h"

#define MAIN_BASE_ADDRESS (0x00010000)	//0x00000000~0x0001FFF8
#define MAIN_ADDRESS_8U		MAIN_BASE_ADDRESS
#define MAIN_ADDRESS_16U	(MAIN_BASE_ADDRESS+24)
#define MAIN_ADDRESS_32U	(MAIN_BASE_ADDRESS+48)

void flash_init(void);
uint8_t flash_clear(uint32_t address);
uint8_t flash_write8(uint32_t address, uint8_t* data,char size);
uint8_t flash_write16(uint32_t address, uint16_t* data,char size);
uint8_t flash_write32(uint32_t address, uint32_t* data,char size);
void flash_read8(uint32_t address, uint8_t* data,char size);
void flash_read16(uint32_t address, uint16_t* data,char size);
void flash_read32(uint32_t address, uint32_t* data,char size);

void flash_data_updata(void);

extern uint8_t gData8[3];
extern uint16_t gData16[3];
extern uint32_t gData32[3];

#ifdef __cplusplus
}
#endif
#endif
