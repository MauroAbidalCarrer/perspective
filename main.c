#include "header.h"
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
	G->cons = loc(sizeof(int*) * 4);
	for(int i = 0; i < 4; i++)
	{
		G->cons[i] = loc(SI * size); 
		for(int j = 0; j < size; j++)
			G->cons[i][j] = av[1+i][j] - 48;
	}
	G->vals  = array2D(size, size);
	G->next = NULL;
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
	int j = 0;
	int size = 0;
	while(con[j] != '\n')
	{
		if(con[j] == 0)
			return NULL;
		size += isNum(con[j++]);
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
int isLegalG(int t, int y, int x, game G)
{
	int* segV = rSeg(y, x, 0, G);
	int* segH = rSeg(y, x, 1, G);
	int isLeg = 1;
	for(int i = 0; i < G.size; i++)
		isLeg *= (segV[i] != t) * (segH[i] != t);
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
		printf("(%d, %d) trying %d\n", x, y, trial);
		if(isLegalG(trial, y, x, *G))
		{
			G->vals[y][x] = trial;
			printf("(%d, %d) putting %d\n", x, y, trial);
			printGame(*G);
			if ((y == s-1 && x == s-1) 
					|| setVal(y + (x+1)/s, (x+1)%s, G))
				return 1;
			G->vals[y][x] = 0;
		}
		else
			printf("(%d, %d) could not put %d\n", x, y, trial);
	}
	return 0;
}
game createGame(int s/*size*/)
{
	//alloc mem
	game G;
	G.size = s;
	G.vals = array2D(s, s);
	G.cons = array2D(4, s);
	G.next = NULL;
	//set vals
if(!setVal(0, 0, &G))
	printf("could not gen\n");
	//set constrains
	for(int i = 0; i < s; i++)
	{
		int* H = rSeg(i, 0, 1, G);
		int* V = rSeg(0, i, 0, G);
		G.cons[0][i] = count(0, V, s);
		G.cons[1][i] = count(1, H, s);
		G.cons[2][i] = count(1, V, s);
		G.cons[3][i] = count(0, H, s);
	}
	return G;
}
game* readGames(char** con/*fileContent*/)
{
	//read constrains and get size
	while(!isNum(**con))
	{
		if(**con==0)
			return NULL;
		*con +=1;
	}
	int size;
	int** cons = loc(sizeof(int*) * 4);
	if((cons[0] = lineOfCons(*con, &size))==NULL)
		return NULL;
	cons[1] = loc(sizeof(int) * size);
	cons[3] = loc(sizeof(int) * size);
	int s;
	for(int i = 0; i < size; ++i)
	{
		*con = nextN(*con);
		int* line;
		if((line= lineOfCons(*con, &s)) == NULL)
			return NULL;
		if(s != 2)
		{printf("i=%d, s=%d\n con=\n%s", i,  s, *con);
			return NULL;}
		cons[3][i] = *line;
		cons[1][i] = line[1];
	}
	*con = nextN(*con);
	if((cons[2] = lineOfCons(*con, &s))==NULL)
	{printf("second line went wrong\n");
		return NULL;}
	if(s != size){
		printf("size=%d not equal to %d\n", s, size);
		return NULL;}
	*con += nextC(*con,'\n');
	//create game
	game* G = loc(sizeof(game));
	G->cons = cons;
	G->vals = array2D(size, size);
	G->size = size;
	G->next = readGames(con);
	return G;
}
int main(int ac, char** av)
{
	game* G;
	if (ac == 5)//then create game with av
	{
		int err = checkArguments(av);
		if(err != -1)
			return error(err);
		game* G = newGameFromAv(av);
		return 0;
	}
	if(ac == 2)//then read file
	{
		if(isNum(*av[1]))
		{
			srand((unsigned int) time(NULL));
			printGame(createGame(*av[1] - 48));
			return 0;
		}
		char* con/*content*/ = getFileContent(av[1]);
		G = readGames(&con);
	}
	while(G != NULL)
	{
		int solved = solve(0, 0, G);
		printGame(*G);
		if(!solved)
			return error(2);
		printf("solved!\n");
		G = G->next;
	}
	return 1;
}
