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
	//�����ѹֵ��target���˻����棬actual�Ӵ������������ȼ���
	*mytarget = 150;
	*myactual = actual;
	res = *mytarget - *myactual;

	return res;
}

int get_speed(const int delta,int *myspeed)	//ע����ѹ��λҪ�ĳɸ�����
{
	int res = 0;
	if(myspeed == NULL)
	{
		res = -1;
		return res;
	}
	//���÷���
	if(delta > 0) DIR = N;	//��	
	else DIR = S;			//˳
	//���ý׶��ٶ�
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
void get_frequency(int *myarr,int *mypsc,int speed)		//�ٶȻ�ΪƵ��
{
	u16 arr = 200;
	u16 psc;
	if(speed != 0)
	{
		psc = 1350000/(arr*speed);	//��ϵ���㣬1350000�ɼ���õ�
		*myarr = arr;
		*mypsc = psc;
	}
}

