/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   broken_gnl_PAPIER_VERT.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlaffita <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:12:58 by mlaffita          #+#    #+#             */
/*   Updated: 2025/06/02 13:16:51 by mlaffita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Version broken, a debugguer 

#include "broken_gnl.h"

char *ft_strchr(char *s, int c);
void	*ft_memcpy(void *dest, const void *src, size_t n);
size_t ft_strlen(char *s);
int	str_append_mem(char **s1, char *s2, size_t size2);
int str_append_str(char **s1, char *s2);
void	*ft_memmove(void *dst, const void *src, size_t n);
char	*get_next_line(int fd);

char *ft_strchr(char *s, int c)
{
	int i = 0;
	while (s[i] != c)
		i++;
	if (s[i] == c)
		return s + i;
	else
		return NULL;
}
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	while (--n > 0)
		((char*)dest)[n - 1] = ((char*)src)[n - 1];
	return dest;
}
size_t ft_strlen(char *s)
{
	size_t ret = 0;
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
	free(*s1);
	*s1 = tmp;
	return (1);
}
int str_append_str(char **s1, char *s2)
{
	return str_append_mem(s1, s2, ft_strlen(s2));
}
void	*ft_memmove(void *dst, const void *src, size_t n)
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
	static char b[BUFFER_SIZE + 1] = " ";
	char	*ret = NULL;
	char *tmp = ft_strchr(b, '\n');
	while (!tmp)
	{
		if(!str_append_str(&ret, b))
			return NULL;
		int read_ret = read(fd, b, BUFFER_SIZE);
		if (read_ret == -1)
			return NULL;
		b[read_ret] = 0;
	}
	if (!str_append_mem(&ret, b, tmp - b + 1))
	{
		free(ret);
		return NULL;
	}
	return ret;
}
