//Pour Exam ? correction fonctionnelle ? 

#include "broken_gnl.h"

char    *f_strchr(char *str, int c)
{
    while (*str)
    {
        if (*str == (char)c)
            return str;
        str++;
    }
    return NULL;
}
void *f_memcpy(void *dst, const void *src, size_t n)
{
    while (n--)
        (((char *)dst)[n] = ((char *)src)[n]);
    return dst;
}
size_t f_strlen(char *str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}
int str_append_mem(char **s1, char *s2, size_t size2)
{
    size_t size1 = (*s1) ? f_strlen(*s1) : 0;
    char *tmp = malloc(size1 + size2 + 1);
    if (!tmp)
        return 0;
    if (*s1)
    {
        f_memcpy(tmp, *s1, size1);
        free(*s1);
    }
    f_memcpy(tmp + size1, s2, size2);
    tmp[size1 + size2] = '\0';
    *s1 = tmp;
    return 1;
}
char    *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1] = {0};
    static size_t buffer_pos = 0;
    static size_t buffer_len = 0;
    char *line = NULL;
    ssize_t bytes_read;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    while (1)
    {
        if (buffer_pos < buffer_len)
        {
            char c = buffer[buffer_pos++];
            if (!str_append_mem(&line, &c, 1))
            {
                free(line);
                return NULL;
            }
            if (c == '\n')
                return line;
        }
        else
        {
            bytes_read = read(fd, buffer, BUFFER_SIZE);
            if (bytes_read < 0)
            {
                free (line);
                return NULL;
            }
            if (bytes_read == 0)
            {
                if (line)
                    return line;
                return NULL;
            }
            buffer_pos = 0;
            buffer_len = bytes_read;
        }
    } 
}
int main(int ac, char **av)
{
    if (ac < 2)
        return 0;
    int fd = open(av[1], O_RDONLY);
    if (fd < 0)
        return 0;
    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        if (line)
            free(line);
    }
    //printf("terminated\n");
    close(fd);
    return 0;
}