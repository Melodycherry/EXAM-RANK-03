#include <unistd.h>

void sort_str(char *str)
{
    int i, j;
    char temp;

    i = 0;
    while (str[i])
    {
        j = i + 1;
        while (str[j])
        {
            if (str[i] > str[j])
            {
                temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
            j++;
        }
        i++;
    }
}
#include <stdio.h>


 int ft_strlen(char *str)
 {
    int i = 0;
    if(!str)
        return 0;
    while (str[i])
        i++;
    return i;}
void permutation(char *str,int index, int size)
{
    if (index == size)
        printf("%s\n",str);
    int i = index;
    while (i < size)
    {
        char c = str[i];
        str[i] = str[index];
        str[index] = c;
        permutation(str,index + 1, size);
         c = str[i];
        str[i] = str[index];
        str[index] = c;
        i++;
    }
}


int main(int ac, char **av)
{
    if (ac != 2)
    {
        write(1, "\n", 1);
        return 0;
    }
    char *str = av[1];
    int size = ft_strlen(str);
    sort_str(str);
    permutation(str, 0, size);
}

