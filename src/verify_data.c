#include "cub3d.h"

int	ver_path(t_data *data)
{
	if (access(data->no, F_OK))
		return (errmessage(6, data->no), 1);
	if (access(data->so, F_OK))
		return (errmessage(6, data->so), 1);
	if (access(data->ea, F_OK))
		return (errmessage(6, data->ea), 1);
	if (access(data->we, F_OK))
		return (errmessage(6, data->we), 1);
	if (access(data->floor, F_OK))
		return (errmessage(6, data->floor), 1);
	if (access(data->ceiling, F_OK))
		return (errmessage(6, data->ceiling), 1);
	return (0);
}

int	ver_color(char *str)
{
	int		i;
	int		len;
	int		count;
	char	*tmp;

	i = 0;
	len = 0;
	count = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			count++;
			while (ft_isdigit(str[i]))
			{
				i++;
				len++;
			}
			tmp = ft_substr(str, i - len, len);
			// printf("s: %s\n", str);
			// printf("substr: %s\n", tmp);
			// printf("atoi: %d\n\n", ft_atoi(tmp));
			if (ft_atoi(tmp) < 0 || ft_atoi(tmp) > 255)
				errmessage(11, tmp);
			free(tmp);
			len = 0;
		}
		if (str[i] != 0)
			i++;
	}
	if (count != 3)
		errmessage(11, NULL);
	return (1);
}

int ver_char(t_data *data, char c)
{
	if ( c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (data->facing != 0)
		{
			ft_free(data);
			errmessage(12, NULL);
		}
		else
		{
			if (c == 'N')
				data->facing = NORTH;
			if (c == 'S')
				data->facing = SOUTH;
			if (c == 'E')
				data->facing = EAST;
			if (c == 'W')
				data->facing = WEST;
			return (1);
		}
	}
	if (c == '0' || c == '1' || c == ' ' || c == '\n')
		return (1);
	return (0);
}

int	parse_map(t_data *data, char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!ver_char(data, map[i][j]))
				errmessage(7, ft_substr(map[i], j, 1));
			j++;
		}
		i++;
	}
	return (1);
}

char	**ft_copy_map(char **map)
{
	int		i;
	int		ilen;
	char	**map2;

	i = 0;
	ilen = ft_height(map);
	map2 = ft_calloc((ilen + 1), sizeof(*map2));
	if (!map2)
	{
		free(map2);
		map2 = NULL;
		return (0);
	}
	while (map[i])
	{
		map2[i] = ft_strdup(map[i]);
		i++;
	}
	return (map2);
}

int	flood_fill(char **map, int x, int y)
{
	if (map[y][x] == '1' || map[y][x] == 'X')
		return (0);
	if (map[y][x] == ' ')
		return (-1);
	map[y][x] = 'X';
	if (flood_fill(map, x + 1, y) == -1)
		return (-1);
	if (flood_fill(map, x - 1, y) == -1)
		return (-1);
	if (flood_fill(map, x, y + 1) == -1)
		return (-1);
	if (flood_fill(map, x, y - 1) == -1)
		return (-1);
	return (0);
}

int	pre_flood(t_data *data)
{
	char	**map2;
	int		x;
	int		y;

	map2 = ft_copy_map(data->map);
	x = ft_strchr_x(map2, data->facing);
	y = ft_strchr_y(map2, data->facing);
	if (flood_fill(map2, x, y) == -1)
	{
		ft_free(data);
		free_map(map2);
		errmessage(13, NULL);
	}
	ft_print_map(map2);
	free_map(map2);
	return (0);
}

int	ver_map(t_data *data)
{
	if (!parse_map(data, data->map))
		return (1);
	if (!pre_flood(data))
		return (1);
	return (0);
}

int	ver_data(t_data *data)
{
	// if (!ver_path(data))
	// 	return (1);
	if (!ver_color(data->floor) && !ver_color(data->ceiling))
		return (1);
	if (!ver_map(data))
		return (1);
	return (0);
}
