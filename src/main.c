#include <stdio.h>
#include "cub3d.h"
#include <stdlib.h>
#include <stdbool.h>

// void	verify_pointer(t_data *data)
// {
//    printf("data->file: %p\n", (void *)data->file);
//     printf("data->map: %p\n", (void *)data->map);
//     printf("data->file_size: %p\n", (void *)&data->file_size);
//     printf("data->width: %p\n", (void *)&data->width);
//     printf("data->height: %p\n", (void *)&data->height);
//     printf("data->facing: %p\n", (void *)&data->facing);
//     printf("data->path[NORTH]: %p\n", (void *)data->path[NORTH]);
//     printf("data->path[SOUTH]: %p\n", (void *)data->path[SOUTH]);
//     printf("data->path[EAST]: %p\n", (void *)data->path[EAST]);
//     printf("data->path[WEST]: %p\n", (void *)data->path[WEST]);
//     printf("data->path[FLOOR]: %p\n", (void *)data->path[FLOOR]);
//     printf("data->path[CEILING]: %p\n", (void *)data->path[CEILING]);
//     printf("data->ceiling: %p\n", (void *)data->ceiling);
//     printf("data->floor: %p\n", (void *)data->floor);
//     printf("data->img[0]: %p\n", (void *)data->img[0]);
//     printf("data->img[1]: %p\n", (void *)data->img[1]);
//     printf("data->img[2]: %p\n", (void *)data->img[2]);
//     printf("data->tex_Wall_N: %p\n", (void *)data->tex_Wall_N);
//     printf("data->tex_Wall_S: %p\n", (void *)data->tex_Wall_S);
//     printf("data->tex_Wall_E: %p\n", (void *)data->tex_Wall_E);
//     printf("data->tex_Wall_O: %p\n", (void *)data->tex_Wall_O);
//     printf("data->ray: %p\n", (void *)data->ray);
//     printf("data->ray->line: %p\n", (void *)data->ray->line);
//     printf("data->ray->line->tex_x: %p\n", (void *)&data->ray->line->tex_x);
// }

int	main( int argc, char **argv)
{
	t_data data;

	// data = *get_data();
	init_struct(&data);
	// verify_pointer(&data);
	ft_file_format(argc, argv[1]);
	ft_read_file(&data, argv);
	if (!ver_data(&data))
		ft_free(&data);
	ft_set_camera(&data);

	init_mlx(&data);
	
	ft_floor_sky(&data);
	ft_load_texture(&data);
	ft_trace_wall(&data, data.ray);
	// ft_restart_image(&data);
	// mlx_loop_hook(mlx, ft_hook, mlx);

	ft_put_pixel(&data);
	mlx_loop_hook(data.mlx, &ft_hook, &data);
	mlx_key_hook(data.mlx, &ft_option, &data);
	mlx_set_cursor_mode(data.mlx, 0x00034002);
	// mlx_cursor_hook(data.mlx, &mouse_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	ft_free(&data);
	return (EXIT_SUCCESS);
}
