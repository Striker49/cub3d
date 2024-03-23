#include "cub3d.h"

void ft_DDA(t_data *data, t_ray *ray)
{
	data->dirX = data->pl_dir_x + data->planeX;
	data->dirY = data->pl_dir_y + data->planeY;
	ray->mapX = (int)data->player.x;
	ray->mapY = (int)data->player.y;

	//Direction du rayon
	data->cameraX = 2 * ray->line->x / (double)WINDOW_WIDTH - 1;
	ray->rayDirX = data->dirX + data->planeX * data->cameraX;
	ray->rayDirY = data->dirY + data->planeY * data->cameraX;

	//longueur du rayon
	double deltaDistX;
	double deltaDistY;
 

	deltaDistX = fabs(1 / ray->rayDirX);
	deltaDistY = fabs(1 / ray->rayDirY);

	int stepX;
	int stepY;


	double sideDistX;
	double sideDistY;

	if(ray->rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (data->player.x - ray->mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (ray->mapX + 1.0 - data->player.x) * deltaDistX;
	}
	if(ray->rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (data->player.y - ray->mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (ray->mapY + 1.0 - data->player.y) * deltaDistY;
	}


	int hit;
	int side;

	hit = 0;
	//Digital Differential Analysis
	while (hit == 0)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			ray->mapX += stepX;
			side = 4;
			if (stepX == -1)
				side = 2;

		}
		else
		{
			sideDistY += deltaDistY;
			ray->mapY += stepY;
			side = 1;
			if (stepY == -1)
				side = 3;
		}
		if (ray->mapX >= 0 && ray->mapY <= data->height && data->map[(int)ray->mapY][(int)ray->mapX] == '1' )
			hit = 1;
	}

	//distance projected
	if (side % 2 == 0)
		ray->perpWallDist = (sideDistX - deltaDistX);
	else
		ray->perpWallDist = (sideDistY - deltaDistY);
}


double	ft_deg_rad(int deg)
{
	double	rad;

	rad = deg * M_PI / 180.0;
	return (rad);
}

void	ft_trace_wall(t_data *data, t_ray *ray)
{
	//trigonometrie pour trouver la hauteur du mur sur l'écran
	ray->line->tex_x = TEX_WIDTH;
	ray->line->x = 0;
	while (ray->line->x < WINDOW_WIDTH)
	{
		ft_DDA(data, ray);
		ray->h_wall = (int)(WINDOW_HEIGHT / ray->perpWallDist);
		ray->line->y0 = -ray->h_wall / 2 + WINDOW_HEIGHT / 2;
		if (ray->line->y0 < 0)
			ray->line->y0 = 0;
		ray->line->y1 = ray->h_wall / 2 + WINDOW_HEIGHT / 2;
		if (ray->line->y1 >= WINDOW_HEIGHT)
			ray->line->y1 = WINDOW_HEIGHT - 1;
		trace_line(data, ray->line);
		ray->line->x++;
		clean_data(data);
		clean_line(ray->line);
		clean_ray(ray);
	}
}

void	trace_line(t_data *data, t_line *line)
{
	int y;

	y = line->y0;
	while (y < line->y1 && line->y1 < WINDOW_HEIGHT && line->y0 >= 0)
	{
		mlx_put_pixel(data->img[0], line->x, y, get_rgba(218, 475, 166, 255));
		y++;
	}
}