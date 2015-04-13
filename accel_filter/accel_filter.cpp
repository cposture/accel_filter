// accel_filter.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ReadData.h"

void position(long int accel_n[2][3], long int vel[2][3], long int displayment[2][3])
{
	int 					i;

	for (i = 0; i < 1; i++)
	{
		vel[1][i] = vel[0][i] + ((accel_n[0][i] + accel_n[1][i]) >> 1);
		displayment[1][i] = displayment[0][i] + ((vel[1][i] + vel[0][i]) >> 1);
	}

	for (i = 0; i < 1; i++)
	{
		vel[0][i] = vel[1][i];
		displayment[0][i] = displayment[1][i];
	}
}
/* 机械滤波 */
void movement_end_check(long int accel_n[3], long int vel[2][3])
{
	static unsigned int countx = 0, county = 0, countz = 0;
	//处理X轴
	if (accel_n[0] == 0) //we count the number of acceleration samples that equals cero
	{
		countx++;
	}
	else
	{
		countx = 0;
	}
	if (countx >= 25) //if this number exceeds 25, we can assume that velocity is cero
	{
		vel[1][0] = 0;
		vel[0][0] = 0;
	}
	

}
int _tmain(int argc, _TCHAR* argv[])
{
	long c;
	long int accel_n[2][3] = { 0 }, vel[2][3] = { 0 }, displayment[2][3] = { 0 };
	ReadData<long> data("E:\\M_Project\\位移计算\\加速度滤波\\accel_filter\\Debug\\a.txt");
	while (data.readNextLine(c))
	{
		accel_n[1][0] = c;
		position(accel_n, vel, displayment);
		accel_n[0][0] = accel_n[1][0];
		movement_end_check(accel_n[1], vel);
	}
	return 0;
}

