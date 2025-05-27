/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broken_gnl_TEST.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:52:31 by mlaffita          #+#    #+#             */
/*   Updated: 2025/05/27 17:49:19 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "broken_gnl.h"

char *ft_strchr(char *s, int c)
{
	int i = 0;
	while (s[i] != c && s[i]) // ajout verif de fin de strr
		i++;
	if (s[i] == c)
		return s + i;
	else
		return NULL;
}
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	while (n-- > 0) // attention , mettre post decrementation 
		((char*)dest)[n] = ((char*)src)[n]; // pas -1 car on a deja decrementer avant d'entrer dans la boucle 
	return dest;
}
size_t ft_strlen(char *s)
{
	size_t ret = 0;
	if (!s)
		return 0; // securisation ici 
	while (*s)
	{
		s++;
		ret++;
	}	
	return ret;
}
int	str_append_mem(char **s1, char *s2, size_t size2)
{
	size_t size1 = ft_strlen(*s1);
	char	*tmp = malloc(size2 + size1 + 1);
	if (!tmp)
		return (0);
	ft_memcpy(tmp, *s1, size1);
	ft_memcpy((tmp + size1), s2, size2);
	tmp[size1 + size2] = 0;
	if (*s1)
		free(*s1); // securise si jamais s1 est null 
	*s1 = tmp;
	return (1);
}
int str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, ft_strlen(s2));
}
void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if (!dst && !src)
		return (NULL); // securisation again 
	if (dst < src) // attention < 
		return ft_memcpy(dst, src, n);
	else if (n == 0 || dst == src) // attention 
		return dst;
	size_t i = ft_strlen((char*)src); // enlever le - 1 et faire 1 condition 
	if (i > 0)
		i = i - 1;
	while (i >= 0)
	{
		((char*)dst)[i] = ((char*)src)[i];
		i--;
	}
	return dst;
}
char	*get_next_line(int fd)
{
	static char b[BUFFER_SIZE + 1] = {0}; // mettre des zero partout a la place des espaces 
	char	*ret = NULL;
	char 	*pos = NULL; // juste initialiser a null et fonction ds la boucle apres 
	int 	read_ret = -1;
	
	while (!pos && read_ret != 0)
	{
		pos = ft_strchr(b, '\n'); // renomer variable car ca retourne la POSITION du '\n
		if (pos)
		{
			if (!str_append_mem(&ret, b, pos - b + 1))
			{
				free(ret);
				return NULL;
			}
			ft_memmove(b, pos + 1, ft_strlen(pos + 1) + 1);
		}
		else
		{
			if(!str_append_str(&ret, b))
			return NULL;
			read_ret = read(fd, b, BUFFER_SIZE);
			b[read_ret] = 0;
			if (read_ret == -1)
			{
				free(ret); // ne pas oublier de freeeee
				return NULL;
			}
			if (read_ret == 0 && b[0] == 0 && (!ret || ret == 0))
				return NULL;
			if (read_ret == 0)
				break;
		}
	}
	return ret;
}

//Ajout de mon main pour test

int main (int ac, char **av)
{
	int fd;
	char *line;
	
	fd = open(av[1], O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}