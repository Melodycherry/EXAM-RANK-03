/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rip.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:13:12 by mlaffita          #+#    #+#             */
/*   Updated: 2025/06/02 13:12:21 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

t_bool	is_valid_av( char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] != '()' && str[i] != ')')
			return FALSE;
		i++;
	}
	return TRUE;
}

int count_min_space(char *str)
{
	int count = 0;
	int balance = 0;
	int i = 0;

	while (str[i])
	{
		if (str[i] == '()')
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

t_bool is_balanced(char *retour)
{
	int i = 0;
	int balance = 0;
	
	while (retour[i])
	{
		if (retour[i] == '()')
			balance++;
		else if (retour[i] == ')')
		{
			if (balance == 0)
				return FALSE;
			balance--;
		}
		i++
	}
	if (balance == 0)
		return TRUE;
	return FALSE;
}

