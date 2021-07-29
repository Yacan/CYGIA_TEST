
#include "Usart.h"	  
#include <stdio.h>

#ifdef STDLib
#ifdef UART_1
#define RX_SIZE						255


uint8_t Uart1RxFlag=0;
uint8_t RX1buff[RX_SIZE]={'\0'};
uint8_t RX2buff[RX_SIZE]={'\0'};
uint8_t Uart1Len = 0;

u8 USART2_RX_BUF[250]; 
u8 USART2_RX_CNT=0;
u16 USART2_RX_STA=0;       //??????  


uint8_t DMARxBuff[RX_SIZE]={'\0'};

/**********Debug*********/
int fputc(int ch, FILE *f)
{
	/* ����һ���ֽ����ݵ�USART2 */
	USART2->SR;
	USART_SendData(USART2, (uint8_t) ch);
	
	/* �ȴ�������� */
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);		

	return (ch);
}
/*********USER API************/

void Uart1_GpioInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��GPIOAʱ��

	//USART1_TX   PA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9
 
	//USART1_RX	  PA.10
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
	GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA10
}

void Uart1_DmaInit(uint8_t *Uart_RxAdd)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	DMA_DeInit(DMA1_Channel5);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Uart_RxAdd;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = RX_SIZE;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel5,&DMA_InitStructure);
 

	DMA_Cmd(DMA1_Channel5,ENABLE);
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);
}
void Uart2_DmaInit(uint8_t *Uart_RxAdd)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	DMA_DeInit(DMA1_Channel5);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Uart_RxAdd;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = RX_SIZE;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel5,&DMA_InitStructure);
 

	DMA_Cmd(DMA1_Channel5,ENABLE);
	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE);
}
/*********************USART1 Init**********************/
//��ʼ��IO ����1 
//bound:������
/*********************USART1 Init**********************/
void Uart1_Init(uint32_t bound)
{
	//GPIO�˿�����
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//ʹ��USART1ʱ��
	USART_DeInit(USART1);  //��λ����1

	Uart1_GpioInit();
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���

 //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;	//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;					//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

	USART_Init(USART1, &USART_InitStructure); 		//��ʼ������
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//�����ж�
	USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 
	
	Uart1_DmaInit(DMARxBuff);
//	USART_ClearFlag(USART1, USART_FLAG_TC);
	USART_GetFlagStatus(USART1, USART_FLAG_TC);
}
/*********************USART1 Init**********************/
//��ʼ��IO ����2
//bound:������
/*********************USART1 Init**********************/
void Uart2_Init(uint32_t bound)
{
		GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    //|RCC_APB2Periph_AFIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//ʹ��GPIOAʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//ʹ��USART2ʱ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;    //PA2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;    //��������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA3
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,ENABLE);//��λ����2
    RCC_APB1PeriphResetCmd(RCC_APB1Periph_USART2,DISABLE);//ֹͣ��λ

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);    //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�   0-3;
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //ʹ�ܴ���2�ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3; //��ռ���ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //�����ȼ�2��
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ʹ���ⲿ�ж�ͨ��
    NVIC_Init(&NVIC_InitStructure); //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

    USART_InitStructure.USART_BaudRate = bound;//����������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;//8λ���ݳ���
    USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;///��żУ��λ
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;//�շ�ģʽ

    USART_Init(USART2, &USART_InitStructure); ; //��ʼ������
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�����ж�
    USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���

}

/*********************USART SendString**********************/
void Uart1_SendString(char *nbuff)
{
	char *pbuff;
	pbuff=nbuff;
	while(*pbuff!='\0')
	{  	   
		USART_SendData(USART1, *(pbuff++));
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET); 
	}
}
void USART2_Send_Data(u8 *buf,u16 len)
{
    u16 t;
     for(t=0;t<len;t++)
    {
        while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
        USART_SendData(USART2,buf[t]);
    }
    while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
}
/*********************USART Send**********************/
void Uart1_SendByte(uint8_t Data)
{   
	USART_SendData(USART1, Data);
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET); 
}
void Uart1_SendArray(uint8_t *buff,uint16_t len)
{
	uint32_t i=0;
	uint8_t *pbuff;
	pbuff=buff;
	for(i=0;i<len;i++)
	{
		USART_SendData(USART1, *(pbuff++));
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET); 
	}
}
/***********************USART1_IRQHandler*************************/
void USART1_IRQHandler(void)                	//����1�жϷ������
{
	/*
	char temp;
  if(USART_GetITStatus(USART1, USART_IT_RXNE) == 1)
  {
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		temp = USART_ReceiveData(USART1);
		if(Uart1RxFlag==0)
		{				
			RX1buff[Uart1Len] = temp;				
			if(temp=='\n'||Uart1Len>254)
			{
				RX1buff[Uart1Len] = temp;
				Uart1RxFlag=1;
			}
			else
		  {			
				Uart1Len++;
		  }
		} 	  
  }
	*/
/***************DMA + USART IDLE****************/	
	uint32_t temp=0;
	uint16_t i=0;
	if(USART_GetITStatus(USART1,USART_IT_IDLE)!=RESET)
	{
		temp=USART1->SR;
		temp=USART1->DR;
		DMA_Cmd(DMA1_Channel5,DISABLE);
		temp=RX_SIZE-DMA_GetCurrDataCounter(DMA1_Channel5);
		if(Uart1RxFlag==0)
		{
			Uart1Len=temp;
			for(i=0;i<temp;i++)
			{
				RX1buff[i]=DMARxBuff[i];
				DMARxBuff[i]=0x00;
			}
			Uart1RxFlag=1;
		}
		else
		{
			for(i=0;i<temp;i++)
			{
				DMARxBuff[i]=0x00;
			}
			Uart1_SendString("MCU is Busy!\r\n");
		}
		DMA_SetCurrDataCounter(DMA1_Channel5,RX_SIZE);
		DMA_Cmd(DMA1_Channel5,ENABLE);

	}
} 
/***********************USART1_IRQHandler*************************/
void USART2_IRQHandler(void)
{
    u8 res;
     if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) //���յ�����
    {
        res =USART_ReceiveData(USART2);     //��ȡ���յ�������
        if(USART2_RX_STA==0)
        {
            USART2_RX_BUF[USART2_RX_CNT] = res;        //��¼���յ���ֵ
            //�����ݽ�β�յ�0xA0��0xA1�������ݽ�����ɣ���һ������������
            if(USART2_RX_BUF[USART2_RX_CNT-1]==0xA0&&USART2_RX_BUF[USART2_RX_CNT]==0xA1)
                USART2_RX_STA=1;//��ʾ�������ݽ���
            USART2_RX_CNT++;                        //������������1
        }
    }
    //���-������������Ҫ�ȶ�SR,�ٶ�DR�Ĵ����������������жϵ�����
    if(USART_GetFlagStatus(USART2,USART_FLAG_ORE) == SET)
    {
        USART_ReceiveData(USART2);
        USART_ClearFlag(USART2,USART_FLAG_ORE);
    }
     USART_ClearFlag(USART2,USART_IT_RXNE); //һ��Ҫ��������ж�
}
#endif
#endif







	

