//���ݻ��ܣ����ں�������
#include "data_stream.h"


Data_bmi_struct Data_bmi;

RC_Ctl_t Data_RC;

moto_info Data_m3508[4];
moto_info Data_m6020[4];
moto_info Data_m2006;


send_float Data_toVOFA[100];
//����λ�����ݺ��嶨��:
// 0:���3058ת��(��ǰ)| 0      |
// 1:���3058ת��(���)|        |   CAN
// 2:���3058ת��(�Һ�)|        |
// 3:���3058ת��(��ǰ)|        |
//                              |
// 4:���6020�Ƕ�(yaw��)  | 1   |
// 5:���6020�ܽǶ�(yaw��)|     |
// 6:���6020�Ƕ�(pitch��)|     |
//
// 7:aimSpeed(��ǰ)| 2          |
// 8:aimSpeed(���)|            |   MECANUM
// 9:aimSpeed(�Һ�)|            |
//10:aimSpeed(��ǰ)|            |
//
//11:ң��������ch0| 3           |   DBUS
//12:ң��������ch1|             |
//13:ң��������ch2|             |
//14:ң��������ch3|             |

//15:�������ܽǶ�
//16:�����ǵ�ǰ�Ƕ�(0~359)

void (*CollectData[DataSource])(void);
