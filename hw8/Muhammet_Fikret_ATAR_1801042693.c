#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE    100
//================================================================
struct dir
{
	char       name[SIZE];
	struct dir *dady; struct dir *per;  struct dir *sub;                                                                                                                                                                                          /* Sub directory of a parent */
	struct dir *near;                                                                                                                                                                                         /* Other elements in the same directory. */
};

typedef struct dir NODE;
//================================================================
void Read_File(char Arr[SIZE][SIZE][SIZE], int col[], int *row);
void Display_Arr(char Arr[SIZE][SIZE][SIZE], int col[], int *row);
char *Find_Root(char Arr[SIZE][SIZE][SIZE], int *row);
NODE *New_Node(char *word);
NODE *New_Near_Node(NODE *node, char *word);
NODE *New_Sub_Dir(NODE *node, char *word);
int Check_SameSub(NODE *top, char *word);
void Display_Tree(NODE *node);
void Create_Tree_Structure(NODE *root, char Arr[SIZE][SIZE][SIZE], int col[], int *row);
void Read_Command(char Arr[SIZE][SIZE][SIZE], int col[], int *row);
void CommandToken(char *WORD, char Tokens[SIZE][SIZE], int *size, int *isRoot);
void DoCommands(NODE *root, char Arr[SIZE][SIZE][SIZE], int row);
void printTokens(char Tokens[SIZE][SIZE], int size, int isRoot);
NODE * cd(NODE *root, NODE *Current, char Tokens[SIZE][SIZE] , int isRoot, int size);
NODE *child(NODE *root, char *WORD);
NODE * WantedNode(NODE *root, NODE *Current, char Tokens[SIZE][SIZE], int isRoot, int size);
void OutputPart(NODE *node, char* outputFile);
void OutputPartActual(NODE *node, char* directory, FILE *fp);

//================================================================
int main(int argc, char const *argv[])
{
	char Files[SIZE][SIZE][SIZE];                              /* 3D Array of files.txt. Seperated by per '/'. Will be used to create struct of tre. */
	char Commands[SIZE][SIZE][SIZE];
	char directoryPer[SIZE] = "";
	int  i,
	     r = 0, r2 = 0,                                     /* Number of rows */
	     c[SIZE] = { 0 }, c2[SIZE] = { 0 };                 /* Numbers of elements in each column  */

	Read_File(Files, c, &r);


	NODE *Root = New_Node(Find_Root(Files, &r));
	Create_Tree_Structure(Root, Files, c, &r);
	
	//Display_Tree(Root);

	Read_Command(Commands, c2, &r2);

	DoCommands(Root, Commands, r2);

	//printf("\n\n");

	//Display_Arr(Commands, c2, &r2);


	OutputPart(Root, "output.txt");

	//Display_Tree(Root);


	return 0;
}


//================================================================

void OutputPart(NODE *node, char* outputFile) {
	

	char directory[SIZE] = "";
	FILE *fp;

	sprintf(directory, "%s", node->name);

	fp = fopen(outputFile, "w");

	fprintf(fp, "%s", directory);
	OutputPartActual(node, directory, fp);

	fclose(fp);


}

void OutputPartActual(NODE *node, char* directory, FILE *fp)
{
	NODE *temp = node;
	int  flag  = 0;
	char directoryPer[SIZE];

	if (temp == NULL)
	{
		return;
	}

	while (temp)
	{
		if (flag == 0)
		{	
			temp = temp->sub;
			if (temp)
			{
				sprintf(directoryPer, "%s/%s", directory, temp->name);
				fprintf(fp, "\n%s",directoryPer);
				flag = 1;
			}
		}
		else
		{
			temp = temp->near;
			if (temp)
			{
				sprintf(directoryPer, "%s/%s", directory, temp->name);
				fprintf(fp, "\n%s",directoryPer);
				
			}
		}
		OutputPartActual(temp, directoryPer, fp);
	}
}


//================================================================
void Read_File(char Arr[SIZE][SIZE][SIZE], int col[], int *row)
{
	FILE *fp = fopen("files.txt", "r");
	char *tok;
	char temp[SIZE];
	int  i = 0, j = 0;

	while (fscanf(fp, "%s", temp) != EOF)
	{
		tok = strtok(temp, "/");
		while (tok != NULL)
		{
			strcpy(Arr[i][j++], tok);

			tok = strtok(NULL, "/");
		}
		col[i] = j;
		i++;
		j = 0;
	}

	(*row) = i;
}


//================================================================
void Display_Arr(char Arr[SIZE][SIZE][SIZE], int col[], int *row)
{
	for (int i = 0; i < (*row); ++i)
	{
		for (int j = 0; j < col[i]; ++j)
		{
			printf("%s  ", Arr[i][j]);
		}
		printf("\n");
	}
}


