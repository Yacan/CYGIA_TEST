#include "MotorPID.h"
#include "timer.h"

extern u16 PWMvalue;
extern float CurTemperature;

PID_ValueStr PID;               //PID�ṹ�壻
char g_bPIDRunFlag = 0;          //PID���б�־λ��PID�㷨����һֱ�����㣬����ÿ��һ��ʱ����һ�Σ�
u16 JsCurTemperature=0.0;
u16 JsSetTemperature=0.0;

void PID_Init(void)
{
	PID.iSetVal=50;
	PID.uKD_Coe=0.1;
	PID.uKI_Coe=0.3;
	PID.uKP_Coe=3;
}

/* ********************************************************
// name:PID_Operation()                                 
// function:PID�㷨                 
/ input:�趨�¶ȣ���ǰ�¶�;                  
// OUTPUT:NONE (but U(k))
// discriction:U(k)+KP*[E(k)-E(k-1)]+KI*E(k)+KD*[E(k)-2E(k-1)+E(k-2)]                                     
******************************************************** */

void PID_Operation(uInt16 SetTemp,uInt16 CurVal)
{
    uInt32 Temp[3] = {0};   //�м���ʱ������
    uInt32 PostSum = 0;     //�����ͣ�
	  PID.iSetVal=SetTemp;
		PID.iCurVal=CurVal;
//	if(PID.iSetVal - PID.iCurVal > 5)      //ƫ�����5��(1k)?
//		//PID.iPriVal = 100;                 //ƫ�����10Ϊ���޷�ֵ�����ȫ�ټ��ȣ�
//	else                                   //�����������ȣ�
//	{
			Temp[0] = PID.iSetVal - PID.iCurVal;    //ƫ��<=10,����E(k)
			/*��ֵ����λ�ƣ�ע��˳�򣬷���Ḳ�ǵ�ǰ�����ֵ*/
			PID.liEkVal[2] = PID.liEkVal[1];
			PID.liEkVal[1] = PID.liEkVal[0];
			PID.liEkVal[0] = Temp[0];
			/* =================================================================== */
					Temp[0] = PID.liEkVal[0] - PID.liEkVal[1];         //E(k)-E(k-1)                                                         
			/* =================================================================== */
			Temp[2] = PID.liEkVal[1] * 2;                          //2E(k-1)
			Temp[2] = (PID.liEkVal[0] + PID.liEkVal[2]) - Temp[2]; //E(k-2)+E(k)-2E(k-1)                                                                              

			/* =================================================================== */
			Temp[0] = (uInt32)PID.uKP_Coe * Temp[0];        //KP*[E(k)-E(k-1)]
			Temp[1] = (uInt32)PID.uKI_Coe * PID.liEkVal[0]; //KI*E(k)
			Temp[2] = (uInt32)PID.uKD_Coe * Temp[2];        //KD*[E(k-2)+E(k)-2E(k-1)]

			/* =========����KP*[E(k)-E(k-1)]��ֵ========= */

					PostSum += Temp[0];                         //�����ͣ�

			/* ========= ����KI*E(k)���� ========= */
  
					PostSum += Temp[1];                         //�����ͣ�

			/* ========= ����KD*[E(k-2)+E(k)-2E(k-1)]��ֵ ========= */
					PostSum += Temp[2];             //�����ͣ�
					printf("CREMENT:%f\r\n",PostSum);

			/* ========= ����U(k) ========= */                        
			PostSum += (uInt32)PID.iPriVal;       //��һʱ�̵�ֵ����ӣ�   
      PID.iPriVal=PostSum;

//   }
	if(PID.iPriVal>1000)
	{
		PID.iPriVal=1000;
	}
	if(PID.iPriVal<10)
	{
		PID.iPriVal=10;
	}
//	 PID.iSetVal=SetTemp;
//	 PID.iCurVal=CurVal;
//	 PID.ierror=PID.iSetVal-PID.iCurVal;
//	 PID.integral+=PID.ierror;
//	 PID.ioutput=PID.uKP_Coe*PID.ierror+PID.uKI_Coe*PID.integral+PID.uKD_Coe*(PID.ierror-PID.iPriVal);
//	 PID.iPriVal=PID.ierror;

}


/* ********************************************************
// name:PID_Output()                                    
// function:PID�������             
// input:NONE( �������� U(k) )                        
// output:�� (���ƶ�)                                     
******************************************************** */

void PID_Output(void)
{
    static uInt16 iTemp;
	  PID_Operation(50,PID.iCurVal);    //ÿ��0.1*10s����һ��PID���㣻
    iTemp = PID.iPriVal;
	  printf("PWM:%f\r\n",iTemp);
	  PID.iCurVal=CurTemperature;  //ʵ���¶�
		TIM_SetCompare2(TIM3,iTemp);
   
		JsCurTemperature=CurTemperature;
		JsSetTemperature=50;
}

