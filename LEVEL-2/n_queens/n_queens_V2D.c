/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens_V2D.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:48:09 by mlaffita          #+#    #+#             */
/*   Updated: 2025/06/02 12:49:14 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Version de Pdemont avec utilisation de tableau 2D

#include <stdio.h>
#include <stdlib.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

void	init_chess_board(int n, int chess_board[n][n]);
t_bool	backtrack_queens(int n, int chess_board[n][n], int col);
t_bool	is_safe(int n, int chess_board[n][n], int row, int col);
void	print_solution(int n, int chess_board[n][n]);

int	main (int ac, char **av)
{
	if (ac != 2)
	{
		fprintf(stderr, "Usage ./n_queens <n>\n");
		exit(EXIT_FAILURE);
	}
	
	int		n = atoi(av[1]);
	int		chess_board[n][n];

	init_chess_board(n, chess_board);
	backtrack_queens(n, chess_board, 0);
	exit(EXIT_SUCCESS);
}

void	init_chess_board(int n, int chess_board[n][n])
{
	int i = 0;

	while (i < n)
	{
		int j = 0;
		while (j < n)
		{
			chess_board[i][j] = 0;
			j++;
		}
		i++;
	}
}

t_bool	backtrack_queens(int n, int chess_board[n][n], int col)
{
	int row = 0;
	
	if (col >= n)
		print_solution(n, chess_board);
	while (row < n)
	{
		if (is_safe(n, chess_board, row, col))
		{
			chess_board[row][col] = 1;
			if (backtrack_queens(n, chess_board, col + 1))
				return TRUE;
			chess_board[row][col] = 0;
		}
		row++;
	}
	return FALSE;
}

t_bool is_safe(int n, int chess_board[n][n], int row, int col)
{
	int	i = 0;
	int	j = 0;

	while (i < col)
	{
		if (chess_board[row][i])
			return FALSE;
		i++;
	}
	i = row;
	j = col;
	while (i > 0 && j > 0)
	{
		if (chess_board[i - 1][j - 1])
			return FALSE;
		i--;
		j--;
	}
	i = row;
	j = col;
	while (i < n && j >= 0)
	{
		if (chess_board[i][j])
			return FALSE;
		i++;
		j--;
	}
	return TRUE;
}

void	print_solution(int n, int chess_board[n][n])
{
	t_bool	is_first = TRUE;
	int	j = 0;

	while (j < n)
	{
		int i = 0;
		while (i < n)
		{
			if (chess_board[i][j])
			{
				if (is_first)
				{
					fprintf(stdout, "%d", i);
					is_first = FALSE;
				}
				else
					fprintf(stdout, " %d", i);
			}
			i++;
		}
		j++;
	}
	fprintf(stdout, "\n");
}