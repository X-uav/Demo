#ifndef __STM32F10X_DRIVER_DELAY_H
#define __STM32F10X_DRIVER_DELAY_H

#include "stm32f10x.h"
#include "misc.h"

void Delay_Configuration(void);
void Delay_us(u32 nus);
void Delay_ms(u16 nms);

#endif
