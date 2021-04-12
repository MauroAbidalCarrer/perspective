#include"header.h"
//_________________________generate random game
int isLegalG(int t, int y, int x, game G)
{
	int* segV = rSeg(y, x, 0, G);
	int* segH = rSeg(y, x, 1, G);
	int isLeg = 1;
	for(int i = 0; i < G.size; i++)
		isLeg *= (segV[i] != t) * (segH[i] != t);
	free(segV);
	free(segH);
	return isLeg;
}
int setVal(int y, int x, game* G)
{
	int s = G->size;
	int trial = rand();
	for(int i = 0; i < s; i++)
	{
		trial = (trial + 1 ) % (s+1);
		trial = trial == 0 ? 1 : trial;
		if(isLegalG(trial, y, x, *G))
		{
			G->vals[y][x] = trial;
			if ((y == s-1 && x == s-1)
					|| setVal(y + (x+1)/s, (x+1)%s, G))
				return 1;
			G->vals[y][x] = 0;
		}
	}
	return 0;
}
game createGame(int s/*size*/, int showAnswer)
{
	//alloc mem
	game G;
	G.size = s;
	G.vals = array2D(s, s);
	G.cons = array2D(4, s);
	G.next = NULL;
	//set vals
	setVal(0, 0, &G);
	//set constrains
	for(int i = 0; i < s; i++)
	{
		int* H = rSeg(i, 0, 1, G);
		int* V = rSeg(0, i, 0, G);
		G.cons[0][i] = count(0, V, s);
		G.cons[1][i] = count(1, H, s);
		G.cons[2][i] = count(1, V, s);
		G.cons[3][i] = count(0, H, s);
		free(H);
		free(V);
	}
	if(!showAnswer)
		clearIntArray(G.vals, s, s);
	return G;
}
