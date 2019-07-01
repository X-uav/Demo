#include "stm32f10x_module_motor.h"

void Motor_GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;										// 复用推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;									// 50MHz翻转频率
  GPIO_Init(GPIOA, &GPIO_InitStructure);												// 初始化IO
  GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3);
}
/***********************************************************************************
函数名：void PWM_Set(const u16 pwm1, const u16 pwm2, const u16 pwm3, const u16 pwm4)
说明：PWM设置
入口：无
出口：无
备注：根据PWM的数值给与相应PWM信号灯的状态:
当PWM为0时，灯灭
不为0时，灯亮
************************************************************************************/
void PWM_Set(const u16 pwm1, const u16 pwm2, const u16 pwm3, const u16 pwm4)
{
    /*
	if (pwm1 == 0)	//没有PWM，此时灯灭
		LED1 = 1;
	else
		LED1 = 0;
	if (pwm2 == 0)	//没有PWM，此时灯灭
		LED2 = 1;
	else
		LED2 = 0;
	if (pwm3 == 0)	//没有PWM，此时灯灭
		LED3 = 1;
	else
		LED3 = 0;
	if (pwm4 == 0)	//没有PWM，此时灯灭
		LED4 = 1;
	else
		LED4 = 0;
	*/
	TIM_SetCompare1(TIM2, pwm1);
	TIM_SetCompare2(TIM2, pwm2);
	TIM_SetCompare3(TIM2, pwm3);
	TIM_SetCompare4(TIM2, pwm4);
}
