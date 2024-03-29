#include "cub3d.h"

void	set_player_angle(t_data *data)
{
	if (data->facing == NORTH)
	{
		data->player_angle = ft_deg_rad(270);
	}
	if (data->facing == SOUTH)
	{
		data->player_angle = ft_deg_rad(90);
	}
	if (data->facing == EAST)
	{
		data->player_angle = 0;
	}
	if (data->facing == WEST)
	{
		data->player_angle = ft_deg_rad(180);
	}
}

int	ver_char(t_data *data, char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (data->facing != -1)
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
	if (data->facing == -1)
		errmessage(14, NULL);
	set_player_angle(data);
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
	if (x < 0 || y < 0)
		return (-1);
	if (map[y] == NULL || map[y][x] == '\n' || map[y][x] == ' ' || map[y][x] == 0)
		return (-1);
	if (map[y][x] == '1' || map[y][x] == 'X')
		return (0);
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
	data->height = ft_height(data->map);
	x = ft_strchr_x(map2, data->facing);
	y = ft_strchr_y(map2, data->facing);
	data->map[y][x] = '0';
	data->player.x = x + 0.5;
	data->player.y = y + 0.5;
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
