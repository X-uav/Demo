#ifndef __STM32F10X_DRIVER_FLASH_H__
#define __STM32F10X_DRIVER_FLASH_H__

#include "stm32f10x.h"
//-----所选STM32的FLASH容量大小(单位为K)----//
#define FLASH_SIZE            64
//-----使能FLASH写入(0，不使能;1，使能)----//
#define FLASH_WREN            1
// The relative offset to start addfress.
#define FLASH_OFFEST          0X0000FC00
// The unlock key value.
#define FLASH_KEY1            0X45670123
#define FLASH_KEY2            0XCDEF89AB

#define FLASH_STATE_OK        0
#define FLASH_STATE_BUSY      1
// Programming error.
#define FLASH_STATE_ERROR_PRO 2
// Write-protect error.
#define FLASH_STATE_ERROR_WP  3
#define FLASH_STATE_TIMEOUT   0XFF

extern void Flash_Lock(void);
extern void Flash_Unlock(void);
extern u16  Flash_ReadHalfWord(u32 flash_addr);
extern void Flash_Read(u32 read_addr, u16 *buffer, u16 half_word_nums);
extern void Flash_Write(u32 write_addr, u16 *buffer, u16 half_word_nums);
extern void Flash_WriteNoCheck(u32 write_addr, u16 *buffer,
                               u16 half_word_nums);
extern u8   Flash_ErasePage(u32 page_addr);
extern u8   Flash_GetStatus(void);
extern u8   Flash_WaitDone(u16 time);
extern u8   Flash_WriteHalfWord(u32 flash_addr, u16 half_word);

#endif
