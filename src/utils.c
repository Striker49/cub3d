#include "cub3d.h"
#include <stdio.h>

void	printmess(int fd, char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

void	ft_print_map(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
		{
			printf("%s", map[i]);
			i++;
		}
	}
}

int	ft_iswhitesp(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

int	ft_height(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int enum_to_direction(char c)
{
	if (c == 1)
		return('N');
	if (c == 2)
		return('S');
	if (c == 3)
		return('E');
	if (c == 4)
		return ('W');
	return (1);
}

int	ft_strchr_x(char **s, int c)
{
	int	i;
	int	j;

	c = enum_to_direction(c);
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (c == s[i][j])
				return (j);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_strchr_y(char **s, int c)
{
	int	i;
	int	j;

	c = enum_to_direction(c);
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		j = 0;
		while (s[i][j])
		{
			if (c == s[i][j])
				return (i);
			j++;
		}
		i++;
	}
	return (0);
}