//================================================================
char *Find_Root(char Arr[SIZE][SIZE][SIZE], int *row)
{
	char *root;

	root = malloc(SIZE * sizeof(char *));

	for (int i = 0; i < (*row); ++i)
	{
		strcpy(root, Arr[i][0]);

		for (int j = 0; j < (*row); ++j)
		{
			/* search for the index 1 that is second column */
			if (strcmp(root, Arr[j][1]) == 0)
			{
				strcpy(root, Arr[j][0]);
			}
		}
	}
	return root;
}


//================================================================
NODE *New_Node(char *word)
{
	NODE *new_node = malloc(sizeof(NODE));

	if (new_node != NULL)
	{
		new_node->near = NULL;
		new_node->sub  = NULL;
		new_node->per  = NULL;
		new_node->dady  = NULL;
		strcpy(new_node->name, word);
	}

	return new_node;
}

//================================================================
NODE *New_Near_Node(NODE *node, char *word)
{

	NODE *temp; 

	if (node == NULL)
	{
		return NULL;
	}

	/* goto last node */
	while (node->near)
	{
		node = node->near;
	}

	temp = New_Node(word);
	node->near = temp;
	temp->per = node;

	return node->near;
}

//================================================================
NODE *New_Sub_Dir(NODE *node, char *word)
{

	NODE *temp;

	if (node == NULL)
	{
		return NULL;
	}
	/* Ternary operator */
	/* If node->sub != NULL */
	/* If node->sub == NULL create newnode*/
	if (node->sub) {
		temp = New_Near_Node(node->sub, word);
		

		return temp;
	}
	else {
		temp = New_Node(word);

		temp->dady = node;
		temp->per = node;
		node->sub = temp;
		

		return node->sub;
	}
}

//================================================================
/* Check the sub directories is exist in the up dir(parent) */
int Check_SameSub(NODE *top, char *word)
{
	int  i  = 0;
	NODE *p = top;

	if (top != NULL)
	{
		/* p->sub != NULL it means that p has sub. It is not a file, it is directory */
		if (p->sub == NULL)
		{
			return 0;
		}

		if (strcmp(p->sub->name, word) == 0)
		{
			return 1;
		}

		p = p->sub;
		while (p->near != NULL)
		{
			if (p->near)
			{
				/* Check the near nodes is exist in same directory */
				if (strcmp(p->near->name, word) == 0)
				{
					return 1;
				}
				p = p->near;
			}
		}
	}

	return 0;
}


//================================================================
void Display_Tree(NODE *node)
{
	NODE *temp = node;
	int  flag  = 0;
	char baba[50];

	if (temp == NULL)
	{
		return;
	}

	strcpy(baba, node->name);

	while (temp)
	{
		if (flag == 0)
		{
			temp = temp->sub;
			printf(" \t%s -- %s\n", baba, temp->name);
			flag = 1;
		}
		else
		{
			temp = temp->near;
			if (temp)
			{
				printf(" \t%s -- %s\n", baba, temp->name);
			}
		}
		Display_Tree(temp);
	}
}

//================================================================
void Create_Tree_Structure(NODE *root, char Arr[SIZE][SIZE][SIZE], int col[], int *row)
{
	NODE *temp = root;
	int  flag  = 0;

	if (root == NULL)
	{
		return;
	}

	for (int i = 0; i < *row; ++i)
	{
		for (int j = 0; j < col[i] - 1; ++j)
		{
			if (strcmp(root->name, Arr[i][j]) == 0)
			{
				if (Check_SameSub(root, root->name) != 1)
				{
					New_Sub_Dir(root, Arr[i][j + 1]);
				}

				if (flag == 0)
				{
					temp = root->sub;
					flag = 1;
				}
				else
				{
					temp = temp->near;
				}

				Create_Tree_Structure(temp, Arr, col, row);
			}
		}
	}
}

//================================================================
void Read_Command(char Arr[SIZE][SIZE][SIZE], int col[], int *row)
{
	FILE *fp = fopen("commands.txt", "r");
	char *tok;
	char temp[SIZE];
	int  i = 0, j = 0;

	while (fgets(temp, SIZE, fp) != NULL)
	{
		tok = strtok(temp, " \n");
		while (tok != NULL)
		{
			strcpy(Arr[i][j++], tok);

			tok = strtok(NULL, " \n");
		}
		col[i] = j;
		i++;
		j = 0;
	}

	(*row) = i;
}

void CommandToken(char *WORD, char Tokens[SIZE][SIZE], int *size, int *isRoot) {

	int i = 0;

	char WORD2[SIZE], *temp;

	strcpy(WORD2, WORD);


	if (WORD2[0] == '/') {
		*isRoot = 1;
	}
	else {
		*isRoot = 0;
	}

	temp = strtok(WORD2, "/");
	
	if (temp != NULL) {
		strcpy(Tokens[i++], temp);
	}

	while (temp != NULL)
	{ 

		temp = strtok(NULL, "/");
		if (temp != NULL) {
			strcpy(Tokens[i++], temp);
		}
		
	}
	*size = i;
}

