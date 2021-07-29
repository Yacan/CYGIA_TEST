#ifndef __GPIO_H
#define __GPIO_H

#define AP_WR				GPIOB,GPIO_Pin_4
#define AP_A1				GPIOB,GPIO_Pin_2
#define AP_A0				GPIOB,GPIO_Pin_3
#define TRIGGER			GPIOB,GPIO_Pin_1
//#define CTRL_K				GPIOC,GPIO_Pin_9
#define HC_CE				GPIOD,GPIO_Pin_1
#define HC_MR				GPIOD,GPIO_Pin_2
#define SYNC				GPIOA,GPIO_Pin_15

#define AP_WR_SET(n)			(n?GPIO_SetBits(AP_WR):GPIO_ResetBits(AP_WR))
#define AP_A1_SET(n)			(n?GPIO_SetBits(AP_A1):GPIO_ResetBits(AP_A1))
#define AP_A0_SET(n)			(n?GPIO_SetBits(AP_A0):GPIO_ResetBits(AP_A0))
#define TRIGGER_SET(n)		(n?GPIO_SetBits(TRIGGER):GPIO_ResetBits(TRIGGER))
//#define CTRL_K_SET(n)			(n?GPIO_SetBits(CTRL_K):GPIO_ResetBits(CTRL_K))
#define HC_CE_SET(n)			(n?GPIO_SetBits(HC_CE):GPIO_ResetBits(HC_CE))
#define HC_MR_SET(n)			(n?GPIO_SetBits(HC_MR):GPIO_ResetBits(HC_MR))
#define SYNC_SET(n)				(n?GPIO_SetBits(SYNC):GPIO_ResetBits(SYNC))


#define CKIN(n)			(n?Cat9555_Output(I2C1_Bus,1,1):Cat9555_Output(I2C1_Bus,1,0))
#define RELAY0(n)		(n?Cat9555_Output(I2C1_Bus,2,1):Cat9555_Output(I2C1_Bus,2,0))
#define RELAY1(n)		(n?GPIO_SetBits(GPIOB,GPIO_Pin_5):GPIO_ResetBits(GPIOB,GPIO_Pin_5))
#define RELAY2(n)		(n?Cat9555_Output(I2C1_Bus,3,1):Cat9555_Output(I2C1_Bus,3,0))
#define RELAY3(n)		(n?Cat9555_Output(I2C1_Bus,4,1):Cat9555_Output(I2C1_Bus,4,0))
#define RELAY4(n)		(n?GPIO_SetBits(GPIOB,GPIO_Pin_8):GPIO_ResetBits(GPIOB,GPIO_Pin_8))
#define RELAY5(n)		(n?GPIO_SetBits(GPIOB,GPIO_Pin_9):GPIO_ResetBits(GPIOB,GPIO_Pin_9))
#define RELAY6(n)		(n?GPIO_SetBits(GPIOB,GPIO_Pin_10):GPIO_ResetBits(GPIOB,GPIO_Pin_10))
#define RELAY7(n)		(n?GPIO_SetBits(GPIOB,GPIO_Pin_11):GPIO_ResetBits(GPIOB,GPIO_Pin_11))
#define RELAY8(n)		(n?GPIO_SetBits(GPIOB,GPIO_Pin_12):GPIO_ResetBits(GPIOB,GPIO_Pin_12))
#define RELAY9(n)		(n?GPIO_SetBits(GPIOB,GPIO_Pin_13):GPIO_ResetBits(GPIOB,GPIO_Pin_13))
#define RELAY10(n)		(n?GPIO_SetBits(GPIOB,GPIO_Pin_14):GPIO_ResetBits(GPIOB,GPIO_Pin_14))
#define RELAY11(n)		(n?GPIO_SetBits(GPIOB,GPIO_Pin_15):GPIO_ResetBits(GPIOB,GPIO_Pin_15))
#define RELAY12(n)		(n?GPIO_SetBits(GPIOA,GPIO_Pin_0):GPIO_ResetBits(GPIOA,GPIO_Pin_0))
#define RELAY13(n)		(n?GPIO_SetBits(GPIOA,GPIO_Pin_1):GPIO_ResetBits(GPIOA,GPIO_Pin_1))
#define RELAY14(n)		(n?GPIO_SetBits(GPIOA,GPIO_Pin_11):GPIO_ResetBits(GPIOA,GPIO_Pin_11))
#define RELAY15(n)		(n?GPIO_SetBits(GPIOA,GPIO_Pin_12):GPIO_ResetBits(GPIOA,GPIO_Pin_12))
#define RELAY16(n)		(n?GPIO_SetBits(GPIOC,GPIO_Pin_0):GPIO_ResetBits(GPIOC,GPIO_Pin_0))
#define RELAY17(n)		(n?GPIO_SetBits(GPIOC,GPIO_Pin_1):GPIO_ResetBits(GPIOC,GPIO_Pin_1))
#define RELAY18(n)		(n?GPIO_SetBits(GPIOC,GPIO_Pin_2):GPIO_ResetBits(GPIOC,GPIO_Pin_2))
#define RELAY19(n)		(n?GPIO_SetBits(GPIOC,GPIO_Pin_3):GPIO_ResetBits(GPIOC,GPIO_Pin_3))
#define RELAY20(n)		(n?GPIO_SetBits(GPIOC,GPIO_Pin_4):GPIO_ResetBits(GPIOC,GPIO_Pin_4))
#define RELAY21(n)		(n?GPIO_SetBits(GPIOC,GPIO_Pin_5):GPIO_ResetBits(GPIOC,GPIO_Pin_5))
#define RELAY22(n)		(n?GPIO_SetBits(GPIOC,GPIO_Pin_6):GPIO_ResetBits(GPIOC,GPIO_Pin_6))
#define RELAY23(n)		(n?GPIO_SetBits(GPIOC,GPIO_Pin_7):GPIO_ResetBits(GPIOC,GPIO_Pin_7))
#define RELAY24(n)		(n?GPIO_SetBits(GPIOC,GPIO_Pin_8):GPIO_ResetBits(GPIOC,GPIO_Pin_8))
#define RELAY25(n)		(n?GPIO_SetBits(GPIOC,GPIO_Pin_9):GPIO_ResetBits(GPIOC,GPIO_Pin_9))
#define RELAY26(n)		(n?GPIO_SetBits(GPIOC,GPIO_Pin_10):GPIO_ResetBits(GPIOC,GPIO_Pin_10))
#define RELAY27(n)		(n?GPIO_SetBits(GPIOC,GPIO_Pin_11):GPIO_ResetBits(GPIOC,GPIO_Pin_11))
#define RELAY28(n)		(n?GPIO_SetBits(GPIOC,GPIO_Pin_12):GPIO_ResetBits(GPIOC,GPIO_Pin_12))
#define RELAY29(n)		(n?GPIO_SetBits(GPIOC,GPIO_Pin_13):GPIO_ResetBits(GPIOC,GPIO_Pin_13))
#define RELAY30(n)		(n?GPIO_SetBits(GPIOC,GPIO_Pin_14):GPIO_ResetBits(GPIOC,GPIO_Pin_14))
#define RELAY31(n)		(n?GPIO_SetBits(GPIOC,GPIO_Pin_15):GPIO_ResetBits(GPIOC,GPIO_Pin_15))




void Gpio_int(void);
void PA10_Control(char type);
void PA9_Control(char type);
void Gain_set(char num);
void EXTI_Config(void);
void Relay_io_int(void);
void Relay_test(unsigned char flag);


#endif
