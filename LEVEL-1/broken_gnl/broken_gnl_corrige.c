#include "broken_gnl.h"

char *ft_strchr(char *s, int c)
{
	int i = 0;
	while (s[i] && s[i] != c) // ajout verif de fin de str
		i++;
	if (s[i] == c)
		return s + i;
	else
		return NULL;
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int	i = 0;		// Travailler avec i
	while (i < n)
	{
		((char*)dest)[i] = ((char*)src)[i];
		i++;
	}
	return dest;
}

size_t ft_strlen(char *s)
{
	size_t ret = 0;
	if (!s)		// ajout verif si s existe
		return 0;
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
	if (*s1) 		// securise si jamais s1 est null 
		free(*s1);
	*s1 = tmp;
	return (1);
}

int str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, ft_strlen(s2));
}

void	*ft_memmove(void *dst, const void *src, size_t n)	//OSEF
{
	if (dst > src)
		return ft_memcpy(dst, src, n);
	else if (dst == src)
		return dst;
	size_t i = ft_strlen((char*)src) - 1;
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
	char 	*tmp = ft_strchr(b, '\n');
	
	while (!tmp)
	{
		if(!str_append_str(&ret, b))
			return NULL;
		int read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
		{
			free(ret); // ne pas oublier de freeeee
			return NULL;
		}
		if (read_ret == 0)
		{
			if (ret && *ret)
				break;
			free(ret);
			return NULL;
		}
		b[read_ret] = 0;
		tmp = ft_strchr(b, '\n'); // renomer variable car ca retourne la POSITION du '\n
	}
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return NULL;
	}
	ft_memcpy(b, tmp + 1, ft_strlen(tmp + 1) + 1);	// initialiser le buffer
	return ret;
}

// char	*get_next_line(int fd)
// {
// 	static char b[BUFFER_SIZE + 1] = {0}; // mettre des zero partout a la place des espaces 
// 	char	*ret = NULL;
// 	char 	*pos = NULL; // juste initialiser a null et fonction ds la boucle apres 
// 	
// 	while (!pos)
// 	{
// 		pos = ft_strchr(b, '\n'); // renomer variable car ca retourne la POSITION du '\n
// 		if (pos)
// 		{
// 			if (!str_append_mem(&ret, b, pos - b + 1))
// 			{
// 				free(ret);
// 				return NULL;
// 			}
// 			ft_memcpy(b, pos + 1, ft_strlen(pos + 1) + 1);
// 		}
// 		else
// 		{
// 			if(!str_append_str(&ret, b))
// 				return NULL;
// 			int read_ret = read(fd, b, BUFFER_SIZE);
// 			if (read_ret == -1)
// 			{
// 				free(ret); // ne pas oublier de freeeee
// 				return NULL;
// 			}
// 			if (read_ret == 0)
// 			{
// 				if (ret && *ret)
// 					break;
// 				free(ret);
// 				return NULL;
// 			}
// 			b[read_ret] = 0;
// 		}
// 	}
// 	return ret;
// }

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
