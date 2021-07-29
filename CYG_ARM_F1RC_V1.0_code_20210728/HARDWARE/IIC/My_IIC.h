#ifndef	 	__SPI_Driver_H
#define		__SPI_Driver_H

#include "stm32f10x.h"

typedef enum I2CBus{
	I2C1_Bus = 1,
	I2C2_Bus,
	I2C3_Bus,
	I2C4_Bus,
	I2C5_Bus,
}I2CBus;


#define I2C1_SCL(n)  		(n?GPIO_SetBits(GPIOB,GPIO_Pin_6):GPIO_ResetBits(GPIOB,GPIO_Pin_6)) //SCL
#define I2C1_SDA(n)  		(n?GPIO_SetBits(GPIOB,GPIO_Pin_7):GPIO_ResetBits(GPIOB,GPIO_Pin_7)) //SDA
#define READ_I2C1_SDA		GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7)  				//输入SDA
#define I2C1_SDA_IN()		{GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=0x80000000;GPIOB->ODR|=1<<7;}	//PB7输入模式
#define I2C1_SDA_OUT()	{GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=0x30000000;GPIOB->ODR|=1<<7;} //PB7输出模式

#define I2C2_SCL(n)  		(n?GPIO_SetBits(GPIOB,GPIO_Pin_6):GPIO_ResetBits(GPIOB,GPIO_Pin_6)) //SCL
#define I2C2_SDA(n)  		(n?GPIO_SetBits(GPIOB,GPIO_Pin_7):GPIO_ResetBits(GPIOB,GPIO_Pin_7)) //SDA
#define READ_I2C2_SDA		GPIO_ReadOutputDataBit(GPIOB,GPIO_Pin_7)  				//输入SDA
#define I2C2_SDA_IN()		{GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(uint32_t)0x8<<(7*4);GPIOB->ODR|=0<<7;}	//PB7输入模式
#define I2C2_SDA_OUT()	{GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(uint32_t)0x3<<(7*4);GPIOB->ODR|=0<<7;} //PB7输出模式

void IIC_Init(u8 IICBus);
uint8_t IIC_Write(u8 IICBus,uint8_t add,uint8_t *regadd,uint8_t addlen,uint8_t *data,uint8_t len);
uint8_t IIC_Read(u8 IICBus,uint8_t add,uint8_t regadd,uint8_t *data,uint8_t len);

#endif 
