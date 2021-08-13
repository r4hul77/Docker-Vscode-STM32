#include "utils.h"

void parseFloat(char* buffer, int& pos, uint16_t bufferLen, float& ret)
{
	for (int i = 0; i < 4; i++)
		((char* )&ret)[i] = buffer[pos + i];
	pos = pos + 4;
}
