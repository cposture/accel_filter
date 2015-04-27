#include "accel_filter.h"
#include "math.h"
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
#if SIGMA_FILTER_OPEN

#define ACC_FILTER_COUNT	16
#define SIGMA_WIDTH			2
int16	acc_xyz_data[3][ACC_FILTER_COUNT] = { 0 };
int16	acc_data_index = 0;
void sigma_Filter(int16 accel[][3], int32 accel_res[][3], int16 pos, int16 N, int16 K)
{
	int32 sums[3][2] = { 0 }, sum[3] = { 0 };
	int16 i, j, temp, count[3] = {0};
	double delta[3], mean;

	for (i = 0; i < 3; i++)
	{
		//以pos为数据中心，求accel[pos-N,pos+N]的和、平方和
		for (j = pos - N; j <= pos + N; j++)
		{
			temp = accel[(j + ACC_FILTER_COUNT) % ACC_FILTER_COUNT][i];
			sums[i][0] += temp;
			sums[i][1] += temp * temp;
		}
		//求序列的平均数和方差，最后求出sigma范围
		mean = sums[i][0] / (2 * N + 1);
		delta[i] = sums[i][1] / (2 * N + 1) - mean * mean;
		delta[i] = SIGMA_WIDTH * sqrt(delta[i]);

		//算出在sigma范围的元素个数及和
		for (j = pos - N; j <= pos + N; j++)
		{
			if (accel[(j + ACC_FILTER_COUNT) % ACC_FILTER_COUNT][i] < delta[i] + accel[pos][i] && accel[(j + ACC_FILTER_COUNT) % ACC_FILTER_COUNT][i] > accel[pos][i] - delta[i])
			{
				count[i]++;
				sum[i] += accel[(j + ACC_FILTER_COUNT) % ACC_FILTER_COUNT][i];
			}
		}

		//超过阀值，则用sigma范围里的元素的平均数替代
		if (count[i] >= K)
		{
			accel_res[pos][i] = sum[i] / count[i];
		}
		else//用序列中所有元素的平均数替代，除了accel[pos]
		{
			accel_res[pos][i] = (sums[i][0] - accel[pos][i]) / (2 * N);
		}
	}
}

#endif