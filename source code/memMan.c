#include"header.h"
//alloc
void* loc(int size)
{
	void* pointer = malloc(size);
	assert(pointer);
	return pointer;
}
int** array2D(int a, int b)
{
	int** array = loc(sizeof(int*)*a);
	for(int i = 0; i < a; i++)
	{
		array[i] = loc(sizeof(int)*b);
		for(int j = 0; j < b; j++)
			array[i][j] = 0;
	}
	return array;
}
game* newGameFromAv(char** av)
{
	game* G = loc(sizeof(game));
	int size = strl(av[1]);
	G->size = size;
	G->cons = array2D(4, size);
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < size; j++)
			G->cons[i][j] = av[1+i][j] - 48;
	}
	G->vals  = array2D(size, size);
	G->next = NULL;
	return G;
}
//free
void freeArray(int** array, int a)
{
	for(int i = 0; i < a; i++)
		free(array[i]);
	free(array);
}
void freeGame(game* G)
{
	if(G->next)
		freeGame(G->next);
	freeArray(G->cons, 4);
	freeArray(G->vals, G->size);
	free(G);
}
//clear mem
void clearIntArray(int** array, int a, int b)
{
	for(int i = 0; i < a; i++)
	{
		for(int j = 0; j < b; j++)
			array[i][j] = 0;
	}
}
