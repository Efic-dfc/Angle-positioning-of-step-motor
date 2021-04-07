/*
	此文件定义了控制电机的相关函数
*/
#ifndef __CONTROL_H
#define __CONTROL_H	 
#include "sys.h"

#define N 0		//逆时针
#define S 1		//顺时针

extern int actual;		//定义实际气压全局变量，用于timer.c的中断函数，模拟实际气压变化



int get_value(int *mytarget,int *myactual);		//计算气压差值并返回
int get_speed(const int delta,int *myspeed);		//带入差值，计算阶段对应速度和方向
void get_frequency(int *myarr,int *mypsc,int speed);	//将速度转化为定时器频率传给定时器




//void manual_driver(int myarr,int mypsc,int speed);		//手动控制，固定速度，按键控制方向。
														//用这个函数前，需要先启动定时器

#endif
