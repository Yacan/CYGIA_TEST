#include "Gpio.h"
#include "stm32f10x_gpio.h"
#include "Delay.h"
#include "usart.h"
#include "stdio.h"

uint16_t count_num = 0;
uint8_t Is_trigger = 0;
uint8_t Is_HC_EN = 0;

void Gpio_int(void)
{	
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//
	/**************Output*************/
	//PA
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_9|GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;	//输出推挽模式
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);		
	GPIO_SetBits(GPIOA,GPIO_Pin_2);
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	PA10_Control(0);
	PA9_Control(0);
	
	//PB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;	//输出推挽模式
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);	
	GPIO_ResetBits(GPIOB,GPIO_Pin_0);
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);
	GPIO_ResetBits(GPIOB,GPIO_Pin_2);
	GPIO_ResetBits(GPIOB,GPIO_Pin_3);
	GPIO_ResetBits(GPIOB,GPIO_Pin_4);
	
	//PC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;	//输出推挽模式
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOD, &GPIO_InitStruct);		
}
void Relay_io_int(void)
{	
	GPIO_InitTypeDef GPIO_InitStruct;
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);//
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//
	/**************Output*************/
	//PA
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;	//输出推挽模式
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);	
	GPIO_SetBits(GPIOA,GPIO_Pin_1);
	GPIO_ResetBits(GPIOA,GPIO_Pin_2);
	GPIO_ResetBits(GPIOA,GPIO_Pin_1);
	GPIO_ResetBits(GPIOA,GPIO_Pin_11);	
	GPIO_ResetBits(GPIOA,GPIO_Pin_12);
	GPIO_ResetBits(GPIOA,GPIO_Pin_14);
	GPIO_ResetBits(GPIOA,GPIO_Pin_15);
	
	//PB
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;	//输出推挽模式
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitStruct);	
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	GPIO_ResetBits(GPIOB,GPIO_Pin_10);
	GPIO_ResetBits(GPIOB,GPIO_Pin_11);
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
	
	//PC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_All;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;	//输出推挽模式
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	GPIO_ResetBits(GPIOC,GPIO_Pin_All);	
}
/*******************************************************************************
* Function Name  : Relay_test
* Description    : 
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
void Relay_test(uint8_t flag)
{
	if(flag)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_2);
		GPIO_SetBits(GPIOA,GPIO_Pin_0);
		GPIO_SetBits(GPIOA,GPIO_Pin_1);
		GPIO_SetBits(GPIOA,GPIO_Pin_11);	
		GPIO_SetBits(GPIOA,GPIO_Pin_12);
		GPIO_SetBits(GPIOA,GPIO_Pin_14);
		GPIO_SetBits(GPIOA,GPIO_Pin_15);
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		GPIO_SetBits(GPIOB,GPIO_Pin_8);
		GPIO_SetBits(GPIOB,GPIO_Pin_9);
		GPIO_SetBits(GPIOB,GPIO_Pin_10);
		GPIO_SetBits(GPIOB,GPIO_Pin_11);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		GPIO_SetBits(GPIOB,GPIO_Pin_13);
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
		GPIO_SetBits(GPIOB,GPIO_Pin_15);
		GPIO_SetBits(GPIOC,GPIO_Pin_All);	
	}
	else
	{
		GPIO_ResetBits(GPIOA,GPIO_Pin_2);
		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);	
		GPIO_ResetBits(GPIOA,GPIO_Pin_12);
		GPIO_ResetBits(GPIOA,GPIO_Pin_14);
		GPIO_ResetBits(GPIOA,GPIO_Pin_15);
		GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		GPIO_ResetBits(GPIOB,GPIO_Pin_8);
		GPIO_ResetBits(GPIOB,GPIO_Pin_9);
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);
		GPIO_ResetBits(GPIOB,GPIO_Pin_11);
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		GPIO_ResetBits(GPIOB,GPIO_Pin_13);
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
		GPIO_ResetBits(GPIOC,GPIO_Pin_All);	
	}
			
}
/*******************************************************************************
* Function Name  : PA2_Control
* Description    : W500复位
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
void PA10_Control(char type)
{
	if(type==0)
		GPIO_ResetBits(GPIOA,GPIO_Pin_10);
	else
		GPIO_SetBits(GPIOA,GPIO_Pin_10);
}
/*******************************************************************************
* Function Name  : PA3_Control
* Description    : W5500中断
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
void PA9_Control(char type)
{
	if(type==0)
		GPIO_ResetBits(GPIOA,GPIO_Pin_9);
	else
		GPIO_SetBits(GPIOA,GPIO_Pin_9);
}
/*******************************************************************************
* Function Name  : 
* Description    : 
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
void EXTI_Config(void)
{ 
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB|RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
		
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
    EXTI_InitStructure.EXTI_Line=EXTI_Line0;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;//EXTI_Trigger_Rising_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure); 

    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;  //
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;//
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00; //
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //
    NVIC_Init(&NVIC_InitStructure);	//
}
/*******************************************************************************
* Function Name  : 
* Description    : 
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line0) == SET)
	{	
		if(EXTI_GetITStatus(EXTI_Line0) == SET)
		{	
				while((EXTI_GetITStatus(EXTI_Line0) != RESET))
				{	
					EXTI_ClearITPendingBit(EXTI_Line0);//清除中断标志位					
					if( GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)==0)
					{
//						count_num = 0;
//						Is_trigger = 1;
						if(Is_HC_EN == 1)//触发
						{
							TRIGGER_SET(0);
							delay_us(50);
							TRIGGER_SET(1);
							Is_HC_EN = 0;
						}
//						HC_CE_SET(1);//CD74HC2017时钟失能
					}
					else if( GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0)==1)
					{
//						count_num = 0;
//						Is_trigger = 1;
//						if(Is_HC_EN == 0)//不触发
//						{
//								TRIGGER_SET(0);
//						}
//						HC_CE_SET(1);
						EXTI_ClearITPendingBit(EXTI_Line0);//清除中断标志位
					}
				}		
		}
	}	
}
/*******************************************************************************
* Function Name  : Gain_set
* Description    : 设置AD8253放大倍数
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
void Gain_set(char num)
{
	switch(num)
	{
		case 0:AP_WR_SET(1);delay_ms(5);AP_A1_SET(0);AP_A0_SET(0);delay_ms(5);AP_WR_SET(0);break;//1倍
		case 1:AP_WR_SET(1);delay_ms(5);AP_A1_SET(0);AP_A0_SET(1);delay_ms(5);AP_WR_SET(0);break;//10倍
		case 2:AP_WR_SET(1);delay_ms(5);AP_A1_SET(1);AP_A0_SET(0);delay_ms(5);AP_WR_SET(0);break;//100倍
		case 3:AP_WR_SET(1);delay_ms(5);AP_A1_SET(1);AP_A0_SET(1);delay_ms(5);AP_WR_SET(0);break;//1000倍
		default:break;
	}
}
