/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:13:12 by mlaffita          #+#    #+#             */
/*   Updated: 2025/06/02 15:46:09 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

t_bool	is_valid_av( char *str);
int count_min_space(char *str);
t_bool is_balanced(char *retour);
t_bool	rip(char *str, char *retour, int min_space, int space_count, int i);
int ft_strlen(char *str);

int main (int ac, char **av)
{	
	// step 1 : verif des arguments, si pas vide et si valide
	if (ac != 2 || av[1][0] == '\0' || is_valid_av(av[1]) == FALSE)
		return (1);

	// step 2 : init min space et str de retour
	int min_space = count_min_space(av[1]);
	char retour[(ft_strlen(av[1]))+ 1];

	// step 3 : fonction de recursion 
	rip(av[1], retour, min_space, 0, 0); // on lui passe la str recue, les 2 init et les 2 count a zero
	return (0);
}

t_bool	is_valid_av( char *str) // seulement pour check si ce qu'on recoit en arg est valide
{
	int i = 0;
	while (str[i])
	{
		if (str[i] != '(' && str[i] != ')') // parentheses ONLY
			return FALSE;
		i++;
	}
	return TRUE;
}

int count_min_space(char *str) // on compte le min space car besoin apres pour resultats
{
	int count = 0;
	int balance = 0;
	int i = 0;

	while (str[i])
	{
		if (str[i] == '(')
			balance++;
		else if (str[i] == ')')
		{
			if (balance == 0)
				count++;
			else
				balance--;
		}
		i++;
	}
	return ( count + balance);
}
int ft_strlen(char *str)
{
	int i  = 0;
	while ( str[i])
		i++;
	return(i);
}

t_bool is_balanced(char *retour) // pour verif si la fonction est equilibree
{
	int i = 0;
	int balance = 0;
	
	while (retour[i])
	{
		if (retour[i] == '(')
			balance++;
		else if (retour[i] == ')')
		{
			if (balance == 0)
				return FALSE;
			balance--;
		}
		i++;
	}
	if (balance == 0)
		return TRUE;
	return FALSE;
}
t_bool	rip(char *str, char *retour, int min_space, int space_count, int i)
{
	// la condition de sortie 
	if (str[i] == '\0') // si on arrive a la fin
	{
		retour[i] = '\0'; // on termine la str 
		if (is_balanced(retour) == TRUE && space_count == min_space) // si c'est bien balanced ET que space ok
			puts(retour); // alors on print
		return TRUE;
	}
	
	// recursion 1er branche a gauche
	retour[i] = ' '; // remplace par espace
	rip(str, retour, min_space, space_count + 1, i + 1); // +1 pour count space ET pour i !!

	// recursion 2eme branche a droite
	retour[i] = str[i]; // on laisse la parenthese actuelle
	rip(str, retour, min_space, space_count, i + 1); // +1 juste pour le i 

	return FALSE;
}
