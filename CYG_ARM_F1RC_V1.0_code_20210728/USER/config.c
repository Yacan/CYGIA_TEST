#include "config.h"
#include "stm32f10x.h"
void GPIO_Config_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

//	/* Enable GPIOX Clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOB, ENABLE);
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable|GPIO_Remap_SWJ_JTAGDisable|GPIO_Remap_SWJ_NoJTRST|GPIO_Remap_PD01, ENABLE);
    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
  //LED
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	//推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);

	//PD--
//	GPIO_InitStructure.GPIO_Pin=Relay14|Relay15|Relay16|Relay17|Relay18|Relay19|Relay20|Relay21|Relay22\
//	|Relay23|Relay24|Relay25|Relay26|Relay06|Relay27|Relay28|Relay29;
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	//推挽输出
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_Init(GPIOD, &GPIO_InitStructure);
//	GPIO_ResetBits(GPIOD,Relay14|Relay15|Relay16|Relay17|Relay18|Relay19|Relay20|Relay21|Relay22\
//	|Relay23|Relay24|Relay25|Relay26|Relay06|Relay27|Relay28|Relay29);
	
	GPIO_InitStructure.GPIO_Pin=Relay00|Relay01|Relay02|Relay03|Relay04|Relay05|Relay06|Relay07|Relay08|Relay09|Relay10|Relay11|Relay12|Relay13|Relay14|Relay15;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	//推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOD,GPIO_InitStructure.GPIO_Pin);
//	
	GPIO_InitStructure.GPIO_Pin=Relay00|Relay01|Relay02|Relay03|Relay04|Relay05|Relay06;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	//推挽输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOE,GPIO_InitStructure.GPIO_Pin);
	
}
