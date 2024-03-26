#include <stdio.h>
#include "cub3d.h"
#include <stdlib.h>
#include <stdbool.h>

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
	mlx_set_mouse_pos(data.mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	ft_put_pixel(&data);
	mlx_loop_hook(data.mlx, &ft_hook, &data);
	// mlx_cursor_hook(data.mlx, &mouse_hook, &data);
	mlx_key_hook(data.mlx, &ft_option, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	ft_free(&data);
	return (EXIT_SUCCESS);
}
