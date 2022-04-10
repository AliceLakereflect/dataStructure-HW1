#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

int ROW, COL;

int arr[10][10];

// Directions
int dx[9] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };
int dy[9] = { 0, 0, 0, -1, -1, -1, 1, 1, 1 };

#define MAXM 10
#define MAXN 10

bool check(int x, int y)
{
     // x, y should be greater then 0
     // x, y should be less than matrix size
	return (x >= 0 && y >= 0 && x < ROW && y < COL);
}

void printMatrix(bool matrix[MAXN][MAXM])
{
     // print matrix if exist bomb
	for (int row = 0; row < ROW; row++) {
		for (int col = 0; col < COL; col++) {
			if (matrix[row][col])
				printf("%d, %d\n", row+1, col+1);
		}
	}
}

bool isSafe(int arr[MAXN][MAXM], int x, int y)
{
     // check matrix index is valid
	if (!check(x, y))
		return false;

     // check matrix index is valid even if it is moved
	for (int i = 0; i < 9; i++) {
		if (check(x + dx[i], y + dy[i])
			&& (arr[x + dx[i]][y + dy[i]] - 1 < 0))
			return false;
	}

     // if valid, reduce bombs number
	for (int i = 0; i < 9; i++) {
		if (check(x + dx[i], y + dy[i]))
			arr[x + dx[i]][y + dy[i]]--;
	}

	return true;
}

bool findUnvisited(bool visited[MAXN][MAXM],int& x, int& y)
{
	for (x = 0; x < ROW; x++)
		for (y = 0; y < COL; y++)
			if (!visited[x][y])
				return true;
	return false;
}

bool isDone(int arr[MAXN][MAXM],bool visited[MAXN][MAXM])
{
	bool done = true;
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
               // mark as done when bomb's cound == 0 and is visited
               // all the positions has to be visited, or 'done' is false;
			done = done && arr[i][j] == 0 && visited[i][j];
		}
	}

	return done;
}

bool bombFinder(bool matrix[MAXN][MAXM],int arr[MAXN][MAXM],bool visited[MAXN][MAXM])
{
     // check if searching is complete
	bool done = isDone(arr, visited);

     // finish and return
	if (done)
		return true;

	int x, y;

	// check if all the positions are visited or not
	if (!findUnvisited(visited, x, y))
		return false;

	// Mark cell (x, y) as visited
	visited[x][y] = true;

	// check if safe to calculate
	if (isSafe(arr, x, y)) {
		// Mark the position with a bomb
		matrix[x][y] = true;

		// Recursive call with (x, y) having a bomb
		if (bombFinder(matrix, arr, visited))
			// If solution exists, then return true
			return true;

          // Reset position (x,y)
		matrix[x][y] = false;
		for (int i = 0; i < 9; i++) {
			if (check(x + dx[i], y + dy[i]))
				arr[x + dx[i]][y + dy[i]]++;
		}
	}

	// Recursive call without (x, y) having a bomb
	if (bombFinder(matrix, arr, visited))
		// If solution exists then return true
		return true;

	visited[x][y] = false;

	// If no solution exists
	return false;
}

void WriteOutput(char filename[], bool matrix[MAXN][MAXM]){
    
     FILE *file = fopen (filename, "w+");
     if (file == NULL)
     {
          fprintf(stderr, "\nCouldn't Open File'\n");
          exit (1);
     }

     // print matrix if exist bomb
	for (int row = 0; row < ROW; row++) {
		for (int col = 0; col < COL; col++) {
			if (matrix[row][col])
                    fprintf(file, "%d, %d\n", row+1, col+1); 
		}
	}

     if(&fwrite != 0)
     {
          printf("Output store in the file successfully\n");
     }
          else
     {
          printf("Error While Writing\n");
     }
     
     fclose(file);
    
}

int main()
{
	int m,n,B;
     FILE * database;
     database = fopen("test.txt", "r");

     if (NULL == database)
     {
          perror("opening database");
          return (-1);
     }

     fscanf(database, "%d %d", &m, &n);
     ROW = m;
     COL = n;
     printf("> m=%d n=%d\n", ROW, COL);
     fscanf(database, "%d", &B);
     printf("> B=%d\n", B);

	printf("Scan bomb hint:\n");
	for (int x = 0; x < ROW; x++) {
		for (int y = 0; y < COL; y++) {
			arr[x][y] = 0;
			fscanf(database, "%d", &arr[x][y]);
			printf("%d ",arr[x][y]);
		}
		printf("\n");
	}

     // 2 temp matrix to save the status 
     bool matrix[MAXN][MAXM];
	bool visited[MAXN][MAXM];
	memset(matrix, false, sizeof(matrix));
	memset(visited, false, sizeof(visited));

     // recursively call the bombFinder to search
     // bombFinder return true when all positions are searched
	if (bombFinder(matrix, arr, visited)) {
		// Function call to print the matrix[][]
		printMatrix(matrix);
	}
	else
		printf("No solution exists\n");

     fclose(database);
     char fileName[30] = "output.txt";
     WriteOutput(fileName, matrix);
     return (0);
}
