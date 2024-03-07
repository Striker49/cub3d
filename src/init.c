#include "cub3d.h"

void	init_struct(t_data *data)
{
	data->file = NULL;
	data->map = NULL;
	data->file_size = 0;
	data->facing = 0;
	data->so = NULL;
	data->no = NULL;
	data->ea = NULL;
	data->we = NULL;
	data->floor = NULL;
	data->ceiling = NULL;
}
