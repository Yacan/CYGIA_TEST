#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "w5500_conf.h"
#include "gpio.h"
#include "cat9555.h"
#include "My_iic.h"
#include "mycmd.h"
#include "My_flash.h"

#define Sendata		W5500_Tcp_Send	//发送函数

#define HELP_CMD				1
#define VERSION_CMD				2
#define SINGLET_CMD				3
#define AD8253_CMD				4
#define RELAY_CMD				5
#define SYNCT_CMD				6
#define CKIN_CMD				7
#define SETIP_CMD				8


extern uint8_t Is_HC_EN;
extern uint16_t count_num;

typedef struct{
	char *buff;
	uint8_t jlen;
	const char flag;
	float(*function)(char* buff);
}TCP_CMD;

float CMD_help(char* buff);
float CMD_version(char* buff);
float CMD_AD8253(char* buff);
float CMD_Relay(char* buff);
float CMD_Sgtrig(char* buff);
float CMD_Synctrig(char* buff);
float CMD_CKIN(char* buff);
float CMD_SETIP(char* buff);

TCP_CMD HELP_CMD_ARR		= {"Help\r\n",6,HELP_CMD,CMD_help};
TCP_CMD VERSION_CMD_ARR	 	= {"Version\r\n",9,VERSION_CMD,CMD_version};
TCP_CMD AD8253_CMD_ARR 		= {"AD8253:0/1/10/100/1000\r\n",7,AD8253_CMD,CMD_AD8253};
TCP_CMD RELAY_CMD_ARR 		= {"Relay:FFFFFFFF\r\n",6,RELAY_CMD,CMD_Relay};
TCP_CMD SINGLETRIG_CMD_ARR	= {"Single Trig\r\n",13,SINGLET_CMD,CMD_Sgtrig};
TCP_CMD SYNCTRIG_CMD_ARR 	= {"SYNC Trig:100\r\n",10,SYNCT_CMD,CMD_Synctrig};
TCP_CMD CKIN_CMD_ARR		= {"CKIN:0/1\r\n",5,CKIN_CMD,CMD_CKIN};
TCP_CMD SETIP_CMD_ARR		= {"Set IP:192.168.2.31\r\n",7,SETIP_CMD,CMD_SETIP};


char Version_buff[] = {"CYG8171_ARM_F1RC_V1.0.3_20210728\r\n"};


