#include "header.h"
int main(int ac, char** av)
{
	if(ac != 5 && ac != 2 && ac != 3)
		return error(0);
	game* G;
	if (ac == 5)//then create game with av
	{
		int err = checkArguments(av);
		if(err != -1)
			return error(err);
		G = newGameFromAv(av);
	}
	if(ac == 2 || ac == 3)
	{
		//generate game
		if(isNum(*av[1]) && strl(av[1]) == 1)
		{	
			if(*av[1] == 48)
				return error(7);
			//taken from the internet
			srand((unsigned int) time(NULL));
			game G;
			if(ac == 3)
			{
				if(myStrstr(av[2], "+a"))
					G = createGame(*av[1] - 48, 1);
				else
					return error(6);
			}
			else
				G = createGame(*av[1] - 48, 0);
			printGame(G);
			freeArray(G.vals, G.size);
			freeArray(G.cons, 4);
			return 0;
		}
		//read game
		char* con/*content*/ = getFileContent(av[1]);
		if(con == NULL)
			return error(4);
		char* keepTrack = con;
		G = readGames(&con);
		free(keepTrack);
	}
	game* firstG = G;
	while(G != NULL)
	{
		int solved = solve(0, 0, G);
		printGame(*G);
		if(!solved)
			return error(2);
		printf("solved!\n");
		G = G->next;
	}
	freeGame(firstG);
	return 0;
}
