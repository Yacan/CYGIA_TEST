/**
******************************************************************************
* @file    			w5500_conf.c                                                                                              
* @version 			V1.2										  		
* @date    			2017-11-01								 
* @brief 				用3.5.0版本库建的工程模板						  	
* @attention		配置MCU，移植w5500程序需要修改的文件，配置w5500的MAC和IP地址 	
*				
* @company  		深圳炜世科技有限公司
* @information  WIZnet W5500官方代理商，全程技术支持，价格绝对优势！
* @website  		www.wisioe.com																							 	 				
* @forum        www.w5500.cn																								 		
* @qqGroup      383035001																										 
******************************************************************************
*/

#include <stdio.h> 
#include <string.h>
#include "w5500_conf.h"
#include "w5500.h"
#include "socket.h"
#include "SPI_Driver.h"
#include "gpio.h"
#include "Delay.h"
#include "mycmd.h"
#include "My_Flash.h"


CONFIG_MSG  ConfigMsg;																	/*配置结构体*/
EEPROM_MSG_STR EEPROM_MSG;															/*EEPROM存储信息结构体*/

/*MAC地址首字节必须为偶数*/
/*如果多块W5500网络适配板在同一现场工作，请使用不同的MAC地址*/
uint8 mac[6]={0x00,0x08,0xdc,0x11,0x11,0x11};

/*定义默认IP信息*/
uint8 local_ip[4]={192,168,2,31};												/*定义W5500默认IP地址*/
uint8 subnet[4]={255,255,255,0};												/*定义W5500默认子网掩码*/
uint8 gateway[4]={192,168,2,1};													/*定义W5500默认网关*/
uint8 dns_server[4]={114,114,114,114};									/*定义W5500默认DNS*/

uint16 local_port=7600;	                    						/*定义本地端口*/

/*定义远端IP信息*/
uint8  remote_ip[4]={192,168,2,10};										/*远端IP地址*/
uint16 remote_port=8080;																/*远端端口号*/

/*IP配置方法选择，请自行选择*/
uint8  ip_from=IP_FROM_DEFINE;				

uint8  dhcp_ok=0;																				/*dhcp成功获取IP*/
uint32 ms=0;																						/*毫秒计数*/
uint32 dhcp_time= 0;																		/*DHCP运行计数*/
vu8    ntptimer = 0;																		/*NPT秒计数*/


/*******************Lower API**************************/
/**
*@brief		从flash中读取ip信息
*@param		
*@return	无
*/
void IP_Init()
{
	uint16_t IP_buff[2] = {0};

	STMFLASH_Read(IP_Address,IP_buff,2);
	if(IP_buff[0]>>8 != 192)	return;
	local_ip[0] = IP_buff[0]>>8;
	local_ip[1] = IP_buff[0];
	local_ip[2] = IP_buff[1]>>8;
	local_ip[3] = IP_buff[1];
//	printf("set ip:%d.%d.%d.%d\r\n",local_ip[0],local_ip[1],local_ip[2],local_ip[3]);
//	local_ip[0] = 192;
//	local_ip[1] = 168;
//	local_ip[2] = 2;
//	local_ip[3] = 31;
}
/*******************Lower API**************************/
/**
*@brief		STM32 SPI1读写8位数据
*@param		dat：写入的8位数据
*@return	无
*/
uint8  W5500_SPI_Write(uint32 reg,uint8 *data ,uint16 len)
{
	uint8_t ret;
	uint8 reg_buf[3];
	reg_buf[0]=(reg & 0x00FF0000)>>16;
	reg_buf[1]=(reg & 0x0000FF00)>>8;
	reg_buf[2]=(reg & 0x000000F8)+4;
	ret=SPI1_Write_Reg(1,reg_buf,data,3,len);
	return ret;
}
uint8 W5500_SPI_Read(uint32 reg,uint8 *data ,uint16 len )
{
	uint8_t ret;
	uint8 reg_buf[3];
	reg_buf[0]=(reg & 0x00FF0000)>>16;
	reg_buf[1]=(reg & 0x0000FF00)>>8;
	reg_buf[2]=(reg & 0x000000F8);
	ret=SPI1_WriteRead_T2R(1,reg_buf,data,3,len);
	return ret;
}
// void wiz_cs(uint8_t val)
// {
// 	if (val == LOW) 
// 	{
// 		GPIO_ResetBits(GPIOA, GPIO_Pin_4); 
// 	}
// 	else if (val == HIGH)
// 	{
// 		GPIO_SetBits(GPIOA, GPIO_Pin_4); 
// 	}
// }
void W5500_Delay(uint16_t num)
{
	delay_ms(num);
}
/**
*@brief		W5500复位设置函数
*@param		无
*@return	无
*/
void reset_w5500(void)
{
	PA10_Control(0);
	W5500_Delay(2);  
	PA10_Control(1);
	W5500_Delay(1600);	

}
/*************************Internal Function***************************/
/**
*@brief		配置W5500的IP地址
*@param		无
*@return	无
*/
void set_w5500_ip(void)
{	
		
  /*复制定义的配置信息到配置结构体*/
	memcpy(ConfigMsg.mac, mac, 6);
	memcpy(ConfigMsg.lip,local_ip,4);
	memcpy(ConfigMsg.sub,subnet,4);
	memcpy(ConfigMsg.gw,gateway,4);
	memcpy(ConfigMsg.dns,dns_server,4);
	
	W5500_Debug(" 使用定义的IP信息配置W5500:\r\n");	
	/*以下配置信息，根据需要选用*/	
	ConfigMsg.sw_ver[0]=FW_VER_HIGH;
	ConfigMsg.sw_ver[1]=FW_VER_LOW;	

	/*将IP配置信息写入W5500相应寄存器*/	
	setSUBR(ConfigMsg.sub);
	setGAR(ConfigMsg.gw);
	setSIPR(ConfigMsg.lip);
	
	getSIPR (local_ip);			
	W5500_Debug(" W5500 IP地址   : %d.%d.%d.%d\r\n", local_ip[0],local_ip[1],local_ip[2],local_ip[3]);
	getSUBR(subnet);
	W5500_Debug(" W5500 子网掩码 : %d.%d.%d.%d\r\n", subnet[0],subnet[1],subnet[2],subnet[3]);
	getGAR(gateway);
	W5500_Debug(" W5500 网关     : %d.%d.%d.%d\r\n", gateway[0],gateway[1],gateway[2],gateway[3]);
	W5500_Debug(" W5500 端口     : %d\r\n", local_port);
}

