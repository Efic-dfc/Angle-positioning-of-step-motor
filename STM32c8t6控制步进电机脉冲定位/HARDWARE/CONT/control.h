/*
	���ļ������˿��Ƶ������غ���
*/
#ifndef __CONTROL_H
#define __CONTROL_H	 
#include "sys.h"

#define N 0		//��ʱ��
#define S 1		//˳ʱ��

extern int actual;		//����ʵ����ѹȫ�ֱ���������timer.c���жϺ�����ģ��ʵ����ѹ�仯



int get_value(int *mytarget,int *myactual);		//������ѹ��ֵ������
int get_speed(const int delta,int *myspeed);		//�����ֵ������׶ζ�Ӧ�ٶȺͷ���
void get_frequency(int *myarr,int *mypsc,int speed);	//���ٶ�ת��Ϊ��ʱ��Ƶ�ʴ�����ʱ��




//void manual_driver(int myarr,int mypsc,int speed);		//�ֶ����ƣ��̶��ٶȣ��������Ʒ���
														//���������ǰ����Ҫ��������ʱ��

#endif
