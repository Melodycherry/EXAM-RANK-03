#include <unistd.h>
#include <stdlib.h>

int ft_strlen(char *s)
{
    if (!s)
        return 0;
    int i = 0;
    while (s[i])
        i++;
    return i;
}

char *ft_strdup(char *s)
{
    if (!s)
        return NULL;
    char *copy = malloc(sizeof(char) * ft_strlen(s) + 1);
    if (!copy)
    {
        return (NULL);
    }
    int i = 0;
    while (s[i])
    {
        copy[i] = s[i];
        i++;
    }
    copy[i] = 0;
    return copy;
}

char *ft_get_line()
{
    static char buffer[10];
    char line[100000];
    static int b_pos = 0;
    static int b_read = 0;
    int i = 0;
    while(1)
    {
        if (b_pos >= b_read)
        {
            b_read = read(0, buffer, 10);
            if (b_read < 1)
            {
                return (NULL);
            }
            b_pos = 0;
        }
        line[i++] = buffer[b_pos++];
        if (buffer[b_pos - 1] == '\n')
        break;
    }
    if (i == 0)
        return NULL;
    line[i] = 0;
    return (ft_strdup(line));
}

void print_it(int n)
{
    int i = 0;
    while (i < n)
    {
        write(1, "*" ,1);
        i++;
    }
}

void filter_sh(char *s,char *filter)
{
    int i = 0;
    int j = 0;
    if(!s || !filter)
        return;
    while(s[i])
    {
        j = 0;
        if (s[i] == filter[j])
        {
            while (s[i] && s[i] == filter[j])
            {
                i++;
                j++;
            }
            if (j == ft_strlen(filter))
            {
                print_it(ft_strlen(filter));
                continue;
            }
            else
            {
                i = i - j;
            }
        }
        write(1, s + i, 1);
        i++;
    }
}


int main(int ac, char **av)
{
    if (ac != 2)
        return 1;
    if (av[1][0] == 0)
        return 1;
    char *s;
    s = ft_get_line();
    while (s)
    {
        filter_sh(s, av[1]);
        free(s);
        s = ft_get_line();
    }
    free(s);
    return (0);
}
