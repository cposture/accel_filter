// accel_filter.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "ReadData.h"


int _tmain(int argc, _TCHAR* argv[])
{
	long c;
	long int accel_n[2][3] = { 0 }, vel[2][3] = { 0 }, displayment[2][3] = { 0 };
	ReadData<long> data("E:\\M_Project\\λ�Ƽ���\\���ٶ��˲�\\accel_filter\\Debug\\a.txt");
	while (data.readNextLine(c))
	{
		accel_n[1][0] = c;
		position(accel_n, vel, displayment);
		accel_n[0][0] = accel_n[1][0];
		movement_end_check(accel_n[1], vel);
	}
	return 0;
}