void printTokens(char Tokens[SIZE][SIZE], int size, int isRoot) {



	for (int i = 0; i < size; ++i)
	{
		printf("%s ", Tokens[i]);
	}
 
 	printf("%d", isRoot);

	printf("\n");
}

NODE *child(NODE *root, char *WORD) {

	NODE *Current = root;

	if (Current == NULL)
		return NULL;

	if (Current->sub == NULL)
		return NULL;

	if (strcmp(Current->sub->name, WORD) == 0)
		return Current->sub;

 	Current = Current->sub;

	while (Current->near)
	{
		if (strcmp(Current->near->name, WORD) == 0)
			return Current->near;

		Current = Current->near;
	}

	return NULL;
}

NODE * WantedNode(NODE *root, NODE *Current, char Tokens[SIZE][SIZE], int isRoot, int size) {

	NODE *temp;

	if (isRoot)
	{
		temp = root;
	} else {
		temp = Current;
	}

	if (isRoot && size == 0) {
		return root;

	}
	
	if (isRoot) {

		for (int i = 1; i < size; ++i)
		{
			temp = child(temp, Tokens[i]);
			//printf("%s\n", temp->name);
		}
	}
	else {
		for (int i = 0; i < size; ++i)
		{
			temp = child(temp, Tokens[i]);
			//printf("%s\n", temp->name);
		}
	}

	return temp;
}

NODE * cd(NODE *root, NODE *Current, char Tokens[SIZE][SIZE], int isRoot, int size)
{
	
	if (isRoot && size == 0) {
		Current = root;
	}
	else if (strcmp(Tokens[0], "..") == 0)
	{
		Current = Current->per;
	}
	else
	{	

		if (isRoot) {
			for (int i = 1; i < size; ++i)
			{
				Current = child(Current, Tokens[i]);

			}
		}
		else {
			for (int i = 0; i < size; ++i)
			{
				Current = child(Current, Tokens[i]);

			}
		}

		
	}
	return Current;
}

void DoCommands(NODE *root, char Arr[SIZE][SIZE][SIZE], int row) {
 
	char Tokens[SIZE][SIZE];
	int size;
	int isRoot;

	NODE *Current = root;
	NODE *tempA, *tempB, *del;

	for (int i = 0; i < row; ++i)
	{

		if (strcmp(Arr[i][0], "copy") == 0) {

			CommandToken(Arr[i][1], Tokens, &size, &isRoot);

			tempA = WantedNode(root, Current, Tokens, isRoot, size);

			CommandToken(Arr[i][2], Tokens, &size, &isRoot);

			tempB = WantedNode(root, Current, Tokens, isRoot, size);

			//printf("%s %s\n", tempB->name, tempA->name );

			New_Sub_Dir(tempB, tempA->name);

			
		}else if (strcmp(Arr[i][0], "move") == 0) {

			CommandToken(Arr[i][1], Tokens, &size, &isRoot);

			tempA = WantedNode(root, Current, Tokens, isRoot, size);

			CommandToken(Arr[i][2], Tokens, &size, &isRoot);

			tempB = WantedNode(root, Current, Tokens, isRoot, size);

			New_Sub_Dir(tempB, tempA->name);

			//tempA->per->near = tempA->near;

			if (tempA->dady != NULL) {
				//printf("var %s\n", tempA->dady->name);

				if (tempA->near != NULL) {
					tempA->near->dady = tempA->dady;
					tempA->dady->sub = tempA->near;
				} else {
					tempA->dady->sub = NULL;
				}


				//tempA->dady->sub = tempA->near;
			}
			else{
				//printf("yok %s\n", tempA->name);
				tempA->per->near = tempA->near;
			}

		} else if (strcmp(Arr[i][0], "delete") == 0) {

			CommandToken(Arr[i][1], Tokens, &size, &isRoot);

			tempA = WantedNode(root, Current, Tokens, isRoot, size);

			//printf("%s\n", tempA->name);
			
			if (tempA->dady != NULL) {
				//printf("var %s\n", tempA->dady->name);

				if (tempA->near != NULL) {
					tempA->near->dady = tempA->dady;
					tempA->dady->sub = tempA->near;
				} else {
					tempA->dady->sub = NULL;
				}


				//tempA->dady->sub = tempA->near;
			}
			else{
				//printf("yok %s\n", tempA->name);
				tempA->per->near = tempA->near;
			}
			
		



		} else if (strcmp(Arr[i][0], "cd") == 0) {

			CommandToken(Arr[i][1], Tokens, &size, &isRoot);


			//printf("size %d isRoot %d \n", size, isRoot);
			Current = cd(root, Current, Tokens, isRoot, size);

			//printf("%s --- %s\n", root->name, Current->name);
		}
	}

}


