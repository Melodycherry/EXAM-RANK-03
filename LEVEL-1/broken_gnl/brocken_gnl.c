#include "get_next_line.h"

#include "get_next_line.h"

void *ft_memmove(void *dest, const void *src, size_t n)
{
    if (!dest || !src || n == 0)
        return dest;
    if (dest < src)
    {
        size_t i = 0;
        while (i < n)
        {
            ((unsigned char )dest)[i] = ((unsigned char)src)[i];
            i++;
        }
    }
    else if (dest == src)
        return dest;
    else
    {
        while (n > 0)
        {
            n--;
             ((unsigned char )dest)[n] = ((unsigned char)src)[n];
        }
    }
    return dest;
}
size_t ft_strlen(char *s)
{
    size_t ret = 0;
    if (!s)
        return 0;
    while (s[ret])
        ret++;
    return (ret);
}

int str_append_mem(char **s1, char *s2, size_t size2)
{
    if (!s1)
        return 0;
    if (!s2 || size2 == 0)  // Changed condition
        return 1;

    size_t size1 = 0;
    if (*s1 != NULL)  // Check if s1 is NULL before using it
        size1 = ft_strlen(s1);

    char *tmp = calloc(size2 + size1 + 1, 1);
    if (!tmp)
        return 0;

    if (*s1 != NULL)  // Only move memory if *s1 exists
        ft_memmove(tmp, *s1, size1);

    ft_memmove(tmp + size1, s2, size2);
    tmp[size1 + size2] = 0;

    if (*s1 != NULL)  // Only free if s1 exists
        free(s1);

    *s1 = tmp;
    return 1;
}
int str_append_str(char **s1, char *s2)
{
    return str_append_mem(s1,s2,ft_strlen(s2));
}

char *ft_strchr(char *str, char c)
{
    int i = 0;
    if (!str)
        return NULL;
    while (str[i])
    {
        if (str[i] == c)
            return str + i;
        i++;
    }
    return NULL;
}

char *ft_strdup(char *s)
{
    if (!s)
        return NULL;
    char *str = calloc(ft_strlen(s) + 1,1);
    if (!str)
        return NULL;
    int i = 0;
    while (s[i])
    {
        str[i] = s[i];
        i++;
    }
    str[i] = 0;
    return str;
}

char *get_next_line(int fd)
{
    if (fd < 0 || BUFFER_SIZE < 1)
        return NULL;
    static char b[BUFFER_SIZE + 1]= "";
    char *line = NULL;
    char *tmp = ft_strchr(b, '\n');
    while (!tmp)
    {
        if (!str_append_mem(&line, b , ft_strlen(b)))
        {
            free(line);
            return NULL;
        }
        int read_ret = read(fd, b , BUFFER_SIZE);
        if (read_ret == 0){
            b[0] = 0;
            return (line);
        }
        b[read_ret] = 0;
        if (read_ret == -1)
        {
            if (line)
            {
                free(line);
                line = NULL;
            }
            return NULL;
        }
        tmp = ft_strchr(b, '\n');
    }
        if (!str_append_mem(&line, b , tmp - b + 1))
        {
            free(line);
            return NULL;
        }

        int reminder = ft_strlen(tmp + 1);
        ft_memmove(b, tmp + 1, reminder);
        b[reminder] = 0;

        return line;
    }
