#include "stm32f10x_driver_eeprom.h"

extern u8 EEPROM_IsValid(void)
{
    Flash_Read(EEPROM_TABLE_ADDRESS, (u16 *)(&EEPROM_TableStructure), 2);

    if ((s16)EEPROM_TableStructure.version == EEPROM_DEFAULT_VERSION)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
