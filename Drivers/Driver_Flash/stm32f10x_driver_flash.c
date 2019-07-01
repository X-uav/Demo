#include "stm32f10x_driver_delay.h"
#include "stm32f10x_driver_flash.h"

// The start address of small capacity flash's last page is 0X08007C00, end
// address is 0X08007FFF. Every page is 1k bytes.

/***************************
函数名：void Flash_Lock(void)
说明：锁定Flash
入口：无
出口：无
备注：无
****************************/
void Flash_Lock(void)
{
    FLASH->CR |= 1 << 7;
}

/***************************
函数名：void Flash_Unlock(void)
说明：解锁Flash
入口：无
出口：无
备注：无
****************************/
void Flash_Unlock(void)
{
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;
}

/*********************************************
函数名：u16 Flash_ReadHalfWord(u32 flash_addr)
说明：读取指定地址的半字(16位数据)
入口：flash_addr : 读地址 (此地址必须为2的倍数)
出口：对应数据
备注：无
**********************************************/
u16 Flash_ReadHalfWord(u32 flash_addr)
{
    return *(vu16 *)flash_addr;
}

/*********************************************************************
函数名：void Flash_Read(u32 read_addr, u16 *buffer, u16 half_word_nums)
说明：从指定地址开始读出指定长度的数据
入口： read_addr: 起始地址
      buffer: 数据指针
      half_word_nums: 半字(16位)数
出口：对应数据
备注：无
**********************************************************************/
void Flash_Read(u32 read_addr, u16 *buffer, u16 half_word_nums)
{
    u16 i;

    for (i = 0; i < half_word_nums; i++)
    {
        //-----读取2个字节-----//
        buffer[i]  = Flash_ReadHalfWord(read_addr);
        //-----偏移2个字节-----//
        read_addr += 2;
    }
}

#if FLASH_WREN

#if FLASH_SIZE < 256
#define FLASH_SECTOR_SIZE 1024 // 字节
#else
#define FLASH_SECTOR_SIZE 2048
#endif

//-----最多是2K字节 (将整个Flash的用数组表示出来)----//
u16 Flash_Buffer[FLASH_SECTOR_SIZE / 2];

/******************************************************************************
函数名：void Flash_Write(u32 write_addr, u16 *buffer, u16 half_word_nums)
说明：从指定地址开始写入指定长度的数据
入口：write_addr: 起始地址(此地址必须为2的倍数)
     buffer: 数据指针
     half_word_nums: 半字(16位)数(要写入的16位数据的个数)
出口：无
备注：无
*******************************************************************************/
void Flash_Write(u32 write_addr, u16 *buffer, u16 half_word_nums)
{
    u16 i;
    //-----扇区内偏移地址(16位字计算)----//
    u16 sector_offset;
    //-----扇区内剩余地址(16位字计算)----//
    u16 sector_remain;
    //-----扇区地址----//
    u32 sector_addr;
    //-----去掉0X08000000后的地址----//
    u32 offset_addr;

    if (write_addr <   FLASH_BASE
    || (write_addr >= (FLASH_BASE + 1024 * FLASH_SIZE)))
    {
        //-----非法地址----//
        return ;
    }

    //-----解锁----//
    Flash_Unlock();

    //-----实际偏移地址----//
    offset_addr   =  write_addr - FLASH_BASE;
    //-----扇区地址  0~127 for STM32F103RBT6----//
    sector_addr   =  offset_addr / FLASH_SECTOR_SIZE;
    //-----在扇区内的偏移(2个字节为基本单位)----//
    sector_offset = (offset_addr % FLASH_SECTOR_SIZE) / 2;
    //-----扇区剩余空间大小----//
    sector_remain = FLASH_SECTOR_SIZE / 2 - sector_offset;

    //-----不大于该扇区范围----//
    if (half_word_nums <= sector_remain)
    {
        sector_remain = half_word_nums;
    }

    while (1)
    {
        //-----读出整个扇区的内容----//
        Flash_Read(sector_addr * FLASH_SECTOR_SIZE + FLASH_BASE, Flash_Buffer,
                   FLASH_SECTOR_SIZE / 2);

        //-----校验数据----//
        for (i = 0; i < sector_remain; i++)
        {
            //-----需要擦除----//
            if (Flash_Buffer[sector_offset + i] != 0XFFFF)
            {
                break;
            }
        }
        //-----需要擦除----//
        if (i < sector_remain)
        {
            //-----擦除这个扇区----//
            Flash_ErasePage(sector_addr * FLASH_SECTOR_SIZE + FLASH_BASE);
            //-----拷贝这个扇区----//
            for (i = 0; i < sector_remain; i++)
            {
                Flash_Buffer[sector_offset + i] = buffer[i];
            }

            //-----写入整个扇区----//
            Flash_WriteNoCheck(sector_addr * FLASH_SECTOR_SIZE + FLASH_BASE,
                                Flash_Buffer, FLASH_SECTOR_SIZE / 2);
        }
        else
        {
            //-----写已经擦除了的,直接写入扇区剩余区间----//
            Flash_WriteNoCheck(write_addr, buffer, sector_remain);
        }

        //-----写入结束----//
        if (half_word_nums == sector_remain)
        {
            break;
        }
        //-----写入未结束----//
        else
        {
            //-----扇区地址增1----//
            sector_addr    += 1;
            //-----偏移位置为0----//
            sector_offset   = 0;
            //-----指针偏移----//
            buffer         += sector_remain;
            //-----写地址偏移----//
            write_addr     += sector_remain;
            //-----字节(16位)数递减----//
            half_word_nums -= sector_remain;
            if (half_word_nums > (FLASH_SECTOR_SIZE / 2))
            {
                //-----下一个扇区还是写不完----//
                sector_remain = FLASH_SECTOR_SIZE / 2;
            }
            else
            {
                //-----下一个扇区可以写完了----//
                sector_remain = half_word_nums;
            }
        }
    }

    //-----上锁----//
    Flash_Lock();
}

