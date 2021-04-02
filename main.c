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
int* lineOfCons(char* con, int* s)
{
	//	printf("line called con =\n%s", con);
	int j = 0;
	int size = 0;
	while(con[j] && con[j] != '\n')
	{
		size += isNum(con[j]);
		j++;
	}
	int* cons = loc(sizeof(int) * size);
	j = 0;
	int i = 0;
	while(con[j] != '\n')
	{
		if(isNum(con[j]))
			cons[i++] = con[j] - 48;
		j++;
	}
	*s = size;
	return cons;
}
game* readGame(char* con/*fileContent*/)
{
	int size;
	int** cons = loc(sizeof(int*) * 4);
	cons[0] = lineOfCons(con, &size);
	cons[1] = loc(sizeof(int) * size);
	cons[3] = loc(sizeof(int) * size);
	int useless;
	for(int i = 0; i < size; ++i)
	{
		con += nextC(con, '\n');
		while(!isNum(*con))
			con++;
		int* yes = lineOfCons(con, &useless);
		cons[3][i] = *yes;
		cons[1][i] = yes[1];
	}
	con += nextC(con, '\n');
	while(!isNum(*con))
		con++;
	cons[2] = lineOfCons(con, &useless);
	for(int j = 0; j < 4; j++)
	{
		for(int k =0; k < size; k++)
			printf("cons[%d][%d]=%d\n", j, k, cons[j][k]);
		printf("\n");
	}

	return NULL;
}
int main(int ac, char** av)
{
	if (ac == 5)//then create game with av
	{
		printf("ac = 5\n");
		int err = checkArguments(av);
		if(err != -1)
			return error(err);
		game* G = newGame(av);
		//printGame(*G);
		int yes = solve(0, 0, G);
		printGame(*G);
		if(!yes)
			return error(2);
		printf("solved!\n");
		return 0;
	}
	if(ac == 2)//then read file
	{
		char* con/*content*/ = getFileContent(av[1]);
		game* G;
		void* azbeyazE = readGame(con);
	}
	return 1;
}
