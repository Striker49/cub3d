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

int	ver_data(t_data *data)
{
	if (!ver_path(data))
		return (1);
	return (0);
}