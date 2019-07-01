#ifndef __STM32F10X_ALGORITHM_FUSION_H
#define __STM32F10X_ALGORITHM_FUSION_H

#include "stm32f10x.h"
#include "math.h"
#include "stm32f10x_module_mpu6050.h"

#define ACC_FILTER_DELAY 8	// 加速度计滤波之后环节,当前为3*16=48ms

//-----变量声明-----//
extern float g_Pitch;		// 姿态欧拉角
extern float g_Roll;
extern float g_Yaw;


//-----函数声明-----//
void ReadFromIMU(void); //// 读取MPU6050的值，包括加速度计和陀螺仪，一共6个值
extern void IMUupdata(float gx, float gy, float gz, float ax, float ay, float az);	// IMU单元数据融合，更新姿态四元数
extern void IMU_Filter(void);		// 加速度计滤波与陀螺仪标定输出

#endif
