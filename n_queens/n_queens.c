#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// void pretty_print(int *board, int n)
// {
//     int row, col;
//     for (row = 0; row < n; row++)
//     {
//         for (col = 0; col < n; col++)
//         {
//             if (board[col] == row)
//                 fprintf(stdout, "Q ");
//             else
//                 fprintf(stdout, ". ");
//         }
//         fprintf(stdout, "\n");
//     }
//     fprintf(stdout, "\n");
// }

void print(int *board, int n)
{
	int i = 0;
	while (i < n)
	{
		fprintf(stdout, "%d", board[i]);
		if (i < n - 1)
			fprintf(stdout, " ");
		else
			fprintf(stdout, "\n");
		i++;
	}
}

int check(int *board, int col, int row)
{
	int i = 0;
	while (i < col)
	{
		if (board[i] == row || board[i] - row == col - i || row - board[i] == col - i)
			return 1;
		i++;
	}
	return 0;
}

void solve(int *board, int col, int n)
{
	int row = 0;
	if (col == n)
	{
		print(board, n);
		// pretty_print(board, n);
		return ;
	}
	while (row < n)
	{
		if (check(board, col, row) == 0)
		{
			board[col] = row;
			solve(board, col + 1, n);
		}
		row++;
	}
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	int n = atoi(argv[1]);
	if (n < 1)
		return 1;
	int *board = malloc(sizeof(int) * n);
	if (!board)
		return 1;

	solve(board, 0, n);
	free(board);
	return 0;
}
