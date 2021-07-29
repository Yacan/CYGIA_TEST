#include "MotorPID.h"
#include "timer.h"

extern u16 PWMvalue;
extern float CurTemperature;

PID_ValueStr PID;               //PID结构体；
char g_bPIDRunFlag = 0;          //PID运行标志位，PID算法不是一直在运算，而是每隔一定时间算一次；
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
// function:PID算法                 
/ input:设定温度，当前温度;                  
// OUTPUT:NONE (but U(k))
// discriction:U(k)+KP*[E(k)-E(k-1)]+KI*E(k)+KD*[E(k)-2E(k-1)+E(k-2)]                                     
******************************************************** */

void PID_Operation(uInt16 SetTemp,uInt16 CurVal)
{
    uInt32 Temp[3] = {0};   //中间临时变量；
    uInt32 PostSum = 0;     //正数和；
	  PID.iSetVal=SetTemp;
		PID.iCurVal=CurVal;
//	if(PID.iSetVal - PID.iCurVal > 5)      //偏差大于5度(1k)?
//		//PID.iPriVal = 100;                 //偏差大于10为上限幅值输出（全速加热）
//	else                                   //否则慢慢加热；
//	{
			Temp[0] = PID.iSetVal - PID.iCurVal;    //偏差<=10,计算E(k)
			/*数值进行位移，注意顺序，否则会覆盖掉前面的数值*/
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

			/* =========计算KP*[E(k)-E(k-1)]的值========= */

					PostSum += Temp[0];                         //正数和；

			/* ========= 计算KI*E(k)计算 ========= */
  
					PostSum += Temp[1];                         //正数和；

			/* ========= 计算KD*[E(k-2)+E(k)-2E(k-1)]的值 ========= */
					PostSum += Temp[2];             //正数和；
					printf("CREMENT:%f\r\n",PostSum);

			/* ========= 计算U(k) ========= */                        
			PostSum += (uInt32)PID.iPriVal;       //上一时刻的值与叠加；   
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
// function:PID控制输出             
// input:NONE( 隐形输入 U(k) )                        
// output:无 (控制端)                                     
******************************************************** */

void PID_Output(void)
{
    static uInt16 iTemp;
	  PID_Operation(50,PID.iCurVal);    //每过0.1*10s调用一次PID运算；
    iTemp = PID.iPriVal;
	  printf("PWM:%f\r\n",iTemp);
	  PID.iCurVal=CurTemperature;  //实际温度
		TIM_SetCompare2(TIM3,iTemp);
   
		JsCurTemperature=CurTemperature;
		JsSetTemperature=50;
}