/******************************************************************************
函数名：void Flash_WriteNoCheck(u32 write_addr, u16 *buffer, u16 half_word_nums)
说明：不检查的写入
入口：write_addr: 起始地址
     buffer: 数据指针
     half_word_nums: 半字(16位)数
出口：无
备注：无
*******************************************************************************/
void Flash_WriteNoCheck(u32 write_addr, u16 *buffer, u16 half_word_nums)
{
    u16 i;

    for (i = 0; i < half_word_nums; i++)
    {
        Flash_WriteHalfWord(write_addr, buffer[i]);
        //-----偏移2个字节-----//
        write_addr += 2;
    }
}

#endif


/***********************************************************
函数名：u8 Flash_ErasePage(u32 page_addr)
说明: 擦除页
入口：无
出口：无
备注：无
***********************************************************/
u8 Flash_ErasePage(u32 page_addr)
{
    u8 status = 0;
    //-----等待上一个操作结束----//
    status = Flash_WaitDone(0X5FFF);

    if (status == FLASH_STATE_OK)
    {
        //-----置位页面清除标志----//
        FLASH->CR |= 1 << 1;
        //-----设置页面地址----//
        FLASH->AR  = page_addr;
        //-----开始擦除页----//
        FLASH->CR |= 1 << 6;
        //-----等待操作结束(>20ms)----//
        status = Flash_WaitDone(0X5FFF);
        if (status != FLASH_STATE_BUSY)
        {
            //-----清除页面清除标志----//
            FLASH->CR &= ~(1 << 1);
        }
    }

    return status;
}

/***********************************************************
函数名：u8 Flash_GetStatus(void)
说明: 获取Flash状态
入口：无
出口：无
备注：无
***********************************************************/
u8 Flash_GetStatus(void)
{
    u32 status = FLASH->SR;

    if (status & (1 << 0))
    {
        //-----忙----//
        return FLASH_STATE_BUSY;
    }
    else if (status & (1 << 2))
    {
        //-----写入错误----//
        return FLASH_STATE_ERROR_PRO;
    }
    else if (status & (1 << 4))
    {
        //-----写保护错误----//
        return FLASH_STATE_ERROR_WP;
    }

    return 0;
}

/***********************************************************
函数名：u8 Flash_WaitDone(u16 time)
说明: 等待操作结束
入口：u16 time: 等待时间
出口：Flash状态
备注：无
***********************************************************/
u8 Flash_WaitDone(u16 time)
{
    u8 status;

    do
    {
        status = Flash_GetStatus();
        if (status != FLASH_STATE_BUSY)
        {
            break;
        }
        Delay_us(1);
        time--;
    }
    while (time);

    if (time == 0)
    {
        status = FLASH_STATE_TIMEOUT;
    }

    return status;
}

/***********************************************************
函数名：u8 Flash_WriteHalfWord(u32 flash_addr, u16 half_word)
说明: 在指定地址写入半字(16位数据)
入口：flash_addr : 写地址 (此地址必须为2的倍数)
     half_word : 写入的半字
出口：Flash状态
备注：无
***********************************************************/
u8 Flash_WriteHalfWord(u32 flash_addr, u16 half_word)
{
    u8 status = Flash_WaitDone(0XFF);

    if (status == FLASH_STATE_OK)
    {
        //-----使能写入----//
        FLASH->CR |= 1 << 0;
        //-----写入半字----//
        *(vu16 *)flash_addr = half_word;
        //-----等待操作结束----//
        status = Flash_WaitDone(0XFF);
        if (status != FLASH_STATE_BUSY)
        {
            //-----失能写入----//
            FLASH->CR &= ~(1 << 0);
        }
    }

    return status;
}
