/*
*********************************************************************************************************
*
*	ģ������ : ������ģ�顣
*	�ļ����� : main.c
*	��    �� : V3.0
*	˵    �� : ��ʵ����Ҫ
*              ʵ��Ŀ�ģ�
*                1. ѧϰFreeRTOS��������ƺ���ʹ�á�
*              ʵ�����ݣ�
*                1. ��������4���û�����
*              ע�����
*                1. ��ʵ���Ƽ�ʹ�ô�������SecureCRT��Ҫ�����ڴ�ӡЧ�������롣��������
*                   V5��������������С�
*                2. ��ؽ��༭��������������TAB����Ϊ4���Ķ����ļ���Ҫ��������ʾ�����롣
*
*	�޸ļ�¼ :
*		�汾��   ����        ����     ˵��
*		v1.0    2013-09-10  Eric2013  �������ļ���ST�̼���汾ΪV1.0.2
*		V2.0    2014-02-24  Eric2013  ����FreeRTOS��V8.0.0������F4�̼��⵽1.3.0 
*	    V3.0    2015-04-01  Eric2013  1. �����̼��⵽V1.5.0
*                                     2. ����BSP�弶֧�ְ�
*									  3. ����FreeRTOS��V8.2.0
*
*	Copyright (C), 2015-2020, ���������� www.armfly.com
*
*********************************************************************************************************
*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "croutine.h"
#include "bsp.h"
#include "GUI.h"

/*
**********************************************************************************************************
											��������
**********************************************************************************************************
*/
static void AppTaskCreate (void);
extern void vSetupTimerTest( void );

/*
**********************************************************************************************************
											��������
**********************************************************************************************************
*/
xTaskHandle xHandleTask3;
int8_t pcWriteBuffer[500];
u8 pcWriteBuffer2[500];

int pidx=0;
int pidy=0;
char pidd=0;
extern uint32_t lwip_localtime;		//lwip����ʱ�������,��λ:ms
u8 buffer[1518];
u8 buffer_[1518];

u8 ucKeyCode=0;
int Max;
WM_HWIN hWin;

char AIR_A_VALUE=32;
char AIR_B_VALUE=32;
char AIR_C_VALUE=32;
char Light_VALUE[6]={0,0,0,0,0,0};

char Send_Flag_AIRA=0;
char Send_Flag_AIRB=0;
char Send_Flag_AIRC=0;
char Send_Flag_Light[6]={0,0,0,0,0,0};
char Send_Flag_Switch[2]={0,0};
char Read_Flag_Data=0;


u8 AIR_A_MODE=0;
u8 AIR_B_MODE=0;
u8 AIR_C_MODE=0;

u8 Temp_A=0;
u8 Hum_A=0;

u8 Temp_B=0;
u8 Hum_B=0;

u8 Temp_C=0;
u8 Hum_C=0;

u8 DATA[100];
u8 DATA_N[32];

char a[5];
char b[5];
/*
*********************************************************************************************************
*	�� �� ��: main
*	����˵��: ��׼c������ڡ�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
int main(void)
{
    /* Ӳ����ʼ�� */
    bsp_Init();
	
	mymem_init(SRAMIN);		//��ʼ���ڲ��ڴ��
//	mymem_init(SRAMEX);		//��ʼ���ⲿ�ڴ��
//	mymem_init(SRAMCCM);	//��ʼ��CCM�ڴ��
	
	/* �������� */
	AppTaskCreate();
    
    vSetupTimerTest();
	
    /* �������ȣ���ʼִ������ */
    vTaskStartScheduler();

	/* ���ϵͳ���������ǲ������е�����ģ����е����Ｋ�п����ǿ�������heap�ռ䲻����ɴ���ʧ�� */
    while (1)
    {
    } 
}

