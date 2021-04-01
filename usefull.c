#include"header.h"
int strl(char* str)
{
	int i = 0;
	while(str[i])
		i++;
	return i;
}

void* loc(int size)
{
	void* pointer = malloc(size);
	assert(pointer);
	return pointer;
}
