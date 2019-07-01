#ifndef __STM32F10X_DRIVER_TIMER_H
#define __STM32F10X_DRIVER_TIMER_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"

//--- 最大PWM值 ---//
//#define MAX_PWM 2000
#define MAX_PWM 999

extern u8  loop500HzFlag,loop200HzFlag,loop50HzFlag,loop600HzFlag,loop100HzFlag,loop20HzFlag,loop10HzFlag;
extern volatile u16 loop500Hzcnt,loop200HzCnt,loop50HzCnt , loop600HzCnt,loop100HzCnt, loop20HzCnt , loop10HzCnt;

extern void TIMx_Configuration(void);

#endif
