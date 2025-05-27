/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:05:40 by mlaffita          #+#    #+#             */
/*   Updated: 2025/04/25 17:07:31 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFFER_SIZE 42

// Écrit une chaîne sur la sortie d'erreur (stderr)
void ft_putstr_fd(char *str)
{
    int i = 0;
    if (!str)
        return ;
    while (str[i])
    {
        write(2, &str[i], 1);
        i++;
    }
}
// Renvoie la longueur d'une chaîne
int ft_strlen(char *str)
{
    int i = 0;
	
    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}
// Compare les n premiers caractères de s1 et s2
int	ft_strncmp(const char *s1, const char *s2, int n)
{
	int	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s2[i] != '\0' && i < n - 1)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// Alloue une mémoire initialisée à 0 (comme calloc standard)
char *ft_calloc(int count, int size)
{
    char *new;
    int i = 0;

    new = malloc(count * size);
    if (!new)
        return NULL;
    while (i < count * size)
    {
        new[i] = '\0';
        i++;
    }
    return (new);
}
// Affiche un message d'erreur, libère line et buf si présents
void    *ft_error(char *msg, char **line, char **buf)
{
    if (msg)
    {
        ft_putstr_fd("Error : ");
        ft_putstr_fd(msg);
        ft_putstr_fd("\n");
    }
    if (line && *line)
    {
        free(*line);
        *line = NULL;
    }
    if (buf && *buf)
    {
        free(*buf);
        *buf = NULL;
    }
    return (NULL);
}
// Vérifie si une ligne contient un '\n'
int is_newline(char *str)
{
    int i = 0;
    if (!str)
        return (0);
    while (str[i])
    {
        if (str[i] == '\n')
            return (1);
        i++;
    }
    return (0);
}
// Concatène *line_p et *buf_p dans une nouvelle chaîne, et la retourne
char    *ft_strjoin(char **line_p, char **buf_p)
{
    int     i = 0;
    int     j = 0;
    char    *new;
    char *line = *line_p;
    char *buf = *buf_p;

    if (!line || !buf)
        return (NULL);
    new = ft_calloc(ft_strlen(line) + ft_strlen(buf) + 1, sizeof(char));
    if (!new)
        return (ft_error("malloc", line_p, buf_p));
    while (line[i])
    {
        new[i] = line[i];
        i++;
    }
    while (buf[j])
        new[i++] = buf[j++];
    return (new);
}
// Libère line après l’avoir concaténé avec buf
char    *join_and_free(char **line, char **buf)
{
    char    *tmp;

    tmp = ft_strjoin(line, buf);
    ft_error(NULL, line, NULL); // libère *line uniquement ???
	// car sa version mise à jour est maintenant dans tmp
	// On libere pas buf car va servir pour les prochains read
    return (tmp);
}
// Remplace toutes les occurrences de sep dans line par un '*'
void replace(char *line, char *sep)
{
    int i = 0;
    int sep_len = ft_strlen(sep);

    while (line[i])
    {
        // Si on trouve une séquence correspondant à sep
        if (ft_strncmp(&line[i], sep, sep_len) == 0)
        {
            write(1, "*", 1);
            i += sep_len;
        }
        else
            write(1, &line[i++], 1);
    }
}
// Gère le cas où une ligne complète est trouvée (\n), puis la remplace
int handle_word(char **line, char **buf, char *sep)
{
    if (is_newline(*line))
    {
        replace(*line, sep);
        ft_error(NULL, line, NULL);
        *line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
        if (*line == NULL)
            return (ft_error("malloc", line, buf), 1);
    }
    return (0);
}
// Fonction principale : lit stdin, cherche les séparateurs, les remplace par '*'
char    *ft_filter(char *sep)
{
    char    *line;
    char    *buf;
    int     ret;

    line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
    ret = 1;
    if (!line || !buf)
        return (ft_error("malloc", &line, &buf));
    while (ret > 0)
    {
        ret = read(0, buf, BUFFER_SIZE);
        if (ret == -1)
            return (ft_error("malloc", &line, &buf));
        buf[ret] = '\0';
        line = join_and_free(&line, &buf);
        if (!line)
            return (ft_error(NULL, &line, &buf));
        if (handle_word(&line, &buf, sep))
            return (NULL);
    }
    return (ft_error(NULL, &line, &buf));
}

int main(int argc, char **argv)
{
    if (argc == 1)
        return (0);
    if (argc > 2)
        return (0);
    ft_filter(argv[1]);
}
