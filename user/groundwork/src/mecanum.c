//麦轮底盘算法，两种模式：1.以底盘自身的正方向为真正方向 2.以云台指向为真正方向。模式选择用遥控器开关控制
#include "math.h"

#include "data_stream.h"

#include "mecanum.h"

#define MAX_SPEED 2000
#define DegreeToRadian  3.1415926535898 / 180.0
#define y 1
#define x 0

int Flag_UsingMpu = 0;
volatile int test = 0;

float RealAngle = 0;
float Float_StartSpinAngle = 0;
float Float_NowAngle = 0;
float Real_forward_X,Real_forward_Y,Real_Right_X,Real_Right_Y;

float aimSpeed[4] = {0,};
volatile float pointRightX,pointRightY,pointLeftX,pointLeftY;
volatile float lim_pointRightX, lim_pointRightY;

void get_aimSpeed(void)
{
	
	//Car start
    //ID:                            1, 2, 3, 4 
    const int forward_back[4]    = { 1, 1,-1,-1};
    const int right_left[4]      = { 1,-1,-1, 1};
	const int turn_right_left[4] = { 1, 1, 1, 1};
    
    int16_t leftX  = Data_RC.rc.ch2 - 1024;
    int16_t rightY = Data_RC.rc.ch1 - 1024;
    int16_t rightX = Data_RC.rc.ch0 - 1024;
	int16_t leftY  = Data_RC.rc.ch3 - 1024;//to -660~660 //暂时用不到该变量

    pointRightX = (float)rightX/(float)660 ;
	pointRightY = (float)rightY/(float)660;
	pointLeftX = (float)leftX / (float)660;
	//float pointleftY = (float)660 / (float)leftY;
		
	//rect to cycle
	lim_pointRightX = pow(pointRightX,2)*(1 - pow(pointRightY,2)/2) ;
	lim_pointRightY = pow(pointRightY,2)*(1 - pow(pointRightX,2)/2) ;
	
	if(!Flag_UsingMpu)
	{
		//不自转情况下的控制
		for(int i = 0;i < 4;i++)
		{
			float coefficients = forward_back[i] * sqrt(lim_pointRightY) * (pointRightY > 0? 1 : -1) + right_left[i] * sqrt(lim_pointRightX) * (pointRightX > 0? 1 : -1)
				+ turn_right_left[i] * pointLeftX;
			aimSpeed[i] = MAX_SPEED * coefficients;
		}	
	}
	else
	{
		float Real_Angle = Data_m6020[0].moto_angle;
		
		float Vector2_realForward[2] = {sinf(DegreeToRadian * Real_Angle),cosf(DegreeToRadian * Real_Angle)};

		float Vector2_realRight[2] = {sinf(DegreeToRadian * (Real_Angle + 90)),cosf(DegreeToRadian * (Real_Angle + 90))};
		
		for(int i = 0;i < 4;i++)
		{
			float coefficients = 0;
			
			coefficients += forward_back[i]    * (Vector2_realForward[y] * sqrt(lim_pointRightY) * (pointRightY > 0? 1 : -1));
			coefficients += right_left[i]      * (Vector2_realForward[x] * sqrt(lim_pointRightY) * (pointRightY > 0? 1 : -1));
			
			coefficients += forward_back[i]    * (Vector2_realRight[y]   * sqrt(lim_pointRightX) * (pointRightX > 0? 1 : -1));
			coefficients += right_left[i]      * (Vector2_realRight[x]   * sqrt(lim_pointRightX) * (pointRightX > 0? 1 : -1));
			
			coefficients += turn_right_left[i] * pointLeftX;
		}
	}
	
	
	//约束速度防止超过设定最大值
	float Float_BiggestAimSpeed = 0;
	
	for(int i = 0;i < 4;i++)
	{	
		if(fabsf(aimSpeed[i]) > MAX_SPEED)
		{
			if(fabsf(aimSpeed[i]) > Float_BiggestAimSpeed)
			{
				Float_BiggestAimSpeed = fabsf(aimSpeed[i]);
			}
		}
		
	}
	if(Float_BiggestAimSpeed != 0)
	{
		for(int i = 0;i < 4;i++)
		{
			aimSpeed[i] = aimSpeed[i] * ((float)MAX_SPEED / (float)Float_BiggestAimSpeed);
		}
	}
}

void CollectData_Mecanum(void)
{
	Data_toVOFA[7].fload_data = aimSpeed[0];
	Data_toVOFA[8].fload_data = aimSpeed[1];
	Data_toVOFA[9].fload_data = aimSpeed[2];
	Data_toVOFA[10].fload_data = aimSpeed[3];
}
