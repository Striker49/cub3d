#include "cub3d.h"

int	ver_path(t_data *data)
{
	if (access(data->path[NORTH], F_OK))
		return (errmessage(6, data->path[NORTH]), 1);
	if (access(data->path[SOUTH], F_OK))
		return (errmessage(6, data->path[SOUTH]), 1);
	if (access(data->path[EAST], F_OK))
		return (errmessage(6, data->path[EAST]), 1);
	if (access(data->path[WEST], F_OK))
		return (errmessage(6, data->path[WEST]), 1);
	if (access(data->path[FLOOR], F_OK))
		return (errmessage(6, data->path[FLOOR]), 1);
	if (access(data->path[CEILING], F_OK))
		return (errmessage(6, data->path[CEILING]), 1);
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
	if (!ver_color(data->path[FLOOR]) && !ver_color(data->path[CEILING]))
		return (1);
	if (!ver_map(data))
		return (1);
	return (0);
}
