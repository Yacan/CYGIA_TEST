#ifndef __CAT9555__H
#define __CAT9555__H
#include "sys.h"

enum dtbIo {
	MCU_Control1=1,
	MCU_Control2,
	TEC0_Slp,
	DMM_1,
	DMM_0,
	DMM_SEL,
	MCU_Fault,
	MCU_SNS,
	DMM_2,
};

uint8_t Cat9555_Config(u8 IICBus,uint8_t ICx,uint8_t *configdata);//ICx is 1 to 8
uint8_t Cat9555_Output(u8 IICBus,uint8_t ch,uint8_t value);//control each IO; ch1 to ch128
uint8_t Cat9555_Input(u8 IICBus,uint8_t ch,uint8_t *value);
void CAT9555_Init(u8 IICBus);
uint8_t Cat9555_Set_IO_State(u8 IICBus,uint8_t ICx,uint8_t *data);//ICx is 1 to 8
#endif
