#ifndef _CONFIG_H
#define _CONFIG_H

//Port B

#define PB0       GPIO_Pin_0
#define PB1				GPIO_Pin_1	 
#define PB2				GPIO_Pin_2	 
#define PB3				GPIO_Pin_3	
#define PB4				GPIO_Pin_4	
#define PB5				GPIO_Pin_5	
#define PB6				GPIO_Pin_6	
#define PB7       GPIO_Pin_7
#define PB8       GPIO_Pin_8
#define PB9       GPIO_Pin_9
#define PB10      GPIO_Pin_10
#define PB11      GPIO_Pin_11
#define PB12      GPIO_Pin_12
#define PB13      GPIO_Pin_13
#define PB14      GPIO_Pin_14
#define PB15      GPIO_Pin_15

#define BIT_00_ON     GPIO_SetBits(GPIOD,GPIO_Pin_0)
#define BIT_00_OFF    GPIO_ResetBits(GPIOD,GPIO_Pin_0)
#define BIT_01_ON     GPIO_SetBits(GPIOD,GPIO_Pin_1)
#define BIT_01_OFF    GPIO_ResetBits(GPIOD,GPIO_Pin_1)
#define BIT_02_ON     GPIO_SetBits(GPIOD,GPIO_Pin_2)
#define BIT_02_OFF    GPIO_ResetBits(GPIOD,GPIO_Pin_2)
#define BIT_03_ON     GPIO_SetBits(GPIOD,GPIO_Pin_3)
#define BIT_03_OFF    GPIO_ResetBits(GPIOD,GPIO_Pin_3)
#define BIT_04_ON     GPIO_SetBits(GPIOD,GPIO_Pin_4)
#define BIT_04_OFF    GPIO_ResetBits(GPIOD,GPIO_Pin_4)
#define BIT_05_ON     GPIO_SetBits(GPIOD,GPIO_Pin_5)
#define BIT_05_OFF    GPIO_ResetBits(GPIOD,GPIO_Pin_5)
#define BIT_06_ON     GPIO_SetBits(GPIOD,GPIO_Pin_6)
#define BIT_06_OFF    GPIO_ResetBits(GPIOD,GPIO_Pin_6)
#define BIT_07_ON     GPIO_SetBits(GPIOD,GPIO_Pin_7)
#define BIT_07_OFF    GPIO_ResetBits(GPIOD,GPIO_Pin_7)
#define BIT_08_ON     GPIO_SetBits(GPIOD,GPIO_Pin_8)
#define BIT_08_OFF    GPIO_ResetBits(GPIOD,GPIO_Pin_8)
#define BIT_09_ON     GPIO_SetBits(GPIOD,GPIO_Pin_9)
#define BIT_09_OFF    GPIO_ResetBits(GPIOD,GPIO_Pin_9)
#define BIT_10_ON     GPIO_SetBits(GPIOD,GPIO_Pin_10)
#define BIT_10_OFF    GPIO_ResetBits(GPIOD,GPIO_Pin_10)
#define BIT_11_ON     GPIO_SetBits(GPIOD,GPIO_Pin_11)
#define BIT_11_OFF    GPIO_ResetBits(GPIOD,GPIO_Pin_11)
#define BIT_12_ON     GPIO_SetBits(GPIOD,GPIO_Pin_12)
#define BIT_12_OFF    GPIO_ResetBits(GPIOD,GPIO_Pin_12)
#define BIT_13_ON     GPIO_SetBits(GPIOD,GPIO_Pin_13)
#define BIT_13_OFF    GPIO_ResetBits(GPIOD,GPIO_Pin_13)
#define BIT_14_ON     GPIO_SetBits(GPIOD,GPIO_Pin_14)
#define BIT_14_OFF    GPIO_ResetBits(GPIOD,GPIO_Pin_14)
#define BIT_15_ON     GPIO_SetBits(GPIOD,GPIO_Pin_15)
#define BIT_15_OFF    GPIO_ResetBits(GPIOD,GPIO_Pin_15)
#define BIT_16_ON     GPIO_SetBits(GPIOE,GPIO_Pin_0)
#define BIT_16_OFF    GPIO_ResetBits(GPIOE,GPIO_Pin_0)
#define BIT_17_ON     GPIO_SetBits(GPIOE,GPIO_Pin_1)
#define BIT_17_OFF    GPIO_ResetBits(GPIOE,GPIO_Pin_1)
#define BIT_18_ON     GPIO_SetBits(GPIOE,GPIO_Pin_2)
#define BIT_18_OFF    GPIO_ResetBits(GPIOE,GPIO_Pin_2)
#define BIT_19_ON     GPIO_SetBits(GPIOE,GPIO_Pin_3)
#define BIT_19_OFF    GPIO_ResetBits(GPIOE,GPIO_Pin_3)
#define BIT_20_ON     GPIO_SetBits(GPIOE,GPIO_Pin_4)
#define BIT_20_OFF    GPIO_ResetBits(GPIOE,GPIO_Pin_4)
#define BIT_21_ON     GPIO_SetBits(GPIOE,GPIO_Pin_5)
#define BIT_21_OFF    GPIO_ResetBits(GPIOE,GPIO_Pin_5)
#define BIT_22_ON     GPIO_SetBits(GPIOE,GPIO_Pin_6)
#define BIT_22_OFF    GPIO_ResetBits(GPIOE,GPIO_Pin_6)



