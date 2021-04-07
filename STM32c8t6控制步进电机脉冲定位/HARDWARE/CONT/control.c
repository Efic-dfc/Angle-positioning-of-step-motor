#include "control.h"
#include <math.h>
#include <stdlib.h> 
#include "timer.h"

int get_value(int *mytarget,int *myactual)	
{
	int res = 0;
	if(mytarget == NULL || myactual == NULL)
	{
		res = -1;
		return res;
	}
	//获得气压值，target从人机界面，actual从传感器，这里先假设
	*mytarget = 150;
	*myactual = actual;
	res = *mytarget - *myactual;

	return res;
}

int get_speed(const int delta,int *myspeed)	//注意气压单位要改成浮点型
{
	int res = 0;
	if(myspeed == NULL)
	{
		res = -1;
		return res;
	}
	//设置方向
	if(delta > 0) DIR = N;	//逆	
	else DIR = S;			//顺
	//设置阶段速度
	if(abs(delta)>=0 && abs(delta) <= 2)	
	{
		*myspeed = 0;	
	}
	else if(2<abs(delta)<=10)
	{
		*myspeed = 15;
	}
	else if(10<abs(delta)<=60)
	{
		*myspeed = 30;
	}
	else 
	{
		*myspeed = 45;
	}
	return res;
}
void get_frequency(int *myarr,int *mypsc,int speed)		//速度化为频率
{
	u16 arr = 200;
	u16 psc;
	if(speed != 0)
	{
		psc = 1350000/(arr*speed);	//关系换算，1350000由计算得到
		*myarr = arr;
		*mypsc = psc;
	}
}

