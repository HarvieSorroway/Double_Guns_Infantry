#ifndef __MECANUM_H
#define __MECANUM_H

#include "stm32f4xx_conf.h"
#include "math.h"


extern float aimSpeed[4];
extern float Float_NowAngle;

void get_aimSpeed(void);
void CollectData_Mecanum(void);

#endif
