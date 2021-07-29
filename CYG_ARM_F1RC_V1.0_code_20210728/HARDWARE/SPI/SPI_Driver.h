#ifndef	 	__MY__IIC__H_
#define		__MY__IIC__H_
#include <stdint.h>

#define SPI_1


#ifdef STDLib
#include "stm32f10x_gpio.h"
#include "stm32f10x_spi.h"
#endif

#ifdef SPI_1
void SPI1_Init(void);
//uint8_t SPI1_Write(uint8_t ch,uint8_t *TxData,uint8_t len);
//uint8_t SPI1_Read(int8_t ch,uint8_t *RxData,uint8_t len);
//uint8_t SPI1_WriteRead(int8_t ch,uint8_t *TxData,uint8_t *RxData,uint8_t len);
uint8_t SPI1_Write_Reg(uint8_t ch,uint8_t *reg,uint8_t *TxData,uint8_t reg_len,uint8_t Tx_len);
uint8_t SPI1_WriteRead_T2R(int8_t ch,uint8_t *TxData,uint8_t *RxData,uint8_t Tx_Len,uint8_t Rx_Len);

#endif


#endif 
