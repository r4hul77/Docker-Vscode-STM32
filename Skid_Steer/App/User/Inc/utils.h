#ifndef UTILS_H
#define UTILS_H
#include <stdint.h>
#include <cstdint>
#include <cstring>

#define PI 3.1415926535


template <class T>
struct movingAvgFilter
{
	T* filterPts;
	uint16_t i;
	T avg;
	bool full;
	uint16_t size_init;
	uint16_t size;

	movingAvgFilter(uint16_t size): filterPts(new T[size]), i(0), avg(0), full(false), size_init(size), size(size)
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
		delete[] filterPts;
	}

	void setBufferSize(uint16_t set_size)
	{
		if (set_size < size_init)
		{
			size = set_size;
			avg = 0;
			full = false;
			i = 0;
		}
	}

};
#endif