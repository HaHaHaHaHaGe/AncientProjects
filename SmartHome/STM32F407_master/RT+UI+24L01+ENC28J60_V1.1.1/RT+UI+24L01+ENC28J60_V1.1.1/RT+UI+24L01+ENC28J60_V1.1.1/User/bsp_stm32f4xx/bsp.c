/*
*********************************************************************************************************
*
*	模块名称 : BSP模块(For STM32F4XX)
*	文件名称 : bsp.c
*	版    本 : V1.1
*	说    明 : 这是硬件底层驱动程序的主文件。每个c文件可以 #include "bsp.h" 来包含所有的外设驱动模块。
*			   bsp = Borad surport packet 板级支持包
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2013-03-01  armfly   正式发布
*		V1.1    2013-06-20  armfly   规范注释，添加必要说明
*
*	Copyright (C), 2013-2014, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/
#include "bsp.h"
//const u8 mymac[6]={0x00,0x00,0x00,0x00,0x00,0x00};	//MAC地址
uint32_t lwip_localtime=0;
/*
*********************************************************************************************************
*	函 数 名: bsp_Init
*	功能说明: 初始化所有的硬件设备。该函数配置CPU寄存器和外设的寄存器并初始化一些全局变量。只需要调用一次
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/

void TIM3_Int_Init(u16 arr,u16 psc)
{ 
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);//??TIM3??牋�
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;//?????牋
	TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;//????牋'
	TIM_TimeBaseInitStructure.TIM_Period=arr;//?????牋
	TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);//???TIM3牋牋
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);//?????3????牋
	TIM_Cmd(TIM3,ENABLE);//?????牋�
  NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;//?????�
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x02;//?????1牋
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x03;//????3牋
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void bsp_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
	u32 x=0;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
    
	bsp_InitDWT();      /* 初始化DWT */
	bsp_InitUart(); 	/* 初始化串口 */
//	bsp_InitKey();		/* 初始化按键变量（必须在 bsp_InitTimer() 之前调用） */
	bsp_InitI2C();
	NRF24L01_Init(); 
	for(x=0;x<500000;x++);  
//	bsp_InitSPIBus();	/* 配置SPI总线 */
	while(NRF24L01_Check())	//检查NRF24L01是否在位.	
	{
			
	}			

	NRF24L01_RX_Mode();
	TIM3_Int_Init(9,8399);
	
	//ENC28J60_SPI3_Init();
//	while(ENC28J60_Init((u8*)mymac));
//	bsp_InitLed(); 		/* 初始LED指示灯端口 */
	
	LCD_InitHard();	    /* 初始化显示器硬件(配置GPIO和FSMC,给LCD发送初始化指令) */
	TOUCH_InitHard();
	
	

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); 
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1|GPIO_Pin_2| GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;	//PG6 7 推挽 	 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		/* 设为输出口 */
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		/* 设为开漏模式 */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/* 上下拉电阻不使能 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	/* IO口最大速度 */  	 
 	GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化指定IO
	GPIO_SetBits(GPIOC,GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12);//PG6,7,8上拉				
}

/*
*********************************************************************************************************
*    函 数 名: bsp_DelayUS
*    功能说明: us级延迟。
*    形    参:  n : 延迟长度，单位1 us
*    返 回 值: 无
*********************************************************************************************************
*/
void bsp_DelayUS(uint32_t _ulDelayTime)
{
    uint32_t ticks;
	uint32_t told,tnow,tcnt=0;
		    	 
	ticks = _ulDelayTime * (SystemCoreClock / 1000000);	 /* 需要的节拍数 */ 		 
	tcnt = 0;
	told = DWT_CYCCNT;         /* 刚进入时的计数器值 */

	while(1)
	{
		tnow = DWT_CYCCNT;	
        
		if(tnow != told)
		{	
		    /* 32位计数器是递增计数器 */    
			if(tnow > told)
			{
				tcnt += tnow - told;	
			}
			/* 重新装载 */
			else 
			{
				tcnt += UINT32_MAX - told + tnow;	
			}	
			
			told = tnow;

			/*时间超过/等于要延迟的时间,则退出 */
			if(tcnt >= ticks)break;
		}  
	}
}

u8 bsp_GetKey(void)
{

	if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10)) return 1;

	if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11)) return 2;

	if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12)) return 3;

	if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1)) return 4;

	if(!GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_2)) return 5;
	
	return 0;
}




void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)
	{
		lwip_localtime++;
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);//???????
	}
}
/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
