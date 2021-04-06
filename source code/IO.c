#include "header.h"
//OUTPUT
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
		{
			if(G.vals[i][j])
				printf("%d ", G.vals[i][j]);
			else
				printf("x ");
		}
		printf("%d\n", G.cons[1][i]);
	}
	printf("  ");
	for(int i  = 0; i < G.size; i++)
		printf("%d ", G.cons[2][i]);
	printf("\n\n");
}

//INPUT
//checks
int error(int code)
{
	char* errors[] = {
		"can only enter one, two or four arguments",
		"not every constrain array has the same length",
		"could not be solved",
		"put only numbers in the arguments",
		"can't open the file",
		"constrains must be in the range 1-9 included",
"Second argument could not be read.\nWrite \"+a\" after the desired size if you want to show the answer of the genrated puzzle",
"cannot generate a puzzle of size 0"
	};
	printf("ERROR %d: %s\n", code, errors[code]);
	return code;
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
			if(av[i][j] == 48)
				return 5;
			j++;
		}
		if(j != length)
			return 1;
	}
	return -1;//no error
}
//read files
char* getFileContent(char* path)
{
	FILE *fd = fopen(path, "r"); // read mode
	if (fd == NULL)
		return NULL;
	int length = 0;
	while(fgetc(fd) != EOF)
		length++;
	rewind(fd);
	char* content = loc(sizeof(char) * (length + 1));
	int i = -1;
	while(++i < length)
		content[i] = fgetc(fd);
	content[i] = 0;
	fclose(fd);
	return content;
}