/*
*********************************************************************************************************
*	�� �� ��: vTask1
*	����˵��: GUI�������
*	��    �Σ�pvParameters ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void vTask1( void *pvParameters )
{
    while(1)
    {
			
				
			
					if(DATA[3]>0)
					{
						DATA_N[0]=0;
						a[0]=(DATA[3]/10)+0x30;
						a[1]=(DATA[3]%10)+0x30;	
						a[2]=' ';
						a[3]='C';
						a[4]=0x00;
							
						b[0]=(DATA[5]/10)+0x30;
						b[1]=(DATA[5]%10)+0x30;	
						b[2]=' ';
						b[3]='%';
						b[4]=0x00;
						TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_6), a);
						TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_7), b);
					}
					else if(DATA_N[0]>10)
					{
						TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_6), "NULL");
						TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_7), "NULL");	
					}

				
				
				
				
				if(DATA[10]>0)
				{
					DATA_N[1]=0;
					a[0]=(DATA[10]/10)+0x30;
					a[1]=(DATA[10]%10)+0x30;	
					a[2]=' ';
					a[3]='C';
					a[4]=0x00;
						
					b[0]=(DATA[12]/10)+0x30;
					b[1]=(DATA[12]%10)+0x30;	
					b[2]=' ';
					b[3]='%';
					b[4]=0x00;
					TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_8), a);
					TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_9), b);
			  }
				else if(DATA_N[1]>10)
				{
					TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_8), "NULL");
					TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_9), "NULL");	
				}
				
				
				if(DATA[17]>0)
				{
					DATA_N[2]=0;
					a[0]=(DATA[17]/10)+0x30;
					a[1]=(DATA[17]%10)+0x30;	
					a[2]=' ';
					a[3]='C';
					a[4]=0x00;
						
					b[0]=(DATA[19]/10)+0x30;
					b[1]=(DATA[19]%10)+0x30;	
					b[2]=' ';
					b[3]='%';
					b[4]=0x00;
					TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_10), a);
					TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_11), b);
			  }
				else if(DATA_N[2]>10)
				{
					TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_10), "NULL");
					TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_11), "NULL");	
				}
				
				
				
				
				
				
				if(DATA[69]==100) 
				{
					DATA_N[3]=0;
					TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_12), "OFF");
				}
				else if(DATA[69]==1)
				{
					DATA_N[3]=0;
					TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_12), "ON");
				}
				else if(DATA_N[3]>10)
					TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_12), "NULL");
				

				if(DATA[76]==100) 
				{
					DATA_N[4]=0;
					TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_13), "OFF");
				}
				else if(DATA[76]==1)
				{
					DATA_N[4]=0;
					TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_13), "ON");
				}
				else if(DATA_N[4]>10)
					TEXT_SetText(WM_GetDialogItem(hWin, ID_TEXT_13), "NULL");
			vTaskDelay( 100 );
	}
}

/*
*********************************************************************************************************
*	�� �� ��: vTask5
*	����˵��: �ڵ����ݴ���
*	��    �Σ�pvParameters ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void vTask5( void *pvParameters )
{
	DATA_N[0]=0;
	DATA_N[1]=0;
	DATA_N[2]=0;
	DATA_N[3]=0;
    while(1)
    {
			if(Read_Flag_Data==0)
				if(Read_Net_Address(DATA,1)==0) DATA_N[0]++; 
			if(Read_Flag_Data==1)
				if(Read_Net_Address(DATA,2)==0) DATA_N[1]++; 
			if(Read_Flag_Data==2)
				if(Read_Net_Address(DATA,3)==0) DATA_N[2]++; 
			if(Read_Flag_Data==3)
				if(Read_Net_Address(DATA,10)==0) DATA_N[3]++; 
			if(Read_Flag_Data==4)
				if(Read_Net_Address(DATA,11)==0) DATA_N[4]++; 
			
		//	Write_Net_Address(AIR_A_VALUE&AIR_A_MODE,1);
			if(Send_Flag_AIRA)  if(!Write_Net_Address(0|AIR_A_MODE,AIR_A_VALUE,1)) Send_Flag_AIRA=0;
			if(Send_Flag_AIRB)  if(!Write_Net_Address(0|AIR_B_MODE,AIR_B_VALUE,2)) Send_Flag_AIRB=0;
			if(Send_Flag_AIRC)  if(!Write_Net_Address(0|AIR_C_MODE,AIR_C_VALUE,3)) Send_Flag_AIRC=0;
//			
			if(Send_Flag_Light[0]) {Write_Net_Address(1,Light_VALUE[0],4); Send_Flag_Light[0]=0;}
			if(Send_Flag_Light[1]) {Write_Net_Address(1,Light_VALUE[1],5); Send_Flag_Light[1]=0;}
			if(Send_Flag_Light[2]) {Write_Net_Address(1,Light_VALUE[2],6); Send_Flag_Light[2]=0;}
			if(Send_Flag_Light[3]) {Write_Net_Address(1,Light_VALUE[3],7); Send_Flag_Light[3]=0;}
			if(Send_Flag_Light[4]) {Write_Net_Address(1,Light_VALUE[4],8); Send_Flag_Light[4]=0;}
			if(Send_Flag_Light[5]) {Write_Net_Address(1,Light_VALUE[5],9); Send_Flag_Light[5]=0;}
			
			Write_Net_Address(2,DATA[30],10); 
			Write_Net_Address(2,DATA[31],11); 
			
			
			Read_Flag_Data++;
			if(Read_Flag_Data==5) Read_Flag_Data=0;
			vTaskDelay( 100 );
    }
		//vTaskDelay( 1000 );
}

/*
*********************************************************************************************************
*	�� �� ��: vTask2
*	����˵��: ����ɨ��
*	��    �Σ�pvParameters ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void vTask2( void *pvParameters )
{
	portTickType xLastWakeTime;
    const portTickType xFrequency = 10;

	/* ��ȡϵͳʱ�� */
    xLastWakeTime = xTaskGetTickCount();

    while(1)
    {
			//RA8875_SetBackLight(Light_VALUE[2]*2.55);
				//GUI_TOUCH_Exec();
				GT811_OnePiontScan();
        vTaskDelayUntil( &xLastWakeTime, xFrequency );
    }
}
/*
*********************************************************************************************************
*	�� �� ��: vTask6
*	����˵��: ����ɨ��
*	��    �Σ�pvParameters ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void vTask6( void *pvParameters )
{
	portTickType xLastWakeTime;
    const portTickType xFrequency = 10;
	//while(lwip_comm_init()!=0);
//	while((lwipdev.dhcpstatus!=2)&&(lwipdev.dhcpstatus!=0XFF))//�ȴ�DHCP��ȡ�ɹ�/��ʱ���
//	{
//		lwip_periodic_handle();
//	}
	u8  TimeAcc = 3;      
	/* ��ȡϵͳʱ�� */
    xLastWakeTime = xTaskGetTickCount();
    while (1) 
		{   
			ucKeyCode = bsp_GetKey();
			if(ucKeyCode != 0)
			{

				if (ucKeyCode == 1) 
				{
					pidx -= TimeAcc;
				}
				if (ucKeyCode == 2)  
				{
					pidx += TimeAcc;
				}
				if (ucKeyCode == 4)    
				{
					pidy -= TimeAcc;
				}
				if (ucKeyCode == 3) 
				{
					pidy += TimeAcc;
				}
				if (ucKeyCode == 5) 
				{
					pidd=1;
				}
				if (pidx < 0) 
				{
				pidx = 0;
				}
				if (pidy < 0) 
				{
				pidy = 0;
				}
				Max = LCD_GetXSize() - 1;
				if (pidx >= Max) 
				{
				pidx = Max;
				}
				Max = LCD_GetYSize() - 1;
				if (pidy > Max) 
				{
				pidy = Max;
				}
				 
				

			}
		 
						
		

        vTaskDelayUntil( &xLastWakeTime, xFrequency );
    }
}
/*
*********************************************************************************************************
*	�� �� ��: vTask3
*	����˵��: GUIˢ��
*	��    �Σ�pvParameters ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void vTask3( void *pvParameters )
{
		GUI_Init();
    WM_SetDesktopColor(GUI_WHITE);      /* Automacally update desktop window */
    WM_SetCreateFlags(WM_CF_MEMDEV);  /* Use memory devices on all windows to avoid flicker */
    PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
    FRAMEWIN_SetDefaultSkin(FRAMEWIN_SKIN_FLEX);
    PROGBAR_SetDefaultSkin(PROGBAR_SKIN_FLEX);
    BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
    CHECKBOX_SetDefaultSkin(CHECKBOX_SKIN_FLEX);
    DROPDOWN_SetDefaultSkin(DROPDOWN_SKIN_FLEX);
    SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
    SLIDER_SetDefaultSkin(SLIDER_SKIN_FLEX);
    HEADER_SetDefaultSkin(HEADER_SKIN_FLEX);
    RADIO_SetDefaultSkin(RADIO_SKIN_FLEX);
	  GUI_CURSOR_Show();
	
		hWin=CreateWindow();
    while(1)
    {
		/* �����Լ�������дNULL����xHandleTask3����������Ե� */
			GUI_Delay(5);
		
    }
}

