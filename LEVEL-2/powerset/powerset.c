#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int ft_atoi(char *str)
{
    int i = 0;
    int sign = 1;
    int result = 0;

    while (str[i] == ' ')
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result * sign);
}

void ft_putnbr(int n)
{
    if (n < 0)
    {
        write(1, "-", 1);
        n = -n;
    }
    if (n >= 10)
        ft_putnbr(n / 10);
    write(1, &((char[]){'0' + n % 10}), 1);
}

void ft_print_all(int *arr, int size)
{
    int i = 0;
    while (i < size)
    {
        ft_putnbr(arr[i]);
        if (i < size - 1)
            write(1, " ", 1);
        i++;
    }
    write(1,"\n",1);
}
int sum_set(int *arr, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
        sum += arr[i];
    return sum;
}


void r_add(int **res,int *r_size,int n)
{
    (*r_size)++;

    int *res2 = malloc(*r_size * sizeof(int));
    int i = 0;
    while (i < *r_size - 1)
    {
        res2[i] = (*res)[i];
        i++;
    } 
    res2[(*r_size) - 1] = n;
    free(*res);
    *res = res2;
}


void r_del(int **res,int *r_size)
{
    (*r_size)--;
}

void power_set(int target, int *arr, int index,int size,int **res,int r_size)
{
    int i = index;
    if (target == sum_set(*res, r_size))
        ft_print_all(*res,r_size);
    
    while (i < size)
    {
       r_add(res,&r_size,arr[i]);
       power_set(target,arr, i + 1,size, res, r_size);
       r_del(res,&r_size);
       i++;
    }
}

int	main(int ac, char **av)
{
    if (ac < 3)
    {
        printf("Usage: ./power_set <target> <set>\n");
        write(1, "\n", 1);
        return (1);
    }
	int	*arr = calloc(sizeof(int) * (ac - 2), 1);
	int	*res = calloc(sizeof(int), 1);
	int	i, target;

	target = ft_atoi(av[1]);
	i = 2;
	while (i < ac)
	{
		arr[i - 2] = ft_atoi(av[i]);
		i++;
	}
	power_set(target, arr, 0, ac - 2, &res, 0);
    free(res);
    free(arr);
	return (0);
}


