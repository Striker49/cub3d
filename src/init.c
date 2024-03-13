#include "cub3d.h"

void	init_struct(t_data *data)
{
	data->file = NULL;
	data->map = NULL;
	data->file_size = 0;
	data->width = 0;
	data->height = 0;
	data->facing = -1;
	data->path = ft_calloc(7 + 1, sizeof(data->path));
	data->path[SOUTH] = NULL;
	data->path[NORTH] = NULL;
	data->path[EAST] = NULL;
	data->path[WEST] = NULL;
	data->path[FLOOR] = NULL;
	data->path[CEILING] = NULL;
	data->img = malloc(sizeof(data->img) * 2 + 1);
}
