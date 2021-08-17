#include "utils.h"



void parseFloat(char* buffer, int& pos, uint16_t bufferLen, float& ret)
{
	for (int i = 0; i < 4; i++)
		((char* )&ret)[i] = buffer[pos + i];
	pos = pos + 4;
}


void float2Bytes(char* buffer, float FloatVarible, int& pos)
{
	std::memcpy(buffer + pos, (char*) &FloatVarible, 4);
	pos += 4;
}

void uint322Bytes(char* buffer, uint32_t uint32Varible, int& pos)
{
	std::memcpy(buffer + pos, (char*) &uint32Varible, 4);
	pos += 4;
}