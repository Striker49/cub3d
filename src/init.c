#include "cub3d.h"

void	init_path_and_texture(t_data *data)
{
	data->path[NORTH] = NULL;
	data->path[SOUTH] = NULL;
	data->path[EAST] = NULL;
	data->path[WEST] = NULL;
	data->path[FLOOR] = NULL;
	data->path[CEILING] = NULL;
	data->n_buf = NULL;
	data->s_buf = NULL;
	data->e_buf = NULL;
	data->o_buf = NULL;
}

void	init_struct(t_data *data)
{
	data->ray = ft_calloc(sizeof(t_ray), 1);
	data->ray->line = ft_calloc(sizeof(t_line), 1);
	data->file = NULL;
	data->map = NULL;
	data->file_size = 0;
	data->width = 0;
	data->height = 0;
	data->facing = -1;
	ft_init_cam(data);
	data->aspect_ratio = 0;
	data->miniMap_satus = 2;
	data->player_angle = ft_deg_rad(180);
	data->cursor_x = WINDOW_WIDTH / 2;
	data->cursor_y = WINDOW_HEIGHT / 2;
	data->i = 0;
	data->j = 0;
	data->c = 0;
	data->temp = NULL;
	init_path_and_texture(data);
	init_ray(data->ray);
	init_line(data->ray->line);
}

void	ft_init_cam(t_data *data)
{
	data->pl_x = 0;
	data->pl_y = 0;
	data->pl_dir_x = 0;
	data->pl_dir_y = 0;
	data->planeX = 0;
	data->planeY = 0.66;
	data->dirX = 0;
	data->dirY = 0;
	data->cameraX = 0;
	data->fov_x = 0;
	data->fov_y = 0;
	data->q = 0;
	data->w = 0;
	data->e = 0;
	data->m = 0;
	data->len = 0;
	data->count = 0;
	data->tmp = NULL;
}

void	init_ray(t_ray *ray)
{
	ray->side = 0;
	ray->perpWallDist = 0.0;
	ray->perpWallDist2 = 0.0;
	ray->rayDirX = 0.0;
	ray->rayDirY = 0.0;
	ray->curr_x = 0;
	ray->mapX = 0;
	ray->mapY = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
	ray->h_wall = 0;
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
	line->wall_x = 0;
	line->tex_height = 0;
	line->tex_length = 0;
}
