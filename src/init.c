#include "cub3d.h"

void	init_struct(t_data *data)
{
	data = ft_calloc(sizeof(struct s_data), 1);

	data->file = NULL;
	data->map = NULL;
	data->file_size = 0;
	data->so = NULL;
	data->no = NULL;
	data->ea = NULL;
	data->we = NULL;
	data->floor = NULL;
	data->ceiling = NULL;
	
}