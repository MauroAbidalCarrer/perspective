#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#define SI sizeof(int)

typedef struct game_s
{
	int** vals;
	int** cons;
	int size;
} game;

//usefull
int strl(char* str);
void* loc(int size);
int isNum(char c);
//IO
void printGame(game G);
int checkArguments(char** av);
int error(int code);
