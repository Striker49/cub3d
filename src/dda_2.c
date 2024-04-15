#include "cub3d.h"

void	ft_dda(t_data *data, t_ray *ray)
{
	int	hit;

	hit = 0;
	ft_rayon(data, ray);
	while (hit == 0)
	{
		ft_forward_until_hit(ray);
		if (ray->mapX >= 0 && ray->mapY <= data->height
			&& data->map[(int)ray->mapY][(int)ray->mapX] == '1')
			hit = 1;
	}
	if (ray->side % 2 == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
}

void	ft_rayon(t_data *data, t_ray *ray)
{
	ft_setup(data, ray);
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (data->player.x - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - data->player.x) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (data->player.y - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - data->player.y) * ray->deltaDistY;
	}
}

void	ft_setup(t_data *data, t_ray *ray)
{
	data->dirX = data->pl_dir_x + data->planeX;
	data->dirY = data->pl_dir_y + data->planeY;
	ray->mapX = (int)data->player.x;
	ray->mapY = (int)data->player.y;
	data->cameraX = 2 * ray->line->x / (double)WIN_WIDTH_MINUS;
	ray->rayDirX = data->dirX + data->planeX * data->cameraX;
	ray->rayDirY = data->dirY + data->planeY * data->cameraX;
	ray->deltaDistX = fabs(1 / ray->rayDirX);
	ray->deltaDistY = fabs(1 / ray->rayDirY);
}

void	ft_forward_until_hit(t_ray *ray)
{
	if (ray->sideDistX < ray->sideDistY)
	{
		ray->sideDistX += ray->deltaDistX;
		ray->mapX += ray->stepX;
		ray->side = 4;
		if (ray->stepX == -1)
			ray->side = 2;
	}
	else
	{
		ray->sideDistY += ray->deltaDistY;
		ray->mapY += ray->stepY;
		ray->side = 1;
		if (ray->stepY == -1)
			ray->side = 3;
	}
}
