/*----------------------------------------------------------------------------
 * Name:    App_cmd.h
 *----------------------------------------------------------------------------*/
    
#ifndef __APP_CMD_H
#define __APP_CMD_H

#define Interface_Debug_Board	 1
/* Private define ------------------------------------------------------------*/
extern char RXbuff[];

unsigned char string_compare_len(const unsigned char *String1,unsigned char *String2,unsigned char LEN);
unsigned char string_compare(const unsigned char *String1, unsigned char *String2);
unsigned char  DataCMP(void);

void Read_voltage(void);
void Process_Data(void);

void Reset(void);
unsigned char PIN_TEST(void);
#endif /* __APP_CMD_H */

/******************* (C) COPYRIGHT 2014 Intelligentgroup   *****END OF FILE****/
