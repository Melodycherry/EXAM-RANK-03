/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brocken_gnl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:05:13 by mlaffita          #+#    #+#             */
/*   Updated: 2025/04/15 11:43:15 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> // ( pour test ) 
#include <unistd.h> // read et close
#include <fcntl.h> // open
#include <stdlib.h> // malloc free

#define BUFFER_SIZE 42 // taille du buffer de lecture 


// libere pointeur et retourne NULL
void    *ft_free(char **buffer, char **line)
{
    if (buffer && *buffer)
    {
        free(*buffer);
        *buffer = NULL;
    }
    if (line && *line)
    {
        free(*line);
        *line = NULL;
    }
    return (NULL);
}

// alloue memoire et initialise a zero 
char    *ft_calloc(int count, int size)
{
    char    *new;
    int      i;

    new = malloc(count * size);
    if (!new)
        return (NULL);
    i = 0;
    while (i < count * size)
        new[i++] = '\0';
    return (new);
}

// verifie si une chaine contient un '\n'
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

// calcul la longueur d'une chaine
int ft_strlen(char *str)
{
    int i = 0;

    if (!str)
        return (0);
    while (str[i])
        i++;
    return (i);
}

// // Concatène deux chaînes, retourne la nouvelle, sans libérer les originales
char    *ft_strjoin(char *s1, char *s2)
{
    int     i = 0;
    int     j = 0;
    char    *new;

    if (!s1 || !s2)
        return (NULL);
    new = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
    if (!new)
        return (NULL);
    while (s1[i])
    {
        new[i] = s1[i];
        i++;
    }
    while (s2[j])
        new[i++] = s2[j++];
    return (new);
}

// Concatène buffer + line, libère l'ancien buffer
char    *join_and_free(char **buffer, char *line)
{
    char *tmp = ft_strjoin(*buffer, line);
    ft_free(buffer, NULL);
    return (tmp);
}

// Extrait une ligne (avec ou sans '\n') depuis le buffer
char    *extract_line(char **buffer_p)
{
    char    *buffer = *buffer_p;
    char    *new;
    int     i = 0;

    if ((*buffer_p)[0] == '\0')
        return (NULL);
    while (buffer[i] && buffer[i] != '\n')
        i++;
	// // Alloue +2 si \n présent, +1 sinon
    new = ft_calloc(buffer[i] == '\n' ? i + 2 : i + 1, sizeof(char));
    if (!new)
        return (ft_free(buffer_p, NULL));
    i = 0;
    while (buffer[i] && buffer[i] != '\n')
    {
        new[i] = buffer[i];
        i++;
    }
    if (buffer[i] == '\n')
        new[i] = '\n';
    return (new);
}

// Récupère le reste du buffer après la ligne extraite
char    *find_next_line(char **buffer_p)
{
    char    *buffer = *buffer_p;
    char    *new;
    int     i = 0;
    int     j = 0;

    if ((*buffer_p)[0] == '\0')
        return (ft_free(buffer_p, NULL));
    while (buffer[i] && buffer[i] != '\n')
        i++;
    if (buffer[i] == '\0') // Pas de \n -> plus rien à lire
        return (ft_free(buffer_p, NULL));
    i++; // passer le '\n'
    new = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
    if (!new)
        return (ft_free(buffer_p, NULL));
    while (buffer[i])
        new[j++] = buffer[i++];
    ft_free(buffer_p, NULL);
    return (new);
}

// Fonction principale : lit et retourne la ligne suivante depuis fd
char    *get_next_line(int fd)
{
    static char *buffer; // buffer statique conservé entre les appels
    char        *line;
    int         ret; // retrun value , pour stocker le result de read, combien d'octet lus

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (ft_free(&buffer, NULL));
    if (!buffer)
        buffer = ft_calloc(1, 1); // init du buffer
    line = ft_calloc(BUFFER_SIZE + 1, sizeof(char)); // +1 pour le '\0'
    if (!buffer || !line)
        return (ft_free(&buffer, &line));
    ret = 1;
    while (ret > 0 && !is_newline(buffer)) // tant qu'on lit encore et qu'on a pas trouve \n ds le buff 
    {
        ret = read(fd, line, BUFFER_SIZE);
        if (ret == -1)
            return (ft_free(&buffer, &line));
        line[ret] = '\0'; // null-terminate la chaîne lue
        buffer = join_and_free(&buffer, line); // on concatène ce qu’on a lu à buffer 
		//(qui contient peut-être déjà une partie de ligne)
        if (!buffer)
            return (ft_free(NULL, &line));
    }
    ft_free(NULL, &line); // libere temporaire
    line = extract_line(&buffer); // extrait la ligne a retourner
    buffer = find_next_line(&buffer); // prépare le buffer pour l'appel suivant
	// met à jour le buffer en supprimant la ligne qu’on vient d’extraire
	// en gardant ce qui vient après pour le prochain appel
    return (line);
}

// Main de test : affiche chaque ligne de chaque fichier donné en argument
int main(int argc, char **argv)
{
    int     fd;
    char    *line;
    int     i;

    i = 1;
    while (i < argc)
    {
        fd = open(argv[i], O_RDONLY);
        if (fd < 0)
        {
            perror("open");
            i++;
            continue;
        }
        while ((line = get_next_line(fd)))
        {
            printf("%s", line);
            free(line);
        }
        close(fd);
        i++;
    }
    return (0);
}

/**
 * @brief Fonction get_next_line — Résumé par étape
 * 
 * Appel initial
 * Si c’est le premier appel : → Le buffer est initialisé à une chaîne vide ("").
 * 
 * Lecture du fichier
 * Tant que le buffer ne contient pas de \n 
 * On lit jusqu’à BUFFER_SIZE octets dans le fichier.
 * On ajoute ce qu’on lit à la fin du buffer.
 * Si une erreur de lecture survient → on libère et retourne NULL.
 * 
 * Dès qu’un \n est trouvé (ou fin de fichier)
 * On extrait une ligne depuis le début du buffer : Comprend tout jusqu’au \n, ou la fin si pas de saut de ligne.
 * On met à jour le buffer :
 * On supprime la ligne extraite du buffer.
 * On garde le reste (si y’en a) pour le prochain appel.
 * 
 * Retour
 * On retourne la ligne extraite
 * Si le fichier est fini et plus rien à lire : La fonction retourne NULL.
 * 
 */

/**
 * NOTE :
 * buffer est statique : Il garde en mémoire ce qui a été lu mais pas encore retourné.
 * Mémoire temporaire (ligne lue) est libérée quand il faut.
 * Pour les appels suivants : Le buffer reprend là où il s’est arrêté.
 * On continue ligne par ligne, jusqu’à la fin du fichier.
 */