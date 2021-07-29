#inclde <stdio.h>


/*******************************************************************************
* Function Name  : StrToHex
* Description    : 字符串转16进制数
* Input          : *hex		保存转换后16进制数据的指针
									 *str		需要转换字符串的指针
									 *str		需要转换字符串的长度
* Output         : 
* Return         : 
*******************************************************************************/
void StrToHex(char *hex,char *str,char len)
{
	uint8_t num = 0,i,j;
	
	len = len/2;
	
	for(i=0;i<len;i++) 
	{
		num << 4;
		for(j=0;j<2;j++)
		{
			num = num<< 4;
			if(*str<='9')
				num += *str-0x30;
			else num += *str-0x37;
			str++;
		}
		printf("output:%#x\r\n",num);
		*hex = num;
		hex++;
	}	
}
/*******************************************************************************
* Function Name  : Io_Set_Byte
* Description    : 按8位设置io口
* Input          : char Byte	8位IO状态
									 char Addr	IO起始地址
* Output         : 
* Return         : 
*******************************************************************************/
void Io_Set_Byte(char Byte,char Addr)
{
	char i=0;
	for(i=0;i<8;i++)
	
}

