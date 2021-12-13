#include "gimbal.h"

float FloatArray_GimbalCoefficients_position[3] = {200,0,0};
float FloatArray_GimbalCoefficients_speed[3] = {7,0,0};
float FloatArray_GimbalCoefficients_current[3] = {1.5,0,0};

float FloatArray_SetAngle[2] = {0,0};

void SetAngles(float Float_Angle_01,float Float_Angle_02)
{
	FloatArray_SetAngle[0] = Float_Angle_01;
	FloatArray_SetAngle[1] = Float_Angle_02;
}

void SetAngles_delta(float Float_Angle_01_delta,float Float_Angle_02_delta)
{
	FloatArray_SetAngle[0] += Float_Angle_01_delta;
	FloatArray_SetAngle[1] += Float_Angle_02_delta;
}
