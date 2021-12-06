//初始化所有需要初始化的函数

#include "init.h"

#include "led.h"
#include "dbus.h"
#include "delay.h"

void init_all()
{
	delay_init(180);
	ledX_init();
	RC_Init();
}
