#ifndef __STM32F10X_DRIVER_EEPROM_H__
#define __STM32F10X_DRIVER_EEPROM_H__

#include <stdbool.h>
#include "stm32f10x.h"

#define EEPROM_DEFAULT_VERSION 1
#define EEPROM_TABLE_ADDRESS   (FLASH_BASE + FLASH_OFFEST + 0)

typedef struct
{
    float nrf_addr[5];
    float offset_acc[3];
    float offset_gyr[3];
    float offset_mag[3];
    float pid_alt[3];
    float pid_alt_vel[3];
    float pid_roll[3];
    float pid_roll_rate[3];
    float pid_pitch[3];
    float pid_pitch_rate[3];
    float pid_yaw[3];
    float pid_yaw_rate[3];
    float version;
    bool  nrf_matched_flag;
} EEPROM_Table;

extern bool eeprom_params_request_flag;
extern EEPROM_Table EEPROM_TableStructure;;

extern void EEPROM_LoadParamsFromEEPROM(void);
extern void EEPROM_ResetDefaultTable(void);
extern void EEPROM_ReadTableFromEEPROM(void);
extern void EEPROM_SaveParamsToEEPROM(void);
extern void EEPROM_SetDefaultParams(void);
extern void EEPROM_TransParamsToTable(void);
extern void EEPROM_TransTableToParams(void);
extern void EEPROM_WriteTableToEEPROM(void);
extern u8   EEPROM_IsValid(void);

#endif
