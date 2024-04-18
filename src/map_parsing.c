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
		data->player_angle = ft_deg_rad(0);
	}
	if (data->facing == WEST)
	{
		data->player_angle = ft_deg_rad(180);
	}
	data->pl_dir_x = cos(data->player_angle) * 5;
	data->pl_dir_y = sin(data->player_angle) * 5;
}

int	ver_char(t_data *data, char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (data->facing != -1)
		{
			// ft_free(data);
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
		while (map[i][j] != '\n')
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
