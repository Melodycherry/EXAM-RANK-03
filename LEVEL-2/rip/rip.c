#include <stdio.h>
#include <string.h>
#include <unistd.h>
// don't forget to print space instead of _ ana i used _ for clarity wsalam

int	is_valid(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i] == '(')
			res++;
		if (str[i] == ')')
			res--;
		if (res < 0)
			return (0);
		i++;
	}
	if (res == 0)
		return (1);
	return (0);
}

void	calc_min(char *str, int *min, int index, int change)
{
	int		i;
	char	c;
  if (change > *min)
      return ;
		if (is_valid(str) && change < *min)
		{
			*min = change;
		}
	i = index;
	while (str[i])
	{
		c = str[i];
		str[i] = '_';
		change++;
		calc_min(str, min, i + 1, change);
		str[i] = c;
		change--;
		i++;
	}
}



void	rip(char *str, int min, int index, int change)
{
	int		i;
	char	c;
  if (change > min)
      return ;
		if (is_valid(str) && change == min)
			puts(str);
	i = index;
	while (str[i])
	{
		c = str[i];
		str[i] = '_';
		change++;
		rip(str, min, i + 1, change);
		str[i] = c;
		change--;
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2 || av[1][0] == 0)
	{
		write (1,"\n",1);
		return (1);
	}
	int min = strlen(av[1]);
	calc_min(av[1], &min, 0, 0);
	rip(av[1], min, 0, 0);
}
