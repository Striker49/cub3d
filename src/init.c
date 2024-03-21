#include "cub3d.h"

void	init_struct(t_data *data)
{
	data->file = NULL;
	data->map = NULL;
	data->file_size = 0;
	data->width = 0;
	data->height = 0;
	data->facing = -1;
	data->path = ft_calloc(7 + 1, sizeof(char*));
	data->path[NORTH] = NULL;
	data->path[SOUTH] = NULL;
	data->path[EAST] = NULL;
	data->path[WEST] = NULL;
	data->path[FLOOR] = NULL;
	data->path[CEILING] = NULL;
	data->img = malloc(sizeof(data->img) * 2 + 1);

	data->pl_dir_x = 0;
	data->pl_dir_y = 1;
	data->player_angle = PI / 2;
}

void	init_ray(t_ray *ray)
{
	t_line *line;
	ray->side = 0;
	ray->perpWallDist = 0.0;
	ray->rayDirX = 0.0;
	ray->rayDirY = 0.0;
	ray->curr_x = 0;
	ray->mapX = 0;
	ray->mapY = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
	ray->line_height = 0;
	ray->h_wall = 0;
	ray->line = line;
	init_line(line);
}

void	init_line(t_line *line)
{
	line->x = 0;
	line->x0 = 0;
	line->x1 = 0;
	line->y = 0;
	line->y0 = 0;
	line->y1 = 0;
	line->tex_x = 0;
	line->tex_y = 0;
}