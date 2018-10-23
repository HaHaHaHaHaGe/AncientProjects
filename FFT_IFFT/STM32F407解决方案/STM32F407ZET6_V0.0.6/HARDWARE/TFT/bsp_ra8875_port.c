/*
*********************************************************************************************************
*
*	模块名称 : RA8875芯片和MCU接口模块
*	文件名称 : bsp_ra8875_port.c
*	版    本 : V1.6
*	说    明 : RA8875底层驱动函数集。
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2013-02-01 armfly  正式发布
*		V1.1    2014-09-04 armfly  同时支持SPI和8080两种接口，自动识别。不采用宏控制。
*
*	Copyright (C), 2014-2015, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#include "bsp_ra8875_port.h"
#include "bsp_tft_lcd.h"
#include "LCD_RA8875.h"
#include "stm32f4xx.h"

uint8_t g_RA8875_IF = RA_HARD_8080_16;	/*　接口类型　*/

/*
*********************************************************************************************************
*	函 数 名: RA8875_ConfigGPIO
*	功能说明: 配置CPU访问接口，如FSMC. SPI等
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void RA8875_ConfigGPIO(void)
{
	static uint8_t s_run_first = 0;
	
	/* 如果已经运行过，则不再执行 */
	if (s_run_first == 1)
	{
		return;
	}
	
	s_run_first = 1;
	
	/* FSMC在 bsp_tft_lcd.c中已经配置好 */
	
	
	/* RA8875按照SPI接口设置后，通过总线方式依然可以读到0X75的特征，因此不能用来自动识别SPI模式 */

}

/*
*********************************************************************************************************
*	函 数 名: RA8875_ReadBusy
*	功能说明: 判断RA8875的WAIT引脚状态
*	形    参: 无
*	返 回 值: 1 表示正忙, 0 表示内部不忙
*********************************************************************************************************
*/
uint8_t RA8875_ReadBusy(void)
{
	if ((PORT_WAIT->IDR & PIN_WAIT) == 0) 
		return 1;
	else 
		return 0;
}

/*
*********************************************************************************************************
*	函 数 名: RA8875_Delaly1us
*	功能说明: 延迟函数, 不准, 主要用于RA8875 PLL启动之前发送指令间的延迟
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void RA8875_Delaly1us(void)
{
	uint8_t i;

	for (i = 0; i < 10; i++);	/* 延迟, 不准 */
}

/*
*********************************************************************************************************
*	函 数 名: RA8875_Delaly1ms
*	功能说明: 延迟函数.  主要用于RA8875 PLL启动之前发送指令间的延迟
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void RA8875_Delaly1ms(void)
{
	uint16_t i;

	for (i = 0; i < 5000; i++);	/* 延迟, 不准 */
}

/*
*********************************************************************************************************
*	函 数 名: RA8875_WriteCmd
*	功能说明: 写RA8875指令寄存器
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void RA8875_WriteCmd(uint8_t _ucRegAddr)
{
	{
		RA8875_REG = _ucRegAddr;	/* 设置寄存器地址 */
	}
}

/*
*********************************************************************************************************
*	函 数 名: RA8875_WriteData
*	功能说明: 写RA8875指令寄存器
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void RA8875_WriteData(uint8_t _ucRegValue)
{
	{
		RA8875_RAM = _ucRegValue;	/* 设置寄存器地址 */
	}
}

/*
*********************************************************************************************************
*	函 数 名: RA8875_ReadData
*	功能说明: 读RA8875寄存器值
*	形    参: 无
*	返 回 值: 寄存器值
*********************************************************************************************************
*/
uint8_t RA8875_ReadData(void)
{
	uint8_t value;
	
	{
		value = RA8875_RAM;		/* 读取寄存器值 */
	}

	return value;	
}

/*
*********************************************************************************************************
*	函 数 名: RA8875_WriteData16
*	功能说明: 写RA8875数据总线，16bit，用于RGB显存写入
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void RA8875_WriteData16(uint16_t _usRGB)
{
	{
		RA8875_RAM = _usRGB;	/* 设置寄存器地址 */
	}
}

/*
*********************************************************************************************************
*	函 数 名: RA8875_ReadData16
*	功能说明: 读RA8875显存，16bit RGB
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
uint16_t RA8875_ReadData16(void)
{
	uint16_t value;
	{
		value = RA8875_RAM;		/* 读取寄存器值 */
	}

	return value;	
}

/*
*********************************************************************************************************
*	函 数 名: RA8875_ReadStatus
*	功能说明: 读RA8875状态寄存器
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
uint8_t RA8875_ReadStatus(void)
{
	uint8_t value;
	{
		value = RA8875_REG;
	}
	return value;	
}

/*
*********************************************************************************************************
*	函 数 名: RA8875_GetDispMemAddr
*	功能说明: 获得显存地址。
*	形    参: 无
*	返 回 值: 显存地址
*********************************************************************************************************
*/
uint32_t RA8875_GetDispMemAddr(void)
{
		return RA8875_RAM_ADDR;
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
