#ifndef _MOTORPID_H_
#define _MOTORPID_H_

typedef float uChar8;
typedef float uInt16;
typedef float uInt32;

typedef struct  PID_Value
{
	uInt32 liEkVal[3];          //差值保存，给定和反馈的差值
	uChar8 uEkFlag[3];          //符号位，1则为对应的负数，0为对应的正数 
	uChar8 uKP_Coe;             //比例系数
	uChar8 uKI_Coe;             //积分常数
	uChar8 uKD_Coe;             //微分常数
	uInt16 iPriVal;             //上一时刻值
	uInt16 ierror;
	uInt16 integral;
	uInt16 ioutput;
	uInt16 iSetVal;             //设定值
	uInt16 iCurVal;             //实际值
	
}PID_ValueStr;

void PID_Init(void);
void PID_Operation(uInt16 SetTemp,uInt16 CurVal);
void PID_Output(void);
#endif
