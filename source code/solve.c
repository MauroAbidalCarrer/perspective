#include "header.h"
//___________________solve game
//0 down 1 right
int* rSeg(int y, int x, int sens, game G){
	int* seg = loc(sizeof(int) * G.size);
	for(int i = 0; i < G.size; i++)
		seg[i]  = G.vals[sens ? y : i][sens ? i : x];
	return seg;
}
//0 right 1 left
int count(int s/*sens*/, int* seg, int size)
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
	int isLeg = 1;
	//horizontal checks
	int* s = rSeg(y, x, 1, G);
	for(int i = 0; i < G.size; i++)
		isLeg *= s[i] != t;
	s[x] = t;
	if(x == G.size - 1){
		isLeg *= (count(0, s, G.size)==G.cons[3][y]);
		isLeg *= (count(1, s, G.size)==G.cons[1][y]);
	}
	else
		isLeg *= count(0, s, G.size) <= G.cons[3][y];
	free(s);

	//vertical checks
	s = rSeg(y, x, 0, G);
	for(int i = 0; i < G.size; i++)
		isLeg *= s[i] != t;
	s[y] = t;
	if(y == G.size - 1){
		isLeg *= (count(0, s, G.size)==G.cons[0][x]);
		isLeg *= (count(1, s, G.size)==G.cons[2][x]);
	}
	else
		isLeg *= count(0, s, G.size) <= G.cons[0][x];
	free(s);
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
			if ((y == s-1 && x == s-1)
					|| solve(y + (x+1)/s, (x+1)%s, G))
				return 1;
			G->vals[y][x] = 0;
		}
	}
	return 0;
}
