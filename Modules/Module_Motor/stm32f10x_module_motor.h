#ifndef __STM32F10x_MODULE_MOTOR_H
#define __STM32F10X_MODULE_MOTOR_H
#include "stm32f10x_driver_timer.h"

void Motor_GPIO_Configuration(void);
extern void PWM_Set(const u16 pwm1,const u16 pwm2,const u16 pwm3,const u16 pwm4);	// PWM设置
#endif
