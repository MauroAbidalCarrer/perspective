#include "header.h"
game* newGame(char** av)
{
	game* G = loc(sizeof(game));
	int size = strl(av[1]);
	G->size = size;
	G->vals = loc(sizeof(int*) * size);
	G->cons = loc(sizeof(int*) * 4);
	for(int i = 0; i < 4; i++)
	{
		G->cons[i] = loc(SI * size); 
		for(int j = 0; j < size; j++)
		{
			G->cons[i][j] = av[1+i][j] - 48;
			G->vals[j] = loc(SI * size);
			for(int k = 0; k < size; k++)
				G->vals[j][k] = 0;
		}
	}
	return G;
}

int* rSeg(int y, int x, int sens, game G)//0 down 1 right
{
	int* seg = loc(sizeof(int) * G.size);
	for(int i = 0; i < G.size; i++)
		seg[i]  = G.vals[sens ? y : i][sens ? i : x];
	return seg;
}
int count(int s/*sens*/, int* seg, int size)//0 right 1 left
{
	int nb = 1;
	int H = s?seg[size-1]:*seg;
	for(int i = s ? size-1 : 0; s?(i>=0):(i<size); i+=(s?-1:1))
	{
		nb += (H < seg[i]);
		H = H < seg[i] ? seg[i] : H;
	}
	return nb;
}
int isLegal(int y, int x, int t, game G)
{
	//printf("isLegal(y=%d, x=%d, %d)\n", y, x, t);
	int isLeg = 1;
	//horizontal checks
	int* s = rSeg(y, x, 1, G);
	for(int i = 0; i < G.size; i++){
		if(s[i] == t)
			return 0;
	}
	s[x] = t;
	if(x == G.size - 1){
		isLeg *= (count(0, s, G.size)==G.cons[3][y]);
		isLeg *= (count(1, s, G.size)==G.cons[1][y]);
	}

	//vertical checks
	s = rSeg(y, x, 0, G);
	for(int i = 0; i < G.size; i++){
		if(s[i] == t)
			return 0;
	}
	s[y] = t;
	if(y == G.size - 1){
		isLeg *= (count(0, s, G.size)==G.cons[0][x]);
		isLeg *= (count(1, s, G.size)==G.cons[2][x]);
	}
	return isLeg;
}
int solve(int y, int x, game* G)
{
	int s = G->size;
	for(int t/*trial*/ = 1; t <= s; t++)
	{
		if(isLegal(y, x, t, *G))
		{
			G->vals[y][x] = t;
			//printGame(*G);
			if ((y == s-1 && x == s-1) 
				|| solve(y + (x+1)/s, (x+1)%s, G))
				return 1;
			G->vals[y][x] = 0;
		}
	}
	return 0;
}
int main(int ac, char** av)
{
	//if ac == 5 then create game with av
	//if ac == 2 rhen read file 
	//else error 0
	if (ac != 5)
		return error(1);
	int err = checkArguments(av);
	if(err != -1)
		return error(err);
	game* G = newGame(av);
	//printGame(*G);
	int yes = solve(0, 0, G);
	printf("\n");
	printGame(*G);
	if(!yes)
		return error(2);
	printf("solved!\n");
}
