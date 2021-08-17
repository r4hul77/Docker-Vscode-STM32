#ifndef UTILS_H
#define UTILS_H
#include <stdint.h>
#include <cstdint>
#include <cstring>

#define PI 3.1415926535

void parseFloat(char* buffer, int& pos, uint16_t bufferLen, float& ret);

void float2Bytes(char* bufferm, float FloatVarible, int& pos);

void uint322Bytes(char* bufferm, uint32_t uint32Variable, int& pos);


template <class T>
struct movingAvgFilter
{
	T* filterPts;
	uint8_t i;
	T avg;
	bool full;
	uint8_t size;

	movingAvgFilter(uint8_t size): filterPts(new T[size]), i(0), avg(0), full(false), size(size)
	{

	}

	void update(T val)
	{
		if (!full)
		{
			avg += val / size;
			i++;
			full = (i == size);
		}
		else
		{
			avg -= filterPts[i] / size;
			avg += val / size;
			filterPts[i] = val;
			i++;
		}
		i = i % size;

	}

	bool ifFull()
	{
		return full;
	}

	T sample()
	{
		return avg;
	}

	~movingAvgFilter()
	{
		delete filterPts;
	}
};
#endif