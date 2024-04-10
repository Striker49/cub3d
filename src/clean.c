#include "cub3d.h"

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
