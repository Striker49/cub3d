#include "cub3d.h"

void    ft_rayon(t_data *data, t_ray *ray)
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
	ray->deltaDistX = fabs(1 / ray->rayDirX);
	ray->deltaDistY = fabs(1 / ray->rayDirY);

    //direction du rayon passe en haut ou en bas du pi
	if(ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (data->player.x - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - data->player.x) * ray->deltaDistX;
	}
	if(ray->rayDirY < 0)
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

void ft_DDA(t_data *data, t_ray *ray)
{
	int hit;
	// int side;

	hit = 0;
    ft_rayon(data, ray);

	//Digital Differential Analysis
	while (hit == 0)
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
		if (ray->mapX >= 0 && ray->mapY <= data->height && data->map[(int)ray->mapY][(int)ray->mapX] == '1' )
			hit = 1;
	}

	//distance projected
	if (ray->side % 2 == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
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
        if (data->ray->side == 1)
		{
			// ft_load_texture(data);
			// ft_scaling_transform(data, data->ray, get_rgba(220, 237, 200, 255));
            mlx_put_pixel(data->img[0], line->x, y, get_rgba(220, 237, 200, 255));
		}
		    // mlx_put_pixel(data->img[0], line->x, y, get_rgba(27, 94, 32, 255));
        else if (data->ray->side == 2)
            mlx_put_pixel(data->img[0], line->x, y, get_rgba(197, 225, 165, 255));
            // mlx_put_pixel(data->img[0], line->x, y, get_rgba(46, 125, 50, 255));
        else if (data->ray->side == 3)
            mlx_put_pixel(data->img[0], line->x, y, get_rgba(220, 237, 200, 255));
            // mlx_put_pixel(data->img[0], line->x, y, get_rgba(46, 125, 50, 255));
	    else
            mlx_put_pixel(data->img[0], line->x, y, get_rgba(197, 225, 165, 255));
            // mlx_put_pixel(data->img[0], line->x, y, get_rgba(27, 94, 32, 255));
		y++;
	}
}