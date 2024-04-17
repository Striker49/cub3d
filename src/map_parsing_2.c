#include "cub3d.h"

int	flood_fill(char **map, int x, int y)
{
	if (x < 0 || y < 0)
		return (-1);
	if (map[y] == NULL || map[y][x] == '\n'
		|| map[y][x] == 0)
		return (-1);
	if (map[y][x] == '1' || map[y][x] == 'X' || map[y][x] == ' ')
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
	printf("before flood\n");
	ft_print_map(data->map);
	if (flood_fill(map2, x, y) == -1)
	{
		ft_free(data);
		free_map(map2);
		errmessage(13, NULL);
	}
	printf("after flood\n");
	ft_print_map(map2);
	free_map(map2);
	return (0);
}

void	replace_spaces(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == ' ')
			{
				data->map[i][j] = 0;
			}
			j++;
		}
		i++;
	}
}