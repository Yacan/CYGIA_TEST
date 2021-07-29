#ifndef _W5500_CONF_H_
#define _W5500_CONF_H_

#include "stm32f10x.h"
#include "stdio.h"
#include "types.h"
#define __GNUC__

typedef  void (*pFunction)(void);

extern uint8  	remote_ip[4];															 /*远端IP地址*/
extern uint16 	remote_port;															 /*远端端口号*/
extern uint16		local_port;																 /*定义本地端口*/
extern uint8  	use_dhcp;																	 /*是否使用DHCP获取IP*/
extern uint8  	use_eeprom;																 /*是否使用EEPROM中的IP配置信息*/

#define W5500_Debug_Define

#ifdef W5500_Debug_Define
#define W5500_Debug(...) printf(__VA_ARGS__)
#else
#define W5500_Debug(...)
#endif



#define FW_VER_HIGH  						1               
#define FW_VER_LOW    					0
#define ON	                 		1
#define OFF	                 		0
#define HIGH	           	 			1
#define LOW		             			0

#define MAX_BUF_SIZE		 				1460											 /*定义每个数据包的大小*/
#define KEEP_ALIVE_TIME	     		30	                       /*30sec*/
#define TX_RX_MAX_BUF_SIZE      2048							 
#define EEPROM_MSG_LEN        	sizeof(EEPROM_MSG)

#define IP_FROM_DEFINE	        0                          /*使用初始定义的IP信息*/
#define IP_FROM_DHCP	          1                          /*使用DHCP获取IP信息*/
#define IP_FROM_EEPROM	        2							             /*使用EEPROM定义的IP信息*/
extern uint8	ip_from;											               /*选择IP信息配置源*/
#pragma pack(1)
/*此结构体定义了W5500可供配置的主要参数*/
typedef struct _CONFIG_MSG											
{
  uint8 mac[6];																						 /*MAC地址*/
  uint8 lip[4];																						 /*local IP本地IP地址*/
  uint8 sub[4];																						 /*子网掩码*/
  uint8 gw[4];																						 /*网关*/	
  uint8 dns[4];																						 /*DNS服务器地址*/
  uint8 rip[4];																						 /*remote IP远程IP地址*/
	uint8 sw_ver[2];																				 /*软件版本号*/
}CONFIG_MSG;
#pragma pack()

#pragma pack(1)
/*此结构体定义了eeprom写入的几个变量，可按需修改*/
typedef struct _EEPROM_MSG	                    
{
	uint8 mac[6];																							/*MAC地址*/
  uint8 lip[4];																							/*local IP本地IP地址*/
  uint8 sub[4];																							/*子网掩码*/
  uint8 gw[4];																							/*网关*/
}EEPROM_MSG_STR;
#pragma pack()

extern EEPROM_MSG_STR EEPROM_MSG;
extern CONFIG_MSG  	ConfigMsg;
extern uint8 dhcp_ok;																				/*DHCP获取成功*/
extern uint32	dhcp_time;																		/*DHCP运行计数*/
extern vu8	ntptimer;																				/*NPT秒计数*/

/*MCU配置相关函数*/
void reboot(void);																					/*STM32软复位*/

/*W5500SPI相关函数*/
//void IINCHIP_WRITE( uint32 addrbsb,  uint8 data);						/*写入一个8位数据到W5500*/
//uint8 IINCHIP_READ(uint32 addrbsb);													/*从W5500读出一个8位数据*/
//uint16 wiz_write_buf(uint32 addrbsb,uint8* buf,uint16 len);	/*向W5500写入len字节数据*/
//uint16 wiz_read_buf(uint32 addrbsb, uint8* buf,uint16 len);	/*从W5500读出len字节数据*/
uint8  W5500_SPI_Write(uint32 reg,uint8 *data ,uint16 len);
uint8 W5500_SPI_Read(uint32 reg,uint8 *data ,uint16 len );

void W5500_Socket_WriteByte(uint32 reg,uint8 data);
uint8 W5500_Socket_ReadByte(uint32 reg);

void W5500_Delay(uint16_t num);

/*W5500基本配置相关函数*/
void reset_w5500(void);																			/*硬复位W5500*/
void set_w5500_mac(void);																		/*配置W5500的MAC地址*/
void set_w5500_ip(void);																		/*配置W5500的IP地址*/

/*需要用定时的的应用函数*/
void dhcp_timer_init(void);																	/*dhcp用到的定时器初始化*/
void ntp_timer_init(void);																	/*npt用到的定时器初始化*/

extern uint16 W5500_tcp_server_port;
void do_tcp_server(void);//TCP Server回环演示函数
uint8 W5500_Tcp_Send(uint8 *buff,uint8 len);
void IP_Init(void);

extern uint8_t gSocketNum;

#endif
