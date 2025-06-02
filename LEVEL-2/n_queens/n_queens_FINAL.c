/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_queens.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:11:59 by mlaffita          #+#    #+#             */
/*   Updated: 2025/06/02 12:44:56 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

typedef enum e_bool // pour pouvoir utiliser un booleen 
{
	FALSE,
	TRUE
}	t_bool;

t_bool	is_safe(int *chess_board, int col, int row);
void	queens(int *chess_board, int n, int col);

int main ( int ac, char **av)
{
	// step 1 : verif des arguments 
	if (ac != 2)
	{
		fprintf(stderr, "Error: usage ./queens n");
		return 1;
	}
	// step 2 : converti n, et creation de chessboard
	int n = atoi(av[1]);
	int chess_board[n];
	
	// step 3 : lance la recursion a partir de la premiere colonne 
	queens(chess_board, n, 0);
	return (0);
}

void	queens(int *chess_board, int n, int col) // place la reine dans le chessboard
{
	int i = 0;
	int row = 0;

	if (col >= n) // condition de sortie
	{
		while (i < n)
		{
			fprintf(stdout, "%d", chess_board[i]); // si soluce complete on la print 
			i++;
		}
		fprintf(stdout, "\n");
	}
	
	while ( row < n) // verif toutes les lignes de la colonne
	{
		if (is_safe(chess_board, col, row))
		{
			chess_board[col] = row; // enregistre le placement
			queens(chess_board, n, col + 1); // appel recursif pour la colonne suivante 
		}
		row++; // test ligne suivante 
	}
}

t_bool	is_safe(int *chess_board, int col, int row) // verif si on peut poser la reine
{
	int i = 0;
	while ( i < col)
	{
		if (chess_board[i] == row || chess_board[i] + i == row + col || chess_board[i] - i == row - col)
			return FALSE; // verif meme ligne, diagonale down, et diagonale up
		i++;
	}
	return TRUE; // si placement est sur
}

