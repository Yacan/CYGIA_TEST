#include "my_iic.h"
#include "delay.h"

//IIC初始化
void IIC_Init(u8 IICBus)
{
  GPIO_InitTypeDef GPIO_InitStruct;
	
 	if(IICBus == I2C1_Bus)
  {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    
		//PB6,7初始化设置
			GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
		GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;	//输出推挽模式
		GPIO_InitStruct.GPIO_Speed=GPIO_Speed_10MHz;
		GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    I2C1_SDA(1);
    I2C1_SCL(1);
	}   
	if(IICBus == I2C2_Bus)
  {
//		__HAL_RCC_GPIOI_CLK_ENABLE();   //使能GPIOI时钟
//    
//    //PI0,1初始化设置
//    GPIO_Initure.Pin=GPIO_PIN_7|GPIO_PIN_8;
//    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
//    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
//    GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;    //快速
//    HAL_GPIO_Init(GPIOI,&GPIO_Initure);
//    
//    I2C2_SDA(1);
//    I2C2_SCL(1);
	}	
}

//产生IIC起始信号
void IIC_Start(u8 IICBus)
{
	if(IICBus == I2C1_Bus)
  {
		I2C1_SDA_OUT();     //sda线输出
		I2C1_SDA(1);	  	  
		I2C1_SCL(1);
		delay_us(4);
		I2C1_SDA(0);//START:when CLK is high,DATA change form high to low 
		delay_us(4);
		I2C1_SCL(0);//钳住I2C总线，准备发送或接收数据 
	}
	if(IICBus == I2C2_Bus)
  {
		I2C2_SDA_OUT();     //sda线输出
		I2C2_SDA(1);	  	  
		I2C2_SCL(1);
		delay_us(4);
		I2C2_SDA(0);//START:when CLK is high,DATA change form high to low 
		delay_us(4);
		I2C2_SCL(0);//钳住I2C总线，准备发送或接收数据 
	}
}	  
//产生IIC停止信号
void IIC_Stop(u8 IICBus)
{
	if(IICBus == I2C1_Bus)
  {
		I2C1_SDA_OUT();//sda线输出
		I2C1_SCL(0);
		I2C1_SDA(0);//STOP:when CLK is high DATA change form low to high
		delay_us(4);
		I2C1_SCL(1); 
		I2C1_SDA(1);//发送I2C总线结束信号
		delay_us(4);
	}
	if(IICBus == I2C2_Bus)
  {
		I2C2_SDA_OUT();//sda线输出
		I2C2_SCL(0);
		I2C2_SDA(0);//STOP:when CLK is high DATA change form low to high
		delay_us(4);
		I2C2_SCL(1); 
		I2C2_SDA(1);//发送I2C总线结束信号
		delay_us(4);
	}	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(u8 IICBus)
{
	u8 I2C1_ucErrTime=0;
	u8 I2C2_ucErrTime=0;

	if(IICBus == I2C1_Bus)
  {
		I2C1_SDA_IN();      //SDA设置为输入  
		I2C1_SDA(1);delay_us(1);	   
		I2C1_SCL(1);delay_us(1);	 
		while(READ_I2C1_SDA)
		{
			I2C1_ucErrTime++;
			if(I2C1_ucErrTime>250)
			{
				IIC_Stop(I2C1_Bus);
				return 1;
			}
		}
		I2C1_SCL(0);//时钟输出0
	}	
	if(IICBus == I2C2_Bus)
  {
		I2C2_SDA_IN();      //SDA设置为输入  
		I2C2_SDA(1);delay_us(1);	   
		I2C2_SCL(1);delay_us(1);	 
		while(READ_I2C2_SDA)
		{
			I2C2_ucErrTime++;
			if(I2C2_ucErrTime>250)
			{
				IIC_Stop(I2C2_Bus);
				return 1;
			}
		}
		I2C2_SCL(0);//时钟输出0
	}
	return 0;  
} 
//产生ACK应答
void IIC_Ack(u8 IICBus)
{
	if(IICBus == I2C1_Bus)
	{
		I2C1_SCL(0);
		I2C1_SDA_OUT();
		I2C1_SDA(0);
		delay_us(2);
		I2C1_SCL(1);
		delay_us(2);
		I2C1_SCL(0);
	}
	if(IICBus == I2C2_Bus)
	{
		I2C2_SCL(0);
		I2C2_SDA_OUT();
		I2C2_SDA(0);
		delay_us(2);
		I2C2_SCL(1);
		delay_us(2);
		I2C2_SCL(0);
	}
}
//不产生ACK应答		    
void IIC_NAck(u8 IICBus)
{
	if(IICBus == I2C1_Bus)
	{
		I2C1_SCL(0);
		I2C1_SDA_OUT();
		I2C1_SDA(1);
		delay_us(2);
		I2C1_SCL(1);
		delay_us(2);
		I2C1_SCL(0);
	}
	if(IICBus == I2C2_Bus)
	{
		I2C2_SCL(0);
		I2C2_SDA_OUT();
		I2C2_SDA(1);
		delay_us(2);
		I2C2_SCL(1);
		delay_us(2);
		I2C2_SCL(0);
	}
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 IICBus,u8 txd)
{                        
  u8 I2C1_t; 
	u8 I2C2_t; 

	if(IICBus == I2C1_Bus)
	{  
		I2C1_SDA_OUT(); 	    
		I2C1_SCL(0);//拉低时钟开始数据传输
		for(I2C1_t=0;I2C1_t<8;I2C1_t++)
		{              
			I2C1_SDA((txd&0x80)>>7);
			txd<<=1; 	  
			delay_us(2);   //对TEA5767这三个延时都是必须的
			I2C1_SCL(1);
			delay_us(2); 
			I2C1_SCL(0);	
			delay_us(2);
		}
	}
	if(IICBus == I2C2_Bus)
	{  
		I2C2_SDA_OUT(); 	    
		I2C2_SCL(0);//拉低时钟开始数据传输
		for(I2C2_t=0;I2C2_t<8;I2C2_t++)
		{              
			I2C2_SDA((txd&0x80)>>7);
			txd<<=1; 	  
			delay_us(2);   //对TEA5767这三个延时都是必须的
			I2C2_SCL(1);
			delay_us(2); 
			I2C2_SCL(0);	
			delay_us(2);
		}
	}		
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(u8 IICBus,unsigned char ack)
{
	unsigned char I2C1_i;
	u8 I2C1_receive = 0;
	
	unsigned char I2C2_i;
	u8 I2C2_receive = 0;

	if(IICBus == I2C1_Bus)
	{
		I2C1_SDA_IN();//SDA设置为输入
		for(I2C1_i=0;I2C1_i<8;I2C1_i++ )
		{
			I2C1_SCL(0); 
			delay_us(2);
			I2C1_SCL(1);
			I2C1_receive<<=1;
			if(READ_I2C1_SDA)I2C1_receive++;   
			delay_us(1); 
		}					 
		if (!ack)
			IIC_NAck(I2C1_Bus);//发送nACK
		else
			IIC_Ack(I2C1_Bus); //发送ACK   
		return I2C1_receive;
	}
	
	if(IICBus == I2C2_Bus)
	{
		I2C2_SDA_IN();//SDA设置为输入
		for(I2C2_i=0;I2C2_i<8;I2C2_i++ )
		{
			I2C2_SCL(0); 
			delay_us(2);
			I2C2_SCL(1);
			I2C2_receive<<=1;
			if(READ_I2C2_SDA)I2C2_receive++;   
			delay_us(1); 
		}					 
		if (!ack)
			IIC_NAck(I2C2_Bus);//发送nACK
		else
			IIC_Ack(I2C2_Bus); //发送ACK   
		return I2C2_receive;
	}
	return 0;
}

uint8_t IIC_Write(u8 IICBus,uint8_t add,uint8_t *regadd,uint8_t addlen,uint8_t *data,uint8_t len)
{
	char I2C1_i = 0;
	char I2C1_sta = 0;
	
	char I2C2_i = 0;
	char I2C2_sta = 0;

	if(IICBus == I2C1_Bus)
	{
		IIC_Start(I2C1_Bus);
		IIC_Send_Byte(I2C1_Bus,add); 
		IIC_Wait_Ack(I2C1_Bus);
		if(addlen == 2)
		{
			IIC_Send_Byte(I2C1_Bus,regadd[0]);
			IIC_Send_Byte(I2C1_Bus,regadd[1]);
			I2C1_sta = IIC_Wait_Ack(I2C1_Bus);
		}
		else
		{
			IIC_Send_Byte(I2C1_Bus,regadd[0]);
			I2C1_sta = IIC_Wait_Ack(I2C1_Bus);		
		}
		for(I2C1_i=0;I2C1_i<len;I2C1_i++)
		{
			IIC_Send_Byte(I2C1_Bus,data[I2C1_i]);
			I2C1_sta = IIC_Wait_Ack(I2C1_Bus);	
		}
		IIC_Stop(I2C1_Bus);	
		return I2C1_sta;
	}
	
	if(IICBus == I2C2_Bus)
	{
		IIC_Start(I2C2_Bus);
		IIC_Send_Byte(I2C2_Bus,add); 
		IIC_Wait_Ack(I2C2_Bus);
		if(addlen == 2)
		{
			IIC_Send_Byte(I2C2_Bus,regadd[0]);
			IIC_Send_Byte(I2C2_Bus,regadd[1]);
			I2C2_sta = IIC_Wait_Ack(I2C2_Bus);
		}
		else
		{
			IIC_Send_Byte(I2C2_Bus,regadd[0]);
			I2C2_sta = IIC_Wait_Ack(I2C2_Bus);		
		}
		for(I2C2_i=0;I2C2_i<len;I2C2_i++)
		{
			IIC_Send_Byte(I2C2_Bus,data[I2C2_i]);
			I2C2_sta = IIC_Wait_Ack(I2C2_Bus);	
		}
		IIC_Stop(I2C2_Bus);	
		return I2C2_sta;
	}
	return 0;
}

uint8_t IIC_Read(u8 IICBus,uint8_t add,uint8_t regadd,uint8_t *data,uint8_t len)
{
	char I2C1_i = 0;
	char I2C1_sta = 0;
	
	char I2C2_i = 0;
	char I2C2_sta = 0;

	if(IICBus == I2C1_Bus)
	{
		IIC_Start(I2C1_Bus);
		IIC_Send_Byte(I2C1_Bus,add);
		I2C1_sta = IIC_Wait_Ack(I2C1_Bus);
		IIC_Send_Byte(I2C1_Bus,regadd);
		I2C1_sta = IIC_Wait_Ack(I2C1_Bus);
		
		IIC_Start(I2C1_Bus);	
		IIC_Send_Byte(I2C1_Bus,add+1);
		I2C1_sta = IIC_Wait_Ack(I2C1_Bus);
		for(I2C1_i=0;I2C1_i<len;I2C1_i++)
		{
			if((len - I2C1_i)==1) data[I2C1_i]=IIC_Read_Byte(I2C1_Bus,0);
			else data[I2C1_i]= IIC_Read_Byte(I2C1_Bus,1);
		}
	//	IIC_NAck();
		IIC_Stop(I2C1_Bus);

		return I2C1_sta;
	}
	
	if(IICBus == I2C2_Bus)
	{
		IIC_Start(I2C2_Bus);
		IIC_Send_Byte(I2C2_Bus,add);
		I2C2_sta = IIC_Wait_Ack(I2C2_Bus);
		IIC_Send_Byte(I2C2_Bus,regadd);
		I2C2_sta = IIC_Wait_Ack(I2C2_Bus);
		
		IIC_Start(I2C2_Bus);	
		IIC_Send_Byte(I2C2_Bus,add+1);
		I2C2_sta = IIC_Wait_Ack(I2C2_Bus);
		for(I2C2_i=0;I2C2_i<len;I2C2_i++)
		{
			if((len - I2C2_i)==1) data[I2C2_i]=IIC_Read_Byte(I2C2_Bus,0);
			else data[I2C2_i]= IIC_Read_Byte(I2C2_Bus,1);
		}
	//	IIC_NAck();
		IIC_Stop(I2C2_Bus);

		return I2C2_sta;
	}
	return 0;
}

