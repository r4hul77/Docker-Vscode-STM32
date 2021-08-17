#include "utils.h"



bool parseFloat(char* buffer, int& pos, uint16_t bufferLen, float& ret)
{	
	if(bufferLen<pos+4)
		return false;

	for (int i = 0; i < 4; i++)
		((char* )&ret)[i] = buffer[pos + i];
	pos = pos + 4;

	return true;
}


bool parseUint32(char* buffer, int& pos, uint16_t bufferLen, uint32_t& ret)
{	
	if(bufferLen<pos+4)
		return false;

	for (int i = 0; i < 4; i++)
		((char* )&ret)[i] = buffer[pos + i];
	pos = pos + 4;

	return true;
}


bool parseInt32(char* buffer, int& pos, uint16_t bufferLen, int& ret)
{	
	if(bufferLen<pos+4)
		return false;

	for (int i = 0; i < 4; i++)
		((char* )&ret)[i] = buffer[pos + i];
	pos = pos + 4;

	return true;
}

bool parseInt16(char* buffer, int& pos, uint16_t bufferLen, int16_t& ret)
{	
	if(bufferLen<pos+2)
		return false;

	for (int i = 0; i < 2; i++)
		((char* )&ret)[i] = buffer[pos + i];
	pos = pos + 2;

	return true;
}


bool float2Bytes(char* buffer, float FloatVarible, int& pos, uint16_t bufferLen)
{
	if(bufferLen<pos+4)
		return false;
	std::memcpy(buffer + pos, (char*) &FloatVarible, 4);
	pos += 4;
	return true;
}

bool uint322Bytes(char* buffer, uint32_t uint32Varible, int& pos, uint16_t bufferLen)
{
	if(bufferLen<pos+4)
		return false;
	std::memcpy(buffer + pos, (char*) &uint32Varible, 4);
	pos += 4;

	return true;
}