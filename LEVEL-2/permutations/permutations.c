/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permutations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:12:17 by mlaffita          #+#    #+#             */
/*   Updated: 2025/06/09 15:34:08 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

int		ft_strlen(char *str);
void	bubble_sort(char *str, int len);
void	swap(char *a, char *b);
void	swap_current(char *str, int first, int last);
t_bool 	is_reverse(char *str, int len);
void	permut(char *str, int len);

int main ( int ac, char **av)
{
	// 1 step : verif
	if (ac != 2 || av[1][0] == '\0')
		return (1);

	// 2 step : init
	int len = ft_strlen(av[1]);
	char *str = av[1];

	// 3 step : bubble sort, print, permut
	bubble_sort(str, len);
	puts(str);
	permut(str, len);

	return (0);
}

void	permut(char *str, int len)
{
	int i;
	int j;
	
	// condition de sortie ! Si derniere permut on stop
	if (is_reverse(str, len))
		return;
	
		// reset i et j 
		i = len - 2;
		while ( i >= 0 && str[i] >= str[i +1]) // indice i du premiere caractere a droite qui peut etre augmente
			i--;
		j = len - 1;
		while (str[j] <= str[i]) // indice j du plus petit caractere a droite de i qui est plus grand que str[i]
			j--;
		
		// swap, swap current, print, recursive
		swap(&str[i], &str[j]); // on echange
		swap_current(str, i + 1, len - 1); // inverse la partie droite apres i
		puts(str); // affiche permut courante
		permut(str, len); // appel recursif 
}
int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}
void	bubble_sort(char *str, int len)
{
	int i = 0;
	int j;
	while ( i < len - 1)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (str[j] > str[j + 1])
				swap(&str[j], &str[j + 1]);
			j++;
		}
		i++;
	}
}
void	swap(char *a, char *b)
{
	char tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	swap_current(char *str, int first, int last)
{
	while (first < last)
	{
		swap(&str[first], &str[last]);
		first++;
		last--;
	}
}
t_bool is_reverse(char *str, int len)
{
	int i = 0;
	while (i < len - 1)
	{
		if (str[i] < str[i + 1])
			return FALSE;
		i++;
	}
	return TRUE;
}