/*
*********************************************************************************************************
*	�� �� ��: vTask4
*	����˵��: ��ӡ������Ϣ	
*	��    �Σ�pvParameters ���ڴ���������ʱ���ݵ��β�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void vTask4( void *pvParameters )
{
	portTickType xLastWakeTime;
    const portTickType xFrequency = 1000;

	 /* ��ȡϵͳʱ�� */
     xLastWakeTime = xTaskGetTickCount();
     
    while(1)
    {

        vTaskList((char *)&pcWriteBuffer);
		//printf("%s\r\n", pcWriteBuffer);
		
		vTaskGetRunTimeStats((char *)&pcWriteBuffer);
		//printf("%s\r\n", pcWriteBuffer);

        vTaskDelayUntil( &xLastWakeTime, xFrequency );
    }
}

/*
*********************************************************************************************************
*	�� �� ��: AppTaskCreate
*	����˵��: ����Ӧ������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void AppTaskCreate (void)
{
		xTaskCreate(    vTask1,     /* ������  */
                    "Number",   /* ������    */
                    500,        /* stack��С����λword��Ҳ����4�ֽ� */
                    NULL,       /* �������  */
                    4,          /* �������ȼ�*/
                    NULL );     /* ������  */
	
	xTaskCreate(    vTask2,     /* ������  */
                    "Touch",   /* ������    */
                    500,        /* stack��С����λword��Ҳ����4�ֽ� */
                    NULL,       /* �������  */
                    3,          /* �������ȼ�*/
                    NULL );     /* ������  */
	
	xTaskCreate(    vTask3,     /* ������  */
                    "GUI",   /* ������    */
                    500,        /* stack��С����λword��Ҳ����4�ֽ� */
                    NULL,       /* �������  */
                    2,          /* �������ȼ�*/
                    NULL );     /* ������  */
	
	
	xTaskCreate(    vTask4,     /* ������  */
                    "Print",   /* ������    */
                    500,        /* stack��С����λword��Ҳ����4�ֽ� */
                    NULL,       /* �������  */
                    1,          /* �������ȼ�*/
                    NULL );     /* ������  */
										
										
	xTaskCreate(    vTask5,     /* ������  */
                    "24L01",   /* ������    */
                    500,        /* stack��С����λword��Ҳ����4�ֽ� */
                    NULL,       /* �������  */
                    5,          /* �������ȼ�*/
                    NULL );     /* ������  */
			
		xTaskCreate(    vTask6,     /* ������  */
                    "TCP/Server",   /* ������    */
                    500,        /* stack��С����λword��Ҳ����4�ֽ� */
                    NULL,       /* �������  */
                    6,          /* �������ȼ�*/
                    NULL );     /* ������  */
}

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
