#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void pretty_print(int *board, int n)
{
    int row, col;
    for (row = 0; row < n; row++)
    {
        for (col = 0; col < n; col++)
        {
            if (board[col] == row)
                fprintf(stdout, "Q ");
            else
                fprintf(stdout, ". ");
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
}

void pretty_print_try(int *board, int n, int try_col, int try_row)
{
    int row, col;
    for (row = 0; row < n; row++)
    {
        for (col = 0; col < n; col++)
        {
            if (col == try_col && row == try_row)
                fprintf(stdout, "? ");
            else if (board[col] == row)
                fprintf(stdout, "Q ");
            else
                fprintf(stdout, ". ");
        }
        fprintf(stdout, "\n");
    }
    fprintf(stdout, "\n");
}

void print_board(int *board, int n)
{
    int i;
    fprintf(stdout, "Board: ");
    for (i = 0; i < n; i++)
        fprintf(stdout, "%d ", board[i]);
    fprintf(stdout, "\n");
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
        fprintf(stdout, "\033[1;32m=== SOLUTION TROUVÉE ===\033[0m\n");
        print_board(board, n);
        pretty_print(board, n);
        return;
    }
    fprintf(stdout, "\033[1;34m\n--- COLONNE %d ---\033[0m\n", col);
    while (row < n)
    {
    system("clear");
    fprintf(stdout, "Essai de placer une reine en colonne %d, ligne %d\n", col, row);
    fprintf(stdout, "(On vérifie seulement si cette nouvelle reine peut coexister avec les reines déjà placées)\n");
    pretty_print_try(board, n, col, row);
    board[col] = row;
    print_board(board, n);
    fprintf(stdout, "Appuie sur Entrée pour continuer...\n");
    getchar();
        if (check(board, col, row) == 0)
        {
            system("clear");
            fprintf(stdout, "\033[1;32mCette reine peut être placée ici (pas de conflit avec les reines précédentes) !\033[0m\n");
            fprintf(stdout, "Reine placée en colonne %d, ligne %d\n", col, row);
            pretty_print(board, n);
            print_board(board, n);
            fprintf(stdout, "Appuie sur Entrée pour passer à la colonne suivante...\n");
            getchar();
            solve(board, col + 1, n);
        }
        else
        {
            fprintf(stdout, "\033[1;31mCette reine ne peut pas être placée ici (conflit avec une reine précédente).\033[0m\n");
        }
        // On retire la reine pour le prochain essai (backtracking)
        board[col] = -1;
        row++;
    }
    fprintf(stdout, "\033[1;33mRetour arrière depuis colonne %d\033[0m\n", col);
}

int main(int argc, char **argv)
{
    if (argc != 2)
        return 1;
    int n = atoi(argv[1]);
    if (n < 1)
        return 1;

    char choice;
    do {
        int *board = malloc(sizeof(int) * n);
        if (!board)
            return 1;
        for (int i = 0; i < n; i++)
            board[i] = -1;

        solve(board, 0, n);
        free(board);

        fprintf(stdout, "\nVoulez-vous recommencer? (o/n): ");
        scanf(" %c", &choice);
        // Vider le buffer
        while (getchar() != '\n');

    } while (choice == 'o' || choice == 'O');

    return 0;
}
