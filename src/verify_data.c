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

int	ver_color(t_data *data)
{
	int		i;
	int		len;
	int		count;
	char	*tmp;

	i = 0;
	len = 0;
	count = 0;
	while (data->floor[i])
	{
		if (ft_isdigit(data->floor[i]))
		{
			count++;
			while (ft_isdigit(data->floor[i]))
			{
				i++;
				len++;
			}
			tmp = ft_substr(data->floor, i - len, len);
			// printf("s: %s\n", data->floor);
			// printf("substr: %s\n", tmp);
			// printf("atoi: %d\n", ft_atoi(tmp));
			if (ft_atoi(tmp) < 0 || ft_atoi(tmp) > 255)
				errmessage(11, tmp);
			free(tmp);
			len = 0;
		}
		i++;
	}
	if (count != 3)
		errmessage(11, NULL);
	return (0);
}

int	ver_data(t_data *data)
{
	// if (!ver_path(data))
	// 	return (1);
	if (!ver_color(data))
		return (1);
	return (0);
}
