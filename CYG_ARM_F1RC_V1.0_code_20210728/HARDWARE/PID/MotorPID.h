#ifndef _MOTORPID_H_
#define _MOTORPID_H_

typedef float uChar8;
typedef float uInt16;
typedef float uInt32;

typedef struct  PID_Value
{
	uInt32 liEkVal[3];          //��ֵ���棬�����ͷ����Ĳ�ֵ
	uChar8 uEkFlag[3];          //����λ��1��Ϊ��Ӧ�ĸ�����0Ϊ��Ӧ������ 
	uChar8 uKP_Coe;             //����ϵ��
	uChar8 uKI_Coe;             //���ֳ���
	uChar8 uKD_Coe;             //΢�ֳ���
	uInt16 iPriVal;             //��һʱ��ֵ
	uInt16 ierror;
	uInt16 integral;
	uInt16 ioutput;
	uInt16 iSetVal;             //�趨ֵ
	uInt16 iCurVal;             //ʵ��ֵ
	
}PID_ValueStr;

void PID_Init(void);
void PID_Operation(uInt16 SetTemp,uInt16 CurVal);
void PID_Output(void);
#endif
