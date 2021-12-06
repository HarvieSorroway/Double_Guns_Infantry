#include "FreeRTOS.h"

#include "init.h"

#include "led.h"
#include "delay.h"
#include "dbus.h"

int main(void)
{
	
	init_all();
    while(1)
	{
		if(RC_CtrlData.rc.s1 == 1)ledX_cmd(3);
		if(RC_CtrlData.rc.s1 == 3)ledX_cmd(5);
		if(RC_CtrlData.rc.s1 == 2)ledX_cmd(7);				
	}
}