/**
*@brief		配置W5500的MAC地址
*@param		无
*@return	无
*/
void set_w5500_mac(void)
{
	memcpy(ConfigMsg.mac, mac, 6);
	setSHAR(ConfigMsg.mac);	/**/
//	memcpy(DHCP_GET.mac, mac, 6);
}

void W5500_Socket_WriteByte(uint32 reg,uint8 data)
{
	W5500_SPI_Write(reg,&data,1);
}
uint8 W5500_Socket_ReadByte(uint32 reg)
{
	uint8 ret;
	W5500_SPI_Read(reg,&ret,1);
	return ret;
}


/*******************User API********************/


uint8 buff[2048];				                              	        /*定义一个2KB的缓存*/
uint8_t gSocketNum=0;
/**
*@brief		TCP Server回环演示函数。
*@param		无
*@return	无
*/
uint8 W5500_Tcp_Send(uint8 *buff,uint8 len)
{
	uint8 ret;
	ret=send(gSocketNum,buff,len);
	return ret;
}
void do_tcp_server(void)
{	
	uint16 i;
	uint16 len=0;  
	switch(getSn_SR(gSocketNum))											            	/*获取socket的状态*/
	{
		case SOCK_CLOSED:													                  /*socket处于关闭状态*/
			socket(gSocketNum ,Sn_MR_TCP,local_port,Sn_MR_ND);	        /*打开socket*/
			break;     
		
		case SOCK_INIT:														                  /*socket已初始化状态*/
			listen(gSocketNum);												                /*socket建立监听*/
			break;
		
		case SOCK_ESTABLISHED:												              /*socket处于连接建立状态*/
			if(getSn_IR(gSocketNum) & Sn_IR_CON)
			{
//				if(gSocketNum==0)
//					close(1);
//				else
//					close(0);
				setSn_IR(gSocketNum, Sn_IR_CON);								          /*清除接收中断标志位*/
			}
			len=getSn_RX_RSR(gSocketNum);									            /*定义len为已接收数据的长度*/
			if(len>0)
			{
				recv(gSocketNum,buff,len);								              	/*接收来自Client的数据*/
				buff[len]=0x00; 											                  /*添加字符串结束符*/
				W5500_Debug("%s",buff);
//				memcpy(RXbuff, buff, len+1);	
				Process_Data(buff);
//				for(i=0;i<len;i++)
//				{
//					RXbuff[i]='\0';
//				}
				// send(gSocketNum,buff,len);									              /*向Client发送数据*/
			}
			break;
		
		case SOCK_CLOSE_WAIT:												                /*socket处于等待关闭状态*/
			close(gSocketNum);
			break;
	}
		if(gSocketNum < 7)
			gSocketNum++;
		else
			gSocketNum = 0;
//	if(gSocketNum ==0)
//		gSocketNum=1;
//	else
//		gSocketNum = 0;
}