/*******************************************************************************
* Function Name  : SYNC_delay
* Description    : 
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
void SYNC_delay(uint16_t num)
{
	uint16_t i;
	for(i=0;i<num;i++)
	{
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();//__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	}
}
/*******************************************************************************
* Function Name  : TCP_Print
* Description    : 定义TCP printf函数
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
void TCP_Print(char *fmt,...)
{
	const char LEN = 100;
	char buffer[LEN];

	va_list arg_ptr; 
	va_start(arg_ptr, fmt); 
	vsnprintf(buffer, LEN+1, fmt, arg_ptr);
	Sendata((uint8_t*)buffer,strlen((char*)buffer));
	va_end(arg_ptr);
}
/*******************************************************************************
* Function Name  : string_compare_len
* Description    : 判断两数组特定长度字符串是否一样
* Input          : const  char *String1, char *String2 ,unsigned char LEN
* Output         : No.
* Return         : 1 or 0
*******************************************************************************/
unsigned char string_compare_len(const char *String1,char *String2,unsigned char LEN)
{
  unsigned char i=0;
	const char *p1=String1;
	char *p2=String2;
	for(i=0;i<LEN;i++)
	{
	    if(*p1!=*p2)
			return 0;
		p1++;
		p2++;
	}
	return 1;
}
/*******************************************************************************
* Function Name  : StrToHex
* Description    : 将大写16进制字符串转hex
* Input          : char *hex:保存转换后16进制数
									 char *str:输出字符串
									 char len:字符串长度
* Output         : No.
* Return         : 1 or 0
*******************************************************************************/
void StrToHex(unsigned char *hex,unsigned char *str,unsigned char len)
{
	unsigned char num = 0,i,j;
	
	len = len/2;
	
	for(i=0;i<len;i++) 
	{
		num = num << 4;
		for(j=0;j<2;j++)
		{
			num = num<< 4;
			if(*str<='9')
				num += *str-0x30;
			else num += *str-0x37;
			str++;
		}
//		printf("output:%#x\r\n",num);
		*hex = num;
		hex++;
	}	
}
/*******************************************************************************
* Function Name  : 
* Description    : 
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
float CMD_help(char *buff)
{
	TCP_Print(HELP_CMD_ARR.buff);
	TCP_Print(VERSION_CMD_ARR.buff);
	TCP_Print(SINGLETRIG_CMD_ARR.buff);
	TCP_Print(SYNCTRIG_CMD_ARR.buff);
	TCP_Print(AD8253_CMD_ARR.buff);
	TCP_Print(RELAY_CMD_ARR.buff);
	TCP_Print(CKIN_CMD_ARR.buff);
	TCP_Print(SETIP_CMD_ARR.buff);
	return 0;
}
/*******************************************************************************
* Function Name  : 
* Description    : 
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
float CMD_version(char *buff)
{
	TCP_Print(Version_buff);
	return 0;
}
/*******************************************************************************
* Function Name  : 
* Description    : 
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
float CMD_Sgtrig(char* buff)
{
	Is_HC_EN = 1;
	return 0;
}
/*******************************************************************************
* Function Name  : CMD_Synctrig
* Description    : 
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
float CMD_Synctrig(char* buff)
{
	uint16_t num = 0,i;
	num = atoi(buff+SYNCTRIG_CMD_ARR.jlen);
	__disable_irq();
	SYNC_SET(1);
	TRIGGER_SET(1);
	SYNC_delay(200);
	SYNC_SET(0);
	for(i=1;i<num;i++)
	{
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
		__NOP();__NOP();__NOP();__NOP();__NOP();//__NOP();__NOP();__NOP();__NOP();__NOP();
	}
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
	__NOP();__NOP();//__NOP();__NOP();__NOP();__NOP();
	TRIGGER_SET(0);
	SYNC_delay(100);
	TRIGGER_SET(1);
	__enable_irq();	
	return 0;
}
/*******************************************************************************
* Function Name  : 
* Description    : 
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
float CMD_AD8253(char* buff)
{
	uint16_t num;
	num = atoi(buff+AD8253_CMD_ARR.jlen);
	switch(num)
	{
		case 1:Gain_set(0);break;
		case 10:Gain_set(1);break;
		case 100:Gain_set(2);break;
		case 1000:Gain_set(3);break;
		default:break;
	}
	//Gain_set(2);
	return 0;
}
/*******************************************************************************
* Function Name  : 
* Description    : 
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
void Relay_control(uint8_t num,uint8_t byte)
{
	uint8_t R_bit = 0,status = 0,i;

	R_bit = num*8;
	
	status = byte;
	
	for(i=0;i<8;i++)
	{
		status = (byte>>i)&0X01;
//		TCP_Print("status = %d\r\n",R_bit);
		switch(R_bit)
		{
			case 0:RELAY0(status);break;
			case 1:RELAY1(status);break;
			case 2:RELAY2(status);break;
			case 3:RELAY3(status);break;
			case 4:RELAY4(status);break;
			case 5:RELAY5(status);break;
			case 6:RELAY6(status);break;
			case 7:RELAY7(status);break;
			case 8:RELAY8(status);break;
			case 9:RELAY9(status);break;
			case 10:RELAY10(status);break;		
			case 11:RELAY11(status);break;
			case 12:RELAY12(status);break;
			case 13:RELAY13(status);break;
			case 14:RELAY14(status);break;
			case 15:RELAY15(status);break;
			case 16:RELAY16(status);break;
			case 17:RELAY17(status);break;	
			case 18:RELAY18(status);break;	
			case 19:RELAY19(status);break;	
			case 20:RELAY20(status);break;	
			case 21:RELAY21(status);break;	
			case 22:RELAY22(status);break;	
			case 23:RELAY23(status);break;	
			case 24:RELAY24(status);break;	
			case 25:RELAY25(status);break;	
			case 26:RELAY26(status);break;	
			case 27:RELAY27(status);break;	
			case 28:RELAY28(status);break;	
			case 29:RELAY29(status);break;	
			case 30:RELAY30(status);break;	
			case 31 :RELAY31(status);break;	
		}
		R_bit++;
	}
}
/*******************************************************************************
* Function Name  : 
* Description    : 
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
float CMD_Relay(char* buff)
{
	static uint8_t flag = 0;
	uint8_t i;
	uint8_t num_buff[4] = {0};
	
	StrToHex(num_buff,(uint8_t*)(buff+RELAY_CMD_ARR.jlen),8);
	for(i=0;i<4;i++)
	{
		Relay_control(i,num_buff[i]);
//		TCP_Print("0x%02x\r\n",num_buff[i]);
	}
}
/*******************************************************************************
* Function Name  : CMD_CKIN
* Description    : 
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
float CMD_CKIN(char* buff)
{
	uint8_t i;
	
	i = atoi(buff+CKIN_CMD_ARR.jlen);
	switch(i)
	{
		case 1:CKIN(1);break;
		default:CKIN(0);break;
	}
	return 0;
}
/*******************************************************************************
* Function Name  : CMD_SETIP
* Description    : 
* Input          : 
* Output         : 
* Return         : 
*******************************************************************************/
float CMD_SETIP(char* buff)
{
	uint8_t ip_Byte[4] = {0};
	uint16_t ip_Words[2] = {0};
	char *in_buff;
	u8 i,j=0,k=strlen(buff);

	in_buff = buff;
	in_buff += SETIP_CMD_ARR.jlen;
	ip_Byte[0] = atoi(in_buff);
	for(i=0;i<k;i++)
	{
		if(*in_buff++ == '.')
		{
			ip_Byte[j+1] = atoi(in_buff);
			j++;
		}
	}	
	ip_Words[0] = ip_Byte[0];
	ip_Words[0] <<= 8;
	ip_Words[0] += ip_Byte[1];
	ip_Words[1] = ip_Byte[2];
	ip_Words[1] <<= 8;
	ip_Words[1] += ip_Byte[3];
//	ip_Words[0] = ((uint16_t)ip_Byte[0])<<8+ip_Byte[1];
//	ip_Words[1] = ((uint16_t)ip_Byte[2])<<8+ip_Byte[3];
//	printf("set ip:%d.%d.%d.%d\r\n",ip_Byte[0],ip_Byte[1],ip_Byte[2],ip_Byte[3]);
//	printf("set ip:%d.%d.%d.%d\r\n",ip_Words[0]>>8,(uint8_t)ip_Words[0],ip_Words[1]>>8,(uint8_t)ip_Words[1]);
//	printf("set ip:%d.%d\r\n",ip_Words[0],ip_Words[1]);
//	STMFLASH_Write_NoCheck(IP_Address,ip_Words,2);
	STMFLASH_Write(IP_Address,ip_Words,2);
}
/*******************************************************************************
* Function Name  : DataCMP
* Description    : 解析串口接收到的命令，并返回相应的数字代码
* Input          : None
* Output         : No.
* Return         : None
*******************************************************************************/
unsigned char  DataCMP(char *recbuff)
{ 
	if(string_compare_len(HELP_CMD_ARR.buff,recbuff ,HELP_CMD_ARR.jlen))					return HELP_CMD_ARR.flag;
	else if(string_compare_len(VERSION_CMD_ARR.buff,recbuff ,VERSION_CMD_ARR.jlen))			return VERSION_CMD_ARR.flag;
	else if(string_compare_len(SINGLETRIG_CMD_ARR.buff,recbuff ,SINGLETRIG_CMD_ARR.jlen))	return SINGLETRIG_CMD_ARR.flag;
	else if(string_compare_len(SYNCTRIG_CMD_ARR.buff,recbuff ,SYNCTRIG_CMD_ARR.jlen))		return SYNCTRIG_CMD_ARR.flag;
	else if(string_compare_len(AD8253_CMD_ARR.buff,recbuff ,AD8253_CMD_ARR.jlen))			return AD8253_CMD_ARR.flag;
	else if(string_compare_len(RELAY_CMD_ARR.buff,recbuff ,RELAY_CMD_ARR.jlen))				return RELAY_CMD_ARR.flag;
	else if(string_compare_len(CKIN_CMD_ARR.buff,recbuff ,CKIN_CMD_ARR.jlen))				return CKIN_CMD_ARR.flag;
	else if(string_compare_len(SETIP_CMD_ARR.buff,recbuff ,SETIP_CMD_ARR.jlen))				return SETIP_CMD_ARR.flag;
	else return 0;
}
/*******************************************************************************
* 函数名  : Process_Socket_Data
* 描述    : W5500接收并发送接收到的数据
* 输入    : s:端口号
* 输出    : 无
* 返回值  : 无
* 说明    : 本过程先调用S_rx_process()从W5500的端口接收数据缓冲区读取数据,
*			然后将读取的数据从Rx_Buffer拷贝到RXbuff缓冲区进行处理。
*			处理完毕，将数据从RXbuff拷贝到Tx_Buffer缓冲区。调用S_tx_process()
*			发送数据。
*******************************************************************************/
void Process_Data(char *buff)
{
	unsigned char switch_select=0;
	//delay_ms(10);
	switch_select=DataCMP(buff); 
	switch(switch_select)
	{
		case HELP_CMD:
			CMD_help(buff);
			break;
		case VERSION_CMD:
			CMD_version(buff);
			break;
		case SINGLET_CMD:
			CMD_Sgtrig(buff);
			TCP_Print("SingleTrig OK\r\n");
			break;
		case SYNCT_CMD:
			CMD_Synctrig(buff);
			TCP_Print("SYNCTrig OK\r\n");
			break;
		case AD8253_CMD:
			CMD_AD8253(buff);
			TCP_Print("Set AD8253 OK\r\n");
			break;
		case RELAY_CMD:
			CMD_Relay(buff);
			TCP_Print("Set relay OK\r\n");
			break;
		case CKIN_CMD:
			CMD_CKIN(buff);
			TCP_Print("Set CKIN OK\r\n");
			break;
		case SETIP_CMD:
			CMD_SETIP(buff);
			TCP_Print("Set IP OK,reseting......\r\n");
			__set_FAULTMASK(1); 
			NVIC_SystemReset(); 
			break;		
		default:TCP_Print("Command Error\r\n");break;
	}		
}

