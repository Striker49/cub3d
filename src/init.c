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
	data->ceiling = ft_calloc(sizeof(int*), 4);
	data->floor = ft_calloc(sizeof(int*), 4);
	data->miniMap_satus = 1;
	data->img = ft_calloc(sizeof(data->img), 3 + 1);
	data->img[0] = ft_calloc(sizeof(mlx_image_t), 1);
	data->img[1] = ft_calloc(sizeof(mlx_image_t), 1);
	data->img[2] = ft_calloc(sizeof(mlx_image_t), 1);
	data->tex_Wall_N = ft_calloc(sizeof(mlx_texture_t), 1 + 1);
	data->tex_Wall_S = ft_calloc(sizeof(mlx_texture_t), 1 + 1);
	data->tex_Wall_E = ft_calloc(sizeof(mlx_texture_t), 1 + 1);
	data->tex_Wall_O = ft_calloc(sizeof(mlx_texture_t), 1 + 1);

	data->ray = ft_calloc(sizeof(t_ray), 1);

	// data->sc_x = 0;
	// data->sc_y = 0;
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
	data->aspect_ratio = 0;
	data->player_angle = ft_deg_rad(180);
	data->cursor_x = WINDOW_WIDTH / 2;
	data->cursor_y = WINDOW_HEIGHT / 2;
	init_ray(data->ray);
}

void	init_ray(t_ray *ray)
{
	t_line *line;
	line = ft_calloc(sizeof(t_line *), 1);
	ray->side = 0;
	ray->perpWallDist = 0.0;
	ray->rayDirX = 0.0;
	ray->rayDirY = 0.0;
	ray->curr_x = 0;
	ray->mapX = 0;
	ray->mapY = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
	// ray->line_height = 0;
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
	line->wall_x = 0;
}

void	clean_data(t_data *data)
{
	data->cameraX = 0;
}

void	clean_line(t_line *line)
{
	line->x0 = 0;
	line->x1 = 0;
	line->y0 = 0;
	line->y1 = 0;
	line->wall_x = 0;
}

void	clean_ray(t_ray *ray)
{
	ray->side = 0;
	ray->perpWallDist = 0.0;
	ray->rayDirX = 0.0;
	ray->rayDirY = 0.0;
	ray->deltaDistX = 0;
	ray->deltaDistY = 0;
	ray->sideDistX = 0;
	ray->sideDistY = 0;
	ray->curr_x = 0;
	ray->mapX = 0;
	ray->mapY = 0;
	ray->stepX = 0;
	ray->stepY = 0;
	ray->h_wall = 0;
}