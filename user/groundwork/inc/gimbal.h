#ifndef GIMBAL_H
#define GIMBAL_H

#include "stm32f4xx_conf.h"

extern float FloatArray_GimbalCoefficients_position[3];
extern float FloatArray_GimbalCoefficients_speed[3];
extern float FloatArray_GimbalCoefficients_current[3];
extern float FloatArray_SetAngle[2];

void SetAngles(float Float_Angle_01,float Float_Angle_02);
void SetAngles_delta(float Float_Angle_01_delta,float Float_Angle_02_delta);
void LimAngle(float up,float down);

#endif
