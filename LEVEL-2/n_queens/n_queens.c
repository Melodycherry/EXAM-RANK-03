#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// yes malloc and printf are allowed dw

void print_board(int *board, int n)
{
    int i = 0;
    while (i < n)
    {
        printf("%d",board[i]);
        if (i < n - 1)
            printf(" ");
        i++;    
    }
    printf("\n");	
}

int is_validate(int *board, int row, int col)
{
    int i = 0;
    while (i < row)
    {
        if (board[i] == col || board[i] - i == col - row || board[i] + i == col + row)
            return 0;
        i++;
    }
    return 1;
}

void nqueen(int n,int *board,int row)
{
    int col = 0;

    if (row == n)
    {
            print_board(board, n);
            return;
    }
    while (col < n)
    {
            if (is_validate(board, row, col))
            {
                board[row] = col;
                nqueen(n, board, row + 1);
            }
       col++;
    }
}

int main(int ac,char  **av)
{
    int n;
    if (ac == 2) {
        n = atoi(av[1]);
    }
    else {
        printf("\n");
        return 1;
    }
    int *board = malloc(sizeof(int) * n);
    if (board == NULL)
        return 1;
    int i = 0;
    while (i < n)
    {
        board[i] = 0;
        i++;
    }
    nqueen(n,board,0);
    free(board);
    return 0;
}
