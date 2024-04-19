#include "cub3d.h"

int	ver_path(t_data *data) //TODO
{
	if (access(data->path[NORTH], F_OK))
		return (errmessage(6, data->path[NORTH]), 1);
	if (access(data->path[SOUTH], F_OK))
		return (errmessage(6, data->path[SOUTH]), 1);
	if (access(data->path[EAST], F_OK))
		return (errmessage(6, data->path[EAST]), 1);
	if (access(data->path[WEST], F_OK))
		return (errmessage(6, data->path[WEST]), 1);
	return (0);
}

int	ver_color(char *str, t_data *data)
{
	data->m = 0;
	data->len = 0;
	data->count = 0;
	while (str[data->m])
	{
		if (ft_isdigit(str[data->m]))
		{
			data->count++;
			while (ft_isdigit(str[data->m]))
			{
				data->m++;
				data->len++;
			}
			data->tmp = ft_substr(str, data->m - data->len, data->len);
			if (ft_atoi(data->tmp) < 0 || ft_atoi(data->tmp) > 255)
				errmessage(11, data->tmp);
			free(data->tmp);
			data->len = 0;
		}
		if (str[data->m] != 0)
			data->m++;
	}
	if (data->count != 3)
		errmessage(11, NULL);
	return (1);
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
	if (ver_path(data))
		return (1);
	if (!ver_color(data->path[FLOOR], data) && !ver_color(data->path[CEILING],
			data))
		return (1);
	if (ver_map(data))
		return (1);
	return (0);
}
