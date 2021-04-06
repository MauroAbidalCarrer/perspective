#include<stdio.h>
#include<time.h>
#include<assert.h>
#include<stdlib.h>
#define SI sizeof(int)

typedef struct game_s
{
	int** vals;
	int** cons;
	int size;
	struct game_s* next;
} game;

//strings
int myStrstr(char* a, char* b);
int strl(char* str);
int isNum(char c);
int nextC(char* str, char c);
int nextCs(char* str, char* Cs);
char* nextN(char* con);
//memMan
void* loc(int size);
int** array2D(int a, int b);
void freeGame(game* G);
void freeArray(int** array, int a);
//IO
void printGame(game G);
int checkArguments(char** av);
int error(int code);
char* getFileContent(char* path);
