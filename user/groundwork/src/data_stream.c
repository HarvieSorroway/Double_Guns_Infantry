//数据汇总，便于后续调用
#include "data_stream.h"


Data_bmi_struct Data_bmi;

RC_Ctl_t Data_RC;

moto_info Data_m3508[4];
moto_info Data_m6020[4];
moto_info Data_m2006;


send_float Data_toVOFA[100];
//各个位的数据含义定义:
// 0:电机3058转速(左前)| 0      |
// 1:电机3058转速(左后)|        |   CAN
// 2:电机3058转速(右后)|        |
// 3:电机3058转速(右前)|        |
//                              |
// 4:电机6020角度(yaw轴)  | 1   |
// 5:电机6020总角度(yaw轴)|     |
// 6:电机6020角度(pitch轴)|     |
//
// 7:aimSpeed(左前)| 2          |
// 8:aimSpeed(左后)|            |   MECANUM
// 9:aimSpeed(右后)|            |
//10:aimSpeed(右前)|            |
//
//11:遥控器数据ch0| 3           |   DBUS
//12:遥控器数据ch1|             |
//13:遥控器数据ch2|             |
//14:遥控器数据ch3|             |

//15:陀螺仪总角度
//16:陀螺仪当前角度(0~359)

void (*CollectData[DataSource])(void);
