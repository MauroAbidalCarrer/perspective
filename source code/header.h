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
game* newGameFromAv(char** av);
int** array2D(int a, int b);
void freeGame(game* G);
void freeArray(int** array, int a);
void clearIntArray(int** array, int a, int b);
//IO
void printGame(game G);
int checkArguments(char** av);
int error(int code);
char* getFileContent(char* path);
//readGame
game* readGames(char** con/*fileContent adress*/);
int* lineOfCons(char* con, int* s);
//solve
int solve(int y, int x, game* G);
int isLegal(int y, int x, int t, game G);
int count(int s/*sens*/, int* seg, int size);
int* rSeg(int y, int x, int sens, game G);
//generate game
game createGame(int s/*size*/, int showAnswer);
int setVal(int y, int x, game* G);
int isLegalG(int t, int y, int x, game G);

