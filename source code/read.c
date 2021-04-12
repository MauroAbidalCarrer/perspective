#include"header.h"
//________________________read game in file content______________
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
game* readGames(char** con/*fileContent adress*/)
{
	//get to the first number
	while(!isNum(**con))
	{
		if(**con==0)
			return NULL;
		*con += 1;
	}
	int size;
	int** cons = loc(sizeof(int*) * 4);
	if((cons[0] = lineOfCons(*con, &size)) == NULL)
		return NULL;
	cons[1] = loc(sizeof(int) * size);
	cons[3] = loc(sizeof(int) * size);
	int s;
	for(int i = 0; i < size; ++i)
	{
		*con = nextN(*con);
		int* line;
		if((line = lineOfCons(*con, &s)) == NULL)
			return NULL;
		if(s != 2)
			return NULL;
		cons[3][i] = *line;
		cons[1][i] = line[1];
		free(line);
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
