#ifndef READDATA_H
#define READDATA_H

#include "stdio.h"
#include "string.h"
template <class DataType> class ReadData
{
private:
	char	*fileName;
	FILE    *fp;
	bool	flag;
public:
	ReadData(char *f)
	{
		fileName = new char[512];
		memcpy(fileName, f, strlen(f) + 1);
		fp = fopen(fileName, "r");
		flag = fp != NULL;
	}
	bool readNextLine(DataType &sLineWord);
	bool isOpenSuccess();
};

template <class DataType>
bool ReadData<DataType>::readNextLine(DataType &sLineWord)
{
	int res = fscanf(fp, "%d", &sLineWord);
	return	res != -1;
}
template <class DataType>
bool ReadData<DataType>::isOpenSuccess()
{
	return flag;
}
#endif
