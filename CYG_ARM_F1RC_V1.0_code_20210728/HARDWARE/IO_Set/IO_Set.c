#inclde <stdio.h>


/*******************************************************************************
* Function Name  : StrToHex
* Description    : �ַ���ת16������
* Input          : *hex		����ת����16�������ݵ�ָ��
									 *str		��Ҫת���ַ�����ָ��
									 *str		��Ҫת���ַ����ĳ���
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
* Description    : ��8λ����io��
* Input          : char Byte	8λIO״̬
									 char Addr	IO��ʼ��ַ
* Output         : 
* Return         : 
*******************************************************************************/
void Io_Set_Byte(char Byte,char Addr)
{
	char i=0;
	for(i=0;i<8;i++)
	
}