// Port C
#define PC0       GPIO_Pin_0
#define PC1				GPIO_Pin_1	 
#define PC2				GPIO_Pin_2	
#define PC3				GPIO_Pin_3	 
#define PC4				GPIO_Pin_4	 
#define PC5				GPIO_Pin_5	
#define PC6				GPIO_Pin_6	
#define PC7       GPIO_Pin_7
#define PC8       GPIO_Pin_8
#define PC9       GPIO_Pin_9
#define PC10      GPIO_Pin_10
#define PC11      GPIO_Pin_11
#define PC12      GPIO_Pin_12
#define PC13      GPIO_Pin_13
#define PC14      GPIO_Pin_14
#define PC15      GPIO_Pin_15


// Port D
#define PD0       GPIO_Pin_0
#define PD1				GPIO_Pin_1	// 
#define PD2				GPIO_Pin_2	// 
#define PD3				GPIO_Pin_3	// 
#define PD4				GPIO_Pin_4	// 
#define PD5				GPIO_Pin_5	// 
#define PD6				GPIO_Pin_6	// 
#define PD7       GPIO_Pin_7
#define PD8				GPIO_Pin_8
#define PD9				GPIO_Pin_9
#define PD10			GPIO_Pin_10
#define PD11			GPIO_Pin_11
#define PD12			GPIO_Pin_12
#define PD13			GPIO_Pin_13
#define PD14			GPIO_Pin_14
#define PD15			GPIO_Pin_15

#define PI0				GPIO_Pin_0
#define PI1				GPIO_Pin_1
#define PI2				GPIO_Pin_2
#define PI3				GPIO_Pin_3
#define PI4				GPIO_Pin_4
#define PI5				GPIO_Pin_5
#define PI6				GPIO_Pin_6


#define Relay00        PD0
#define Relay01        PD1
#define Relay02        PD2
#define Relay03        PD3
#define Relay04        PD4
#define Relay05        PD5
#define Relay06        PD6
#define Relay07        PD7
#define Relay08        PD8
#define Relay09        PD9
#define Relay10        PD10
#define Relay11        PD11
#define Relay12        PD12
#define Relay13        PD13
#define Relay14        PD14
#define Relay15        PD15
#define Relay16        PE0
#define Relay17        PE1
#define Relay18        PE2
#define Relay19        PE3
#define Relay20        PE4
#define Relay21        PE5
#define Relay22        PE6


#define Relay14_ON     GPIO_SetBits(GPIOD,Relay14)
#define Relay14_OFF    GPIO_ResetBits(GPIOD,Relay14)
#define Relay15_ON     GPIO_SetBits(GPIOD,Relay15)
#define Relay15_OFF    GPIO_ResetBits(GPIOD,Relay15)
#define Relay16_ON     GPIO_SetBits(GPIOD,Relay16)
#define Relay16_OFF    GPIO_ResetBits(GPIOD,Relay16)
#define Relay17_ON     GPIO_SetBits(GPIOD,Relay17)
#define Relay17_OFF    GPIO_ResetBits(GPIOD,Relay17)
#define Relay18_ON     GPIO_SetBits(GPIOD,Relay18)
#define Relay18_OFF    GPIO_ResetBits(GPIOD,Relay18)
#define Relay19_ON     GPIO_SetBits(GPIOD,Relay19)
#define Relay19_OFF    GPIO_ResetBits(GPIOD,Relay19)

#define Relay20_ON     GPIO_SetBits(GPIOD,Relay20)
#define Relay20_OFF    GPIO_ResetBits(GPIOD,Relay20)
#define Relay21_ON     GPIO_SetBits(GPIOD,Relay21)
#define Relay21_OFF    GPIO_ResetBits(GPIOD,Relay21)
#define Relay22_ON     GPIO_SetBits(GPIOD,Relay22)
#define Relay22_OFF    GPIO_ResetBits(GPIOD,Relay22)
#define Relay23_ON     GPIO_SetBits(GPIOD,Relay23)
#define Relay23_OFF    GPIO_ResetBits(GPIOD,Relay23)
#define Relay24_ON     GPIO_SetBits(GPIOD,Relay24)
#define Relay24_OFF    GPIO_ResetBits(GPIOD,Relay24)
#define Relay25_ON     GPIO_SetBits(GPIOD,Relay25)
#define Relay25_OFF    GPIO_ResetBits(GPIOD,Relay25)

#define Relay26_ON     GPIO_SetBits(GPIOD,Relay26)
#define Relay26_OFF    GPIO_ResetBits(GPIOD,Relay26)
#define Relay27_ON     GPIO_SetBits(GPIOD,Relay27)
#define Relay27_OFF    GPIO_ResetBits(GPIOD,Relay27)
#define Relay28_ON     GPIO_SetBits(GPIOD,Relay28)
#define Relay28_OFF    GPIO_ResetBits(GPIOD,Relay28)
#define Relay29_ON     GPIO_SetBits(GPIOD,Relay29)
#define Relay29_OFF    GPIO_ResetBits(GPIOD,Relay29)




//ÏµÍ³µÆ
#define LED_RED_OFF		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_SET)
#define LED_RED_ON		GPIO_WriteBit(GPIOA, GPIO_Pin_4, Bit_RESET)  //SYS LED

#define ON                      1
#define OFF                     0


void GPIO_Config_Init(void);




#endif
