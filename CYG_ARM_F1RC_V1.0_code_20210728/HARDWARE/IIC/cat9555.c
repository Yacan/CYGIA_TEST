#include "cat9555.h"
#include "My_IIC.h"
#include <stdio.h>
/*    ph4,ph5      addr: A2,A1,A0 011    config reg 0 output 1 input
      reset cat9555 is input pull up;
*/

uint8_t BIT_AND[8]={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
uint8_t	BIT_OR[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
//设置方向
//MSB-LSB bit x.7 - x.0
//DTB_CAT9555-1 00001100 00000000
//DTB_CAT9555-2 00000000 00000000
uint8_t IO_DIR_DTB1[2] = {0x00,0x0C};
uint8_t IO_DIR_DTB2[2] = {0x00,0x00};
//设置初始状态
//MSB-LSB bit x.7 - x.0
//DTB_CAT9555-1 00010001 00000110
//DTB_CAT9555-2 00000000 00000000
uint8_t IO_STA_DTB1[2] = {0x06,0x11};
uint8_t IO_STA_DTB2[2] = {0x00,0x00};

uint8_t IO_DIR_PDD1[2] = {0x00,0x00};
uint8_t IO_DIR_PDD2[2] = {0x00,0x00};

uint8_t IO_STA_PDD1[2] = {0x00,0x00};
uint8_t IO_STA_PDD2[2] = {0x00,0x00};
void CAT9555_Init(u8 IICBus)
{	
	char sta = 0;
	
	sta += Cat9555_Config(IICBus,1,IO_DIR_PDD1);
	sta += Cat9555_Set_IO_State(IICBus,1,IO_STA_PDD1);

	if(sta != 0) printf("Initial PDD cat9555 fail.\r\n");
}

/********************** Hard Lever API *********************/
//return 1 mean FAIL ,return 0 mean OK.
uint8_t Cat9555_I2cApiWrite(u8 IICBus,uint8_t add,uint8_t regadd,uint8_t *data,uint8_t len)
{
	char sta;
	/*** need edit api ***/
	sta =  IIC_Write(IICBus,add,&regadd,1,data,len);
	return sta; //success 0
}
uint8_t Cat9555_I2cApiRead(u8 IICBus,uint8_t add,uint8_t regadd,uint8_t *data,uint8_t len)
{
	char sta;
	sta = IIC_Read(IICBus,add,regadd,data,len);
	return sta;
	/*** need edit api ***/
}
/********************** User API *********************/

uint8_t Cat9555_Config(u8 IICBus,uint8_t ICx,uint8_t *configdata)//ICx is 1 to 8
{
	uint8_t add=0;
	add=((ICx-1) << 1) + 0x40;
	if (Cat9555_I2cApiWrite(IICBus,add,0x06,configdata,2)!=0)
	{
		return 1;
	}
	else
		return 0;
}

uint8_t Cat9555_Output(u8 IICBus,uint8_t ch,uint8_t value)//control each IO; ch1 to ch128
{
	uint8_t chx,ic_add,reg_add,io,temp;

	chx=ch-1;
	ic_add=((chx/16)<<1)+0x40;
	reg_add=chx%16/8+2;  //command 02,03
	io=chx%16%8;

	if (Cat9555_I2cApiRead(IICBus,ic_add,reg_add,&temp,1)!=0)
		return 1;
	if (value==1)
		temp=temp | BIT_OR[io];
	else
		temp=temp & BIT_AND[io];
	if (Cat9555_I2cApiWrite(IICBus,ic_add,reg_add,&temp,1)!=0)	
		return 1;
	else
		return 0;

}
uint8_t Cat9555_Input(u8 IICBus,uint8_t ch,uint8_t *value)
{
	uint8_t chx,ic_add,reg_add,io,temp;

	chx=ch-1;
	ic_add=((chx/16)<<1)+0x40;
	reg_add=chx%16/8;     //command 00,01
	io=chx%16%8;
	if (Cat9555_I2cApiRead(IICBus,ic_add,reg_add,&temp,1)!=0)
		return 1;
	temp=temp & BIT_OR[io];
	if (temp==BIT_OR[io])
		*value=1;
	else
		*value=0;
	return 0;

}

uint8_t Cat9555_Set_IO_State(u8 IICBus,uint8_t ICx,uint8_t *data)//ICx is 1 to 8
{
	uint8_t add=0;
	add=((ICx-1) << 1) + 0x40;
	if (Cat9555_I2cApiWrite(IICBus,add,0x02,data,2)!=0)
	{
		return 1;
	}
	else
		return 0;
}
