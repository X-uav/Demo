#ifndef __STM32F10X_MODULE_LED_H
#define __STM32F10X_MODULE_LED_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

void LED_Configuration(void);
void LED_Front_Off(void);
void LED_Front_ON(void);
void LED_Tail_Off(void);
void LED_Tail_ON(void);

#endif
