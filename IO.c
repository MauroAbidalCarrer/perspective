#include "header.h"
void printGame(game G)
{
	printf("  ");
	for(int i  = 0; i < G.size; i++)
		printf("%d ", G.cons[0][i]);
	printf("\n");;
	for(int i  = 0; i < G.size; i++)
	{
		printf("%d ", G.cons[3][i]);
		for(int j  = 0; j < G.size; j++)
			printf("%d ", G.vals[i][j]);
		printf("%d\n", G.cons[1][i]);
	}
	printf("  ");
	for(int i  = 0; i < G.size; i++)
		printf("%d ", G.cons[2][i]);
	printf("\n");
}
int error(int code)
{
	char* errors[] = {
		"needs 4 arguments",
		"not every constrain array has the same length",
		"could  not be solved",
		"put only numbers in the arguments"
	};
	printf("ERROR %d: %s\n", code, errors[code]);
	return 1;
}
int checkArguments(char** av)
{
	int length = strl(av[1]);
	for(int i = 1; i < 5; i++)
	{
		int j = 0;
		while(av[i][j]){
			if(!isNum(av[i][j]))
				return 3;
			j++;
		}
		if(j != length)
			return 1;
	}
	return -1;//no error
}