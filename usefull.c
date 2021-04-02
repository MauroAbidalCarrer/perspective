#include"header.h"

void* loc(int size)
{
	void* pointer = malloc(size);
	assert(pointer);
	return pointer;
}

//strings and chars
int strl(char* str)
{
	int i = 0;
	while(str[i])
		i++;
	return i;
}
int isNum(char c)
{return (c>=48&&c<=58);}
int nextC(char* str, char c)
{
	int i = -1;
	while(str[++i])
	{
		if(str[i] == c)
			return i;
	}
	return -1;
}
int nextCs(char* str, char* Cs)
{
	int i = -1;
	while(str[++i])
	{
		int next = nextC(Cs, str[i]);
		if(next != 1)
			return next;
	}
	return -1;
}
int nextN(char* str)
{
	int i = -1;
	while(str[++i])
	{
		if(isNum(str[i]))
			return i;
	}
	return -1;
}
