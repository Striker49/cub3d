#include <stdio.h>
#include "cub3d.h"
#include <stdlib.h>
#include <stdbool.h>

int	main( int argc, char **argv)
{
	t_data data;

	init_struct(&data);
	ft_file_format(argc, argv[1]);
	ft_read_file(&data, argv);
	if (!ver_data(&data))
		ft_free(&data);

	init_mlx(&data);
	
	ft_floor_sky(&data);
	ft_load_texture(&data);
	ft_trace_wall(&data, data.ray);
	// ft_restart_image(&data);
	// mlx_loop_hook(mlx, ft_hook, mlx);

	ft_put_pixel(&data);
	mlx_loop_hook(data.mlx, &ft_hook, &data);
	mlx_key_hook(data.mlx, &ft_option, &data);
	// mlx_set_cursor_mode(data.mlx, 0x00034002);
	// mlx_cursor_hook(data.mlx, &mouse_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	ft_free(&data);
	return (EXIT_SUCCESS);
}
