#include <stdio.h>
#include "cub3d.h"
#include <stdlib.h>
#include <stdbool.h>

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

// void	ft_scaling_transform(t_data *data, t_ray *ray)
// {
// 	double wall_x;
// 	t_color *color;

// 	if (ray->side == WEST || ray->side == EAST)
// 		wall_x = data->pl_y + ray->perpWallDist * ray->rayDirY;
// 	else
// 		wall_x = data->pl_x + ray->perpWallDist * ray->rayDirX;
// 	wall_x -= floor(wall_x); //fct qui arrondie de math.h

// 	ray->line->x = ray->curr_x;

// 	color->Color1[0] = 199;
// 	color->Color1[1] = 0;
// 	color->Color1[2] = 57;

// 	color->Color2[0] = 88;
// 	color->Color2[1] = 24;
// 	color->Color2[2] = 69;
	
// 	//paint texture
// 	if (data->map[ray->mapY][ray->mapX] == '1')
// 	{
// 		// paint_texture_line(data, ray, ray->line, wall_x);
// 		// mlx_texture_to_image(mlx_t* mlx, mlx_texture_t* texture);
// 	}
// 	ray->line->y0 = 0;
// 	ray->line->y1 = ray->draw_start;


// 	paint_line(data, ray->line, color);

// 	ray->line->y0 = WINDOW_HEIGHT;
// 	ray->line->y1 = ray->draw_end;

// 	paint_line(data, ray->line, color);

// }


void ft_DDA(t_data *data, t_ray *ray)
{
	double posX = data->player.x;
	double posY = data->player.y;
	double planeX = 0;
	double planeY = 0.66;
	double dirX = data->pl_dir_x + planeX;
	double dirY = data->pl_dir_y + planeY;
	ray->mapX = (int)data->player.x;
	ray->mapY = (int)data->player.y;
	double cameraX;

	//Direction du rayon
	cameraX = 2 * ray->line->x / (double)WINDOW_WIDTH - 1;
	ray->rayDirX = dirX + planeX * cameraX;
	ray->rayDirY = dirY + planeY * cameraX;

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


	int hit;
	int side;
	hit = 0;
	int posiytive_map_Y;
	int posiytive_map_X;
	//Digital Differential Analysis
	// while (data->map[ray->mapX][ray->mapY] != 1 && hit == 0)
	while (hit == 0)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			ray->mapX += stepX;
			// side = 0;
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

	// //distance projected
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
		ft_DDA(data, ray); // 1 rayon
		// ray->h_wall = -1 * (ray->line->tex_x / ray->perpWallDist) * (WINDOW_HEIGHT * (ft_deg_rad(60) / 360));
		ray->h_wall = (int)(WINDOW_HEIGHT / ray->perpWallDist);
		// ray->line->y0 = (WINDOW_HEIGHT - ray->h_wall) / 2;
		ray->line->y0 = -ray->h_wall / 2 + WINDOW_HEIGHT / 2;
		if (ray->line->y0 < 0)
			ray->line->y0 = 0;
		// ray->line->y1 = ray->line->y0 + ray->h_wall;
		ray->line->y1 = ray->h_wall / 2 + WINDOW_HEIGHT / 2;
		if (ray->line->y1 >= WINDOW_HEIGHT)
			ray->line->y1 = WINDOW_HEIGHT - 1;
		trace_line(data, ray->line);
		ray->line->x++;
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
		mlx_put_pixel(data->img[0], line->x, y, get_rgba(255, 255, 255, 255));
		y++;
	}
}

// void ft_put_image(void *param)
// {
// 	t_data *data;

// 	data = param;
// 	ft_floor_sky(data);
// 	// printf("yo\n");
// 	ft_DDA(data, data->ray);
// 	ft_trace_wall(data, data->ray);
// }

// void 	ft_restart_image(t_data *data, void *param)
// {
// 	double rot_speed;
// 	double move_speed;

// 	rot_speed = 0.06;
// 	move_speed = 0.03;

// 	if ()
// }

int	main( int argc, char **argv)
{
	t_data data;

	init_struct(&data);
	ft_file_format(argc, argv[1]);
	ft_read_file(&data, argv);
	if (!ver_data(&data))
		ft_free(&data);
	ft_set_camera(&data);
	if (!(data.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d", true)))
	{
		return(EXIT_FAILURE);
	}
	if (!(data.img[0] = mlx_new_image(data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT)))
	{
		mlx_close_window(data.mlx);
		return(EXIT_FAILURE);
	}
	ft_floor_sky(&data);
	ft_trace_wall(&data, data.ray);
	// ft_scaling_transform(&data, data.ray);
	if (mlx_image_to_window(data.mlx, data.img[0], 0, 0) == -1)
	{
		mlx_close_window(data.mlx);
		return(EXIT_FAILURE);
	}
	// ft_restart_image(&data);
	// mlx_loop_hook(mlx, ft_hook, mlx);

	init_mlx(&data);
	ft_put_pixel(&data);
	// mlx_loop_hook(data.mlx, &ft_put_image, data.mlx);
	mlx_loop_hook(data.mlx, &ft_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	ft_free(&data);
	return (EXIT_SUCCESS);
}
