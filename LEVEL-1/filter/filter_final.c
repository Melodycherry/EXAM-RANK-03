/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_final.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 08:42:38 by mlaffita          #+#    #+#             */
/*   Updated: 2025/05/14 08:43:05 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static void    filter(char *buffer, char *key);

int main(int ac, char **av)
{
	char	c;
    char    *buffer;
    ssize_t bytes_read; // car signed size type, pour le eventuel -1 en cas d'erreur
	int		buffer_size = 0;

    // etape 1 : verification de l entree argument
    if (ac != 2 || av[1][0] == '\0')
        return (1);
    // etape 2 : allocation du buffer, verif et initatilisation a 0
    buffer = calloc(1, sizeof(char));	// plus safe, remplis de 0 -> donc pas besoin de '\0'
    if (!buffer)
        return (perror("Error"), 1);
    // etape 3 : reallocation du buffer a chaque iteration jusqua la fin +verif
	while ((bytes_read = read(STDIN_FILENO, &c, 1)) > 0) // attention parenthese !
	{
		buffer = realloc(buffer, buffer_size + 2); // + 2 ? Pour eviter overflow et undefined behavior ?
		if (!buffer)
			return (perror("Error"), free(buffer), 1);
		buffer[buffer_size] = c;
		buffer_size++;					// Incremente avant le '\0'
		buffer[buffer_size] = '\0';		// Attention ne pas oublier cette fois le'\0'
	}
    // etape 4 : remplacer le mot par des ***
    filter(buffer, av[1]);
    free(buffer);
    return (0);
}

static void    filter(char *buffer, char *key)
{
    int i = 0;
    int j = 0;

    while(buffer[i])
    {
		// compare char by char entre buff et key
        while (buffer[i + j] == key[j] && buffer[i + j] && key[j])
            j++;
        if (key[j] != '\0') // si on a pas match tt le mot
            j = 0;
        if (j != 0) // si on trouve la correspondance complete 
        {
            int k = 0;
            while (k < j)
            {
                printf("%c", '*');
                k++;
            }
            i += j; // pour skip les char remplaces 
            j = 0;
        }
        else // si pas de correspondance on affiche normalement
            printf("%c", buffer[i++]);
    }
}
