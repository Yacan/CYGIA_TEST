#include "SPI_Driver.h"
#include "delay.h"


#ifdef SPI_1

#define SPI1_FILO

#define SPI_SCK_1	GPIO_SetBits(GPIOA, GPIO_Pin_7)			/* SCK = 1 */
#define SPI_SCK_0	GPIO_ResetBits(GPIOA, GPIO_Pin_7)		/* SCK = 0 */

#define SPI_MOSI_1	GPIO_SetBits(GPIOA, GPIO_Pin_5)			/* MOSI = 1 */
#define SPI_MOSI_0	GPIO_ResetBits(GPIOA, GPIO_Pin_5)		/* MOSI = 0 */

#define SPI_CS_1	GPIO_SetBits(GPIOA, GPIO_Pin_8)			/* CS = 1 */
#define SPI_CS_0	GPIO_ResetBits(GPIOA, GPIO_Pin_8)		/* CS = 0 */

#define SPI_READ_MISO    GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6)    /* 读MISO口线状态 */

#define Dummy_Byte    0x00    //读取时MISO发送的数据，可以为任意数据


void SPI1_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    //SCK、MOSI、CS引脚初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_7|GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;           //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //MISO引脚初始化
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU ;               //浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    SPI_CS_1;
    SPI_SCK_1;
}
void SPI1_CS_Ctr(uint8_t CS_CH,uint8_t type)
{
	uint16_t delay=0;
#ifdef STDLib	
	if(CS_CH==1)		//
	{
		if(type==0)
			SPI_CS_0;
		else
			SPI_CS_1;
	}
#endif
}

//SPI可以同时读取和写入数据，因此一个函数即可满足要求
uint8_t SPI_ReadWriteByte(uint8_t txData)
{
    uint8_t i;
    uint8_t rxData = 0;

    for(i = 0; i < 8; i++)
    {
        SPI_SCK_0;
        delay_us(1);
        //数据发送
        if(txData & 0x80)
		{
            SPI_MOSI_1;
        }
		else
		{
            SPI_MOSI_0;
        }
        txData <<= 1;
        delay_us(1);

        SPI_SCK_1;
        delay_us(1);
        //数据接收
        rxData <<= 1;
        if(SPI_READ_MISO)
		{
            rxData++;
        }
        delay_us(1);
    }
    SPI_SCK_0;

    return rxData;
}

uint8_t SPI_ReadByte(void)
{
//	uint8_t i;
//    uint8_t rxData = 0;
//	for(i = 0; i < 8; i++)
//    {
//        SPI_SCK_1;
//        delay_us(1);
//        //数据接收
//        rxData <<= 1;
//        if(SPI_READ_MISO)
//		{
//            rxData++;
//        }
//		SPI_SCK_0;
//		delay_us(1);
//    }
//	return rxData;
    return SPI_ReadWriteByte(Dummy_Byte);
}

void SPI_WriteByte(uint8_t txData)
{
    (void)SPI_ReadWriteByte(txData);
}


//uint8_t SPI1_Write(uint8_t ch,uint8_t *TxData,uint8_t len)
//{
//	uint8_t *pd;
//	uint16_t i;
//	SPI1_CS_Ctr(ch,0);
//	pd=TxData;
//	for(i=0;i<len;i++)
//	{
//		SPI_WriteByte(*pd);
//		pd++;
//	}	
//	SPI1_CS_Ctr(ch,1);
//	return 0;
//}
//uint8_t SPI1_Read(int8_t ch,uint8_t *RxData,uint8_t len)
//{
//	uint8_t *pd;
//	uint16_t timeout;
//	uint16_t i;
//	SPI1_CS_Ctr(ch,0);
//	pd=RxData;
//	for(i=0;i<len;i++)
//	{
//		timeout=200;
//		SPI_WriteByte(0xff);
//		*pd=SPI_ReadByte();
//		pd++;
//	}
//	SPI1_CS_Ctr(ch,1);
//	return 0;
//}
//uint8_t SPI1_WriteRead(int8_t ch,uint8_t *TxData,uint8_t *RxData,uint8_t len)
//{
//	
//	uint8_t *Tpd,*Rpd;
//	uint16_t timeout;
//	uint16_t i;
//	SPI1_CS_Ctr(ch,0);
//	Tpd=TxData;
//	Rpd=RxData;
//	for(i=0;i<len;i++)
//	{
//		timeout=2000;
//		SPI_WriteByte(*Tpd);
//		Tpd++;
//		*Rpd=SPI_ReadByte();
//		Rpd++;
//	}
//	SPI1_CS_Ctr(ch,1);
//	return 0;
//}
uint8_t SPI1_Write_Reg(uint8_t ch,uint8_t *reg,uint8_t *TxData,uint8_t reg_len,uint8_t Tx_len)
{
	uint8_t *pd;
	uint16_t timeout;
	uint16_t i;
	SPI1_CS_Ctr(ch,0);
	pd=reg;
	for(i=0;i<reg_len;i++)
	{	
		SPI_WriteByte(*pd);
		pd++;
	}
	pd=TxData;
	for(i=0;i<Tx_len;i++)
	{
		timeout=2000;	
		SPI_WriteByte(*pd);
		pd++;
	}
	SPI1_CS_Ctr(ch,1);
	return 0;
}
uint8_t SPI1_WriteRead_T2R(int8_t ch,uint8_t *TxData,uint8_t *RxData,uint8_t Tx_Len,uint8_t Rx_Len)
{
	
	uint8_t *Tpd,*Rpd;
	uint16_t i;
	SPI1_CS_Ctr(ch,0);
	Tpd=TxData;
	Rpd=RxData;
	for( i=0;i<Tx_Len;i++)
	{
		SPI_WriteByte(*Tpd);
		Tpd++;
//		*Rpd=SPI_ReadByte();
	}
	for( i=0;i<Rx_Len;i++)
	{
//		SPI_WriteByte(0x00);	
		*Rpd=SPI_ReadByte();
		Rpd++;
	}
	SPI1_CS_Ctr(ch,1);
	return 0;
}
#endif


