#include"header.h"

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
