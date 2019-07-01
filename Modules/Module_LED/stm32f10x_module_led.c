#include "stm32f10x_module_led.h"

void LED_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOA,  &GPIO_InitStructure);
  GPIO_ResetBits(GPIOA,GPIO_Pin_11 | GPIO_Pin_8);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB,  &GPIO_InitStructure);
  GPIO_ResetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_3);
}

void LED_Front_Off(void)
{
    GPIO_ResetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_3);
}

void LED_Front_ON(void)
{
    GPIO_SetBits(GPIOB,GPIO_Pin_1 | GPIO_Pin_3);
}

void LED_Tail_Off(void)
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_11 | GPIO_Pin_8);
}

void LED_Tail_ON(void)
{
    GPIO_SetBits(GPIOA,GPIO_Pin_11 | GPIO_Pin_8);
}
