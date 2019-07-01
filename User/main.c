#include "stm32f10x.h"

#include "stm32f10x_driver_delay.h"
#include "stm32f10x_driver_iic.h"
#include "stm32f10x_driver_timer.h"
#include "stm32f10x_driver_spi.h"
#include "stm32f10x_driver_nvic.h"
#include "stm32f10x_driver_usart.h"
#include "stm32f10x_driver_flash.h"

#include "stm32f10x_module_led.h"
#include "stm32f10x_module_motor.h"
#include "stm32f10x_module_mpu6050.h"
#include "stm32f10x_module_nrf24l01.h"

//-----外部变量声明-----//
extern u16 g_tim3counter;	// 定时器2计数器，用来在进入程序时的强制置0

//-----姿态角-----//
extern float g_Pitch;	// 范围-180°~+180° -->上正下负
extern float g_Roll;		// 范围-90°~+90°		-->左负右正
extern float g_Yaw;		// 范围-180°~+180° -->逆时针为正,顺时针为负

//-----系统控制周期开关变量-----//
__IO u8 g_ConCycT_flag = 0;	// 每个控制周期开始时置1,volatile类型保证中断不出错

void HardWare_Init(void)
{
    LED_Configuration();
    Delay_Configuration();
    TIMx_Configuration();
    NVIC_Configuration();
    IIC_Configuration();
    SPI_Configuration();
    USART_Configuration();
    Motor_GPIO_Configuration();
    MPU6050_Init();
    NRF24L01_Init();
}

int main(int argc, char *argv[])
{

    HardWare_Init();

    PWM_Set(100,100,100,100);

}
