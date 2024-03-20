#include <stdio.h>
#include "cub3d.h"
#include <stdlib.h>
#include <stdbool.h>

// void	draw_square(t_data *data, int32_t i, int32_t y, int32_t color)
// {
// 	int	l;
// 	int	k;
// 	k = y;
// 	l = i;
// 	while (y < k + 9)
// 	{
// 		i = l ;
// 		while (i < l + 9)
// 		{
// 			mlx_put_pixel(data->img[0], i, y, color);
// 			i++;
// 		}
// 		y++;
// 	}
// }

// int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
// {
//     return (r << 24 | g << 16 | b << 8 | a);
// }

// void ft_put_pixel(void* param)
// {
// 	t_data	*data;
// 	uint32_t y;
// 	uint32_t i;
// 	uint32_t color;

// 	data = param;
// 	y = 0;
// 	while (y < data->height)
// 	{
// 		i = 0;
// 		while (i < data->width)
// 		{
// 			// printf("i: %d\n", i);
// 			if (data->map[y][i] == '0')
// 				color = ft_pixel(0xFF, 0xFF, 0xFF,0xFF);
// 			else if (data->map[y][i] == '1')
// 				color = ft_pixel(0x0, 0x0, 0x8B,0xFF);
// 			else if (data->map[y][i] == 'P')
// 				color = ft_pixel(0xDC, 0x14, 0x3C,0xFF);
// 			else
// 				color = ft_pixel(0x0, 0x0, 0x0,0xFF);
// 			draw_square(data, i * 10, y * 10, color);
// 			// mlx_put_pixel(data->img[0], i * 10, y * 10, color);
// 			i++;
// 		}
// 		// printf("y: %d\n", y);
// 		y++;
// 	}
// }

// int	main( int argc, char **argv)
// {
// 	t_data	data;

// 	init_struct(&data);
// 	ft_file_format(argc, argv[1]);
// 	ft_read_file(&data, argv);
// 	if (!ver_data(&data))
// 		ft_free(&data);
// 	// init_mlx(&data);
// 	// ft_put_pixel(&data);
// 	// mlx_loop_hook(data.mlx, &ft_hook, &data);
// 	// mlx_loop(data.mlx);
// 	// mlx_terminate(data.mlx);
// 	// ft_free(&data);
// 	return (EXIT_SUCCESS);
// }

void ft_DDA(t_data *data, t_ray *ray)
{
	double posX = 22;
	double posY = 12;
	double dirX = -1;
	double dirY = 0;
	double planeX = 0;
	double planeY = 0.66;

	int x;
	double cameraX;
	// double rayDirX;
	// double rayDirY;

	//Direction du rayon
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		cameraX = 2 * x / (double)WINDOW_WIDTH - 1;
		ray->rayDirX = dirX + planeX * cameraX;
		ray->rayDirY = dirY + planeY * cameraX;
		x++;
	}

	//longueur du rayon
	double deltaDistX;
	double deltaDistY;

	deltaDistX = sqrt(1 + (ray->rayDirY * ray->rayDirY) / (ray->rayDirX * ray->rayDirX));
	deltaDistY = sqrt(1 + (ray->rayDirX * ray->rayDirX) / (ray->rayDirY * ray->rayDirY));
 
	// int mapX;
	// int mapY;

	double sideDistX;
	double sideDistY;

	deltaDistX = (ray->rayDirX == 0) ? 1e30 : fabs(1 / ray->rayDirX);
	deltaDistY = (ray->rayDirY == 0) ? 1e30 : fabs(1 / ray->rayDirY);
	// double perpWallDist;

	int stepX;
	int stepY;

	int hit;
	int side;
	hit = 0;

	if(ray->rayDirX < 0)
	{
		stepX = -1;
		sideDistX = (posX - ray->mapX) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (ray->mapX + 1.0 - posX) * deltaDistX;
	}
	if(ray->rayDirY < 0)
	{
		stepY = -1;
		sideDistY = (posY - ray->mapY) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (ray->mapY + 1.0 - posY) * deltaDistY;
	}

	//Digital Differential Analysis
	while (hit == 0)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			ray->mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			ray->mapY += stepY;
			side = 1;
		}
		if (data->map[ray->mapX][ray->mapY] > 0)
			hit = 1;
	}

	//distance projected
	if (side == 0)
		ray->perpWallDist = (sideDistX - deltaDistX);
	else
		ray->perpWallDist = (sideDistY - deltaDistY);
}

void	ft_scaling_transform(t_data *data, t_ray *ray)
{
	double wall_x;
	t_color *color;

	if (ray->side == WEST || ray->side == EAST)
		wall_x = data->pl_y + ray->perpWallDist * ray->rayDirY;
	else
		wall_x = data->pl_x + ray->perpWallDist * ray->rayDirX;
	wall_x -= floor(wall_x); //fct qui arrondie de math.h

	ray->line->x = ray->curr_x;

	color->Color1[0] = 199;
	color->Color1[1] = 0;
	color->Color1[2] = 57;

	color->Color2[0] = 88;
	color->Color2[1] = 24;
	color->Color2[2] = 69;
	
	//paint texture
	if (data->map[ray->mapY][ray->mapX] == '1')
	{
		// paint_texture_line(data, ray, ray->line, wall_x);
		// mlx_texture_to_image(mlx_t* mlx, mlx_texture_t* texture);
	}
	ray->line->y0 = 0;
	ray->line->y1 = ray->draw_start;


	paint_line(data, ray->line, color);

	ray->line->y0 = WINDOW_HEIGHT;
	ray->line->y1 = ray->draw_end;

	paint_line(data, ray->line, color);

}

int	main( int argc, char **argv)
{
	t_data data;
	t_ray ray;

	init_struct(&data);
	ft_file_format(argc, argv[1]);
	ft_read_file(&data, argv);
	ft_set_camera(&data);
	if (!(data.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "MLX42", true)))
	{
		return(EXIT_FAILURE);
	}
	if (!(data.img = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT)))
	{
		mlx_close_window(data.mlx);
		return(EXIT_FAILURE);
	}
	ft_floor_sky(&data);
	// ft_DDA(&data, &ray);
	// ft_scaling_transform(&data, &ray);
	if (mlx_image_to_window(data.mlx, data.img, 0, 0) == -1)
	{
		mlx_close_window(data.mlx);
		return(EXIT_FAILURE);
	}
	
	// mlx_loop_hook(mlx, ft_put_pixel, mlx);
	// mlx_loop_hook(mlx, ft_hook, mlx);

	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	if (!ver_data(&data))
		ft_free(&data);
	return (EXIT_SUCCESS);
}
