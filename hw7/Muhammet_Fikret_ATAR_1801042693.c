#include <stdio.h>

#define VISITED 0 /* to mark 0, means that is checked before */
#define TO_ISLAND 1 /* converts numbers to 1 that are bigger than given water length */
#define ROW 512 /* Row number */
#define COL 512 /* Column number */
#define INIT 0

int readMap(int map[ROW][COL]); /* read the file and write to matrix */ 
int howManyIslandAreThere(int map[ROW][COL],  int L); /* find the number of island */
int isIsland(int map[ROW][COL], int r, int c,  int L); /* check the matrix index that is valid */
void islandPoints(int map[ROW][COL], int L); /* find and write the coordinates in the matrix */



int main(int argc, char const *argv[]) {

	int  L;
	int map[ROW][COL] = {INIT}; /* Matrix 2d array */

	/* L is length for water level */
	L = readMap(map);
	/* write coordinates */
	islandPoints(map, L);

	return 0;
}

void islandPoints(int map[ROW][COL], int L) {

	FILE *fp; /* file pointer */
	int i, j, sumOfIsland, temp;

	/* open file in write mode */
	fp = fopen("output.txt", "w");

	/* number of island calculated */
	sumOfIsland = howManyIslandAreThere(map, L);

	temp = sumOfIsland;

	fprintf(fp, "%d\n", sumOfIsland);

	for (i = 0; i < ROW; ++i)
		for (j = 0; j < COL; ++j)
			if (map[i][j] > L){
				temp--;
				if (temp > 0)
					fprintf(fp,"%d %d\n", i, j);
				else
					fprintf(fp,"%d %d", i, j);
			}
	fclose(fp);
}


/* check the indexes are valid or not */
int isIsland(int map[ROW][COL], int r, int c, int L) {

	if (r < 0  || c < 0 || r >= ROW || c >= COL || map[r][c] <= L)
		return TO_ISLAND;

	map[r][c] = L - 1;

	isIsland(map, r, c + 1, L);
	isIsland(map, r, c - 1, L);
	isIsland(map, r + 1, c, L);
	return isIsland(map, r - 1, c, L);
}

int howManyIslandAreThere(int map[ROW][COL], int L) {

	int r, c;
	int sumOfIsland = INIT;

	for (r = 0; r < ROW; ++r) {
		for (c = 0; c < COL; ++c) {
			if (map[r][c] > L) {
				sumOfIsland += isIsland(map, r, c, L);
				map[r][c] = L + 1;
			}
		}
	}
	return sumOfIsland;
}

int readMap(int map[ROW][COL]) {

	FILE *fp;  /* file pointer */
	int i = INIT, j = INIT;
	int L;
	 /* open file to read the text */
	fp = fopen("input.txt", "r");

	fscanf(fp, "%d", &L);
	while(!feof(fp))
	{
		fscanf(fp, "%d", &map[i][j]);
		j++;
		if (j == COL){
			i++;
			j = 0;
		}	
	}
	fclose(fp);

	return L;
}