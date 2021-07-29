/**
******************************************************************************
* @file    			w5500_conf.c                                                                                              
* @version 			V1.2										  		
* @date    			2017-11-01								 
* @brief 				��3.5.0�汾�⽨�Ĺ���ģ��						  	
* @attention		����MCU����ֲw5500������Ҫ�޸ĵ��ļ�������w5500��MAC��IP��ַ 	
*				
* @company  		��������Ƽ����޹�˾
* @information  WIZnet W5500�ٷ������̣�ȫ�̼���֧�֣��۸�������ƣ�
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


CONFIG_MSG  ConfigMsg;																	/*���ýṹ��*/
EEPROM_MSG_STR EEPROM_MSG;															/*EEPROM�洢��Ϣ�ṹ��*/

/*MAC��ַ���ֽڱ���Ϊż��*/
/*������W5500�����������ͬһ�ֳ���������ʹ�ò�ͬ��MAC��ַ*/
uint8 mac[6]={0x00,0x08,0xdc,0x11,0x11,0x11};

/*����Ĭ��IP��Ϣ*/
uint8 local_ip[4]={192,168,2,31};												/*����W5500Ĭ��IP��ַ*/
uint8 subnet[4]={255,255,255,0};												/*����W5500Ĭ����������*/
uint8 gateway[4]={192,168,2,1};													/*����W5500Ĭ������*/
uint8 dns_server[4]={114,114,114,114};									/*����W5500Ĭ��DNS*/

uint16 local_port=7600;	                    						/*���屾�ض˿�*/

/*����Զ��IP��Ϣ*/
uint8  remote_ip[4]={192,168,2,10};										/*Զ��IP��ַ*/
uint16 remote_port=8080;																/*Զ�˶˿ں�*/

/*IP���÷���ѡ��������ѡ��*/
uint8  ip_from=IP_FROM_DEFINE;				

uint8  dhcp_ok=0;																				/*dhcp�ɹ���ȡIP*/
uint32 ms=0;																						/*�������*/
uint32 dhcp_time= 0;																		/*DHCP���м���*/
vu8    ntptimer = 0;																		/*NPT�����*/


/*******************Lower API**************************/
/**
*@brief		��flash�ж�ȡip��Ϣ
*@param		
*@return	��
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
*@brief		STM32 SPI1��д8λ����
*@param		dat��д���8λ����
*@return	��
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
*@brief		W5500��λ���ú���
*@param		��
*@return	��
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
*@brief		����W5500��IP��ַ
*@param		��
*@return	��
*/
void set_w5500_ip(void)
{	
		
  /*���ƶ����������Ϣ�����ýṹ��*/
	memcpy(ConfigMsg.mac, mac, 6);
	memcpy(ConfigMsg.lip,local_ip,4);
	memcpy(ConfigMsg.sub,subnet,4);
	memcpy(ConfigMsg.gw,gateway,4);
	memcpy(ConfigMsg.dns,dns_server,4);
	
	W5500_Debug(" ʹ�ö����IP��Ϣ����W5500:\r\n");	
	/*����������Ϣ��������Ҫѡ��*/	
	ConfigMsg.sw_ver[0]=FW_VER_HIGH;
	ConfigMsg.sw_ver[1]=FW_VER_LOW;	

	/*��IP������Ϣд��W5500��Ӧ�Ĵ���*/	
	setSUBR(ConfigMsg.sub);
	setGAR(ConfigMsg.gw);
	setSIPR(ConfigMsg.lip);
	
	getSIPR (local_ip);			
	W5500_Debug(" W5500 IP��ַ   : %d.%d.%d.%d\r\n", local_ip[0],local_ip[1],local_ip[2],local_ip[3]);
	getSUBR(subnet);
	W5500_Debug(" W5500 �������� : %d.%d.%d.%d\r\n", subnet[0],subnet[1],subnet[2],subnet[3]);
	getGAR(gateway);
	W5500_Debug(" W5500 ����     : %d.%d.%d.%d\r\n", gateway[0],gateway[1],gateway[2],gateway[3]);
	W5500_Debug(" W5500 �˿�     : %d\r\n", local_port);
}

/**
*@brief		����W5500��MAC��ַ
*@param		��
*@return	��
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


uint8 buff[2048];				                              	        /*����һ��2KB�Ļ���*/
uint8_t gSocketNum=0;
/**
*@brief		TCP Server�ػ���ʾ������
*@param		��
*@return	��
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
	switch(getSn_SR(gSocketNum))											            	/*��ȡsocket��״̬*/
	{
		case SOCK_CLOSED:													                  /*socket���ڹر�״̬*/
			socket(gSocketNum ,Sn_MR_TCP,local_port,Sn_MR_ND);	        /*��socket*/
			break;     
		
		case SOCK_INIT:														                  /*socket�ѳ�ʼ��״̬*/
			listen(gSocketNum);												                /*socket��������*/
			break;
		
		case SOCK_ESTABLISHED:												              /*socket�������ӽ���״̬*/
			if(getSn_IR(gSocketNum) & Sn_IR_CON)
			{
//				if(gSocketNum==0)
//					close(1);
//				else
//					close(0);
				setSn_IR(gSocketNum, Sn_IR_CON);								          /*��������жϱ�־λ*/
			}
			len=getSn_RX_RSR(gSocketNum);									            /*����lenΪ�ѽ������ݵĳ���*/
			if(len>0)
			{
				recv(gSocketNum,buff,len);								              	/*��������Client������*/
				buff[len]=0x00; 											                  /*����ַ���������*/
				W5500_Debug("%s",buff);
//				memcpy(RXbuff, buff, len+1);	
				Process_Data(buff);
//				for(i=0;i<len;i++)
//				{
//					RXbuff[i]='\0';
//				}
				// send(gSocketNum,buff,len);									              /*��Client��������*/
			}
			break;
		
		case SOCK_CLOSE_WAIT:												                /*socket���ڵȴ��ر�״̬*/
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
